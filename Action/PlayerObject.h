#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "PlayerObjectStateBase.h"

// �N���X�̑O���錾
class SkeletalMeshComponent;
class Animation;
class BoxCollider;
class Mesh;
class SphereCollider;
enum class PlayerState;


/*
@file PlayerObject.h
@brief �Q�[�����̃v���C���[
	   �Q�[�����̃v���C���[�̏������ƍX�V�������s��
*/
class PlayerObject : public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	�ė��p���邩�t���O
	@param	�I�u�W�F�N�g���ʗptag
	*/
	PlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~PlayerObject();

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;
	
	/*
	@fn ���͏���
	@brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
	*/
	void GameObjectInput(const InputState& _keyState)override;
	
	/*
	@fn �߂荞�ݔ���
	*/
	void FixCollision(AABB& myAABB, const AABB& pairAABB);
	
	/*
	@fn �����߂�����
	*/
	void playerCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox,Vector3& _calcFixVec);
	
	/*
	@fn �O���x�N�g����p���ăL�����N�^�[����]������֐�
	*/
	void RotateToNewForward(const Vector3& forward);


	//----------------------getter�Q------------------------------//
	// �����点�邩������Ȃ�

	/*
	@fn SkeletalMeshComponent��state�ɓn���֐�
	@return SkeletalMeshComponent�@SkeletalMeshComponent�̃|�C���^��Ԃ�
	*/
	SkeletalMeshComponent* GetSkeletalMeshComponent() { return skeltalMeshComponent; }

	/*
	@fn Animation��Ԃ��֐�
	@return Animation Animation�̃|�C���^��Ԃ�
	*/
	const Animation* GetAnimation(PlayerState _state);

	// �萔�ł���O���r�e�B�i�d�́j�𑼂�CPP�Ō��邽�߂�getter
	static const float GetGravity() { return Gravity; }


	// ���neffect���Ŏg�p����t���O�p��getter
	static bool GetChackJumpFlag() { return chackJumpFlag; }
	static bool GetChackIsJumpingFlag() { return chackIsJumping; }

	// �߂�l��Vector3
	Vector3 GetForwardVec() { return forwardVec; }
	Vector3 GetRightVec() { return rightVec; }
	Vector3 GetCharaForwardVec() { return charaForwardVec;	}
	Vector3 GetRotateVec() { return rotateVec; }
	Vector3 GetVelocity() { return velocity; }
	Vector3 GetRespownPos() { return respownPos; }

	// �߂�l��const float
	const float GetDeadSpace() { return DeadSpace; }
	const float GetFirstMovePower() { return FirstMovePower; }
	const float GetMovePower() { return MovePower; }
	const float GetAirMovePower() { return AirMovePower; }
	const float GetFirstJumpPower() { return FirstJumpPower; }
	const float GetDecelerationForce() { return DecelerationForce; }

	// �߂�l��float
	float GetMoveSpeed() { return moveSpeed; }
	float GetJumpPower() { return jumpPower; }

	// �߂�l��int
	int GetTurnDelayCount() { return turnDelayCount; }

	// �߂�l��bool
	bool GetOnGround() { return onGround; }
	bool GetJumpFlag() { return jumpFlag; }
	bool GetSwitchJumpFlag() { return switchJumpFlag; }
	bool GetIsAvailableJumpKey() { return isAvailableJumpKey; }
	bool GetInputFlag() { return inputFlag; }
	bool GetRunFlag() { return runFlag; }
	bool GetDeadFlag() { return deadFlag; };
	bool GetRespawnFlag() { return respawnFlag; };
	bool GetIsAvailableInput() { return isAvailableInput; };
	bool GetIsHitWall() { return isHitWall; };

	// �V�[���J�ڎ��Ɏg���t���O��getter
	bool GetClearFlag() { return clearFlag; }
	bool GetNextSceneFlag() { return nextSceneFlag; }
	bool GetReStartFlag() { return reStartFlag; }

	// �߂�l��int
	int GetJumpFrameCount() { return jumpFrameCount; }

	// �߂�l��PlayerState
	PlayerState GetNowState() { return nowState; }

	//---------------------------setter�Q------------------------------//
	// �����点�邩������Ȃ�
	// ������Vector3
	void SetCharaForwardVec(Vector3 _charaForwardVec) { charaForwardVec = _charaForwardVec; }
	void SetVelocity(Vector3 _velocity) { velocity = _velocity; }
	void SetRespownPos(Vector3 _respownPos) { velocity = _respownPos; }

	// ������float
	void SetMoveSpeed(float _moveSpeed) { moveSpeed = _moveSpeed; }

	// ������int
	void SetTurnDelayCount(bool _turnDelayCount) { turnDelayCount = _turnDelayCount; }

	// ������bool
	void SetJumpFlag(bool _jumpFlag) { jumpFlag = _jumpFlag; }
	void SetSwitchJumpFlag(bool _switchJumpFlag) { switchJumpFlag = _switchJumpFlag; }
	void SetIsAvailableJumpKey(bool _isAvailableJumpKey) { isAvailableJumpKey = _isAvailableJumpKey; }
	void SetJumpPower(float _jumpPower) { jumpPower = _jumpPower; }
	void SetInputFlag(bool _inputFlag) { inputFlag = _inputFlag; }
	void SetRunFlag(bool _runFlag) { runFlag = _runFlag; }
	void SetJumpFrameCount(bool _jumpFrameCount) { jumpFrameCount = _jumpFrameCount; }
	void SetDeadFlag(bool _deadFlag) { deadFlag = _deadFlag; }
	void SetRespawnFlag(bool _respawnFlag) { respawnFlag = _respawnFlag; }
	void SetIsAvailableInput(bool _isAvailableInput) { isAvailableInput = _isAvailableInput; }
	void SetIsHitWall(bool _isHitWall) { isHitWall = _isHitWall; }




