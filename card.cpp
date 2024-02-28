#include "card.h"
#include "ImGuiManager.h"
#include "Mymath.h"
#include <cassert>

void Card::Initialize(
    Model* model, uint32_t textureHandle, uint32_t textureHandle2, uint32_t textureHandle3) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	textureHandle_ = textureHandle;
	textureHandle2_ = textureHandle2;
	textureHandle3_ = textureHandle3;

	worldTransform_.translation_ = {0.0f, 1.0f, -1.1f};
	worldTransform_.rotation_ = {0.3f, 0.0f, 0.0f};
	worldTransform_.scale_ = {0.6f, 0.6f, 0.001f};

}

void Card::Update() {

	ImGui::Begin("card");
	ImGui::DragFloat3("tr", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rot", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("sc", &worldTransform_.scale_.x, 0.1f);
	ImGui::End();

	worldTransform_.UpdateMatrix();
	if (takeFlag == 1) {
		type = rand()%3;
	}
}

void Card::Draw(ViewProjection& viewProjection) {
	if (mode == 1) {
		if (type == 0) {
			model_->Draw(worldTransform_, viewProjection, textureHandle_);
		}
		if (type == 1) {
			model_->Draw(worldTransform_, viewProjection, textureHandle2_);
		}
		if (type == 2) {
			model_->Draw(worldTransform_, viewProjection, textureHandle3_);
		}
		
	}
}