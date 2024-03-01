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
#include"card.h"
#include"Card2.h"
#include"deck.h"
#include"Title.h"
#include"Parameters.h"

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


	

	
private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	uint32_t textureHandle_ = 0;
	uint32_t textureHandle2_ = 0;
	uint32_t textureHandle3_ = 0;
	uint32_t textureHandle4_ = 0;
	uint32_t textureHandle5_ = 0;
	uint32_t textureHandle6_ = 0;
	uint32_t textureHandle7_ = 0;

	uint32_t textureHandleToufu_;
	uint32_t textureHandleRenga_; 
	uint32_t textureHandleCD_;
	uint32_t textureHandleDonuts_;
	// タイトル (スプライト)
	uint32_t textureHandleTitle_ = 0;
	

	std::unique_ptr<Model> NabeModel_;
	std::unique_ptr<Nabe> Nabe_;

	std::unique_ptr<Model> kotatsuModel_;
	std::unique_ptr<kotatsu>kotatsu_;
	
	std::unique_ptr<Model> konroModel_;
	std::unique_ptr<Konro>konro_;

	std::unique_ptr<Model> deckModel_;
	std::unique_ptr<deck> deck_;

	std::unique_ptr<Model> cardmodel_;
	std::unique_ptr<Card> card_;

	std::unique_ptr<Model> card2model_;
	std::unique_ptr<Card2> card2_;

	std::unique_ptr<Model> Titlemodel_;
	std::unique_ptr<Title> Title_;

	std::unique_ptr<Model> Parametersmodel_;
	std::unique_ptr<Parameters> Parameters_;


	int mx_ = 0;
	int my_ = 0;
	
	int sceneMode_ = 0; 
	/// ゲームシーン用
	/// </summary>
};
