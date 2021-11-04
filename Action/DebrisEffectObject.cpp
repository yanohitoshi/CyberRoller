#include "DebrisEffectObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Mesh.h"

DebrisEffectObject::DebrisEffectObject(const Vector3& _pos, const Vector3& _direction)
	: GameObject(false,Tag::GROUND)
	, MovePower(50.0f)
{
	//GameObject�����o�ϐ��̏�����
	SetPosition(_pos);
	SetScale(Vector3(2.0f,2.0f,2.0f));
	tag = Tag::GROUND;
	state = Active;
	isPushBackToPlayer = false;
	isCheckGroundToPlayer = false;
	isPushBackToCamera = false;

	direction = _direction;
	// �������ԏ�����
	lifeCount = 60;

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/groundModel/debrisGround.gpmesh"));
	//���b�V�����擾
	mesh = meshComponent->GetMesh();
	// �P�x�����擾
	luminance = mesh->GetLuminace();

	moveSpeed = (float)(rand() % 1500 + 1000 );

	Rotation(this, (float)(rand() % 361 + 50), Vector3::UnitX);
	Rotation(this, (float)(rand() % 361 + 50), Vector3::UnitY);
	Rotation(this, (float)(rand() % 361 + 50), Vector3::UnitZ);
}

DebrisEffectObject::~DebrisEffectObject()
{
}

void DebrisEffectObject::UpdateGameObject(float _deltaTime)
{
	// �������Ԃ����炷
	LifeCountDown();
	velocity = direction * moveSpeed;
	SetPosition(position + velocity * _deltaTime);

	// z�������x�N�g�����}�C�i�X�����ɂ��Ă���
	direction.z -= 0.05f;

	// -1.0�ȉ��ɂȂ�����1.0�ŌŒ�
	if (direction.z <= -1.0f)
	{
		direction.z = -1.0f;
	}

	// ���C�t�J�E���g��0�ȉ��ɂȂ�����
	if (lifeCount <= 0)
	{
		// �X�e�[�^�X��dead�ɕύX
		state = State::Dead;
		SetState(state);
	}
}

void DebrisEffectObject::LifeCountDown()
{
	//�������Ԃ��[���ɂȂ�Ƃ��̃I�u�W�F�N�g���X�V�I������
	if (lifeCount <= 0)
	{
		meshComponent->SetVisible(false);
		SetState(State::Dead);

	}
	else
	{
		meshComponent->SetVisible(true);
		lifeCount--;
	}
}
