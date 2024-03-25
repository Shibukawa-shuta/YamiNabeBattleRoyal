#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Nabe.h"
#include "kotatsu.h"
#include"Konro.h"
#include"Food.h"
#include"Card2.h"
#include"deck.h"
#include"Title.h"
#include"GameOver.h"
#include"Fade.h"

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
		mx_ = x;
		my_ = y;
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
	uint32_t textureHandleUi_ = 0;
	uint32_t textureHandleUi2_ = 0;
	uint32_t textureHandleUi3_ = 0;
	uint32_t textureHandleUi4_ = 0;

	uint32_t textureHandleToufu_;
	uint32_t textureHandleRenga_; 
	uint32_t textureHandleCD_;
	uint32_t textureHandleDonuts_;
	// タイトル (スプライト)
	uint32_t textureHandleTitle_ = 0;
	//ゲームオーバー
	uint32_t textureHandleOver_ = 0;

	std::unique_ptr<Model> NabeModel_;
	std::unique_ptr<Nabe> Nabe_;

	std::unique_ptr<Model> kotatsuModel_;
	std::unique_ptr<kotatsu>kotatsu_;
	
	std::unique_ptr<Model> konroModel_;
	std::unique_ptr<Konro>konro_;

	std::unique_ptr<Model> deckModel_;
	std::unique_ptr<deck> deck_;

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

	int mx_ = 0;
	int my_ = 0;
	
	
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


	/// ゲームシーン用
	/// </summary>
};
