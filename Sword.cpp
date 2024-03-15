#include "Sword.h"
#include <ImGuiManager.h>
#define _USE_MATH_DEFIN
#include <math.h>
#include <assert.h>

Vector3 Sword::GetWorldPosition() 
{ 
	
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Sword::Initialize(Model* model_,Vector3 Position) 
{

	
	model = model_;
	worldTransform_.Initialize();

	worldTransform_.translation_ = Position;

}

void Sword::Update() 
{ 

	worldTransform_.UpdateMatrix();

}

void Sword::Draw(ViewProjection& viewprojection) 
{ 
	if (isDead_ == true) 
	{
		model->Draw(worldTransform_, viewprojection, textureHandle_);
	}
}

void Sword::OnCollision() 
{

	isDead_ = false;
	/*
	 assert(player_);

	// sword速さ

	const float kSpeed = 0.25f;

	Vector3 velocity{kSpeed, kSpeed, kSpeed};

	 
	Vector3 playerpos = player_->GetWorldPosition();

	Vector3 sword = GetWorldPosition();

	Vector3 Result = {

	    playerpos.x - sword.x, playerpos.y - sword.y, playerpos.z - sword.z - 7.5f

	};

	Vector3 ResultNomalize = Normalize(Result);

	velocity = {

	    ResultNomalize.x * velocity.x, ResultNomalize.y * velocity.y, ResultNomalize.z * velocity.z

	};

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity);

	worldTransform_.UpdateMatrix();
	*/
	

}
