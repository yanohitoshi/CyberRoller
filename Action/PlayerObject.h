#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "PlayerObjectStateBase.h"

// クラスの前方宣言
class SkeletalMeshComponent;
class Animation;
class BoxCollider;
class Mesh;
class SphereCollider;
enum class PlayerState;


/*
@file PlayerObject.h
@brief ゲーム中のプレイヤー
	   ゲーム中のプレイヤーの初期化と更新処理を行う
*/
class PlayerObject : public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	再利用するかフラグ
	@param	オブジェクト判別用tag
	*/
	PlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~PlayerObject();

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;
	
	/*
	@fn 入力処理
	@brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
	*/
	void GameObjectInput(const InputState& _keyState)override;
	
	/*
	@fn めり込み判定
	*/
	void FixCollision(AABB& myAABB, const AABB& pairAABB);
	
	/*
	@fn 押し戻し処理
	*/
	void playerCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox,Vector3& _calcFixVec);
	
	/*
	@fn 前方ベクトルを用いてキャラクターを回転させる関数
	*/
	void RotateToNewForward(const Vector3& forward);


	//----------------------getter群------------------------------//
	// ※減らせるかもしれない

	/*
	@fn SkeletalMeshComponentをstateに渡す関数
	@return SkeletalMeshComponent　SkeletalMeshComponentのポインタを返す
	*/
	SkeletalMeshComponent* GetSkeletalMeshComponent() { return skeltalMeshComponent; }

	/*
	@fn Animationを返す関数
	@return Animation Animationのポインタを返す
	*/
	const Animation* GetAnimation(PlayerState _state);

	// 定数であるグラビティ（重力）を他のCPPで見るためのgetter
	static const float GetGravity() { return Gravity; }


	// 着地effect側で使用するフラグ用のgetter
	static bool GetChackJumpFlag() { return chackJumpFlag; }
	static bool GetChackIsJumpingFlag() { return chackIsJumping; }

	// 戻り値→Vector3
	Vector3 GetForwardVec() { return forwardVec; }
	Vector3 GetRightVec() { return rightVec; }
	Vector3 GetCharaForwardVec() { return charaForwardVec;	}
	Vector3 GetRotateVec() { return rotateVec; }
	Vector3 GetVelocity() { return velocity; }
	Vector3 GetRespownPos() { return respownPos; }

	// 戻り値→const float
	const float GetDeadSpace() { return DeadSpace; }
	const float GetFirstMovePower() { return FirstMovePower; }
	const float GetMovePower() { return MovePower; }
	const float GetAirMovePower() { return AirMovePower; }
	const float GetFirstJumpPower() { return FirstJumpPower; }
	const float GetDecelerationForce() { return DecelerationForce; }

	// 戻り値→float
	float GetMoveSpeed() { return moveSpeed; }
	float GetJumpPower() { return jumpPower; }

	// 戻り値→int
	int GetTurnDelayCount() { return turnDelayCount; }

	// 戻り値→bool
	bool GetOnGround() { return onGround; }
	bool GetJumpFlag() { return jumpFlag; }
	bool GetSwitchJumpFlag() { return switchJumpFlag; }
	bool GetIsAvailableJumpKey() { return isAvailableJumpKey; }
	bool GetInputFlag() { return inputFlag; }
	bool GetRunFlag() { return runFlag; }
	bool GetDeadFlag() { return deadFlag; };
	bool GetRespawnFlag() { return respawnFlag; };
	bool GetIsAvailableInput() { return isAvailableInput; };
	bool GetIsHitWall() { return isHitWall; };

	// シーン遷移時に使うフラグのgetter
	bool GetClearFlag() { return clearFlag; }
	bool GetNextSceneFlag() { return nextSceneFlag; }
	bool GetReStartFlag() { return reStartFlag; }

	// 戻り値→int
	int GetJumpFrameCount() { return jumpFrameCount; }

	// 戻り値→PlayerState
	PlayerState GetNowState() { return nowState; }

	//---------------------------setter群------------------------------//
	// ※減らせるかもしれない
	// 引数→Vector3
	void SetCharaForwardVec(Vector3 _charaForwardVec) { charaForwardVec = _charaForwardVec; }
	void SetVelocity(Vector3 _velocity) { velocity = _velocity; }
	void SetRespownPos(Vector3 _respownPos) { velocity = _respownPos; }

	// 引数→float
	void SetMoveSpeed(float _moveSpeed) { moveSpeed = _moveSpeed; }

	// 引数→int
	void SetTurnDelayCount(bool _turnDelayCount) { turnDelayCount = _turnDelayCount; }

	// 引数→bool
	void SetJumpFlag(bool _jumpFlag) { jumpFlag = _jumpFlag; }
	void SetSwitchJumpFlag(bool _switchJumpFlag) { switchJumpFlag = _switchJumpFlag; }
	void SetIsAvailableJumpKey(bool _isAvailableJumpKey) { isAvailableJumpKey = _isAvailableJumpKey; }
	void SetJumpPower(float _jumpPower) { jumpPower = _jumpPower; }
	void SetInputFlag(bool _inputFlag) { inputFlag = _inputFlag; }
	void SetRunFlag(bool _runFlag) { runFlag = _runFlag; }
	void SetJumpFrameCount(bool _jumpFrameCount) { jumpFrameCount = _jumpFrameCount; }
	void SetDeadFlag(bool _deadFlag) { deadFlag = _deadFlag; }
	void SetRespawnFlag(bool _respawnFlag) { respawnFlag = _respawnFlag; }
	void SetIsAvailableInput(bool _isAvailableInput) { isAvailableInput = _isAvailableInput; }
	void SetIsHitWall(bool _isHitWall) { isHitWall = _isHitWall; }




