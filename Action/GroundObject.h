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
@file BoxObject.h
@brief ボックスオブジェクトの生成と更新処理を行う
*/
class GroundObject : public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	@param	ライト付か否か
	*/
	GroundObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~GroundObject();
	
	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// Meshを管理するクラス
	Mesh* mesh;
	// 3Dモデルの描画を行うクラス
	MeshComponent* meshComponent;
	// 当たり判定を行うクラス
	BoxCollider* boxCollider;
	// プレイヤーがすり抜けないようにAABBのサイズを補正するための定数
	const float CorrectionAabbValue;
};

