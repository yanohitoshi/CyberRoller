#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class MeshComponent;
class Mesh;
class BoxCollider;
class ExplosionObjectStateBase;
enum class ExplosionObjectState;

/*
@file ExplosionObjectBase.h
@brief 爆発するオブジェクトの基底クラス
*/
class ExplosionObjectBase :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	オブジェクト判別用tag
	*/
	ExplosionObjectBase(const Tag _objectTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	virtual ~ExplosionObjectBase() {};

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
	void AddStatePoolMap(ExplosionObjectStateBase* _state, ExplosionObjectState _stateTag);

	/*
	@brief ステートプール用マップからステートクラスを削除する関数
	@param	_stateTag 鍵となるタグ
	*/
	void RemoveStatePoolMap(ExplosionObjectState _stateTag);

	/*
	@brief ステートプール用マップをクリアする
	*/
	void ClearStatePoolMap();

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	@param	当たり判定タグ
	*/
	virtual void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag) {};

	// Meshの読み込みを行うクラス
	Mesh* mesh;
	// 3Dモデルの描画を行うクラス
	MeshComponent* meshComponent;
	// AABBの当たり判定を行うクラス
	BoxCollider* boxCollider;

	// オブジェクトの現在のステータス
	ExplosionObjectState nowState;
	// オブジェクトの次のステータス
	ExplosionObjectState nextState;

	// 爆発開始状態か
	bool isStartExplosion;
	// 爆発したか
	bool isExplode;
	// 爆発するオブジェクトに当たったか
	bool isHitExplosionObject;
	// ヒットした相手がジャンプアタック状態のプレイヤーかどうか
	bool isHitJumpAttackPlayer;
	// 落下開始するか
	bool isFallStart;
	// 当たった時の当たったオブジェクトのポジション
	Vector3 hitPosition;
	// 初期ポジション
	Vector3 firstPosition;
	// 降るエリア
	Vector3 fallArea;

	// 落下速度
	float fallSpeed;

	// 全stateが格納されるマップ
	std::unordered_map<ExplosionObjectState, ExplosionObjectStateBase*> statePoolMap;

public:

	/*
	@fn meshComponentのgetter
	@return meshComponentのポインタ
	*/
	MeshComponent* GetMeshComponent() { return meshComponent; }

	/*
	@brief　爆発したかフラグのgetter
	@return	isExplode
	*/
	bool GetIsExplode() { return isExplode; }
	
	/*
	@brief　爆発開始状態かフラグのgetter
	@return	isStartExplosion
	*/
	bool GetIsStartExplosion() { return isStartExplosion; }
	
	/*
	@brief　ヒットした相手がジャンプアタック状態のプレイヤーかどうかフラグのgetter
	@return	isHitJumpAttackPlayer
	*/
	bool GetIsHitJumpAttackPlayer() { return isHitJumpAttackPlayer; }
	
	/*
	@brief　爆発するオブジェクトに当たったかフラグのgetter
	@return	isHitExplosionObject
	*/
	bool GetIsHitExplosionObject() { return isHitExplosionObject; }

	/*
	@brief　落下開始するかフラグのgetter
	@return	isFallStart
	*/
	bool GetIsFallStart() { return isFallStart; }

	/*
	@brief　当たった時の当たったオブジェクトのポジションのgetter
	@return	hitPosition
	*/
	Vector3 GetHitPosition() { return hitPosition; }
	
	/*
	@brief　降るエリアのgetter
	@return	fallArea
	*/
	Vector3 GetFallArea() { return fallArea; }
	
	/*
	@brief　初期ポジションのgetter
	@return	firstPosition
	*/
	Vector3 GetFirstPosition() { return firstPosition; }

	/*
	@brief　落下速度のgetter
	@return	fallSpeed
	*/
	float GetFallSpeed() { return fallSpeed; }

	/*
	@brief isExplodeのsetter関数
	@param	_isExplode 爆発しているか
	*/
	void SetIsExplode(bool _isExplode) { isExplode = _isExplode; }
	
	/*
	@brief isStartExplosionのsetter関数
	@param	_isStartExplosion 爆発開始状態か
	*/
	void SetIsStartExplosion(bool _isStartExplosion) { isStartExplosion = _isStartExplosion; }
	
	/*
	@brief isHitExplosionObjectのsetter関数
	@param	_isHitExplosionObject 爆発するオブジェクトに触れたか
	*/
	void SetIsHitExplosionObject(bool _isHitExplosionObject) { isHitExplosionObject = _isHitExplosionObject; }

	/*
	@brief fallSpeedのsetter関数
	@param	_fallSpeed 落下速度
	*/
	void SetFallSpeed(float _fallSpeed) { fallSpeed = _fallSpeed; }
};

