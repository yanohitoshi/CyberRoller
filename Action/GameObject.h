#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include <vector>
#include <functional>
#include "Math.h"
#include "Collision.h"
#include <unordered_map>
#include "Game.h"

// クラスの前方宣言
class Vector3;
class Matrix4;
class Component;
struct InputState;
class ColliderComponent;
class MainCameraObject;
class PlayerObject;
enum class PhysicsTag;

/*
@brief	ゲームオブジェクトの状態
*/
enum State
{
	//アクティブ
	Active,
	//更新が停止している
	Paused,
	// 無効化状態
	Disabling,
	//オブジェクトの更新が終了(外部からのみActiveに変更可能)
	Dead
};

/*
@enum　GameObjectタグ(objectがなんなのかの判別に使用)
*/
enum Tag
{
	// その他
	OTHER,
	// カメラ
	CAMERA,
	// カメラ変更ポイント
	CAMERA_CHANGE_OBLIQUE,
	// プレイヤー
	PLAYER,
	// ジャンプアタック時のプレイヤー
	JUMP_ATTACK_PLAYER,
	// エネミー
	ENEMY,
	// プレイヤー追跡エリア
	PLAYER_TRACKING_AREA,
	// グラウンド
	GROUND,
	// 動くグラウンド
	MOVE_GROUND,
	// 壊れるグラウンド
	BREAK_GROUND,
	// 壁
	WALL,
	// 爆弾
	BOMB,
	// 爆発エリア
	EXPLOSION_AREA,
	// 棘
	NEEDLE,
	// 棘用パネル
	NEEDLE_PANEL,
	// 押し出し板
	PUSH_BOARD,
	// 押し出し板のベース
	PUSH_BOX,
	// 最初の動く壁
	FIRST_MOVE_WALL,
	// 2番目の動く壁
	SECOND_MOVE_WALL,
	// ゲームクリア前の動く壁
	CLEAR_SCENE_MOVE_WALL,
	// 最初の区画のスイッチ
	FIRST_SWITCH,
	// 2番目の区画のスイッチ
	SECOND_SWITCH,
	// ゲームクリア前のスイッチ
	CLEAR_SCENE_SWITCH,
	// ジャンプスイッチ
	JUMP_SWITCH,
	// スイッチのベースオブジェクト
	SWITCH_BASE,
	// 収集物
	COLLECTION,
	// シーン
	SCENE,
	// ゲームクリアオブジェクト
	CLEAR_POINT,
	// リスポーンポイント
	RESPOWN_POINT,
	// UI
	UI,
	// タイトル上のオブジェクト
	TITLE_OBJECT,
	// タイトルで自動で動くプレイヤーオブジェクト
	TITLE_PLAYER,
	// タイトル上のオブジェクト
	RESULT_OBJECT,
	// パーティクル
	PARTICLE,
};

/*
@enum　動く方向のタグ
*/
enum MoveDirectionTag
{
	// X軸方向
	MOVE_X,
	// Y軸方向
	MOVE_Y,
	// Z軸方向
	MOVE_Z
};

