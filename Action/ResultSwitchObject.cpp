//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
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

/*
@fn コンストラクタ
@param	ポジション
@param	objectのサイズ
@param	オブジェクト判別用tag
@param	回転角度
*/
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
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/Switch/model/S_EnergyCube.gpmesh"));
	luminance = 0.2f;
	//Z軸を90度回転させる
	float radian = Math::ToRadians(_angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitY, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

	// スイッチの色を設定
	meshComponent->SetColor(AllClearColer);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
ResultSwitchObject::~ResultSwitchObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void ResultSwitchObject::UpdateGameObject(float _deltaTime)
{
}