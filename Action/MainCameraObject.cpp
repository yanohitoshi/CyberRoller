#include "MainCameraObject.h"
#include "CameraObjectBase.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "InputSystem.h"
#include "PlayerObject.h"
#include "LineSegmentCollider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "FirstStageScene.h"
#include "FirstStageUI.h"
#include "CountDownFont.h"
#include "PlayerObjectStateIdlingDance.h"

const float MainCameraObject::yawSpeed = 0.055f;
const float MainCameraObject::pitchSpeed = 0.03f;

MainCameraObject::MainCameraObject(const Vector3 _pos, PlayerObject* _playerObject) :
	CameraObjectBase(false,Tag::CAMERA)
{
	SetPosition(_pos);
	float PI = Math::Pi;
	yaw = Math::ToRadians(180);
	pitch = Math::ToRadians(30);
	radius = 700.0f;
	timeOverRadius = 400.0f;
	danceRadius = 500.0f;

	height = 0.0f;
	tmpMovePos = Vector3(0.0f,0.0f,0.0f);
	forwardVec = Vector3(1.0f, 0.0f, 0.0f);
	boxcollider = new BoxCollider(this, ColliderComponent::CameraTag, GetOnCollisionFunc());
	AABB aabb = { Vector3(-100.0f,-100.0f,-50.0f),Vector3(100.0f,100.0f,50.0f) };
	boxcollider->SetObjectBox(aabb);

	playerObject = _playerObject;

	lerpObjectPos = Vector3::Zero;
	hitPosition = Vector3::Zero;

	hitFlag = false;
	tmpHitFlag = false;
}


MainCameraObject::~MainCameraObject()
{
}

void MainCameraObject::UpdateGameObject(float _deltaTime)
{
	if (playerObject->GetClearFlag() == false && CountDownFont::timeOverFlag == false && !PlayerObjectStateIdlingDance::GetIsDancing())
	{
		// ���̃t���[���œ������Ă��đO�̃t���[���œ������Ă��Ȃ����
		if (hitFlag == true && tmpHitFlag == false)
		{
			// ���������|�W�V�������}�C�i�X��������
			if (hitPosition.x < 0.0f)
			{
				hitPosition.x *= -1.0f;
			}
			if (hitPosition.y < 0.0f)
			{
				hitPosition.y *= -1.0f;
			}

			// ���������|�W�V�������׏����������J�����̉�]���a�Ƃ��č̗p
			if (hitPosition.x < hitPosition.y)
			{
				radius = lerpObjectPos.x - hitPosition.x;
				// ����Ώە����瓖�������ꏊ�������Ē��������
				// ���̂܂܎g���ƕǂɂ߂荞�މ\��������̂ŏ�������������
				radius -= 20.f;
			}
			else if (hitPosition.x > hitPosition.y)
			{
				// ����Ώە����瓖�������ꏊ�������Ē��������
				radius = lerpObjectPos.y - hitPosition.y;
				// ���̂܂܎g���ƕǂɂ߂荞�މ\��������̂ŏ�������������
				radius -= 20.f;
			}

			// ���a���}�C�i�X�ɂȂ��Ă�����v���X�ɕϊ�
			if (radius <= 0.0f)
			{
				radius *= -1.0f;
			}
		}
		else
		{
			radius = 700.0f;
		}

		if (radius >= 700.0f)
		{
			radius = 700.0f;
		}
		else if (radius <= 10.0f)
		{
			radius = 10.0f;
		}

		if (pitch < 0.0f && pitch > -30.0f)
		{
			radius -= 300.0f;
		}
		//else if (pitch <= -30.0f && pitch >= -60.0f)
		//{
		//	radius -= 600.0f;
		//}

		tmpMovePos.x = radius * cosf(pitch) * cosf(yaw) + lerpObjectPos.x;
		tmpMovePos.y = radius * cosf(pitch) * sinf(yaw) + lerpObjectPos.y;
		tmpMovePos.z = radius * sinf(pitch) + height + lerpObjectPos.z;

		position = Vector3::Lerp(position, tmpMovePos, _deltaTime * 9.0f);
		SetPosition(position);
		Vector3 viewPosition = Vector3(lerpObjectPos.x, lerpObjectPos.y, lerpObjectPos.z + 100.0f);
		view = Matrix4::CreateLookAt(position, viewPosition, Vector3(0.0f, 0.0f, 1.0f));
		RENDERER->SetViewMatrix(view);

		forwardVec = lerpObjectPos - position;
		forwardVec.Normalize();
		forwardVec.z = 0.0f;

		hitPosition = Vector3::Zero;
		tmpHitFlag = hitFlag;
		hitFlag = false;
	}
	else if (playerObject->GetClearFlag() == true)
	{
		view = Matrix4::CreateLookAt(position, lerpObjectPos, Vector3(0.0f, 0.0f, 1.0f));
		RENDERER->SetViewMatrix(view);
	}
	else if (CountDownFont::timeOverFlag == true)
	{
		yaw += 0.01f;
		tmpMovePos.x = timeOverRadius * cosf(pitch) * cosf(yaw) + lerpObjectPos.x;
		tmpMovePos.y = timeOverRadius * cosf(pitch) * sinf(yaw) + lerpObjectPos.y;
		tmpMovePos.z = radius * sinf(pitch) + height + lerpObjectPos.z;

		position = Vector3::Lerp(position, tmpMovePos, _deltaTime * 7.0f);
		SetPosition(position);

		view = Matrix4::CreateLookAt(position, lerpObjectPos, Vector3(0.0f, 0.0f, 1.0f));
		RENDERER->SetViewMatrix(view);

	}
	else if (PlayerObjectStateIdlingDance::GetIsDancing() && CountDownFont::timeOverFlag == false)
	{
		yaw += 0.01f;
		tmpMovePos.x = danceRadius * cosf(pitch) * cosf(yaw) + lerpObjectPos.x;
		tmpMovePos.y = danceRadius * cosf(pitch) * sinf(yaw) + lerpObjectPos.y;
		tmpMovePos.z = radius * sinf(pitch) + height + lerpObjectPos.z;

		position = Vector3::Lerp(position, tmpMovePos, _deltaTime * 7.0f);
		SetPosition(position);

		view = Matrix4::CreateLookAt(position, lerpObjectPos, Vector3(0.0f, 0.0f, 1.0f));
		RENDERER->SetViewMatrix(view);
	}

}

