#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class MeshComponent;
class BoxCollider;
class Mesh;
class SoundEffectComponent;

/*
@enum CollectionTag 何番目の収集物か判別するタグ
*/
enum class CollectionTag
{
	FIRST,
	SECOND,
	THIRD
};

/*
@file CollectionObject.h
@brief 収集物の生成と更新を行う
*/
class CollectionObject :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	オブジェクト判別用tag
	@param	何番目の収集物かを判定するタグ
	*/
	CollectionObject(const Vector3& _pos, const Tag& _objectTag, CollectionTag _collectionTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~CollectionObject()override;

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn 回転処理関数
	@param 回転する角度
	@param 回転する軸
	*/
	void RotationProcess(float _angle,Vector3 _axis);

	/*
	@fn 可動処理関数
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void Movable(float _deltaTime);

	/*
	@fn 収集された時の処理関数
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void Collected(float _deltaTime);

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	@param	当たったGameObjectの当たり判定タグ
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// 3Dモデルの描画を行うクラス
	MeshComponent* meshComponent;
	Mesh* mesh;
	// サウンドエフェクトクラス
	SoundEffectComponent* soundEffectComponent;
	BoxCollider* boxCollider;
	CollectionTag collectionTag;

	// Z軸をずらす定数
	const float ShiftPositionZ;
	// 収集されたときの移動速度
	const float CollectedSpeed;
	// 上下移動速度
	const float VerticalMoveSpeed;
	// サイン計算を行うタイミング
	const int ChangeRateTime;
	// 収集された後移動する時間
	const int CollectedMoveTime;
	// 収集された後描画する時間
	const int CollectedVisibleTime;

	// 収集されたときの回転角度
	float collectedRotationAngle;
	// 収集されたかどうか
	bool isCollected;
	// サウンドエフェクトを再生するかどうか
	bool isPlaySoundEffect;
	// 収集されてからのカウントを数える
	int collectedCount;
	// フレームカウントを数える
	int frameCount;

	// コサイン関数に渡す値
	float value;
	// コサイン関数からの値をもらう変数
	float rate;

public:

	/*
	@fn 獲得されているかどうかを取得
	@return isCollected 獲得されているかどうか
	*/
	bool GetIsCollected() { return isCollected; }

	/*
	@fn 何番目の収集物か判別するタグ取得
	@return collectionTag 何番目の収集物か判別するタグ
	*/
	CollectionTag GetCollectionTag() { return collectionTag; }
};

