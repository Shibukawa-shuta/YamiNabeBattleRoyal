#include "ImGuiManager.h"
#include "Mymath.h"
#include "Card2.h"
#include <cassert>

void Card2::Initialize(
    Model* model, uint32_t textureHandle, uint32_t textureHandleCD, uint32_t textureHandleDonuts,
    uint32_t textureHandleToufu, uint32_t textureHandleRenga) {
	assert(model);
	model_ = model;
	input_ = Input::GetInstance();
	for (int i = 0; i < 3; i++) {
		worldTransform_[i].Initialize();
	}

	//カード　↓
	textureHandle_ = textureHandle;
	textureHandleRenga_ = textureHandleRenga;
	textureHandleCD_ = textureHandleCD;
	textureHandleToufu_ = textureHandleToufu;
	textureHandleDonuts_ = textureHandleDonuts;
	//ここまで　↑


	//カードの位置　↓
	//左
	worldTransform_[0].translation_ = {1.4f, 0.9f, -1.98f};
	worldTransform_[0].rotation_ = {0.9f, 0.0f, 0.0f};
	worldTransform_[0].scale_ = {0.18f, 0.25f, 0.00f};
	//真ん中
	worldTransform_[1].translation_ = {1.4f, 0.9f, -1.98f};
	worldTransform_[1].rotation_ = {0.9f, 0.0f, 0.0f};
	worldTransform_[1].scale_ = {0.18f, 0.25f, 0.00f};
	//右
	worldTransform_[2].translation_ = {1.4f, 0.9f, -1.98f};
	worldTransform_[2].rotation_ = {0.9f, 0.0f, 0.0f};
	worldTransform_[2].scale_ = {0.18f, 0.25f, 0.00f};
	//ここまで　↑

	
	//カードを引く時の効果音
	se_ = Audio::GetInstance();
	DrawHandleSE_ = se_->LoadWave("Audio/drawSe.wav");
	
	//カードを使う時の効果音
	se_ = Audio::GetInstance();
	PlayHandleSE_ = se_->LoadWave("Audio/playSe.wav");

	//カードテクスチャ

}

void Card2::Update() {
	ImGui::Text("select: %.2f" ,selectedCardIndex_);
		ImGui::Begin("card2");
		ImGui::DragFloat3("tr", &worldTransform_[1].translation_.x, 0.1f);
		ImGui::DragFloat3("rot", &worldTransform_[1].rotation_.x, 0.1f);
		ImGui::DragFloat3("sc", &worldTransform_[1].scale_.x, 0.1f);
		ImGui::End();

	    ImGui::Text("Mouse Position: %d, %d", mouseX_, mouseY_);
	    ImGui::Text("takeCount: %d", takeCount);
	    ImGui::Text("eatFlag: %d", eatFlag);
	    ImGui::Text("eatTimer: %d", eatTimer);
	//マウスの位置を取る
		Vector2 mousePosition = input_->GetMousePosition();
	    mouseX_ = (int)mousePosition.x;
		mouseY_ = (int)mousePosition.y;
	 // マウスでカードを選択
	SelectCardWithMouse();
	Move();
}


	void Card2::Move() {
	takeFlag = 0;
	//カード画面の時に
	if (mode == 0) {

		//カードを使う
		  if (Input::GetInstance()->IsTriggerMouse(0) && cardFlag == 1 &&selectedCardIndex_>=0) {
				worldTransform_[selectedCardIndex_].translation_.x = 4.0f;
				cardFlag = 0;
		  }
			//ターン終了
		    if (Input::GetInstance()->IsTriggerMouse(0) && mouseX_ >= 50 &&
		        mouseX_ <= 140 && mouseY_ >= 570 && mouseY_ <= 650) {
			   //食べ物を追加してタイマーをリセットする
			    eatFlag = 1;
			    takeCount = 2;
			    eatTimer = 120; 
				cardFlag = 1;
			    // カードを引く時のBGM
			    DrawSE_ = se_->PlayWave(DrawHandleSE_, false);
		    }
		    
    } 
	

	//カードを座標まで持っていく
	if (worldTransform_[0].translation_.x >= -0.4f && cardFlag == 1) {
		worldTransform_[0].translation_.x -= speed;
	}
	if (worldTransform_[1].translation_.x >= 0.0f && cardFlag == 1) {
		worldTransform_[1].translation_.x -= speed;
	}
	if (worldTransform_[2].translation_.x >= 0.4f && cardFlag == 1) {
		worldTransform_[2].translation_.x -= speed;
	}	
}
    
	//初期値に戻す
	void Card2::Start() {
	worldTransform_[0].translation_ = {1.4f, 0.9f, -1.98f};
	worldTransform_[0].rotation_ = {0.9f, 0.0f, 0.0f};
	worldTransform_[0].scale_ = {0.18f, 0.25f, 0.00f};

	worldTransform_[1].translation_ = {1.4f, 0.9f, -1.98f};
	worldTransform_[1].rotation_ = {0.9f, 0.0f, 0.0f};
	worldTransform_[1].scale_ = {0.18f, 0.25f, 0.00f};

	worldTransform_[2].translation_ = {1.4f, 0.9f, -1.98f};
	worldTransform_[2].rotation_ = {0.9f, 0.0f, 0.0f};
	worldTransform_[2].scale_ = {0.18f, 0.25f, 0.00f};

	 eatFlag = 1;
 }

void Card2::SelectCardWithMouse() {
	// マウスの座標を取得
	 Vector2 mousePosition = input_->GetMousePosition();
	 mouseX_ = (int)mousePosition.x;
	 mouseY_ = (int)mousePosition.y;
	selectedCardIndex_ = -1;
	//カード選択
	if (mouseX_ >= 270 && mouseX_ <= 470) {
		selectedCardIndex_ = 0;
	}
	if (mouseX_ >= 510 && mouseX_ <= 720) {
		selectedCardIndex_ = 1;
	}
	if (mouseX_ >= 740 && mouseX_ <= 950) {
		selectedCardIndex_ = 2;
	}

	//カードを選択しているかの判定
	for (int i = 0; i < 3; i++) {
		worldTransform_[i].UpdateMatrix();
		// カードが選択されている場合、位置を少し上にずらす
		if (i == selectedCardIndex_) {
			    worldTransform_[i].translation_.y = 1.0f;
			    select = i; // ずらす距離を調整する
		} else if (i != selectedCardIndex_) {
			    worldTransform_[i].translation_.y = 0.9f;
		}
	}
}

void Card2::Draw(ViewProjection& viewProjection) {
	//カード描画
	for (int i = 0; i < 3; i++) {
			model_->Draw(worldTransform_[i], viewProjection, textureHandle_);
	}
}