//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CollectionEffectManager.h"
#include "CollectionObject.h"
#include "CollectionRipplesEffect.h"
#include "CollectionLightEffect.h"
#include "CrystalEffectManager.h"

/*
@fn コンストラクタ
@param	親クラスのポインタ
*/
CollectionEffectManager::CollectionEffectManager(CollectionObject* _owner)
	:GameObject(false, Tag::PARTICLE)
	, LightEffectRandValue(100)
	, MaxLightEffects(24)
	, TowFrequency(2)
	, ThreeFrequency(3)
	, RandValue(100)
	, ActiveTime(30)
{
	// メンバー変数の初期化	
	owner = _owner;
	position = owner->GetPosition();
	generateFlag = true;
	velocity = Vector3::Zero;
	effectPosition = Vector3::Zero;
	colorNum = 0;
	activeCount = 0;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
CollectionEffectManager::~CollectionEffectManager()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void CollectionEffectManager::UpdateGameObject(float _deltaTime)
{
	// 親クラスのステータスがActiveだったら
	if (owner->GetIsCollected())
	{
		// particleStateを有効化
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// particleStateを無効化
		particleState = ParticleState::PARTICLE_DISABLE;
	}

	// パーティクルの状態を見て
	switch (particleState)
	{
	case (PARTICLE_DISABLE):
		// 初期化
		generateFlag = true;
		break;

		// 有効状態だったら
	case PARTICLE_ACTIVE:

		ActiveEffect(_deltaTime);
		break;
	}
}

/*
@fn エフェクトがアクティブ時の処理関数
@param	_deltaTime 前のフレームでかかった時間
*/
void CollectionEffectManager::ActiveEffect(float _deltaTime)
{
	// 生成フラグがtrueの時
	if (generateFlag)
	{
		CreationRipplesEffect();
		// 生成フラグをfalseに変更
		generateFlag = false;
	}

	// カウントを数える
	++activeCount;

	// エフェクトがActiveとなっていられる時間内だったら
	if (activeCount < ActiveTime)
	{
		CreationLightEffect();
	}
}

/*
@fn 波紋エフェクト生産処理関数
*/
void CollectionEffectManager::CreationRipplesEffect()
{
	// オーナーのポジション取得
	effectPosition = owner->GetPosition();
	new CollectionRipplesEffect(this, effectPosition, Vector3::Zero);
}

/*
@fn 光エフェクト生産処理関数
*/
void CollectionEffectManager::CreationLightEffect()
{
	// エフェクトの色情報変数
	CrystalColor color = CrystalColor::WHITE;

	// 色番号に応じて色情報を変更
	if (colorNum == CrystalColor::WHITE)
	{
		color = CrystalColor::WHITE;
	}
	else if (colorNum == CrystalColor::RED)
	{
		color = CrystalColor::RED;
	}
	else if (colorNum == CrystalColor::BLUE)
	{
		color = CrystalColor::BLUE;
	}
	else if (colorNum == CrystalColor::GREEN)
	{
		color = CrystalColor::GREEN;
	}

	// 色番号を進める
	++colorNum;

	// 色番号が無になったら
	if (colorNum >= CrystalColor::NONE)
	{
		// 番号を初期状態に戻す
		colorNum = 0;
	}

	// ランダムな値を生成
	Vector3 randDir((float)(rand() % RandValue), (float)(rand() % RandValue), 1.0f);
	randDir.Normalize();

	if (activeCount % TowFrequency == 0)
	{
		randDir.x *= -1.0f;
	}
	
	if (activeCount % ThreeFrequency == 0)
	{
		randDir.y *= -1.0f;
	}

	randDir.z = 1.0f;

	new CollectionLightEffect(this, effectPosition, randDir, color);
}
