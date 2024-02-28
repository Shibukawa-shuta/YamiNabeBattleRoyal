#include "ImGuiManager.h"
#include "Mymath.h"
#include "kotatsu.h"
#include <cassert>
void kotatsu::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransformOfKotatsu_.Initialize();
	input_ = Input::GetInstance();

	worldTransformOfKotatsu_.translation_ = {0.0f, -1.7f, 0.0f};
	worldTransformOfKotatsu_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformOfKotatsu_.scale_ = {3.0f, 3.0f, 3.0f};
}

void kotatsu::Update() {

	ImGui::Begin("kotatsu");
	ImGui::DragFloat3("tr", &worldTransformOfKotatsu_.translation_.x, 0.1f);
	ImGui::DragFloat3("rot", &worldTransformOfKotatsu_.rotation_.x, 0.1f);
	ImGui::DragFloat3("sc", &worldTransformOfKotatsu_.scale_.x, 0.1f);
	ImGui::End();
	worldTransformOfKotatsu_.UpdateMatrix();
}

void kotatsu::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransformOfKotatsu_, viewProjection);
}

