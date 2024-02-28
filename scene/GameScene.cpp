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

	// ワールド
	worldTransform_.Initialize();

	viewProjection_.translation_ = {0.0f, 2.0f, -3.0f};
	viewProjection_.rotation_ = {0.6f, 0.0f, 0.0f};

	//
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

	// こたつ
	deck_ = std::make_unique<deck>();
	deckModel_.reset(Model::CreateFromOBJ("deck", true));
	deck_->Initialize(deckModel_.get());

	//食材
	textureHandle_ = TextureManager::Load("Toufu.jpg");
	textureHandle2_ = TextureManager::Load("CD.png");
	textureHandle3_ = TextureManager::Load("Donuts.png");
	viewProjection_.Initialize();
	cardmodel_.reset(Model::Create());
	card_ = std::make_unique<Card>();
	card_->Initialize(cardmodel_.get(), textureHandle_, textureHandle2_, textureHandle3_ );

	// カード
	textureHandle_ = TextureManager::Load("card1.png");
	viewProjection_.Initialize();
	card2model_.reset(Model::Create());
	card2_ = std::make_unique<Card2>();
	card2_->Initialize(card2model_.get(), textureHandle_);
}

void GameScene::Update() {
	Nabe_->Update();
	kotatsu_-> Update();
	konro_->Update();
	deck_->Update();
	card_->Update();
	card2_->Update();


	card_->SetMode(card2_->GetMode());
	card_->SetTakeFlag(card2_->GetTakeFlag());
	card2_->SetMouse(mx_, my_);
	

	ImGui::Begin("MOUSE");
	ImGui::InputInt("X", &mx_);
	ImGui::InputInt("Y", &my_);
	ImGui::End();
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
	Nabe_->Draw(viewProjection_);
	kotatsu_->Draw(viewProjection_);
	konro_->Draw(viewProjection_);
	deck_->Draw(viewProjection_);
	card_->Draw(viewProjection_);
	card2_->Draw(viewProjection_);
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
