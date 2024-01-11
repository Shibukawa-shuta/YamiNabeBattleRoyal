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

	uint32_t textureHandleFood_ = 0;
	Sprite* spriteFood_ = nullptr;

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

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	uint32_t textureHandle_ = 0;

	std::unique_ptr<Model> NabeModel_;
	std::unique_ptr<Nabe> Nabe_;

	std::unique_ptr<Model> kotatsuModel_;
	std::unique_ptr<kotatsu>kotatsu_;
	
	std::unique_ptr<Model> konroModel_;
	std::unique_ptr<Konro>konro_;

	std::unique_ptr<Model> deckModel_;
	std::unique_ptr<deck> deck_;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
