#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include <vector>
#include <string>
#include "Math.h"
#include "Collision.h"
#include "Renderer.h"

// クラスの前方宣言
class Renderer;
class VertexArray;
class Texture;

/*
@file Mesh.h
@brief メッシュデータ
*/
class Mesh
{
public:

	/*
	@fn コンストラクタ
	@brief Meshクラスの生成
	*/
    Mesh();
	
	/*
	@fn デストラクタ
	@brief Meshクラスの削除
	*/
    ~Mesh();

	/*
	@brief  メッシュデータの読み込み
	@param	_fileName ロードしたいメッシュのファイル名
	@param	_renderer Rendererクラスのポインタ
	@return true : 成功 , false : 失敗
	*/
    bool Load(const std::string& _fileName, Renderer* _renderer);

	/*
	@brief  ロードしたメッシュデータの解放
	*/
    void Unload();	

private:

	// テクスチャステージに割り当てられたテクスチャ
	std::unordered_map<TextureStage, int> stageDefTexture;

    //このメッシュに使うテクスチャのポインタの可変長コンテナ
    std::vector<Texture*> textures;

	//このメッシュに使う頂点データ
	std::vector<Vector3> verts;

    //このメッシュに使うシェーダーの名前
    std::string shaderName;

	//クラスのポインタ
    VertexArray* vertexArray;


    //オブジェクト空間での境界球の半径
    float radius;

    //鏡面反射成分の大きさ
    float specPower;
	
	// 自己発行強度
	float luminance;

	// AABB変数
	AABB box;

public: //ゲッターセッター

	/*
	@brief	VertexArrayのgetter関数
	@return	VertexArray型のポインタ
	*/
	VertexArray* GetVertexArray() { return vertexArray; }

	/*
	@brief	Textureクラスのgetter関数
	@return Textureクラスのポインタ
	*/
	Texture* GetTexture(size_t _index);

	/*
	@brief	ShaderNameのgetter関数
	@return ShaderName
	*/
	const std::string& GetShaderName() const { return shaderName; }

	/*
	@brief	半径のgetter関数
	@return 半径
	*/
	float GetRadius() const { return radius; }

	/*
	@brief	鏡面反射成分のgetter関数
	@return 鏡面反射成分
	*/
	float GetSpecPower() const { return specPower; }

	/*
	@brief	luminanceのgetter関数
	@return luminance
	*/
	float GetLuminace() const { return luminance; }

	/*
	@brief	textureステージごとのtextureIDのgetter関数
	@return textureステージごとのtextureID
	*/
	int GetTextureID(TextureStage stage);

	/*
	@brief	MeshのAABBのgetter関数
	@return MeshのAABB
	*/
	const AABB& GetBox() const { return box; }

	/*
	@brief	頂点データのgetter関数
	@return 頂点データ
	*/
	std::vector<Vector3> GetVerts() { return verts; }


};