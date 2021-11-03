//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"
#include "Renderer.h"
#include "Texture.h"

/*
@param _pos オブジェクトの生成場所
@param _velocity オブジェクトの移動量
@param _lifeCount オブジェクトの生存時間
@param _spriteFileName 画像へのアドレス
@param _useStaticBillboardMat StaticBillboardMatを使用して回転計算を行うかどうか
@param _scale 画像の拡大サイズ(デフォルトの値は10)
*/
ParticleEffectBase::ParticleEffectBase(const Vector3& _pos, const Vector3& _velocity, const int& _lifeCount, const std::string& _spriteFileName, bool _useStaticBillboardMat,const float& _scale)
	: GameObject(false,Tag::PARTICLE)
	, lifeCount(_lifeCount)
{
	// メンバー変数の初期化
	velocity = _velocity;
	SetPosition(_pos);
	particleComponent = new ParticleComponent(this, _useStaticBillboardMat);
	particleComponent->SetTextureID(RENDERER->GetTexture(_spriteFileName)->GetTextureID());
	particleComponent->SetColor(Vector3(1.0f, 1.0f, 1.0f));
	particleComponent->SetScale(_scale);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
ParticleEffectBase::~ParticleEffectBase()
{
}

/*
@fn 更新処理関数
@brief 派生クラスの更新関数を呼び座標に移動量を足し続ける
@param	最後のフレームを完了するのに要した時間
*/
void ParticleEffectBase::UpdateGameObject(float _deltaTime)
{
	// オブジェクトの更新
	UpdateParticleObject(_deltaTime);
	// ポジションの更新
	SetPosition(position + velocity);
}

/*
@fn 派生クラスごとに決定する更新関数
*/
void ParticleEffectBase::UpdateParticleObject(float _deltaTime)
{
	// カウントダウンする
	LifeCountDown();
}

/*
@fn 生存時間をカウントダウンする関数。派生クラスで更新関数を決定した場合そこに追加すること。
*/
void ParticleEffectBase::LifeCountDown()
{
	//生存時間がゼロになるとこのオブジェクトを更新終了する
	if (lifeCount <= 0)
	{
		particleComponent->SetVisible(false);
		SetState(State::Dead);

	}
	else
	{
		particleComponent->SetVisible(true);
		lifeCount--;
	}

}

/*
@fn 回転計算処理
@param _axis 回転軸
*/
void ParticleEffectBase::Rotation(GameObject* _owner, const float _angle, const Vector3 _axis)
{
	//ランダムな値回転させる
	float radian = Math::ToRadians(_angle);
	Quaternion rot = _owner->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	_owner->SetRotation(target);
}