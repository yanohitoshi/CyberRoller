#include "StageSelectSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "StageSelectSceneUI.h"

/*
@fn �R���X�g���N�^
*/
StageSelectSprite::StageSelectSprite(StageSelectSceneUI* _owner, SceneState _state,Vector3& _pos,const std::string& _spriteFileName)
	: GameObject(false, Tag::UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 100.0f, 0.0f));
	SetScale(Vector3(1.0f, 1.0f, 1.0f));
	SetPosition(_pos);

	myState = _state;
	_owner->AddStageSelectSpriteMap(this, myState);

	// spriteComponen��new����
	sprite = new SpriteComponent(this, false);
	// �w�i�e�N�X�`�������[�h
	Texture* tex = RENDERER->GetTexture(_spriteFileName);
	// �w�i�e�N�X�`�����Z�b�g
	sprite->SetTexture(tex);
	// �f���f���Ȃ����Z�b�g
	sprite->SetVisible(true);
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
}