#pragma once
#include "GameObject.h"

// クラスの前方宣言
class MeshComponent;

/*
@file ResultSwitchBaseObject.h
@brief リザルトシーン用スイッチの土台class
*/
class ResultSwitchBaseObject :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	*/
	ResultSwitchBaseObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~ResultSwitchBaseObject();

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// 3Dモデルの描画を行うクラス
	MeshComponent* meshComponent;

	// リザルト用スイッチだった場合に回転させる角度
	const float Angle;
};

