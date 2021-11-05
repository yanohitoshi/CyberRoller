#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include <vector>
#include <functional>
#include "Math.h"
#include "Collision.h"
#include <unordered_map>
#include "Game.h"

// �N���X�̑O���錾
class Vector3;
class Matrix4;
class Component;
struct InputState;
class ColliderComponent;
class MainCameraObject;
class PlayerObject;
enum class PhysicsTag;

/*
@brief	�Q�[���I�u�W�F�N�g�̏��
*/
enum State
{
	//�A�N�e�B�u
	Active,
	//�X�V����~���Ă���
	Paused,
	// ���������
	Disabling,
	//�I�u�W�F�N�g�̍X�V���I��(�O������̂�Active�ɕύX�\)
	Dead
};

/*
@enum�@GameObject�^�O(object���Ȃ�Ȃ̂��̔��ʂɎg�p)
*/
enum Tag
{
	// ���̑�
	OTHER,
	// �J����
	CAMERA,
	// �J�����ύX�|�C���g
	CAMERA_CHANGE_OBLIQUE,
	// �v���C���[
	PLAYER,
	// �W�����v�A�^�b�N���̃v���C���[
	JUMP_ATTACK_PLAYER,
	// �G�l�~�[
	ENEMY,
	// �v���C���[�ǐՃG���A
	PLAYER_TRACKING_AREA,
	// �O���E���h
	GROUND,
	// �����O���E���h
	MOVE_GROUND,
	// ����O���E���h
	BREAK_GROUND,
	// ��
	WALL,
	// ���e
	BOMB,
	// �����G���A
	EXPLOSION_AREA,
	// ��
	NEEDLE,
	// ���p�p�l��
	NEEDLE_PANEL,
	// �����o����
	PUSH_BOARD,
	// �����o���̃x�[�X
	PUSH_BOX,
	// �ŏ��̓�����
	FIRST_MOVE_WALL,
	// 2�Ԗڂ̓�����
	SECOND_MOVE_WALL,
	// �Q�[���N���A�O�̓�����
	CLEAR_SCENE_MOVE_WALL,
	// �ŏ��̋��̃X�C�b�`
	FIRST_SWITCH,
	// 2�Ԗڂ̋��̃X�C�b�`
	SECOND_SWITCH,
	// �Q�[���N���A�O�̃X�C�b�`
	CLEAR_SCENE_SWITCH,
	// �W�����v�X�C�b�`
	JUMP_SWITCH,
	// �X�C�b�`�̃x�[�X�I�u�W�F�N�g
	SWITCH_BASE,
	// ���W��
	COLLECTION,
	// �V�[��
	SCENE,
	// �Q�[���N���A�I�u�W�F�N�g
	CLEAR_POINT,
	// ���X�|�[���|�C���g
	RESPOWN_POINT,
	// UI
	UI,
	// �^�C�g����̃I�u�W�F�N�g
	TITLE_OBJECT,
	// �^�C�g���Ŏ����œ����v���C���[�I�u�W�F�N�g
	TITLE_PLAYER,
	// �^�C�g����̃I�u�W�F�N�g
	RESULT_OBJECT,
	// �p�[�e�B�N��
	PARTICLE,
};

/*
@enum�@���������̃^�O
*/
enum MoveDirectionTag
{
	// X������
	MOVE_X,
	// Y������
	MOVE_Y,
	// Z������
	MOVE_Z
};

