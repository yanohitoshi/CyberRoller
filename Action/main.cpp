//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SDL.h"
#include "Game.h"

/*
�N���X���ł̐錾���Ԃ�public>protected>private>public(GetSet)�̏�
*/

/*
�@�Eenum�^�ϐ��͑S�đ啶���Œ�`
�@�E�萔�͍ŏ��̒P��̓������ƒP�ꂲ�Ƃ̓�������啶���ɂ��Ē�`
�@�E�ϐ��͍ŏ��̒P��̓������͏������ŒP�ꂲ�Ƃ̓�������啶���ɂ��Ē�`
*/

/*
 @file ��.h
 @brief �ȒP�Ȑ���
*/

	/*
	   @fn�����Ɋ֐��̐���������
	   @brief �v�����
	   @param ������ ����
	   @param ������ ����
	   @return �߂�l�̐���
	   @sa �Q�Ƃ��ׂ��֐��������΃����N���\���
	   @detail �ڍׂȐ���
	 */

/*
	@param ������ ����
*/

/*
  @fn
  @brief
*/

/*
  @fn
*/

/*
   @fn
   @brief
   @return
*/

/*
	 @enum Enum
	 ����
*/

/*
	 @struct Struct
	 ����
*/



/*
@fn	main�֐�
@param  �R�}���h���C�������̐�
@param  �R�}���h���C������
*/
int main(int argc, char** argv)
{
	Game game;
	//�Q�[���N���X�̒�`
	//�Q�[���N���X�̏�����������������
	bool success = game.Initialize();

	// �Q�[���̏������ɐ������Ă�����
	if (success)
	{
		// �Q�[�����[�v�J�n
		game.GameLoop();
	}

	//�Q�[���N���X�̏I������
	game.Termination();

	return 0;
}

