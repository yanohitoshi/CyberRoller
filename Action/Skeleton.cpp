//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Skeleton.h"
#include <fstream>
#include <sstream>
#include <document.h>
#include <SDL_log.h>
#include "MatrixPalette.h"

/*
@fn スケルトンのファイルからのロード
@param _filename
@return 成功、失敗
*/
bool Skeleton::Load(const std::string& fileName)
{
	// ファイル名からテキストファイルをオープンして、RapidJSONに解析させる
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

	// JSONオブジェクトか
	if (!doc.IsObject())
	{
		SDL_Log("Skeleton %s is not valid json", fileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// Check the metadata　メタデータのチェック（バージョンチェック）
	if (ver != 1)
	{
		SDL_Log("Skeleton %s unknown format", fileName.c_str());
		return false;
	}

	// bonecount ボーン数の取得
	const rapidjson::Value& bonecount = doc["bonecount"];
	if (!bonecount.IsUint())
	{
		SDL_Log("Skeleton %s doesn't have a bone count.", fileName.c_str());
		return false;
	}

	size_t count = bonecount.GetUint();

	// ボーン数がMAX_SKELETON_BONESを超えていた場合 (196本が最大)
	if (count > MaxSkeletonBones)
	{
		SDL_Log("Skeleton %s exceeds maximum bone count.", fileName.c_str());
		return false;
	}

	bones.reserve(count);

	// ボーン配列の取得
	const rapidjson::Value& tmpBones = doc["bones"];
	if (!tmpBones.IsArray())
	{
		SDL_Log("Skeleton %s doesn't have a bone array?", fileName.c_str());
		return false;
	}

	// ボーン配列のサイズとボーン数が異なる場合はエラーを返す
	if (tmpBones.Size() != count)
	{
		SDL_Log("Skeleton %s has a mismatch between the bone count and number of bones", fileName.c_str());
		return false;
	}

	Bone temp;

	// ボーン配列数分ループ
	for (rapidjson::SizeType i = 0; i < count; i++)
	{
		// ボーンが読めるか？
		if (!tmpBones[i].IsObject())
		{
			SDL_Log("Skeleton %s: Bone %d is invalid.", fileName.c_str(), i);
			return false;
		}

		// "name" ボーン名
		const rapidjson::Value& name = tmpBones[i]["name"];
		temp.name = name.GetString();

		// "parent" 親ボーンID
		const rapidjson::Value& parent = tmpBones[i]["parent"];
		temp.parent = parent.GetInt();

		// "bindpose" バインドポーズ
		const rapidjson::Value& bindpose = tmpBones[i]["bindpose"];
		if (!bindpose.IsObject())
		{
			SDL_Log("Skeleton %s: Bone %d is invalid.", fileName.c_str(), i);
			return false;
		}

		// バインドポーズの回転、位置
		const rapidjson::Value& rot = bindpose["rot"];
		const rapidjson::Value& trans = bindpose["trans"];

		// 回転と位置が配列じゃなかったらエラー返す
		if (!rot.IsArray() || !trans.IsArray())
		{
			SDL_Log("Skeleton %s: Bone %d is invalid.", fileName.c_str(), i);
			return false;
		}

		// バインドポーズの回転成分
		temp.localBindPose.rotation.x = static_cast<float>(rot[0].GetDouble());
		temp.localBindPose.rotation.y = static_cast<float>(rot[1].GetDouble());
		temp.localBindPose.rotation.z = static_cast<float>(rot[2].GetDouble());
		temp.localBindPose.rotation.w = static_cast<float>(rot[3].GetDouble());

		// バインドポーズの移動成分
		temp.localBindPose.translation.x = static_cast<float>(trans[0].GetDouble());
		temp.localBindPose.translation.y = static_cast<float>(trans[1].GetDouble());
		temp.localBindPose.translation.z = static_cast<float>(trans[2].GetDouble());

		// ボーン配列に格納する
		bones.emplace_back(temp);
	}

	// Now that we have the bones　ここでボーン配列は読みこまれているので、逆バインドポーズ行列を計算する
	ComputeGlobalInvBindPose();

	return true;
}

/*
@fn スケルトンがロードされたときに自動的に呼び出され各ボーンのグローバル逆バインドポーズを計算
*/
void Skeleton::ComputeGlobalInvBindPose()
{
	// Resize to number of bones, which automatically fills identity    mGlobalInvIndPoses配列を、ボーン数分確保＆自動的に単位行列で初期化
	globalInvBindPoses.resize(GetNumBones());

	// Step 1: Compute global bind pose for each bone　　　　　　　　　　　ステップ１：それぞれのボーンのグローバルバインドポーズを計算

	// The global bind pose for root is just the local bind pose         root ([0]のこと) のグローバルバインドポーズは、ローカルバインドポーズのことです。
	globalInvBindPoses[0] = bones[0].localBindPose.ToMatrix();

	// Each remaining bone's global bind pose is its local pose          残りの各ボーンのグローバルバインドポーズは、
	// multiplied by the parent's global bind pose                       そのローカルポーズに親のグローバルバインドポーズを掛けたものです。
	for (size_t i = 1; i < globalInvBindPoses.size(); i++)
	{
		Matrix4 localMat = bones[i].localBindPose.ToMatrix();                     // そのボーンのローカルバインドポーズを行列に変換して locakMatに代入
		globalInvBindPoses[i] = localMat * globalInvBindPoses[bones[i].parent]; // localMat * 自分の親のグローバルバインドポーズ行列
	}

	// Step 2: Invert                                                   ステップ２：逆行列にする
	for (size_t i = 0; i < globalInvBindPoses.size(); i++)
	{
		globalInvBindPoses[i].Invert();
	}
}
