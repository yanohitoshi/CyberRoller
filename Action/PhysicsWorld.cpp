//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PhysicsWorld.h"
#include <algorithm>
#include <SDL.h>
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "ColliderComponent.h"

PhysicsWorld* PhysicsWorld::physics = nullptr;

/*
@fn PhysicsWorldのインスタンス生成関数
*/
void PhysicsWorld::CreateInstance()
{
	if (physics == nullptr)
	{
		physics = new PhysicsWorld();
	}
}

/*
@fn PhysicsWorldのインスタンス削除関数
*/
void PhysicsWorld::DeleteInstance()
{
	if (physics != nullptr)
	{
		delete physics;
		physics = nullptr;
	}
}

/*
@fn PhysicsWorldのインスタンス生成関数
//コンストラクタの隠蔽
*/
PhysicsWorld::PhysicsWorld()
{
}

/*
@fn ヒットチェックを行う関数(Box)
@brief　BoxCollider(AABB)の当たり判定を行う
@param	_box 当たり判定に用いるBoxColliderのポインタ
*/
void PhysicsWorld::HitCheck(BoxCollider* _box)
{
	//コライダーの親オブジェクトがActiveじゃなければ終了する
	if (_box->GetOwner()->GetState() != State::Active)
	{
		return;
	}

	if (_box->GetBoxTag() == PhysicsTag::PLAYER_TAG)
	{
		// プレイヤーと地面の判定処理
		IntersectCheckBox(_box,groundBoxes);
		
		// プレイヤーと動く地面の判定処理
		IntersectCheckBox(_box, moveGroundBoxes);

		// プレイヤーと壁の判定処理
		IntersectCheckBox(_box,wallBoxes);

		// プレイヤーとエネミーの判定処理
		IntersectCheckBox(_box, enemyBoxes);

		// プレイヤーとクリアポイントの判定処理
		IntersectCheckBox(_box, clearPointBoxes);

		// プレイヤーとリスポーンポイントの判定処理
		IntersectCheckBox(_box, respownPointBoxes);

		// プレイヤーと棘配置用床の判定処理
		IntersectCheckBox(_box, needlePlaneBoxes);

		// プレイヤーとスイッチの土台の判定処理
		IntersectCheckBox(_box, switchBaseBoxes);

		// プレイヤーとスイッチの判定処理
		IntersectCheckBox(_box, switchBoxes);
	}

	if (_box->GetBoxTag() == PhysicsTag::ENEMY_TAG)
	{
		IntersectCheckBox(_box, groundBoxes);
		IntersectCheckBox(_box, enemyBoxes);
	}

	if (_box->GetBoxTag() == PhysicsTag::CAMERA_TAG)
	{
		// カメラと地面の判定処理
		IntersectCheckBox(_box, groundBoxes);
	}

	if (_box->GetBoxTag() == PhysicsTag::MOVE_GROUND_TAG)
	{
		// 動く床とジャンプスイッチの判定処理
		IntersectCheckBox(_box, jumpSwitchBoxes);

		// 動く床と棘配置用床の判定処理
		IntersectCheckBox(_box, needlePlaneBoxes);
	}
}

/*
@fn 当たり判定を行う関数(Box)
@brief　BoxCollider(AABB)の当たり判定を行う
@param	_box 当たり判定に用いるBoxColliderのポインタ
@param	_checkBoxes 当たり判定を行う相手の可変長配列
*/
void PhysicsWorld::IntersectCheckBox(BoxCollider* _box, std::vector<BoxCollider*> _checkBoxes)
{
	for (auto itr : _checkBoxes)
	{
		//自分自身とは当たり判定を行わない
		if (itr == _box)
		{
			continue;
		}

		if (itr->GetOwner() == nullptr)
		{
			continue;
		}

		//コライダーの親オブジェクトがActiveじゃなければ終了する
		if (itr->GetOwner()->GetState() != State::Active)
		{
			continue;
		}

		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());

		// Hitしていたら
		if (hit)
		{
			onCollisionFunc func = collisionFunction.at(_box);
			func(*(itr->GetOwner()),(itr->GetBoxTag()));
			func = collisionFunction.at(itr);
			func(*(_box->GetOwner()),(_box->GetBoxTag()));
			_box->RefreshWorldTransform();
		}
	}
}

