#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "PushBoxObject.h"

// クラスの前方宣言
class MeshComponent;
class BoxCollider;
class Mesh;
class PushBoxObject;
/*
@file PushBoardObject.h
@brief PushBoardObjectの生成と更新を行う
*/
class PushBoardObject :
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
	PushBoardObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, PushBoxData _pushBoxData);
	
	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~PushBoardObject();
	
	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn 可動処理関数
	*/
	void MovableProcess();
	
	/*
	@fn 反転チェック処理関数
	*/
	void ChackInversionProcess();

	/*
	@fn X軸反転チェック処理関数
	*/
	void ChackAxisX();

	/*
	@fn Y軸反転チェック処理関数
	*/
	void ChackAxisY();

	/*
	@fn Z軸反転チェック処理関数
	*/
	void ChackAxisZ();

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
	const float MoveSpeed;
	// 折り返す際の速度
	const float CutBackSpeed;
	//移動方向
	Vector3 direction;
	// どの方向に動くかを判定するためのTag変数
	MoveDirectionTag moveTag;

};
