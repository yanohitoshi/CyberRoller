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
@enum AnimState
	�@�v���C���[�̃A�j���[�V�����̏��
	  �^�C�g���p
*/
enum AnimState
{
	IDLE,
	WALK,
	RUN,
	JUMPLOOP,
	JUMPSTART,
	JUMPEND,
	DOWN,
	DOWN_LOOP,
	DOWN_UP,
	DOWN_OVER,
	PLAYER_DEAD,
	ITEMNUM
};

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
	void FixCollision(AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag);
	
	/*
	@fn �����߂�����
	*/
	void playerCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox,Vector3& _calcFixVec,const Tag& __pairTag);
	
	// �V�[���J�ڎ��Ɏg���t���O��getter
	static bool GetClearFlag() { return clearFlag; }
	static bool GetNextSceneFlag() { return nextSceneFlag; }
	static bool GetReStartFlag() { return reStartFlag; }

	// ���neffect���Ŏg�p����t���O�p��getter
	static bool GetChackJumpFlag() { return chackJumpFlag; }
	static bool GetChackIsJumpingFlag() { return chackIsJumping; }

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

	//--------------state���Ń����o�[�ϐ����g�p���邽�߂�getter�Q------------------------------//
	// �����点�邩������Ȃ�
	// �߂�l��Vector3
	Vector3 GetForwardVec() { return forwardVec; }
	Vector3 GetRightVec() { return rightVec; }
	Vector3 GetCharaForwardVec() { return charaForwardVec;	}
	Vector3 GetTmpCharaForwardVec() { return tmpCharaForwardVec; }
	Vector3 GetRotateVec() { return rotateVec; }
	Vector3 GetVelocity() { return velocity; }
	Vector3 GetRespownPos() { return respownPos; }

	// �߂�l��const float
	const float GetDeadSpace() { return DeadSpace; }
	const float GetFirstMovePower() { return FirstMovePower; }
	const float GetMovePower() { return movePower; }
	const float GetAirMovePower() { return airMovePower; }
	const float GetFirstJumpPower() { return FirstJumpPower; }
	const float GetDecelerationForce() { return decelerationForce; }

	// �߂�l��float
	float GetMoveSpeed() { return moveSpeed; }
	float GetJumpPower() { return jumpPower; }

	// �߂�l��int
	int GetTurnDelayCount() { return turnDelayCount; }

	// �߂�l��bool
	bool GetOnGround() { return onGround; }
	bool GetJumpFlag() { return jumpFlag; }
	bool GetIsJumping() { return isJumping; }
	bool GetSwitchJumpFlag() { return switchJumpFlag; }
	bool GetIsAvailableJumpKey() { return isAvailableJumpKey; }
	bool GetInputFlag() { return inputFlag; }
	bool GetRunFlag() { return runFlag; }
	bool GetDeadFlag() { return deadFlag; };
	bool GetRespawnFlag() { return respawnFlag; };
	bool GetIsAvailableInput() { return isAvailableInput; };
	bool GetIsHitWall() { return isHitWall; };

	// �߂�l��int
	int GetJumpFrameCount() { return jumpFrameCount; }

	// �߂�l��PlayerState
	PlayerState GetNowState() { return nowState; }

	//--------------state���Ń����o�[�ϐ����g�p���邽�߂�setter�Q------------------------------//
	// �����点�邩������Ȃ�
	// ������Vector3
	void SetCharaForwardVec(Vector3 _charaForwardVec) { charaForwardVec = _charaForwardVec; }
	void SetTmpCharaForwardVec(Vector3 _tmpCharaForwardVec) { charaForwardVec = _tmpCharaForwardVec; }
	void SetRotateVec(Vector3 _rotateVec) { charaForwardVec = _rotateVec; }
	void SetVelocity(Vector3 _velocity) { velocity = _velocity; }
	void SetRespownPos(Vector3 _respownPos) { velocity = _respownPos; }

	// ������float
	void SetMoveSpeed(float _moveSpeed) { moveSpeed = _moveSpeed; }

	// ������int
	void SetTurnDelayCount(bool _turnDelayCount) { turnDelayCount = _turnDelayCount; }

	// ������bool
	void SetJumpFlag(bool _jumpFlag) { jumpFlag = _jumpFlag; }
	void SetIsJumping(bool _isJumpFlag) { isJumping = _isJumpFlag; }
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

	// �萔�ł���O���r�e�B�i�d�́j�𑼂�CPP�Ō��邽�߂�getter
	static const float GetGravity() { return Gravity; }

	// �O���x�N�g����p���ăL�����N�^�[����]������֐�
	void RotateToNewForward(const Vector3& forward);


private:

	//3D���f���̕`����s���N���X
	SkeletalMeshComponent* skeltalMeshComponent;
	Mesh* mesh;
	//�����蔻����s���N���X
	BoxCollider* boxCollider;
	SphereCollider* groundChackSphereCol;

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

	//�����߂��Ɏg���v���C���[��AABB
	AABB playerBox;
	//-----------�A�j���[�V�����֌W------------//
	std::vector<const Animation*> animTypes;
	//�Đ�����A�j���[�V�����̏��
	int animState;
	//�؂�ւ�������𔻒f���邽�߂̕ϐ�
	int tmpAnimState;
	//-----------------------------------------//

	// ���͒l��dead�X�y�[�X
	const float DeadSpace;

	//�����x�̒萔
	const float movePower;
	const float airMovePower;
	// ���������
	const float decelerationForce;
	// �����x
	const float FirstMovePower;
	float moveSpeed;

	//���͂����������ǂ������肷�邽�߂̃t���O
	bool inputFlag = false;

	//�E�����x�N�g��
	Vector3 rightVec;

	//�L�����N�^�[�̑O���x�N�g��
	Vector3 charaForwardVec;

	//�L�����N�^�[����]�����邩�O���x�N�g���Ɣ�r���邽�߂̃x�N�g��
	Vector3 tmpCharaForwardVec;

	//�����ɍ��킹�ĉ�]�����邽�߂̃x�N�g��
	Vector3 rotateVec;

	// �������ꂽ�Ƃ��̃|�W�V������ۑ����邽�߂�vector3�ϐ�
	Vector3 firstPos;
	Vector3 startPos;
	Vector3 respownPos;

	// ���̃I�u�W�F�N�g���牟����Ă��鎞�̑��x
	Vector3 pushedVelocity;

	//�d��
	static const float Gravity;

	//�����W�����v�͒萔
	const float FirstJumpPower;

	// �U��Ԃ�f�B���C�p�J�E���g�ϐ�
	int turnDelayCount;

	//�W�����v��
	float jumpPower;

	//�W�����v�����ǂ����̃t���O
	bool isJumping;

	//���������W�����v�{�^�������p�\���t���O
	bool isAvailableJumpKey;

	//�W�����v�ł��邩�t���O
	bool jumpFlag;

	//�W�����v�{�^����������Ă���Ԃ̃t���[���J�E���g
	int jumpFrameCount;

	//�W�����v�X�C�b�`�����������ǂ���
	bool switchJumpFlag;

	//�ڒn�t���O
	bool onGround;

	//�����Ԃ��ǂ���
	bool runFlag;

	// ���͂��\���ǂ���
	bool isAvailableInput;

	// ���͂��Ȃ��ԃJ�E���g
	int reStartCount;

	// �_�E����Ԃ��ǂ���
	bool downFlag;

	// �_�E�����R���e�B�j���[�I����YES���I�����ꂽ���ǂ���
	bool downUpFlag;

	// �_�E�����R���e�B�j���[�I����NO���I�����ꂽ���ǂ���
	bool downOverFlag;

	// �ŏI�X�e�[�W�p�̃N���A�t���O
	static bool clearFlag;

	// �ŏI�X�e�[�W�ȊO�ł̎��̃V�[���֑J�ڂ���t���O
	static bool nextSceneFlag;

	// ��莞�Ԉȏ���͂��Ȃ������ۂɃ^�C�g���֖߂�t���O
	static bool reStartFlag;


	// ���neffect�𔭐�������ۂɎg�p����t���O
	// JumpFlag�`�F�b�N�p
	static bool chackJumpFlag;
	// isJumping�`�F�b�N�p�i�W�����v�����ǂ����j
	static bool chackIsJumping;

	// ���񂾍ۂɂ������X�|�[�������Ȃ����߂̃J�E���g
	int respawnCount;

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

	// state�v�[��
	std::vector<class PlayerObjectStateBase*> statePools;

};

