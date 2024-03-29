#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SkeletalMeshComponent;
class Mesh;
class Animation;
class BoxCollider;
class EnemyObjectStateBase;
enum class EnemyState;

/*
@enum  MoveEnemyTag Enemyの移動方向を判別するタグ
*/
enum class MoveEnemyTag
{
	NOEN_MOVE,
	LEFT_MOVE,
	RIGHT_MOVE,
};

/*
@struct  MoveEnemyData
	左右に移動する敵が固有で持つデータ構造体
*/
struct MoveEnemyData
{
	MoveEnemyTag tag;
	Vector3 direction;
	float distance;
	float speed;
};


/*
@file EnemyObjectBase.h
@brief 敵オブジェクトの基底クラス
*/
class EnemyObjectBase :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@brief 通常のエネミーのコンストラクタ
	@param	ポジション
	@param	再利用するかフラグ
	@param	オブジェクト判別用tag
	*/
	EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag);

	/*
	@fn コンストラクタ
	@brief 移動するエネミーのコンストラクタ
	@param	ポジション
	@param	再利用するかフラグ
	@param	オブジェクト判別用tag
	@param	移動する敵のデータ構造体
	*/
	EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag, MoveEnemyData _moveEnemyData);

	/*
	@fn コンストラクタ
	@brief 移動するエネミーのコンストラクタ
	@param	ポジション
	@param	再利用するかフラグ
	@param	オブジェクト判別用tag
	@param	移動速度
	*/
	EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag, float _moveSpeed);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	virtual ~EnemyObjectBase() {};

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	virtual void UpdateGameObject(float _deltaTime) {};

	/*
	@fn めり込み判定
	*/
	virtual void FixCollision(AABB& myAABB, const AABB& pairAABB) {};


protected:

	/*
	@brief ステートプール用マップにステートクラスを追加する関数
	@param	_state 追加するステートクラスのポインタ
	@param	_stateTag 鍵となるタグ
	*/
	void AddStatePoolMap(EnemyObjectStateBase* _state, EnemyState _stateTag);

	/*
	@brief ステートプール用マップからステートクラスを削除する関数
	@param	_stateTag 鍵となるタグ
	*/
	void RemoveStatePoolMap(EnemyState _stateTag);

	/*
	@brief ステートプール用マップをクリアする
	*/
	void ClearStatePoolMap();

	// 3Dモデルの描画を行うクラス
	SkeletalMeshComponent* skeltalMeshComponent;
	// Meshの読み込みを行うクラス
	Mesh* mesh;
	// AABBの当たり判定を行うクラス
	BoxCollider* boxCollider;
	// エネミーのAABB構造体
	AABB enemyBox;

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/
	virtual void OnCollision(const GameObject& _hitObject) {};

	//右方向ベクトル
	Vector3 rightVec;
	//キャラクターの前方ベクトル
	Vector3 charaForwardVec;
	//方向に合わせて回転させるためのベクトル
	Vector3 rotateVec;
	// 初期位置
	Vector3 firstPosition;
	// 初期位置
	Vector3 respawnPosition;
	// 移動方向
	Vector3 moveDirection;
	// 自分を倒したオブジェクトのポジション
	Vector3 defeatedObjectPosition;

	// 攻撃対象オブジェクトのポジション
	Vector3 attackObjectPosition;

	// AABBの最小値
	const Vector3 BoxMin;
	// AABBの最大値
	const Vector3 BoxMax;
	// 大きさ
	const Vector3 Size;


	// 初期位置からリスポーンするポジションを計算するための間隔
	const float respawnPositionOffset;
	// 速度
	float moveSpeed;
	// 移動距離
	float moveDistance;

	//接地フラグ
	bool onGround;
	// 死んでいるかどうか
	bool isDead;
	// 怯んでいるかどうか
	bool isFlinch;
	// 追跡相手をとらえているかどうか
	bool isTracking;
	// 攻撃モーション中か
	bool isAttack;
	bool isVisible;

	// 移動する敵のTag
	MoveEnemyTag moveEnemyTag;

	// 今のenemyのstate状態を保存するための変数
	EnemyState nowState;
	// 変更された次のenemyのstate状態を保存するための変数
	EnemyState nextState;
	// Animationプール
	std::vector<const Animation*> animTypes;
	// 全stateが格納されるマップ
	std::unordered_map<EnemyState, EnemyObjectStateBase*> statePoolMap;

