#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class MeshComponent;
class BoxCollider;
class Mesh;

/*
@file NeedlePanelObject.h
@brief NeedlePanelObjectの生成を行う
*/
class NeedlePanelObject :
    public GameObject
{
public:
	
	/*
	@fn コンストラクタ
	@param	ポジション
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	*/
	NeedlePanelObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag);
	
	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~NeedlePanelObject();
	
	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	@param	当たったGameObjectの当たり判定タグ
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;
	// 3Dモデルの描画を行うクラス
	Mesh* mesh;
	MeshComponent* meshComponent;
	// 当たり判定を行うクラス
	BoxCollider* boxCollider;
};

