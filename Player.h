#pragma once
#include "Input.h"
#include "MatrixTrans.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"

class Player {


public:

		Vector3 GetWorldPosition();
	///< summary>
	/// デストラクタ
	///  <summary>
	   Player();
	~Player();

	///< summary>
	/// 攻撃
	///  <summary>

	///< summary>
	/// 初期化
	///</summary>
	void Initialize(Model* model);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>

	void Draw(ViewProjection& viewProjection);

	
	float GetX() { return worldTransform_.translation_.x; }
	float GetY() { return worldTransform_.translation_.y; }

	

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	// モデル
	Model* model_ = nullptr;

	Input* input_ = nullptr;

	

	

	



};
