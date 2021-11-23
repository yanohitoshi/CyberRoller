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
class JumpAttackPlayerObject;
class PlayerObjectStateBase;
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
	@param	_keyState 入力情報
	*/
	void GameObjectInput(const InputState& _keyState)override;
	
	/*
	@fn めり込み判定と押し戻し
	@param	myAABB 自分のAABB
	@param	pairAABB 当たった相手のAABB
	@param	_hitObjectTag ヒットしたオブジェクトのタグ
	*/
	void FixCollision(AABB& myAABB, const AABB& pairAABB,Tag _hitObjectTag);
	
	/*
	@fn 押し戻し処理
	@brief	x,y,z軸で押し戻し処理を行う
	@param	_movableBox 移動オブジェクトのAABB
	@param	_fixedBox 当たったオブジェクトのAABB
	@param	_calcFixVec 速度差分ベクトル
	*/
	void PlayerCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox,Vector3& _calcFixVec);

	/*
	@fn 押し戻し処理
	@brief	x,y軸で押し戻し処理を行う
	@param	_movableBox 移動オブジェクトのAABB
	@param	_fixedBox 当たったオブジェクトのAABB
	@param	_calcFixVec 速度差分ベクトル
	*/
	void HorizontalPlayerCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);
	
	/*
	@brief 前方ベクトルを用いてキャラクターを回転させる関数
	@param	forward 前方ベクトル
	*/
	void RotateToNewForward(const Vector3& forward);



