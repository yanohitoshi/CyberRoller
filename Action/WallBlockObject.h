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
@file WallBlockObject.h
@brief 壁objectの生成を行う
*/
class WallBlockObject : public GameObject
{
public:
	
	/*
	@fn コンストラクタ
	@param	ポジション
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	*/
	WallBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag);
	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~WallBlockObject();

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// 3Dモデルの描画を行うクラス
	MeshComponent* meshComponent;
	Mesh* mesh;

	// 当たり判定を行うクラス
	BoxCollider* boxCollider;

};