/*
@fn 当たり判定を行う関数(Sphere)
@brief　SphereCollider(Sphere)の当たり判定を行う
@param	_sphere 当たり判定に用いるSphereColliderのポインタ
@param	_checkBoxes 当たり判定を行う相手の可変長配列
*/
void PhysicsWorld::IntersectCheckSphere(SphereCollider* _sphere, std::vector<BoxCollider*> _checkBoxes)
{
	for (auto itr : _checkBoxes)
	{
		//コライダーの親オブジェクトがActiveじゃなければ終了する
		if (itr->GetOwner()->GetState() != State::Active)
		{
			continue;
		}

		bool hit = Intersect(_sphere->GetWorldSphere(), itr->GetWorldBox());

		// Hitしていたら
		if (hit)
		{
			onCollisionFunc func = collisionFunction.at(_sphere);
			func(*(itr->GetOwner()),(itr->GetBoxTag()));
			func = collisionFunction.at(itr);
			func(*(_sphere->GetOwner()),(_sphere->GetSphereTag()));
			_sphere->RefreshWorldTransform();
		}
	}
}

/*
@fn HitCheck関数(Sphere)
@brief　SphereCollider(Sphere)の当たり判定を行う
@param	_sphere 当たり判定に用いるSphereColliderのポインタ
*/
void PhysicsWorld::HitCheck(SphereCollider * _sphere)
{
	//コライダーの親オブジェクトがActiveじゃなければ終了する
	if (_sphere->GetOwner()->GetState() != State::Active)
	{
		return;
	}

	if (_sphere->GetSphereTag() == PhysicsTag::GROUND_CHECK_TAG)
	{
		// 接地判定スフィアと地面の当たり判定
		IntersectCheckSphere(_sphere,groundBoxes);

		// 接地判定スフィアと動く地面の当たり判定
		IntersectCheckSphere(_sphere, moveGroundBoxes);

		// 接地判定スフィアとスイッチの土台の当たり判定
		IntersectCheckSphere(_sphere, switchBaseBoxes);

		// 接地判定スフィアとスイッチの当たり判定
		IntersectCheckSphere(_sphere, switchBoxes);

		// 接地判定スフィアとジャンプスイッチの当たり判定
		IntersectCheckSphere(_sphere, jumpSwitchBoxes);
	}

	if (_sphere->GetSphereTag() == PhysicsTag::PLAYER_TRACKING_AREA_TAG)
	{
		// 接地判定スフィアとジャンプスイッチの当たり判定
		IntersectCheckSphere(_sphere, playerBoxes);
	}

	if (_sphere->GetSphereTag() == PhysicsTag::ENEMY_ATTACK_AREA_TAG)
	{
		// 接地判定スフィアとジャンプスイッチの当たり判定
		IntersectCheckSphere(_sphere, playerBoxes);
	}

	if (_sphere->GetSphereTag() == PhysicsTag::ATTACK_RANGE_TAG)
	{
		// ジャンプアタック判定スフィアとジャンプスイッチの当たり判定
		IntersectCheckSphere(_sphere, enemyBoxes);
	}

	if (_sphere->GetSphereTag() == PhysicsTag::JUMP_ATTACK_PLAYER_TAG)
	{
		// 接地判定スフィアとジャンプスイッチの当たり判定
		IntersectCheckSphere(_sphere, enemyBoxes);
		IntersectCheckSphere(_sphere, groundBoxes);
		IntersectCheckSphere(_sphere, moveGroundBoxes);
	}
}

