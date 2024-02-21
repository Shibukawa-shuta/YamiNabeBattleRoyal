#include "GameScene.h"
#include "TextureManager.h"
#include "ImGuiManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//背景
	textureHandleTitleBG_ = TextureManager::Load("back.png");
	spriteTBG_ = Sprite::Create(textureHandleTitleBG_, {0, 0});

	// 背景
	textureHandleGameBG_ = TextureManager::Load("black.png");
	spriteGBG_ = Sprite::Create(textureHandleGameBG_, {0, 0});
	// ワールド
	worldTransform_.Initialize();
	//カメラ
	viewProjection_.translation_ = {0.0f, 2.0f, -3.0f};
	viewProjection_.rotation_ = {0.6f, 0.0f, 0.0f};
	viewProjection_.Initialize();

	//鍋
	Nabe_ = std::make_unique<Nabe>();
	NabeModel_.reset(Model::CreateFromOBJ("nabe", true));
	Nabe_->Initialize(NabeModel_.get());


	//こたつ
	kotatsu_ = std::make_unique<kotatsu>();
	kotatsuModel_.reset(Model::CreateFromOBJ("kotatsu", true));
	kotatsu_->Initialize(kotatsuModel_.get());

	// こたつ
	konro_ = std::make_unique<Konro>();
	konroModel_.reset(Model::CreateFromOBJ("konro", true));
	konro_->Initialize(konroModel_.get());

	//カードデッキ
	deck_ = std::make_unique<deck>();
	deckModel_.reset(Model::CreateFromOBJ("deck", true));
	deck_->Initialize(deckModel_.get());

	//食材
	textureHandle_ = TextureManager::Load("Toufu.jpg");
	textureHandle2_ = TextureManager::Load("CD.png");
	textureHandle3_ = TextureManager::Load("Donuts.png");
	//選択
	textureHandle4_ = TextureManager::Load("shake.png");
	textureHandle5_ = TextureManager::Load("taberu.png");
	textureHandle6_ = TextureManager::Load("turnend.png");
	textureHandle7_ = TextureManager::Load("Draw.png");
	viewProjection_.Initialize();
	cardmodel_.reset(Model::Create());
	card_ = std::make_unique<Card>();
	card_->Initialize(
	    cardmodel_.get(), textureHandle_, textureHandle2_, textureHandle3_,
		textureHandle4_,textureHandle5_,textureHandle6_,textureHandle7_);

	// カード
	textureHandle_ = TextureManager::Load("card1.png");
	textureHandleDonuts_ = TextureManager::Load("cardDonuts.png");
	textureHandleCD_ = TextureManager::Load("cardCD.png");
	textureHandleRenga_ = TextureManager::Load("cardRenga.png");
	textureHandleToufu_ = TextureManager::Load("cardToufu.png");
	viewProjection_.Initialize();
	card2model_.reset(Model::Create());
	card2_ = std::make_unique<Card2>();
	card2_->Initialize(
	    card2model_.get(), textureHandle_, 
		textureHandleToufu_, textureHandleRenga_,
	    textureHandleCD_, textureHandleDonuts_);
	    // タイトル											 
	    textureHandleTitle_ = TextureManager::Load("Title2.png");
	viewProjection_.Initialize();
	Titlemodel_.reset(Model::Create());
	Title_ = std::make_unique<Title>();
	Title_->Initialize(cardmodel_.get(), textureHandleTitle_);

}

void GameScene::Update() {
	switch (sceneMode_) {
	case 0:
		sceneMode_ = Title_->Update();
		// カメラ
		viewProjection_.translation_ = {0.0f, 2.0f, -3.0f};
		viewProjection_.rotation_ = {0.6f, 0.0f, 0.0f};
		viewProjection_.Initialize();
		Nabe_->Start();
		kotatsu_->Start();
		konro_->Start();
		deck_->Start();
		card_->Start();
		card2_->Start();
		
		break;
	case 1:
		Nabe_->Update();
		kotatsu_->Update();
		konro_->Update();
		deck_->Update();
		card_->Update();
		card2_->Update();
		Title_->Update();

		card_->SetMode(card2_->GetMode());
		card_->SetTakeFlag(card2_->GetTakeFlag());
		card_->SetEatFlag(card2_->GetEatFlag());
		card_->SetEatTimer(card2_->GetEatTimer());
		card_->SetHP(card2_->GetHP());
		card_->SetSatietyLevel(card2_->GetSatietyLevel());
		Title_->SetScene(card2_->Getscene());
		card2_->SetMouse(mx_, my_);
		card_->SetTakeCount(card2_->GetTakeCount());
	
		if (input_->TriggerKey(DIK_RETURN)) {
			sceneMode_ = 0;
		}
		break;
	}
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
	
	switch (sceneMode_) {
	case 0:
		spriteTBG_->Draw();
		break;
	case 1:
		spriteGBG_->Draw();
		break;
	
	}
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);


	switch (sceneMode_) {
	case 0:
		Title_->Draw(viewProjection_);
		break;

	case 1:
		
		Nabe_->Draw(viewProjection_);
		kotatsu_->Draw(viewProjection_);
		konro_->Draw(viewProjection_);
		deck_->Draw(viewProjection_);
		card_->Draw(viewProjection_);
		card2_->Draw(viewProjection_);
		
		break;
	
	}
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
