//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TitleJumpAttackPlayerObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "TitlePlayerObject.h"
#include "JumpAttackEffectManager.h"

/*
@fn コンストラクタ
@param	親クラスのポインタ
@param	オブジェクトのサイズ
@param	オブジェクト判別用tag
*/
TitleJumpAttackPlayerObject::TitleJumpAttackPlayerObject(TitlePlayerObject* _ownerObject, const Vector3& _size, const Tag _objectTag)
	: GameObject(false, _objectTag)
	, ShiftPositionZ(100.0f)
{
	ownerObject = _ownerObject;
	position = ownerObject->GetPosition();
	position.z += ShiftPositionZ;
	SetPosition(position);
	SetScale(_size);

	meshComponent = new MeshComponent(this, false, false);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Player/JumpAttackPlayerModel/JumpAttackPlayer.gpmesh"));
	meshComponent->SetVisible(false);
	//メッシュ情報取得
	mesh = meshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();
	SetState(State::Disabling);
	new JumpAttackEffectManager(this);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
TitleJumpAttackPlayerObject::~TitleJumpAttackPlayerObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void TitleJumpAttackPlayerObject::UpdateGameObject(float _deltaTime)
{
	if (!meshComponent->GetVisible())
	{
		SetPosition(ownerObject->GetPosition());
		SetState(State::Disabling);
	}
	else
	{
		SetState(State::Active);
	}
}

/*
@fn 回転処理関数
*/
void TitleJumpAttackPlayerObject::RotationProcess(float _angle, Vector3 _axis)
{
	//Z軸を90度回転させる
	float radian = Math::ToRadians(_angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}
