#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

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

    void UpdateGameObject(float _deltaTime)override;

private:

    void OnCollision(const GameObject& _hitObject)override;

    Mesh* mesh;
    MeshComponent* meshComponent;
    BoxCollider* boxCollider;

};
