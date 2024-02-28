#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

// 自キャラ
class Card {
public:
	// 初期化
	void Initialize(
	    Model* model, uint32_t textureHandel, uint32_t textureHandel2, uint32_t textureHandel3);

	// 更新
	void Update();

	// 描画
	void Draw(ViewProjection& viewProjection);

	void SetMode(int SetMode) { mode = SetMode; }
	void SetTakeFlag(int setTake) { takeFlag = setTake; }
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;

	int mode = 0;
	int takeFlag = 0;
	int type = 0;
	Input* input_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	uint32_t textureHandle2_ = 0u;
	uint32_t textureHandle3_ = 0u;

};