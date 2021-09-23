#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include <vector>
#include <map>
#include <functional>
#include <iostream>
#include "Math.h"
#include "Collision.h"

// PhysicsWorld のインスタンスgetter関数
#define PHYSICS PhysicsWorld::GetInstance()

// クラスの前方宣言
class Game;
class GameObject;
class BoxCollider;
class SphereCollider;
class ColliderComponent;
class LineSegmentCollider;
class PlaneCollider;

typedef std::function<void(GameObject&)> onCollisionFunc;
typedef std::map<ColliderComponent*, std::function<void(GameObject&)>> onCollisionMap;

/*
@file PhysicsWorld.h
@brief 当たり判定を行うclass
*/
class PhysicsWorld
{
public:

	/*
	@brief　PhysicsWorldのインスタンスのgetter関数
	@return	PhysicsWorldのインスタンスを返す
	*/
	static PhysicsWorld* GetInstance() { return physics; }

	/*
	@fn PhysicsWorldのインスタンス生成関数
	*/
	static void CreateInstance();

	/*
	@fn PhysicsWorldのインスタンス削除関数
	*/
	static void DeleteInstance();

	/*
	@fn HitCheck関数(Box)
	@brief　BoxCollider(AABB)の当たり判定を行う
	@param	_box 当たり判定に用いるBoxColliderのポインタ
	*/
    void HitCheck(BoxCollider* _box);

	void IntersectCheckBox(BoxCollider* _box, std::vector<BoxCollider*> _checkBoxes);

	void IntersectCheckSphere(SphereCollider* _sphere, std::vector<BoxCollider*> _checkBoxes);
	
	/*
	@fn HitCheck関数(Sphere)
	@brief　SphereCollider(Sphere)の当たり判定を行う
	@param	_sphere 当たり判定に用いるSphereColliderのポインタ
	*/
    void HitCheck(SphereCollider* _sphere);

	/*
	@fn BoxColliderを追加する関数
	@brief　BoxColliderを当たり判定のタグを参照してそれぞれの可変長コンテナに格納を行う
	@param	_box　追加するBoxColliderのポインタ
	@param	_func 関数ポインタに紐づけする関数
	*/
    void AddBox(BoxCollider* _box, onCollisionFunc _func);
	
	/*
	@fn BoxColliderを削除する関数
	@brief　使わなくなったBoxColliderを当たり判定タグを参照してそれぞれの可変長コンテナから探し削除を行う
	@param	_line　削除するBoxColliderのポインタ
	*/
    void RemoveBox(BoxCollider* _box);
	
	/*
	@fn SphereColliderを追加する関数
	@brief　SphereColliderを当たり判定のタグを参照してそれぞれの可変長コンテナに格納を行う
	@param	_sphere　追加するSphereColliderのポインタ
	@param	_func 関数ポインタに紐づけする関数
	*/
	void AddSphere(SphereCollider* _sphere, onCollisionFunc _func);
	
	/*
	@fn SphereColliderを削除する関数
	@brief　使わなくなったSphereColliderを当たり判定タグを参照してそれぞれの可変長コンテナから探し削除を行う
	@param	_sphere　削除するSphereColliderのポインタ
	*/
	void RemoveSphere(SphereCollider* _sphere);
	
private:

	//コンストラクタの隠蔽
	PhysicsWorld();

	static PhysicsWorld* physics;

	//それぞれのobjectごとのAABBの可変長配列
	std::vector<BoxCollider*> boxes;
    std::vector<BoxCollider*> playerBoxes;
	std::vector<BoxCollider*> enemyBoxes;
	std::vector<BoxCollider*> wallBoxes;
	std::vector<BoxCollider*> groundBoxes;
	std::vector<BoxCollider*> moveGroundBoxes;
	std::vector<BoxCollider*> switchBoxes;
	std::vector<BoxCollider*> switchBaseBoxes;
	std::vector<BoxCollider*> needlePlaneBoxes;
	std::vector<BoxCollider*> jumpSwitchBoxes;
	std::vector<BoxCollider*> groundCheckBoxes;
	std::vector<BoxCollider*> footCheckBoxes;
	std::vector<BoxCollider*> cameraBoxes;
	std::vector<BoxCollider*> clearPointBoxes;
	std::vector<BoxCollider*> respownPointBoxes;


	//それぞれのsphereごとのAABBの可変長配列
	std::vector<SphereCollider*> groundCheckSpheres;
	std::vector<SphereCollider*> switchCheckSpheres;
	std::vector<SphereCollider*> attackRangeSpheres;
	std::vector<SphereCollider*> jumpAttackPlayerSpheres;
	std::vector<SphereCollider*> enemyTrackingSpheres;

	onCollisionMap collisionFunction;

};

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);
