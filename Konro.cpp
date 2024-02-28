#include "ImGuiManager.h"
#include "Mymath.h"
#include "Konro.h"
#include <cassert>
void Konro::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransformOfKonro_.Initialize();
	input_ = Input::GetInstance();

	worldTransformOfKonro_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransformOfKonro_.rotation_ = {0.0f, 4.715f, 0.0f};
	worldTransformOfKonro_.scale_ = {1.0f, 1.0f, 1.0f};
}

void Konro::Update() {

	ImGui::Begin("Konro");
	ImGui::DragFloat3("tr", &worldTransformOfKonro_.translation_.x, 0.1f);
	ImGui::DragFloat3("rot", &worldTransformOfKonro_.rotation_.x, 0.1f);
	ImGui::DragFloat3("sc", &worldTransformOfKonro_.scale_.x, 0.1f);
	ImGui::End();
	worldTransformOfKonro_.UpdateMatrix();
}

void Konro::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransformOfKonro_, viewProjection);
}