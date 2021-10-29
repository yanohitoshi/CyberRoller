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

/*
@fn デストラクタ
*/
GeometryInstanceManager::~GeometryInstanceManager()
{

	//ジオメトリインスタンスのアクター情報の中の行列バッファのメモリを解放する
	for (auto itr = geometryInstanceGameObjectInfoMap.begin(); itr != geometryInstanceGameObjectInfoMap.end(); itr++)
	{
		delete itr->second.modelMatrice;
	}
	//マップのクリア
	geometryInstanceGameObjectInfoMap.clear();
}

/*
@fn インスタンス用のメッシュを設定する
@param _mesh 登録するメッシュ
@param _maxInstanceNum 最大インスタンス数
@param _type ジオメトリインスタンスの種類
*/
void GeometryInstanceManager::SetInstanceMesh(Mesh* _mesh, const unsigned int _maxInstanceNum, GeometryInstanceType _type)
{
	//登録したいジオメトリインスタンスの種類が既に登録されているかどうかを調べる
	auto info = geometryInstanceGameObjectInfoMap.find(_type);

	//登録済みの場合
	if (info != geometryInstanceGameObjectInfoMap.end())
	{
		//後の処理をスキップ
		return;
	}
	else //登録されていないとき
	{
		//メッシュを登録
		geometryInstanceGameObjectInfoMap[_type].mesh = _mesh;
	}

	// インスタンス最大数​
	geometryInstanceGameObjectInfoMap[_type].maxInstanceNum = _maxInstanceNum;


	// MeshVAOの取得
	geometryInstanceGameObjectInfoMap[_type].vertexArray = _mesh->GetVertexArray()->GetVertexArray();


	// インデックス数の取得​
	geometryInstanceGameObjectInfoMap[_type].numIndices = _mesh->GetVertexArray()->GetNumIndices();


	// 行列バッファの作成​
	geometryInstanceGameObjectInfoMap[_type].modelMatrice = new float[geometryInstanceGameObjectInfoMap[_type].maxInstanceNum * matrixElemNum];


	// もともとあるmeshをインスタンスメッシュとして再登録​
	unsigned int instanceVao;
	//バッファの生成
	glGenBuffers(1, &instanceVao);

	//頂点バッファーとする
	glBindBuffer(GL_ARRAY_BUFFER, instanceVao);
	{

		// 行列バッファをinstanceVaoとバインド​
		glBufferData(GL_ARRAY_BUFFER, geometryInstanceGameObjectInfoMap[_type].maxInstanceNum * matrix4Size, &geometryInstanceGameObjectInfoMap[_type].modelMatrice[0], GL_DYNAMIC_DRAW);

		// meshVAOをinstanceVaoに登録​
		glBindVertexArray(geometryInstanceGameObjectInfoMap[_type].vertexArray);

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


		glVertexAttribDivisor(3, 1);

		glVertexAttribDivisor(4, 1);

		glVertexAttribDivisor(5, 1);

		glVertexAttribDivisor(6, 1);


		glBindVertexArray(0);
	}

	//ジオメトリインスタンスのアクター情報に頂点バッファーをセット
	geometryInstanceGameObjectInfoMap[_type].instanceVAO = instanceVao;
}

/*
@fn 行列バッファの更新
*/
void GeometryInstanceManager::PrepareModelMatrice()
{
	// インスタンス種類ごとに行列バッファを埋める​
	for (auto itr = geometryInstanceGameObjectMap.begin(); itr != geometryInstanceGameObjectMap.end(); ++itr)
	{

		int num = 0;

		for (auto actor : itr->second)
		{
			//アクターのワールド空間
			Matrix4 mat = actor->GetWorldTransform();

			//行列の行と列を転置する ​
			mat.Transpose();

			//行列バッファに情報をコピー
			memcpy(&(geometryInstanceGameObjectInfoMap[itr->first].modelMatrice[num * matrixElemNum]), mat.GetAsFloatPtr(), matrix4Size); // matrixElemNum は16, matrix4Sizeは行列のサイズ​
			++num;
		}

	}

	// インスタンス種類ごとに行列バッファをコピー​
	for (auto itr = geometryInstanceGameObjectMap.begin(); itr != geometryInstanceGameObjectMap.end(); ++itr)
	{
		// 行列バッファにコピー​
		glBindBuffer(GL_ARRAY_BUFFER, geometryInstanceGameObjectInfoMap[itr->first].instanceVAO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, itr->second.size() * matrix4Size, &geometryInstanceGameObjectInfoMap[itr->first].modelMatrice[0]);
	}
}

