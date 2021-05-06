#include "Game.h"
#include "Math.h"
#include "GameObject.h"
#include "Component.h"
#include "InputSystem.h"
#include "PhysicsWorld.h"
#include "MainCameraObject.h"
#include "TitleCameraObject.h"
#include "CameraObjectBase.h"

int GameObject::gameObjectId = 0;
MainCameraObject* GameObject::mainCamera = nullptr;
TitleCameraObject* GameObject::titleCamera = nullptr;

//PauzingEvent GameObject::pauzingEvent = PauzingEvent::NoneEvent;

std::vector<GameObject*> GameObject::pendingGameObjects;
std::unordered_map<Tag, std::vector<GameObject*>> GameObject::gameObjectMap;
bool GameObject::updatingGameObject = false;


/*
@param	�Q�[���N���X�̃|�C���^
*/
GameObject::GameObject(bool _reUseGameObject,const Tag _objectTag)
	: state(Active)
	, worldTransform()
	, position(Vector3::Zero)
	, scale(Vector3(1.0f, 1.0f, 1.0f))
	, rotation(Quaternion::Identity)
	, recomputeWorldTransform(true)
	, myObjectId(gameObjectId)
	, tag(_objectTag)
	, reUseObject(_reUseGameObject)
	,aabb({ Vector3::Zero,Vector3::Zero })
{
	//ID�ɐ��l��1�ǉ�
	++gameObjectId;

	//GameObjectManager�Ƀ|�C���^��n��
	AddGameObject(this);

}

GameObject::~GameObject()
{
	//GameObjectManager����|�C���^���폜����
	RemoveGameObject(this);
	while (!components.empty())
	{
		delete components.back();
	}
	// �����ꂽ�^�C�~���O�ŃI�u�W�F�N�gID�̑��������炷
	gameObjectId--;
}

/*
@brief	�t���[�����̏���
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::Update(float _deltaTime)
{
	//�X�V��Ԃ��A�N�e�B�u
	if (state == Active)
	{
		//Transform�̃��[���h�ϊ�
		ComputeWorldTransform();
		//�Q�[���I�u�W�F�N�g�̍X�V
		UpdateGameObject(_deltaTime);
		//���̃Q�[���I�u�W�F�N�g�ɕt������R���|�[�l���g�̍X�V
		UpdateComponents(_deltaTime);
		//Transform�̃��[���h�ϊ�
		ComputeWorldTransform();
	}
	else
	{
		//PausingUpdateGameObject();
		UpdateComponents(_deltaTime);
	}
}

/*
@brief	�A�^�b�`����Ă�R���|�[�l���g�̃A�b�v�f�[�g
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::UpdateComponents(float _deltaTime)
{
	// Dead�łȂ�������X�V�������s��
	if (state != State::Dead)
	{	
		for (auto itr : components)
		{
			itr->Update(_deltaTime);
		}
	}

}
/*
@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
@param	�Ō�̃t���[������������̂ɗv��������
*/
void GameObject::UpdateGameObject(float _deltaTime)
{
}

/*
@fn ���͏�Ԃ��󂯎��GameObject��Component�̓��͍X�V�֐����Ăяo��
*/
void GameObject::ProcessInput(const InputState& _keyState)
{
	//�R���|�[�l���g�̓��͊֐��ɃR���g���[���[�̓��͏�Ԃ�
	for (auto comp : components)
	{
		comp->ProcessInput(_keyState);
	}
	//�Q�[���I�u�W�F�N�g�̓��͊֐��ɃR���g���[���[�̓��͏�Ԃ�
	GameObjectInput(_keyState);
}

/*
@fn ���͂������Ŏ󂯎��X�V�֐�
@brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
*/
void GameObject::GameObjectInput(const InputState & _keyState)
{
}

/*
@brief	�R���|�[�l���g��ǉ�����
@param	�ǉ�����R���|�[�l���g�̃|�C���^
*/
void GameObject::AddComponent(Component * _component)
{
	// �X�V���l�����R���|�[�l���g��z��ɒǉ�
	int order = _component->GetUpdateOder();
	auto itr = components.begin();
	for (;
		itr != components.end();
		++itr)
	{
		if (order < (*itr)->GetUpdateOder())
		{
			break;
		}
	}
	components.insert(itr, _component);
}

/*
@brief	�R���|�[�l���g���폜����
@param	�폜����R���|�[�l���g�̃|�C���^
*/
void GameObject::RemoveComponent(Component * _component)
{
	// �폜����R���|�[�l���g��T���č폜
	auto itr = std::find(components.begin(), components.end(), _component);
	if (itr != components.end())
	{
		components.erase(itr);
	}
}
/*
@fn ���݂̎d�l��s�����Ƃ��ł��Ȃ��������O�����狭���ɍs�����߂̊֐�
@exsample �Q�[���I�u�W�F�N�g�S�̂̍X�V����~���ɑΏۂ̃Q�[���I�u�W�F�N�g���X�V����
*/
void GameObject::ExceptionUpdate()
{
	ComputeWorldTransform();

	UpdateGameObject(0.016f);
	UpdateComponents(0.016f);

	ComputeWorldTransform();
}


