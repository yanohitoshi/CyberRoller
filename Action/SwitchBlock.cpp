//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SwitchBlock.h"
#include "Skeleton.h"
#include "ChangeColorMeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "BoxCollider.h"
#include "MainCameraObject.h"
#include "TutorialSwitchParticlEffect.h"
#include "TutorialSwitchOkEffect.h"
#include "SwitchEffectMakeManeger.h"
#include "FirstStageUI.h"
#include <string>

/*
@fn コンストラクタ
@param	ポジション
@param	objectのサイズ
@param	オブジェクト判別用tag
@param	チュートリアル用スイッチかどうかフラグ
*/
SwitchBlock::SwitchBlock(GameObject* _owner, const Vector3& _size, const Tag& _objectTag,bool _isTutorial)
	: GameObject(false, _objectTag)
	, MoveUpSpeed(150.0f)
	, MoveDownSpeed(-250.0f)
	, ShiftStopPosition(40.0f)
	, AllClearColer(Vector3(1.0f, 1.0f, 0.5f))
	, OnColor(Vector3(0.1f, 0.1f, 1.0f))
	, OffColor(Vector3(1.0f, 0.1f, 0.1f))
	,isTutorialSwitch(_isTutorial)
{
	//GameObjectメンバ変数の初期化
	position = _owner->GetPosition();
	SetPosition(position);
	SetScale(_size);
	tag = _objectTag;
	velocity = Vector3::Zero;
	initPosition = position;
	stopPoint = position.z - ShiftStopPosition;
	isPushBackToPlayer = true;
	isSendVelocityToPlayer = true;
	isCheckGroundToPlayer = true;

	//モデル描画用のコンポーネント
	meshComponent = new ChangeColorMeshComponent(this,false,true);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/switch_model/S_EnergyCube.gpmesh"));

	//メッシュ情報取得
	mesh = meshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();
	//押し戻し判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::SWITCH_TAG, GetOnCollisionFunc());
	AABB aabb = { Vector3(-55.0f,-55.0f,-40.0f),Vector3(55.0f,55.0f,55.0f) };
	boxCollider->SetObjectBox(aabb);

	// フラグの初期化
	tmpChangeColorFlag = false;
	changeColorFlag = false;
	pushStop = false;
	isOnPlayer = false;
	isHitPlayer = false;
	onFlag = false;
	isAvailableSwitch = true;

	// チュートリアル用のスイッチだったらチュートリアル用のパーティクルを付与
	if (isTutorialSwitch)
	{
		new TutorialSwitchParticlEffect(Vector3(position.x,position.y,position.z + 250.0f),this);
		new TutorialSwitchOkEffect(Vector3(position.x, position.y, position.z + 250.0f), this);
	}

	// スイッチ用のエフェクトを付与
	new SwitchEffectMakeManeger(this);

}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
SwitchBlock::~SwitchBlock()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void SwitchBlock::UpdateGameObject(float _deltaTime)
{
	// 当たり判定用のworld上のAABBを取得
	aabb = boxCollider->GetWorldBox();

	// スイッチの状態を確認
	CheckOnFlag(tag);
	// 色変更処理
	ColorChangeProcess();
	// 可動処理
	MovableProcess();

	// ポジションに速度を足す
	position = position + velocity * _deltaTime;
	// ポジションを更新
	SetPosition(position);

	// 当たり判定系フラグを初期化
	isOnPlayer = false;
	isHitPlayer = false;

}

