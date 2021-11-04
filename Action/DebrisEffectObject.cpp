#include "DebrisEffectObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Mesh.h"

DebrisEffectObject::DebrisEffectObject(const Vector3& _pos, const Vector3& _direction)
	: GameObject(false,Tag::GROUND)
	, MovePower(50.0f)
{
	//GameObjectメンバ変数の初期化
	SetPosition(_pos);
	SetScale(Vector3(2.0f,2.0f,2.0f));
	tag = Tag::GROUND;
	state = Active;
	isPushBackToPlayer = false;
	isCheckGroundToPlayer = false;
	isPushBackToCamera = false;

	direction = _direction;
	// 生存時間初期化
	lifeCount = 60;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/groundModel/debrisGround.gpmesh"));
	//メッシュ情報取得
	mesh = meshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	moveSpeed = (float)(rand() % 1500 + 1000 );

	Rotation(this, (float)(rand() % 361 + 50), Vector3::UnitX);
	Rotation(this, (float)(rand() % 361 + 50), Vector3::UnitY);
	Rotation(this, (float)(rand() % 361 + 50), Vector3::UnitZ);
}

DebrisEffectObject::~DebrisEffectObject()
{
}

void DebrisEffectObject::UpdateGameObject(float _deltaTime)
{
	// 生存時間を減らす
	LifeCountDown();
	velocity = direction * moveSpeed;
	SetPosition(position + velocity * _deltaTime);

	// z軸方向ベクトルをマイナス方向にしていく
	direction.z -= 0.05f;

	// -1.0以下になったら1.0で固定
	if (direction.z <= -1.0f)
	{
		direction.z = -1.0f;
	}

	// ライフカウントが0以下になったら
	if (lifeCount <= 0)
	{
		// ステータスをdeadに変更
		state = State::Dead;
		SetState(state);
	}
}

void DebrisEffectObject::LifeCountDown()
{
	//生存時間がゼロになるとこのオブジェクトを更新終了する
	if (lifeCount <= 0)
	{
		meshComponent->SetVisible(false);
		SetState(State::Dead);

	}
	else
	{
		meshComponent->SetVisible(true);
		lifeCount--;
	}
}
