#include "card.h"
#include "ImGuiManager.h"
#include "Mymath.h"
#include <cassert>

void Card::Initialize(
    Model* model, uint32_t textureHandle, uint32_t textureHandle2, uint32_t textureHandle3,
    uint32_t textureHandle4, uint32_t textureHandle5, uint32_t textureHandle6,uint32_t textureHandle7) {
	assert(model);
	model_ = model;
	for (int i = 0; i < 5; i++) {
		worldTransform_[i].Initialize();
	}
	input_ = Input::GetInstance();
	textureHandle_ = textureHandle;
	textureHandle2_ = textureHandle2;
	textureHandle3_ = textureHandle3;
	textureHandle4_ = textureHandle4;
	textureHandle5_ = textureHandle5;
	textureHandle6_ = textureHandle6;
	textureHandle7_ = textureHandle7;

	worldTransform_[0].translation_ = {0.0f, 1.5f, -0.5f};
	worldTransform_[0].rotation_ = {0.3f, 0.0f, 0.0f};
	worldTransform_[0].scale_ = {0.5f, 0.5f, 0.0f};

	//混ぜる
	worldTransform_[1].translation_ = {0.4f, 1.3f, -0.9f};
	worldTransform_[1].rotation_ = {0.8f, 0.0f, 0.0f};
	worldTransform_[1].scale_ = {0.2f, 0.2f, 0.001f};
	//食べる
	worldTransform_[2].translation_ = {-0.4f, 1.3f, -0.9f};
	worldTransform_[2].rotation_ = {0.8f, 0.0f, 0.0f};
	worldTransform_[2].scale_ = {0.2f, 0.2f, 0.001f};

	// ターン終了
	worldTransform_[3].translation_ = {-1.4f, 0.2f, -1.5f};
	worldTransform_[3].rotation_ = {0.8f, 0.0f, 0.0f};
	worldTransform_[3].scale_ = {0.15f, 0.15f, 0.001f};

	worldTransform_[4].translation_ = {1.4f, 0.2f, -1.35f};
	worldTransform_[4].rotation_ = {1.5f, 0.0f, 0.0f};
	worldTransform_[4].scale_ = {0.25f, 0.25f, 0.001f};

}

void Card::Update() {

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

	for (int i = 0; i < 5; i++) {
		worldTransform_[i].UpdateMatrix();
	}
	if (takeFlag == 1 && eatFlag == 1) {
		type = rand() % 3;
	}

	if (takeCount == 0) {
		worldTransform_[1].scale_ = {0.2f, 0.2f, 0.0f};
	} else if (takeCount >= 0) {
		worldTransform_[1].scale_ = {0.2f, 0.2f, 0.001f};
	}
	
	if (eatFlag == 0) {
		// 食べる
		worldTransform_[2].scale_ = {0.2f, 0.2f, 0.0f};
	} else if(eatFlag == 1){
		worldTransform_[2].scale_ = {0.2f, 0.2f, 0.001f};
	}
	if (eatFlag == 1) {
		worldTransform_[0].scale_ = {0.5f, 0.5f, 0.0f};
	}
	if (eatFlag == 2) {
		worldTransform_[0].scale_ = {0.5f, 0.5f, 0.001f};
	}
}

void Card::Start() {
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

void Card::Draw(ViewProjection& viewProjection) {
	if (mode == 1) {
		for (int i = 0; i < 5; i++) {
			if (eatFlag >= 1 && type == 0) {
				model_->Draw(worldTransform_[0], viewProjection, textureHandle_);
			}
			if (eatFlag >= 1 && type == 1) {
				model_->Draw(worldTransform_[0], viewProjection, textureHandle2_);
			}
			if (eatFlag >= 1 && type == 2) {
				model_->Draw(worldTransform_[0], viewProjection, textureHandle3_);
			}
			model_->Draw(worldTransform_[1], viewProjection, textureHandle4_);
			model_->Draw(worldTransform_[2], viewProjection, textureHandle5_);
		}
	}
	if (mode == 0) {
		model_->Draw(worldTransform_[3], viewProjection, textureHandle6_);
		model_->Draw(worldTransform_[4], viewProjection, textureHandle7_);
	}
}