#include "TitleGroundObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"

TitleGroundObject::TitleGroundObject(const Vector3& _p, const Vector3& _size, const Vector3& _playerPos, const Tag& _objectTag) :
	BoxObject(_p ,_size , _objectTag)
	, targetPos(_playerPos)
{
	//GameObject�����o�ϐ��̏�����
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	rePositionFlag = false;
	goalPos = Vector3(position.x, position.y - 1000.0f, position.z);
	initPos = Vector3(position.x, position.y + 1000.0f, position.z);
	velocity = Vector3(0.0f, -400.0f, 0.0f);
	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);

}

TitleGroundObject::~TitleGroundObject()
{
}

void TitleGroundObject::UpdateGameObject(float _deltaTime)
{
	// �|�W�V�����ɑ��x�𑫂�
	position += velocity * _deltaTime;
	// �|�W�V�������X�V
	SetPosition(position);
	// �w��ʒu�܂ŃI�u�W�F�N�g�������Ă�����
	if (position.y <= goalPos.y)
	{
		// ���|�W�V�����p�t���O��true��
		rePositionFlag = true;
	}

	// ���|�W�V�����p�t���O��true��������
	if (rePositionFlag == true)
	{
		// �|�W�V�����ɏ����|�W�V�������Z�b�g
		position = initPos;
		// �|�W�V�������X�V
		SetPosition(position);
		// ���|�W�V�����p�t���O��false��
		rePositionFlag = false;
	}
	
}