/*
@file GameObject.h
@brief �Q�[���I�u�W�F�N�g�̊��N���X
*/
class GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�ė��p���邩�ǂ����̃t���O
	@param	�I�u�W�F�N�g���ʗptag
	*/
	GameObject(bool _reUseGameObject,const Tag _objectTag);

	/*
	@brief	�f�X�g���N�^
	*/
	virtual ~GameObject();

	/*
	@brief	�t���[�����̏���
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void Update(float _deltaTime);

	/*
	@brief	�A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateComponents(float _deltaTime);

	/*
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void UpdateGameObject(float _deltaTime);

	/*
	@fn ���͏�Ԃ��󂯎��GameObject��Component�̓��͍X�V�֐����Ăяo��
	@param	_keyState ���͏��
	*/
	void ProcessInput(const InputState& _keyState);

	/*
	@fn ���͂������Ŏ󂯎��X�V�֐�
	@brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
	@param	_keyState ���͏��
	*/
	virtual void GameObjectInput(const InputState& _keyState);

	/*
	@brief	�R���|�[�l���g��ǉ�����
	@param	�ǉ�����R���|�[�l���g�̃|�C���^
	*/
	void AddComponent(Component* _component);

	/*
	@brief	�R���|�[�l���g���폜����
	@param	�폜����R���|�[�l���g�̃|�C���^
	*/
	void RemoveComponent(Component* _component);

	/*
	@fn ���݂̎d�l��s�����Ƃ��ł��Ȃ��������O�����狭���ɍs�����߂̊֐�
	@exsample �Q�[���I�u�W�F�N�g�S�̂̍X�V����~���ɑΏۂ̃Q�[���I�u�W�F�N�g���X�V����
	*/
	void ExceptionUpdate();
	/*
	@brief	Transform�̃��[���h�ϊ�
	*/
	void ComputeWorldTransform();

	/*
	@fn �����߂��֐�(���z�֐�)
	@brief �����߂����s��
	@param myAABB ������AABB
	@param pairAABB �����AABB
	@param _pairTag ���肪�Ȃ�̃I�u�W�F�N�g�Ȃ̂�����p��Tag
	*/
	virtual void FixCollision(const AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag);

	/*
	@fn �I�u�W�F�N�g�̉�]���v�Z����֐�
	@brief �O���x�N�g�����g�p���ăI�u�W�F�N�g����]������
	@param forward �O���x�N�g��
	*/
	void RotateToNewForward(const Vector3& forward);

	/*
	@fn �ÓI��mainCamera�𐶐�����
	@param _pos �|�W�V����
	@param _playerObject �Ǐ]����v���C���[�̃|�C���^
	*/
	static void CreateMainCamera(const Vector3 _pos, PlayerObject* _playerObject);

	/*
	@fn �ÓI��titleCamera�𐶐�����
	@param _pos �|�W�V����
	*/
	static void CreateTitleCamera(const Vector3 _pos);

	/*
	@fn �ÓI��titleCamera�𐶐�����
	@param _pos �|�W�V����
	*/
	static void CreateResultCamera(const Vector3 _pos);

	/*
	@brief�@tag���g�p����GameObject��T�����߂̊֐�
	@return	std::vector<GameObject*>��Ԃ�
	*/
	static std::vector<GameObject*> FindGameObject(Tag _tag);

	/*
	@brief�@�g�p�����S�Ă�GameObject�̍폜
	*/
	static 	void RemoveUsedGameObject();


protected:

	std::function<void(GameObject&, PhysicsTag)> GetOnCollisionFunc() { return std::bind(&GameObject::OnCollision, this, std::placeholders::_1, std::placeholders::_2); }
	virtual void OnCollision(const GameObject& _hitObject,const PhysicsTag _physicsTag) {}

	/*
	@fn �Փ˂������Ƃ��m�肵���Ƃ��A�߂荞�݂�߂��֐�
	@param _movableBox �ړ�����
	@param _fixedBox �ړ����Ȃ�����
	@param _calcFixVec �ړ����̂̕␳�����x�N�g��
	*/
	void CalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);

	void Rotation(GameObject* _owner, const float _angle, const Vector3 _axis);

	// �Q�[�������C���J����
	static class CameraObjectBase* mainCamera;
	// �^�C�g����ʂŎg�p����J����
	static class TitleCameraObject* titleCamera;
	// �^�C�g����ʂŎg�p����J����
	static class ResultCameraObject* resultCamera;

	//�Q�[���I�u�W�F�N�g�̏��
	State state;
	//�Q�[���I�u�W�F�N�g�̃^�O
	Tag tag;
	//�Q�[���I�u�W�F�N�g��ID�A�J�E���g�p
	static int gameObjectId;

	//���̃Q�[���I�u�W�F�N�g��ID
	const int MyObjectId;

	//Transform
	Vector3 position;
	Quaternion rotation;
	Vector3 scale;
	Matrix4 worldTransform;
	Vector3 velocity;
	Vector3 forwardVec;

	// �I�u�W�F�N�g�̋P�x
	float luminance;

	// AABB
	AABB aabb;

	//���[���h�ϊ��̏������s���K�v�������邩
	bool recomputeWorldTransform;

	//switch�p�t���O
	bool onFlag;

	// �v���C���[�Ɖ����߂����s���I�u�W�F�N�g���ǂ���
	bool isPushBackToPlayer;

	// ���x���v���C���[�Ɋ֗^���邩�ǂ���
	bool isSendVelocityToPlayer;

	// �v���C���[�Ɛڒn������s�����ǂ���
	bool isCheckGroundToPlayer;

	// �J�����Ɖ����߂����s���I�u�W�F�N�g���ǂ���
	bool isPushBackToCamera;

	//�A�^�b�`����Ă���R���|�[�l���g
	std::vector<class Component*>components;

