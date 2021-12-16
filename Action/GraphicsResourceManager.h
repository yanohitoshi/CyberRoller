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
class Font;

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
    @brief  テクスチャの取得
    @param	_fileName　取得したいテクスチャのファイル名
    @return Textureクラスのポインタ
    */
    Texture* CreateTexture(const std::string& _fileName);

    /*
    @brief  フォントの取得
    @param	_fileName　取得したいフォントのファイル名
    @return Fontクラスのポインタ
    */
    Font* CreateFont(const std::string& _fileName);

    /*
    @brief  スケルトンモデルの取得
    @param _fileName モデルへのアドレス
    @return スケルトンモデルクラスのポインタ
    */
    const class Skeleton* CreateSkeleton(const char* _fileName);

    /*
    @brief  アニメーションの取得
    @param _fileName アニメーションへのアドレス
    @return スケルトンアニメーションクラスのポインタ
    */
    const class Animation* CreateAnimation(const char* _fileName, bool _loop);

    /*
    @brief  メッシュの取得
    @param	_fileName 取得したいメッシュのファイル名
    @return Meshクラスのポインタ
    */
    Mesh* CreateMesh(const std::string& _fileName);

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

    /*
    @brief	時間制限用textureの生成
    @param	_value　最大値
    @param _fontSize　フォントサイズ
    */
    void CreateTimeFontTexture(int _value, int _fontSize);


    //自分のインスタンス
    static GraphicsResourceManager* graphicsResource;

    // スケルトンデータ
    std::unordered_map<std::string, class Skeleton*> skeletons;
    // アニメーションデータ
    std::unordered_map<std::string, class Animation*> anims;

    //ファイル名でメッシュを取得するための連想配列
    std::unordered_map<std::string, Mesh*> meshes;

    //ファイル名でテクスチャを取得するための連想配列
    std::unordered_map<std::string, Texture*>textures;

    // 使用する全種類のシェーダーを格納するコンテナ
    std::unordered_map<ShaderTag, Shader*> shaders;

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

    // 制限時間用フォントtextureの最大数（作りたい数字の最大値）
    const int MaxTimeFontTextures;
    // 制限時間用フォントのサイズ
    const int TimeFontSize;

public:

    /*
    @brief	カウントダウンタイムごとのTimeTextureを取ってくる関数（白）
    @param	カウントダウンタイム
    @return カウントダウンタイムごとのTimeTexture
    */
    Texture* GetTimeTexture(int _time);

    /*
    @brief	カウントダウンタイムごとのTimeTextureを取ってくる関数（黒）
    @param	カウントダウンタイム
    @return カウントダウンタイムごとのTimeTexture
    */
    Texture* GetTimeBlackTexture(int _time);

    /*
    @brief	カウントダウンタイムごとのTimeTextureを取ってくる関数（赤）
    @param	カウントダウンタイム
    @return カウントダウンタイムごとのTimeTexture
    */
    Texture* GetTimeRedTexture(int _time);

    Shader* FindUseShader(ShaderTag _shaderTag);

};

