//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ResultSwitchBaseObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "ResultSwitchObject.h"

/*
@fn コンストラクタ
@param	ポジション
@param	objectのサイズ
@param	オブジェクト判別用tag
*/
ResultSwitchBaseObject::ResultSwitchBaseObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag)
	: GameObject(false, _objectTag)
	, Angle(90.0f)
{
	// ポジション・スケール・Tagの初期化
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	isPushBackToPlayer = true;
	isChackGroundToPlayer = true;
	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);

	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/switch_model/S_EnergySwitch.gpmesh"));

	//Z軸を90度回転させる
	float radian = Math::ToRadians(Angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitY, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

	// リザルト用のスイッチ本体を生成
	new ResultSwitchObject(this, Vector3(2.6f, 2.6f, 2.0f), tag, Angle);
	
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
ResultSwitchBaseObject::~ResultSwitchBaseObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void ResultSwitchBaseObject::UpdateGameObject(float _deltaTime)
{
}
