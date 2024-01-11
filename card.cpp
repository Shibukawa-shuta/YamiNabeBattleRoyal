#include "card.h"
#include <cassert>
#include "ImGuiManager.h"
#include "Mymath.h"

void Card::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	textureHandle_ = textureHandle;
}

void Card::Update() { 
	
	ImGui::Begin("card");
	ImGui::DragFloat3("tr", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rot", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("sc", &worldTransform_.scale_.x, 0.1f);
	ImGui::End();
	
	worldTransform_.UpdateMatrix();
}


void Card::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}