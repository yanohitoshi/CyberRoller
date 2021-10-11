#include "GeometryInstanceManager.h"
#include "Mesh.h"
#include "VertexArray.h"
#include <glew.h>
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "GameObject.h"

// マトリックスサイズ(16)
const unsigned int matrixElemNum = 16;
//マトリックスサイズ
const size_t matrix4Size = sizeof(float) * matrixElemNum;

GeometryInstanceManager::~GeometryInstanceManager()
{

	//ジオメトリインスタンスのアクター情報の中の行列バッファのメモリを解放する
	for (auto itr = mGeometryInstanceActorInfoMap.begin(); itr != mGeometryInstanceActorInfoMap.end(); itr++)
	{
		delete itr->second.mModelMatrice;
	}
	//マップのクリア
	mGeometryInstanceActorInfoMap.clear();
}

void GeometryInstanceManager::SetInstanceMesh(Mesh* _mesh, const unsigned int _maxInstanceNum, GeometryInstanceType _type)
{
	//登録したいジオメトリインスタンスの種類が既に登録されているかどうかを調べる
	auto info = mGeometryInstanceActorInfoMap.find(_type);

	//登録済みの場合
	if (info != mGeometryInstanceActorInfoMap.end())
	{
		//後の処理をスキップ
		return;
	}
	else //登録されていないとき
	{
		//メッシュを登録
		mGeometryInstanceActorInfoMap[_type].mMesh = _mesh;
	}

	// インスタンス最大数​
	mGeometryInstanceActorInfoMap[_type].mMaxInstanceNum = _maxInstanceNum;


	// MeshVAOの取得
	mGeometryInstanceActorInfoMap[_type].mVertexArray = _mesh->GetVertexArray()->GetVertexArray();


	// インデックス数の取得​
	mGeometryInstanceActorInfoMap[_type].mNumIndices = _mesh->GetVertexArray()->GetNumIndices();


	// 行列バッファの作成​
	mGeometryInstanceActorInfoMap[_type].mModelMatrice = new float[mGeometryInstanceActorInfoMap[_type].mMaxInstanceNum * matrixElemNum];


	// もともとあるmeshをインスタンスメッシュとして再登録​
	unsigned int instanceVao;
	//バッファの生成
	glGenBuffers(1, &instanceVao);

	//頂点バッファーとする
	glBindBuffer(GL_ARRAY_BUFFER, instanceVao);
	{

		// 行列バッファをinstanceVaoとバインド​
		glBufferData(GL_ARRAY_BUFFER, mGeometryInstanceActorInfoMap[_type].mMaxInstanceNum * matrix4Size, &mGeometryInstanceActorInfoMap[_type].mModelMatrice[0], GL_DYNAMIC_DRAW);

		// meshVAOをinstanceVaoに登録​
		glBindVertexArray(mGeometryInstanceActorInfoMap[_type].mVertexArray);

		// 頂点アトリビュートに行列データを1行ずつ(vec4ずつ）セット​
		const int matRowNum = 4;

		const int matColNum = 4;

		const int startAttrib = 3;

		// 頂点アトリビュート 3,4,5,6に行列を1行ずつセット​
		glEnableVertexAttribArray(3);

		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, matrix4Size, (void*)0);                        // 行列の 1行目​

		glEnableVertexAttribArray(4);

		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, matrix4Size, (void*)(1 * sizeof(float) * 4)); // 2行目​

		glEnableVertexAttribArray(5);

		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, matrix4Size, (void*)(2 * sizeof(float) * 4)); // 3行目​

		glEnableVertexAttribArray(6);

		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, matrix4Size, (void*)(3 * sizeof(float) * 4));  // 4行目​

		//glEnableVertexAttribArray(7);

		//glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, matrix4Size, (void*)(4 * sizeof(float) * 4));  // 4行目​


		glVertexAttribDivisor(3, 1);

		glVertexAttribDivisor(4, 1);

		glVertexAttribDivisor(5, 1);

		glVertexAttribDivisor(6, 1);

		//glVertexAttribDivisor(7, 1);

		glBindVertexArray(0);
	}

	//ジオメトリインスタンスのアクター情報に頂点バッファーをセット
	mGeometryInstanceActorInfoMap[_type].mInstanceVAO = instanceVao;
}