/*
@fn BoxColliderを追加する関数
@brief　BoxColliderを当たり判定のタグを参照してそれぞれの可変長コンテナに格納を行う
@param	_box　追加するBoxColliderのポインタ
@param	_func 関数ポインタに紐づけする関数
*/
void PhysicsWorld::AddBox(BoxCollider * _box, onCollisionFunc _func)
{
	// タグを取得
	PhysicsTag objTag = _box->GetBoxTag();

	// Tagに応じたvector配列に格納
	switch (_box->GetBoxTag())
	{
	case PhysicsTag::GROUND_TAG:
		groundBoxes.emplace_back(_box);
		break;

	case PhysicsTag::MOVE_GROUND_TAG:
		moveGroundBoxes.emplace_back(_box);
		break;

	case PhysicsTag::WALL_TAG:
		wallBoxes.emplace_back(_box);
		break;

	case PhysicsTag::PLAYER_TAG:
		playerBoxes.emplace_back(_box);
		break;

	case PhysicsTag::SWITCH_TAG:
		switchBoxes.emplace_back(_box);
		break;

	case PhysicsTag::SWITCH_BASE_TAG:
		switchBaseBoxes.emplace_back(_box);
		break;

	case PhysicsTag::JUMP_SWITCH_TAG:
		jumpSwitchBoxes.emplace_back(_box);
		break;

	case PhysicsTag::GROUND_CHECK_TAG:
		groundCheckBoxes.emplace_back(_box);
		break;

	case PhysicsTag::FOOT_CHECK_TAG:
		footCheckBoxes.emplace_back(_box);
		break;

	case PhysicsTag::CAMERA_TAG:
		cameraBoxes.emplace_back(_box);
		break;

	case PhysicsTag::CLEAR_POINT_TAG:
		clearPointBoxes.emplace_back(_box);
		break;

	case PhysicsTag::NEEDLE_TAG:
		needlePlaneBoxes.emplace_back(_box);
		break;

	case PhysicsTag::RESPOWN_TAG:
		respownPointBoxes.emplace_back(_box);
		break;

	case PhysicsTag::ENEMY_TAG:
		enemyBoxes.emplace_back(_box);
		break;
	}

	//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
	collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
}

