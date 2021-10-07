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
enum class PhysicsTag;


typedef std::function<void(GameObject&, PhysicsTag)> onCollisionFunc;
// 関数ポインタを格納するmap
typedef std::map<ColliderComponent*, std::function<void(GameObject&, PhysicsTag)>> onCollisionMap;

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
	@fn ヒットチェックを行う関数(Box)
	@brief　BoxCollider(AABB)の当たり判定を行う
	@param	_box 当たり判定に用いるBoxColliderのポインタ
	*/
    void HitCheck(BoxCollider* _box);

	/*
	@fn 当たり判定を行う関数(Box)
	@brief　BoxCollider(AABB)の当たり判定を行う
	@param	_box 当たり判定に用いるBoxColliderのポインタ
	@param	_checkBoxes 当たり判定を行う相手の可変長配列
	*/
	void IntersectCheckBox(BoxCollider* _box, std::vector<BoxCollider*> _checkBoxes);

	/*
	@fn 当たり判定を行う関数(Sphere)
	@brief　SphereCollider(Sphere)の当たり判定を行う
	@param	_sphere 当たり判定に用いるSphereColliderのポインタ
	@param	_checkBoxes 当たり判定を行う相手の可変長配列
	*/
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
	@fn 削除するBoxColliderが格納されている関数
	@brief　使わなくなったBoxColliderを当たり判定タグを参照してそれぞれの可変長コンテナから探し削除を行う
	@param	_box　削除するBoxColliderのポインタ
	*/
    void SelectRemoveBoxes(BoxCollider* _box);
	
	/*
	@fn BoxColliderを削除する関数
	@brief　使わなくなったBoxColliderを当たり判定タグを参照してそれぞれの可変長コンテナから探し削除を行う
	@param	_boxes　削除するBoxColliderが格納されている可変長配列のポインタ
	@param	_box　削除するBoxColliderのポインタ
	*/
	void RemoveBox(std::vector<BoxCollider*> _boxes, BoxCollider* _box);

	/*
	@fn SphereColliderを追加する関数
	@brief　SphereColliderを当たり判定のタグを参照してそれぞれの可変長コンテナに格納を行う
	@param	_sphere　追加するSphereColliderのポインタ
	@param	_func 関数ポインタに紐づけする関数
	*/
	void AddSphere(SphereCollider* _sphere, onCollisionFunc _func);
	
	/*
	@fn 削除するSphereColliderが格納されている関数
	@brief　使わなくなったSphereColliderを当たり判定タグを参照してそれぞれの可変長コンテナから探し削除を行う
	@param	_sphere　削除するSphereColliderのポインタ
	*/
	void SelectRemoveSpheres(SphereCollider* _box);

	/*
	@fn SphereColliderを削除する関数
	@brief　使わなくなったSphereColliderを当たり判定タグを参照してそれぞれの可変長コンテナから探し削除を行う
	@param	_spheres　削除するSphereColliderが格納されている可変長配列のポインタ
	@param	_sphere　削除するSphereColliderのポインタ
	*/
	void RemoveSphere(std::vector<SphereCollider*> _spheres,SphereCollider* _sphere);
	
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
	std::vector<SphereCollider*> attackRangeSpheres;
	std::vector<SphereCollider*> jumpAttackPlayerSpheres;
	std::vector<SphereCollider*> playerTrackingAreaSpheres;
	std::vector<SphereCollider*> enemyAttackAreaSpheres;

	onCollisionMap collisionFunction;

};