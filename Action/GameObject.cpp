//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Game.h"
#include "Math.h"
#include "GameObject.h"
#include "Component.h"
#include "InputSystem.h"
#include "PhysicsWorld.h"
#include "MainCameraObject.h"
#include "TitleCameraObject.h"
#include "ResultCameraObject.h"
#include "CameraObjectBase.h"
#include "AutoMoveCamera.h"

int GameObject::gameObjectId = 0;
CameraObjectBase* GameObject::mainCamera = nullptr;
TitleCameraObject* GameObject::titleCamera = nullptr;
ResultCameraObject* GameObject::resultCamera = nullptr;

std::vector<GameObject*> GameObject::pendingGameObjects;
std::unordered_map<Tag, std::vector<GameObject*>> GameObject::gameObjectMap;
bool GameObject::updatingGameObject = false;

/*
@fn コンストラクタ
@param	再利用するかどうかのフラグ
@param	オブジェクト判別用tag
*/
GameObject::GameObject(bool _reUseGameObject,const Tag _objectTag)
	: state(Active)
	, worldTransform()
	, position(Vector3::Zero)
	, scale(Vector3(1.0f, 1.0f, 1.0f))
	, rotation(Quaternion::Identity)
	, recomputeWorldTransform(true)
	, MyObjectId(gameObjectId)
	, tag(_objectTag)
	, reUseObject(_reUseGameObject)
	, aabb({ Vector3::Zero,Vector3::Zero })
	, isPushBackToPlayer(false)
	, isSendVelocityToPlayer(false)
	, isCheckGroundToPlayer(false)
	, isPushBackToCamera(false)
	, luminance(0.0f)
{

	//IDに数値を1追加
	++gameObjectId;

	//GameObjectManagerにポインタを渡す
	AddGameObject(this);

}

GameObject::~GameObject()
{
	//GameObjectManagerからポインタを削除する
	RemoveGameObject(this);

	while (!components.empty())
	{
		delete components.back();
	}

	// 消されたタイミングでオブジェクトIDの総数を減らす
	gameObjectId--;
}

/*
@brief	フレーム毎の処理
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::Update(float _deltaTime)
{
	//更新状態がアクティブ
	if (state != Dead)
	{
		//Transformのワールド変換
		ComputeWorldTransform();
		//ゲームオブジェクトの更新
		UpdateGameObject(_deltaTime);
		//このゲームオブジェクトに付属するコンポーネントの更新
		UpdateComponents(_deltaTime);
		//Transformのワールド変換
		ComputeWorldTransform();
	}
	else
	{
		UpdateComponents(_deltaTime);
	}
}

/*
@brief	アタッチされてるコンポーネントのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::UpdateComponents(float _deltaTime)
{
	// Deadでなかったら更新処理を行う
	if (state != State::Dead)
	{	
		for (auto itr : components)
		{
			itr->Update(_deltaTime);
		}
	}

}

/*
@brief	ゲームオブジェクトのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::UpdateGameObject(float _deltaTime)
{
}

/*
@fn 入力状態を受け取りGameObjectとComponentの入力更新関数を呼び出す
@param	_keyState 入力情報
*/
void GameObject::ProcessInput(const InputState& _keyState)
{
	//コンポーネントの入力関数にコントローラーの入力状態を
	for (auto comp : components)
	{
		comp->ProcessInput(_keyState);
	}
	//ゲームオブジェクトの入力関数にコントローラーの入力状態を
	GameObjectInput(_keyState);
}

/*
@fn 入力を引数で受け取る更新関数
@brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
@param	_keyState 入力情報
*/
void GameObject::GameObjectInput(const InputState & _keyState)
{
}

/*
@brief	コンポーネントを追加する
@param	追加するコンポーネントのポインタ
*/
void GameObject::AddComponent(Component * _component)
{
	// 更新を考慮しコンポーネントを配列に追加
	int order = _component->GetUpdateOder();
	auto itr = components.begin();
	for (;
		itr != components.end();
		++itr)
	{
		if (order < (*itr)->GetUpdateOder())
		{
			break;
		}
	}
	components.insert(itr, _component);
}

/*
@brief	コンポーネントを削除する
@param	削除するコンポーネントのポインタ
*/
void GameObject::RemoveComponent(Component * _component)
{
	// 削除するコンポーネントを探して削除
	auto itr = std::find(components.begin(), components.end(), _component);
	if (itr != components.end())
	{
		components.erase(itr);
	}
}

/*
@fn 現在の仕様上行うことができない処理を外部から強引に行うための関数
@exsample ゲームオブジェクト全体の更新が停止中に対象のゲームオブジェクトを更新する
*/
void GameObject::ExceptionUpdate()
{
	ComputeWorldTransform();

	UpdateGameObject(0.016f);
	UpdateComponents(0.016f);

	ComputeWorldTransform();
}

/*
@brief	Transformのワールド変換
*/
void GameObject::ComputeWorldTransform()
{
	// ワールド座標を変換する必要がある際更新をかける
	if (recomputeWorldTransform)
	{
		// フラグをおろしScale・rotation・positionを更新
		recomputeWorldTransform = false;
		worldTransform = Matrix4::CreateScale(scale);
		worldTransform *= Matrix4::CreateFromQuaternion(rotation);
		worldTransform *= Matrix4::CreateTranslation(position);

		// コンポーネントによる更新がある場合更新をする
		for (auto itr : components)
		{
			itr->OnUpdateWorldTransform();
		}
	}
}

