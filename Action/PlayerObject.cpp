//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObject.h"
#include "SkeletalMeshComponent.h"
#include "Mesh.h"
#include "MainCameraObject.h"
#include <string>
#include "Renderer.h"
#include "Skeleton.h"
#include "Animation.h"
#include "InputSystem.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "PlayerSandSmokeMakeManeger.h"
#include "LandingEffectManeger.h"
#include "CountDownFont.h"
#include "PlayerObjectStateIdle.h"
#include "PlayerObjectStateRun.h"
#include "PlayerObjectStateDead.h"
#include "PlayerObjectStateJumpEndToIdle.h"
#include "PlayerObjectStateJunpEndToRun.h"
#include "PlayerObjectStateJumpLoop.h"
#include "PlayerObjectStateJumpStart.h"
#include "PlayerObjectStateDownLoop.h"
#include "PlayerObjectStateDownOver.h"
#include "PlayerObjectStateDownStart.h"
#include "PlayerObjectStateDownUp.h"
#include "PlayerObjectStateRespown.h"
#include "PlayerObjectStateRunStart.h"
#include "PlayerObjectStateRunStop.h"
#include "PlayerObjectStateRunTurn.h"
#include "PlayerObjectStateIdlingDance.h"
#include "PlayerObjectStateFlinch.h"
#include "PlayerObjectStateFallDead.h"

// 定数と静的メンバーの初期化
const float PlayerObject::Gravity = 4500.0f;
bool PlayerObject::chackJumpFlag = false;
bool PlayerObject::chackIsJumping = false;