/*
@brief	Transform�̃��[���h�ϊ�
*/
void GameObject::ComputeWorldTransform()
{
	// ���[���h���W��ϊ�����K�v������ۍX�V��������
	if (recomputeWorldTransform)
	{
		// �t���O�����낵Scale�Erotation�Eposition���X�V
		recomputeWorldTransform = false;
		worldTransform = Matrix4::CreateScale(scale);
		worldTransform *= Matrix4::CreateFromQuaternion(rotation);
		worldTransform *= Matrix4::CreateTranslation(position);

		// �R���|�[�l���g�ɂ��X�V������ꍇ�X�V������
		for (auto itr : components)
		{
			itr->OnUpdateWorldTransform();
		}
	}
}

void GameObject::FixCollision(const AABB & myAABB, const AABB & pairAABB, const Tag& _pairTag)
{
	Vector3 ment = Vector3(0, 0, 0);
	calcCollisionFixVec(myAABB, pairAABB, ment);
	SetPosition(GetPosition() + (ment));
}

void GameObject::CreateMainCamera(const Vector3 _pos, PlayerObject* _playerObject)
{
	mainCamera = new MainCameraObject(_pos,_playerObject);
}

void GameObject::CreateTitleCamera(const Vector3 _pos)
{
	titleCamera = new TitleCameraObject(_pos);
}

std::vector<GameObject*> GameObject::FindGameObject(Tag _tag)
{
	// Map����K�v�ȃI�u�W�F�N�g�z���T���ĕԂ�
	return gameObjectMap.find(_tag)->second;
}


void GameObject::AddGameObject(GameObject* _object)
{
	// �r���Œǉ����ꂽ�I�u�W�F�N�g����x�ꎞ�ǉ��p�z��ɒǉ�
	if (updatingGameObject)
	{
		pendingGameObjects.emplace_back(_object);
	}
	else
	{
		// �r���ǉ��łȂ��ꍇ�ŏ��ɂ��ꂼ��̔z��ɒǉ�
		auto gameObjects = gameObjectMap.find(_object->GetTag());
		if (gameObjects != gameObjectMap.end())
		{
			gameObjects->second.emplace_back(_object);
		}
		else
		{
			std::vector<GameObject*> tmpVector;
			tmpVector.emplace_back(_object);
			gameObjectMap[_object->GetTag()] = tmpVector;
		}
	}
}

void GameObject::RemoveGameObject(GameObject* _object)
{
	// �r���ǉ��p�z��ɑΏۂ̃I�u�W�F�N�g���������ꍇ�폜����
	auto itr = std::find(pendingGameObjects.begin(), pendingGameObjects.end(), _object);
	if (itr != pendingGameObjects.end())
	{
		std::iter_swap(itr, pendingGameObjects.end() - 1);
		pendingGameObjects.pop_back();
	}

	// �S�̂�gameObject�z��ɑΏۂ̃I�u�W�F�N�g���������ꍇ�폜����
	auto gameObjects = gameObjectMap.find(_object->GetTag())->second;
	itr = std::find(gameObjects.begin(), gameObjects.end(), _object);
	if (itr != gameObjects.end())
	{
		std::iter_swap(itr, gameObjects.end() - 1);
		gameObjects.pop_back();
	}

}

void GameObject::RemoveUsedGameObject()
{
	// ���݃V�[����ɍ���Ă���I�u�W�F�N�g��S�č폜����
	for (auto itr = GameObject::gameObjectMap.begin(); itr != GameObject::gameObjectMap.end(); ++itr)
	{
		for (auto gameObject : itr->second)
		{
			delete gameObject;
		}
		itr->second.clear();
	}
	gameObjectMap.clear();
}


// forward�x�N�g���̌����ɉ�]����
// in forward : �����������O�������x�N�g��
void GameObject::RotateToNewForward(const Vector3& forward)
{
	// X���x�N�g��(1,0,0)��forward�̊Ԃ̊p�x�����߂�
	float dot = Vector3::Dot(Vector3::UnitX, forward);
	float angle = Math::Acos(dot);
	// �������������ꍇ
	if (dot > 0.9999f)
	{
		SetRotation(Quaternion::Identity);
	}
	// ������������ꍇ
	else if (dot < -0.9999f)
	{
		SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	}
	else
	{
		// ���x�N�g����forward�Ƃ̊O�ς����]�������Ƃ߁A��]������
		Vector3 axis = Vector3::Cross(Vector3::UnitX, forward);
		axis.Normalize();
		SetRotation(Quaternion(axis, angle));
	}
}

