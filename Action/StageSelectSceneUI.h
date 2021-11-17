#pragma once
#include "GameObject.h"
#include <unordered_map>

// �N���X�̑O���錾
class SkyBoxObject;
class StageSelectIconSprite;
class StageUnSelectIcon;
class StageSelectSprite;

class StageSelectSceneUI :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @brief  object�̐������s��
    */
    StageSelectSceneUI();

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~StageSelectSceneUI()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

    /*
    @brief �I������Ă����Ԃ̃A�C�R���p�}�b�v�ɃX�v���C�g�N���X��ǉ�����֐�
    @param	_state �ǉ�����X�v���C�g�N���X�̃|�C���^
    @param	_stateTag ���ƂȂ�^�O
    */
    void AddSelectIconSpriteMap(StageSelectIconSprite* _sprite, SceneState _stateTag);

    /*
    @brief �I������Ă����Ԃ̃A�C�R���p�}�b�v����X�v���C�g�N���X���폜����֐�
    @param	_stateTag ���ƂȂ�^�O
    */
    void RemoveSelectIconSpriteMap(SceneState _stateTag);

    /*
    @brief �I������Ă��Ȃ���Ԃ̃A�C�R���p�}�b�v�ɃX�v���C�g�N���X��ǉ�����֐�
    @param	_state �ǉ�����X�v���C�g�N���X�̃|�C���^
    @param	_stateTag ���ƂȂ�^�O
    */
    void AddUnSelectIconSpriteMap(StageUnSelectIcon* _sprite, SceneState _stateTag);

    /*
    @brief �I������Ă��Ȃ���Ԃ̃A�C�R���p�}�b�v����X�v���C�g�N���X���폜����֐�
    @param	_stateTag ���ƂȂ�^�O
    */
    void RemoveUnSelectIconSpriteMap(SceneState _stateTag);

    /*
    @brief stage�I����ʂ̃X�v���C�g�N���X�p�}�b�v�ɃX�v���C�g�N���X��ǉ�����֐�
    @param	_state �ǉ�����X�v���C�g�N���X�̃|�C���^
    @param	_stateTag ���ƂȂ�^�O
    */
    void AddStageSelectSpriteMap(StageSelectSprite* _sprite, SceneState _stateTag);

    /*
    @brief �I������Ă��Ȃ���Ԃ̃A�C�R���p�}�b�v����X�v���C�g�N���X���폜����֐�
    @param	_stateTag ���ƂȂ�^�O
    */
    void RemoveStageSelectSpriteMap(SceneState _stateTag);

private:

    // �X�J�C�{�b�N�X�N���X�̃|�C���^
    SkyBoxObject* skyBox;

    /*
    @brief �S�Ă�sprite�}�b�v���N���A����
    */
    void ClearAllSpriteMap();

    // StageSelectIconSprite���i�[����Map
    std::unordered_map<SceneState, StageSelectIconSprite*> selectIconSpriteMap;

    // StageUnSelectIcon���i�[����Map
    std::unordered_map<SceneState, StageUnSelectIcon*> unSelectIconMap;

    // StageSelectSprite���i�[����Map
    std::unordered_map<SceneState, StageSelectSprite*> selectSpriteMap;
};

