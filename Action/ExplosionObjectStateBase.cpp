//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateBase.h"

/*
@fn 前方ベクトルを用いてキャラクターを回転させる関数
@param	_owner 親クラスのポインタ
@param	_forward 今のフレームの前方ベクトル
@param	_tmpForward 前のフレームの前方ベクトル
*/
void ExplosionObjectStateBase::RotationProcess(ExplosionObjectBase* _owner, float _angle, Vector3 _axis)
{
	//_axis軸を_angle度回転させる
	float radian = Math::ToRadians(_angle);
	Quaternion rot = _owner->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	_owner->SetRotation(target);
}

/*
@fn 垂直移動処理
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void ExplosionObjectStateBase::VerticalMove(ExplosionObjectBase* _owner, float _deltaTime)
{
	++frameCount;

	if (frameCount % ChangeRateTime == 0)
	{
		++angle;
		rate = Math::Cos(angle);
	}

	velocity.z = rate * VerticalMoveSpeed;

	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
}