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
	//コライダーの親オブジェクトがActiveでもDisablingでも終了する
	if (_box->GetOwner()->GetState() != State::Active && _box->GetOwner()->GetState() != State::Disabling)
	{
		return;
	}

	if (_box->GetBoxTag() == PhysicsTag::PLAYER_TAG)
	{
		// プレイヤーと地面の判定処理
		IntersectCheckBox(_box, boxesMap[PhysicsTag::GROUND_TAG]);
		
		// プレイヤーと動く地面の判定処理
		IntersectCheckBox(_box, boxesMap[PhysicsTag::MOVE_GROUND_TAG]);

		// プレイヤーと壁の判定処理
		IntersectCheckBox(_box, boxesMap[PhysicsTag::WALL_TAG]);

		// プレイヤーとエネミーの判定処理
		IntersectCheckBox(_box, boxesMap[PhysicsTag::ENEMY_TAG]);

		// プレイヤーとクリアポイントの判定処理
		IntersectCheckBox(_box, boxesMap[PhysicsTag::CLEAR_POINT_TAG]);

		// プレイヤーとリスポーンポイントの判定処理
		IntersectCheckBox(_box, boxesMap[PhysicsTag::RESPOWN_TAG]);

		// プレイヤーと棘配置用床の判定処理
		IntersectCheckBox(_box, boxesMap[PhysicsTag::NEEDLE_TAG]);

		// プレイヤーとスイッチの土台の判定処理
		IntersectCheckBox(_box, boxesMap[PhysicsTag::SWITCH_BASE_TAG]);

		// プレイヤーとスイッチの判定処理
		IntersectCheckBox(_box, boxesMap[PhysicsTag::SWITCH_TAG]);
	}

	if (_box->GetBoxTag() == PhysicsTag::ENEMY_TAG)
	{
		IntersectCheckBox(_box, boxesMap[PhysicsTag::GROUND_TAG]);
		IntersectCheckBox(_box, boxesMap[PhysicsTag::ENEMY_TAG]);
	}

	if (_box->GetBoxTag() == PhysicsTag::CAMERA_TAG)
	{
		// カメラと地面の判定処理
		IntersectCheckBox(_box, boxesMap[PhysicsTag::GROUND_TAG]);
	}

	if (_box->GetBoxTag() == PhysicsTag::MOVE_GROUND_TAG)
	{
		// 動く床とジャンプスイッチの判定処理
		IntersectCheckBox(_box, boxesMap[PhysicsTag::JUMP_SWITCH_TAG]);

		// 動く床と棘配置用床の判定処理
		IntersectCheckBox(_box, boxesMap[PhysicsTag::NEEDLE_TAG]);
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

		// 相手がエネミーでステータスが無効化状態だったら終了する
		if (itr->GetBoxTag() == PhysicsTag::ENEMY_TAG && itr->GetOwner()->GetState() == State::Disabling)
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
		IntersectCheckSphere(_sphere, boxesMap[PhysicsTag::GROUND_TAG]);

		// 接地判定スフィアと動く地面の当たり判定
		IntersectCheckSphere(_sphere, boxesMap[PhysicsTag::MOVE_GROUND_TAG]);

		// 接地判定スフィアとスイッチの土台の当たり判定
		IntersectCheckSphere(_sphere, boxesMap[PhysicsTag::SWITCH_BASE_TAG]);

		// 接地判定スフィアとスイッチの当たり判定
		IntersectCheckSphere(_sphere, boxesMap[PhysicsTag::SWITCH_TAG]);

		// 接地判定スフィアとジャンプスイッチの当たり判定
		IntersectCheckSphere(_sphere, boxesMap[PhysicsTag::JUMP_SWITCH_TAG]);
	}

	if (_sphere->GetSphereTag() == PhysicsTag::PLAYER_TRACKING_AREA_TAG)
	{
		// 接地判定スフィアとジャンプスイッチの当たり判定
		IntersectCheckSphere(_sphere, boxesMap[PhysicsTag::PLAYER_TAG]);
	}

	if (_sphere->GetSphereTag() == PhysicsTag::ENEMY_ATTACK_AREA_TAG)
	{
		// 接地判定スフィアとジャンプスイッチの当たり判定
		IntersectCheckSphere(_sphere, boxesMap[PhysicsTag::PLAYER_TAG]);
	}

	if (_sphere->GetSphereTag() == PhysicsTag::ATTACK_RANGE_TAG)
	{
		// ジャンプアタック判定スフィアとジャンプスイッチの当たり判定
		IntersectCheckSphere(_sphere, boxesMap[PhysicsTag::ENEMY_TAG]);
	}

	if (_sphere->GetSphereTag() == PhysicsTag::JUMP_ATTACK_PLAYER_TAG)
	{
		// 接地判定スフィアとジャンプスイッチの当たり判定
		IntersectCheckSphere(_sphere, boxesMap[PhysicsTag::ENEMY_TAG]);
		IntersectCheckSphere(_sphere, boxesMap[PhysicsTag::GROUND_TAG]);
		IntersectCheckSphere(_sphere, boxesMap[PhysicsTag::MOVE_GROUND_TAG]);
	}
}

