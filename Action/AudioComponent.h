#pragma once
#include "Component.h"
#include <String>

class AudioComponent :
    public Component
{
public:

	/*
	@brief	コンストラクタ
	@param	アタッチするゲームオブジェクトのポインタ
	@param	なんのColliderなのか判定用Tag(PhysicsTag)
	@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
	@param  当たり判定時に、めり込みから動かす処理の優先度を決める数値
	*/
	AudioComponent(GameObject* _owner, const std::string& _fileName,int _updateOrder = 200);

	~AudioComponent()override {};

protected:

	// 当たり判定を行うかどうかの判定用Tag
	const std::string& myFileName;

public: // ゲッターセッター


};