#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SpriteComponent;
class Texture;
class Font;

/*
@file CountDownFont.h
@brief カウントダウンフォントの表示を行う
*/
class CountDownFont
    : public GameObject
{
public:

    /*
    @brief	コンストラクタ
    @param	カウントする時間
    */
    CountDownFont(int _time);
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~CountDownFont();
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;
    

private:

    // @fix
    // 時間切れになったかどうかのフラグ変数
    static bool timeOverFlag;
    // カウントを開始するかのフラグ変数
    static bool countStartFlag;

    // SpriteComponent変数
    SpriteComponent* sprite;
    // フレームカウント
    int frameCount;
    // 計測する時間
    int time;
    // WarningSpriteClassを起動するかどうかフラグ
    bool warningFlag;

    // 時間を1進めるタイミングを比較する定数
    const int AddTimeCount;
    // 時間制限の色を変更するタイミングを比較する定数
    const int ChangeColorCount;

public://ゲッターセッター

    /*
    @fn timeOverFlagのsetter関数
    @brief	timeOverFlagに値をセット
    @param	_timeOverFlag 時間切れになったかどうかのフラグ
    */
    static void SetTimeOverFlag(bool _timeOverFlag) { timeOverFlag = _timeOverFlag; }

    /*
    @fn countStartFlagのsetter関数
    @brief	countStartFlagに値をセット
    @param	_countStartFlag カウントを開始するかのフラグ
    */
    static void SetCountStartFlag(bool _countStartFlag) { countStartFlag = _countStartFlag; }

    /*
    @fn timeOverFlagのgetter関数
    @brief	timeOverFlagを取得
    @return	時間切れになったかどうかのフラグ
    */
    static bool GetTimeOverFlag() { return timeOverFlag; }

    /*
    @fn countStartFlagのgetter関数
    @brief	countStartFlagを取得
    @return	カウントを開始するかのフラグ
    */
    static bool GetCountStartFlag() { return countStartFlag; }

    /*
    @fn warningFlagのgetter関数
    @brief	warningFlagを取得
    @return	WarningSpriteClassを起動するかどうかフラグ
    */
    bool GetWarningFlag() { return warningFlag; }

};