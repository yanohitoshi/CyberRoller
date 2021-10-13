#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class MeshComponent;
class BoxCollider;
class Mesh;
class GeometryInstanceComponent;

/*
@struct PushBoxData
	プッシュボックスで扱う固有のデータ構造体
*/
struct PushBoxData
{
	MoveDirectionTag tag;
	Vector3 direction;
	Vector3 distance;
	float cutBackSpeed;
	float speed;
};

/*
@file PushBoxObject.h
@brief PushBoxObjectの生成と更新を行う
*/
class PushBoxObject :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	@param  プッシュボードを更新するのに使用するデータ構造体
	*/
	PushBoxObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, PushBoxData _pushBoxData);
	
	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~PushBoxObject()override;

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

};

