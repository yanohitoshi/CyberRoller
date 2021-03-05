#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

/*
@file WallBlockObject.h
@brief 壁objectの生成を行う
*/

class WallBlockObject : public GameObject
{
public:
	
	/*
	@fn コンストラクタ
	@param	ポジション
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	*/
	WallBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag);
	~WallBlockObject();

	void UpdateGameObject(float _deltaTime)override;

private:

	MeshComponent* meshComponent;
	BoxCollider* boxCollider;
	Mesh* mesh;

};