private:

	/*
	@fn クリアしている状態かをチェックする関数
	@param	_tag チェックするオブジェクトのタグ
	*/
	void ClearCheck(Tag _tag);
	
	/*
	@fn クリアに必要なスイッチをチェックする関数
	@param	_checkVector チェックするスイッチが格納されている可変長コンテナ
	*/
	void SwitchCheckProcess(std::vector<GameObject*> _checkVector);

	/*
	@fn スイッチジャンプを使用可能にする関数
	*/
	void ActiveSwitchJumpProcess();

	/*
	@fn リスタートチェック関数
	*/
	void CheckRestartProcess();

	/*
	@brief	攻撃対象の敵を探す
	@param	_hitObject ヒットしたオブジェクト
	@return GameObject* 探し出したオブジェクト
	*/
	GameObject* FindTargetObject(const GameObject& _hitObject);

	// 3Dモデルの描画を行うクラス
	SkeletalMeshComponent* skeltalMeshComponent;
	// Meshの読み込みを行うクラス
	Mesh* mesh;
	// AABBの当たり判定を行うクラス
	BoxCollider* boxCollider;
	// 球体の当たり判定を行うクラス
	SphereCollider* groundCheckSphereCol;
	// 球体の当たり判定を行うクラス
	SphereCollider* jumpAttackSphereCol;

	// ジャンプ攻撃中のプレイヤーを持つためのポインタ変数
	JumpAttackPlayerObject* jumpAttackPlayerObject;

	// @選択している敵を見つけるための可変長配列
	std::vector<GameObject*> selectEnemy;

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	@param	当たったGameObjectの当たり判定タグ
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	/*
	@fn 足元判定用当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	@param	当たったGameObjectの当たり判定タグ
	*/
	void OnCollisionGround(const GameObject& _hitObject, const PhysicsTag _physicsTag);

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数(ジャンプ攻撃を行うエネミーとの判定を取る)
	@param	当たったGameObject
	@param	当たったGameObjectの当たり判定タグ
	*/
	void OnCollisionAttackTarget(const GameObject& _hitObject, const PhysicsTag _physicsTag);

	/*
	@brief ステートプール用マップにステートクラスを追加する関数
	@param	_state 追加するステートクラスのポインタ
	@param	_stateTag 鍵となるタグ
	*/
	void AddStatePoolMap(PlayerObjectStateBase* _state, PlayerState _stateTag);

	/*
	@brief ステートプール用マップからステートクラスを削除する関数
	@param	_stateTag 鍵となるタグ
	*/
	void RemoveStatePoolMap(PlayerState _stateTag);

	/*
	@brief ステートプール用マップをクリアする
	*/
	void ClearStatePoolMap();

	//重力
	static const float Gravity;

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
	// 空中移動時の初速度
	const float FirstAirMovePower;
	//初期ジャンプ力定数
	const float FirstJumpPower;
	// プレイヤーが落下したかどうかを判定する位置
	//（※現状ステージに落下がないのでもしすり抜けてしまった場合）
	const float FallPpsitionZ;
	// 生成されるときのポジションをずらす
	const float FirstPositionZ;

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
	// ジャンプアタック中でないときにヒットした敵のポジション
	Vector3 hitKnockBackObjectPosition;

	// ジャンプ攻撃対象の敵のポインタ
	GameObject* attackTarget;

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

	// 最終ステージ用のクリアフラグ
	bool clearFlag;
	// 最終ステージ以外での次のシーンへ遷移するフラグ
	bool nextSceneFlag;
	// 一定時間以上入力がなかった際にタイトルへ戻るフラグ
	bool restartFlag;
	//入力があったかどうか判定するためのフラグ
	bool inputFlag;
	//引き続きジャンプボタンが利用可能かフラグ
	bool isAvailableJumpKey;

	// ジャンプアタックが利用可能かフラグ
	bool isAvailableJumpAttck;
	// ジャンプアタックフラグ
	bool isJumpAttck;
	// ジャンプアタックするオブジェクトの選択フラグ
	bool isSelectingTargetObject;
	// ジャンプアタック成功したか
	bool isJumpAttackSuccess;
	// ジャンプ攻撃がキャンセルされたか
	bool isJumpAttackCancel;

	//ジャンプできるかフラグ
	bool jumpFlag;
	//ジャンプスイッチを押したかどうか
	bool switchJumpFlag;
	//接地フラグ
	bool onGround;
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
	// 敵にヒットしたか
	bool isHitEnemy;
	// ダンス状態か
	bool isDancing;
	// 爆発に当たったか
	bool isHitExplosion;
	
	// 今のプレーヤーのstate状態を保存するための変数
	PlayerState nowState;
	// 変更された次のプレーヤーのstate状態を保存するための変数
	PlayerState nextState;

	// Animationプール
	std::vector<const Animation*> animTypes;

	// 全stateが格納されるマップ
	std::unordered_map<PlayerState, PlayerObjectStateBase*> statePoolMap;
	
