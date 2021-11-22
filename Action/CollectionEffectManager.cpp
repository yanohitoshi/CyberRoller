#include "CollectionEffectManager.h"
#include "CollectionObject.h"
#include "CollectionRipplesEffect.h"
#include "CollectionLightEffect.h"
#include "CrystalEffectManager.h"

CollectionEffectManager::CollectionEffectManager(CollectionObject* _owner)
	:GameObject(false, Tag::PARTICLE)
	, LightEffectRandValue(100)
	, MaxLightEffects(24)
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

CollectionEffectManager::~CollectionEffectManager()
{
}

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

		ActiveEffectProcess(_deltaTime);

		break;
	}
}

void CollectionEffectManager::ActiveEffectProcess(float _deltaTime)
{
	if (generateFlag)
	{
		CreationRipplesEffect();
		generateFlag = false;
	}

	++activeCount;
	if (activeCount < 30)
	{
		CreationLightEffect();
	}

}

void CollectionEffectManager::GenerateEffectProcess()
{
}

void CollectionEffectManager::CreationRipplesEffect()
{
	effectPosition = owner->GetPosition();
	new CollectionRipplesEffect(this, effectPosition, Vector3::Zero);
}

void CollectionEffectManager::CreationLightEffect()
{
	CrystalColor color = CrystalColor::WHITE;

	if (colorNum == 0)
	{
		color = CrystalColor::WHITE;
	}
	else if (colorNum == 1)
	{
		color = CrystalColor::RED;
	}
	else if (colorNum == 2)
	{
		color = CrystalColor::BLUE;
	}
	else if (colorNum == 3)
	{
		color = CrystalColor::GREEN;
	}

	++colorNum;
	if (colorNum >= 4)
	{
		colorNum = 0;
	}

	// ランダムな値を生成
	Vector3 randDir((float)(rand() % 100), (float)(rand() % 100), 1.0f);
	randDir.Normalize();

	if (activeCount % 2 == 0)
	{
		randDir.x *= -1.0f;
	}
	
	if (activeCount % 3 == 0)
	{
		randDir.y *= -1.0f;
	}

	randDir.z = 1.0f;

	new CollectionLightEffect(this, effectPosition, randDir, color);

}
