//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include <string>
#include "PlayerObject.h"
#include "SkeletalMeshComponent.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "MainCameraObject.h"
#include "Renderer.h"
#include "Skeleton.h"
#include "Animation.h"
#include "InputSystem.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "CountDownFont.h"
#include "PlayerSandSmokeMakeManager.h"
#include "LandingEffectManager.h"
#include "PlayerTransformEffectManager.h"
#include "PlayerKnockBackEffectManager.h"
#include "PlayerDeadEffectManager.h"
#include "PlayerObjectStateIdle.h"
#include "PlayerObjectStateRun.h"
#include "PlayerObjectStateDead.h"
#include "PlayerObjectStateJumpEndToIdle.h"
#include "PlayerObjectStateJunpEndToRun.h"
#include "PlayerObjectStateJumpLoop.h"
#include "PlayerObjectStateJumpStart.h"
#include "PlayerObjectStateJumpAttack.h"
#include "PlayerObjectStateJumpAttackEnd.h"
#include "PlayerObjectStateDownLoop.h"
#include "PlayerObjectStateDownOver.h"
#include "PlayerObjectStateDownStart.h"
#include "PlayerObjectStateDownUp.h"
#include "PlayerObjectStateRespown.h"
#include "PlayerObjectStateRunStart.h"
#include "PlayerObjectStateRunStop.h"
#include "PlayerObjectStateRunTurn.h"
#include "PlayerObjectStateIdlingDance.h"
#include "PlayerObjectStateKnockBack.h"
#include "PlayerObjectStateFallDead.h"
#include "PlayerObjectStateExplosionBlowAway.h"
#include "JumpAttackPlayerObject.h"

#include "ParticleComponent.h"

// 定数と静的メンバーの初期化
const float PlayerObject::Gravity = 4500.0f;