public:// ゲッターセッター

	/*
	@fn skeltalMeshComponentのgetter関数
	@return SkeletalMeshComponent　SkeletalMeshComponentクラスのポインタを返す
	*/
	SkeletalMeshComponent* GetSkeletalMeshComponent() { return skeltalMeshComponent; }

	/*
	@fn Animationのgetter関数
	@param _state 現在のプレイヤーのステータス
	@return Animation Animationクラスのポインタを返す
	*/
	const Animation* GetAnimation(PlayerState _state);

	/*
	@fn 重力のgetter関数
	@return Gravity 重力定数
	*/
	static const float GetGravity() { return Gravity; }

	/*
	@fn forwardVecのgetter関数
	@return forwardVecを返す
	*/
	Vector3 GetForwardVec() { return forwardVec; }
	
	/*
	@fn rightVecのgetter関数
	@return rightVecを返す
	*/
	Vector3 GetRightVec() { return rightVec; }
	
	/*
	@fn charaForwardVecのgetter関数
	@return charaForwardVecを返す
	*/
	Vector3 GetCharaForwardVec() { return charaForwardVec; }
	
	/*
	@fn rotateVecのgetter関数
	@return rotateVecを返す
	*/
	Vector3 GetRotateVec() { return rotateVec; }
	
	/*
	@fn velocityのgetter関数
	@return velocityを返す
	*/
	Vector3 GetVelocity() { return velocity; }
	
	/*
	@fn respownPosのgetter関数
	@return respownPosを返す
	*/
	Vector3 GetRespownPos() { return respownPos; }

	/*
	@fn hitKnockBackObjectPositionのgetter関数
	@return hitKnockBackObjectPositionを返す
	*/
	Vector3 GetHitKnockBackObjectPosition() { return hitKnockBackObjectPosition; }

	/*
	@fn hitEnemyPositionのgetter関数
	@return respownPosを返す
	*/
	GameObject* GetAttackTargetEnemy() { return attackTarget; }

	/*
	@fn DeadSpaceのgetter関数
	@return DeadSpaceを返す
	*/
	const float GetDeadSpace() { return DeadSpace; }
	
	/*
	@fn FirstMovePowerのgetter関数
	@return FirstMovePowerを返す
	*/
	const float GetFirstMovePower() { return FirstMovePower; }

	/*
	@fn FirstAirMovePowerのgetter関数
	@return FirstAirMovePowerを返す
	*/
	const float GetFirstAirMovePower() { return FirstAirMovePower; }
	
	/*
	@fn MovePowerのgetter関数
	@return MovePowerを返す
	*/
	const float GetMovePower() { return MovePower; }
	
	/*
	@fn AirMovePowerのgetter関数
	@return AirMovePowerを返す
	*/
	const float GetAirMovePower() { return AirMovePower; }
	
	/*
	@fn FirstJumpPowerのgetter関数
	@return FirstJumpPowerを返す
	*/
	const float GetFirstJumpPower() { return FirstJumpPower; }
	
	/*
	@fn DecelerationForceのgetter関数
	@return DecelerationForceを返す
	*/
	const float GetDecelerationForce() { return DecelerationForce; }

	/*
	@fn moveSpeedのgetter関数
	@return moveSpeedを返す
	*/
	float GetMoveSpeed() { return moveSpeed; }
	
	/*
	@fn jumpPowerのgetter関数
	@return jumpPowerを返す
	*/
	float GetJumpPower() { return jumpPower; }

	/*
	@fn turnDelayCountのgetter関数
	@return turnDelayCountを返す
	*/	
	int GetTurnDelayCount() { return turnDelayCount; }

	/*
	@fn onGroundのgetter関数
	@return onGroundを返す
	*/
	bool GetOnGround() { return onGround; }
	
	/*
	@fn jumpFlagのgetter関数
	@return jumpFlagを返す
	*/
	bool GetJumpFlag() { return jumpFlag; }
	
	/*
	@fn switchJumpFlagのgetter関数
	@return switchJumpFlagを返す
	*/
	bool GetSwitchJumpFlag() { return switchJumpFlag; }
	
	/*
	@fn isAvailableJumpKeyのgetter関数
	@return isAvailableJumpKeyを返す
	*/
	bool GetIsAvailableJumpKey() { return isAvailableJumpKey; }
	
	/*
	@fn inputFlagのgetter関数
	@return inputFlagを返す
	*/
	bool GetInputFlag() { return inputFlag; }
		
	/*
	@fn deadFlagのgetter関数
	@return deadFlagを返す
	*/
	bool GetDeadFlag() { return deadFlag; }
	
	/*
	@fn respawnFlagのgetter関数
	@return respawnFlagを返す
	*/
	bool GetRespawnFlag() { return respawnFlag; }
	
	/*
	@fn isAvailableInputのgetter関数
	@return isAvailableInputを返す
	*/
	bool GetIsAvailableInput() { return isAvailableInput; }
	
	/*
	@fn isAvailableJumpAttckのgetter関数
	@return isAvailableJumpKeyを返す
	*/
	bool GetIsAvailableJumpAttck() { return isAvailableJumpAttck; }

	/*
	@fn isJumpAttckのgetter関数
	@return isAvailableInputを返す
	*/
	bool GetIsJumpAttck() { return isJumpAttck; }
	
	/*
	@fn isJumpAttckのgetter関数
	@return isAvailableInputを返す
	*/
	bool GetIsSelectingTargetObject() { return isSelectingTargetObject; }
	
	/*
	@fn isJumpAttackSuccessのgetter関数
	@return isAvailableInputを返す
	*/
	bool GetIsJumpAttackSuccess() { return isJumpAttackSuccess; }

	/*
	@fn isJumpAttackCancelのgetter関数
	@return isJumpAttackCancelを返す
	*/
	bool GetIsJumpAttackCancel() { return isJumpAttackCancel; }

	/*
	@fn isHitWallのgetter関数
	@return isHitWallを返す
	*/
	bool GetIsHitEnemy() { return isHitEnemy; }

	/*
	@fn clearFlagのgetter関数
	@return clearFlagを返す
	*/
	bool GetClearFlag() { return clearFlag; }
	
	/*
	@fn nextSceneFlagのgetter関数
	@return nextSceneFlagを返す
	*/
	bool GetNextSceneFlag() { return nextSceneFlag; }

	/*
	@fn restartFlagのgetter関数
	@return restartFlagを返す
	*/
	bool GetRestartFlag() { return restartFlag; }

	/*
	@fn isDancingのgetter関数
	@return isDancingを返す
	*/
	bool GetIsDancing() { return isDancing; }

	/*
	@fn isDancingのgetter関数
	@return isDancingを返す
	*/
	bool GetIsHitExplosion() { return isHitExplosion; }

	/*
	@fn jumpFrameCountのgetter関数
	@return jumpFrameCountを返す
	*/
	int GetJumpFrameCount() { return jumpFrameCount; }

	/*
	@fn nowStateのgetter関数
	@return nowStateを返す
	*/
	PlayerState GetNowState() { return nowState; }

	/*
	@fn AttackTargetObjectのsetter関数
	@param	GameObject* _target ジャンプ攻撃の対象となるオブジェクトのポインタ
	*/
	void SetAttackTargetObject(GameObject* _target) { attackTarget = _target; }

	/*
	@fn nextStateのsetter関数
	@param	PlayerState _nextState プレイヤーの次のステータス
	*/
	void SetNextState(PlayerState _nextState) { nextState = _nextState; }

	/*
	@fn charaForwardVecのsetter関数
	@param	Vector3 _charaForwardVec キャラクターの前方ベクトル
	*/
	void SetCharaForwardVec(Vector3 _charaForwardVec) { charaForwardVec = _charaForwardVec; }
	
	/*
	@fn velocityのsetter関数
	@param	Vector3 _velocity キャラクターの速度ベクトル
	*/
	void SetVelocity(Vector3 _velocity) { velocity = _velocity; }
	
	/*
	@fn respownPosのsetter関数
	@param	Vector3 _respownPos キャラクターのリスポーンするポジション
	*/
	void SetRespownPos(Vector3 _respownPos) { respownPos = _respownPos; }

	/*
	@fn moveSpeedのsetter関数
	@param	float _moveSpeed キャラクターのスピード
	*/
	void SetMoveSpeed(float _moveSpeed) { moveSpeed = _moveSpeed; }

	/*
	@fn jumpPowerのsetter関数
	@param	float _jumpPower キャラクターのジャンプ力
	*/
	void SetJumpPower(float _jumpPower) { jumpPower = _jumpPower; }

	/*
	@fn turnDelayCountのsetter関数
	@param	int _turnDelayCount キャラクターの振り返りディレイカウント
	*/
	void SetTurnDelayCount(int _turnDelayCount) { turnDelayCount = _turnDelayCount; }

	/*
	@fn jumpFlagのsetter関数
	@param	bool _jumpFlag ジャンプ可能かの状態をセット
	*/
	void SetJumpFlag(bool _jumpFlag) { jumpFlag = _jumpFlag; }
	
	/*
	@fn switchJumpFlagのsetter関数
	@param	bool _switchJumpFlag スイッチジャンプ状態のセット
	*/
	void SetSwitchJumpFlag(bool _switchJumpFlag) { switchJumpFlag = _switchJumpFlag; }
	
	/*
	@fn isAvailableJumpKeyのsetter関数
	@param	bool _isAvailableJumpKey ジャンプ利用可能かの状態をセット
	*/
	void SetIsAvailableJumpKey(bool _isAvailableJumpKey) { isAvailableJumpKey = _isAvailableJumpKey; }
	
	/*
	@fn inputFlagのsetter関数
	@param	bool _inputFlag 入力されているかをセット
	*/
	void SetInputFlag(bool _inputFlag) { inputFlag = _inputFlag; }
		
	/*
	@fn jumpFrameCountのsetter関数
	@param	bool _jumpFrameCount ジャンプ中のカウントをセット
	*/
	void SetJumpFrameCount(bool _jumpFrameCount) { jumpFrameCount = _jumpFrameCount; }
	
	/*
	@fn deadFlagのsetter関数
	@param	bool _deadFlag 死亡状態かどうかをセット
	*/
	void SetDeadFlag(bool _deadFlag) { deadFlag = _deadFlag; }
	
	/*
	@fn respawnFlagのsetter関数
	@param	bool _respawnFlag リスポーンフラグをセット
	*/
	void SetRespawnFlag(bool _respawnFlag) { respawnFlag = _respawnFlag; }
	
	/*
	@fn isAvailableInputのsetter関数
	@param	bool _isAvailableInput 入力可能かどうかをセット
	*/
	void SetIsAvailableInput(bool _isAvailableInput) { isAvailableInput = _isAvailableInput; }

	/*
	@fn isAvailableJumpAttckのsetter関数
	@param	bool _isAvailableJumpAttck 入力可能かどうかをセット
	*/
	void SetIsAvailableJumpAttck(bool _isAvailableJumpAttck) { isAvailableJumpAttck = _isAvailableJumpAttck; }

	/*
	@fn isJumpAttckのsetter関数
	@param	bool _isAvailableInput 入力可能かどうかをセット
	*/
	void SetIsJumpAttck(bool _isJumpAttck) { isJumpAttck = _isJumpAttck; }
	
	/*
	@fn isJumpAttckのsetter関数
	@param	bool _isAvailableInput 入力可能かどうかをセット
	*/
	void SetIsSelectingTargetObject(bool _isSelectingTargetEnemy) { isSelectingTargetObject = _isSelectingTargetEnemy; }
	
	/*
	@fn isJumpAttackSuccessのsetter関数
	@param	bool _isJumpAttackSuccess ジャンプ攻撃が成功したかどうかをセット
	*/
	void SetIsJumpAttackSuccess(bool _isJumpAttackSuccess) { isJumpAttackSuccess = _isJumpAttackSuccess; }

	/*
	@fn isJumpAttackCancelのsetter関数
	@param	bool _isJumpAttackCancel 入力可能かどうかをセット
	*/
	void SetIsJumpAttackCancel(bool _isJumpAttackCancel) { isJumpAttackCancel = _isJumpAttackCancel; }

	/*
	@fn isHitEnemyのsetter関数
	@param	bool _isHitEnemy 怯みモーションを行う敵にヒットしたかどうかをセット
	*/
	void SetIsHitEnemy(bool _isHitEnemy) { isHitEnemy = _isHitEnemy; }

	/*
	@fn isHitExplosionのsetter関数
	@param	bool _isHitWall 爆弾の爆発にヒットしているか
	*/
	void SetIsHitExplosion(bool _isHitExplosion) { isHitExplosion = _isHitExplosion; }

	/*
	@fn isDancingのsetter関数
	@param	bool isDancing ダンスしているかどうか
	*/
	void SetIsDancing(bool _isDancing) { isDancing = _isDancing; }

};