/*
@fn 描画処理
@param _shader 描画するシェーダー
*/
void GeometryInstanceManager::Draw(Shader* _shader)
{

	// 全種類のインスタンス描画​
	for (auto itr = geometryInstanceGameObjectMap.begin(); itr != geometryInstanceGameObjectMap.end(); ++itr)
	{

		if (itr->second.empty())
		{
			continue;
		}

		// 表面の鏡面反射指数をセット
		_shader->SetFloatUniform("uSpecPower", geometryInstanceGameObjectInfoMap[itr->first].mesh->GetSpecPower());
		_shader->SetFloatUniform("uLuminance", geometryInstanceGameObjectInfoMap[itr->first].mesh->GetLuminace());

		// テクスチャのセット​
		SetTextureToShader(_shader, itr->first);


		// インスタンシング描画​
		glBindVertexArray(geometryInstanceGameObjectInfoMap[itr->first].vertexArray);

		glDrawElementsInstanced(GL_TRIANGLES,
			geometryInstanceGameObjectInfoMap[itr->first].numIndices,
			GL_UNSIGNED_INT,
			0,
			static_cast<GLsizei>(itr->second.size()));

		glBindVertexArray(0);
	}
}

/*
@fn シェーダーにテクスチャをセット
@param _shader シェーダー
@param _type ジオメトリインスタンスの種類
*/
void GeometryInstanceManager::SetTextureToShader(Shader* _shader, GeometryInstanceType _type)
{
	// メッシュテクスチャセット
	int texID, stageCount = 0;
	texID = geometryInstanceGameObjectInfoMap[_type].mesh->GetTextureID(TextureStage::DIFFUSE_MAP); // ディフューズ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uDiffuseMap", stageCount);
		stageCount++;
	}
	texID = geometryInstanceGameObjectInfoMap[_type].mesh->GetTextureID(TextureStage::NORMAL_MAP); // 法線マップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uNormalMap", stageCount);
		stageCount++;
	}
	texID = geometryInstanceGameObjectInfoMap[_type].mesh->GetTextureID(TextureStage::SPECULAR_MAP); // スペキュラーマップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uSpecularMap", stageCount);
		stageCount++;
	}
	texID = geometryInstanceGameObjectInfoMap[_type].mesh->GetTextureID(TextureStage::EMISSIVE_MAP); // 自己放射マップ
	{
		glActiveTexture(GL_TEXTURE0 + stageCount);
		glBindTexture(GL_TEXTURE_2D, texID);
		_shader->SetIntUniform("uEmissiveMap", stageCount);
		stageCount++;
	}
}

/*
@fn ジオメトリインスタンス用のオブジェクトを追加
@param _gameObject 追加するオブジェクト
@param _type 追加するオブジェクトのジオメトリインスタンスの種類
*/
void GeometryInstanceManager::AddGeometryInstanceGameObject(GameObject* _gameObject, GeometryInstanceType _type)
{
	//マップの中に追加するアクターのコンテナがあるかどうかを調べる
	auto gameObjects = geometryInstanceGameObjectMap.find(_type);

	//あるとき
	if (gameObjects != geometryInstanceGameObjectMap.end())
	{
		//アクターに対応したコンテナに追加
		gameObjects->second.emplace_back(_gameObject);
	}
	else //ないとき
	{
		//コンテナを作成して追加する
		std::vector<GameObject*> tmpVector;
		tmpVector.emplace_back(_gameObject);
		geometryInstanceGameObjectMap[_type] = tmpVector;
	}
}

/*
@fn ジオメトリインスタンス用のオブジェクトを削除
@param _gameObject 削除するオブジェクト
@param _type 削除するオブジェクトのジオメトリインスタンスの種類
*/
void GeometryInstanceManager::RemoveGeometryInstanceGameObject(GameObject* _gameObject, GeometryInstanceType _type)
{
	//マップの中に削除するアクターがいるかどうかを調べる
	auto iter = std::find(geometryInstanceGameObjectMap[_type].begin(), geometryInstanceGameObjectMap[_type].end(), _gameObject);

	//いるとき
	if (iter != geometryInstanceGameObjectMap[_type].end())
	{
		std::iter_swap(iter, geometryInstanceGameObjectMap[_type].end() - 1);
		geometryInstanceGameObjectMap[_type].pop_back();
	}
}

/*
@fn ジオメトリインスタンスのアクターを格納するマップをクリア
*/
void GeometryInstanceManager::ClearGeometryInstanceGameObjectMap()
{
	//マップのクリア
	geometryInstanceGameObjectMap.clear();
}
