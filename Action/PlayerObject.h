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
class JumpAttackPlayerObject;
class PlayerObjectStateBase;
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
	@param	_keyState ���͏��
	*/
	void GameObjectInput(const InputState& _keyState)override;
	
	/*
	@fn �߂荞�ݔ���Ɖ����߂�
	@param	myAABB ������AABB
	@param	pairAABB �������������AABB
	@param	_hitObjectTag �q�b�g�����I�u�W�F�N�g�̃^�O
	*/
	void FixCollision(AABB& myAABB, const AABB& pairAABB,Tag _hitObjectTag);
	
	/*
	@fn �����߂�����
	@brief	x,y,z���ŉ����߂��������s��
	@param	_movableBox �ړ��I�u�W�F�N�g��AABB
	@param	_fixedBox ���������I�u�W�F�N�g��AABB
	@param	_calcFixVec ���x�����x�N�g��
	*/
	void PlayerCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox,Vector3& _calcFixVec);

	/*
	@fn �����߂�����
	@brief	x,y���ŉ����߂��������s��
	@param	_movableBox �ړ��I�u�W�F�N�g��AABB
	@param	_fixedBox ���������I�u�W�F�N�g��AABB
	@param	_calcFixVec ���x�����x�N�g��
	*/
	void HorizontalPlayerCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);
	
	/*
	@brief �O���x�N�g����p���ăL�����N�^�[����]������֐�
	@param	forward �O���x�N�g��
	*/
	void RotateToNewForward(const Vector3& forward);