private:

	/*
	@fn クリアしている状態かをチェックする関数
	*/
	void ClearChack(Tag _tag);

	//----------------Component系Class変数--------------------//
	// 3Dモデルの描画を行うクラス
	SkeletalMeshComponent* skeltalMeshComponent;
	// Meshの読み込みを行うクラス
	Mesh* mesh;
	// AABBの当たり判定を行うクラス
	BoxCollider* boxCollider;
	// 球体の当たり判定を行うクラス
	SphereCollider* groundChackSphereCol;
	//--------------------------------------------------------//

	//----------------private関数群---------------------------//
	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/	
	void OnCollision(const GameObject& _hitObject)override;

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数(足元判定用)
	@param	当たったGameObject
	*/
	void OnCollisionGround(const GameObject& _hitObject);

	//--------------------------------------------------------//
	
	//--------------------static変数群------------------------//
	// 最終ステージ用のクリアフラグ
	bool clearFlag;
	// 最終ステージ以外での次のシーンへ遷移するフラグ
	bool nextSceneFlag;
	// 一定時間以上入力がなかった際にタイトルへ戻るフラグ
	bool reStartFlag;
	// 着地effectを発生させる際に使用するフラグ
	// JumpFlagチェック用
	static bool chackJumpFlag;
	// isJumpingチェック用（ジャンプ中かどうか）
	static bool chackIsJumping;
	//重力
	static const float Gravity;
	//--------------------------------------------------------//
	
	//------------------------定数群--------------------------//
	// リスタートをかける時間
	const int RestartTime;
	// 入力値のdeadスペース
	const float DeadSpace;
	//加速度の定数
	const float MovePower;
	// 空中での加速定数
	const float AirMovePower;
	// 減速する力
	const float DecelerationForce;
	// 初速度
	const float FirstMovePower;
	//初期ジャンプ力定数
	const float FirstJumpPower;
	// プレイヤーが落下したかどうかを判定する位置
	//（※現状ステージに落下がないのでもしすり抜けてしまった場合）
	const float FallPpsitionZ;
	// 生成されるときのポジションをずらす
	const float FirstPositionZ;
	// ひるむ速度定数
	const float FlinchSpeed;

	//--------------------------------------------------------//
	//--------------------------変数群------------------------//
	//押し戻しに使うプレイヤーのAABB
	AABB playerBox;
	//右方向ベクトル
	Vector3 rightVec;
	//キャラクターの前方ベクトル
	Vector3 charaForwardVec;
	//方向に合わせて回転させるためのベクトル
	Vector3 rotateVec;
	// 生成されたときのポジションを保存するためのvector3変数
	Vector3 firstPos;
	// リスポーンする場所
	Vector3 respownPos;
	// 他のオブジェクトから押されている時の速度
	Vector3 pushedVelocity;

	// 死んだ際にすぐリスポーンさせないためのカウント
	int respawnCount;
	// 入力がない間カウント
	int reStartCount;
	//ジャンプボタンが押されている間のフレームカウント
	int jumpFrameCount;
	// 振り返りディレイ用カウント変数
	int turnDelayCount;

	// 速度
	float moveSpeed;
	//ジャンプ力
	float jumpPower;

	//入力があったかどうか判定するためのフラグ
	bool inputFlag;
	//引き続きジャンプボタンが利用可能かフラグ
	bool isAvailableJumpKey;
	//ジャンプできるかフラグ
	bool jumpFlag;
	//ジャンプスイッチを押したかどうか
	bool switchJumpFlag;
	//接地フラグ
	bool onGround;
	//走り状態かどうか
	bool runFlag;
	// 入力が可能かどうか
	bool isAvailableInput;
	// ダウン状態かどうか
	bool downFlag;
	// ダウン時コンティニュー選択でYESが選択されたかどうか
	bool downUpFlag;
	// ダウン時コンティニュー選択でNOが選択されたかどうか
	bool downOverFlag;
	// リスポーン用フラグ
	bool respawnFlag;
	// dead状態かそうじゃないか確認用フラグ
	bool deadFlag;
	// 壁と押し戻しを行ったか
	bool isHitWall;
	
	// 今のプレーヤーのstate状態を保存するための変数
	PlayerState nowState;
	// 変更された次のプレーヤーのstate状態を保存するための変数
	PlayerState nextState;

	//----------------------可変長配列群----------------------//
	// Animationプール
	std::vector<const Animation*> animTypes;
	// stateプール
	std::vector<class PlayerObjectStateBase*> statePools;
	//--------------------------------------------------------//
};

