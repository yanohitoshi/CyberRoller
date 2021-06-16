#include "PhysicsWorld.h"
#include <algorithm>
#include <SDL.h>
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "LineSegmentCollider.h"
#include "PlaneCollider.h"
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

void PhysicsWorld::HitChackBoxPlayerToGround(BoxCollider* _box)
{
	for (auto itr : groundBoxes)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_box->GetOwner()));
			_box->refreshWorldTransform();

		}
	}
}

void PhysicsWorld::HitChackBoxPlayerToMoveGround(BoxCollider* _box)
{
	for (auto itr : moveGroundBoxes)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_box->GetOwner()));
			_box->refreshWorldTransform();

		}
	}
}

void PhysicsWorld::HitChackBoxPlayerToWall(BoxCollider* _box)
{
	for (auto itr : wallBoxes)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_box->GetOwner()));
			_box->refreshWorldTransform();

		}
	}
}

void PhysicsWorld::HitChackBoxPlayerToClearPoint(BoxCollider* _box)
{
	for (auto itr : clearPointBoxes)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_box->GetOwner()));
			_box->refreshWorldTransform();

		}
	}
}

void PhysicsWorld::HitChackBoxPlayerToRespownPoint(BoxCollider* _box)
{
	for (auto itr : respownPointBoxes)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_box->GetOwner()));
			_box->refreshWorldTransform();

		}
	}
}

void PhysicsWorld::HitChackBoxPlayerToNeedlePlane(BoxCollider* _box)
{
	for (auto itr : needlePlaneBoxes)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_box->GetOwner()));
			_box->refreshWorldTransform();

		}
	}
}

void PhysicsWorld::HitChackBoxPlayerToSwitchBase(BoxCollider* _box)
{
	for (auto itr : switchBaseBoxes)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_box->GetOwner()));
			_box->refreshWorldTransform();

		}
	}
}

void PhysicsWorld::HitChackBoxPlayerToSwitch(BoxCollider* _box)
{
	for (auto itr : switchBoxes)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_box->GetOwner()));
			_box->refreshWorldTransform();

		}
	}
}

void PhysicsWorld::HitChackBoxCameraToGround(BoxCollider* _box)
{
	for (auto itr : groundBoxes)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_box->GetOwner()));
			_box->refreshWorldTransform();

		}
	}
}

void PhysicsWorld::HitChackBoxCameraToWall(BoxCollider* _box)
{
	for (auto itr : wallBoxes)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_box->GetOwner()));
			_box->refreshWorldTransform();

		}
	}
}

void PhysicsWorld::HitChackBoxMoveGroundToJumpSwitch(BoxCollider* _box)
{
	for (auto itr : jumpSwitchBoxes)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_box->GetOwner()));
			_box->refreshWorldTransform();

		}
	}
}

void PhysicsWorld::HitChackBoxMoveGroundToNeedlePlane(BoxCollider* _box)
{
	for (auto itr : needlePlaneBoxes)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_box->GetOwner()));
			_box->refreshWorldTransform();

		}
	}
}

void PhysicsWorld::HitChackSphereGroundChackToGround(SphereCollider* _sphere)
{
	for (auto itr : groundBoxes)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_sphere->GetOwner()));
			_sphere->refreshWorldTransform();
		}
	}
}

void PhysicsWorld::HitChackSphereGroundChackToMoveGround(SphereCollider* _sphere)
{
	for (auto itr : moveGroundBoxes)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_sphere->GetOwner()));
			_sphere->refreshWorldTransform();
		}
	}
}

void PhysicsWorld::HitChackSphereGroundChackToSwitchBase(SphereCollider* _sphere)
{
	for (auto itr : switchBaseBoxes)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_sphere->GetOwner()));
			_sphere->refreshWorldTransform();
		}
	}
}

void PhysicsWorld::HitChackSphereGroundChackToSwitch(SphereCollider* _sphere)
{
	for (auto itr : switchBoxes)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_sphere->GetOwner()));
			_sphere->refreshWorldTransform();
		}
	}
}

