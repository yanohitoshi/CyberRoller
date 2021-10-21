#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SkeletalMeshComponent;
class Mesh;
class Animation;
class BoxCollider;
class EnemyObjectStateBase;
enum class EnemyState;

/*
@enum  MoveEnemyTag Enemy�̈ړ������𔻕ʂ���^�O
*/
enum class MoveEnemyTag
{
	NOEN_MOVE,
	LEFT_MOVE,
	RIGHT_MOVE,
};

/*
@struct  MoveEnemyData
	���E�Ɉړ�����G���ŗL�Ŏ��f�[�^�\����
*/
struct MoveEnemyData
{
	MoveEnemyTag tag;
	Vector3 direction;
	float distance;
	float speed;
};


/*
@file EnemyObjectBase.h
@brief �G�I�u�W�F�N�g�̊��N���X
*/
class EnemyObjectBase :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@brief �ʏ�̃G�l�~�[�̃R���X�g���N�^
	@param	�|�W�V����
	@param	�ė��p���邩�t���O
	@param	�I�u�W�F�N�g���ʗptag
	@param	�ǐՑΏ�
	*/
	EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag, GameObject* _trackingObject);

	/*
	@fn �R���X�g���N�^
	@brief �ړ�����G�l�~�[�̃R���X�g���N�^
	@param	�|�W�V����
	@param	�ė��p���邩�t���O
	@param	�I�u�W�F�N�g���ʗptag
	@param	�ړ����x
	@param	�ړ�����
	@param	�ړ�����
	*/
	EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag, GameObject* _trackingObject, MoveEnemyData _moveEnemyData);

	/*
	@fn �R���X�g���N�^
	@brief �ړ�����G�l�~�[�̃R���X�g���N�^
	@param	�|�W�V����
	@param	�ė��p���邩�t���O
	@param	�I�u�W�F�N�g���ʗptag
	@param	�ړ����x
	@param	�ǐՑΏ�
	*/
	EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag, float _moveSpeed, GameObject* _trackingObject);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	virtual ~EnemyObjectBase() {};

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	virtual void UpdateGameObject(float _deltaTime) {};

	/*
	@fn �߂荞�ݔ���
	*/
	virtual void FixCollision(AABB& myAABB, const AABB& pairAABB) {};


protected:

	/*
	@brief �X�e�[�g�v�[���p�}�b�v�ɃX�e�[�g�N���X��ǉ�����֐�
	@param	_state �ǉ�����X�e�[�g�N���X�̃|�C���^
	@param	_stateTag ���ƂȂ�^�O
	*/
	void AddStatePoolMap(EnemyObjectStateBase* _state, EnemyState _stateTag);

	/*
	@brief �X�e�[�g�v�[���p�}�b�v����X�e�[�g�N���X���폜����֐�
	@param	_stateTag ���ƂȂ�^�O
	*/
	void RemoveStatePoolMap(EnemyState _stateTag);

	/*
	@brief �X�e�[�g�v�[���p�}�b�v���N���A����
	*/
	void ClearStatePoolMap();

	// 3D���f���̕`����s���N���X
	SkeletalMeshComponent* skeltalMeshComponent;
	// Mesh�̓ǂݍ��݂��s���N���X
	Mesh* mesh;
	// AABB�̓����蔻����s���N���X
	BoxCollider* boxCollider;
	// �G�l�~�[��AABB�\����
	AABB enemyBox;
	// �ǐՂ���I�u�W�F�N�g�̃|�C���^
	GameObject* trackingObject;

	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
	@param	��������GameObject
	*/
	virtual void OnCollision(const GameObject& _hitObject) {};

	//�E�����x�N�g��
	Vector3 rightVec;
	//�L�����N�^�[�̑O���x�N�g��
	Vector3 charaForwardVec;
	//�����ɍ��킹�ĉ�]�����邽�߂̃x�N�g��
	Vector3 rotateVec;
	// �����ʒu
	Vector3 firstPosition;
	// �����ʒu
	Vector3 respawnPosition;
	// �ړ�����
	Vector3 moveDirection;
	// AABB�̍ŏ��l
	const Vector3 BoxMin;
	// AABB�̍ő�l
	const Vector3 BoxMax;
	// �傫��
	const Vector3 Size;


	// �����ʒu���烊�X�|�[������|�W�V�������v�Z���邽�߂̊Ԋu
	const float respawnPositionOffset;
	// ���x
	float moveSpeed;
	// �ړ�����
	float moveDistance;

	//�ڒn�t���O
	bool onGround;
	// ����ł��邩�ǂ���
	bool isDeadFlag;
	// �ǐՑ�����Ƃ炦�Ă��邩�ǂ���
	bool isTracking;
	// �U�����[�V��������
	bool isAttack;
	bool isVisible;

	// �ړ�����G��Tag
	MoveEnemyTag moveEnemyTag;

	// ����enemy��state��Ԃ�ۑ����邽�߂̕ϐ�
	EnemyState nowState;
	// �ύX���ꂽ����enemy��state��Ԃ�ۑ����邽�߂̕ϐ�
	EnemyState nextState;
	// Animation�v�[��
	std::vector<const Animation*> animTypes;
	// �Sstate���i�[�����}�b�v
	std::unordered_map<EnemyState, EnemyObjectStateBase*> statePoolMap;

private:



