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

// 定数と静的メンバーの初期化
const float PlayerObject::Gravity = 4500.0f;
bool PlayerObject::clearFlag = false;
bool PlayerObject::nextSceneFlag = false;
bool PlayerObject::reStartFlag = false;
bool PlayerObject::chackJumpFlag = false;
bool PlayerObject::chackIsJumping = false;

PlayerObject::PlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
	, playerBox({ Vector3::Zero,Vector3::Zero })
	, FirstJumpPower(1200.0f)
	, MovePower(90.0f)
	, FirstMovePower(0.0f)
	, AirMovePower(60.0f)
	, DecelerationForce(80.0f)
	, DeadSpace(0.1f)
	, FallPpsitionZ(-500.0f)
	, FirstPositionZ(5000.0f)
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
	//リスポ－ンflag初期化
	respawnFlag = false;
	// リスポ－ンflag位置初期化
	respownPos = _pos;

	// 前方ベクトル初期化
	forwardVec = Vector3(0.0f, 0.0f, 0.0f);
	// キャラクターの前方ベクトル初期化
	charaForwardVec = Vector3(1.0f, 0.0f, 0.0f);
	// 前フレームでのキャラクターの前方ベクトル保存用ベクトル初期化
	tmpCharaForwardVec = Vector3(0.0f, 0.0f, 0.0f);
	// 右方向ベクトル初期化
	rightVec = Vector3(0.0f,0.0f,0.0f);
	// 回転ベクトル初期化
	rotateVec = Vector3(0.1f, 0.0f, 0.0f);
	// 回転ベクトルNormalize
	rotateVec.Normalize();
	// 押し出されたときにその速度を保存しキャラクターの速度に足すためのベクトル初期化
	pushedVelocity = Vector3::Zero;

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
	// ジャンプ中かどうかフラグ初期化
	isJumping = false;
	// ジャンプが利用可能かフラグ初期化
	isAvailableJumpKey = false;
	// ジャンプ中のフレームをカウントする用のカウント初期化
	jumpFrameCount = 0;

	// ジャンプswitch用フラグ初期化
	switchJumpFlag = false;

	//clear判定フラグ
	clearFlag = false;
	reStartCount = 0;

	// ダウン・コンティニュー・deadフラグ初期化
	downFlag = false;
	downUpFlag = false;
	downOverFlag = false;
	deadFlag = false;

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
	boxCollider = new BoxCollider(this,ColliderComponent::PlayerTag, GetOnCollisionFunc());
	playerBox = mesh->GetBox();
	playerBox = { Vector3(-60.0f,-10.0f,0.0f),Vector3(60.0f,10.0f,179.0f) };
	boxCollider->SetObjectBox(playerBox);

	//接地判定用のsphereCollider
	groundChackSphereCol = new SphereCollider(this, ColliderComponent::GroundCheckTag, std::bind(&PlayerObject::OnCollisionGround, this, std::placeholders::_1));
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
	statePools.push_back(new PlayerObjectStateRespown);

	// stateを初期化
	nowState = PlayerState::PLAYER_STATE_IDLE;
	nextState = PlayerState::PLAYER_STATE_IDLE;
}

PlayerObject::~PlayerObject()
{
	// 静的フラグの初期化
	clearFlag = false;
	nextSceneFlag = false;
	reStartFlag = false;
	chackJumpFlag = false;
	chackIsJumping = false;
}

void PlayerObject::UpdateGameObject(float _deltaTime)
{

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

	if (respawnFlag == true)
	{
		mainCamera->ReSetYaw();
	}

	// RENDERERに現在のポジションを送る
	RENDERER->SetPlayerPositon(position);
	
	// フレームの最後に接地判定と押されている速度を初期化
	onGround = false;
	pushedVelocity = Vector3::Zero;

	if (nowState == PlayerState::PLAYER_STATE_RUN_START || nowState == PlayerState::PLAYER_STATE_RUN)
	{
		++turnDelayCount;
	}

}

