//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TitlePlayerObject.h"
#include "SkeletalMeshComponent.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"
#include "TitlePlayerStateBase.h"
#include "TitleJumpAttackPlayerObject.h"
#include "TitlePlayerStateJumpAttack.h"
#include "TitlePlayerStateJumpLoop.h"
#include "TitlePlayerStateJumpStart.h"
#include "TitlePlayerStateRun.h"

/*
@fn コンストラクタ
@param	ポジション
@param	再利用するかフラグ
@param	オブジェクト判別用tag
*/
TitlePlayerObject::TitlePlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
	, InitPosition(_pos)
	, RotationAngle(90.0f)
{
	// メンバー変数初期化
	jumpCount = 0;
	jumpFlag = false;
	// ポジションをセット
	SetPosition(_pos);

	//モデル描画用のコンポーネント
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMes hをセット(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERING_OBJECT_MANAGER->CreateMesh("Assets/Model/Player/model/SK_Rob.gpmesh"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERING_OBJECT_MANAGER->CreateSkeleton("Assets/Model/Player/model/SK_Rob.gpskel"));
	//メッシュ情報取得
	mesh = skeltalMeshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	//アニメ―ション用の可変長配列をリサイズ
	animTypes.resize(static_cast<unsigned int>(TitlePlayerState::STATE_NUM));
	//アニメーションを読み込み
	animTypes[static_cast<unsigned int>(TitlePlayerState::RUN)] = RENDERING_OBJECT_MANAGER->CreateAnimation("Assets/Model/Player/animation/Running.gpanim", true);
	animTypes[static_cast<unsigned int>(TitlePlayerState::JUMP_LOOP)] = RENDERING_OBJECT_MANAGER->CreateAnimation("Assets/Model/Player/animation/Floating.gpanim", true);
	animTypes[static_cast<unsigned int>(TitlePlayerState::JUMP_START)] = RENDERING_OBJECT_MANAGER->CreateAnimation("Assets/Model/Player/animation/Jump_up.gpanim", false);

	AddStatePoolMap(new TitlePlayerStateJumpAttack, TitlePlayerState::JUMP_ATTACK);
	AddStatePoolMap(new TitlePlayerStateJumpLoop, TitlePlayerState::JUMP_LOOP);
	AddStatePoolMap(new TitlePlayerStateJumpStart, TitlePlayerState::JUMP_START);
	AddStatePoolMap(new TitlePlayerStateRun, TitlePlayerState::RUN);

	// 回転処理
	RotationProcess(RotationAngle,Vector3::UnitZ);

	// タイトル用ジャンプアタックプレイヤーを追加
	titleJumpAttackPlayerObject = new TitleJumpAttackPlayerObject(this, Vector3(50.0f, 50.0f, 50.0f), JUMP_ATTACK_PLAYER);

	// ステータスの初期化
	nowState = TitlePlayerState::STATE_NUM;
	nextState = TitlePlayerState::RUN;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
TitlePlayerObject::~TitlePlayerObject()
{
	RemoveStatePoolMap(TitlePlayerState::JUMP_ATTACK);
	RemoveStatePoolMap(TitlePlayerState::JUMP_LOOP);
	RemoveStatePoolMap(TitlePlayerState::JUMP_START);
	RemoveStatePoolMap(TitlePlayerState::RUN);
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void TitlePlayerObject::UpdateGameObject(float _deltaTime)
{
	// Rendererにポジションを送る
	RENDERING_OBJECT_MANAGER->SetPlayerPositon(position);

	// ステート外部からステート変更があったか？
	if (nowState != nextState)
	{
		//マップの中に追加するアクターのコンテナがあるかどうかを調べる
		auto state = statePoolMap.find(nextState);
		if (state != statePoolMap.end())
		{
			statePoolMap[nextState]->Enter(this, _deltaTime);
		}

		nowState = nextState;
		return;
	}

	// ステート実行
	//マップの中に追加するアクターのコンテナがあるかどうかを調べる
	auto state = statePoolMap.find(nowState);
	if (state != statePoolMap.end())
	{
		nextState = statePoolMap[nowState]->Update(this, _deltaTime);
	}

	// ステート内部からステート変更あったか？
	if (nowState != nextState)
	{
		auto state = statePoolMap.find(nextState);
		if (state != statePoolMap.end())
		{
			statePoolMap[nextState]->Enter(this, _deltaTime);
		}
		nowState = nextState;
	}
}

/*
@fn 回転処理関数
*/
void TitlePlayerObject::RotationProcess(float _angle, Vector3 _axis)
{
	//Z軸を90度回転させる
	float radian = Math::ToRadians(_angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

/*
@brief ステートプール用マップにステートクラスを追加する関数
@param	_state 追加するステートクラスのポインタ
@param	_stateTag 鍵となるタグ
*/
void TitlePlayerObject::AddStatePoolMap(TitlePlayerStateBase* _state, TitlePlayerState _stateTag)
{
	//マップの中に追加するアクターのコンテナがあるかどうかを調べる
	auto stateMaps = statePoolMap.find(_stateTag);

	//あるとき
	if (stateMaps != statePoolMap.end())
	{
		return;
	}
	else //ないとき
	{
		statePoolMap[_stateTag] = _state;
	}
}

/*
@brief ステートプール用マップからステートクラスを削除する関数
@param	_stateTag 鍵となるタグ
*/
void TitlePlayerObject::RemoveStatePoolMap(TitlePlayerState _stateTag)
{
	delete statePoolMap[_stateTag];
}

/*
@brief ステートプール用マップをクリアする
*/
void TitlePlayerObject::ClearStatePoolMap()
{
	statePoolMap.clear();
}

/*
@fn Animationのgetter関数
@param _state 現在のプレイヤーのステータス
@return Animation Animationクラスのポインタを返す
*/
const Animation* TitlePlayerObject::GetAnimation(TitlePlayerState _state)
{
	// _state番目のアニメーションを返す
	return animTypes[static_cast<unsigned int>(_state)];
}