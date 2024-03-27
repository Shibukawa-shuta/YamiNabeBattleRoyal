#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"time.h"
#include<stdlib.h>
// 自キャラ
class Food {
public:
	// 初期化
	void Initialize(Model* model, uint32_t textureHandle, uint32_t textureHandle2, uint32_t textureHandle3);
	// 更新
	void Update();

	// 描画
	void Draw(ViewProjection& viewProjection);

	void Start();
	void SetTakeCount(int setTakeCount) { takeCount = setTakeCount; }
	void SetMode(int SetMode) { mode = SetMode; }

	// ワールド変換データ
	WorldTransform worldTransform_[5];
	// 食材モデル
	Model* model_ = nullptr;

	void SetMouse(int x, int y) {
		mouseX_ = x;
		mouseY_ = y;
	}

	int mode = 0;
	int takeFlag = 0;
	int eatFlag = 1;
	int eatTimer = 120;
	int type = 0;
	int takeCount = 2;

	//鍋の中身
	int foods[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int foodMax = 3;
	int selectFood = 0;
	int mixedCount = 0;

	int mouseX_ = 0;
	int mouseY_ = 0;

	Input* input_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_[10];
	uint32_t textureHandleUi_[10];

};