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

	// マリオ
	textureHandle_ = TextureManager::Load("Toufu.jpg");
	viewProjection_.Initialize();
	model_.reset(Model::Create());
	card_ = std::make_unique<Card>();
	card_->Initialize(model_.get(), textureHandle_);

	/*textureHandle_ = TextureManager::Load("Toufu.jpg");

	Food_ = std::make_unique<Food>();
	Food_->Initialize(FoodModel_.get(),textureHandle_);*/
}

void GameScene::Update() {
	Nabe_->Update();
	kotatsu_-> Update();
	konro_->Update();
	card_->Update();
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

		/*Card_->Draw(viewProjection_);*/

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
	card_->Draw(viewProjection_);


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