private:

	/*
	@fn �N���A���Ă����Ԃ����`�F�b�N����֐�
	*/
	void ClearChack(Tag _tag);

	//----------------Component�nClass�ϐ�--------------------//
	// 3D���f���̕`����s���N���X
	SkeletalMeshComponent* skeltalMeshComponent;
	// Mesh�̓ǂݍ��݂��s���N���X
	Mesh* mesh;
	// AABB�̓����蔻����s���N���X
	BoxCollider* boxCollider;
	// ���̂̓����蔻����s���N���X
	SphereCollider* groundChackSphereCol;
	//--------------------------------------------------------//

	//----------------private�֐��Q---------------------------//
	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/	
	void OnCollision(const GameObject& _hitObject)override;

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�(��������p)
	@param	��������GameObject
	*/
	void OnCollisionGround(const GameObject& _hitObject);

	//--------------------------------------------------------//
	
	//--------------------static�ϐ��Q------------------------//
	// �ŏI�X�e�[�W�p�̃N���A�t���O
	bool clearFlag;
	// �ŏI�X�e�[�W�ȊO�ł̎��̃V�[���֑J�ڂ���t���O
	bool nextSceneFlag;
	// ��莞�Ԉȏ���͂��Ȃ������ۂɃ^�C�g���֖߂�t���O
	bool reStartFlag;
	// ���neffect�𔭐�������ۂɎg�p����t���O
	// JumpFlag�`�F�b�N�p
	static bool chackJumpFlag;
	// isJumping�`�F�b�N�p�i�W�����v�����ǂ����j
	static bool chackIsJumping;
	//�d��
	static const float Gravity;
	//--------------------------------------------------------//
	
	//------------------------�萔�Q--------------------------//
	// ���X�^�[�g�������鎞��
	const int RestartTime;
	// ���͒l��dead�X�y�[�X
	const float DeadSpace;
	//�����x�̒萔
	const float MovePower;
	// �󒆂ł̉����萔
	const float AirMovePower;
	// ���������
	const float DecelerationForce;
	// �����x
	const float FirstMovePower;
	//�����W�����v�͒萔
	const float FirstJumpPower;
	// �v���C���[�������������ǂ����𔻒肷��ʒu
	//�i������X�e�[�W�ɗ������Ȃ��̂ł������蔲���Ă��܂����ꍇ�j
	const float FallPpsitionZ;
	// ���������Ƃ��̃|�W�V���������炷
	const float FirstPositionZ;
	// �Ђ�ޑ��x�萔
	const float FlinchSpeed;

	//--------------------------------------------------------//
	//--------------------------�ϐ��Q------------------------//
	//�����߂��Ɏg���v���C���[��AABB
	AABB playerBox;
	//�E�����x�N�g��
	Vector3 rightVec;
	//�L�����N�^�[�̑O���x�N�g��
	Vector3 charaForwardVec;
	//�����ɍ��킹�ĉ�]�����邽�߂̃x�N�g��
	Vector3 rotateVec;
	// �������ꂽ�Ƃ��̃|�W�V������ۑ����邽�߂�vector3�ϐ�
	Vector3 firstPos;
	// ���X�|�[������ꏊ
	Vector3 respownPos;
	// ���̃I�u�W�F�N�g���牟����Ă��鎞�̑��x
	Vector3 pushedVelocity;

	// ���񂾍ۂɂ������X�|�[�������Ȃ����߂̃J�E���g
	int respawnCount;
	// ���͂��Ȃ��ԃJ�E���g
	int reStartCount;
	//�W�����v�{�^����������Ă���Ԃ̃t���[���J�E���g
	int jumpFrameCount;
	// �U��Ԃ�f�B���C�p�J�E���g�ϐ�
	int turnDelayCount;

	// ���x
	float moveSpeed;
	//�W�����v��
	float jumpPower;

	//���͂����������ǂ������肷�邽�߂̃t���O
	bool inputFlag;
	//���������W�����v�{�^�������p�\���t���O
	bool isAvailableJumpKey;
	//�W�����v�ł��邩�t���O
	bool jumpFlag;
	//�W�����v�X�C�b�`�����������ǂ���
	bool switchJumpFlag;
	//�ڒn�t���O
	bool onGround;
	//�����Ԃ��ǂ���
	bool runFlag;
	// ���͂��\���ǂ���
	bool isAvailableInput;
	// �_�E����Ԃ��ǂ���
	bool downFlag;
	// �_�E�����R���e�B�j���[�I����YES���I�����ꂽ���ǂ���
	bool downUpFlag;
	// �_�E�����R���e�B�j���[�I����NO���I�����ꂽ���ǂ���
	bool downOverFlag;
	// ���X�|�[���p�t���O
	bool respawnFlag;
	// dead��Ԃ���������Ȃ����m�F�p�t���O
	bool deadFlag;
	// �ǂƉ����߂����s������
	bool isHitWall;
	
	// ���̃v���[���[��state��Ԃ�ۑ����邽�߂̕ϐ�
	PlayerState nowState;
	// �ύX���ꂽ���̃v���[���[��state��Ԃ�ۑ����邽�߂̕ϐ�
	PlayerState nextState;

	//----------------------�ϒ��z��Q----------------------//
	// Animation�v�[��
	std::vector<const Animation*> animTypes;
	// state�v�[��
	std::vector<class PlayerObjectStateBase*> statePools;
	//--------------------------------------------------------//
};

