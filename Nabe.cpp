#include "ImGuiManager.h"
#include "Mymath.h"
#include "Nabe.h"
#include <cassert>
void Nabe::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransformOfNabe_.Initialize();
	input_ = Input::GetInstance();

	worldTransformOfNabe_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransformOfNabe_.rotation_ = {0.0f, 1.6f, 0.0f};
	worldTransformOfNabe_.scale_ = {1.0f, 1.0f, 1.0f};
}

void Nabe::Update() {
	

	ImGui::Begin("Nabe");
	ImGui::DragFloat3("tr", &worldTransformOfNabe_.translation_.x, 0.1f);
	ImGui::DragFloat3("rot", &worldTransformOfNabe_.rotation_.x, 0.1f);
	ImGui::DragFloat3("sc", &worldTransformOfNabe_.scale_.x, 0.1f);
	ImGui::End();
	worldTransformOfNabe_.UpdateMatrix();
}


void Nabe::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransformOfNabe_, viewProjection);
}