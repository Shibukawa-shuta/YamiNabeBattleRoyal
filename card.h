#pragma once
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

// 自キャラ
class Card {
public:
	// 初期化
	void Initialize(Model* model, uint32_t textureHandel);

	// 更新
	void Update();

	// 描画
	void Draw(ViewProjection& viewProjection);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;

	Input* input_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};
