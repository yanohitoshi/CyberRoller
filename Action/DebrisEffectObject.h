#pragma once
#include "GameObject.h"

// �N���X�̑O���錾
class MeshComponent;
class Mesh;

class DebrisEffectObject :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�ƂȂ�N���X�̃|�C���^
    @param	�|�W�V����
    @param	�ړ����x
    */
    DebrisEffectObject(const Vector3& _pos, const Vector3& _direction);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~DebrisEffectObject()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    void LifeCountDown();

    // Mesh���Ǘ�����N���X
    Mesh* mesh;
    // 3D���f���̕`����s���N���X
    MeshComponent* meshComponent;

    Vector3 direction;
    int lifeCount;

    float moveSpeed;
    const float MovePower;

    //// ���t���[������scale�l 
    //const float AddScale;
    //// ���t���[������alpha�l
    //const float SubAlpha;
    //// �G�t�F�N�g�̐F
    //const Vector3 EffectColor;
};

