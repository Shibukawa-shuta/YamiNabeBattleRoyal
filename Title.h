#pragma once
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
class Title {
public:
	void Initialize(Model* model, uint32_t textureHandleTitle);
	int Update();
	void SetScene(int SetScene) { scene = SetScene; }
	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	uint32_t textureHandleTitle_ = 0u;
	Input* input_ = nullptr;
	Model* model_ = nullptr;

	int scene = 0;
};