void PhysicsWorld::HitChackSphereGroundChackToJumpSwitch(SphereCollider* _sphere)
{
	for (auto itr : jumpSwitchBoxes)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_sphere->GetOwner()));
			_sphere->refreshWorldTransform();
		}
	}
}



void PhysicsWorld::HitCheck(BoxCollider* _box)
{
	//コライダーの親オブジェクトがActiveじゃなければ終了する
	if (_box->GetOwner()->GetState() != State::Active)
	{
		return;
	}

	if (_box->GetBoxTag() == ColliderComponent::PLAYER_TAG)
	{
		// プレイヤーと地面の判定処理
		HitChackBoxPlayerToGround(_box);
		
		// プレイヤーと動く地面の判定処理
		HitChackBoxPlayerToMoveGround(_box);

		// プレイヤーと壁の判定処理
		HitChackBoxPlayerToWall(_box);

		// プレイヤーとクリアポイントの判定処理
		HitChackBoxPlayerToClearPoint(_box);

		// プレイヤーとリスポーンポイントの判定処理
		HitChackBoxPlayerToRespownPoint(_box);

		// プレイヤーと棘配置用床の判定処理
		HitChackBoxPlayerToNeedlePlane(_box);

		// プレイヤーとスイッチの土台の判定処理
		HitChackBoxPlayerToSwitchBase(_box);

		// プレイヤーとスイッチの判定処理
		HitChackBoxPlayerToSwitch(_box);

	}

	if (_box->GetBoxTag() == ColliderComponent::CAMERA_TAG)
	{
		// カメラと地面の判定処理
		HitChackBoxCameraToGround(_box);

		// カメラと壁の判定処理
		HitChackBoxCameraToWall(_box);
	}

	if (_box->GetBoxTag() == ColliderComponent::MOVE_GROUND_TAG)
	{
		// 動く床とジャンプスイッチの判定処理
		HitChackBoxMoveGroundToJumpSwitch(_box);

		// 動く床と棘配置用床の判定処理
		HitChackBoxMoveGroundToNeedlePlane(_box);
	}

}

void PhysicsWorld::HitCheck(SphereCollider * _sphere)
{
	//コライダーの親オブジェクトがActiveじゃなければ終了する
	if (_sphere->GetOwner()->GetState() != State::Active)
	{
		return;
	}

	if (_sphere->GetSphereTag() == ColliderComponent::GROUND_CHECK_TAG)
	{
		// 接地判定スフィアと地面の当たり判定
		HitChackSphereGroundChackToGround(_sphere);

		// 接地判定スフィアと動く地面の当たり判定
		HitChackSphereGroundChackToMoveGround(_sphere);

		// 接地判定スフィアとスイッチの土台の当たり判定
		HitChackSphereGroundChackToSwitchBase(_sphere);

		// 接地判定スフィアとスイッチの当たり判定
		HitChackSphereGroundChackToSwitch(_sphere);

		// 接地判定スフィアとジャンプスイッチの当たり判定
		HitChackSphereGroundChackToJumpSwitch(_sphere);

	}
}

//線分とAABBの当たり判定チェック関数(未実装)
void PhysicsWorld::HitCheck(LineSegmentCollider* _line)
{
	//コライダーの親オブジェクトがActiveじゃなければ終了する
	if (_line->GetOwner()->GetState() != State::Active)
	{
		return;
	}

	float t;
	Vector3 colPos = Vector3::Zero;

	for (auto itr : wallBoxes)
	{
		//コライダーの親オブジェクトがActiveじゃなければ終了する
		if (itr->GetOwner()->GetState() != State::Active)
		{
			continue;
		}

		bool hit = ColRayBox(_line->GetWorldLineSegment(), itr->GetWorldBox(),t,colPos);

		if (hit)
		{
			onCollisionFunc func = collisionFunction.at(_line);
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_line->GetOwner()));
		}
	}
}

