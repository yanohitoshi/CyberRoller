#include "ResultSwitchObject.h"
#include "Skeleton.h"
#include "ChangeColorMeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "BoxCollider.h"
#include "MainCameraObject.h"
#include "TutorialSwitchParticlEffect.h"
#include "TutorialSwitchOkEffect.h"
#include "SwitchEffectMakeManeger.h"
#include "FirstStageUI.h"
#include <string>


ResultSwitchObject::ResultSwitchObject(GameObject* _owner, const Vector3& _size, const Tag& _objectTag, const float _angle)
	: GameObject(false, _objectTag)
	, AllClearColer(Vector3(1.0f, 1.0f, 0.5f))
	, OnColor(Vector3(0.1f, 0.1f, 1.0f))
	, OffColor(Vector3(1.0f, 0.1f, 0.1f))
{
	//GameObjectメンバ変数の初期化
	position = _owner->GetPosition();
	SetPosition(position);
	SetScale(_size);
	tag = _objectTag;
	velocity = Vector3::Zero;

	//モデル描画用のコンポーネント
	meshComponent = new ChangeColorMeshComponent(this, false, true);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/switch_model/S_EnergyCube.gpmesh"));

	//Z軸を90度回転させる
	float radian = Math::ToRadians(_angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitY, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

	// スイッチの色を設定
	meshComponent->SetColor(AllClearColer);
}

ResultSwitchObject::~ResultSwitchObject()
{
}

void ResultSwitchObject::UpdateGameObject(float _deltaTime)
{
}



