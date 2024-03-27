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

	//背景
	textureHandleGameOverBG_ = TextureManager::Load("back.png");
	spriteOBG_ = Sprite::Create(textureHandleGameOverBG_, {0, 0});

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
	

	//和室
	haikei_ = std::make_unique<haikei>();
	haikeimodel_.reset(Model::CreateFromOBJ("washitsu", true));
	haikei_->Initialize(haikeimodel_.get());

	//食材
	textureHandle_ = TextureManager::Load("/TextureFoods/Toufu.png");
	textureHandle2_ = TextureManager::Load("/TextureFoods/CD.png");
	textureHandle3_ = TextureManager::Load("/TextureFoods/Donuts.png");
	//選択
	textureHandleUi_ = TextureManager::Load("shake.png");
	textureHandleUi2_ = TextureManager::Load("taberu.png");
	textureHandleUi3_ = TextureManager::Load("turnend.png");
	textureHandleUi4_ = TextureManager::Load("Draw.png");
	viewProjection_.Initialize();
	cardmodel_.reset(Model::Create());

	food_ = std::make_unique<Food>();
	food_->Initialize(
	    cardmodel_.get(), textureHandle_, textureHandle2_, textureHandle3_,
		textureHandleUi_,textureHandleUi2_,textureHandleUi3_,textureHandleUi4_);

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

	// ゲームオーバー										 
	    textureHandleOver_ = TextureManager::Load("GameOver.png");
	viewProjection_.Initialize();
	Overmodel_.reset(Model::Create());
	Over_ = std::make_unique<GameOver>();
	Over_->Initialize(cardmodel_.get(), textureHandleOver_);

	//フェード
	textureHandleBlack_ = TextureManager::Load("black.png");
	spriteBlack_.reset(Sprite::Create(textureHandleBlack_, {0, 0}));


	//フェードの生成
	fade_ = std::make_unique<Fade>();
	fade_->Initialize(spriteBlack_.get(),textureHandleBlack_);

	//サウンド
	audio_ = Audio::GetInstance();
	GameDataHandleBGM_ = audio_->LoadWave("Audio/battle.wav");

	//効果音
	se_ = Audio::GetInstance();
	GameDataHandleSE_ = se_->LoadWave("Audio/drawSe.wav");

	
}

void GameScene::Update() {
	switch (sceneMode_) {
	case 0:

	  if (Title_->Update() == true)
		{
			fade_->FadeOutStart();
		}
	  if (fade_->IsEnd() == true) {

	        audio_->StopWave(TitleBGM_);
			Start2();
			sceneMode_ = 1u;

			fade_->FadeInStart();
		}



		// カメラ
		viewProjection_.translation_ = {0.0f, 2.0f, -3.0f};
		viewProjection_.rotation_ = {0.6f, 0.0f, 0.0f};
		viewProjection_.Initialize();
		haikei_->Start();
		Nabe_->Start();
		kotatsu_->Start();
		konro_->Start();
		deck_->Start();
		food_->Start();
		card2_->Start();
	

		break;
	case 1:

		
		haikei_->Update();
		Nabe_->Update();
		kotatsu_->Update();
		konro_->Update();
		deck_->Update();
		food_->Update();
		card2_->Update();
		Title_->Update();
		Over_->Update();

		food_->SetMode(card2_->GetMode());
		food_->SetHP(card2_->GetHP());
		food_->SetSatietyLevel(card2_->GetSatietyLevel());
		Title_->SetScene(card2_->Getscene());
		card2_->SetMouse(mx_, my_);
		food_->SetMouse(mx_, my_);


	


		if (input_->TriggerKey(DIK_RETURN)) {
	
			 audio_->StopWave(GameSceneBGM_);

			sceneMode_ = 2;
		fade_->FadeInStart();
		}

	
		break;

		case 2:

			//二巡目
	if (Over_->Update() == true)
		{
			fade_->FadeOutStart();
		}
		if (fade_->IsEnd() == true)
		{
			Title_->Start();
			sceneMode_ = 0u;
			fade_->FadeInStart();
		}

		break;
	}
	    fade_->Update();
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
	
		break;
	case 2:
		spriteOBG_->Draw();
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
		haikei_->Draw(viewProjection_);
		Nabe_->Draw(viewProjection_);
		kotatsu_->Draw(viewProjection_);
		konro_->Draw(viewProjection_);
		deck_->Draw(viewProjection_);
		food_->Draw(viewProjection_);
		card2_->Draw(viewProjection_);
	

		break;

    case 2:
		Over_->Draw(viewProjection_);
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
	

	fade_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Start2() {
	GameSceneBGM_ = audio_->PlayWave(GameDataHandleBGM_, false);

}


