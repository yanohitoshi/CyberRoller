#pragma once

/*
@file VertexArray.h
@brief 頂点配列データを作る
*/
class VertexArray
{
public:
	// 頂点レイアウト列挙
	enum Layout
	{
		PosNormTex,     // 位置&法線&テクスチャUV を持ったフォーマット
		PosNormSkinTex  // 位置&法線& "スキン用の影響ボーン＆重み情報" & テクスチャUV 
	};

	/*
	@param	頂点バッファの配列のポインタ
	@param	頂点数
	@param	インデックスバッファの配列のポインタ
	@param	インデックスの数
	*/
	VertexArray(const float* _verts, unsigned int _numVerts,
		const unsigned int* _indices, unsigned int _numIndices);
	// 頂点配列コンストラクタ 
	VertexArray(const void* verts, unsigned int numVerts, Layout layout,
		const unsigned int* indices, unsigned int numIndices);
	VertexArray();
	~VertexArray();

	/*
	@brief	頂点配列をアクティブにする（描画に使用できるようにする）
	*/
	void SetActive();

	// スカイボックス用頂点配列オブジェクトの作成
	void CreateCubeVerts();

private:

	//頂点バッファにある頂点の数
	unsigned int numVerts;
	//インデクスバッファにあるインデックスの数
	unsigned int numIndices;
	//頂点バッファのOpenGL ID
	unsigned int vertexBuffer;
	//インデックスバッファのOpenGL ID
	unsigned int indexBuffer;
	//頂点配列オブジェクトのOpenGL ID
	unsigned int vertexArray;
	//unsigned int m_VAO;                                            // 頂点配列オブジェクトID
	//unsigned int m_VBO;                                           // 頂点バッファID (OpenGLに登録時に付与される)

public://ゲッターセッター

	/*
	@fn numIndicesのgetter関数
	@brief	インデックスバッファにあるインデックスの数を取得する
	@return numIndices（インデックスの数）
	*/
	unsigned int GetNumIndices() const { return numIndices; }

	/*
	@fn numVertsのgetter関数
	@brief	頂点バッファにある頂点の数を取得する
	@return numVerts（頂点の数）
	*/
	unsigned int GetNumVerts() const { return numVerts; }

	unsigned int GetVertexArray() const { return vertexArray; }

};

