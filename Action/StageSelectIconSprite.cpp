//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "StageSelectIconSprite.h"
#include "RenderingObjectManager.h"
#include "SpriteComponent.h"
#include "StageSelectSceneUI.h"

/*
@fn �R���X�g���N�^
@parma �e�N���X�̃|�C���^
@parma �V�[���̃X�e�[�^�X
@parma �`�悷��摜�̃t�@�C���l�[��
*/
StageSelectIconSprite::StageSelectIconSprite(StageSelectSceneUI* _owner, SceneState _state, const std::string& _spriteFileName)
	: GameObject(false, Tag::UI)
	, FirstStagePosition(Vector3(-800.0f, -300.0f, 0.0f))
	, SecondStagePosition(Vector3(-400.0f, -300.0f, 0.0f))
	, ThirdStagePosition(Vector3(0.0f, -300.0f, 0.0f))
	, FourthStagePosition(Vector3(400.0f, -300.0f, 0.0f))
	, FinalStagePosition(Vector3(800.0f, -300.0f, 0.0f))
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	SetScale(Vector3(0.25f, 0.25f, 0.25f));

	myState = _state;
	_owner->AddSelectIconSpriteMap(this, myState);


	switch (myState)
	{
	case FIRST_SATGE_SCENE:
		// �|�W�V�������Z�b�g
		SetPosition(FirstStagePosition);
		break;
	case SECOND_SATGE_SCENE:
		// �|�W�V�������Z�b�g
		SetPosition(SecondStagePosition);
		break;
	case THIRD_SATGE_SCENE:
		// �|�W�V�������Z�b�g
		SetPosition(ThirdStagePosition);
		break;
	case FOURTH_SATGE_SCENE:
		// �|�W�V�������Z�b�g
		SetPosition(FourthStagePosition);
		break;
	case FINAL_STAGE_SCENE:
		// �|�W�V�������Z�b�g
		SetPosition(FinalStagePosition);
		break;
	}

	isVisible = true;

	// spriteComponen��new����
	sprite = new SpriteComponent(this, false);
	// �w�i�e�N�X�`�������[�h
	Texture* tex = RENDERING_OBJECT_MANAGER->CreateTexture(_spriteFileName);
	// �w�i�e�N�X�`�����Z�b�g
	sprite->SetTexture(tex);
	// �f���f���Ȃ����Z�b�g
	sprite->SetVisible(isVisible);
	// alpha�l���Z�b�g
	sprite->SetAlpha(1.0f);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
StageSelectIconSprite::~StageSelectIconSprite()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void StageSelectIconSprite::UpdateGameObject(float _deltaTime)
{
	// �f���f���Ȃ����Z�b�g
	sprite->SetVisible(isVisible);
}
