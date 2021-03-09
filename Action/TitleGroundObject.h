#pragma once
#include "BoxObject.h"

/*
@file TitleGroundObject.h
@brief TitleGroundObjectの生成と更新を行う
*/
class TitleGroundObject :
    public BoxObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	playerのポジション
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	*/
	TitleGroundObject(const Vector3& _p, const Vector3& _size,const Vector3& _playerPos , const Tag& _objectTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~TitleGroundObject();
	
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

	// playerのポジションを保存する用の変数
	Vector3 targetPos;
	// 目標ポジション変数
	Vector3 goalPos;
	// 初期ポジション変数
	Vector3 initPos;
	// 目標に到達したときにポジションをリセットするフラグ
	bool rePositionFlag;
};