void PlayerObject::GameObjectInput(const InputState& _keyState)
{

	// スタート時のカウントダウンが終わったら入力可能状態にする
	if (CountDownFont::countStartFlag == true)
	{
		isAvailableInput = true;
	}
	else if (CountDownFont::countStartFlag == false || CountDownFont::timeOverFlag == true)
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
	chackIsJumping = isJumping;

	// 一定時間入力が無かったらタイトルに戻る
	if (inputFlag == false && jumpFlag == false)
	{
		++reStartCount;
		if (reStartCount >= 10000)
		{
			reStartFlag = true;
		}
	}
	else
	{
		reStartCount = 0;
	}

}


/*
@fn めり込み判定と押し戻し
*/
void PlayerObject::FixCollision(AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag)
{
	if (_pairTag == Tag::GROUND || _pairTag == Tag::WALL || _pairTag == Tag::FIRST_MOVE_WALL ||
		_pairTag == Tag::SECOND_MOVE_WALL || _pairTag == Tag::TUTORIAL_MOVE_WALL ||
		_pairTag == Tag::NEXT_SCENE_MOVE_WALL || _pairTag == Tag::CLEAR_SCENE_MOVE_WALL ||
		_pairTag == Tag::MOVE_GROUND || _pairTag == Tag::PUSH_BOARD || _pairTag == Tag::PUSH_BOX ||
		_pairTag == Tag::TUTORIAL_SWITCH || _pairTag == Tag::FIRST_SWITCH ||
		_pairTag == Tag::SECOND_SWITCH || _pairTag == Tag::NEXT_SCENE_SWITCH ||
		_pairTag == Tag::CLEAR_SCENE_SWITCH)
	{
		Vector3 ment = Vector3(0, 0, 0);
		playerCalcCollisionFixVec(myAABB, pairAABB, ment, _pairTag);
		SetPosition(position + ment);
	}

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

void PlayerObject::OnCollision(const GameObject& _hitObject)
{
	if (onGround == false)
	{
		playerBox = boxCollider->GetWorldBox();
		FixCollision(playerBox, _hitObject.aabb, _hitObject.GetTag());
	}

	Tag hitTag = _hitObject.GetTag();

	if (hitTag == Tag::WALL || hitTag == Tag::FIRST_MOVE_WALL || hitTag == Tag::SECOND_MOVE_WALL || 
		hitTag == Tag::TUTORIAL_MOVE_WALL || hitTag == Tag::NEXT_SCENE_MOVE_WALL || hitTag == Tag::CLEAR_SCENE_MOVE_WALL)
	{
		if (velocity.x >= 1000.0f || velocity.y >= 1000.0f ||
			velocity.x <= -1000.0f || velocity.y <= -1000.0f)
		{
			isHitWall = true;
		}
	}
	else
	{
		isHitWall = false;
	}

	if (_hitObject.GetTag() == Tag::GROUND || _hitObject.GetTag() == Tag::MOVE_GROUND ||
		_hitObject.GetTag() == Tag::PUSH_BOARD || _hitObject.GetTag() == Tag::PUSH_BOX ||
		_hitObject.GetTag() == Tag::TUTORIAL_SWITCH || _hitObject.GetTag() == Tag::FIRST_SWITCH ||
		_hitObject.GetTag() == Tag::SECOND_SWITCH || _hitObject.GetTag() == Tag::NEXT_SCENE_SWITCH ||
		_hitObject.GetTag() == Tag::CLEAR_SCENE_SWITCH)
	{
		pushedVelocity = _hitObject.GetVelocity();
	}

	if (_hitObject.GetTag() == Tag::CLEAR_POINT)
	{
		std::vector<GameObject*> switches;
		switches = GameObject::FindGameObject(Tag::CLEAR_SCENE_SWITCH);
		int switchCount = 0;
		int flagCount = 0;
		for (auto itr : switches)
		{
			++switchCount;
			if (itr->GetSwitchFlag() == true)
			{
				++flagCount;
			}
		}

		if (flagCount == switchCount)
		{
			clearFlag = true;
		}

	}

	if (_hitObject.GetTag() == Tag::NEXT_SCENE_POINT)
	{
		std::vector<GameObject*> switches;
		switches = GameObject::FindGameObject(Tag::NEXT_SCENE_SWITCH);
		int switchCount = 0;
		int flagCount = 0;
		for (auto itr : switches)
		{
			++switchCount;
			if (itr->GetSwitchFlag() == true)
			{
				++flagCount;
			}
		}

		if (flagCount == switchCount)
		{
			nextSceneFlag = true;
		}
	}

	if (_hitObject.GetTag() == Tag::TUTORIAL_CLEAR_POINT)
	{
		std::vector<GameObject*> switches;
		switches = GameObject::FindGameObject(Tag::TUTORIAL_SWITCH);
		int switchCount = 0;
		int flagCount = 0;
		for (auto itr : switches)
		{
			++switchCount;
			if (itr->GetSwitchFlag() == true)
			{
				++flagCount;
			}
		}

		if (flagCount == switchCount)
		{
			nextSceneFlag = true;
		}
	}

	if (_hitObject.GetTag() == Tag::RESPOWN_POINT)
	{
		respownPos = Vector3::Zero;
		respownPos = _hitObject.GetPosition();
	}

	if (_hitObject.GetTag() == Tag::NEEDLE_PANEL)
	{
		deadFlag = true;
	}

}

void PlayerObject::OnCollisionGround(const GameObject& _hitObject)
{
	if (_hitObject.GetTag() == Tag::GROUND || _hitObject.GetTag() == Tag::MOVE_GROUND || 
		_hitObject.GetTag() == Tag::PUSH_BOARD || _hitObject.GetTag() == Tag::PUSH_BOX ||
		_hitObject.GetTag() == Tag::TUTORIAL_SWITCH || _hitObject.GetTag() == Tag::FIRST_SWITCH ||
		_hitObject.GetTag() == Tag::SECOND_SWITCH || _hitObject.GetTag() == Tag::NEXT_SCENE_SWITCH ||
		_hitObject.GetTag() == Tag::CLEAR_SCENE_SWITCH)
	{
		onGround = true;

		if (jumpFlag == false && onGround == true)
		{
			velocity.z = 0.0f;
			jumpFrameCount = 0;
		}

		if (jumpFlag == true)
		{
			jumpFlag = false;
			isAvailableJumpKey = true;
			jumpPower = FirstJumpPower;
		}

		switchJumpFlag = false;

	}


	if (_hitObject.GetTag() == Tag::JUMP_SWITCH && jumpFlag == false)
	{
		if (switchJumpFlag == false)
		{
			jumpFrameCount = 0;
			jumpPower = FirstJumpPower;
			switchJumpFlag = true;

		}
	}

	if (_hitObject.GetTag() == Tag::GROUND || _hitObject.GetTag() == Tag::MOVE_GROUND ||
		_hitObject.GetTag() == Tag::TUTORIAL_SWITCH || _hitObject.GetTag() == Tag::FIRST_SWITCH ||
		_hitObject.GetTag() == Tag::SECOND_SWITCH || _hitObject.GetTag() == Tag::NEXT_SCENE_SWITCH ||
		_hitObject.GetTag() == Tag::CLEAR_SCENE_SWITCH)
	{
		pushedVelocity = _hitObject.GetVelocity();
	}
}


/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
//@param _calcFixVec 移動物体の補正差分ベクトル
*/
void PlayerObject::playerCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec,const Tag& __pairTag)
{
	_calcFixVec = Vector3(0, 0, 0);

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
		_calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		_calcFixVec.y = dy;
	}
	else
	{
		_calcFixVec.z = dz;
	}

}

const Animation* PlayerObject::GetAnimation(PlayerState _state)
{
	return animTypes[static_cast<unsigned int>(_state)];
}

