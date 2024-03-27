#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"Food.h"
#include"Card2.h"
#include"Title.h"
#include"GameOver.h"
#include"Fade.h"
#include"haikei.h"
#include"Object.h"
#include"Camera.h"
#include"GameUI.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();
	// BG(スプライト)
	uint32_t textureHandleGameBG_ = 0;
	Sprite* spriteGBG_ = nullptr;

	// BG(スプライト)
	uint32_t textureHandleTitleBG_ = 0;
	Sprite* spriteTBG_ = nullptr;

	// BG(スプライト)
	uint32_t textureHandleGameOverBG_ = 0;
	Sprite* spriteOBG_ = nullptr;

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
	void SetMouse(int x, int y) {
		mouseX_ = x;
		mouseY_ = y;
	}

	void Start2();

	

	
private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Audio* se_ = nullptr;
	

	


	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	uint32_t textureHandle_ = 0;
	uint32_t textureHandle2_ = 0;
	uint32_t textureHandle3_ = 0;

	uint32_t textureHandleToufu_;
	uint32_t textureHandleRenga_; 
	uint32_t textureHandleCD_;
	uint32_t textureHandleDonuts_;

	uint32_t textureHandleShake_ = 0;
	uint32_t textureHandleEat_ = 0;
	uint32_t textureHandleTurnend_ = 0;
	


	// タイトル (スプライト)
	uint32_t textureHandleTitle_ = 0;
	//ゲームオーバー
	uint32_t textureHandleOver_ = 0;

	// 鍋
	std::unique_ptr<Model> NabeModel_;
	std::unique_ptr<Nabe> Nabe_;
	// こたつ
	std::unique_ptr<Model> kotatsuModel_;
	std::unique_ptr<kotatsu> kotatsu_;
	// コンロ
	std::unique_ptr<Model> konroModel_;
	std::unique_ptr<Konro> konro_;
	// デッキ
	std::unique_ptr<Model> deckModel_;
	std::unique_ptr<deck> deck_;
	// カメラ
	std::unique_ptr<Camera> camera_;

	std::unique_ptr<Model> UImodel_;
	std::unique_ptr<GameUI> gameui_;

	
	std::unique_ptr<Model> cardmodel_;
	std::unique_ptr<Food> food_;

	std::unique_ptr<Model> card2model_;
	std::unique_ptr<Card2> card2_;

	std::unique_ptr<Model> Titlemodel_;
	std::unique_ptr<Title> Title_;

	std::unique_ptr<Model> Overmodel_;
	std::unique_ptr<GameOver> Over_;

	std::unique_ptr<Fade>fade_;



	//フェード
	uint32_t textureHandleBlack_ = 0u;
	std::unique_ptr<Sprite> spriteBlack_;

	//背景

	std::unique_ptr<Model> haikeimodel_;
	std::unique_ptr<haikei> haikei_;

	int mouseX_ = 0;
	int mouseY_ = 0;
	
	int cardFlag = 0;
	
	int selectedCardIndex_ = -1;

	int mode = 0;

	int takeFlag = 0;

	int card_ = 0;

	int cardModel_ = 0;



	float viewSpeed = 0.025f;

    uint32_t sceneMode_ = 0u;

	//タイトルサウンド
	uint32_t TitleDataHandleBGM_ = 0;
	uint32_t TitleBGM_ = 0;

	//ゲームプレイサウンド
	uint32_t GameDataHandleBGM_ = 0;
	uint32_t GameSceneBGM_ = 0;

	//ゲームプレイ効果音
	uint32_t GameDataHandleSE_ = 0;
	uint32_t GameSceneSE_ = 0;

		//カードを引く効果音
	uint32_t DrawHandleSE_ = 0;
	uint32_t DrawSE_ = 0;

	/// ゲームシーン用
	/// </summary>
};
