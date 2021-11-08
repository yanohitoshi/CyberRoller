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
    @param	���F������pTag
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
    void ActiveEffectProcess(float _deltaTime);

    /*
    @fn �G�t�F�N�g���Y�����֐�
    */
    void GenerateEffectProcess();

    /*
    @fn �g��G�t�F�N�g���Y�����֐�
    */
    void CreationRipplesEffect();

    void CreationLightEffect();


    CollectionObject* owner;
    bool generateFlag;
    Vector3 effectPosition;
    // particle�̏�ԊǗ��p�ϐ�
    ParticleState particleState;
    int activeCount;
    int colorNum;
    // �����_���͈̔͂̊���
    const int LightEffectRandValue;
    // 1�x�ɐ�������G�t�F�N�g�̐�
    const int MaxLightEffects;

};

