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
@file NeedleObject.h
@brief NeedleObjectの生成と更新を行う
*/
class NeedleObject :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	親となるobjectのポインタ
	@param	親objectとの間隔
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	*/
	NeedleObject(GameObject* _owner, const Vector3& _offset, const Vector3& _size, const Tag& _objectTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~NeedleObject();
	
	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	// 3Dモデルの描画を行うクラス
	Mesh* mesh;
	MeshComponent* meshComponent;
	// 当たり判定を行うクラス
	BoxCollider* boxCollider;
	// 親となるクラスのポインタ保存用変数
	GameObject* owner;

};

