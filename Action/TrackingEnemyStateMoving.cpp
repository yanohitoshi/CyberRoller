//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TrackingEnemyStateMoving.h"

// ���݂�statePattern�̎d�l��̃N���X��ǉ����Ȃ��Ƃ����Ȃ��ꍇ�����肻�̂��߂̋�̃N���X�ł��B
// ���P���@�͍����ł��B

/*
@fn �R���X�g���N�^
*/
TrackingEnemyStateMoving::TrackingEnemyStateMoving()
{
}

/*
@fn �f�X�g���N�^
*/
TrackingEnemyStateMoving::~TrackingEnemyStateMoving()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
EnemyState TrackingEnemyStateMoving::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void TrackingEnemyStateMoving::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
}