void GeometryInstanceManager::PrepareModelMatrice()
{
	// インスタンス種類ごとに行列バッファを埋める​
	for (auto itr = mGeometryInstanceActorMap.begin(); itr != mGeometryInstanceActorMap.end(); ++itr)
	{

		int num = 0;

		for (auto actor : itr->second)
		{
			//アクターのワールド空間
			Matrix4 mat = actor->GetWorldTransform();

			//行列の行と列を転置する ​
			mat.Transpose();

			//行列バッファに情報をコピー
			memcpy(&(mGeometryInstanceActorInfoMap[itr->first].mModelMatrice[num * matrixElemNum]), mat.GetAsFloatPtr(), matrix4Size); // matrixElemNum は16, matrix4Sizeは行列のサイズ​
			++num;
		}

	}

	// インスタンス種類ごとに行列バッファをコピー​
	for (auto itr = mGeometryInstanceActorMap.begin(); itr != mGeometryInstanceActorMap.end(); ++itr)
	{
		// 行列バッファにコピー​
		glBindBuffer(GL_ARRAY_BUFFER, mGeometryInstanceActorInfoMap[itr->first].mInstanceVAO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, itr->second.size() * matrix4Size, &mGeometryInstanceActorInfoMap[itr->first].mModelMatrice[0]);
	}
}

void GeometryInstanceManager::Draw(Shader* _shader)
{

	// 全種類のインスタンス描画​
	for (auto itr = mGeometryInstanceActorMap.begin(); itr != mGeometryInstanceActorMap.end(); ++itr)
	{

		if (itr->second.empty())
		{
			continue;
		}

		// 表面の鏡面反射指数をセット
		_shader->SetFloatUniform("uSpecPower", mGeometryInstanceActorInfoMap[itr->first].mMesh->GetSpecPower());
		_shader->SetFloatUniform("uLuminance", mGeometryInstanceActorInfoMap[itr->first].mMesh->GetLuminace());
		//_shader->SetFloatUniform("uAlpha", mGeometryInstanceActorInfoMap[itr->first].mMesh->GetAlpha());

		// テクスチャのセット​
		SetTextureToShader(_shader, itr->first);


		// インスタンシング描画​
		glBindVertexArray(mGeometryInstanceActorInfoMap[itr->first].mVertexArray);

		glDrawElementsInstanced(GL_TRIANGLES,

			mGeometryInstanceActorInfoMap[itr->first].mNumIndices,

			GL_UNSIGNED_INT,

			0,

			static_cast<GLsizei>(itr->second.size()));

		glBindVertexArray(0);
	}
}

void GeometryInstanceManager::SetTextureToShader(Shader* _shader, GeometryInstanceType _type)
{
	// メッシュテクスチャセット
	int texID, stageCount = 0;
	texID = mGeometryInstanceActorInfoMap[_type].mMesh->GetTextureID(TextureStage::DIFFUSE_MAP); // ディフューズ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uDiffuseMap", stageCount);
		stageCount++;
	}
	texID = mGeometryInstanceActorInfoMap[_type].mMesh->GetTextureID(TextureStage::NORMAL_MAP); // 法線マップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uNormalMap", stageCount);
		stageCount++;
	}
	texID = mGeometryInstanceActorInfoMap[_type].mMesh->GetTextureID(TextureStage::SPECULAR_MAP); // スペキュラーマップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uSpecularMap", stageCount);
		stageCount++;
	}
	texID = mGeometryInstanceActorInfoMap[_type].mMesh->GetTextureID(TextureStage::EMISSIVE_MAP); // 自己放射マップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uEmissiveMap", stageCount);
		stageCount++;
	}
}

void GeometryInstanceManager::AddGeometryInstanceActor(GameObject* _gameObject, GeometryInstanceType _type)
{
	//マップの中に追加するアクターのコンテナがあるかどうかを調べる
	auto gameObjects = mGeometryInstanceActorMap.find(_type);

	//あるとき
	if (gameObjects != mGeometryInstanceActorMap.end())
	{
		//アクターに対応したコンテナに追加
		gameObjects->second.emplace_back(_gameObject);
	}
	else //ないとき
	{
		//コンテナを作成して追加する
		std::vector<GameObject*> tmpVector;
		tmpVector.emplace_back(_gameObject);
		mGeometryInstanceActorMap[_type] = tmpVector;
	}
}

void GeometryInstanceManager::RemoveGeometryInstanceActor(GameObject* _gameObject, GeometryInstanceType _type)
{
	//マップの中に削除するアクターがいるかどうかを調べる
	auto iter = std::find(mGeometryInstanceActorMap[_type].begin(), mGeometryInstanceActorMap[_type].end(), _gameObject);

	//いるとき
	if (iter != mGeometryInstanceActorMap[_type].end())
	{
		std::iter_swap(iter, mGeometryInstanceActorMap[_type].end() - 1);
		mGeometryInstanceActorMap[_type].pop_back();
	}
}

void GeometryInstanceManager::ClearGeometryInstanceActorMap()
{
	//マップのクリア
	mGeometryInstanceActorMap.clear();
}
