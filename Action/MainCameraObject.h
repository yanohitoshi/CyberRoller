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
@brief 手動で回転させることが出来るカメラクラス
*/
class MainCameraObject :
	public CameraObjectBase
{
public:

	/*
	@brief	コンストラクタ
	@param	ポジション
	@param	プレイヤーのポインタ
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
	@param	_keyState 入力情報
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
	void CalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);
	
	/*
	@brief 追跡する対象オブジェクトのポジションのgetter
	@param 追跡する対象オブジェクトポジション
	*/
	Vector3 GetlerpObjectPos() { return lerpObjectPos; }

private:

	/*
	@brief ゲーム中の移動処理
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void InGameMovableProcess(float _deltaTime);
	
	/*
	@brief 半径補正計算処理
	*/
	void CorrectionRadius();
	
	/*
	@brief ピッチ補正計算処理
	*/
	void CorrectionPitch();

	/*
	@brief ポジション計算処理
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void CalculationPosition(float _deltaTime);

	/*
	@brief ビュー行列計算処理
	*/
	void CalculationViewMatrix();

	/*
	@brief ゲームクリア時の処理
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void GameClearProcess(float _deltaTime);

	/*
	@brief ゲームオーバー時の処理
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void GameOverProcess(float _deltaTime);
	
	/*
	@brief プレイヤーがダンス状態の時の処理
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void PlayerInDanceProcess(float _deltaTime);
	
	/*
	@brief 入力チェックとその処理
	@param	_keyState 入力情報
	*/
	void CheckInputProcess(const InputState& _keyState);

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	@param	当たったGameObjectの当たり判定タグ
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

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

	// 少し先を注視するようにしたいのでZ軸をずらす定数
	const float ShiftGazePoint;

	//親オブジェクトとの差
	Vector3 offsetPos;

	// 押し戻しを行う相手と当たった位置を保存するVector3変数
	Vector3 hitPosition;

	// 当たり判定を行うクラス(AABB/球体)
	BoxCollider* boxcollider;

	//追従先のオブジェクトを所持しているか
	bool hasParentObject;

	// 押し戻しを行う相手と当たったかを判定するフラグ
	bool hitFlag;

	// 前のフレームで押し戻しを行う相手と当たったかを判定するフラグ
	bool tmpHitFlag;

	//カメラの高さ
	float height;

	//カメラ回転の半径
	float radius;

};

