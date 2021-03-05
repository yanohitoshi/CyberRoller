#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

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
	~PushBoxObject();

	void UpdateGameObject(float _deltaTime)override;

private:

	Mesh* mesh;
	MeshComponent* meshComponent;
	BoxCollider* boxCollider;

};

