#include "PlayerObjectStateExplosionBlowAway.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateExplosionBlowAway::PlayerObjectStateExplosionBlowAway()
	: knockBackFrameCount(0)
	, KnockBackPower(20.0f)
	, KnockBackTime(10)
	, FallDeadPositonZ(-500.0f)
{
}

PlayerObjectStateExplosionBlowAway::~PlayerObjectStateExplosionBlowAway()
{
}

PlayerState PlayerObjectStateExplosionBlowAway::Update(PlayerObject* _owner, float _deltaTime)
{
	// �m�b�N�o�b�N�̎��Ԃ𐔂���
	++knockBackFrameCount;

	// �ڒn��������
	if (!_owner->GetOnGround())
	{
		// �d�͂�������
		velocity.z -= PlayerObject::GetGravity() * _deltaTime;
	}

	// �m�b�N�o�b�N���Ԃ��߂��Ă��Ȃ�������
	if (knockBackFrameCount <= KnockBackTime)
	{
		knockBackSpeed += KnockBackPower;
		// ���x��ǉ�
		velocity += knockBackDirection * knockBackSpeed;
	}

	// �ړ����x�Ƀf���^�^�C�����|���Ă�����|�W�V�����ɒǉ����čX�V
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// �ڒn���Ƀm�b�N�o�b�N���Ԃ��߂�����
	if (_owner->GetOnGround() && knockBackFrameCount >= KnockBackTime)
	{
		// ���x������
		velocity = Vector3::Zero;
		_owner->SetVelocity(velocity);
		// �����Ƀq�b�g�������ǂ�����false�ɃZ�b�g
		_owner->SetIsHitExplosion(false);
		// state���A�C�h�����O�ɕύX
		state = PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE;
	}

	// �������S�n�_�ɓ��B������
	if (FallDeadPositonZ >= _owner->GetPosition().z)
	{
		// ���x������
		velocity = Vector3::Zero;
		_owner->SetVelocity(velocity);
		// �����Ƀq�b�g�������ǂ�����false�ɃZ�b�g
		_owner->SetIsHitExplosion(false);
		// �W�����v���[�v��Ԃ̃A�j���[�V�������Đ�
		skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPLOOP));
		// �X�e�[�^�X�𗎉����S�ɑJ��
		state = PlayerState::PLAYER_STATE_FALL_DEAD;
	}

	// ���S��ԃ`�F�b�N
	CheckDeadFlag(_owner);
	// ���Ԑ؂�`�F�b�N
	CheckTimeOverFlag();

	// �X�V���ꂽstate��Ԃ�
	return state;
}

void PlayerObjectStateExplosionBlowAway::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_KNOCKBACK));
	// state�����ݏ�Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_BLOWAWAY;

	// ���x������
	velocity = Vector3::Zero;
	knockBackSpeed = 50.0f;

	// �J�E���g��������
	knockBackFrameCount = 0;

	// ���������G�l�~�[�̃|�W�V�������擾
	hitEnemyPosition = _owner->GetHitKnockBackObjectPosition();
	// �m�b�N�o�b�N��������x�N�g�����v�Z
	knockBackDirection = _owner->GetPosition() - hitEnemyPosition;

	// ������0�ɋ߂��Ȃ�������
	if (!Math::NearZero(knockBackDirection.Length()))
	{
		// ���K��
		knockBackDirection.Normalize();
	}

	// ��]����
	// �m�b�N�o�b�N�����������Ƌt�̕�������������̂�x,y����-1.0��������
	RotationProcess(_owner, Vector3(knockBackDirection.x * -1.0f, knockBackDirection.y * -1.0f, 0.0f), _owner->GetCharaForwardVec());

	// ������x�N�g����ǉ�
	knockBackDirection.z = 1.0f;
}
