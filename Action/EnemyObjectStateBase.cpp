//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@fn �O���x�N�g����p���ăL�����N�^�[����]������֐�
@param	_owner �e�N���X�̃|�C���^
@param	_forward ���̃t���[���̑O���x�N�g��
@param	_tmpForward �O�̃t���[���̑O���x�N�g��
*/
void EnemyObjectStateBase::RotationProcess(EnemyObjectBase* _owner, Vector3 _forward, Vector3 _tmpForward)
{
	// �O���x�N�g�����O�̃t���[������ς���Ă�����
	if (_tmpForward != _forward)
	{
		//�O�̃t���[���ƍ��̃t���[���̑O���x�N�g���Ő��`��Ԃ����
		Vector3 rotatioin = Vector3::Lerp(_forward, _tmpForward, 0.01f);

		// ��]�������߂�
		_owner->RotateToNewForward(rotatioin);
		// �O���x�N�g���X�V
		_owner->SetCharaForwardVec(rotatioin);
	}
}