PlayerObject::PlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
	, playerBox({ Vector3::Zero,Vector3::Zero })
	, FirstJumpPower(1200.0f)
	, MovePower(90.0f)
	, FirstMovePower(0.0f)
	, AirMovePower(60.0f)
	, DecelerationForce(100.0f)
	, DeadSpace(0.3f)
	, FallPpsitionZ(-500.0f)
	, FirstPositionZ(5000.0f)
	, RestartTime(10000)
	, FlinchSpeed(1000.0f)
{

	//GameObjectメンバ変数の初期化
	state = Active;
	scale = Vector3(1.2f, 1.2f, 1.2f);
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	SetScale(scale);
	SetPosition(_pos);

	// 最初のポジションを保存
	firstPos = Vector3(position.x, position.y, FirstPositionZ);
	// ジャンプパワーを初速にセット
	jumpPower = FirstJumpPower;
	//リスポ－ンするまでのカウント初期化
	respawnCount = 0;
	// リスポ－ンflag位置初期化
	respownPos = firstPos;
	// フラグ初期化
	respawnFlag = false;
	clearFlag = false;
	nextSceneFlag = false;
	restartFlag = false;
	// ダウン・コンティニュー・deadフラグ初期化
	downFlag = false;
	downUpFlag = false;
	downOverFlag = false;
	deadFlag = false;
	//clear判定フラグ
	clearFlag = false;
	// 接地フラグ初期化
	onGround = false;
	// 入力フラグ初期化
	inputFlag = false;
	// 入力可能かフラグ初期化
	isAvailableInput = true;
	// 走り状態かフラグ初期化
	runFlag = false;

	// ジャンプフラグ初期化
	jumpFlag = false;
	// ジャンプが利用可能かフラグ初期化
	isAvailableJumpKey = false;

	// 前方ベクトル初期化
	forwardVec = Vector3(0.0f, 0.0f, 0.0f);
	// キャラクターの前方ベクトル初期化
	charaForwardVec = Vector3(1.0f, 0.0f, 0.0f);
	// 右方向ベクトル初期化
	rightVec = Vector3(0.0f,0.0f,0.0f);
	// 回転ベクトル初期化
	rotateVec = Vector3(0.1f, 0.0f, 0.0f);
	// 回転ベクトルNormalize
	rotateVec.Normalize();
	// 押し出されたときにその速度を保存しキャラクターの速度に足すためのベクトル初期化
	pushedVelocity = Vector3::Zero;

	// ジャンプ中のフレームをカウントする用のカウント初期化
	jumpFrameCount = 0;

	// ジャンプswitch用フラグ初期化
	switchJumpFlag = false;

	// カウント初期化
	reStartCount = 0;
	turnDelayCount = 0;

	//モデル描画用のコンポーネント
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMes hをセット(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/robo_model/SK_Rob.gpmesh"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/robo_model/SK_Rob.gpskel"));

	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	//アニメ―ション用の可変長配列をリサイズ
	animTypes.resize(static_cast<unsigned int>(PlayerState::PLAYER_STATE_NUM));

	//-----------アニメーションを読み込み-----------------//
	// アイドリングアニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_IDLE)] = RENDERER->GetAnimation("Assets/Model/robo_model/Happy_Idle_Anim.gpanim", true);
	// 一定以上入力がなかった際のアイドリングアニメーション（ダンス）
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_IDLE_DANCE)] = RENDERER->GetAnimation("Assets/Model/robo_model/Tut_Hip_Hop_Dance.gpanim", true);
	// 走りアニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_RUN)] = RENDERER->GetAnimation("Assets/Model/robo_model/Running.gpanim", true);
	// 走りだしアニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_RUN_START)] = RENDERER->GetAnimation("Assets/Model/robo_model/Idle_To_Sprint_2.gpanim", false);
	// 走り終わりアニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_RUN_STOP)] = RENDERER->GetAnimation("Assets/Model/robo_model/Run_To_Stop.gpanim", false);
	// 走り中の切り替えしアニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_RUN_TURN)] = RENDERER->GetAnimation("Assets/Model/robo_model/Change_Direction.gpanim", false);
	// 走り中壁に当たった際の怯みアニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_RUN_TO_FLINCH)] = RENDERER->GetAnimation("Assets/Model/robo_model/Receiving_An_Uppercut.gpanim", false);
	// ジャンプループアニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_JUMPLOOP)] = RENDERER->GetAnimation("Assets/Model/robo_model/Floating.gpanim", true);
	// ジャンプ開始アニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_JUMPSTART)] = RENDERER->GetAnimation("Assets/Model/robo_model/Jump_up.gpanim", false);
	// 次の状態が待機の時の着地アニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE)] = RENDERER->GetAnimation("Assets/Model/robo_model/Landing.gpanim", false);
	// 次の状態が走りの時の着地アニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_JUMPEND_TO_RUN)] = RENDERER->GetAnimation("Assets/Model/robo_model/Falling_To_Roll.gpanim", false);
	// タイムオーバー時のアニメーション（start）
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_DOWNSTART)] = RENDERER->GetAnimation("Assets/Model/robo_model/Praying_down.gpanim", false);
	// タイムオーバー時のアニメーション（loop）
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_DOWN_LOOP)] = RENDERER->GetAnimation("Assets/Model/robo_model/Praying_Idle.gpanim", false);
	// タイムオーバー時のアニメーション（コンティニュー）
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_DOWN_UP)] = RENDERER->GetAnimation("Assets/Model/robo_model/Praying_up.gpanim", false);
	// タイムオーバー時のアニメーション（ゲームオーバー）
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_DOWN_OVER)] = RENDERER->GetAnimation("Assets/Model/robo_model/over_down.gpanim", false);
	// 死亡時のアニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_DEAD)] = RENDERER->GetAnimation("Assets/Model/robo_model/Stunned.gpanim", false);

	//anim変数を速度1.0fで再生
	skeltalMeshComponent->PlayAnimation(animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_IDLE)], 1.0f);


	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = skeltalMeshComponent->GetMesh();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this,ColliderComponent::PLAYER_TAG, GetOnCollisionFunc());
	playerBox = mesh->GetBox();
	playerBox = { Vector3(-60.0f,-10.0f,0.0f),Vector3(60.0f,10.0f,179.0f) };
	boxCollider->SetObjectBox(playerBox);

	//接地判定用のsphereCollider
	groundChackSphereCol = new SphereCollider(this, ColliderComponent::GROUND_CHECK_TAG, std::bind(&PlayerObject::OnCollisionGround, this, std::placeholders::_1));
	Sphere groundChackSphere = { Vector3(0.0f,0.0f,0.0f),5.0f };
	groundChackSphereCol->SetObjectSphere(groundChackSphere);

	// 砂ぼこりと着地時のeffectを持たせる
	new PlayerSandSmokeMakeManeger(this);
	new LandingEffectManeger(this);

	// stateプールの初期化
	// ※順番に配列に追加していくのでステータスの列挙と合う順番に追加
	statePools.push_back(new PlayerObjectStateIdle);
	statePools.push_back(new PlayerObjectStateIdlingDance);
	statePools.push_back(new PlayerObjectStateRun);
	statePools.push_back(new PlayerObjectStateRunStart);
	statePools.push_back(new PlayerObjectStateRunStop);
	statePools.push_back(new PlayerObjectStateRunTurn);
	statePools.push_back(new PlayerObjectStateFlinch);
	statePools.push_back(new PlayerObjectStateJumpLoop);
	statePools.push_back(new PlayerObjectStateJumpStart);
	statePools.push_back(new PlayerObjectStateJumpEndToIdle);
	statePools.push_back(new PlayerObjectStateJunpEndToRun);
	statePools.push_back(new PlayerObjectStateDownStart);
	statePools.push_back(new PlayerObjectStateDownLoop);
	statePools.push_back(new PlayerObjectStateDownUp);
	statePools.push_back(new PlayerObjectStateDownOver);
	statePools.push_back(new PlayerObjectStateDead);
	statePools.push_back(new PlayerObjectStateFallDead);
	statePools.push_back(new PlayerObjectStateRespown);

	// stateを初期化
	nowState = PlayerState::PLAYER_STATE_IDLE;
	nextState = PlayerState::PLAYER_STATE_IDLE;
}

