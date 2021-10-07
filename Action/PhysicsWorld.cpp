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

void PhysicsWorld::CreateInstance()
{
	if (physics == nullptr)
	{
		physics = new PhysicsWorld();
	}
}

void PhysicsWorld::DeleteInstance()
{
	if (physics != nullptr)
	{
		delete physics;
		physics = nullptr;
	}
}

PhysicsWorld::PhysicsWorld()
{
}




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

void PhysicsWorld::IntersectCheckBox(BoxCollider* _box, std::vector<BoxCollider*> _checkBoxes)
{
	for (auto itr : _checkBoxes)
	{
		//自分自身とは当たり判定を行わない
		if (itr == _box)
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
			_box->refreshWorldTransform();
		}
	}
}

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
			_sphere->refreshWorldTransform();
		}
	}
}

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



void PhysicsWorld::AddBox(BoxCollider * _box, onCollisionFunc _func)
{

	PhysicsTag objTag = _box->GetBoxTag();

	// @fix
	// Tagに応じたvector配列に格納
	switch (objTag)
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

void PhysicsWorld::RemoveBox(BoxCollider * _box)
{
	// @fix
	if (_box->GetBoxTag() == PhysicsTag::PLAYER_TAG)
	{
		auto iter = std::find(playerBoxes.begin(), playerBoxes.end(), _box);
		if (iter != playerBoxes.end())
		{
			std::iter_swap(iter, playerBoxes.end() - 1);
			playerBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == PhysicsTag::WALL_TAG)
	{
		auto iter = std::find(wallBoxes.begin(), wallBoxes.end(), _box);
		if (iter != wallBoxes.end())
		{
			std::iter_swap(iter, wallBoxes.end() - 1);
			wallBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == PhysicsTag::GROUND_TAG)
	{
		auto iter = std::find(groundBoxes.begin(), groundBoxes.end(), _box);
		if (iter != groundBoxes.end())
		{
			std::iter_swap(iter, groundBoxes.end() - 1);
			groundBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == PhysicsTag::MOVE_GROUND_TAG)
	{
		auto iter = std::find(moveGroundBoxes.begin(), moveGroundBoxes.end(), _box);
		if (iter != moveGroundBoxes.end())
		{
			std::iter_swap(iter, moveGroundBoxes.end() - 1);
			moveGroundBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == PhysicsTag::SWITCH_TAG)
	{
		auto iter = std::find(switchBoxes.begin(), switchBoxes.end(), _box);
		if (iter != switchBoxes.end())
		{
			std::iter_swap(iter, switchBoxes.end() - 1);
			switchBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == PhysicsTag::FOOT_CHECK_TAG)
	{
		auto iter = std::find(footCheckBoxes.begin(), footCheckBoxes.end(), _box);
		if (iter != footCheckBoxes.end())
		{
			std::iter_swap(iter, footCheckBoxes.end() - 1);
			footCheckBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}


	if (_box->GetBoxTag() == PhysicsTag::SWITCH_BASE_TAG)
	{
		auto iter = std::find(switchBaseBoxes.begin(), switchBaseBoxes.end(), _box);
		if (iter != switchBaseBoxes.end())
		{
			std::iter_swap(iter, switchBaseBoxes.end() - 1);
			switchBaseBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == PhysicsTag::JUMP_SWITCH_TAG)
	{
		auto iter = std::find(jumpSwitchBoxes.begin(), jumpSwitchBoxes.end(), _box);
		if (iter != jumpSwitchBoxes.end())
		{
			std::iter_swap(iter, jumpSwitchBoxes.end() - 1);
			jumpSwitchBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == PhysicsTag::GROUND_CHECK_TAG)
	{
		auto iter = std::find(groundCheckBoxes.begin(), groundCheckBoxes.end(), _box);
		if (iter != groundCheckBoxes.end())
		{
			std::iter_swap(iter, groundCheckBoxes.end() - 1);
			groundCheckBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == PhysicsTag::CAMERA_TAG)
	{
		auto iter = std::find(cameraBoxes.begin(), cameraBoxes.end(), _box);
		if (iter != cameraBoxes.end())
		{
			std::iter_swap(iter, cameraBoxes.end() - 1);
			cameraBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == PhysicsTag::CLEAR_POINT_TAG)
	{
		auto iter = std::find(clearPointBoxes.begin(), clearPointBoxes.end(), _box);
		if (iter != clearPointBoxes.end())
		{
			std::iter_swap(iter, clearPointBoxes.end() - 1);
			clearPointBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == PhysicsTag::RESPOWN_TAG)
	{
		auto iter = std::find(respownPointBoxes.begin(), respownPointBoxes.end(), _box);
		if (iter != respownPointBoxes.end())
		{
			std::iter_swap(iter, respownPointBoxes.end() - 1);
			respownPointBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == PhysicsTag::NEEDLE_TAG)
	{
		auto iter = std::find(needlePlaneBoxes.begin(), needlePlaneBoxes.end(), _box);
		if (iter != needlePlaneBoxes.end())
		{
			std::iter_swap(iter, needlePlaneBoxes.end() - 1);
			needlePlaneBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == PhysicsTag::ENEMY_TAG)
	{
		auto iter = std::find(enemyBoxes.begin(), enemyBoxes.end(), _box);
		if (iter != enemyBoxes.end())
		{
			std::iter_swap(iter, enemyBoxes.end() - 1);
			enemyBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

}

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

void PhysicsWorld::RemoveSphere(SphereCollider * _sphere)
{
	if (_sphere->GetSphereTag() == PhysicsTag::GROUND_CHECK_TAG)
	{
		auto iter = std::find(groundCheckSpheres.begin(), groundCheckSpheres.end(), _sphere);
		if (iter != groundCheckSpheres.end())
		{
			std::iter_swap(iter, groundCheckSpheres.end() - 1);
			groundCheckSpheres.pop_back();
		}

		collisionFunction.erase(_sphere);
	}

	if (_sphere->GetSphereTag() == PhysicsTag::ATTACK_RANGE_TAG)
	{
		auto iter = std::find(attackRangeSpheres.begin(), attackRangeSpheres.end(), _sphere);
		if (iter != attackRangeSpheres.end())
		{
			std::iter_swap(iter, attackRangeSpheres.end() - 1);
			attackRangeSpheres.pop_back();
		}

		collisionFunction.erase(_sphere);
	}

	if (_sphere->GetSphereTag() == PhysicsTag::JUMP_ATTACK_PLAYER_TAG)
	{
		auto iter = std::find(jumpAttackPlayerSpheres.begin(), jumpAttackPlayerSpheres.end(), _sphere);
		if (iter != jumpAttackPlayerSpheres.end())
		{
			std::iter_swap(iter, jumpAttackPlayerSpheres.end() - 1);
			jumpAttackPlayerSpheres.pop_back();
		}

		collisionFunction.erase(_sphere);
	}

	if (_sphere->GetSphereTag() == PhysicsTag::PLAYER_TRACKING_AREA_TAG)
	{
		auto iter = std::find(playerTrackingAreaSpheres.begin(), playerTrackingAreaSpheres.end(), _sphere);
		if (iter != playerTrackingAreaSpheres.end())
		{
			std::iter_swap(iter, playerTrackingAreaSpheres.end() - 1);
			playerTrackingAreaSpheres.pop_back();
		}

		collisionFunction.erase(_sphere);
	}

	if (_sphere->GetSphereTag() == PhysicsTag::ENEMY_ATTACK_AREA_TAG)
	{
		auto iter = std::find(enemyAttackAreaSpheres.begin(), enemyAttackAreaSpheres.end(), _sphere);
		if (iter != enemyAttackAreaSpheres.end())
		{
			std::iter_swap(iter, enemyAttackAreaSpheres.end() - 1);
			enemyAttackAreaSpheres.pop_back();
		}

		collisionFunction.erase(_sphere);
	}
}