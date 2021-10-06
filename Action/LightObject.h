#pragma once
#include "GameObject.h"

// クラスの前方宣言
class MeshComponent;

class LightObject :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	*/
	LightObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag,bool _isRight);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~LightObject();

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	MeshComponent* meshComponent;

};

