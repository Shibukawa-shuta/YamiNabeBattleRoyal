#include "Title.h"
#include "GameScene.h"
#include "ImGuiManager.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <TextureManager.h>


void Title::Initialize(Model* model, uint32_t textureHandleTitle) {
	assert(model);
	model_ = model;
	input_ = Input::GetInstance();
	textureHandleTitle_ = textureHandleTitle;

	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 1.4f, -1.6f};
	worldTransform_.rotation_ = {0.6f,0.0f,0.0f};
	worldTransform_.scale_ = {1.0f,1.0f, 0.001f};
	worldTransform_.UpdateMatrix();
}

bool Title::Update() {
	timer_++;
	if (scene == 0 && input_->TriggerKey(DIK_SPACE)) {
	
		return true;
	}  
	
	return false;
}

void Title::Draw(ViewProjection& viewProjection) {
	
		model_->Draw(worldTransform_, viewProjection, textureHandleTitle_);

}
