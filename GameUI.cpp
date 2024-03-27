#include "GameUI.h"
#include "ImGuiManager.h"
#include "Mymath.h"
#include <cassert>

void GameUI::Initialize(
    Model* model, uint32_t textureHandleShake, uint32_t textureHandleEat,
    uint32_t textureHandleTurnend) {
	assert(model);
	model_ = model;

	for (int i = 0; i < 5; i++) {
		worldTransform_[i].Initialize();
	}

	input_ = Input::GetInstance();
	textureHandleShake_ = textureHandleShake;
	textureHandleEat_ = textureHandleEat;
	textureHandleTurnend_ = textureHandleTurnend;

	worldTransform_[0].translation_ = {0.0f, 1.5f, -0.5f};
	worldTransform_[0].rotation_ = {0.3f, 0.0f, 0.0f};
	worldTransform_[0].scale_ = {0.5f, 0.5f, 0.0f};

	// 混ぜる
	worldTransform_[1].translation_ = {0.4f, 1.3f, -0.9f};
	worldTransform_[1].rotation_ = {0.8f, 0.0f, 0.0f};
	worldTransform_[1].scale_ = {0.2f, 0.2f, 0.001f};
	// 食べる
	worldTransform_[2].translation_ = {-0.4f, 1.3f, -0.9f};
	worldTransform_[2].rotation_ = {0.8f, 0.0f, 0.0f};
	worldTransform_[2].scale_ = {0.2f, 0.2f, 0.001f};

	// ターン終了
	worldTransform_[3].translation_ = {-1.4f, 0.2f, -1.5f};
	worldTransform_[3].rotation_ = {0.8f, 0.0f, 0.0f};
	worldTransform_[3].scale_ = {0.15f, 0.15f, 0.001f};
}

void GameUI::Update() {
	TurnEnd();
	// Imgui　ここから　↓
	ImGui::Begin("card");
	ImGui::DragFloat3("tr", &worldTransform_[0].translation_.x, 0.1f);
	ImGui::DragFloat3("rot", &worldTransform_[0].rotation_.x, 0.1f);
	ImGui::DragFloat3("sc", &worldTransform_[0].scale_.x, 0.1f);
	ImGui::End();

	ImGui::Begin("use");
	ImGui::DragFloat3("tr", &worldTransform_[4].translation_.x, 0.1f);
	ImGui::DragFloat3("rot", &worldTransform_[4].rotation_.x, 0.1f);
	ImGui::DragFloat3("sc", &worldTransform_[4].scale_.x, 0.1f);
	ImGui::End();
	// ここまで　↑

	for (int i = 0; i < 5; i++) {
		worldTransform_[i].UpdateMatrix();
	}
}

void GameUI::Start() {
	worldTransform_[0].translation_ = {0.0f, 1.5f, -0.5f};
	worldTransform_[0].rotation_ = {0.3f, 0.0f, 0.0f};
	worldTransform_[0].scale_ = {0.5f, 0.5f, 0.001f};

	worldTransform_[1].translation_ = {0.4f, 1.3f, -0.9f};
	worldTransform_[1].rotation_ = {0.8f, 0.0f, 0.0f};
	worldTransform_[1].scale_ = {0.2f, 0.2f, 0.001f};

	worldTransform_[2].translation_ = {-0.4f, 1.3f, -0.9f};
	worldTransform_[2].rotation_ = {0.8f, 0.0f, 0.0f};
	worldTransform_[2].scale_ = {0.2f, 0.2f, 0.001f};
}

void GameUI::TurnEnd() {
	// マウスの位置を取る
	Vector2 mousePosition = input_->GetMousePosition();
	mouseX_ = (int)mousePosition.x;
	mouseY_ = (int)mousePosition.y;

	// ターン終了
	if (Input::GetInstance()->IsTriggerMouse(0) && mouseX_ >= 50 && mouseX_ <= 140 &&
	    mouseY_ >= 570 && mouseY_ <= 650) {
		cardFlag = 1;
	}
}

void GameUI::Draw(ViewProjection& viewProjection) {
	// 画面が上の時に
	if (mode == 1) {
		//混ぜる
		model_->Draw(worldTransform_[1], viewProjection, textureHandleShake_);
		//食べる
		model_->Draw(worldTransform_[2], viewProjection, textureHandleEat_);
	}
	// 画面が下の時に
	if (mode == 0) {
		//ターン終了
		model_->Draw(worldTransform_[3], viewProjection, textureHandleTurnend_);
	}
}