#pragma once
#include "BoxObject.h"

/*
@file TitleGroundObject.h
@brief TitleGroundObject�̐����ƍX�V���s��
*/
class TitleGroundObject :
    public BoxObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param	�|�W�V����
	@param	player�̃|�W�V����
	@param	object�̃T�C�Y
	@param	�I�u�W�F�N�g���ʗptag
	*/
	TitleGroundObject(const Vector3& _p, const Vector3& _size,const Vector3& _playerPos , const Tag& _objectTag);
	~TitleGroundObject();
	
	/*
	@fn �X�V����
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// 3D���f���̕`����s���N���X
	Mesh* mesh;
	MeshComponent* meshComponent;

	// player�̃|�W�V������ۑ�����p�̕ϐ�
	Vector3 targetPos;
	// �ڕW�|�W�V�����ϐ�
	Vector3 goalPos;
	// �����|�W�V�����ϐ�
	Vector3 initPos;
	// �ڕW�ɓ��B�����Ƃ��Ƀ|�W�V���������Z�b�g����t���O
	bool rePositionFlag;
};