/*
@fn BoxColliderを追加する関数
@brief　BoxColliderを当たり判定のタグを参照してそれぞれの可変長コンテナに格納を行う
@param	_box　追加するBoxColliderのポインタ
@param	_func 関数ポインタに紐づけする関数
*/
void PhysicsWorld::AddBoxes(BoxCollider* _box, onCollisionFunc _func)
{
	// 途中追加でない場合最初にそれぞれの配列に追加
	auto boxes = boxesMap.find(_box->GetBoxTag());
	if (boxes != boxesMap.end())
	{
		boxes->second.emplace_back(_box);
	}
	else
	{
		std::vector<BoxCollider*> tmpVector;
		tmpVector.emplace_back(_box);
		boxesMap[_box->GetBoxTag()] = tmpVector;
	}
	//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
	collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_box), _func));
}

/*
@fn BoxColliderを削除する関数
@brief　使わなくなったBoxColliderを当たり判定タグを参照してそれぞれの可変長コンテナから探し削除を行う
@param	_box　削除するBoxColliderのポインタ
*/
void PhysicsWorld::RemoveBoxes(BoxCollider* _box)
{
	auto boxes = std::find(boxesMap[_box->GetBoxTag()].begin(), boxesMap[_box->GetBoxTag()].end(), _box);
	if (boxes != boxesMap[_box->GetBoxTag()].end())
	{
		std::iter_swap(boxes, boxesMap[_box->GetBoxTag()].end() - 1);
		boxesMap[_box->GetBoxTag()].pop_back();
	}
	collisionFunction.erase(_box);
}

/*
@fn SphereColliderを追加する関数
@brief　SphereColliderを当たり判定のタグを参照してそれぞれの可変長コンテナに格納を行う
@param	_sphere　追加するSphereColliderのポインタ
@param	_func 関数ポインタに紐づけする関数
*/
void PhysicsWorld::AddSpheres(SphereCollider* _sphere, onCollisionFunc _func)
{
	auto spheres = spheresMap.find(_sphere->GetSphereTag());
	if (spheres != spheresMap.end())
	{
		spheres->second.emplace_back(_sphere);
	}
	else
	{
		std::vector<SphereCollider*> tmpVector;
		tmpVector.emplace_back(_sphere);
		spheresMap[_sphere->GetSphereTag()] = tmpVector;
	}
	//コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
	collisionFunction.insert(std::make_pair(static_cast<ColliderComponent*>(_sphere), _func));
}

/*
@fn 削除するSphereColliderが格納されている関数
@brief　使わなくなったSphereColliderを当たり判定タグを参照してそれぞれの可変長コンテナから探し削除を行う
@param	_sphere　削除するSphereColliderのポインタ
*/
void PhysicsWorld::RemoveSpheres(SphereCollider* _sphere)
{
	auto spheres = std::find(spheresMap[_sphere->GetSphereTag()].begin(), spheresMap[_sphere->GetSphereTag()].end(), _sphere);
	if (spheres != spheresMap[_sphere->GetSphereTag()].end())
	{
		std::iter_swap(spheres, spheresMap[_sphere->GetSphereTag()].end() - 1);
		spheresMap[_sphere->GetSphereTag()].pop_back();
	}
	collisionFunction.erase(_sphere);
}