/*
@fn 削除するBoxColliderが格納されている関数
@brief　使わなくなったBoxColliderを当たり判定タグを参照してそれぞれの可変長コンテナから探し削除を行う
@param	_box　削除するBoxColliderのポインタ
*/
void PhysicsWorld::SelectRemoveBoxes(BoxCollider* _box)
{
	// タグを取得
	PhysicsTag objTag = _box->GetBoxTag();

	switch (objTag)
	{
	case PhysicsTag::GROUND_TAG:
		RemoveBox(groundBoxes, _box);
		break;

	case PhysicsTag::MOVE_GROUND_TAG:
		RemoveBox(moveGroundBoxes, _box);
		break;

	case PhysicsTag::WALL_TAG:
		RemoveBox(wallBoxes, _box);
		break;

	case PhysicsTag::PLAYER_TAG:
		RemoveBox(playerBoxes, _box);
		break;

	case PhysicsTag::SWITCH_TAG:
		RemoveBox(switchBoxes, _box);
		break;

	case PhysicsTag::SWITCH_BASE_TAG:
		RemoveBox(switchBaseBoxes, _box);
		break;

	case PhysicsTag::JUMP_SWITCH_TAG:
		RemoveBox(jumpSwitchBoxes, _box);
		break;

	case PhysicsTag::GROUND_CHECK_TAG:
		RemoveBox(groundCheckBoxes, _box);
		break;

	case PhysicsTag::FOOT_CHECK_TAG:
		RemoveBox(footCheckBoxes, _box);
		break;

	case PhysicsTag::CAMERA_TAG:
		RemoveBox(cameraBoxes, _box);
		break;

	case PhysicsTag::CLEAR_POINT_TAG:
		RemoveBox(clearPointBoxes, _box);
		break;

	case PhysicsTag::NEEDLE_TAG:
		RemoveBox(needlePlaneBoxes, _box);
		break;

	case PhysicsTag::RESPOWN_TAG:
		RemoveBox(respownPointBoxes, _box);
		break;

	case PhysicsTag::ENEMY_TAG:
		RemoveBox(enemyBoxes, _box);
		break;
	}

	//if (objTag == PhysicsTag::GROUND_TAG)
	//{
	//	auto iter = std::find(groundBoxes.begin(), groundBoxes.end(), _box);
	//	if (iter != groundBoxes.end())
	//	{
	//		std::iter_swap(iter, groundBoxes.end() - 1);
	//		groundBoxes.pop_back();
	//	}
	//}

	//if (objTag == PhysicsTag::MOVE_GROUND_TAG)
	//{
	//	auto iter = std::find(moveGroundBoxes.begin(), moveGroundBoxes.end(), _box);
	//	if (iter != moveGroundBoxes.end())
	//	{
	//		std::iter_swap(iter, moveGroundBoxes.end() - 1);
	//		moveGroundBoxes.pop_back();
	//	}
	//}

	//if (objTag == PhysicsTag::WALL_TAG)
	//{
	//	auto iter = std::find(wallBoxes.begin(), wallBoxes.end(), _box);
	//	if (iter != wallBoxes.end())
	//	{
	//		std::iter_swap(iter, wallBoxes.end() - 1);
	//		wallBoxes.pop_back();
	//	}
	//}

	//if (objTag == PhysicsTag::PLAYER_TAG)
	//{
	//	auto iter = std::find(playerBoxes.begin(), playerBoxes.end(), _box);
	//	if (iter != groundBoxes.end())
	//	{
	//		std::iter_swap(iter, playerBoxes.end() - 1);
	//		playerBoxes.pop_back();
	//	}
	//}

	//if (objTag == PhysicsTag::SWITCH_TAG)
	//{
	//	auto iter = std::find(switchBoxes.begin(), switchBoxes.end(), _box);
	//	if (iter != switchBoxes.end())
	//	{
	//		std::iter_swap(iter, switchBoxes.end() - 1);
	//		switchBoxes.pop_back();
	//	}
	//}

	//if (objTag == PhysicsTag::SWITCH_BASE_TAG)
	//{
	//	auto iter = std::find(switchBaseBoxes.begin(), switchBaseBoxes.end(), _box);
	//	if (iter != switchBaseBoxes.end())
	//	{
	//		std::iter_swap(iter, switchBaseBoxes.end() - 1);
	//		switchBaseBoxes.pop_back();
	//	}
	//}

	//if (objTag == PhysicsTag::FOOT_CHECK_TAG)
	//{
	//	auto iter = std::find(footCheckBoxes.begin(), footCheckBoxes.end(), _box);
	//	if (iter != footCheckBoxes.end())
	//	{
	//		std::iter_swap(iter, footCheckBoxes.end() - 1);
	//		footCheckBoxes.pop_back();
	//	}
	//}

	//if (objTag == PhysicsTag::CAMERA_TAG)
	//{
	//	auto iter = std::find(cameraBoxes.begin(), cameraBoxes.end(), _box);
	//	if (iter != cameraBoxes.end())
	//	{
	//		std::iter_swap(iter, cameraBoxes.end() - 1);
	//		cameraBoxes.pop_back();
	//	}
	//}

	//if (objTag == PhysicsTag::CLEAR_POINT_TAG)
	//{
	//	auto iter = std::find(clearPointBoxes.begin(), clearPointBoxes.end(), _box);
	//	if (iter != clearPointBoxes.end())
	//	{
	//		std::iter_swap(iter, clearPointBoxes.end() - 1);
	//		clearPointBoxes.pop_back();
	//	}
	//}

	//if (objTag == PhysicsTag::NEEDLE_TAG)
	//{
	//	auto iter = std::find(needlePlaneBoxes.begin(), needlePlaneBoxes.end(), _box);
	//	if (iter != needlePlaneBoxes.end())
	//	{
	//		std::iter_swap(iter, needlePlaneBoxes.end() - 1);
	//		needlePlaneBoxes.pop_back();
	//	}
	//}
	//if (objTag == PhysicsTag::RESPOWN_TAG)
	//{
	//	auto iter = std::find(respownPointBoxes.begin(), respownPointBoxes.end(), _box);
	//	if (iter != respownPointBoxes.end())
	//	{
	//		std::iter_swap(iter, respownPointBoxes.end() - 1);
	//		respownPointBoxes.pop_back();
	//	}
	//}
	//if (objTag == PhysicsTag::ENEMY_TAG)
	//{
	//	auto iter = std::find(enemyBoxes.begin(), enemyBoxes.end(), _box);
	//	if (iter != enemyBoxes.end())
	//	{
	//		std::iter_swap(iter, enemyBoxes.end() - 1);
	//		enemyBoxes.pop_back();
	//	}
	//}
	//if (objTag == PhysicsTag::JUMP_SWITCH_TAG)
	//{
	//	auto iter = std::find(jumpSwitchBoxes.begin(), jumpSwitchBoxes.end(), _box);
	//	if (iter != jumpSwitchBoxes.end())
	//	{
	//		std::iter_swap(iter, jumpSwitchBoxes.end() - 1);
	//		jumpSwitchBoxes.pop_back();
	//	}
	//}

	//if (objTag == PhysicsTag::GROUND_CHECK_TAG)
	//{
	//	auto iter = std::find(groundCheckBoxes.begin(), groundCheckBoxes.end(), _box);
	//	if (iter != groundCheckBoxes.end())
	//	{
	//		std::iter_swap(iter, groundCheckBoxes.end() - 1);
	//		groundCheckBoxes.pop_back();
	//	}
	//}

	//collisionFunction.erase(_box);
}