/*
@fn コンストラクタ
@param	ポジション
@param	再利用するかフラグ
@param	オブジェクト判別用tag
*/
PlayerObject::PlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
	, playerBox({ Vector3::Zero,Vector3::Zero })
	, FirstJumpPower(1200.0f)
	, MovePower(60.0f)
	, FirstMovePower(20.0f)
	, AirMovePower(30.0f)
	, FirstAirMovePower(300.0f)
	, DecelerationForce(100.0f)
	, DeadSpace(0.3f)
	, FallPpsitionZ(-500.0f)
	, FirstPositionZ(2000.0f)
	, RestartTime(10000)
{

	//GameObjectメンバ変数の初期化
	state = Active;
	scale = Vector3(1.5f, 1.5f, 1.5f);
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
	// 接地フラグ初期化
	onGround = false;
	// 入力フラグ初期化
	inputFlag = false;
	// 入力可能かフラグ初期化
	isAvailableInput = true;

	// ジャンプフラグ初期化
	jumpFlag = false;
	// ジャンプが利用可能かフラグ初期化
	isAvailableJumpKey = false;
	isAvailableJumpAttck = false;
	isJumpAttck = false;
	isSelectingTargetEnemy = false;
	isJumpAttackSuccess = false;
	// 前方ベクトル初期化
	forwardVec = Vector3(1.0f, 0.0f, 0.0f);
	// キャラクターの前方ベクトル初期化
	charaForwardVec = Vector3(1.0f, 0.0f, 0.0f);
	// 右方向ベクトル初期化
	rightVec = Vector3(0.0f,1.0f,0.0f);
	// 回転ベクトル初期化
	rotateVec = Vector3(0.0f, 0.0f, 0.0f);
	// 
	hitKnockBackObjectPosition = Vector3::Zero;
	// 
	attackTarget = nullptr;

	// 押し出されたときにその速度を保存しキャラクターの速度に足すためのベクトル初期化
	pushedVelocity = Vector3::Zero;

	// ジャンプ中のフレームをカウントする用のカウント初期化
	jumpFrameCount = 0;

	// ジャンプswitch用フラグ初期化
	switchJumpFlag = false;

	isHitExplosion = false;

	// カウント初期化
	reStartCount = 0;
	turnDelayCount = 0;

	//モデル描画用のコンポーネント
	skeltalMeshComponent = new SkeletalMeshComponent(this);
	//Rendererクラス内のMesh読み込み関数を利用してMes hをセット(.gpmesh)
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Player/PlayerModel/SK_Rob.gpmesh"));
	//Rendererクラス内のSkeletonデータ読み込み関数を利用してSkeletonをセット(.gpskel)
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton("Assets/Model/Player/PlayerModel/SK_Rob.gpskel"));
	// mesh情報を取得
	mesh = skeltalMeshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	//Rendererクラス内のSkeletonデータ読み込み関数を利用してAnimationをセット(.gpanim)
	//アニメ―ション用の可変長配列をリサイズ
	animTypes.resize(static_cast<unsigned int>(PlayerState::PLAYER_STATE_NUM));

	//-----------アニメーションを読み込み-----------------//
	// アイドリングアニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_IDLE)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Happy_Idle_Anim.gpanim", true);
	// 一定以上入力がなかった際のアイドリングアニメーション（ダンス）
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_IDLE_DANCE)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Tut_Hip_Hop_Dance.gpanim", true);
	// 走りアニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_RUN)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Running.gpanim", true);
	// 走りだしアニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_RUN_START)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Idle_To_Sprint_2.gpanim", false);
	// 走り終わりアニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_RUN_STOP)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Run_To_Stop.gpanim", false);
	// 走り中の切り替えしアニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_RUN_TURN)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Change_Direction.gpanim", false);
	// 敵に当たった際のノックバックアニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_KNOCKBACK)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Receiving_An_Uppercut.gpanim", false);
	// ジャンプループアニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_JUMPLOOP)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Floating.gpanim", true);
	// ジャンプ開始アニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_JUMPSTART)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Jump_up.gpanim", false);
	// 次の状態が待機の時の着地アニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Landing.gpanim", false);
	// 次の状態が走りの時の着地アニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_JUMPEND_TO_RUN)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Falling_To_Roll.gpanim", false);
	// タイムオーバー時のアニメーション（start）
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_DOWNSTART)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Praying_down.gpanim", false);
	// タイムオーバー時のアニメーション（loop）
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_DOWN_LOOP)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Praying_Idle.gpanim", false);
	// タイムオーバー時のアニメーション（コンティニュー）
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_DOWN_UP)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Praying_up.gpanim", false);
	// タイムオーバー時のアニメーション（ゲームオーバー）
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_DOWN_OVER)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/over_down.gpanim", false);
	// 死亡時のアニメーション
	animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_DEAD)] = RENDERER->GetAnimation("Assets/Model/Player/PlayerAnimation/Stunned.gpanim", false);

	//anim変数を速度1.0fで再生
	skeltalMeshComponent->PlayAnimation(animTypes[static_cast<unsigned int>(PlayerState::PLAYER_STATE_IDLE)], 1.0f);


	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = skeltalMeshComponent->GetMesh();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this,PhysicsTag::PLAYER_TAG, GetOnCollisionFunc());
	playerBox = mesh->GetBox();
	playerBox = { Vector3(-10.0f,-10.0f,0.0f),Vector3(50.0f,10.0f,179.0f) };
	boxCollider->SetObjectBox(playerBox);

	//接地判定用のsphereCollider
	groundCheckSphereCol = new SphereCollider(this, PhysicsTag::GROUND_CHECK_TAG, std::bind(&PlayerObject::OnCollisionGround, this, std::placeholders::_1,std::placeholders::_2));
	Sphere groundCheckSphere = { Vector3(0.0f,0.0f,0.0f),8.0f };
	groundCheckSphereCol->SetObjectSphere(groundCheckSphere);

	//ジャンプ攻撃判定用のsphereCollider
	jumpAttackSphereCol = new SphereCollider(this, PhysicsTag::ATTACK_RANGE_TAG, std::bind(&PlayerObject::OnCollisionAttackTarget, this, std::placeholders::_1,std::placeholders::_2));
	Sphere jumpAttackSphere = { Vector3(0.0f,0.0f,0.0f),800.0f };
	jumpAttackSphereCol->SetObjectSphere(jumpAttackSphere);

	// プレイヤーに必要なeffectを持たせる
	new PlayerSandSmokeMakeManager(this);
	new LandingEffectManager(this);
	new PlayerTransformEffectManager(this);
	new PlayerKnockBackEffectManager(this);
	new PlayerDeadEffectManager(this);

	// stateをstatePool用マップに追加
	AddStatePoolMap(new PlayerObjectStateIdle, PlayerState::PLAYER_STATE_IDLE);
	AddStatePoolMap(new PlayerObjectStateIdlingDance, PlayerState::PLAYER_STATE_IDLE_DANCE);
	AddStatePoolMap(new PlayerObjectStateRun, PlayerState::PLAYER_STATE_RUN);
	AddStatePoolMap(new PlayerObjectStateRunStart, PlayerState::PLAYER_STATE_RUN_START);
	AddStatePoolMap(new PlayerObjectStateRunStop, PlayerState::PLAYER_STATE_RUN_STOP);
	AddStatePoolMap(new PlayerObjectStateRunTurn, PlayerState::PLAYER_STATE_RUN_TURN);
	AddStatePoolMap(new PlayerObjectStateKnockBack, PlayerState::PLAYER_STATE_KNOCKBACK);
	AddStatePoolMap(new PlayerObjectStateJumpLoop, PlayerState::PLAYER_STATE_JUMPLOOP);
	AddStatePoolMap(new PlayerObjectStateJumpStart, PlayerState::PLAYER_STATE_JUMPSTART);
	AddStatePoolMap(new PlayerObjectStateJumpEndToIdle, PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE);
	AddStatePoolMap(new PlayerObjectStateJunpEndToRun, PlayerState::PLAYER_STATE_JUMPEND_TO_RUN);
	AddStatePoolMap(new PlayerObjectStateJumpAttack, PlayerState::PLAYER_STATE_JUMP_ATTACK);
	AddStatePoolMap(new PlayerObjectStateJumpAttackEnd, PlayerState::PLAYER_STATE_JUMP_ATTACK_END);
	AddStatePoolMap(new PlayerObjectStateDownStart, PlayerState::PLAYER_STATE_DOWNSTART);
	AddStatePoolMap(new PlayerObjectStateDownLoop, PlayerState::PLAYER_STATE_DOWN_LOOP);
	AddStatePoolMap(new PlayerObjectStateDownUp, PlayerState::PLAYER_STATE_DOWN_UP);
	AddStatePoolMap(new PlayerObjectStateDownOver, PlayerState::PLAYER_STATE_DOWN_OVER);
	AddStatePoolMap(new PlayerObjectStateDead, PlayerState::PLAYER_STATE_DEAD);
	AddStatePoolMap(new PlayerObjectStateFallDead, PlayerState::PLAYER_STATE_FALL_DEAD);
	AddStatePoolMap(new PlayerObjectStateRespown, PlayerState::PLAYER_STATE_RESPAWN);
	AddStatePoolMap(new PlayerObjectStateExplosionBlowAway, PlayerState::PLAYER_STATE_BLOWAWAY);

	// stateを初期化
	nowState = PlayerState::PLAYER_STATE_IDLE;
	nextState = PlayerState::PLAYER_STATE_IDLE;

	jumpAttackPlayerObject = new JumpAttackPlayerObject(this,Vector3(50.0f, 50.0f, 50.0f), JUMP_ATTACK_PLAYER);

}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
PlayerObject::~PlayerObject()
{
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_IDLE);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_IDLE_DANCE);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_RUN);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_RUN_START);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_RUN_STOP);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_RUN_TURN);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_KNOCKBACK);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_JUMPLOOP);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_JUMPSTART);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_JUMPEND_TO_RUN);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_JUMP_ATTACK);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_JUMP_ATTACK_END);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_DOWNSTART);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_DOWN_LOOP);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_DOWN_UP);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_DOWN_OVER);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_DEAD);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_FALL_DEAD);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_RESPAWN);
	RemoveStatePoolMap(PlayerState::PLAYER_STATE_BLOWAWAY);
	ClearStatePoolMap();
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void PlayerObject::UpdateGameObject(float _deltaTime)
{
	if (FallPpsitionZ >= position.z)
	{
		nextState = PlayerState::PLAYER_STATE_FALL_DEAD;
	}

	if (isHitEnemy && nowState != PlayerState::PLAYER_STATE_DEAD)
	{
		nextState = PlayerState::PLAYER_STATE_KNOCKBACK;
	}

	if (isHitExplosion && nowState != PlayerState::PLAYER_STATE_DEAD)
	{
		nextState = PlayerState::PLAYER_STATE_BLOWAWAY;
	}

	// ステート外部からステート変更があったか？
	if (nowState != nextState)
	{
		//マップの中に追加するアクターのコンテナがあるかどうかを調べる
		auto state = statePoolMap.find(nextState);
		if (state != statePoolMap.end())
		{
			statePoolMap[nextState]->Enter(this, _deltaTime);
		}

		nowState = nextState;
		return;
	}

	// ステート実行
	//マップの中に追加するアクターのコンテナがあるかどうかを調べる
	auto state = statePoolMap.find(nowState);
	if (state != statePoolMap.end())
	{
		nextState = statePoolMap[nowState]->Update(this, _deltaTime);
	}

	// プレイヤー以外の影響でポジションが変更された時用
	position = (position + pushedVelocity * _deltaTime );
	// ポジションをセット
	SetPosition(position);

	// ステート内部からステート変更あったか？
	if (nowState != nextState)
	{
		auto state = statePoolMap.find(nextState);
		if (state != statePoolMap.end())
		{
			statePoolMap[nextState]->Enter(this, _deltaTime);
		}
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
		mainCamera->ResetCamera();
	}

	// RENDERERに現在のポジションを送る
	RENDERER->SetPlayerPositon(position);
	
	// フレームの最後に接地判定と押されている速度を初期化
	onGround = false;
	isHitEnemy = false;
	pushedVelocity = Vector3::Zero;
	isSelectingTargetEnemy = false;
	attackTarget = nullptr;

	// ステータスが走りはじめもしくはランループだったら切り替えしディレイカウントをカウントする
	// 連続で切り替えしアニメーションに入らないように抑制をかけるため
	if (nowState == PlayerState::PLAYER_STATE_RUN_START || nowState == PlayerState::PLAYER_STATE_RUN)
	{
		// カウントを数える
		++turnDelayCount;
	}

	// 一定時間放置によるゲームをリセットするかチェック
	CheckRestartProcess();
}

