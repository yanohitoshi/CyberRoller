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


SwitchBlock::SwitchBlock(GameObject* _owner, const Vector3& _size, const Tag& _objectTag)
	: GameObject(false, _objectTag)
	, MOVE_UP_SPEED(150.0f)
	, MOVE_DOWN_SPEED(-250.0f)
	, SHIFT_STOP_POSITION(40.0f)
	, ALL_CLEAR_COLOR(Vector3(1.0f, 1.0f, 0.5f))
	, ON_CLEAR(Vector3(0.1f, 0.1f, 1.0f))
	, OFF_CLEAR(Vector3(1.0f, 0.1f, 0.1f))
{
	//GameObjectメンバ変数の初期化
	position = _owner->GetPosition();
	SetPosition(position);
	SetScale(_size);
	tag = _objectTag;
	velocity = Vector3::Zero;
	initPosition = position;
	stopPoint = position.z - SHIFT_STOP_POSITION;
	//モデル描画用のコンポーネント
	meshComponent = new ChangeColorMeshComponent(this,false,true);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/switch_model/S_EnergyCube.gpmesh"));

	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//押し戻し判定用のコンポーネント
	boxCollider = new BoxCollider(this, ColliderComponent::SwitchTag, GetOnCollisionFunc());
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
	if (tag == Tag::TUTORIAL_SWITCH)
	{
		new TutorialSwitchParticlEffect(Vector3(position.x,position.y,position.z + 250.0f),this);
		new TutorialSwitchOkEffect(Vector3(position.x, position.y, position.z + 250.0f), this);
	}

	// スイッチ用のエフェクトを付与
	new SwitchEffectMakeManeger(this);

}

SwitchBlock::~SwitchBlock()
{
}

void SwitchBlock::UpdateGameObject(float _deltaTime)
{
	// 当たり判定用のworld上のAABBを取得
	aabb = boxCollider->GetWorldBox();

	// スイッチの状態を確認
	ChackOnFlag(tag);

	// 前のフレームで色の変換が起きたかフラグを保存
	tmpChangeColorFlag = changeColorFlag;

	// ポジションが色を変更する位置よりも低くプレイヤーが乗っていたら色変更フラグをtrueに
	if (position.z <= stopPoint && isOnPlayer == true)
	{
		changeColorFlag = true;
	}
	else
	{
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

	// スイッチの状態を見て色を変更
	if (onFlag == true && isAvailableSwitch == true)
	{
		// ONの時
		meshComponent->SetColor(ON_CLEAR);
	}
	else if (onFlag == false && isAvailableSwitch == true)
	{
		// OFFの時
		meshComponent->SetColor(OFF_CLEAR);
	}
	else if (isAvailableSwitch == false)
	{
		// 区画の全てのスイッチが押されている時
		meshComponent->SetColor(ALL_CLEAR_COLOR);
	}
	
	// スイッチの可動処理
	// プレイヤーが乗っていなくてかつ当たっていなかったら
	if (isOnPlayer == false && isHitPlayer == false)
	{
		// 初期のポジションよりも低い位置に居たら
		if (position.z < initPosition.z)
		{
			// 上昇する速度を持たせる
			velocity.z = MOVE_UP_SPEED;
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
			velocity.z = MOVE_DOWN_SPEED;
		}
		else if (pushStop == true) // 停止フラグがtrueだったら
		{
			// 速度を切る
			velocity.z = 0.0f;
		}
	}

	// ポジションに速度を足す
	position = position + velocity * _deltaTime;
	// ポジションを更新
	SetPosition(position);

	// 当たり判定系フラグを初期化
	isOnPlayer = false;
	isHitPlayer = false;

}


void SwitchBlock::ChackOnFlag(Tag& _Tag)
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

void SwitchBlock::OnCollision(const GameObject& _hitObject)
{
	// ヒットしたオブジェクトがプレイヤーだったら
	if (_hitObject.GetTag() == Tag::PLAYER)
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

void SwitchBlock::PlayerFootOnCollision(const GameObject& _hitObject)
{
}
