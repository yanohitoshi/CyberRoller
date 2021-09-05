#pragma once
#include "GameObject.h"
#include <glew.h>

// クラスの前方宣言
class ChangeColorMeshComponent;

/*
@file ResultSwitchObject.h
@brief リザルトシーン用スイッチclass
*/
class ResultSwitchObject :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	*/
	ResultSwitchObject(GameObject* _owner, const Vector3& _size, const Tag& _objectTag, const float _angle );

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~ResultSwitchObject();

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// 色変更機能付きMeshComponent
	ChangeColorMeshComponent* meshComponent;

	// 全スイッチがONの時の色
	const Vector3 AllClearColer;
	// スイッチがONの時の色
	const Vector3 OnColor;
	// スイッチがOFFの時の色
	const Vector3 OffColor;
};

