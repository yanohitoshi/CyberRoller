#pragma once
#include "GameObject.h"

class CollectionObject;
class CollectionUI;

class FifthStageUI :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @brief  object�̐������s��
    @param	_playerObject �v���C���[�N���X�̃|�C���^
    */
    FifthStageUI(PlayerObject* _playerObject, CollectionObject* _first, CollectionObject* _second, CollectionObject* _third);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~FifthStageUI();

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

    CollectionUI* firstCollectionUI;
    CollectionUI* secondCollectionUI;
    CollectionUI* thirdCollectionUI;

    int clearCount;
    bool isChangePosition;
};