void PhysicsWorld::AddBox(BoxCollider * _box, onCollisionFunc _func)
{

	ColliderComponent::PhysicsTag objTag = _box->GetBoxTag();

	if (objTag == ColliderComponent::PLAYER_TAG)
	{
		playerBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}


	if (objTag == ColliderComponent::GROUND_TAG)
	{
		groundBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}

	if (objTag == ColliderComponent::MOVE_GROUND_TAG)
	{
		moveGroundBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}


	if (objTag == ColliderComponent::GROUND_CHECK_TAG)
	{
		groundCheckBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}

	if (objTag == ColliderComponent::WALL_TAG)
	{
		wallBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}

	if (objTag == ColliderComponent::SWITCH_TAG)
	{
		switchBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}

	if (objTag == ColliderComponent::FOOT_CHECK_TAG)
	{
		footCheckBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}

	if (objTag == ColliderComponent::SWITCH_BASE)
	{
		switchBaseBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}
	
	if (objTag == ColliderComponent::JUMP_SWITCH_TAG)
	{
		jumpSwitchBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}

	if (objTag == ColliderComponent::CAMERA_TAG)
	{
		cameraBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}

	if (objTag == ColliderComponent::CLEAR_POINT_TAG)
	{
		clearPointBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}

	if (objTag == ColliderComponent::RESPOWN_TAG)
	{
		respownPointBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}

	if (objTag == ColliderComponent::NEEDLE_TAG)
	{
		needlePlaneBoxes.emplace_back(_box);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
	}

}