/*
@fn BoxColliderを削除する関数
@brief　使わなくなったBoxColliderを当たり判定タグを参照してそれぞれの可変長コンテナから探し削除を行う
@param	_boxes　削除するBoxColliderが格納されている可変長配列のポインタの参照
@param	_box　削除するBoxColliderのポインタ
*/
void PhysicsWorld::RemoveBox(std::vector<BoxCollider*>& _boxes,BoxCollider* _box)
{
	auto iter = std::find(_boxes.begin(), _boxes.end(), _box);
	if (iter != _boxes.end())
	{
		std::iter_swap(iter, _boxes.end() - 1);
		_boxes.pop_back();
	}
	collisionFunction.erase(_box);
}

/*
@fn SphereColliderを追加する関数
@brief　SphereColliderを当たり判定のタグを参照してそれぞれの可変長コンテナに格納を行う
@param	_sphere　追加するSphereColliderのポインタ
@param	_func 関数ポインタに紐づけする関数
*/
void PhysicsWorld::AddSphere(SphereCollider * _sphere, onCollisionFunc _func)
{
	PhysicsTag objTag = _sphere->GetSphereTag();

	// Tagに応じたvector配列に格納
	switch (objTag)
	{
	case PhysicsTag::GROUND_CHECK_TAG:
		groundCheckSpheres.emplace_back(_sphere);
		break;

	case PhysicsTag::ATTACK_RANGE_TAG:
		attackRangeSpheres.emplace_back(_sphere);
		break;

	case PhysicsTag::JUMP_ATTACK_PLAYER_TAG:
		jumpAttackPlayerSpheres.emplace_back(_sphere);
		break;

	case PhysicsTag::PLAYER_TRACKING_AREA_TAG:
		playerTrackingAreaSpheres.emplace_back(_sphere);
		break;

	case PhysicsTag::ENEMY_ATTACK_AREA_TAG:
		enemyAttackAreaSpheres.emplace_back(_sphere);
		break;
	}

	//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
	collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_sphere), _func));
}

