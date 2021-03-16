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
	@param  どれくらいの距離動くのか
	@param　どの方向に動くのか
	@param　速度
	@param　戻る際に速度を落とす割合
	@param　どの方向に動くのか判別するためのタグ
	*/
	PushBoxObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Vector3& _distance, const Vector3& _direction, const float& _speed, const float& _cutBackSpeed , MoveDirectionTag _moveTag);
	
	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~PushBoxObject();

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

