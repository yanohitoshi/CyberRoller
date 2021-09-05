#include "ResultCameraObject.h"
#include "Renderer.h"

ResultCameraObject::ResultCameraObject(const Vector3 _pos)
	:CameraObjectBase(false, Tag::RESULT_OBJECT)
	, ShiftPosition(5000.0f)
{
	//Title用に表示してるobjectから少し離れた位置に配置
	SetPosition(Vector3(_pos.x - ShiftPosition, _pos.y , _pos.z));
	// リザルトシーンでのカメラの注視点を保存
	target = _pos;
}

ResultCameraObject::~ResultCameraObject()
{
}

void ResultCameraObject::UpdateGameObject(float _deltaTime)
{
	//view行列を生成
	view = Matrix4::CreateLookAt(position, target, Vector3::UnitZ);
	//レンダラーのview行列にセット
	RENDERER->SetViewMatrix(view);
}

void ResultCameraObject::GameObjectInput(const InputState& _keyState)
{
}
