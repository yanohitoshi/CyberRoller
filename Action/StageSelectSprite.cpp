//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "StageSelectSprite.h"
#include "SpriteComponent.h"
#include "StageSelectSceneUI.h"
#include "GraphicsResourceManager.h"

/*
@fn �R���X�g���N�^
@parma �e�N���X�̃|�C���^
@parma �V�[���̃X�e�[�^�X
@parma �`�悷��摜�̃t�@�C���l�[��
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

	// spriteComponen��new����
	sprite = new SpriteComponent(this, false);
	// �w�i�e�N�X�`�������[�h
	Texture* tex = GRAPHICS_RESOURCE->CreateTexture(_spriteFileName);
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