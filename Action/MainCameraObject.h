#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "CameraObjectBase.h"
#include "PlayerObject.h"

// クラスの前方宣言
class BoxCollider;

/*
@file MainCameraObject.h
@brief メインカメラ ゲーム中のオブジェクトを映す
*/
class MainCameraObject :
	public CameraObjectBase
{
public:
	/*
	@brief	コンストラクタ
	@param	ポジション
	*/
	MainCameraObject(const Vector3 _pos, PlayerObject* _playerObject);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~MainCameraObject();

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime = 1.0f)override;
	
	/*
	@fn 入力を引数で受け取る更新関数
	@brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
	*/
	void GameObjectInput(const InputState& _keyState)override;

	/*
	@brief	見る対象物の情報を得る
	@param _offset　見たい座標との差
	@param _parentPos　見る座標
	*/
	void SetViewMatrixLerpObject(const Vector3& _offset, const Vector3& _parentPos);

	/*
	@brief 押し戻しを行う
	@param 自分のAABB
	@param 相手のAABB
	@param ペアとなる相手のTag
	*/
	void FixCollision(AABB& myAABB, const AABB& pairAABB);

	/*
	@brief 押し戻し計算を行う
	@param 自分のAABB
	@param 相手のAABB
	@param 押し戻し量
	*/
	void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);
	
	/*
	@brief	player以外のものを注視する際に使うsetter
	@param 見る対象物のポジション
	*/
	void SetLerpObjectPos(const Vector3& _pos) { lerpObjectPos = _pos; }
	
	/*
	@brief カメラの前方ベクトルを得るためのgetter
	@param カメラの前方ベクトル
	*/
	Vector3 GetCameraVec() { return forwardVec; }
	

	/*
	@brief 追跡する対象オブジェクトのポジションのgetter
	@param 追跡する対象オブジェクトポジション
	*/
	Vector3 GetlerpObjectPos() { return lerpObjectPos; }

	/*
	@brief リスポーンしたときにカメラの位置を初期状態にセットする関数
	*/
	void ReSetYaw() { yaw = Math::ToRadians(180); }

	//追従先のオブジェクト座標
	Vector3 lerpObjectPos;

private:

	void InGameMovableProcess(float _deltaTime);

	void CorrectionRadius();

	void CorrectionPitch();

	void CalculationPosition(float _deltaTime);

	void CalculationViewMatrix();

	void GameClearProcess(float _deltaTime);

	void GameOverProcess(float _deltaTime);

	void PlayerInDanceProcess(float _deltaTime);

	void ChackInputProcess(const InputState& _keyState);

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	// AABBの初期化時の最大値定数
	const Vector3 AabbInitMax;
	// AABBの初期化時の最小値定数
	const Vector3 AabbInitMin;

	// カメラのヨーの移動速度
	const float YawSpeed;
	// カメラのピッチの移動速度
	const float PitchSpeed;
	// 自動回転する際の移動速度
	const float AutomaticMoveSpeed;

	// カメラの高さの最大値
	const float MaxPitch;
	// カメラの高さの最小値
	const float MinPitch;

	// カメラ半径の最大値
	const float MaxRadius;
	// カメラ半径の中間点の値
	const float MediumRadius;
	// カメラ半径の最小値
	const float MinRadius;
	// タイムオーバー時の半径
	const float TimeOverRadius;
	// ダンス時状態時の半径
	const float DanceRadius;
	// 見る対象物から当たった場所を引いて長さを取る際の補正定数
	const float CorrectionBackRadius;

	// 線形保管時にデルタタイムをかけるとき用の補正定数
	const float DeltaCorrection;

	// 少し先を注視するようにしたいのでZ軸をずらす定数
	const float ShiftGazePoint;

	// プレイヤーのポインタを保持するための変数
	PlayerObject* playerObject;

	//親オブジェクトとの差
	Vector3 offsetPos;

	//移動先position
	Vector3 tmpMovePos;
	Vector3 tmpPosition;

	// 押し戻しを行う相手と当たった位置を保存するVector3変数
	Vector3 hitPosition;

	// 当たり判定を行うクラス(AABB/球体)
	BoxCollider* boxcollider;

	// view行列
	Matrix4 view;

	//追従先のオブジェクトを所持しているか
	bool hasParentObject;

	// 押し戻しを行う相手と当たったかを判定するフラグ
	bool hitFlag;

	// 前のフレームで押し戻しを行う相手と当たったかを判定するフラグ
	bool tmpHitFlag;

	//カメラの高さ
	float height;

	//カメラ回転計算用のヨーとピッチ
	float yaw;
	float pitch;

	//カメラ回転の半径
	float radius;





};