void MainCameraObject::GameObjectInput(const InputState& _keyState)
{
	Vector2 rightAxis = Vector2(0.0f, 0.0f);
	rightAxis = _keyState.Controller.GetLAxisRightVec();

	if (playerObject->GetClearFlag() == false)
	{
		if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_RIGHT) == 1 ||
			rightAxis.x > 0)
		{
			yaw += yawSpeed;
		}

		if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_LEFT) == 1 ||
			rightAxis.x < 0)
		{
			yaw -= yawSpeed;
		}

		if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_UP) == 1 ||
			rightAxis.y < 0)
		{
			pitch -= pitchSpeed;
		}

		if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_DOWN) == 1 ||
			rightAxis.y > 0)
		{
			pitch += pitchSpeed;
		}

	}

	if (pitch > Math::ToRadians(70.0f))
	{
		pitch = Math::ToRadians(70.0f);
	}
	if (pitch < Math::ToRadians(-30.0f))
	{
		pitch = Math::ToRadians(-30.0f);
	}
}


/*
@param _offset�@���������W�Ƃ̍�
@param _parentPos�@������W
*/
void MainCameraObject::SetViewMatrixLerpObject(const Vector3 & _offset, const Vector3 & _parentPos)
{
	hasParentObject = true;
	offsetPos = _offset;
	lerpObjectPos = _parentPos;
}


void MainCameraObject::OnCollision(const GameObject& _hitObject)
{	
	if (hitFlag == false)
	{
		hitFlag = true;
		hitPosition = _hitObject.GetPosition();
	}

	AABB myAabb = boxcollider->GetWorldBox();
	FixCollision(myAabb, _hitObject.aabb, _hitObject.GetTag());

}

void MainCameraObject::FixCollision(AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag)
{
	if (_pairTag == Tag::GROUND || _pairTag == Tag::WALL || _pairTag == Tag::FIRST_MOVE_WALL ||
		_pairTag == Tag::SECOND_MOVE_WALL || _pairTag == Tag::NEXT_SCENE_MOVE_WALL||
		_pairTag == Tag::CLEAR_SCENE_MOVE_WALL || _pairTag == Tag::TUTORIAL_MOVE_WALL)
	{
		Vector3 ment = Vector3(0, 0, 0);
		calcCollisionFixVec(myAABB, pairAABB, ment);
		SetPosition(position + ment);


	}

}

void MainCameraObject::calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
{
	_calcFixVec = Vector3(0, 0, 0);

	float dx1 = _fixedBox.min.x - _movableBox.max.x;
	float dx2 = _fixedBox.max.x - _movableBox.min.x;
	float dy1 = _fixedBox.min.y - _movableBox.max.y;
	float dy2 = _fixedBox.max.y - _movableBox.min.y;
	float dz1 = _fixedBox.min.z - _movableBox.max.z;
	float dz2 = _fixedBox.max.z - _movableBox.min.z;

	// dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;


	// x, y, z�̂����ł��������������ňʒu�𒲐�
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
