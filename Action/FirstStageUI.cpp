//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "FirstStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "JumpTutorialParticl.h"
#include "MoveTutorialParticl.h"
#include "StartCountDownSprite.h"


FirstStageUI::FirstStageUI()
	: GameObject(false, Tag::UI)
	, JumpTutorialPosition(Vector3(3700.0f, -1000.0f, 700.0f))
	, MoveTutorialPosition(Vector3(3700.0f, -2200.0f, 700.0f))
{
	// �W�����v�`���[�g���A���pParticl
	new JumpTutorialParticl(JumpTutorialPosition);
	// �ړ��`���[�g���A���pParticl
	new MoveTutorialParticl(MoveTutorialPosition);

	// �v���C���[�𓮂������Ƃ��ł���悤�ɂ��邽�߂̃t���O
	CountDownFont::SetCountStartFlag(true);
}

FirstStageUI::~FirstStageUI()
{
	// �v���C���[�𓮂������Ƃ��ł���悤�ɂ��邽�߂̃t���O�̏�����
	CountDownFont::SetCountStartFlag(false);
}

void FirstStageUI::UpdateGameObject(float _deltaTime)
{
}
