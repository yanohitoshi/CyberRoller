#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

// �N���X�̑O���錾
class CollectionObject;
enum CrystalColor;

/*
@file CollectionEffectManager.h
@brief ���W���G�t�F�N�g�̐������s��
*/
class CollectionEffectManager :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�N���X�̃|�C���^
    */
    CollectionEffectManager(CollectionObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~CollectionEffectManager()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    /*
    @fn �G�t�F�N�g���A�N�e�B�u���̏����֐�
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void ActiveEffect(float _deltaTime);

    /*
    @fn �g��G�t�F�N�g���Y�����֐�
    */
    void CreationRipplesEffect();

    /*
    @fn ���G�t�F�N�g���Y�����֐�
    */
    void CreationLightEffect();

    // �����t���O
    bool generateFlag;

    // �e�N���X�̃|�C���^�ϐ�
    CollectionObject* owner;
    // ��������G�t�F�N�g�̃|�W�V����
    Vector3 effectPosition;
    // particle�̏�ԊǗ��p�ϐ�
    ParticleState particleState;
    // Active�̎��Ԃ𐔂���
    int activeCount;
    // �F�ԍ��ϐ�
    int colorNum;

    // �G�t�F�N�g��Active�Ȏ���
    const int ActiveTime;
    // �����_���̒l�萔
    const int RandValue;
    // �����_���͈̔͂̊���
    const int LightEffectRandValue;
    // 1�x�ɐ�������G�t�F�N�g�̐�
    const int MaxLightEffects;
    // 2�̔{���̎��Ƀt���[���J�E���g�Ɣ�r���邽�߂̒萔
    const int TowFrequency;
    // 3�̔{���̎��Ƀt���[���J�E���g�Ɣ�r���邽�߂̒萔
    const int ThreeFrequency;

};

