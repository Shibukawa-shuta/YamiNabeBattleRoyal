#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"Object.h"
#include"card.h"
#include"Card2.h"
#include"deck.h"
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
	uint32_t textureHandleBG_ = 0;
	Sprite* spriteBG_ = nullptr;

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
	

	// シーン切り替え
	int sceneMode_ = 1;

	// タイトル
	void TitleUpdate();
	void TitleDraw2DNear();

	// タイトル (スプライト)
	uint32_t textureHandleTitle_ = 0;
	Sprite* spriteTitle_ = nullptr;

	// タイトル (文字)
	uint32_t textureHandleTitleEnter_ = 0;
	Sprite* spriteEnter_ = nullptr;

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	uint32_t textureHandle_ = 0;
	uint32_t textureHandle2_ = 0;
	uint32_t textureHandle3_ = 0;

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

	int mx_ = 0;
	int my_ = 0;
	

	/// ゲームシーン用
	/// </summary>
};
