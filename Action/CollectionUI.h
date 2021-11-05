#pragma once
#include "GameObject.h"

class CollectionObject;
class CollectedSprite;
class UnCollectedSprite;
class CollectedEffectSprite;

class CollectionUI :
    public GameObject
{
public:
    
    /*
    @brief	�R���X�g���N�^
    */
    CollectionUI(CollectionObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~CollectionUI()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

    void DrawInGame();

    void ResetDraw();

    void SetDrawPosition(Vector3 _position);

private:


    CollectionObject* owner;
    CollectedSprite* collectedSprite;
    UnCollectedSprite* unCollectedSprite;
    CollectedEffectSprite* collectedEffectSprite;

    bool isInGame;
};

