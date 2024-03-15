#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "DebugCamera.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Sword.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void CheckonCollision();

	bool isDebugCameraActive_ = false;
	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	void swordSpawn();

	void SwordUpdate();
	void swordDraw();
	void LoadSwordPopData();
	void UpdateSwordPopCommands();

private: 
	

	ViewProjection viewProjection_;
	WorldTransform worldTransform_;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	Model* model_ = nullptr;
	Model* playermodel_ = nullptr;
	Model* swordmodel_ = nullptr;

	Player* player_ = nullptr;
	Sword* sword_ = nullptr;

	std::list<Sword*> swords_;

	uint32_t textureHandle = 0;
	Vector3 swordposition;


	std::stringstream swordPopCommands;
	
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
