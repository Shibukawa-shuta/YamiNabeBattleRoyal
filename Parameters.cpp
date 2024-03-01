#include "Parameters.h"
#include "ImGuiManager.h"
#include "Mymath.h"
#include <cassert>

void Parameters::Update(){
	ImGui::Text("HP: %d", HP);
	ImGui::Text("satietyLevel: %d", satietylevel);
}

void Parameters::Move() {
	if (mode == 0) {
		if (Input::GetInstance()->IsTriggerMouse(0) && mx_ >= 50 && mx_ <= 140 && my_ >= 570 &&
		    my_ <= 650) {
			// 食べ物を追加してタイマーをリセットする
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
	}