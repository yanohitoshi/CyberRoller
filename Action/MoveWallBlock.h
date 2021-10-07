#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class MeshComponent;
class BoxCollider;
class Mesh;

/*
@file MoveWallBlock.h
@brief 動く壁の生成と更新処理を行う
*/
class MoveWallBlock : public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	@param	動く速度
	@param	止まる位置
	*/
	MoveWallBlock(const Vector3& _p, const Vector3& _size, const Tag& _objectTag,float _speed,Vector3 _stopPos);
	
	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~MoveWallBlock();
	
	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	
	/*
	@fn 壁を開く関数
	@brief	壁を開く処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void OpenWall(float _deltaTime);

	/*
	@fn スイッチの状態を確認する関数
	@param	どの種類のobjectか判定する用のTag
	@param	フレームレート固定用deltaTime
	*/
	void ChackSwitch(Tag& _tag);
	
	/*
	@fn どの壁がどのスイッチを確認するかセットする関数
	@param	どの種類のobjectか判定する用のTag
	*/
	void SetChackSwitchTag(Tag& _tag);

	// 3Dモデルの描画を行うクラス
	MeshComponent* meshComponent;
	Mesh* mesh;

	// 当たり判定を行うクラス
	BoxCollider* boxCollider;

	// 開閉速度定数
	const float MoveSpeed;
	// Y軸ををずらして壁を中心に位置づけるための定数
	const float ShiftPositionY;

	// objectの初期位置を保存する用のvector
	Vector3 initPos;
	// objectの停止位置を保存する用のvector
	Vector3 stopPos;

	// チェックするTag保存用
	Tag chackTag;

	// open/close判定用flag
	bool openFlag;

public: // ゲッター・セッター

	/*
	@fn openFlagのgetter関数
	@return	openFlag open/close判定用Flag
	*/
	bool GetOpenFlag() { return openFlag; }
};

