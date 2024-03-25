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
	textureHandle_ = textureHandle;

	textureHandleRenga_ = textureHandleRenga;
	textureHandleCD_ = textureHandleCD;
	textureHandleToufu_ = textureHandleToufu;
	textureHandleDonuts_ = textureHandleDonuts;

	for (int i = 0; i < 3; i++) {
		worldTransform_[i].Initialize();
	}

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

	//カードを引く時の効果音
	se_ = Audio::GetInstance();
	GameDataHandleSE_ = se_->LoadWave("Audio/se.wav");
}

void Card2::Update() {
	ImGui::Text("select: %.2f" ,selectedCardIndex_);
		ImGui::Begin("card2");
		ImGui::DragFloat3("tr", &worldTransform_[1].translation_.x, 0.1f);
		ImGui::DragFloat3("rot", &worldTransform_[1].rotation_.x, 0.1f);
		ImGui::DragFloat3("sc", &worldTransform_[1].scale_.x, 0.1f);
		ImGui::End();
		//マウスの位置を取る
	Vector2 mousePosition = input_->GetMousePosition();
	ImGui::Text("Mouse Position: %d, %d", mx_,my_);
	ImGui::Text("takeCount: %d", takeCount);
	ImGui::Text("eatFlag: %d", eatFlag);
	ImGui::Text("eatTimer: %d", eatTimer);
	ImGui::Text("HP: %d", HP);
	ImGui::Text("satietyLevel: %d", satietylevel);
	ImGui::Text("scene: %d", scene);
	 // マウスでカードを選択
	SelectCardWithMouse();

	for (int i = 0; i < 3; i++) {
		worldTransform_[i].UpdateMatrix();
		// カードが選択されている場合、位置を少し上にずらす
		if (i == selectedCardIndex_) {
			worldTransform_[i].translation_.y = 1.0f;
			select = i;// ずらす距離を調整する
		} else if (i != selectedCardIndex_) {
			worldTransform_[i].translation_.y = 0.9f;
		}
	}
	Move();
}


	void Card2::Move() {
	// マウスが上の時に
	takeFlag = 0;
	
	if (my_ <= 200) {
		mode = 1;
	}
	//マウスが下の時に
	else if (my_ >= 550) {
		//カード画面になる
		mode = 0;
	}
	//カード画面の時に
	if (mode == 0) {
		//カードドロー
			if (Input::GetInstance()->IsTriggerMouse(0) && cardFlag == 0 && mx_ >= 960 &&
			    mx_ <= 1280 && my_ >= 470 && my_ <= 720) {
				//カードを引く時のBGM
				GameSceneSE_ = se_->PlayWave(GameDataHandleSE_, false);

				cardFlag = 1;
			}
			else if (Input::GetInstance()->IsTriggerMouse(0) && cardFlag == 1 &&selectedCardIndex_>=0) {
				worldTransform_[selectedCardIndex_].translation_.x = 4.0f;
				cardFlag = 0;
			}
			//ターン終了
		    if (Input::GetInstance()->IsTriggerMouse(0) && mx_ >= 50 &&
		        mx_ <= 140 && my_ >= 570 && my_ <= 650) {
			   //食べ物を追加してタイマーをリセットする
			    eatFlag = 1;
			    takeCount = 2;
			    eatTimer = 120;
			    satietylevel -= 2;
			    
			    if (satietylevel <= 0) {
				    satietylevel = 0;
				    HP -= 2;
				}
			    if (HP <= 0) {
				    scene = 2;
				}
		    }
		    
    } 
	if (mode == 1) {
		  //混ぜる
		  //カウンターが0より大きい時マウスを押せる
		    if (takeCount > 0) {
			    if (Input::GetInstance()->IsTriggerMouse(0) && 
					mx_ >= 740 && mx_ <= 960 &&
			        my_ >= 340 && my_ <= 540) {
					takeFlag = 1;
				    takeCount -= 1;
			    }
		    }
			//食べる
		    if (Input::GetInstance()->IsTriggerMouse(0) &&
				mx_ >= 340 && mx_ <= 530 && my_ >= 340 &&
		        my_ <= 530 && eatFlag == 1) {
			    eatFlag = 2;
		    }
		    if (eatFlag == 2 && eatTimer <= 120) {
			    eatTimer--;
		    }
		    if (eatTimer <= 0) {
			    eatFlag = 0;
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
	selectedCardIndex_ = -1;
	if (mx_ >= 270 && mx_ <= 470) {
		selectedCardIndex_ = 0;
	}
	if (mx_ >= 510 && mx_ <= 720) {
		selectedCardIndex_ = 1;
	}
	if (mx_ >= 740 && mx_ <= 950) {
		selectedCardIndex_ = 2;
	}
}

void Card2::Draw(ViewProjection& viewProjection) {
	if (mode == 1) {
		if (viewProjection.rotation_.x <= 0.75f) {
			viewProjection.rotation_.x += viewSpeed;
		}
		if (viewProjection.translation_.y <= 2.5f) {
			viewProjection.translation_.y += viewSpeed;
		}
		if (viewProjection.translation_.z <= -2.0f) {
			viewProjection.translation_.z += viewSpeed*2;
		}
		
		viewProjection.UpdateMatrix();
	}
	if (mode == 0) {
		if (viewProjection.rotation_.x >= 0.6f) {
			viewProjection.rotation_.x -= viewSpeed;
		}
		if (viewProjection.translation_.y >= 2.0f) {
			viewProjection.translation_.y -= viewSpeed;
		}
		if (viewProjection.translation_.z >= -3.0f) {
			viewProjection.translation_.z -= viewSpeed*2;
		}
		viewProjection.UpdateMatrix();
	}
	for (int i = 0; i < 3; i++) {
			model_->Draw(worldTransform_[i], viewProjection, textureHandle_);
	}
	
}