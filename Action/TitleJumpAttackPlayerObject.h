#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class MeshComponent;
class Mesh;
class TitlePlayerObject;

/*
@file TitleJumpAttackPlayerObject.h
@brief タイトルシーン中でのジャンプアタックプレイヤー
*/
class TitleJumpAttackPlayerObject :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	親クラスのポインタ
	@param	オブジェクトのサイズ
	@param	オブジェクト判別用tag
	*/
	TitleJumpAttackPlayerObject(TitlePlayerObject* _ownerObject, const Vector3& _size, const Tag _objectTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~TitleJumpAttackPlayerObject();

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn 回転処理関数
	*/
	void RotationProcess(float _angle, Vector3 _axis);

private:

	// 3Dモデルの描画を行うクラス
	MeshComponent* meshComponent;
	TitlePlayerObject* ownerObject;
	Mesh* mesh;
	// Z軸をずらすための定数
	const float ShiftPositionZ;
public:

	/*
	@fn meshComponentのgetter関数
	@return meshComponent　meshComponentクラスのポインタを返す
	*/
	MeshComponent* GetMeshComponent() { return meshComponent; }

};