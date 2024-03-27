#pragma once

#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

// 自キャラ
class GameUI {
public:
	// 初期化
	void Initialize(
	    Model* model, uint32_t textureHandleShake, uint32_t textureHandleEat,
	    uint32_t textureHandleTurnend);

	// 更新
	void Update();

	// 描画
	void Draw(ViewProjection& viewProjection);

	void Start();

	void TurnEnd();

	void Eat();

	void Shake();

	void SetMode(int SetMode) { mode = SetMode; }
	void SetCardFlag(int SetCardFlag) { cardFlag = SetCardFlag; }

	void SetMouse(int x, int y) {
		mouseX_ = x;
		mouseY_ = y;
	}
	// ワールド変換データ
	WorldTransform worldTransform_[5];
	// モデル
	Model* model_ = nullptr;

	// カメラから受け渡し　モード
	int mode = 0;

	int mouseX_ = 0;
	int mouseY_ = 0;

	// カードの処理　ここから↓
	int select = 0;
	int cardFlag = 0;
	// ここまで　↑

	Input* input_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandleShake_ = 0u;
	uint32_t textureHandleEat_ = 0u;
	uint32_t textureHandleTurnend_ = 0u;
};