#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

// 自キャラ
class Card {
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
	void SetTakeFlag(int setTake) { takeFlag = setTake; }
	void SetEatFlag(int setEat) { eatFlag = setEat; }
	void SetEatTimer(int setEattimer) { eatTimer = setEattimer; }
	// ワールド変換データ
	WorldTransform worldTransform_[5];
	// モデル
	Model* model_ = nullptr;

	int mode = 0;
	int takeFlag = 0;
	int eatFlag = 1;
	int eatTimer = 120;
	int type = 0;
	int takeCount = 2;

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