private:

	/*
	@fn �N���A���Ă����Ԃ����`�F�b�N����֐�
	@param	_tag �`�F�b�N����I�u�W�F�N�g�̃^�O
	*/
	void ClearCheck(Tag _tag);
	
	/*
	@fn �N���A�ɕK�v�ȃX�C�b�`���`�F�b�N����֐�
	@param	_checkVector �`�F�b�N����X�C�b�`���i�[����Ă���ϒ��R���e�i
	*/
	void SwitchCheckProcess(std::vector<GameObject*> _checkVector);

	/*
	@fn �X�C�b�`�W�����v���g�p�\�ɂ���֐�
	*/
	void ActiveSwitchJumpProcess();

	/*
	@fn ���X�^�[�g�`�F�b�N�֐�
	*/
	void CheckRestartProcess();

	/*
	@brief	�U���Ώۂ̓G��T��
	@param	_hitObject �q�b�g�����I�u�W�F�N�g
	@return GameObject* �T���o�����I�u�W�F�N�g
	*/
	GameObject* FindTargetObject(const GameObject& _hitObject);

	// 3D���f���̕`����s���N���X
	SkeletalMeshComponent* skeltalMeshComponent;
	// Mesh�̓ǂݍ��݂��s���N���X
	Mesh* mesh;
	// AABB�̓����蔻����s���N���X
	BoxCollider* boxCollider;
	// ���̂̓����蔻����s���N���X
	SphereCollider* groundCheckSphereCol;
	// ���̂̓����蔻����s���N���X
	SphereCollider* jumpAttackSphereCol;

	// �W�����v�U�����̃v���C���[�������߂̃|�C���^�ϐ�
	JumpAttackPlayerObject* jumpAttackPlayerObject;

	// @�I�����Ă���G�������邽�߂̉ϒ��z��
	std::vector<GameObject*> selectEnemy;

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	@param	��������GameObject�̓����蔻��^�O
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	/*
	@fn ��������p�����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	@param	��������GameObject�̓����蔻��^�O
	*/
	void OnCollisionGround(const GameObject& _hitObject, const PhysicsTag _physicsTag);

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�(�W�����v�U�����s���G�l�~�[�Ƃ̔�������)
	@param	��������GameObject
	@param	��������GameObject�̓����蔻��^�O
	*/
	void OnCollisionAttackTarget(const GameObject& _hitObject, const PhysicsTag _physicsTag);

	/*
	@brief �X�e�[�g�v�[���p�}�b�v�ɃX�e�[�g�N���X��ǉ�����֐�
	@param	_state �ǉ�����X�e�[�g�N���X�̃|�C���^
	@param	_stateTag ���ƂȂ�^�O
	*/
	void AddStatePoolMap(PlayerObjectStateBase* _state, PlayerState _stateTag);

	/*
	@brief �X�e�[�g�v�[���p�}�b�v����X�e�[�g�N���X���폜����֐�
	@param	_stateTag ���ƂȂ�^�O
	*/
	void RemoveStatePoolMap(PlayerState _stateTag);

	/*
	@brief �X�e�[�g�v�[���p�}�b�v���N���A����
	*/
	void ClearStatePoolMap();

	//�d��
	static const float Gravity;

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
	// �󒆈ړ����̏����x
	const float FirstAirMovePower;
	//�����W�����v�͒萔
	const float FirstJumpPower;
	// �v���C���[�������������ǂ����𔻒肷��ʒu
	//�i������X�e�[�W�ɗ������Ȃ��̂ł������蔲���Ă��܂����ꍇ�j
	const float FallPpsitionZ;
	// ���������Ƃ��̃|�W�V���������炷
	const float FirstPositionZ;

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
	// �W�����v�A�^�b�N���łȂ��Ƃ��Ƀq�b�g�����G�̃|�W�V����
	Vector3 hitKnockBackObjectPosition;

	// �W�����v�U���Ώۂ̓G�̃|�C���^
	GameObject* attackTarget;

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

	// �ŏI�X�e�[�W�p�̃N���A�t���O
	bool clearFlag;
	// �ŏI�X�e�[�W�ȊO�ł̎��̃V�[���֑J�ڂ���t���O
	bool nextSceneFlag;
	// ��莞�Ԉȏ���͂��Ȃ������ۂɃ^�C�g���֖߂�t���O
	bool restartFlag;
	//���͂����������ǂ������肷�邽�߂̃t���O
	bool inputFlag;
	//���������W�����v�{�^�������p�\���t���O
	bool isAvailableJumpKey;

	// �W�����v�A�^�b�N�����p�\���t���O
	bool isAvailableJumpAttck;
	// �W�����v�A�^�b�N�t���O
	bool isJumpAttck;
	// �W�����v�A�^�b�N����I�u�W�F�N�g�̑I���t���O
	bool isSelectingTargetObject;
	// �W�����v�A�^�b�N����������
	bool isJumpAttackSuccess;
	// �W�����v�U�����L�����Z�����ꂽ��
	bool isJumpAttackCancel;

	//�W�����v�ł��邩�t���O
	bool jumpFlag;
	//�W�����v�X�C�b�`�����������ǂ���
	bool switchJumpFlag;
	//�ڒn�t���O
	bool onGround;
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
	// �G�Ƀq�b�g������
	bool isHitEnemy;
	// �_���X��Ԃ�
	bool isDancing;
	// �����ɓ���������
	bool isHitExplosion;
	
	// ���̃v���[���[��state��Ԃ�ۑ����邽�߂̕ϐ�
	PlayerState nowState;
	// �ύX���ꂽ���̃v���[���[��state��Ԃ�ۑ����邽�߂̕ϐ�
	PlayerState nextState;

	// Animation�v�[��
	std::vector<const Animation*> animTypes;

	// �Sstate���i�[�����}�b�v
	std::unordered_map<PlayerState, PlayerObjectStateBase*> statePoolMap;
	
public:// �Q�b�^�[�Z�b�^�[

	/*
	@fn skeltalMeshComponent��getter�֐�
	@return SkeletalMeshComponent�@SkeletalMeshComponent�N���X�̃|�C���^��Ԃ�
	*/
	SkeletalMeshComponent* GetSkeletalMeshComponent() { return skeltalMeshComponent; }

	/*
	@fn Animation��getter�֐�
	@param _state ���݂̃v���C���[�̃X�e�[�^�X
	@return Animation Animation�N���X�̃|�C���^��Ԃ�
	*/
	const Animation* GetAnimation(PlayerState _state);

	/*
	@fn �d�͂�getter�֐�
	@return Gravity �d�͒萔
	*/
	static const float GetGravity() { return Gravity; }

	/*
	@fn forwardVec��getter�֐�
	@return forwardVec��Ԃ�
	*/
	Vector3 GetForwardVec() { return forwardVec; }
	
	/*
	@fn rightVec��getter�֐�
	@return rightVec��Ԃ�
	*/
	Vector3 GetRightVec() { return rightVec; }
	
	/*
	@fn charaForwardVec��getter�֐�
	@return charaForwardVec��Ԃ�
	*/
	Vector3 GetCharaForwardVec() { return charaForwardVec; }
	
	/*
	@fn rotateVec��getter�֐�
	@return rotateVec��Ԃ�
	*/
	Vector3 GetRotateVec() { return rotateVec; }
	
	/*
	@fn velocity��getter�֐�
	@return velocity��Ԃ�
	*/
	Vector3 GetVelocity() { return velocity; }
	
	/*
	@fn respownPos��getter�֐�
	@return respownPos��Ԃ�
	*/
	Vector3 GetRespownPos() { return respownPos; }

	/*
	@fn hitKnockBackObjectPosition��getter�֐�
	@return hitKnockBackObjectPosition��Ԃ�
	*/
	Vector3 GetHitKnockBackObjectPosition() { return hitKnockBackObjectPosition; }

	/*
	@fn hitEnemyPosition��getter�֐�
	@return respownPos��Ԃ�
	*/
	GameObject* GetAttackTargetEnemy() { return attackTarget; }

	/*
	@fn DeadSpace��getter�֐�
	@return DeadSpace��Ԃ�
	*/
	const float GetDeadSpace() { return DeadSpace; }
	
	/*
	@fn FirstMovePower��getter�֐�
	@return FirstMovePower��Ԃ�
	*/
	const float GetFirstMovePower() { return FirstMovePower; }

	/*
	@fn FirstAirMovePower��getter�֐�
	@return FirstAirMovePower��Ԃ�
	*/
	const float GetFirstAirMovePower() { return FirstAirMovePower; }
	
	/*
	@fn MovePower��getter�֐�
	@return MovePower��Ԃ�
	*/
	const float GetMovePower() { return MovePower; }
	
	/*
	@fn AirMovePower��getter�֐�
	@return AirMovePower��Ԃ�
	*/
	const float GetAirMovePower() { return AirMovePower; }
	
	/*
	@fn FirstJumpPower��getter�֐�
	@return FirstJumpPower��Ԃ�
	*/
	const float GetFirstJumpPower() { return FirstJumpPower; }
	
	/*
	@fn DecelerationForce��getter�֐�
	@return DecelerationForce��Ԃ�
	*/
	const float GetDecelerationForce() { return DecelerationForce; }

	/*
	@fn moveSpeed��getter�֐�
	@return moveSpeed��Ԃ�
	*/
	float GetMoveSpeed() { return moveSpeed; }
	
	/*
	@fn jumpPower��getter�֐�
	@return jumpPower��Ԃ�
	*/
	float GetJumpPower() { return jumpPower; }

	/*
	@fn turnDelayCount��getter�֐�
	@return turnDelayCount��Ԃ�
	*/	
	int GetTurnDelayCount() { return turnDelayCount; }

	/*
	@fn onGround��getter�֐�
	@return onGround��Ԃ�
	*/
	bool GetOnGround() { return onGround; }
	
	/*
	@fn jumpFlag��getter�֐�
	@return jumpFlag��Ԃ�
	*/
	bool GetJumpFlag() { return jumpFlag; }
	
	/*
	@fn switchJumpFlag��getter�֐�
	@return switchJumpFlag��Ԃ�
	*/
	bool GetSwitchJumpFlag() { return switchJumpFlag; }
	
	/*
	@fn isAvailableJumpKey��getter�֐�
	@return isAvailableJumpKey��Ԃ�
	*/
	bool GetIsAvailableJumpKey() { return isAvailableJumpKey; }
	
	/*
	@fn inputFlag��getter�֐�
	@return inputFlag��Ԃ�
	*/
	bool GetInputFlag() { return inputFlag; }
		
	/*
	@fn deadFlag��getter�֐�
	@return deadFlag��Ԃ�
	*/
	bool GetDeadFlag() { return deadFlag; }
	
	/*
	@fn respawnFlag��getter�֐�
	@return respawnFlag��Ԃ�
	*/
	bool GetRespawnFlag() { return respawnFlag; }
	
	/*
	@fn isAvailableInput��getter�֐�
	@return isAvailableInput��Ԃ�
	*/
	bool GetIsAvailableInput() { return isAvailableInput; }
	
	/*
	@fn isAvailableJumpAttck��getter�֐�
	@return isAvailableJumpKey��Ԃ�
	*/
	bool GetIsAvailableJumpAttck() { return isAvailableJumpAttck; }

	/*
	@fn isJumpAttck��getter�֐�
	@return isAvailableInput��Ԃ�
	*/
	bool GetIsJumpAttck() { return isJumpAttck; }
	
	/*
	@fn isJumpAttck��getter�֐�
	@return isAvailableInput��Ԃ�
	*/
	bool GetIsSelectingTargetObject() { return isSelectingTargetObject; }
	
	/*
	@fn isJumpAttackSuccess��getter�֐�
	@return isAvailableInput��Ԃ�
	*/
	bool GetIsJumpAttackSuccess() { return isJumpAttackSuccess; }

	/*
	@fn isJumpAttackCancel��getter�֐�
	@return isJumpAttackCancel��Ԃ�
	*/
	bool GetIsJumpAttackCancel() { return isJumpAttackCancel; }

	/*
	@fn isHitWall��getter�֐�
	@return isHitWall��Ԃ�
	*/
	bool GetIsHitEnemy() { return isHitEnemy; }

	/*
	@fn clearFlag��getter�֐�
	@return clearFlag��Ԃ�
	*/
	bool GetClearFlag() { return clearFlag; }
	
	/*
	@fn nextSceneFlag��getter�֐�
	@return nextSceneFlag��Ԃ�
	*/
	bool GetNextSceneFlag() { return nextSceneFlag; }

	/*
	@fn restartFlag��getter�֐�
	@return restartFlag��Ԃ�
	*/
	bool GetRestartFlag() { return restartFlag; }

	/*
	@fn isDancing��getter�֐�
	@return isDancing��Ԃ�
	*/
	bool GetIsDancing() { return isDancing; }

	/*
	@fn isDancing��getter�֐�
	@return isDancing��Ԃ�
	*/
	bool GetIsHitExplosion() { return isHitExplosion; }

	/*
	@fn jumpFrameCount��getter�֐�
	@return jumpFrameCount��Ԃ�
	*/
	int GetJumpFrameCount() { return jumpFrameCount; }

	/*
	@fn nowState��getter�֐�
	@return nowState��Ԃ�
	*/
	PlayerState GetNowState() { return nowState; }

	/*
	@fn AttackTargetObject��setter�֐�
	@param	GameObject* _target �W�����v�U���̑ΏۂƂȂ�I�u�W�F�N�g�̃|�C���^
	*/
	void SetAttackTargetObject(GameObject* _target) { attackTarget = _target; }

	/*
	@fn nextState��setter�֐�
	@param	PlayerState _nextState �v���C���[�̎��̃X�e�[�^�X
	*/
	void SetNextState(PlayerState _nextState) { nextState = _nextState; }

	/*
	@fn charaForwardVec��setter�֐�
	@param	Vector3 _charaForwardVec �L�����N�^�[�̑O���x�N�g��
	*/
	void SetCharaForwardVec(Vector3 _charaForwardVec) { charaForwardVec = _charaForwardVec; }
	
	/*
	@fn velocity��setter�֐�
	@param	Vector3 _velocity �L�����N�^�[�̑��x�x�N�g��
	*/
	void SetVelocity(Vector3 _velocity) { velocity = _velocity; }
	
	/*
	@fn respownPos��setter�֐�
	@param	Vector3 _respownPos �L�����N�^�[�̃��X�|�[������|�W�V����
	*/
	void SetRespownPos(Vector3 _respownPos) { respownPos = _respownPos; }

	/*
	@fn moveSpeed��setter�֐�
	@param	float _moveSpeed �L�����N�^�[�̃X�s�[�h
	*/
	void SetMoveSpeed(float _moveSpeed) { moveSpeed = _moveSpeed; }

	/*
	@fn jumpPower��setter�֐�
	@param	float _jumpPower �L�����N�^�[�̃W�����v��
	*/
	void SetJumpPower(float _jumpPower) { jumpPower = _jumpPower; }

	/*
	@fn turnDelayCount��setter�֐�
	@param	int _turnDelayCount �L�����N�^�[�̐U��Ԃ�f�B���C�J�E���g
	*/
	void SetTurnDelayCount(int _turnDelayCount) { turnDelayCount = _turnDelayCount; }

	/*
	@fn jumpFlag��setter�֐�
	@param	bool _jumpFlag �W�����v�\���̏�Ԃ��Z�b�g
	*/
	void SetJumpFlag(bool _jumpFlag) { jumpFlag = _jumpFlag; }
	
	/*
	@fn switchJumpFlag��setter�֐�
	@param	bool _switchJumpFlag �X�C�b�`�W�����v��Ԃ̃Z�b�g
	*/
	void SetSwitchJumpFlag(bool _switchJumpFlag) { switchJumpFlag = _switchJumpFlag; }
	
	/*
	@fn isAvailableJumpKey��setter�֐�
	@param	bool _isAvailableJumpKey �W�����v���p�\���̏�Ԃ��Z�b�g
	*/
	void SetIsAvailableJumpKey(bool _isAvailableJumpKey) { isAvailableJumpKey = _isAvailableJumpKey; }
	
	/*
	@fn inputFlag��setter�֐�
	@param	bool _inputFlag ���͂���Ă��邩���Z�b�g
	*/
	void SetInputFlag(bool _inputFlag) { inputFlag = _inputFlag; }
		
	/*
	@fn jumpFrameCount��setter�֐�
	@param	bool _jumpFrameCount �W�����v���̃J�E���g���Z�b�g
	*/
	void SetJumpFrameCount(bool _jumpFrameCount) { jumpFrameCount = _jumpFrameCount; }
	
	/*
	@fn deadFlag��setter�֐�
	@param	bool _deadFlag ���S��Ԃ��ǂ������Z�b�g
	*/
	void SetDeadFlag(bool _deadFlag) { deadFlag = _deadFlag; }
	
	/*
	@fn respawnFlag��setter�֐�
	@param	bool _respawnFlag ���X�|�[���t���O���Z�b�g
	*/
	void SetRespawnFlag(bool _respawnFlag) { respawnFlag = _respawnFlag; }
	
	/*
	@fn isAvailableInput��setter�֐�
	@param	bool _isAvailableInput ���͉\���ǂ������Z�b�g
	*/
	void SetIsAvailableInput(bool _isAvailableInput) { isAvailableInput = _isAvailableInput; }

	/*
	@fn isAvailableJumpAttck��setter�֐�
	@param	bool _isAvailableJumpAttck ���͉\���ǂ������Z�b�g
	*/
	void SetIsAvailableJumpAttck(bool _isAvailableJumpAttck) { isAvailableJumpAttck = _isAvailableJumpAttck; }

	/*
	@fn isJumpAttck��setter�֐�
	@param	bool _isAvailableInput ���͉\���ǂ������Z�b�g
	*/
	void SetIsJumpAttck(bool _isJumpAttck) { isJumpAttck = _isJumpAttck; }
	
	/*
	@fn isJumpAttck��setter�֐�
	@param	bool _isAvailableInput ���͉\���ǂ������Z�b�g
	*/
	void SetIsSelectingTargetObject(bool _isSelectingTargetEnemy) { isSelectingTargetObject = _isSelectingTargetEnemy; }
	
	/*
	@fn isJumpAttackSuccess��setter�֐�
	@param	bool _isJumpAttackSuccess �W�����v�U���������������ǂ������Z�b�g
	*/
	void SetIsJumpAttackSuccess(bool _isJumpAttackSuccess) { isJumpAttackSuccess = _isJumpAttackSuccess; }

	/*
	@fn isJumpAttackCancel��setter�֐�
	@param	bool _isJumpAttackCancel ���͉\���ǂ������Z�b�g
	*/
	void SetIsJumpAttackCancel(bool _isJumpAttackCancel) { isJumpAttackCancel = _isJumpAttackCancel; }

	/*
	@fn isHitEnemy��setter�֐�
	@param	bool _isHitEnemy ���݃��[�V�������s���G�Ƀq�b�g�������ǂ������Z�b�g
	*/
	void SetIsHitEnemy(bool _isHitEnemy) { isHitEnemy = _isHitEnemy; }

	/*
	@fn isHitExplosion��setter�֐�
	@param	bool _isHitWall ���e�̔����Ƀq�b�g���Ă��邩
	*/
	void SetIsHitExplosion(bool _isHitExplosion) { isHitExplosion = _isHitExplosion; }

	/*
	@fn isDancing��setter�֐�
	@param	bool isDancing �_���X���Ă��邩�ǂ���
	*/
	void SetIsDancing(bool _isDancing) { isDancing = _isDancing; }

};