#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

class NeedleObject :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	親となるobjectのポインタ
	@param	親objectとの間隔
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	*/
	NeedleObject(GameObject* _owner, const Vector3& _offset, const Vector3& _size, const Tag& _objectTag);
	~NeedleObject();
	
	/*
	@fn 更新処理
	@param	フレームレート固定用deltaTime
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	// 3Dモデルの描画を行うクラス
	Mesh* mesh;
	MeshComponent* meshComponent;
	// 当たり判定を行うクラス
	BoxCollider* boxCollider;
	// 親となるクラスのポインタ保存用変数
	GameObject* owner;

};