PlayerObject::~PlayerObject()
{
	// 静的フラグの初期化
	chackJumpFlag = false;
	chackIsJumping = false;
}

void PlayerObject::UpdateGameObject(float _deltaTime)
{
	if (FallPpsitionZ >= position.z)
	{
		nextState = PlayerState::PLAYER_STATE_FALL_DEAD;
	}

	// ステート外部からステート変更があったか？
	if (nowState != nextState)
	{
		statePools[static_cast<unsigned int>(nextState)]->Enter(this, _deltaTime);
		nowState = nextState;
		return;
	}

	// ステート実行
	nextState = statePools[static_cast<unsigned int>(nowState)]->Update(this, _deltaTime);

	// プレイヤー以外の影響でポジションが変更された時用
	position = (position + pushedVelocity * _deltaTime );
	// ポジションをセット
	SetPosition(position);

	// ステート内部からステート変更あったか？
	if (nowState != nextState)
	{
		statePools[static_cast<unsigned int>(nextState)]->Enter(this, _deltaTime);
		nowState = nextState;
	}

	//カメラにplayerのpositionを渡す
	if (clearFlag == false && nextSceneFlag == false && position.z >= FallPpsitionZ)
	{
		mainCamera->SetLerpObjectPos(position);
	}

	// リスポーンフラグがtrueだったら
	if (respawnFlag == true)
	{
		// カメラを初期にリセット
		mainCamera->ResetYaw();
	}

	// RENDERERに現在のポジションを送る
	RENDERER->SetPlayerPositon(position);
	
	// フレームの最後に接地判定と押されている速度を初期化
	onGround = false;
	pushedVelocity = Vector3::Zero;

	// ステータスが走りはじめもしくはランループだったら切り替えしディレイカウントをカウントする
	// 連続で切り替えしアニメーションに入らないように抑制をかけるため
	if (nowState == PlayerState::PLAYER_STATE_RUN_START || nowState == PlayerState::PLAYER_STATE_RUN)
	{
		// カウントを数える
		++turnDelayCount;
	}

	// 一定時間放置によるゲームをリセットするかチェック
	ChackRestartProcess();

}

