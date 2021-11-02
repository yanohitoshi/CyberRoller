#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Component.h"
#include "Math.h"

// クラスの前方宣言
class GameObject;
class Shader;
class Mesh;

/*
 @file MeshComponent.h
 @brief メッシュデータの管理と描画を行う
*/
class MeshComponent : public Component
{
public:

	/*
	@fn コンストラクタ
	@param _skelton スケルトンデータを用いるか。
	@param _color 途中で色の変更を用いるか。
	*/
    MeshComponent(GameObject* _owner,bool _skelton,bool _color);
	
	/*
	@fn デストラクタ
	@brief  Componentの削除を行う
	*/
    ~MeshComponent();

	/*
	@brief　描画処理
	@param	_shader 使用するシェーダークラスのポインタ
	*/
    virtual void Draw(Shader* _shader);

protected:

	//メッシュデータクラスへのポインタ
    Mesh* mesh;
	//テクスチャサイズ
    size_t textureIndex;
	//描画をするかどうか
	bool visible;
	//スケルトンデータを用いるか
	bool isSkelton;
	//カラーチェンジを用いるか
	bool isColorChange;
	// 輝度
	float luminance;
	// 色情報
	Vector3 emissiveColor;
	/*
	@brief　使用するtextureをセットする
	@param	_shader 使用するシェーダークラスのポインタ
	*/
	virtual void SetTextureToShader(Shader* _shader);

public: //ゲッターセッター

	/*
	@brief　メッシュコンポーネントが使うMeshの設定
	@param	_mesh 設定するMeshクラスのポインタ
	*/
	virtual void SetMesh(Mesh* _mesh) { mesh = _mesh; }

	/*
	@return 設定されたMeshクラスのポインタ
	*/
	virtual Mesh* GetMesh() { return mesh; }

	void SetEmissiveColor(Vector3 _emissiveColor) { emissiveColor = _emissiveColor; }

	/*
	@brief　メッシュコンポーネントが使うTextureインデックスの設定
	*/
	void SetTextureIndex(size_t _index) { textureIndex = _index; }

	/*
	@brief　描画をするかどうかを設定
	@param	true : 描画する , false : 描画しない
	*/
	void SetVisible(bool _visible) { visible = _visible; }

	/*
	@brief　描画をするかどうかを取得する
	@return	true : 描画する , false : 描画しない
	*/
	bool GetVisible() const { return visible; }

	/*
	@return スケルトンデータを用いるか
	*/
	bool GetIsSkeltal()const { return isSkelton; }

	/*
	@return カラーチェンジを用いるか
	*/
	bool GetIsColorChange()const { return isColorChange; }
	
};