/*
@fn 削除するSphereColliderが格納されている関数
@brief　使わなくなったSphereColliderを当たり判定タグを参照してそれぞれの可変長コンテナから探し削除を行う
@param	_sphere　削除するSphereColliderのポインタ
*/
void PhysicsWorld::SelectRemoveSpheres(SphereCollider* _sphere)
{
	PhysicsTag objTag = _sphere->GetSphereTag();

	// Tagに応じたvector配列に格納
	switch (objTag)
	{
	case PhysicsTag::GROUND_CHECK_TAG:
		RemoveSphere(groundCheckSpheres, _sphere);
		break;

	case PhysicsTag::ATTACK_RANGE_TAG:
		RemoveSphere(attackRangeSpheres, _sphere);
		break;

	case PhysicsTag::JUMP_ATTACK_PLAYER_TAG:
		RemoveSphere(jumpAttackPlayerSpheres, _sphere);
		break;

	case PhysicsTag::PLAYER_TRACKING_AREA_TAG:
		RemoveSphere(playerTrackingAreaSpheres, _sphere);
		break;

	case PhysicsTag::ENEMY_ATTACK_AREA_TAG:
		RemoveSphere(enemyAttackAreaSpheres, _sphere);
		break;
	}

	//if (objTag == PhysicsTag::GROUND_CHECK_TAG)
	//{
	//	auto iter = std::find(groundCheckSpheres.begin(), groundCheckSpheres.end(), _sphere);
	//	if (iter != groundCheckSpheres.end())
	//	{
	//		std::iter_swap(iter, groundCheckSpheres.end() - 1);
	//		groundCheckSpheres.pop_back();
	//	}
	//}

	//if (objTag == PhysicsTag::ATTACK_RANGE_TAG)
	//{
	//	auto iter = std::find(attackRangeSpheres.begin(), attackRangeSpheres.end(), _sphere);
	//	if (iter != attackRangeSpheres.end())
	//	{
	//		std::iter_swap(iter, attackRangeSpheres.end() - 1);
	//		attackRangeSpheres.pop_back();
	//	}
	//}

	//if (objTag == PhysicsTag::JUMP_ATTACK_PLAYER_TAG)
	//{
	//	auto iter = std::find(jumpAttackPlayerSpheres.begin(), jumpAttackPlayerSpheres.end(), _sphere);
	//	if (iter != jumpAttackPlayerSpheres.end())
	//	{
	//		std::iter_swap(iter, jumpAttackPlayerSpheres.end() - 1);
	//		jumpAttackPlayerSpheres.pop_back();
	//	}
	//}

	//if (objTag == PhysicsTag::PLAYER_TRACKING_AREA_TAG)
	//{
	//	auto iter = std::find(playerTrackingAreaSpheres.begin(), playerTrackingAreaSpheres.end(), _sphere);
	//	if (iter != playerTrackingAreaSpheres.end())
	//	{
	//		std::iter_swap(iter, playerTrackingAreaSpheres.end() - 1);
	//		playerTrackingAreaSpheres.pop_back();
	//	}
	//}

	//if (objTag == PhysicsTag::ENEMY_ATTACK_AREA_TAG)
	//{
	//	auto iter = std::find(enemyAttackAreaSpheres.begin(), enemyAttackAreaSpheres.end(), _sphere);
	//	if (iter != enemyAttackAreaSpheres.end())
	//	{
	//		std::iter_swap(iter, enemyAttackAreaSpheres.end() - 1);
	//		enemyAttackAreaSpheres.pop_back();
	//	}
	//}
	//
	//collisionFunction.erase(_sphere);
}

/*
@fn SphereColliderを削除する関数
@brief　使わなくなったSphereColliderを当たり判定タグを参照してそれぞれの可変長コンテナから探し削除を行う
@param	_spheres　削除するSphereColliderが格納されている可変長配列のポインタの参照
@param	_sphere　削除するSphereColliderのポインタ
*/
void PhysicsWorld::RemoveSphere(std::vector<SphereCollider*>& _spheres, SphereCollider* _sphere)
{
	auto iter = std::find(_spheres.begin(), _spheres.end(), _sphere);
	if (iter != _spheres.end())
	{
		std::iter_swap(iter, _spheres.end() - 1);
		_spheres.pop_back();
	}
	collisionFunction.erase(_sphere);
}