void PlayerObject::GameObjectInput(const InputState& _keyState)
{

	// スタート時のカウントダウンが終わったら入力可能状態にする
	if (CountDownFont::GetCountStartFlag() == true)
	{
		isAvailableInput = true;
	}
	else if (CountDownFont::GetCountStartFlag() == false || CountDownFont::GetTimeOverFlag() == true)
	{
		// カウントダウンが終わっていないまたはタイムオーバーになったら入力を切る
		isAvailableInput = false;
	}

	//今カメラが向いている方向をplayerに渡す
	forwardVec = mainCamera->GetCameraVec();

	//カメラの向きから右方向を計算
	rightVec = Vector3::Cross(forwardVec, Vector3(0.0f, 0.0f, 1.0f));

	// ステート実行
	statePools[static_cast<unsigned int>(nowState)]->Input(this, _keyState);

	// 着地エフェクト用の判定フラグを更新
	chackJumpFlag = jumpFlag;



}


/*
@fn めり込み判定と押し戻し
*/
void PlayerObject::FixCollision(AABB& myAABB, const AABB& pairAABB)
{

	// 仮速度変数
	Vector3 ment = Vector3::Zero;
	// プレイヤーの押し戻し計算
	playerCalcCollisionFixVec(myAABB, pairAABB, ment);
	// 押し戻し計算を考慮しポジションを更新
	SetPosition(position + ment);

}

void PlayerObject::RotateToNewForward(const Vector3& forward)
{
	// X軸ベクトル(1,0,0)とforwardの間の角度を求める
	float dot = Vector3::Dot(Vector3::UnitX, forward);
	float angle = Math::Acos(dot);
	// 下向きだった場合
	if (dot > 0.9999f)
	{
		SetRotation(Quaternion::Identity);
	}
	// 上向きだった場合
	else if (dot < -0.9999f)
	{
		SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	}
	else
	{
		// 軸ベクトルとforwardとの外積から回転軸をもとめ、回転させる
		Vector3 axis = Vector3::Cross(Vector3::UnitX, forward);
		axis.Normalize();
		SetRotation(Quaternion(axis, angle));
	}
}

void PlayerObject::ClearChack(Tag _tag)
{
	// フラグ検索用可変長配列を生成
	std::vector<GameObject*> switches;

	// クリア条件用スイッチを探して格納
	switches = GameObject::FindGameObject(Tag::CLEAR_SCENE_SWITCH);

	// スイッチの状態確認関数呼び出し
	SwitchChackProcess(switches);

}

void PlayerObject::SwitchChackProcess(std::vector<GameObject*> _chackVector)
{
	// スイッチの総数カウント初期化
	int switchCount = 0;
	// ONになっているスイッチ総数カウント初期化
	int flagCount = 0;

	// スイッチの総数とONになっているスイッチの総数を数える
	for (auto itr : _chackVector)
	{
		// スイッチの総数カウント
		++switchCount;

		// フラグをチェック
		if (itr->GetSwitchFlag() == true)
		{
			// ONになっているスイッチの総数カウント
			++flagCount;
		}
	}

	// スイッチの総数とONになっているスイッチの総数が一致していたら
	if (flagCount == switchCount)
	{
		// クリア状態にする
		clearFlag = true;
	}

}

void PlayerObject::ChackFlinchSpeedProcess()
{
	// 一定速度以上だったら
	if (velocity.x >= FlinchSpeed || velocity.y >= FlinchSpeed ||
		velocity.x <= -FlinchSpeed || velocity.y <= -FlinchSpeed)
	{
		// 壁に当たったフラグをtrueに
		isHitWall = true;
	}
}