void PhysicsWorld::RemoveBox(BoxCollider * _box)
{

	if (_box->GetBoxTag() == ColliderComponent::PLAYER_TAG)
	{
		auto iter = std::find(playerBoxes.begin(), playerBoxes.end(), _box);
		if (iter != playerBoxes.end())
		{
			std::iter_swap(iter, playerBoxes.end() - 1);
			playerBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == ColliderComponent::WALL_TAG)
	{
		auto iter = std::find(wallBoxes.begin(), wallBoxes.end(), _box);
		if (iter != wallBoxes.end())
		{
			std::iter_swap(iter, wallBoxes.end() - 1);
			wallBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == ColliderComponent::GROUND_TAG)
	{
		auto iter = std::find(groundBoxes.begin(), groundBoxes.end(), _box);
		if (iter != groundBoxes.end())
		{
			std::iter_swap(iter, groundBoxes.end() - 1);
			groundBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == ColliderComponent::MOVE_GROUND_TAG)
	{
		auto iter = std::find(moveGroundBoxes.begin(), moveGroundBoxes.end(), _box);
		if (iter != moveGroundBoxes.end())
		{
			std::iter_swap(iter, moveGroundBoxes.end() - 1);
			moveGroundBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == ColliderComponent::SWITCH_TAG)
	{
		auto iter = std::find(switchBoxes.begin(), switchBoxes.end(), _box);
		if (iter != switchBoxes.end())
		{
			std::iter_swap(iter, switchBoxes.end() - 1);
			switchBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == ColliderComponent::FOOT_CHECK_TAG)
	{
		auto iter = std::find(footCheckBoxes.begin(), footCheckBoxes.end(), _box);
		if (iter != footCheckBoxes.end())
		{
			std::iter_swap(iter, footCheckBoxes.end() - 1);
			footCheckBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}


	if (_box->GetBoxTag() == ColliderComponent::SWITCH_BASE)
	{
		auto iter = std::find(switchBaseBoxes.begin(), switchBaseBoxes.end(), _box);
		if (iter != switchBaseBoxes.end())
		{
			std::iter_swap(iter, switchBaseBoxes.end() - 1);
			switchBaseBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == ColliderComponent::JUMP_SWITCH_TAG)
	{
		auto iter = std::find(jumpSwitchBoxes.begin(), jumpSwitchBoxes.end(), _box);
		if (iter != jumpSwitchBoxes.end())
		{
			std::iter_swap(iter, jumpSwitchBoxes.end() - 1);
			jumpSwitchBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == ColliderComponent::GROUND_CHECK_TAG)
	{
		auto iter = std::find(groundCheckBoxes.begin(), groundCheckBoxes.end(), _box);
		if (iter != groundCheckBoxes.end())
		{
			std::iter_swap(iter, groundCheckBoxes.end() - 1);
			groundCheckBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == ColliderComponent::CAMERA_TAG)
	{
		auto iter = std::find(cameraBoxes.begin(), cameraBoxes.end(), _box);
		if (iter != cameraBoxes.end())
		{
			std::iter_swap(iter, cameraBoxes.end() - 1);
			cameraBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == ColliderComponent::CLEAR_POINT_TAG)
	{
		auto iter = std::find(clearPointBoxes.begin(), clearPointBoxes.end(), _box);
		if (iter != clearPointBoxes.end())
		{
			std::iter_swap(iter, clearPointBoxes.end() - 1);
			clearPointBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == ColliderComponent::RESPOWN_TAG)
	{
		auto iter = std::find(respownPointBoxes.begin(), respownPointBoxes.end(), _box);
		if (iter != respownPointBoxes.end())
		{
			std::iter_swap(iter, respownPointBoxes.end() - 1);
			respownPointBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	if (_box->GetBoxTag() == ColliderComponent::NEEDLE_TAG)
	{
		auto iter = std::find(needlePlaneBoxes.begin(), needlePlaneBoxes.end(), _box);
		if (iter != needlePlaneBoxes.end())
		{
			std::iter_swap(iter, needlePlaneBoxes.end() - 1);
			needlePlaneBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	//auto iter = std::find(boxes.begin(), boxes.end(), _box);
	//if (iter != boxes.end())
	//{
	//	std::iter_swap(iter, boxes.end() - 1);
	//	boxes.pop_back();
	//}
 //   collisionFunction.erase(_box);
}

void PhysicsWorld::AddSphere(SphereCollider * _sphere, onCollisionFunc _func)
{
	ColliderComponent::PhysicsTag objTag = _sphere->GetSphereTag();

	if (objTag == ColliderComponent::GROUND_CHECK_TAG)
	{
		groundCheckSpheres.emplace_back(_sphere);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_sphere), _func));
	}

	if (objTag == ColliderComponent::SWITCH_CHECK_TAG)
	{
		switchCheckSpheres.emplace_back(_sphere);
		//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
		collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_sphere), _func));
	}
}

void PhysicsWorld::RemoveSphere(SphereCollider * _sphere)
{
	if (_sphere->GetSphereTag() == ColliderComponent::GROUND_CHECK_TAG)
	{
		auto iter = std::find(groundCheckSpheres.begin(), groundCheckSpheres.end(), _sphere);
		if (iter != groundCheckSpheres.end())
		{
			std::iter_swap(iter, groundCheckSpheres.end() - 1);
			groundCheckSpheres.pop_back();
		}

		collisionFunction.erase(_sphere);
	}

	if (_sphere->GetSphereTag() == ColliderComponent::SWITCH_CHECK_TAG)
	{
		auto iter = std::find(switchCheckSpheres.begin(), switchCheckSpheres.end(), _sphere);
		if (iter != switchCheckSpheres.end())
		{
			std::iter_swap(iter, switchCheckSpheres.end() - 1);
			switchCheckSpheres.pop_back();
		}

		collisionFunction.erase(_sphere);
	}

}

void PhysicsWorld::AddLineSegment(LineSegmentCollider* _line, onCollisionFunc _func)
{
	lines.emplace_back(_line);
	//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
	collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_line), _func));
}

void PhysicsWorld::RemoveLineSegment(LineSegmentCollider* _line)
{
	auto iter = std::find(lines.begin(), lines.end(), _line);
	if (iter != lines.end())
	{
		std::iter_swap(iter, lines.end() - 1);
		lines.pop_back();
	}

	collisionFunction.erase(_line);
}

void PhysicsWorld::AddPlane(PlaneCollider* _plane, onCollisionFunc _func)
{
	planes.emplace_back(_plane);
	//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
	collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_plane), _func));
}

void PhysicsWorld::RemovePlane(PlaneCollider* _plane)
{
	auto iter = std::find(planes.begin(), planes.end(), _plane);
	if (iter != planes.end())
	{
		std::iter_swap(iter, planes.end() - 1);
		planes.pop_back();
	}

	collisionFunction.erase(_plane);

}

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
{
	_calcFixVec = Vector3(0, 0, 0);
	float dx1 = _fixedBox.min.x - _movableBox.max.x;
	float dx2 = _fixedBox.max.x - _movableBox.min.x;
	float dy1 = _fixedBox.min.y - _movableBox.max.y;
	float dy2 = _fixedBox.max.y - _movableBox.min.y;
	float dz1 = _fixedBox.min.z - _movableBox.max.z;
	float dz2 = _fixedBox.max.z - _movableBox.min.z;

	// dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;

	// x, y, zのうち最も差が小さい軸で位置を調整
	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		_calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		_calcFixVec.y = dy;
	}
	else
	{
		_calcFixVec.z = dz;
	}

}


//void PhysicsWorld::SphereAndSphere()
//{
//	for (size_t i = 0; i < spheres.size(); i++)
//	{
//		if (spheres[i]->GetOwner()->GetState() != Active)
//		{
//			continue;
//		}
//		for (size_t j = i + 1; j < spheres.size(); j++)
//		{
//			if (spheres[j]->GetOwner()->GetState() != Active)
//			{
//				continue;
//			}
//			bool hit = Intersect(spheres[i]->GetWorldSphere(), spheres[j]->GetWorldSphere());
//
//			if (hit)
//			{
//				SphereCollider* sphereA = spheres[i];
//				SphereCollider* sphereB = spheres[j];
//
//				//sphereA->GetOwner()->OnCollision(*(sphereB->GetOwner()));
//				//sphereB->GetOwner()->OnCollision(*(sphereA->GetOwner()));
//			}
//		}
//	}
//}
//
//void PhysicsWorld::BoxAndBox()
//{
//	for (size_t i = 0; i < boxes.size(); i++)
//	{
//		if (boxes[i]->GetOwner()->GetState() != Active)
//		{
//			continue;
//		}
//		for (size_t j = i + 1; j < boxes.size(); j++)
//		{
//			if (boxes[j]->GetOwner()->GetState() != Active)
//			{
//				continue;
//			}
//			bool hit = Intersect(boxes[i]->GetWorldBox(), boxes[j]->GetWorldBox());
//
//			if (hit)
//			{
//				BoxCollider* boxA = boxes[i];
//				BoxCollider* boxB = boxes[j];
//
//				//boxA->GetOwner()->OnCollision(*(boxB->GetOwner()));
//				//boxB->GetOwner()->OnCollision(*(boxA->GetOwner()));
//			}
//		}
//	}
//}
//
//void PhysicsWorld::SphereAndBox()
//{
//
//
//	for (size_t i = 0; i < spheres.size(); i++)
//	{
//		if (spheres[i]->GetOwner()->GetState() != Active)
//		{
//			continue;
//		}
//		for (size_t j = 0; j < boxes.size(); j++)
//		{
//			if (boxes[j]->GetOwner()->GetState() != Active)
//			{
//				continue;
//			}
//			bool hit = Intersect(spheres[i]->GetWorldSphere(), boxes[j]->GetWorldBox());
//
//			if (hit)
//			{
//				//spheres[i]->GetOwner()->OnCollision(*(boxes[j]->GetOwner()));
//				//boxes[j]->GetOwner()->OnCollision(*(spheres[i]->GetOwner()));
//			}
//		}
//	}
//}

