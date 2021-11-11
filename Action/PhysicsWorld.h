#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include <vector>
#include <map>
#include <unordered_map>
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
class Shader;
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
	void AddBoxes(BoxCollider* _box, onCollisionFunc _func);

	/*
	@fn BoxColliderを削除する関数
	@brief　使わなくなったBoxColliderを当たり判定タグを参照してそれぞれの可変長コンテナから探し削除を行う
	@param	_box　削除するBoxColliderのポインタ
	*/
	void RemoveBoxes(BoxCollider* _box);

	/*
	@fn SphereColliderを追加する関数
	@brief　SphereColliderを当たり判定のタグを参照してそれぞれの可変長コンテナに格納を行う
	@param	_sphere　追加するSphereColliderのポインタ
	@param	_func 関数ポインタに紐づけする関数
	*/
	void AddSpheres(SphereCollider* _sphere, onCollisionFunc _func);
	

	/*
	@fn 削除するSphereColliderが格納されている関数
	@brief　使わなくなったSphereColliderを当たり判定タグを参照してそれぞれの可変長コンテナから探し削除を行う
	@param	_sphere　削除するSphereColliderのポインタ
	*/
	void RemoveSpheres(SphereCollider* _sphere);
	
	/*
	@fn デバッグ用ボックス表示準備
	*/
	void DebugShowBox();

	/*
	@fn デバッグモードフラグを切り替え
	*/
	void ToggleDebugMode() { boolDebugMode = !boolDebugMode; }

private:

	/*
	@fn PhysicsWorldのインスタンス生成関数
	//コンストラクタの隠蔽
	*/
	PhysicsWorld();

	/*
	@fn デバッグ用の矩形当たり判定を描画
	@param _Boxs 矩形当たり判定
	@param _Color ラインの色
	*/
	void DrawBoxs(std::vector<class BoxCollider*>& _Boxs, const Vector3& _Color);

	/*
	@fn 頂点配列を初期化
	*/
	void InitBoxVertices();

	// デバッグモードフラグ
	bool boolDebugMode;

	// ボックス描画用のVAO 
	unsigned int boxVAO;

	// デバッグ用の当たり判定描画用シェーダー
	Shader* lineShader;

	// インスタンス
	static PhysicsWorld* physics;

	// BoxColliderを格納するMap
	std::unordered_map<PhysicsTag, std::vector<BoxCollider*>> boxesMap;

	// SphereColliderを格納するMap
	std::unordered_map<PhysicsTag, std::vector<SphereCollider*>> spheresMap;

	onCollisionMap collisionFunction;
};