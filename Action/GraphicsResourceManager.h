#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SDL.h"
#include <unordered_map>    

// シングルトンなのでインスタンスのgetterを静的領域にdefineで定義
#define GRAPHICS_RESOURCE GraphicsResourceManager::GetInstance()

// クラスの前方宣言
class Mesh;
class MeshComponent;
class SpriteComponent;
class ParticleComponent;
class Texture;
class VertexArray;
class Shader;

/*
enum class シェーダーの種類を判別するタグ
*/
enum class ShaderTag
{
    SPRITE,
    SKYBOX,
    SWITCH,
    GEOMETRY_INSTANCE,
    DEPTH,
    SKINNED_DEPTH,
    SHADOW,
    SKINNED_SHADOW,
    PARTICLE,
    DEBUG,
};

class GraphicsResourceManager
{

public:

    /*
    @brief  インスタンスを取得する
    @return AudioManagerクラスのインスタンス
    */

    static GraphicsResourceManager* GetInstance() { return graphicsResource; }

    /*
    @brief  インスタンスを作成する
    */
    static void CreateInstance();

    /*
    @brief  インスタンスを削除する
    */
    static void DeleteInstance();

    /*
    @brief  スプライトの追加
    @param	_spriteComponent　追加するSpriteComponentクラスのポインタ
    */
    void AddSpriteComponent(SpriteComponent* _spriteComponent);

    /*
    @brief スプライトの削除
    @param	_spriteComponent　削除するSpriteComponentクラスのポインタ
    */
    void RemoveSpriteComponent(SpriteComponent* _spriteComponent);

    /*
    @brief  パーティクルの追加
    @param	_particleComponent　追加するParticleObjectクラスのポインタ
    */
    void AddParticleComponent(ParticleComponent* _particleComponent);

    /*
    @brief  スプライトの削除
    @param	削除するParticleObjectクラスのポインタ
    */
    void RemoveParticleComponent(ParticleComponent* _particleComponent);

    /*
    @brief  メッシュコンポーネントの追加
    @param	_meshComponent　追加するMeshComponentクラスのポインタ
    */
    void AddMeshComponent(MeshComponent* _meshComponent);

    /*
    @brief  メッシュコンポーネントの削除
    @param	_meshComponent　削除するMeshComponentクラスのポインタ
    */
    void RemoveMeshComponent(MeshComponent* _meshComponent);

    /*
    @brief	Particle用頂点データのセット関数
    */
    void SetParticleVertex();

    // アクティブスカイボックス
    void SetActiveSkyBox(class CubeMapComponent* in_skyBox) { activeSkyBox = in_skyBox; }
    class CubeMapComponent* GetSkyBox() { return activeSkyBox; }
    class VertexArray* GetCubeMapVerts() { return cubeVerts; }

    /*
    @brief  シェーダーの読み込み
    @return true : 成功 , false : 失敗
    */
    bool LoadShaders();

    /*
    @fn 終了処理関数
    @brief 生成したMusic・Soundの解放処理を行う
    */
    void ShutDown();

private:

    /*
    @fn コンストラクタ
    */
    GraphicsResourceManager();

    /*
    @fn デストラクタ
    @brife 保持している全てのResourceを解放する
    */
    ~GraphicsResourceManager();

    //自分のインスタンス
    static GraphicsResourceManager* graphicsResource;

    // スケルトンデータ
    std::unordered_map<std::string, class Skeleton*> skeletons;
    // アニメーションデータ
    std::unordered_map<std::string, class Animation*> anims;

    //ファイル名でメッシュを取得するための連想配列
    std::unordered_map<std::string, Mesh*> meshes;

    //メッシュコンポーネントのポインタの可変長コンテナ
    std::vector<MeshComponent*> meshComponents;
    //カラーチェンジコンポーネントのポインタの可変長コンテナ
    std::vector<MeshComponent*> colorChangeMeshComponents;
    //スプライトコンポーネントのポインタの可変長コンテナ
    std::vector<SpriteComponent*> sprites;
    //パーティクルのポインタ
    std::vector<ParticleComponent*> particles;
    //ファイル名でテクスチャを取得するための連想配列
    std::unordered_map<std::string, Texture*>textures;
    // スケルトンメッシュの描画に使われる
    std::vector<class SkeletalMeshComponent*>skeletalMeshes;
    // 色を変えるメッシュの描画に使われる
    std::vector<class ChangeColorMeshComponent*>changeColorMeshes;

    // 使用する全種類のシェーダーを格納するコンテナ
    std::unordered_map<ShaderTag, Shader*> shaders;

    // スプライトの頂点配列
    VertexArray* spriteVerts;

    // パーティクル用頂点定義
    VertexArray* particleVertex;

    // キューブ頂点配列
    VertexArray* cubeVerts;

    // フォントマップ
    std::unordered_map<std::string, class Font*> fonts;

    // 時間表示用のフォントtexture
    // 白色
    std::vector<Texture*> timeFontTextures;
    // 黒色
    std::vector<Texture*> timeBlackFontTextures;
    // 赤色
    std::vector<Texture*> timeRedFontTextures;

    // キューブマップ
    class CubeMapComponent* activeSkyBox; // 有効な(描画する)スカイボックス


    Shader* LoadShader(const std::string& _vertName, const std::string& _fragName);

    /*
    @brief シェーダをまとめているコンテナに格納する
    @param	_shader 追加するシェーダークラスのポインタ
    @param	_shaderTag 鍵となるシェーダーの種類を判別するタグ
    */
    void AddShaderMap(Shader* _shader, ShaderTag _shaderTag);

};