public:// ゲッターセッター

	/*
	@fn skeltalMeshComponentのgetter関数
	@return SkeletalMeshComponent　SkeletalMeshComponentクラスのポインタを返す
	*/
	SkeletalMeshComponent* GetSkeletalMeshComponent() { return skeltalMeshComponent; }

	/*
	@fn Animationのgetter関数
	@param _state 現在のエネミーのステータス
	@return Animation Animationクラスのポインタを返す
	*/
	const Animation* GetAnimation(EnemyState _state);

	/*
	@fn forwardVecのgetter関数
	@return Vector3 forwardVec 前方ベクトルを返す
	*/
	Vector3 GetForwardVec() { return forwardVec; }

	/*
	@fn rightVecのgetter関数
	@return Vector3 rightVec 右方向ベクトルを返す
	*/
	Vector3 GetRightVec() { return rightVec; }

	/*
	@fn charaForwardVecのgetter関数
	@return charaForwardVecを返す
	*/
	Vector3 GetCharaForwardVec() { return charaForwardVec; }

	/*
	@fn rotateVecのgetter関数
	@return Vector3 rotateVec 回転値を返す
	*/
	Vector3 GetRotateVec() { return rotateVec; }

	/*
	@fn velocityのgetter関数
	@return Vector3 velocity 速度を返す
	*/
	Vector3 GetVelocity() { return velocity; }

	/*
	@fn moveDirectionのgetter関数
	@return Vector3 moveDirection 移動方向を返す
	*/
	Vector3 GetMoveDirection() { return moveDirection; }

	/*
	@fn firstPositionのgetter関数
	@return Vector3 firstPosition 初期ポジションを返す
	*/
	Vector3 GetFirstPosition() { return firstPosition; }

	/*
	@fn respawnPositionのgetter関数
	@return Vector3 respawnPosition リスポーンする場所を返す
	*/
	Vector3 GetRespawnPosition() { return respawnPosition; }

	/*
	@fn defeatedObjectPositionのgetter関数
	@return Vector3 defeatedObjectPosition 自分を倒したオブジェクトのポジションを返す
	*/
	Vector3 GetDefeatedObjectPosition() { return defeatedObjectPosition; }
	
	/*
	@fn attackObjectPositionのgetter関数
	@return Vector3 defeatedObjectPosition 自分を倒したオブジェクトのポジションを返す
	*/
	Vector3 GetAttackObjectPosition() { return attackObjectPosition; }

	/*
	@fn moveDistanceのgetter関数
	@return moveDistanceを返す
	*/
	float GetMoveDistance() { return moveDistance; }

	/*
	@fn moveSpeedのgetter関数
	@return moveSpeedを返す
	*/
	float GetMoveSpeed() { return moveSpeed; }

	/*
	@fn onGroundのgetter関数
	@return onGroundを返す
	*/
	bool GetOnGround() { return onGround; }

	/*
	@fn isDeadFlagのGettrer関数
	@return	bool isDeadFlag 死亡状態を返す
	*/
	bool GetIsDead() { return isDead; }
	
	/*
	@fn isFlinchのGettrer関数
	@return	bool isFlinch 怯み状態かどうかを返す
	*/
	bool GetIsFlinch() { return isFlinch; }

	/*
	@fn isTrackingのGettrer関数
	@return	bool isTracking 追跡するオブジェクトを捉えているかを返す
	*/
	bool GetIsTracking() { return isTracking; }
	
	/*
	@fn isVisibleのGettrer関数
	@return	bool isVisible 表示中かどうかを返す
	*/
	bool GetIsVisible() { return isVisible; }

	/*
	@fn nowStateのgetter関数
	@return EnemyState nowState 現在のステータスを返す
	*/
	EnemyState GetNowState() { return nowState; }

	/*
	@fn moveEnemyTagのgetter関数
	@return MoveEnemyTag moveEnemyTag 移動方向を指すTagを返す
	*/
	MoveEnemyTag GetMoveEnemyTag() { return moveEnemyTag; }

	/*
	@fn charaForwardVecのsetter関数
	@param	Vector3 _charaForwardVec キャラクターの前方ベクトル
	*/
	void SetCharaForwardVec(Vector3 _charaForwardVec) { charaForwardVec = _charaForwardVec; }

	/*
	@fn velocityのsetter関数
	@param	Vector3 _velocity キャラクターの速度ベクトル
	*/
	void SetAttackObjectPosition(Vector3 _attackObjectPosition) { attackObjectPosition = _attackObjectPosition; }

	/*
	@fn velocityのsetter関数
	@param	Vector3 _velocity キャラクターの速度ベクトル
	*/
	void SetVelocity(Vector3 _velocity) { velocity = _velocity; }

	/*
	@fn velocityのsetter関数
	@param	Vector3 _moveDirection キャラクターの移動方向ベクトル
	*/
	void SetMoveDirection(Vector3 _moveDirection) { moveDirection = _moveDirection; }

	/*
	@fn moveDistanceのsetter関数
	@param	float moveDistance キャラクターの移動距離
	*/
	void SetMoveDistance(float _moveDistance) { moveDistance = _moveDistance; }

	/*
	@fn moveSpeedのsetter関数
	@param	float _moveSpeed キャラクターのスピード
	*/
	void SetMoveSpeed(float _moveSpeed) { moveSpeed = _moveSpeed; }

	/*
	@fn isDeadFlagのsetter関数
	@param	bool isDeadFlag 死亡状態
	*/
	void SetIsDead(bool _isDeadFlag) { isDead = _isDeadFlag; }

	/*
	@fn isDeadFlagのsetter関数
	@param	bool isDeadFlag 死亡状態
	*/
	void SetIsFlinch(bool _isFlinch) { isFlinch = _isFlinch; }

	/*
	@fn isTrackingのsetter関数
	@param	bool _isTracking キャラクターの前方ベクトル
	*/
	void SetIsTracking(bool _isTracking) { isTracking = _isTracking; }

	/*
	@fn isAttackのsetter関数
	@param	bool isAttack 攻撃状態かどうか
	*/
	void SetIsAttack(bool _isAttack) { isAttack = _isAttack; }
	
	/*
	@fn isVisibleのsetter関数
	@param	bool isVisible 表示中かどうか
	*/
	void SetIsVisible(bool _isVisible) { isVisible = _isVisible; }
};