public:// �Q�b�^�[�Z�b�^�[

	/*
	@fn skeltalMeshComponent��getter�֐�
	@return SkeletalMeshComponent�@SkeletalMeshComponent�N���X�̃|�C���^��Ԃ�
	*/
	SkeletalMeshComponent* GetSkeletalMeshComponent() { return skeltalMeshComponent; }

	/*
	@fn trackingObject��getter�֐�
	@return trackingObject�@�ǐՂ���I�u�W�F�N�g�̃|�C���^��Ԃ�
	*/
	GameObject* GetTrackingObject(){ return trackingObject; }

	/*
	@fn Animation��getter�֐�
	@param _state ���݂̃G�l�~�[�̃X�e�[�^�X
	@return Animation Animation�N���X�̃|�C���^��Ԃ�
	*/
	const Animation* GetAnimation(EnemyState _state);

	/*
	@fn forwardVec��getter�֐�
	@return Vector3 forwardVec �O���x�N�g����Ԃ�
	*/
	Vector3 GetForwardVec() { return forwardVec; }

	/*
	@fn rightVec��getter�֐�
	@return Vector3 rightVec �E�����x�N�g����Ԃ�
	*/
	Vector3 GetRightVec() { return rightVec; }

	/*
	@fn charaForwardVec��getter�֐�
	@return charaForwardVec��Ԃ�
	*/
	Vector3 GetCharaForwardVec() { return charaForwardVec; }

	/*
	@fn rotateVec��getter�֐�
	@return Vector3 rotateVec ��]�l��Ԃ�
	*/
	Vector3 GetRotateVec() { return rotateVec; }

	/*
	@fn velocity��getter�֐�
	@return Vector3 velocity ���x��Ԃ�
	*/
	Vector3 GetVelocity() { return velocity; }

	/*
	@fn moveDirection��getter�֐�
	@return Vector3 moveDirection �ړ�������Ԃ�
	*/
	Vector3 GetMoveDirection() { return moveDirection; }

	/*
	@fn firstPosition��getter�֐�
	@return Vector3 firstPosition �����|�W�V������Ԃ�
	*/
	Vector3 GetFirstPosition() { return firstPosition; }

	/*
	@fn respawnPosition��getter�֐�
	@return Vector3 respawnPosition ���X�|�[������ꏊ��Ԃ�
	*/
	Vector3 GetRespawnPosition() { return respawnPosition; }

	/*
	@fn moveDistance��getter�֐�
	@return moveDistance��Ԃ�
	*/
	float GetMoveDistance() { return moveDistance; }

	/*
	@fn moveSpeed��getter�֐�
	@return moveSpeed��Ԃ�
	*/
	float GetMoveSpeed() { return moveSpeed; }

	/*
	@fn onGround��getter�֐�
	@return onGround��Ԃ�
	*/
	bool GetOnGround() { return onGround; }

	/*
	@fn isDeadFlag��Gettrer�֐�
	@return	bool isDeadFlag ���S��Ԃ�Ԃ�
	*/
	bool GetIsDeadFlag() { return isDeadFlag; }

	/*
	@fn isTracking��Gettrer�֐�
	@return	bool isTracking �ǐՂ���I�u�W�F�N�g�𑨂��Ă��邩��Ԃ�
	*/
	bool GetIsTracking() { return isTracking; }
	
	/*
	@fn isVisible��Gettrer�֐�
	@return	bool isVisible �\�������ǂ�����Ԃ�
	*/
	bool GetIsVisible() { return isVisible; }

	/*
	@fn nowState��getter�֐�
	@return EnemyState nowState ���݂̃X�e�[�^�X��Ԃ�
	*/
	EnemyState GetNowState() { return nowState; }

	/*
	@fn moveEnemyTag��getter�֐�
	@return MoveEnemyTag moveEnemyTag �ړ��������w��Tag��Ԃ�
	*/
	MoveEnemyTag GetMoveEnemyTag() { return moveEnemyTag; }

	/*
	@fn trackingObject��getter�֐�
	@param �ǐՂ���I�u�W�F�N�g�̃|�C���^���Z�b�g
	*/
	void SetTrackingObject(GameObject* _trackingObject) { trackingObject = _trackingObject; }

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
	@fn velocity��setter�֐�
	@param	Vector3 _moveDirection �L�����N�^�[�̈ړ������x�N�g��
	*/
	void SetMoveDirection(Vector3 _moveDirection) { moveDirection = _moveDirection; }

	/*
	@fn moveDistance��setter�֐�
	@param	float moveDistance �L�����N�^�[�̈ړ�����
	*/
	void SetMoveDistance(float _moveDistance) { moveDistance = _moveDistance; }

	/*
	@fn moveSpeed��setter�֐�
	@param	float _moveSpeed �L�����N�^�[�̃X�s�[�h
	*/
	void SetMoveSpeed(float _moveSpeed) { moveSpeed = _moveSpeed; }

	/*
	@fn isDeadFlag��setter�֐�
	@param	bool isDeadFlag ���S���
	*/
	void SetIsDeadFlag(bool _isDeadFlag) { isDeadFlag = _isDeadFlag; }

	/*
	@fn isTracking��setter�֐�
	@param	bool _isTracking �L�����N�^�[�̑O���x�N�g��
	*/
	void SetIsTracking(bool _isTracking) { isTracking = _isTracking; }

	/*
	@fn isAttack��setter�֐�
	@param	bool isAttack �U����Ԃ��ǂ���
	*/
	void SetIsAttack(bool _isAttack) { isAttack = _isAttack; }
	
	/*
	@fn isVisible��setter�֐�
	@param	bool isVisible �\�������ǂ���
	*/
	void SetIsVisible(bool _isVisible) { isVisible = _isVisible; }
};