/*
@file GameObject.h
@brief ゲームオブジェクトの基底クラス
*/
class GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	再利用するかどうかのフラグ
	@param	オブジェクト判別用tag
	*/
	GameObject(bool _reUseGameObject,const Tag _objectTag);

	/*
	@brief	デストラクタ
	*/
	virtual ~GameObject();

	/*
	@brief	フレーム毎の処理
	@param	最後のフレームを完了するのに要した時間
	*/
	void Update(float _deltaTime);

	/*
	@brief	アタッチされてるコンポーネントのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateComponents(float _deltaTime);

	/*
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float _deltaTime);

	/*
	@fn 入力状態を受け取りGameObjectとComponentの入力更新関数を呼び出す
	@param	_keyState 入力情報
	*/
	void ProcessInput(const InputState& _keyState);

	/*
	@fn 入力を引数で受け取る更新関数
	@brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
	@param	_keyState 入力情報
	*/
	virtual void GameObjectInput(const InputState& _keyState);

	/*
	@brief	コンポーネントを追加する
	@param	追加するコンポーネントのポインタ
	*/
	void AddComponent(Component* _component);

	/*
	@brief	コンポーネントを削除する
	@param	削除するコンポーネントのポインタ
	*/
	void RemoveComponent(Component* _component);

	/*
	@fn 現在の仕様上行うことができない処理を外部から強引に行うための関数
	@exsample ゲームオブジェクト全体の更新が停止中に対象のゲームオブジェクトを更新する
	*/
	void ExceptionUpdate();
	/*
	@brief	Transformのワールド変換
	*/
	void ComputeWorldTransform();

	/*
	@fn 押し戻し関数(仮想関数)
	@brief 押し戻しを行う
	@param myAABB 自分のAABB
	@param pairAABB 相手のAABB
	@param _pairTag 相手がなんのオブジェクトなのか見る用のTag
	*/
	virtual void FixCollision(const AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag);

	/*
	@fn オブジェクトの回転を計算する関数
	@brief 前方ベクトルを使用してオブジェクトを回転させる
	@param forward 前方ベクトル
	*/
	void RotateToNewForward(const Vector3& forward);

	/*
	@fn 静的なmainCameraを生成する
	@param _pos ポジション
	@param _playerObject 追従するプレイヤーのポインタ
	*/
	static void CreateMainCamera(const Vector3 _pos, PlayerObject* _playerObject);

	/*
	@fn 静的なtitleCameraを生成する
	@param _pos ポジション
	*/
	static void CreateTitleCamera(const Vector3 _pos);

	/*
	@fn 静的なtitleCameraを生成する
	@param _pos ポジション
	*/
	static void CreateResultCamera(const Vector3 _pos);

	/*
	@brief　tagを使用してGameObjectを探すための関数
	@return	std::vector<GameObject*>を返す
	*/
	static std::vector<GameObject*> FindGameObject(Tag _tag);

	/*
	@brief　使用した全てのGameObjectの削除
	*/
	static 	void RemoveUsedGameObject();


protected:

	std::function<void(GameObject&, PhysicsTag)> GetOnCollisionFunc() { return std::bind(&GameObject::OnCollision, this, std::placeholders::_1, std::placeholders::_2); }
	virtual void OnCollision(const GameObject& _hitObject,const PhysicsTag _physicsTag) {}

	/*
	@fn 衝突したことが確定したとき、めり込みを戻す関数
	@param _movableBox 移動物体
	@param _fixedBox 移動しない物体
	@param _calcFixVec 移動物体の補正差分ベクトル
	*/
	void CalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);

	void Rotation(GameObject* _owner, const float _angle, const Vector3 _axis);

	// ゲーム中メインカメラ
	static class CameraObjectBase* mainCamera;
	// タイトル画面で使用するカメラ
	static class TitleCameraObject* titleCamera;
	// タイトル画面で使用するカメラ
	static class ResultCameraObject* resultCamera;

	//ゲームオブジェクトの状態
	State state;
	//ゲームオブジェクトのタグ
	Tag tag;
	//ゲームオブジェクトのID、カウント用
	static int gameObjectId;

	//このゲームオブジェクトのID
	const int MyObjectId;

	//Transform
	Vector3 position;
	Quaternion rotation;
	Vector3 scale;
	Matrix4 worldTransform;
	Vector3 velocity;
	Vector3 forwardVec;

	// オブジェクトの輝度
	float luminance;

	// AABB
	AABB aabb;

	//ワールド変換の処理を行う必要性があるか
	bool recomputeWorldTransform;

	//switch用フラグ
	bool onFlag;

	// プレイヤーと押し戻しを行うオブジェクトかどうか
	bool isPushBackToPlayer;

	// 速度がプレイヤーに関与するかどうか
	bool isSendVelocityToPlayer;

	// プレイヤーと接地判定を行うかどうか
	bool isCheckGroundToPlayer;

	// カメラと押し戻しを行うオブジェクトかどうか
	bool isPushBackToCamera;

	//アタッチされているコンポーネント
	std::vector<class Component*>components;

