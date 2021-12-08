//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CollectionUI.h"
#include "CollectedSprite.h"
#include "UnCollectedSprite.h"
#include "SpriteComponent.h"
#include "CollectionObject.h"
#include "CollectedEffectSprite.h"

/*
@brief	�R���X�g���N�^
@param �e�N���X�̃|�C���^
*/
CollectionUI::CollectionUI(CollectionObject* _owner)
	: GameObject(false, Tag::UI)
{
	owner = _owner;
	CollectionTag tag = owner->GetCollectionTag();
	collectedSprite = new CollectedSprite(tag);
	unCollectedSprite = new UnCollectedSprite(tag);
	collectedEffectSprite = new CollectedEffectSprite(tag);
	isInGame = true;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
CollectionUI::~CollectionUI()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CollectionUI::UpdateGameObject(float _deltaTime)
{
}

/*
@fn �ʏ펞�̕`��
*/
void CollectionUI::DrawInGame()
{
	if (owner->GetIsCollected())
	{
		collectedSprite->GetSpriteComponent()->SetVisible(true);
		collectedEffectSprite->GetSpriteComponent()->SetVisible(true);
		unCollectedSprite->GetSpriteComponent()->SetVisible(false);
	}
	else
	{
		collectedSprite->GetSpriteComponent()->SetVisible(false);
		collectedEffectSprite->GetSpriteComponent()->SetVisible(false);
		unCollectedSprite->GetSpriteComponent()->SetVisible(true);
	}
}

/*
@fn �`������Z�b�g����
*/
void CollectionUI::ResetDraw()
{
	collectedSprite->GetSpriteComponent()->SetVisible(false);
	collectedEffectSprite->GetSpriteComponent()->SetVisible(false);
	collectedEffectSprite->Reset();
	unCollectedSprite->GetSpriteComponent()->SetVisible(false);
}

/*
@fn �`�悷��|�W�V������ύX����
@param _position �Z�b�g����ʒu
*/
void CollectionUI::SetDrawPosition(Vector3 _position)
{
	collectedSprite->SetPosition(_position);
	unCollectedSprite->SetPosition(_position);
	collectedEffectSprite->SetPosition(_position);
}