private:

	/*
	@brief�@GameObject�̒ǉ�
	@param	�ǉ�����GameObject�̃|�C���^
	*/
	static void AddGameObject(GameObject* _object);

	/*
	@brief�@GameObject�̍폜
	@param	�폜����GameObject�̃|�C���^
	*/
	static void RemoveGameObject(GameObject* _object);


	//�V�[�����ׂ��ۂɊJ�������I�u�W�F�N�g���ǂ����A�J�����Ȃǂ��ΏۂɂȂ�
	bool reUseObject;
	// �r���ǉ������ۈꎞ�I�ɕۑ������ϒ��z��
	static std::vector<GameObject*> pendingGameObjects;
	// �S�I�u�W�F�N�g���i�[�����A�z�ϒ��z��
	static std::unordered_map<Tag, std::vector<GameObject*>> gameObjectMap;
	// GameObject�̍X�V�t���O
	static bool updatingGameObject;

	/*
	@brief  �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g����
	*/
	friend void UpdateGameObjects(float _deltaTime);

	/*
	@brief  �Q�[���I�u�W�F�N�g�̓��͏���
	*/
	friend void ProcessInputs(const InputState & _state);
	
public://�Q�b�^�[�Z�b�^�[

	/*
	@brief�@�I�u�W�F�N�g�̃|�W�V�������擾����
	@return	position
	*/
	const Vector3& GetPosition() const { return position; }

	/*
	@brief�@�I�u�W�F�N�g�̃|�W�V������ݒ肷��
	@param	position
	*/
	virtual void SetPosition(const Vector3& _pos) { position = _pos; recomputeWorldTransform = true; }

	/*
	@brief�@���[���h���W�̍ĕϊ��t���O��getter
	@return	recomputeWorldTransform
	*/
	bool GetRecomputeWorldTransform() { return recomputeWorldTransform; }

	/*
	@brief�@�I�u�W�F�N�g�̃X�P�[�����擾����
	@return	scale
	*/
	Vector3 GetScaleFloat() const { return scale; }

	/*
	@brief�@�I�u�W�F�N�g�̃X�P�[����ݒ肷��(x.y.z�̔䗦�������Ƃ�)
	@param	scale float�^
	*/
	void SetScale(float _scale) { scale.x = _scale; scale.y = _scale; scale.z = _scale; recomputeWorldTransform = true; }

	/*
	@brief�@�I�u�W�F�N�g�̃X�P�[����ݒ肷��(x���݂̂̏ꍇ)
	@param	scale float�^
	*/
	void SetScaleX(float _scale) { scale.x = _scale; recomputeWorldTransform = true; }

	/*
	@brief�@�I�u�W�F�N�g�̃X�P�[����ݒ肷��(y���݂̂̏ꍇ)
	@param	scale float�^
	*/
	void SetScaleY(float _scale) { scale.y = _scale; recomputeWorldTransform = true; }

	/*
	@brief�@�I�u�W�F�N�g�̃X�P�[����ݒ肷��(z���݂̂̏ꍇ)
	@param	scale float�^
	*/
	void SetScaleZ(float _scale) { scale.z = _scale; recomputeWorldTransform = true; }

	/*
	@brief�@�I�u�W�F�N�g�̃X�P�[����ݒ肷��(x.y.z�̔䗦���Ⴄ�Ƃ�)
	@param	scale Vector3�^
	*/
	void SetScale(Vector3 _scale) { scale.x = _scale.x; scale.y = _scale.y; scale.z = _scale.z; recomputeWorldTransform = true; }

	/*
	@brief�@�I�u�W�F�N�g�̃X�P�[�����擾(x.y.z�̔䗦�������Ƃ�)
	@return	scale Vector3�^
	*/
	float GetScale() { return scale.x; }

	/*
	@brief�@�I�u�W�F�N�g�̃X�P�[�����擾����(x.y.z�̔䗦���Ⴄ�Ƃ�)
	@return	scale Vector3�^
	*/
	Vector3 GetScaleVec() { return scale; }

	/*
	@brief�@�I�u�W�F�N�g�̋P�x���擾
	@return	luminance �P�x
	*/
	float GetLuminance() { return luminance; }

	/*
	@brief�@�I�u�W�F�N�g�̃N�H�[�^�j�I�����擾����
	@return	rotation�iQuaternion�^�j
	*/
	const Quaternion& GetRotation() const { return rotation; }

	/*
	@brief�@�I�u�W�F�N�g�̃N�H�[�^�j�I����ݒ肷��
	@param	rotation�iQuaternion�^�j
	*/
	virtual void SetRotation(const Quaternion& _qotation) { rotation = _qotation;  recomputeWorldTransform = true; }

	/*
	@brief�@�I�u�W�F�N�g�̏�Ԃ��擾����
	@return	state
	*/
	State GetState() const { return state; }

	/*
	@brief�@�I�u�W�F�N�g�̏�Ԃ�ݒ肷��
	@param	state
	*/
	virtual void SetState(State _state) { state = _state; }

	/*
	@brief�@�I�u�W�F�N�g�̃��[���h�s����擾����
	@return	worldTransform
	*/
	const Matrix4& GetWorldTransform() const { return worldTransform; }

	/*
	@brief�@�I�u�W�F�N�g�̑O����\���x�N�g�����擾����
	@param	forward(Vector3�^)
	*/
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, rotation); }

	/*
	@brief�@�I�u�W�F�N�g�̉E��\���x�N�g�����擾����
	@param	right(Vector3�^)
	*/
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, rotation); }

	/*
	@brief�@�I�u�W�F�N�g�̏��\���x�N�g�����擾����
	@param	up(Vector3�^)
	*/
	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitZ, rotation); }

	/*
	@brief�@�I�u�W�F�N�g�̏��\���x�N�g�����擾����
	@param	up(Vector3�^)
	*/
	Vector3 GetForwardVec() const { return forwardVec; }

	/*
	@fn Tag��getter�֐�
	@brief �I�u�W�F�N�g�����ʂ���Tag���擾
	@return Tag �I�u�W�F�N�g�����ʂ���Tag
	*/
	Tag GetTag() const { return tag; }

	/*
	@fn aabb��getter�֐�
	@brief �I�u�W�F�N�g�̃��[���h��Ԃł�AABB�̎擾
	@return aabb �I�u�W�F�N�g���ꂼ��Ń��[���h��Ԃł�AABB�̒l��ۑ����Ă���ϐ�
	*/
	AABB GetAabb() const { return aabb; }

	/*
	@fn myObjectId�ϐ���getter�֐�
	@brief ���ꂼ��̃I�u�W�F�N�g������ID�̎擾
	@return int myObjectId ���ꂼ��̃I�u�W�F�N�g������ID
	*/
	int GetObjectId() const { return MyObjectId; };

	/*
	@fn gameObjectId�ϐ���getter�֐�
	@brief �S�I�u�W�F�N�g�������m�F���邽�߂̃g�[�^��ID�̎擾
	@return int gameObjectId �I�u�W�F�N�g����������邽�т�1������ID
	*/
	static int GetTotalObjectId() { return gameObjectId; };

	/*
	@fn reUseObject�ϐ���getter�֐�
	@brief �V�[�����܂����ŗ��p���邩�ǂ����t���O�̎擾
	@return bool reUseObject �V�[�����܂����ŗ��p���邩�ǂ����t���O
	*/
	bool GetReUseGameObject() { return reUseObject; }

	/*
	@brief�@�v���C���[�Ɖ����߂�������s�����t���O��getter
	@return	isPushBackToPlayer
	*/
	bool GetisPushBackToPlayer() const { return isPushBackToPlayer; }

	/*
	@brief�@�v���C���[�ɑ��x�𑗂�I�u�W�F�N�g���ǂ����t���O��getter
	@return	isSendVelocityToPlayer
	*/
	bool GetisSendVelocityToPlayer() const { return isSendVelocityToPlayer; }

	/*
	@brief�@�v���C���[�Ɖ����߂�������s�����t���O��getter
	@return	isCheckGroundToPlayer
	*/
	bool GetIsCheckGroundToPlayer() const { return isCheckGroundToPlayer; }

	/*
	@brief�@�J�����Ɖ����߂�������s�����t���O��getter
	@return	isPushBackToPlayer
	*/
	bool GetisPushBackToCamera() const { return isPushBackToCamera; }

	/*
	@brief�@�X�C�b�`�p�t���O��getter
	@return	onFlag
	*/
	bool GetSwitchFlag() { return onFlag; }

	/*
	@brief�@Velocity��gettta�֐�
	@param	velocity(Vector3�^)
	*/
	const Vector3& GetVelocity() const { return velocity; }

	/*
	@brief�@���C���J������getter
	@return	MainCameraObject*�@���C���J������Ԃ�
	*/
	static CameraObjectBase* GetMainCamera() { return mainCamera; }
};