private:

	/*
	@brief　GameObjectの追加
	@param	追加するGameObjectのポインタ
	*/
	static void AddGameObject(GameObject* _object);

	/*
	@brief　GameObjectの削除
	@param	削除するGameObjectのポインタ
	*/
	static void RemoveGameObject(GameObject* _object);


	//シーンを跨ぐ際に開放されるオブジェクトかどうか、カメラなどが対象になる
	bool reUseObject;
	// 途中追加される際一時的に保存される可変長配列
	static std::vector<GameObject*> pendingGameObjects;
	// 全オブジェクトが格納される連想可変長配列
	static std::unordered_map<Tag, std::vector<GameObject*>> gameObjectMap;
	// GameObjectの更新フラグ
	static bool updatingGameObject;

	/*
	@brief  ゲームオブジェクトのアップデート処理
	*/
	friend void UpdateGameObjects(float _deltaTime);

	/*
	@brief  ゲームオブジェクトの入力処理
	*/
	friend void ProcessInputs(const InputState & _state);
	
public://ゲッターセッター

	/*
	@brief　オブジェクトのポジションを取得する
	@return	position
	*/
	const Vector3& GetPosition() const { return position; }

	/*
	@brief　オブジェクトのポジションを設定する
	@param	position
	*/
	virtual void SetPosition(const Vector3& _pos) { position = _pos; recomputeWorldTransform = true; }

	/*
	@brief　ワールド座標の再変換フラグのgetter
	@return	recomputeWorldTransform
	*/
	bool GetRecomputeWorldTransform() { return recomputeWorldTransform; }

	/*
	@brief　オブジェクトのスケールを取得する
	@return	scale
	*/
	Vector3 GetScaleFloat() const { return scale; }

	/*
	@brief　オブジェクトのスケールを設定する(x.y.zの比率が同じとき)
	@param	scale float型
	*/
	void SetScale(float _scale) { scale.x = _scale; scale.y = _scale; scale.z = _scale; recomputeWorldTransform = true; }

	/*
	@brief　オブジェクトのスケールを設定する(x軸のみの場合)
	@param	scale float型
	*/
	void SetScaleX(float _scale) { scale.x = _scale; recomputeWorldTransform = true; }

	/*
	@brief　オブジェクトのスケールを設定する(y軸のみの場合)
	@param	scale float型
	*/
	void SetScaleY(float _scale) { scale.y = _scale; recomputeWorldTransform = true; }

	/*
	@brief　オブジェクトのスケールを設定する(z軸のみの場合)
	@param	scale float型
	*/
	void SetScaleZ(float _scale) { scale.z = _scale; recomputeWorldTransform = true; }

	/*
	@brief　オブジェクトのスケールを設定する(x.y.zの比率が違うとき)
	@param	scale Vector3型
	*/
	void SetScale(Vector3 _scale) { scale.x = _scale.x; scale.y = _scale.y; scale.z = _scale.z; recomputeWorldTransform = true; }

	/*
	@brief　オブジェクトのスケールを取得(x.y.zの比率が同じとき)
	@return	scale Vector3型
	*/
	float GetScale() { return scale.x; }

	/*
	@brief　オブジェクトのスケールを取得する(x.y.zの比率が違うとき)
	@return	scale Vector3型
	*/
	Vector3 GetScaleVec() { return scale; }

	/*
	@brief　オブジェクトの輝度を取得
	@return	luminance 輝度
	*/
	float GetLuminance() { return luminance; }

	/*
	@brief　オブジェクトのクォータニオンを取得する
	@return	rotation（Quaternion型）
	*/
	const Quaternion& GetRotation() const { return rotation; }

	/*
	@brief　オブジェクトのクォータニオンを設定する
	@param	rotation（Quaternion型）
	*/
	virtual void SetRotation(const Quaternion& _qotation) { rotation = _qotation;  recomputeWorldTransform = true; }

	/*
	@brief　オブジェクトの状態を取得する
	@return	state
	*/
	State GetState() const { return state; }

	/*
	@brief　オブジェクトの状態を設定する
	@param	state
	*/
	virtual void SetState(State _state) { state = _state; }

	/*
	@brief　オブジェクトのワールド行列を取得する
	@return	worldTransform
	*/
	const Matrix4& GetWorldTransform() const { return worldTransform; }

	/*
	@brief　オブジェクトの前方を表すベクトルを取得する
	@param	forward(Vector3型)
	*/
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, rotation); }

	/*
	@brief　オブジェクトの右を表すベクトルを取得する
	@param	right(Vector3型)
	*/
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, rotation); }

	/*
	@brief　オブジェクトの上を表すベクトルを取得する
	@param	up(Vector3型)
	*/
	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitZ, rotation); }

	/*
	@brief　オブジェクトの上を表すベクトルを取得する
	@param	up(Vector3型)
	*/
	Vector3 GetForwardVec() const { return forwardVec; }

	/*
	@fn Tagのgetter関数
	@brief オブジェクトを識別するTagを取得
	@return Tag オブジェクトを識別するTag
	*/
	Tag GetTag() const { return tag; }

	/*
	@fn aabbのgetter関数
	@brief オブジェクトのワールド空間でのAABBの取得
	@return aabb オブジェクトそれぞれでワールド空間でのAABBの値を保存している変数
	*/
	AABB GetAabb() const { return aabb; }

	/*
	@fn myObjectId変数のgetter関数
	@brief それぞれのオブジェクトが持つIDの取得
	@return int myObjectId それぞれのオブジェクトが持つID
	*/
	int GetObjectId() const { return MyObjectId; };

	/*
	@fn gameObjectId変数のgetter関数
	@brief 全オブジェクト総数を確認するためのトータルIDの取得
	@return int gameObjectId オブジェクトが生成されるたびに1増えるID
	*/
	static int GetTotalObjectId() { return gameObjectId; };

	/*
	@fn reUseObject変数のgetter関数
	@brief シーンをまたいで利用するかどうかフラグの取得
	@return bool reUseObject シーンをまたいで利用するかどうかフラグ
	*/
	bool GetReUseGameObject() { return reUseObject; }

	/*
	@brief　プレイヤーと押し戻し判定を行うかフラグのgetter
	@return	isPushBackToPlayer
	*/
	bool GetisPushBackToPlayer() const { return isPushBackToPlayer; }

	/*
	@brief　プレイヤーに速度を送るオブジェクトかどうかフラグのgetter
	@return	isSendVelocityToPlayer
	*/
	bool GetisSendVelocityToPlayer() const { return isSendVelocityToPlayer; }

	/*
	@brief　プレイヤーと押し戻し判定を行うかフラグのgetter
	@return	isCheckGroundToPlayer
	*/
	bool GetIsCheckGroundToPlayer() const { return isCheckGroundToPlayer; }

	/*
	@brief　カメラと押し戻し判定を行うかフラグのgetter
	@return	isPushBackToPlayer
	*/
	bool GetisPushBackToCamera() const { return isPushBackToCamera; }

	/*
	@brief　スイッチ用フラグのgetter
	@return	onFlag
	*/
	bool GetSwitchFlag() { return onFlag; }

	/*
	@brief　Velocityのgettta関数
	@param	velocity(Vector3型)
	*/
	const Vector3& GetVelocity() const { return velocity; }

	/*
	@brief　メインカメラのgetter
	@return	MainCameraObject*　メインカメラを返す
	*/
	static CameraObjectBase* GetMainCamera() { return mainCamera; }
};

