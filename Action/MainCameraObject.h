#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "CameraObjectBase.h"
#include "PlayerObject.h"

// クラスの前方宣言
class LineSegmentCollider;
class SphereCollider;
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
	MainCameraObject(const Vector3 _pos);

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
	void FixCollision(AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag);

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

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	//親オブジェクトとの差
	Vector3 offsetPos;
	//追従先のオブジェクトを所持しているか
	bool hasParentObject;
	Vector3 cameraFront = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 cameraUp = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 direction;
	Vector3 vel;
	//カメラの高さ
	float height;
	//カメラ回転計算用のヨーとピッチ
	float yaw;
	float pitch;
	//カメラの移動速度
	static const float yawSpeed;
	static const float pitchSpeed;

	//カメラ回転の半径
	float radius;
	// タイムオーバー時の半径
	float timeOverRadius;
	// ダンス時状態時の半径
	float danceRadius;

	//移動先position
	Vector3 tmpMovePos;
	Vector3 tmpPosition;

	// 当たり判定を行うクラス(AABB/線分/球体※線分未実装)
	BoxCollider* boxcollider;
	LineSegmentCollider* lineSegmentCollider;
	SphereCollider* sphereCollider;

	// view行列
	Matrix4 view;

	// 押し戻しを行う相手と当たった位置を保存するVector3変数
	Vector3 hitPosition;

	// 押し戻しを行う相手と当たったかを判定するフラグ
	bool hitFlag;
	// 前のフレームで押し戻しを行う相手と当たったかを判定するフラグ
	bool tmpHitFlag;
};

