#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "TextureManager.h"
#include <cassert>
#include <fstream>


GameScene::GameScene() {}

GameScene::~GameScene() {

	delete playermodel_;
	delete debugCamera_;
	delete swordmodel_;
}

void GameScene::CheckonCollision() 
{ 
	
	Vector3 posA, posB;

	
	
	

}


void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugCamera_ = new DebugCamera(-18, 18);
	
	model_ = Model::Create();
	playermodel_ = (Model::CreateFromOBJ("float", true));
	swordmodel_ = (Model::CreateFromOBJ("float_L_arm", true));

	viewProjection_.Initialize();
	

	//剣の生成
	sword_ = new Sword();

	// 自キャラの生成
	player_ = new Player();

	// 自キャラの初期化
	player_->Initialize(playermodel_);

	//剣の初期化
	sword_->Initialize(swordmodel_,swordposition);
	sword_->SetGameScene(this);


}

void GameScene::Update() 
{

	player_->Update();
	debugCamera_->Update();
	sword_->Update();
	CheckonCollision();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_P)) {
		isDebugCameraActive_ = true;
	}
#endif
	// カメラ
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}

	viewProjection_.translation_.x = player_->GetX();
	viewProjection_.UpdateMatrix();
	
	

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_->Draw(viewProjection_);

	sword_->Draw(viewProjection_);

	swordDraw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::swordSpawn()
{

     Sword* sword = new Sword;

	 sword->Initialize(model_, swordposition);

	 sword->SetPlayer(player_);

	 sword->SetGameScene(this);

	 swords_.push_back(sword);

}

void GameScene::SwordUpdate() 
{  

	for (Sword* sword : swords_)
	{
		sword->Update();
	}

}

void GameScene::swordDraw() 
{

	for (Sword* sword : swords_)
	{
		sword->Draw(viewProjection_);
    }

}

void GameScene::LoadSwordPopData()
{
	// ファイルを開く
	std::ifstream file;
	file.open("Resources/Sword.csv");
	assert(file.is_open());

	// ファイルの内容を文字列ストリームにコピー
	swordPopCommands<< file.rdbuf();

	// ファイルを閉じる
	file.close();

}

void GameScene::UpdateSwordPopCommands() 
{
	// 1行列分の文字列を入れる変数
	std::string line;

	// コマンド実行ループ
	while (getline(swordPopCommands, line)) {

		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		// 区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}

		if (word.find("POP") == 0) {
			// x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// 敵を発生させる

			swordposition = {x, y, z};

			swordSpawn();


		}

		
		
	}

}
