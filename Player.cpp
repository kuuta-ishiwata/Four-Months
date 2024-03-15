#include "Player.h"
#include "ImGuiManager.h"
#include <cassert>
#include "ImGuiManager.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include <memory>


Player::Player() {}

Player::~Player() {}


void Player::Initialize(Model* model)
{

	input_ = Input::GetInstance();
	// NULLポインタチェック
	assert(model);
	model_ = model;
	worldTransform_.translation_ = {10.0f, 0.0f, 0.0f};
	worldTransform_.Initialize();
}

Vector3 Player::GetWorldPosition() 
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::Update() 
{

	// ゲームパッドの状態を得る変数 

	XINPUT_STATE joyState;

	// ゲームパッド状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// キャラクターの移動速さ
		const float speed = 0.2f;
		// 移動量
		Vector3 move = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * speed, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * speed};

		// 移動量に速さを反映
		move = Normalize(move);
		move = Multiply3(speed, move);	

		// 移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	}

	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection& viewProjection) 
{

	model_->Draw(worldTransform_, viewProjection);

}