/*
@fn 入力処理
@brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
*/
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
	auto state = statePoolMap.find(nowState);
	if (state != statePoolMap.end())
	{
		statePoolMap[nowState]->Input(this, _keyState);
	}

	if (nowState == PlayerState::PLAYER_STATE_JUMP_ATTACK)
	{
		skeltalMeshComponent->SetVisible(false);
	}
	else
	{
		skeltalMeshComponent->SetVisible(true);
	}
}


/*
@fn めり込み判定
@param	myAABB 自分のAABB
@param	pairAABB 当たった相手のAABB
@param	_hitObjectTag ヒットしたオブジェクトのタグ
*/
void PlayerObject::FixCollision(AABB& myAABB, const AABB& pairAABB,Tag _hitObjectTag)
{
	// 仮速度変数
	Vector3 ment = Vector3::Zero;

	if (_hitObjectTag == Tag::ENEMY || _hitObjectTag == Tag::PUSH_BOARD)
	{
		HorizontalPlayerCalcCollisionFixVec(myAABB, pairAABB, ment);
	}
	else
	{
		// プレイヤーの押し戻し計算
		PlayerCalcCollisionFixVec(myAABB, pairAABB, ment);
	}

	// 押し戻し計算を考慮しポジションを更新
	SetPosition(position + ment);
}

