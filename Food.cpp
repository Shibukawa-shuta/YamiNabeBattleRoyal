﻿#include "Food.h"
#include "ImGuiManager.h"
#include "Mymath.h"
#include <cassert>

void Food::Initialize(
    Model* model, uint32_t textureHandle, uint32_t textureHandle2, uint32_t textureHandle3,
    uint32_t textureHandle4, uint32_t textureHandle5, uint32_t textureHandle6,uint32_t textureHandle7) {
	assert(model);
	model_ = model;

	unsigned int currentTime = (unsigned int)time(nullptr);
	srand(currentTime);
	for (int i = 0; i < 10; i++) {
		foods[i] = rand() % foodMax;
	}
	selectFood = rand() % 10;
	while (foods[selectFood] == -1) {
		selectFood = rand() % 10;
	}
	for (int i = 0; i < 5; i++) {
		worldTransform_[i].Initialize();
	}
	input_ = Input::GetInstance();
	textureHandle_[0] = textureHandle;
	textureHandle_[1] = textureHandle2;
	textureHandle_[2] = textureHandle3;
	textureHandleUi_[0] = textureHandle4;
	textureHandleUi_[1] = textureHandle5;
	textureHandleUi_[2] = textureHandle6;
	textureHandleUi_[3] = textureHandle7;

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

void Food::Update() {

	if (mode == 1) {
		// 混ぜる
// 
		// カウンターが0より大きい時マウスを押せる
		
		while (foods[selectFood] == -1) {
			selectFood = rand() % 10;
		}
		if (takeCount > 0) {
			if (Input::GetInstance()->IsTriggerMouse(0) && mx_ >= 740 && mx_ <= 960 && my_ >= 340 &&
			    my_ <= 540) {
				
				takeFlag = 1;
				//takeCount -= 1;
			}
		}
		if (takeFlag == 1 && worldTransform_[0].translation_.y > 0) {
			worldTransform_[0].translation_.y -= 0.1f;
			
			if (worldTransform_[0].translation_.y <= 0) {
				selectFood = rand() % 10;
				while (foods[selectFood] == -1) {
					selectFood = rand() % 10;
				}
				takeFlag = 0;
			}
		}
		if (takeFlag ==0 && worldTransform_[0].translation_.y < 1.5f) {
			worldTransform_[0].translation_.y += 0.1f;
		}
		// 食べる
		if (Input::GetInstance()->IsTriggerMouse(0) && mx_ >= 340 && mx_ <= 530 && my_ >= 340 &&
		    my_ <= 530 && eatFlag == 1) {
			eatFlag = 2;
			foods[selectFood] = -1;
		}
		if (eatFlag == 2 && eatTimer <= 120) {

			eatTimer--;
		}
		if (eatTimer <= 0) {
			eatFlag = 0;
		}
	}
	
	ImGui::Begin("card");
	ImGui::DragFloat3("tr", &worldTransform_[0].translation_.x, 0.1f);
	ImGui::DragFloat3("rot", &worldTransform_[0].rotation_.x, 0.1f);
	ImGui::DragFloat3("sc", &worldTransform_[0].scale_.x, 0.1f);
	ImGui::End();

	ImGui::Begin("Foods");
	for (int i = 0; i < 10; i++) {
		ImGui::InputInt("i", &foods[i]);
	}
	ImGui::End();

	ImGui::Begin("use");
	ImGui::DragFloat3("tr", &worldTransform_[4].translation_.x, 0.1f);
	ImGui::DragFloat3("rot", &worldTransform_[4].rotation_.x, 0.1f);
	ImGui::DragFloat3("sc", &worldTransform_[4].scale_.x, 0.1f);
	ImGui::End();

	for (int i = 0; i < 5; i++) {
		worldTransform_[i].UpdateMatrix();
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

void Food::Start() {
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

void Food::Draw(ViewProjection& viewProjection) {
	if (mode == 1) {

		for (int i = 0; i < 5; i++) {
			if (eatFlag >= 1 && foods[selectFood]==0) {
				model_->Draw(worldTransform_[0], viewProjection, textureHandle_[0]);
			}
			if (eatFlag >= 1 && foods[selectFood] == 1) {
				model_->Draw(worldTransform_[0], viewProjection, textureHandle_[1]);
			}
			if (eatFlag >= 1 && foods[selectFood] == 2) {
				model_->Draw(worldTransform_[0], viewProjection, textureHandle_[2]);
			}
			//混ぜる
	
			model_->Draw(worldTransform_[1], viewProjection, textureHandleUi_[0]);
			//食べる
	
			model_->Draw(worldTransform_[2], viewProjection, textureHandleUi_[1]);
		}
	}
	if (mode == 0) {
		model_->Draw(worldTransform_[3], viewProjection, textureHandleUi_[2]);
		model_->Draw(worldTransform_[4], viewProjection, textureHandleUi_[3]);
	}
}