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
	static PhysicsWorld* GetInstance() { return physics; }
	static void CreateInstance();
	static void DeleteInstance();

	/*
	@fn HitCheck関数
	@brief　当たり判定を行う
	*/
	void HitCheck();

	/*
	@fn HitCheck関数(Box)
	@brief　BoxCollider(AABB)の当たり判定を行う
	@param	_box 当たり判定に用いるBoxColliderのポインタ
	*/
    void HitCheck(BoxCollider* _box);
	
	/*
	@fn HitCheck関数(Sphere)
	@brief　SphereCollider(Sphere)の当たり判定を行う
	@param	_sphere 当たり判定に用いるSphereColliderのポインタ
	*/
    void HitCheck(SphereCollider* _sphere);

	/*
	@fn HitCheck関数(LineSegment)
	@brief　LineSegmentCollider(LineSegment)の当たり判定を行う
	@param	_line　当たり判定に用いるLineSegmentColliderのポインタ
	*/
	void HitCheck(LineSegmentCollider* _line);

	/*
	@fn BoxColliderを追加する関数
	@brief　BoxColliderの追加を行う
	@param	_box　追加するBoxColliderのポインタ
	@param	_func 関数ポインタに紐づけする関数
	*/
    void AddBox(BoxCollider* _box, onCollisionFunc _func);
	
	/*
	@fn BoxColliderを削除する関数
	@brief　使わなくなったBoxCollider削除を行う
	@param	_line　削除するBoxColliderのポインタ
	*/
    void RemoveBox(BoxCollider* _box);
	
	/*
	@fn SphereColliderを追加する関数
	@brief　SphereColliderの追加を行う
	@param	_sphere　追加するSphereColliderのポインタ
	@param	_func 関数ポインタに紐づけする関数
	*/
	void AddSphere(SphereCollider* _sphere, onCollisionFunc _func);
	
	/*
	@fn SphereColliderを削除する関数
	@brief　使わなくなったSphereCollider削除を行う
	@param	_sphere　削除するSphereColliderのポインタ
	*/
	void RemoveSphere(SphereCollider* _sphere);
	
	/*
	@fn LineSegmentColliderを追加する関数
	@brief　LineSegmentColliderの追加を行う
	@param	_line　追加するLineSegmentColliderのポインタ
	@param	_func 関数ポインタに紐づけする関数
	*/
	void AddLineSegment(LineSegmentCollider* _line, onCollisionFunc _func);
	
	/*
	@fn LineSegmentColliderを削除する関数
	@brief　使わなくなったLineSegmentCollider削除を行う
	@param	_line　削除するLineSegmentColliderのポインタ
	*/
	void RemoveLineSegment(LineSegmentCollider* _line);
	
	/*
	@fn PlaneColliderを追加する関数
	@brief　PlaneColliderの追加を行う
	@param	_plane　追加するPlaneColliderのポインタ
	@param	_func 関数ポインタに紐づけする関数
	*/
	void AddPlane(PlaneCollider* _plane, onCollisionFunc _func);
	
	/*
	@fn PlaneColliderを削除する関数
	@brief　使わなくなったPlaneCollider削除を行う
	@param	_plane　削除するPlaneColliderのポインタ
	*/
	void RemovePlane(PlaneCollider* _plane);
	
private:
	//コンストラクタの隠蔽
	PhysicsWorld();

	static PhysicsWorld* physics;

	//void SphereAndSphere();
	//void BoxAndBox();
	//void SphereAndBox();

	//それぞれのobjectごとのAABBの可変長配列
	std::vector<BoxCollider*> boxes;
    std::vector<BoxCollider*> playerBoxes;
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
	//std::vector<SphereCollider*> spheres;
	std::vector<LineSegmentCollider*> lines;
	std::vector<PlaneCollider*> planes;
	onCollisionMap collisionFunction;

};

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);
