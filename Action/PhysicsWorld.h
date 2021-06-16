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
	
	/*
	@fn LineSegmentColliderを追加する関数
	@brief　LineSegmentColliderを当たり判定のタグを参照してそれぞれの可変長コンテナに格納を行う
	@param	_line　追加するLineSegmentColliderのポインタ
	@param	_func 関数ポインタに紐づけする関数
	*/
	void AddLineSegment(LineSegmentCollider* _line, onCollisionFunc _func);
	
	/*
	@fn LineSegmentColliderを削除する関数
	@brief　使わなくなったLineSegmentColliderを当たり判定タグを参照してそれぞれの可変長コンテナから探し削除を行う
	@param	_line　削除するLineSegmentColliderのポインタ
	*/
	void RemoveLineSegment(LineSegmentCollider* _line);
	
	/*
	@fn PlaneColliderを追加する関数
	@brief　PlaneColliderを当たり判定のタグを参照してそれぞれの可変長コンテナに格納を行う
	@param	_plane　追加するPlaneColliderのポインタ
	@param	_func 関数ポインタに紐づけする関数
	*/
	void AddPlane(PlaneCollider* _plane, onCollisionFunc _func);
	
	/*
	@fn PlaneColliderを削除する関数
	@brief　使わなくなったPlaneColliderを当たり判定タグを参照してそれぞれの可変長コンテナから探し削除を行う
	@param	_plane　削除するPlaneColliderのポインタ
	*/
	void RemovePlane(PlaneCollider* _plane);
	
private:

	//コンストラクタの隠蔽
	PhysicsWorld();

	static PhysicsWorld* physics;

	/*
	@fn AABBとAABBの当たり判定
	@brief　playerと地面の当たり判定を行う(BoxCollider)
	@param	_box 当たり判定に用いるBoxColliderのポインタ
	*/
	void HitChackBoxPlayerToGround(BoxCollider* _box);
	
	/*
	@fn AABBとAABBの当たり判定
	@brief　playerと動く地面の当たり判定を行う(BoxCollider)
	@param	_box 当たり判定に用いるBoxColliderのポインタ
	*/
	void HitChackBoxPlayerToMoveGround(BoxCollider* _box);
	
	/*
	@fn AABBとAABBの当たり判定
	@brief　playerと壁の当たり判定を行う(BoxCollider)
	@param	_box 当たり判定に用いるBoxColliderのポインタ
	*/
	void HitChackBoxPlayerToWall(BoxCollider* _box);
	
	/*
	@fn AABBとAABBの当たり判定
	@brief　playerとクリアポイントの当たり判定を行う(BoxCollider)
	@param	_box 当たり判定に用いるBoxColliderのポインタ
	*/
	void HitChackBoxPlayerToClearPoint(BoxCollider* _box);
	
	/*
	@fn AABBとAABBの当たり判定
	@brief　playerとリスポーンポイントの当たり判定を行う(BoxCollider)
	@param	_box 当たり判定に用いるBoxColliderのポインタ
	*/
	void HitChackBoxPlayerToRespownPoint(BoxCollider* _box);
	
	/*
	@fn AABBとAABBの当たり判定
	@brief　playerと棘配置用床の当たり判定を行う(BoxCollider)
	@param	_box 当たり判定に用いるBoxColliderのポインタ
	*/
	void HitChackBoxPlayerToNeedlePlane(BoxCollider* _box);
	
	/*
	@fn AABBとAABBの当たり判定
	@brief　playerとスイッチの土台の当たり判定を行う(BoxCollider)
	@param	_box 当たり判定に用いるBoxColliderのポインタ
	*/
	void HitChackBoxPlayerToSwitchBase(BoxCollider* _box);
	
	/*
	@fn AABBとAABBの当たり判定
	@brief　playerとスイッチの土台の当たり判定を行う(BoxCollider)
	@param	_box 当たり判定に用いるBoxColliderのポインタ
	*/
	void HitChackBoxPlayerToSwitch(BoxCollider* _box);

	/*
	@fn AABBとAABBの当たり判定
	@brief　カメラと地面の当たり判定を行う(BoxCollider)
	@param	_box 当たり判定に用いるBoxColliderのポインタ
	*/
	void HitChackBoxCameraToGround(BoxCollider* _box);
	
	/*
	@fn AABBとAABBの当たり判定
	@brief　カメラと動く地面の当たり判定を行う(BoxCollider)
	@param	_box 当たり判定に用いるBoxColliderのポインタ
	*/
	void HitChackBoxCameraToWall(BoxCollider* _box);
	
	/*
	@fn AABBとAABBの当たり判定
	@brief　動く床とジャンプスイッチの当たり判定を行う(BoxCollider)
	@param	_box 当たり判定に用いるBoxColliderのポインタ
	*/
	void HitChackBoxMoveGroundToJumpSwitch(BoxCollider* _box);
	
	/*
	@fn AABBとAABBの当たり判定
	@brief　動く床と棘配置用床の当たり判定を行う(BoxCollider)
	@param	_box 当たり判定に用いるBoxColliderのポインタ
	*/
	void HitChackBoxMoveGroundToNeedlePlane(BoxCollider* _box);

	/*
	@fn SphereとAABBの当たり判定
	@brief　プレイヤーの接地判定と地面の当たり判定を行う(SphereCollider)
	@param	_sphere　当たり判定に用いるSphereColliderのポインタ
	*/
	void HitChackSphereGroundChackToGround(SphereCollider* _sphere);
	/*
	@fn SphereとAABBの当たり判定
	@brief　プレイヤーの接地判定と動く地面の当たり判定を行う(SphereCollider)
	@param	_sphere　当たり判定に用いるSphereColliderのポインタ
	*/
	void HitChackSphereGroundChackToMoveGround(SphereCollider* _sphere);
	/*
	@fn SphereとAABBの当たり判定
	@brief　プレイヤーの接地判定とスイッチの土台の当たり判定を行う(SphereCollider)
	@param	_sphere　当たり判定に用いるSphereColliderのポインタ
	*/
	void HitChackSphereGroundChackToSwitchBase(SphereCollider* _sphere);
	/*
	@fn SphereとAABBの当たり判定
	@brief　プレイヤーの接地判定とスイッチの当たり判定を行う(SphereCollider)
	@param	_sphere　当たり判定に用いるSphereColliderのポインタ
	*/
	void HitChackSphereGroundChackToSwitch(SphereCollider* _sphere);
	/*
	@fn SphereとAABBの当たり判定
	@brief　プレイヤーの接地判定とジャンプスイッチの当たり判定を行う(SphereCollider)
	@param	_sphere　当たり判定に用いるSphereColliderのポインタ
	*/
	void HitChackSphereGroundChackToJumpSwitch(SphereCollider* _sphere);

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
