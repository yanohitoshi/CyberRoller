#pragma once
#include "GameObject.h"

// classの前置宣言
class SkeletalMeshComponent;
class Animation;
class BoxCollider;
class Mesh;
enum class EnemyState;

class EnemyObjectBase :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	再利用するかフラグ
	@param	オブジェクト判別用tag
	*/
	EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag);

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

	/*
	@fn 押し戻し処理
	*/
	void EnemyCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);

protected:

	// 3Dモデルの描画を行うクラス
	SkeletalMeshComponent* skeltalMeshComponent;
	// Meshの読み込みを行うクラス
	Mesh* mesh;
	// AABBの当たり判定を行うクラス
	BoxCollider* boxCollider;

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

	// 速度
	float moveSpeed;

	//接地フラグ
	bool onGround;

	bool isDeadFlag;

	// 今のプレーヤーのstate状態を保存するための変数
	EnemyState nowState;
	// 変更された次のプレーヤーのstate状態を保存するための変数
	EnemyState nextState;

	// Animationプール
	std::vector<const Animation*> animTypes;
	// stateプール
	std::vector<class EnemyObjectStateBase*> statePools;

private:



public:// ゲッターセッター

	/*
	@fn skeltalMeshComponentのgetter関数
	@return SkeletalMeshComponent　SkeletalMeshComponentクラスのポインタを返す
	*/
	SkeletalMeshComponent* GetSkeletalMeshComponent() { return skeltalMeshComponent; }

	/*
	@fn Animationのgetter関数
	@param _state 現在のプレイヤーのステータス
	@return Animation Animationクラスのポインタを返す
	*/
	const Animation* GetAnimation(EnemyState _state);

	/*
	@fn forwardVecのgetter関数
	@return forwardVecを返す
	*/
	Vector3 GetForwardVec() { return forwardVec; }

	/*
	@fn rightVecのgetter関数
	@return rightVecを返す
	*/
	Vector3 GetRightVec() { return rightVec; }

	/*
	@fn charaForwardVecのgetter関数
	@return charaForwardVecを返す
	*/
	Vector3 GetCharaForwardVec() { return charaForwardVec; }

	/*
	@fn rotateVecのgetter関数
	@return rotateVecを返す
	*/
	Vector3 GetRotateVec() { return rotateVec; }

	/*
	@fn velocityのgetter関数
	@return velocityを返す
	*/
	Vector3 GetVelocity() { return velocity; }

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
	@fn nowStateのgetter関数
	@return nowStateを返す
	*/
	EnemyState GetNowState() { return nowState; }

	/*
	@fn charaForwardVecのsetter関数
	@param	Vector3 _charaForwardVec キャラクターの前方ベクトル
	*/
	void SetCharaForwardVec(Vector3 _charaForwardVec) { charaForwardVec = _charaForwardVec; }

	/*
	@fn velocityのsetter関数
	@param	Vector3 _velocity キャラクターの速度ベクトル
	*/
	void SetVelocity(Vector3 _velocity) { velocity = _velocity; }

	/*
	@fn moveSpeedのsetter関数
	@param	float _moveSpeed キャラクターのスピード
	*/
	void SetMoveSpeed(float _moveSpeed) { moveSpeed = _moveSpeed; }

	bool GetIsDeadFlag() { return isDeadFlag; }
	void SetIsDeadFlag(bool _isDeadFlag) { isDeadFlag = _isDeadFlag; }
};

