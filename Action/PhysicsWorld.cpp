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

	if (_box->GetBoxTag() == ColliderComponent::PLAYER_TAG)
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

	if (_box->GetBoxTag() == ColliderComponent::NORMAL_ENEMY_TAG)
	{
		IntersectCheckBox(_box, groundBoxes);
	}

	if (_box->GetBoxTag() == ColliderComponent::CAMERA_TAG)
	{
		// カメラと地面の判定処理
		IntersectCheckBox(_box, groundBoxes);
	}

	if (_box->GetBoxTag() == ColliderComponent::MOVE_GROUND_TAG)
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_box->GetOwner()));
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
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_sphere->GetOwner()));
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

	if (_sphere->GetSphereTag() == ColliderComponent::GROUND_CHECK_TAG)
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

	if (_sphere->GetSphereTag() == ColliderComponent::ATTACK_RANGE_TAG)
	{
		// 接地判定スフィアとジャンプスイッチの当たり判定
		IntersectCheckSphere(_sphere, enemyBoxes);
	}
}



void PhysicsWorld::AddBox(BoxCollider * _box, onCollisionFunc _func)
{

	ColliderComponent::PhysicsTag objTag = _box->GetBoxTag();

	// Tagに応じたvector配列に格納
	switch (objTag)
	{
	case ColliderComponent::GROUND_TAG:
		groundBoxes.emplace_back(_box);
		break;

	case ColliderComponent::MOVE_GROUND_TAG:
		moveGroundBoxes.emplace_back(_box);
		break;

	case ColliderComponent::WALL_TAG:
		wallBoxes.emplace_back(_box);
		break;

	case ColliderComponent::PLAYER_TAG:
		playerBoxes.emplace_back(_box);
		break;

	case ColliderComponent::SWITCH_TAG:
		switchBoxes.emplace_back(_box);
		break;

	case ColliderComponent::SWITCH_BASE:
		switchBaseBoxes.emplace_back(_box);
		break;

	case ColliderComponent::JUMP_SWITCH_TAG:
		jumpSwitchBoxes.emplace_back(_box);
		break;

	case ColliderComponent::GROUND_CHECK_TAG:
		groundCheckBoxes.emplace_back(_box);
		break;

	case ColliderComponent::FOOT_CHECK_TAG:
		footCheckBoxes.emplace_back(_box);
		break;

	case ColliderComponent::CAMERA_TAG:
		cameraBoxes.emplace_back(_box);
		break;

	case ColliderComponent::CLEAR_POINT_TAG:
		clearPointBoxes.emplace_back(_box);
		break;

	case ColliderComponent::NEEDLE_TAG:
		needlePlaneBoxes.emplace_back(_box);
		break;

	case ColliderComponent::RESPOWN_TAG:
		respownPointBoxes.emplace_back(_box);
		break;

	case ColliderComponent::NORMAL_ENEMY_TAG:
		enemyBoxes.emplace_back(_box);
		break;
	}

	//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
	collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
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

	if (_box->GetBoxTag() == ColliderComponent::NORMAL_ENEMY_TAG)
	{
		auto iter = std::find(enemyBoxes.begin(), enemyBoxes.end(), _box);
		if (iter != enemyBoxes.end())
		{
			std::iter_swap(iter, enemyBoxes.end() - 1);
			enemyBoxes.pop_back();
		}

		collisionFunction.erase(_box);
	}

	//auto iter = std::find(boxes.begin(), boxes.end(), _box);
	//if (iter != boxes.end())
	//{
	//	std::iter_swap(iter, boxes.end() - 1);
	//	boxes.pop_back();
	//}
	//  collisionFunction.erase(_box);
}

void PhysicsWorld::AddSphere(SphereCollider * _sphere, onCollisionFunc _func)
{
	ColliderComponent::PhysicsTag objTag = _sphere->GetSphereTag();

	// Tagに応じたvector配列に格納
	switch (objTag)
	{
	case ColliderComponent::GROUND_CHECK_TAG:
		groundCheckSpheres.emplace_back(_sphere);
		break;
	case ColliderComponent::SWITCH_CHECK_TAG:
		switchCheckSpheres.emplace_back(_sphere);
		break;
	case ColliderComponent::ATTACK_RANGE_TAG:
		attackRangeSpheres.emplace_back(_sphere);
		break;
	}

	//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
	collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_sphere), _func));
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

	if (_sphere->GetSphereTag() == ColliderComponent::ATTACK_RANGE_TAG)
	{
		auto iter = std::find(attackRangeSpheres.begin(), attackRangeSpheres.end(), _sphere);
		if (iter != attackRangeSpheres.end())
		{
			std::iter_swap(iter, attackRangeSpheres.end() - 1);
			attackRangeSpheres.pop_back();
		}

		collisionFunction.erase(_sphere);
	}

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


