#pragma once
#include "Model.h"
#include "Player.h"
#include <list>
#include <vector>

class GameScene;

class Player;

class Sword {

public:
	Vector3 GetWorldPosition();

	void Initialize(Model* model_, Vector3 Position);

	void Update();

	void Draw(ViewProjection& viewprojection);

	void OnCollision();

	
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	void SetPlayer(Player* player) { player_ = player; }



private:


	Model* model = nullptr;
	WorldTransform worldTransform_;
	ViewProjection viewprojection_;

	GameScene* gameScene_ = nullptr;

	Player* player_ = nullptr;
	uint32_t textureHandle_ = 0;
	bool isDead_ = true;


};
