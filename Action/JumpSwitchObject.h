#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

/*
@file JumpSwitchObject.h
@brief JumpSwitch�̐����ƍX�V���s��
*/
class JumpSwitchObject :
    public GameObject
{

public:

    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	object�̃T�C�Y
    @param	�I�u�W�F�N�g���ʗptag
    */
    JumpSwitchObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag);
    ~JumpSwitchObject();
    
    /*
    @fn �X�V����
    @param	�Ō�̃t���[������������̂ɗv��������
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    
    /*
    @fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
    @param	��������GameObject
    */
    void OnCollision(const GameObject& _hitObject)override;
    // 3D���f���̕`����s���N���X
    Mesh* mesh;
    MeshComponent* meshComponent;
    // �����蔻����s���N���X
    BoxCollider* boxCollider;

};
