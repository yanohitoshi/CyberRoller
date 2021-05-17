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
@file MoveBlockObject.h
@brief MoveBlockObjectの生成と更新を行う
*/
class MoveBlockObject :
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
	@param　どの方向に動くのか判別するためのタグ
	*/
	MoveBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Vector3& _distance, const Vector3& _direction,const float& _speed,MoveDirectionTag _moveTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~MoveBlockObject();

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	
	/*
	@fn 移動状態を確認する関数
	*/
	void ChackMoveProcess();

	// 3Dモデルの描画を行うクラス
	Mesh* mesh;
	MeshComponent* meshComponent;
	// 当たり判定を行うクラス
	BoxCollider* boxCollider;

	//初期位置
	Vector3 initPos;
	//移動先位置
	Vector3 goalPos;
	//反転フラグ
	bool inversionFlag;
	//移動速度
	float moveSpeed;
	//移動方向
	Vector3 direction;
	// どの方向に動くかを判定するためのTag変数
	MoveDirectionTag moveTag;

};

