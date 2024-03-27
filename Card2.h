#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"Audio.h"

// 自キャラ
class Card2 {
public:
	// 初期化
	void Initialize(
	    Model* model, uint32_t textureHandle, 
		uint32_t textureHandleCD, uint32_t textureHandleDonuts,
	    uint32_t textureHandleToufu, uint32_t textureHandleRenga);

	void Start();
	// 更新
	void Update();

	//移動
	void Move();

	// 描画
	void Draw(ViewProjection& viewProjection);

	void SelectCardWithMouse();
	void SetMouse(int x, int y) {
		mouseX_ = x;
		mouseY_ = y;
	}
	void SetMode(int SetMode) { mode = SetMode; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_[4];
	// モデル
	Model* model_ = nullptr;
	//効果音
	Audio* se_ = nullptr;
	//インプット
	Input* input_ = nullptr;
	//モード
	int mode = 0;
	//カードの処理
	int selectedCardIndex_ = -1;
	int select = 0;
	int cardFlag = 0;
	//マウス
	int mouseX_ = 0;
	int mouseY_ = 0;

	float speed = 0.04f;

	//あとで消す
	int takeFlag = 0;
	int takeCount = 2;
	int eatFlag = 0;
	int eatTimer = 120;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//食材カード
	uint32_t textureHandleToufu_ = 0u;
	uint32_t textureHandleRenga_ = 0u;
	uint32_t textureHandleCD_ = 0u;
	uint32_t textureHandleDonuts_ = 0u;

	//カードを引く効果音
	uint32_t DrawHandleSE_ = 0;
	uint32_t DrawSE_ = 0;

	//カードを使う時の効果音
	uint32_t PlayHandleSE_ = 0;
	uint32_t PlaySE_ = 0;

};