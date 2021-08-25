//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Skeleton.h"
#include <fstream>
#include <sstream>
#include <document.h>
#include <SDL_log.h>
#include "MatrixPalette.h"

/*
@fn �X�P���g���̃t�@�C������̃��[�h
@param _filename
@return �����A���s
*/
bool Skeleton::Load(const std::string& fileName)
{
	// �t�@�C��������e�L�X�g�t�@�C�����I�[�v�����āARapidJSON�ɉ�͂�����
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		SDL_Log("File not found: Skeleton %s", fileName.c_str());
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	// JSON�I�u�W�F�N�g��
	if (!doc.IsObject())
	{
		SDL_Log("Skeleton %s is not valid json", fileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// Check the metadata�@���^�f�[�^�̃`�F�b�N�i�o�[�W�����`�F�b�N�j
	if (ver != 1)
	{
		SDL_Log("Skeleton %s unknown format", fileName.c_str());
		return false;
	}

	// bonecount �{�[�����̎擾
	const rapidjson::Value& bonecount = doc["bonecount"];
	if (!bonecount.IsUint())
	{
		SDL_Log("Skeleton %s doesn't have a bone count.", fileName.c_str());
		return false;
	}

	size_t count = bonecount.GetUint();

	// �{�[������MAX_SKELETON_BONES�𒴂��Ă����ꍇ (196�{���ő�)
	if (count > MaxSkeletonBones)
	{
		SDL_Log("Skeleton %s exceeds maximum bone count.", fileName.c_str());
		return false;
	}

	bones.reserve(count);

	// �{�[���z��̎擾
	const rapidjson::Value& tmpBones = doc["bones"];
	if (!tmpBones.IsArray())
	{
		SDL_Log("Skeleton %s doesn't have a bone array?", fileName.c_str());
		return false;
	}

	// �{�[���z��̃T�C�Y�ƃ{�[�������قȂ�ꍇ�̓G���[��Ԃ�
	if (tmpBones.Size() != count)
	{
		SDL_Log("Skeleton %s has a mismatch between the bone count and number of bones", fileName.c_str());
		return false;
	}

	Bone temp;

	// �{�[���z�񐔕����[�v
	for (rapidjson::SizeType i = 0; i < count; i++)
	{
		// �{�[�����ǂ߂邩�H
		if (!tmpBones[i].IsObject())
		{
			SDL_Log("Skeleton %s: Bone %d is invalid.", fileName.c_str(), i);
			return false;
		}

		// "name" �{�[����
		const rapidjson::Value& name = tmpBones[i]["name"];
		temp.name = name.GetString();

		// "parent" �e�{�[��ID
		const rapidjson::Value& parent = tmpBones[i]["parent"];
		temp.parent = parent.GetInt();

		// "bindpose" �o�C���h�|�[�Y
		const rapidjson::Value& bindpose = tmpBones[i]["bindpose"];
		if (!bindpose.IsObject())
		{
			SDL_Log("Skeleton %s: Bone %d is invalid.", fileName.c_str(), i);
			return false;
		}

		// �o�C���h�|�[�Y�̉�]�A�ʒu
		const rapidjson::Value& rot = bindpose["rot"];
		const rapidjson::Value& trans = bindpose["trans"];

		// ��]�ƈʒu���z�񂶂�Ȃ�������G���[�Ԃ�
		if (!rot.IsArray() || !trans.IsArray())
		{
			SDL_Log("Skeleton %s: Bone %d is invalid.", fileName.c_str(), i);
			return false;
		}

		// �o�C���h�|�[�Y�̉�]����
		temp.localBindPose.rotation.x = static_cast<float>(rot[0].GetDouble());
		temp.localBindPose.rotation.y = static_cast<float>(rot[1].GetDouble());
		temp.localBindPose.rotation.z = static_cast<float>(rot[2].GetDouble());
		temp.localBindPose.rotation.w = static_cast<float>(rot[3].GetDouble());

		// �o�C���h�|�[�Y�̈ړ�����
		temp.localBindPose.translation.x = static_cast<float>(trans[0].GetDouble());
		temp.localBindPose.translation.y = static_cast<float>(trans[1].GetDouble());
		temp.localBindPose.translation.z = static_cast<float>(trans[2].GetDouble());

		// �{�[���z��Ɋi�[����
		bones.emplace_back(temp);
	}

	// Now that we have the bones�@�����Ń{�[���z��͓ǂ݂��܂�Ă���̂ŁA�t�o�C���h�|�[�Y�s����v�Z����
	ComputeGlobalInvBindPose();

	return true;
}

/*
@fn �X�P���g�������[�h���ꂽ�Ƃ��Ɏ����I�ɌĂяo����e�{�[���̃O���[�o���t�o�C���h�|�[�Y���v�Z
*/
void Skeleton::ComputeGlobalInvBindPose()
{
	// Resize to number of bones, which automatically fills identity    mGlobalInvIndPoses�z����A�{�[�������m�ہ������I�ɒP�ʍs��ŏ�����
	globalInvBindPoses.resize(GetNumBones());

	// Step 1: Compute global bind pose for each bone�@�@�@�@�@�@�@�@�@�@�@�X�e�b�v�P�F���ꂼ��̃{�[���̃O���[�o���o�C���h�|�[�Y���v�Z

	// The global bind pose for root is just the local bind pose         root ([0]�̂���) �̃O���[�o���o�C���h�|�[�Y�́A���[�J���o�C���h�|�[�Y�̂��Ƃł��B
	globalInvBindPoses[0] = bones[0].localBindPose.ToMatrix();

	// Each remaining bone's global bind pose is its local pose          �c��̊e�{�[���̃O���[�o���o�C���h�|�[�Y�́A
	// multiplied by the parent's global bind pose                       ���̃��[�J���|�[�Y�ɐe�̃O���[�o���o�C���h�|�[�Y���|�������̂ł��B
	for (size_t i = 1; i < globalInvBindPoses.size(); i++)
	{
		Matrix4 localMat = bones[i].localBindPose.ToMatrix();                     // ���̃{�[���̃��[�J���o�C���h�|�[�Y���s��ɕϊ����� locakMat�ɑ��
		globalInvBindPoses[i] = localMat * globalInvBindPoses[bones[i].parent]; // localMat * �����̐e�̃O���[�o���o�C���h�|�[�Y�s��
	}

	// Step 2: Invert                                                   �X�e�b�v�Q�F�t�s��ɂ���
	for (size_t i = 0; i < globalInvBindPoses.size(); i++)
	{
		globalInvBindPoses[i].Invert();
	}
}