void PlayerObject::OnCollision(const GameObject& _hitObject)
{
	// Hitしたオブジェクトのタグを取得
	Tag hitObjectTag = _hitObject.GetTag();

	// 空中でかつ押し戻しを行うオブジェクトだったら
	if (onGround == false && _hitObject.GetisPushBackToPlayer())
	{
		// プレイヤーのワールドボックスを取得
		playerBox = boxCollider->GetWorldBox();
		// 押し戻し用関数へ渡す
		FixCollision(playerBox, _hitObject.aabb);
	}
	else if (hitObjectTag == Tag::PUSH_BOARD)
	{
		// 押し戻し用関数へ渡す
		FixCollision(playerBox, _hitObject.aabb);
	}

	// 当たった際にプレイヤーがひるむオブジェクトだったら
	if (_hitObject.GetisFlinchToPlayer())
	{
		// ひるむ速度かチェックする処理
		ChackFlinchSpeedProcess();
	}
	else // それ以外だったら
	{
		// 壁に当たったフラグをfalseに
		isHitWall = false;
	}

	// 当たったオブジェクトがプレイヤーに速度の影響を与えるオブジェクトだったら
	if (_hitObject.GetisSendVelocityToPlayer())
	{
		// そのオブジェクトの速度を保存
		pushedVelocity = _hitObject.GetVelocity();
	}

	// ステージをクリアしたかをチェック
	if (hitObjectTag == Tag::CLEAR_POINT)
	{
		ClearChack(hitObjectTag);
	}

	// 当たったオブジェクトがリスポーンオブジェクトだったら
	if (hitObjectTag == Tag::RESPOWN_POINT)
	{
		// リスポーン用変数を初期化
		respownPos = Vector3::Zero;
		// 当たったリスポーンオブジェクトのポジションを取得
		respownPos = _hitObject.GetPosition();
	}

	// 当たったオブジェクトが棘オブジェクトだったら
	if (hitObjectTag == Tag::NEEDLE_PANEL)
	{
		// 死亡フラグをtureにセット
		deadFlag = true;
	}

}

void PlayerObject::OnCollisionGround(const GameObject& _hitObject)
{
	// 接地判定を行うオブジェクトだったら
	if (_hitObject.GetisChackGroundToPlayer())
	{
		// 接地フラグをtrueに
		onGround = true;
		// オブジェクトの速度をもらう
		pushedVelocity = _hitObject.GetVelocity();
	}

	// 当たったオブジェクトがジャンプスイッチでかつジャンプフラグがfalseだったら
	if (_hitObject.GetTag() == Tag::JUMP_SWITCH && jumpFlag == false)
	{
		// スイッチジャンプアクティブ
		ActiveSwitchJumpProcess();
	}

}

void PlayerObject::ActiveSwitchJumpProcess()
{
	// もし、ジャンプスイッチフラグがfalseだったら
	if (switchJumpFlag == false)
	{
		// フレームカウントを初期化
		jumpFrameCount = 0;
		// ジャンプ力を初期値にセット
		jumpPower = FirstJumpPower;
		// ジャンプスイッチフラグをtrueに
		switchJumpFlag = true;
	}
}

void PlayerObject::ChackRestartProcess()
{
	// 一定時間入力が無かったらタイトルに戻る
	if (inputFlag == false && jumpFlag == false)
	{
		// リスタートカウントを数える
		++reStartCount;
		// リスタートカウントが一定数を超えたら
		if (reStartCount >= RestartTime)
		{
			// リスタートフラグをtrueに
			restartFlag = true;
		}
	}
	else
	{
		// 入力があったらリスタートカウントを初期化
		reStartCount = 0;
	}
}


/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
//@param _calcFixVec 移動物体の補正差分ベクトル
*/
void PlayerObject::playerCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
{
	// 速度ベクトル初期化
	_calcFixVec = Vector3::Zero;

	// Boxを利用して判定を取る用の変数計算
	float dx1 = _fixedBox.min.x - _movableBox.max.x;
	float dx2 = _fixedBox.max.x - _movableBox.min.x;
	float dy1 = _fixedBox.min.y - _movableBox.max.y;
	float dy2 = _fixedBox.max.y - _movableBox.min.y;
	float dz1 = _fixedBox.min.z - _movableBox.max.z;
	float dz2 = _fixedBox.max.z - _movableBox.min.z;

	// dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;

	// x, y, zのうち最も差が小さい軸で位置を調整
	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		// xだったらx軸方向に押し戻し
		_calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		// yだったらx軸方向に押し戻し
		_calcFixVec.y = dy;
	}
	else
	{
		// zだったらx軸方向に押し戻し
		_calcFixVec.z = dz;
	}

}

const Animation* PlayerObject::GetAnimation(PlayerState _state)
{
	// _state番目のアニメーションを返す
	return animTypes[static_cast<unsigned int>(_state)];
}

