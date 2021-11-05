#pragma once
#include "GameObject.h"

class MeshComponent;
class Mesh;
class BoxCollider;
class ExplosionObjectStateBase;
enum class ExplosionObjectState;

class ExplosionObject :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	オブジェクト判別用tag
	@param	移動速度
	@param	追跡するオブジェクトのポインタ
	@param	追跡エリアの値
	*/
	ExplosionObject(const Vector3& _pos, const Tag _objectTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~ExplosionObject()override;

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

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
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// Meshの読み込みを行うクラス
	Mesh* mesh;
	// 3Dモデルの描画を行うクラス
	MeshComponent* meshComponent;
	// AABBの当たり判定を行うクラス
	BoxCollider* boxCollider;

	ExplosionObjectState nowState;
	ExplosionObjectState nextState;

	// 爆発開始状態か
	bool isStartExplosion;
	// 爆発したか
	bool isExplode;
	// 爆発するオブジェクトに当たったか
	bool isHitExplosionObject;
	// ヒットした相手がジャンプアタック状態のプレイヤーかどうか
	bool isHitJumpAttackPlayer;
	// プレイヤーが当たった時のプレイヤーのポジション
	Vector3 hitPosition;
	// 初期ポジション
	Vector3 firstPosition;

	// 全stateが格納されるマップ
	std::unordered_map<ExplosionObjectState, ExplosionObjectStateBase*> statePoolMap;

public:

	MeshComponent* GetMeshComponent() { return meshComponent; }

	bool GetIsExplode() { return isExplode; }
	bool GetIsStartExplosion() { return isStartExplosion; }
	bool GetIsHitJumpAttackPlayer() { return isHitJumpAttackPlayer; }
	bool GetIsHitExplosionObject() { return isHitExplosionObject; }
	Vector3 GetHitPosition() { return hitPosition; }
	Vector3 GetFirstPosition() { return firstPosition; }

	void SetIsExplode(bool _isExplode) { isExplode = _isExplode; }
	void SetIsStartExplosion(bool _isStartExplosion) { isStartExplosion = _isStartExplosion; }
	void SetIsHitExplosionObject(bool _isHitExplosionObject) { isHitExplosionObject = _isHitExplosionObject; }
};