/*
@fn 可動処理関数
*/
void SwitchBlock::MovableProcess()
{
	// スイッチの可動処理
	// プレイヤーが乗っていなくてかつ当たっていなかったら
	if (isOnPlayer == false && isHitPlayer == false)
	{
		// 初期のポジションよりも低い位置に居たら
		if (position.z < initPosition.z)
		{
			// 上昇する速度を持たせる
			velocity.z = MoveUpSpeed;
		}
		else if (position.z >= initPosition.z) // 初期ポジションまで到達していたら
		{
			// 速度を切る
			velocity.z = 0.0f;
		}
	}
	else if (isOnPlayer == true) // プレイヤーが乗っていたら
	{
		// 停止フラグがfalseだったら
		if (pushStop == false)
		{
			// 下降の速度を持たせる
			velocity.z = MoveDownSpeed;
		}
		else if (pushStop == true) // 停止フラグがtrueだったら
		{
			// 速度を切る
			velocity.z = 0.0f;
		}
	}
}

/*
@fn 色変更処理
*/
void SwitchBlock::ColorChangeProcess()
{
	// 前のフレームで色の変換が起きたかフラグを保存
	tmpChangeColorFlag = changeColorFlag;

	// ポジションが色を変更する位置よりも低くプレイヤーが乗っていたら色変更フラグをtrueに
	if (position.z <= stopPoint && isOnPlayer == true)
	{
		changeColorFlag = true;
	}
	else
	{
		// その他の場合カラーチェンジフラグをfalseに
		changeColorFlag = false;
	}

	// 前のフレームで色が変更されていなかったら
	if (changeColorFlag == true && tmpChangeColorFlag == false)
	{
		// スイッチの利用が可能状態だったら
		if (isAvailableSwitch == true)
		{
			// スイッチがOFFだったら
			if (onFlag == false)
			{
				onFlag = true;
			}
		}
	}

	SetColorProcess();
}

/*
@fn 色セット処理
*/
void SwitchBlock::SetColorProcess()
{
	// スイッチの状態を見て色を変更
	if (onFlag == true && isAvailableSwitch == true)
	{
		// ONの時
		meshComponent->SetColor(OnColor);
	}
	else if (onFlag == false && isAvailableSwitch == true)
	{
		// OFFの時
		meshComponent->SetColor(OffColor);
	}
	else if (isAvailableSwitch == false)
	{
		// 区画の全てのスイッチが押されている時
		meshComponent->SetColor(AllClearColer);
		luminance = 0.2f;
	}
}

/*
@fn タグごとのスイッチの状態チェック関数
@param _Tag チェックするスイッチのTag
*/
void SwitchBlock::CheckOnFlag(Tag& _Tag)
{
	// 調べるスイッチの可変長配列を保存するための配列
	std::vector<GameObject*> switches;

	// _Tagを使用して調べるスイッチを探す
	switches = GameObject::FindGameObject(_Tag);

	// カウントを生成
	int switchCount = 0;
	int flagCount = 0;
	for (auto itr : switches)
	{
		// スイッチの数を数える
		++switchCount;
		if (itr->GetSwitchFlag() == true)
		{
			// ONになっているスイッチの数を数える
			++flagCount;
		}
	}
	// スイッチの総数とONになっているスイッチの総数が同じだったら
	if (flagCount == switchCount)
	{
		// スイッチを利用不可にする
		isAvailableSwitch = false;
	}

}

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
	動く床と接している時にその速度をもらうための
@param	当たったGameObject
@param	当たったGameObjectの当たり判定タグ
*/
void SwitchBlock::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	if (_physicsTag == PhysicsTag::GROUND_CHECK_TAG)
	{
		// プレイヤーとのHitフラグをtrueに
		isHitPlayer = true;

		// 上に乗っているフラグをtrueに
		isOnPlayer = true;
		// 一度停止フラグをfalseに
		pushStop = false;
		// もし停止位置にあったら
		if (position.z <= stopPoint)
		{
			// 停止フラグをtrueに
			pushStop = true;
		}
	}

	// ヒットしたオブジェクトが動く床だったら
	if (_hitObject.GetTag() == Tag::MOVE_GROUND)
	{
		// 動く床の速度を持たせる
		Vector3 groundVel = _hitObject.GetVelocity();
		velocity.x = groundVel.x;
		velocity.y = groundVel.y;
	}

}