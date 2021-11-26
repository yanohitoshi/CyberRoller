#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

class CollectionObject;
class CollectionUI;

/*
@file SecondStageUI.h
@brief SecondStage��UI�\�����s��
*/
class FirstStageUI :
    public GameObject
{
public:
    
    /*
    @fn �R���X�g���N�^
    @brief  object�̐������s��
    @param	_playerObject �v���C���[�N���X�̃|�C���^
    @param	_first 1�ڂ̎��W���I�u�W�F�N�g�̃|�C���^
    @param	_second 2�ڂ̎��W���I�u�W�F�N�g�̃|�C���^
    @param	_third 3�ڂ̎��W���I�u�W�F�N�g�̃|�C���^
    */
    FirstStageUI(PlayerObject* _playerObject,CollectionObject* _first, CollectionObject* _second, CollectionObject* _third);
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~FirstStageUI();

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �V�[���̎��Ԑ����̒l
    const int SceneTime;
    // �X�J�C�{�b�N�X�N���X�̃|�C���^�ϐ�
    class SkyBoxObject* skyBox;

    PlayerObject* playerObject;

    // �e���W����UI�N���X�̃|�C���^
    CollectionUI* firstCollectionUI;
    CollectionUI* secondCollectionUI;
    CollectionUI* thirdCollectionUI;

    // ���ꂼ��̎��W���̌��ʂ�\�����鎞��
    const int FirstDrawTime;
    const int SecondDrawTime;
    const int ThirdDrawTime;

    // ���ꂼ��̎��W���̌��ʂ�\������ꏊ
    const Vector3 FirstCollectionPosition;
    const Vector3 SecondCollectionPosition;
    const Vector3 ThirdCollectionPosition;

    // �N���A��̃J�E���g�𐔂���ϐ�
    int clearCount;
    // �|�W�V�������ύX����Ă��邩�ǂ���
    bool isChangePosition;
};

