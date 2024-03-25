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
	void Initialize(
	    Model* model, uint32_t textureHandle, uint32_t textureHandle2, uint32_t textureHandle3,
	    uint32_t textureHandle4, uint32_t textureHandle5, uint32_t textureHandle6,
	    uint32_t textureHandle7);
	// 更新
	void Update();

	// 描画
	void Draw(ViewProjection& viewProjection);

	void Start();
	void SetTakeCount(int setTakeCount) { takeCount = setTakeCount; }

	void SetMode(int SetMode) { mode = SetMode; }
	void SetHP(int setHp) { HP = setHp; }
	void SetSatietyLevel(int setsatietylevel) { satietylevel = setsatietylevel; }
	// ワールド変換データ
	WorldTransform worldTransform_[5];
	// 食材モデル
	Model* model_ = nullptr;

	void SetMouse(int x, int y) {
		mx_ = x;
		my_ = y;
	}

	int mode = 0;
	int takeFlag = 0;
	int eatFlag = 1;
	int eatTimer = 120;
	int type = 0;
	int takeCount = 2;

	//鍋の中身
	int foods[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int foodMax = 2;
	int selectFood = 0;
	int mixedCount = 0;

	int mx_ = 0;
	int my_ = 0;

	int HP = 10;
	int satietylevel = 10;
	Input* input_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	uint32_t textureHandle2_ = 0u;
	uint32_t textureHandle3_ = 0u;
	uint32_t textureHandle4_ = 0u;
	uint32_t textureHandle5_ = 0u;
	uint32_t textureHandle6_ = 0u;
	uint32_t textureHandle7_ = 0u;

};