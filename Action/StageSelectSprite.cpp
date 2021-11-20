#include "StageSelectSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "StageSelectSceneUI.h"

/*
@fn �R���X�g���N�^
*/
StageSelectSprite::StageSelectSprite(StageSelectSceneUI* _owner, SceneState _state,const std::string& _spriteFileName)
	: GameObject(false, Tag::UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 100.0f, 0.0f));
	SetScale(Vector3(1.0f, 1.0f, 1.0f));

	myState = _state;
	_owner->AddStageSelectSpriteMap(this, myState);
	isVisible = true;
	//switch (myState)
	//{
	//case FIRST_SATGE_SCENE:
	//	// �|�W�V�������Z�b�g
	//	SetPosition(Vector3(0.0f, 100.0f, 0.0f));
	//	break;
	//case SECOND_SATGE_SCENE:
	//	// �|�W�V�������Z�b�g
	//	SetPosition(Vector3(1500.0f, 100.0f, 0.0f));
	//	break;
	//case THIRD_SATGE_SCENE:
	//	// �|�W�V�������Z�b�g
	//	SetPosition(Vector3(2500.0f, 100.0f, 0.0f));
	//	break;
	//case FOURTH_SATGE_SCENE:
	//	// �|�W�V�������Z�b�g
	//	SetPosition(Vector3(3500.0f, 100.0f, 0.0f));
	//	break;
	//case FINAL_STAGE_SCENE:
	//	// �|�W�V�������Z�b�g
	//	SetPosition(Vector3(4500.0f, 100.0f, 0.0f));
	//	break;
	//}

	// spriteComponen��new����
	sprite = new SpriteComponent(this, false);
	// �w�i�e�N�X�`�������[�h
	Texture* tex = RENDERER->GetTexture(_spriteFileName);
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
StageSelectSprite::~StageSelectSprite()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void StageSelectSprite::UpdateGameObject(float _deltaTime)
{
	// �f���f���Ȃ����Z�b�g
	sprite->SetVisible(isVisible);
}

void StageSelectSprite::MoveLeft()
{
}

void StageSelectSprite::MoveRight()
{
}