/*
@fn 押し戻し関数(仮想関数)
@brief 押し戻しを行う
@param myAABB 自分のAABB
@param pairAABB 相手のAABB
@param _pairTag 相手がなんのオブジェクトなのか見る用のTag
*/
void GameObject::FixCollision(const AABB & myAABB, const AABB & pairAABB, const Tag& _pairTag)
{
	Vector3 ment = Vector3(0, 0, 0);
	CalcCollisionFixVec(myAABB, pairAABB, ment);
	SetPosition(GetPosition() + (ment));
}

/*
@fn 静的なmainCameraを生成する
@param _pos ポジション
@param _playerObject 追従するプレイヤーのポインタ
*/
void GameObject::CreateMainCamera(const Vector3 _pos, PlayerObject* _playerObject)
{
	//mainCamera = new MainCameraObject(_pos,_playerObject);
	mainCamera = new AutoMoveCamera(_pos, _playerObject);
}

/*
@fn 静的なtitleCameraを生成する
@param _pos ポジション
*/
void GameObject::CreateTitleCamera(const Vector3 _pos)
{
	titleCamera = new TitleCameraObject(_pos);
}

/*
@fn 静的なtitleCameraを生成する
@param _pos ポジション
*/
void GameObject::CreateResultCamera(const Vector3 _pos)
{
	resultCamera = new ResultCameraObject(_pos);
}

/*
@brief　tagを使用してGameObjectを探すための関数
@return	std::vector<GameObject*>を返す
*/
std::vector<GameObject*> GameObject::FindGameObject(Tag _tag)
{
	// Mapから必要なオブジェクト配列を探して返す
	return gameObjectMap.find(_tag)->second;
}

/*
@brief　GameObjectの追加
@param	追加するGameObjectのポインタ
*/
void GameObject::AddGameObject(GameObject* _object)
{
	// 途中で追加されたオブジェクトを一度一時追加用配列に追加
	if (updatingGameObject)
	{
		pendingGameObjects.emplace_back(_object);
	}
	else
	{
		// 途中追加でない場合最初にそれぞれの配列に追加
		auto gameObjects = gameObjectMap.find(_object->GetTag());
		if (gameObjects != gameObjectMap.end())
		{
			gameObjects->second.emplace_back(_object);
		}
		else
		{
			std::vector<GameObject*> tmpVector;
			tmpVector.emplace_back(_object);
			gameObjectMap[_object->GetTag()] = tmpVector;
		}
	}
}

/*
@brief　GameObjectの削除
@param	削除するGameObjectのポインタ
*/
void GameObject::RemoveGameObject(GameObject* _object)
{
	// 途中追加用配列に対象のオブジェクトがあった場合削除する
	auto itr = std::find(pendingGameObjects.begin(), pendingGameObjects.end(), _object);
	if (itr != pendingGameObjects.end())
	{
		std::iter_swap(itr, pendingGameObjects.end() - 1);
		pendingGameObjects.pop_back();
	}

	// 全体のgameObject配列に対象のオブジェクトがあった場合削除する
	auto gameObjects = gameObjectMap.find(_object->GetTag())->second;
	itr = std::find(gameObjects.begin(), gameObjects.end(), _object);
	if (itr != gameObjects.end())
	{
		std::iter_swap(itr, gameObjects.end() - 1);
		gameObjects.pop_back();
	}

}

/*
@brief　使用した全てのGameObjectの削除
*/
void GameObject::RemoveUsedGameObject()
{
	// 現在シーン上に作られているオブジェクトを全て削除する
	for (auto itr = GameObject::gameObjectMap.begin(); itr != GameObject::gameObjectMap.end(); ++itr)
	{
		for (auto gameObject : itr->second)
		{
			delete gameObject;
		}
		itr->second.clear();
	}
	gameObjectMap.clear();
}

/*
@fn オブジェクトの回転を計算する関数
@brief 前方ベクトルを使用してオブジェクトを回転させる
@param forward 前方ベクトル
*/
void GameObject::RotateToNewForward(const Vector3& forward)
{
	// X軸ベクトル(1,0,0)とforwardの間の角度を求める
	float dot = Vector3::Dot(Vector3::UnitX, forward);
	float angle = Math::Acos(dot);
	// 下向きだった場合
	if (dot > 0.9999f)
	{
		SetRotation(Quaternion::Identity);
	}
	// 上向きだった場合
	else if (dot < -0.9999f)
	{
		SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	}
	else
	{
		// 軸ベクトルとforwardとの外積から回転軸をもとめ、回転させる
		Vector3 axis = Vector3::Cross(Vector3::UnitX, forward);
		axis.Normalize();
		SetRotation(Quaternion(axis, angle));
	}
}

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void GameObject::CalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
{
	// 速度ベクトル初期化
	_calcFixVec = Vector3::Zero;

	// Boxを利用して判定を取る用の変数計算
	float dx1 = _fixedBox.min.x - _movableBox.max.x;
	float dx2 = _fixedBox.max.x - _movableBox.min.x;
	float dy1 = _fixedBox.min.y - _movableBox.max.y;
	float dy2 = _fixedBox.max.y - _movableBox.min.y;
	float dz1 = _fixedBox.min.z - _movableBox.max.z;
	float dz2 = _fixedBox.max.z - _movableBox.min.z;

	// dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;

	// x, y, zのうち最も差が小さい軸で位置を調整
	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		// xだったらx軸方向に押し戻し
		_calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		// yだったらx軸方向に押し戻し
		_calcFixVec.y = dy;
	}
	else
	{
		// zだったらx軸方向に押し戻し
		_calcFixVec.z = dz;
	}
}