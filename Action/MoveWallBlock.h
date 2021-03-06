#pragma once
#include "GameObject.h"

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
	~MoveWallBlock();
	
	/*
	@fn 更新処理
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	
	/*
	@fn スイッチの状態を確認する関数
	@param	どの種類のobjectか判定する用のTag
	@param	フレームレート固定用deltaTime
	*/
	void ChackSwitch(Tag& _tag, float _deltaTime);
	
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

	//開閉速度
	const float moveSpeed;
	//objectの初期位置を保存する用のvector
	Vector3 initPos;
	//objectの停止位置を保存する用のvector
	Vector3 stopPos;
	//open/close判定用flag
	bool openFlag;
	// チェックするTag保存用
	Tag chackTag;
};