/*
@brief 前方ベクトルを用いてキャラクターを回転させる関数
@param	forward 前方ベクトル
*/
void PlayerObject::RotateToNewForward(const Vector3& forward)
{
	// X軸ベクトル(1,0,0)とforwardの間の角度を求める
	float dot = Vector3::Dot(Vector3::UnitX, forward);
	float angle = Math::Acos(dot);
	// 下向きだった場合
	if (dot > 0.9f)
	{
		SetRotation(Quaternion::Identity);
	}
	// 上向きだった場合
	else if (dot < -0.9f)
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

/*
@fn クリアしている状態かをチェックする関数
@param	_tag チェックするオブジェクトのタグ
*/
void PlayerObject::ClearCheck(Tag _tag)
{
	// フラグ検索用可変長配列を生成
	std::vector<GameObject*> switches;

	// クリア条件用スイッチを探して格納
	switches = GameObject::FindGameObject(Tag::CLEAR_SCENE_SWITCH);

	// スイッチの状態確認関数呼び出し
	SwitchCheckProcess(switches);

}

/*
@fn クリアに必要なスイッチをチェックする関数
@param	_checkVector チェックするスイッチが格納されている可変長コンテナ
*/
void PlayerObject::SwitchCheckProcess(std::vector<GameObject*> _checkVector)
{
	// スイッチの総数カウント初期化
	int switchCount = 0;
	// ONになっているスイッチ総数カウント初期化
	int flagCount = 0;

	// スイッチの総数とONになっているスイッチの総数を数える
	for (auto itr : _checkVector)
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

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
@param	当たったGameObjectの当たり判定タグ
*/
void PlayerObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// Hitしたオブジェクトのタグを取得
	Tag hitObjectTag = _hitObject.GetTag();

	// 空中でかつ押し戻しを行うオブジェクトだったら
	if (onGround == false && _hitObject.GetisPushBackToPlayer())
	{
		// プレイヤーのワールドボックスを取得
		playerBox = boxCollider->GetWorldBox();
		// 押し戻し用関数へ渡す
		FixCollision(playerBox, _hitObject.GetAabb(), hitObjectTag);
	}

	// 当たったオブジェクトが敵だったら
	if (hitObjectTag == Tag::ENEMY && _physicsTag == PhysicsTag::ENEMY_TAG)
	{
		// ジャンプアタック状態でなかったら
		if (!isJumpAttck)
		{
			isHitEnemy = true;
			hitKnockBackObjectPosition = _hitObject.GetPosition();
		}
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
		ClearCheck(hitObjectTag);
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

	if (_physicsTag == PhysicsTag::EXPLOSION_AREA_TAG && !isHitExplosion)
	{
		// 死亡フラグをtureにセット
		isHitExplosion = true;
		hitKnockBackObjectPosition = _hitObject.GetPosition();
	}
}

/*
@fn 足元判定用当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
@param	当たったGameObjectの当たり判定タグ
*/
void PlayerObject::OnCollisionGround(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// 接地判定を行うオブジェクトだったら
	if (_hitObject.GetIsCheckGroundToPlayer())
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

/*
@fn 当たり判定が行われHitした際に呼ばれる関数(ジャンプ攻撃を行うエネミーとの判定を取る)
@param	当たったGameObject
@param	当たったGameObjectの当たり判定タグ
*/
void PlayerObject::OnCollisionAttackTarget(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	if (_hitObject.GetState() != State::Active)
	{
		return;
	}

	if (attackTarget != nullptr)
	{
		// ヒットしたEnemyのポジションと距離を計算
		Vector3 hitEnemyPosition = _hitObject.GetPosition();
		Vector3 hitEnemyDistance = hitEnemyPosition - position;
		hitEnemyDistance.z = 0.0f;
		
		// select中のEnemyのポジションと距離を計算
		Vector3 selectEnemyPosition = attackTarget->GetPosition();
		Vector3 selectEnemyDistance = selectEnemyPosition - position;
		selectEnemyDistance.z = 0.0f;
		
		// 距離をベクトルの長さで比較選択している敵よりも新しい敵の方が近かったら更新
		if (hitEnemyDistance.Length() < selectEnemyDistance.Length())
		{
			attackTarget = FindTargetEnemy(_hitObject);
		}
	}
	else
	{
		attackTarget = FindTargetEnemy(_hitObject);
	}

	isSelectingTargetEnemy = true;
}

/*
@brief ステートプール用マップにステートクラスを追加する関数
@param	_state 追加するステートクラスのポインタ
@param	_stateTag 鍵となるタグ
*/
void PlayerObject::AddStatePoolMap(PlayerObjectStateBase* _state, PlayerState _stateTag)
{
	//マップの中に追加するアクターのコンテナがあるかどうかを調べる
	auto stateMaps = statePoolMap.find(_stateTag);

	//あるとき
	if (stateMaps != statePoolMap.end())
	{
		return;
	}
	else //ないとき
	{
		statePoolMap[_stateTag] = _state;
	}
}

/*
@brief ステートプール用マップからステートクラスを削除する関数
@param	_stateTag 鍵となるタグ
*/
void PlayerObject::RemoveStatePoolMap(PlayerState _stateTag)
{
	delete statePoolMap[_stateTag];
}

/*
@brief ステートプール用マップをクリアする
*/
void PlayerObject::ClearStatePoolMap()
{
	statePoolMap.clear();
}

/*
@fn スイッチジャンプを使用可能にする関数
*/
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

/*
@fn リスタートチェック関数
*/
void PlayerObject::CheckRestartProcess()
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
@brief	攻撃対象の敵を探す
@param	_hitObject ヒットしたオブジェクト
@return GameObject* 探し出したオブジェクト
*/
GameObject* PlayerObject::FindTargetEnemy(const GameObject& _hitObject)
{
	// 判定内に入った敵オブジェクトのポインタを取得
	std::vector<GameObject*>targetEnemies = FindGameObject(_hitObject.GetTag());
	GameObject* selectEnemy = nullptr;
	for (auto itr : targetEnemies)
	{
		if (itr->GetObjectId() == _hitObject.GetObjectId())
		{
			selectEnemy = itr;
		}
	}
	return selectEnemy;
}

/*
@fn 押し戻し処理
@brief	x,y,z軸で押し戻し処理を行う
@param	_movableBox 移動オブジェクトのAABB
@param	_fixedBox 当たったオブジェクトのAABB
@param	_calcFixVec 速度差分ベクトル
*/
void PlayerObject::PlayerCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
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

/*
@fn 押し戻し処理
@brief	x,y軸で押し戻し処理を行う
@param	_movableBox 移動オブジェクトのAABB
@param	_fixedBox 当たったオブジェクトのAABB
@param	_calcFixVec 速度差分ベクトル
*/
void PlayerObject::HorizontalPlayerCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
{
	// 速度ベクトル初期化
	_calcFixVec = Vector3::Zero;

	// Boxを利用して判定を取る用の変数計算
	float dx1 = _fixedBox.min.x - _movableBox.max.x;
	float dx2 = _fixedBox.max.x - _movableBox.min.x;
	float dy1 = _fixedBox.min.y - _movableBox.max.y;
	float dy2 = _fixedBox.max.y - _movableBox.min.y;

	// dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;

	// x, y, zのうち最も差が小さい軸で位置を調整
	if (Math::Abs(dx) <= Math::Abs(dy))
	{
		// xだったらx軸方向に押し戻し
		_calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx))
	{
		// yだったらx軸方向に押し戻し
		_calcFixVec.y = dy;
	}
}

/*
@fn Animationのgetter関数
@param _state 現在のプレイヤーのステータス
@return Animation Animationクラスのポインタを返す
*/
const Animation* PlayerObject::GetAnimation(PlayerState _state)
{
	// _state番目のアニメーションを返す
	return animTypes[static_cast<unsigned int>(_state)];
}