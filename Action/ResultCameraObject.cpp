//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ResultCameraObject.h"
#include "Renderer.h"

/*
@brief	コンストラクタ
@param	カメラの注視点
*/
ResultCameraObject::ResultCameraObject(const Vector3 _pos)
	:CameraObjectBase(false, Tag::RESULT_OBJECT)
	, ShiftPosition(5000.0f)
{
	//Title用に表示してるobjectから少し離れた位置に配置
	SetPosition(Vector3(_pos.x - ShiftPosition, _pos.y , _pos.z));
	// リザルトシーンでのカメラの注視点を保存
	target = _pos;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
ResultCameraObject::~ResultCameraObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	deltaTime固定
*/
void ResultCameraObject::UpdateGameObject(float _deltaTime)
{
	//view行列を生成
	view = Matrix4::CreateLookAt(position, target, Vector3::UnitZ);
	//レンダラーのview行列にセット
	RENDERER->SetViewMatrix(view);
}