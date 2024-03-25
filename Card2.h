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
	
	
	int GetMode() { return mode; }
	int GetHP() { return HP; }
	int GetSatietyLevel() { return satietylevel; }
	int Getscene() { return scene; }
	// 更新
	void Update();

	//移動
	void Move();

	// 描画
	void Draw(ViewProjection& viewProjection);

	void SelectCardWithMouse();

	
	void SetMouse(int x, int y) {
		mx_ = x;
		my_ = y;
	}
	

private:
	// ワールド変換データ
	WorldTransform worldTransform_[4];
	// モデル
	Model* model_ = nullptr;
	//効果音
	Audio* se_ = nullptr;

	int selectedCardIndex_ = -1;
	
	int mode = 0;
	int select = 0;
	int cardFlag = 0;
	
	int mx_ = 0;
	int my_ = 0;

	float speed = 0.04f;
	float viewSpeed = 0.025f;
	
	int takeFlag = 0;
	int takeCount = 2;
	int eatFlag = 0;
	int eatTimer = 120;

	int HP = 10;
	int satietylevel = 10;
	int scene = 0;
	Input* input_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	uint32_t textureHandleToufu_ = 0u;
	uint32_t textureHandleRenga_ = 0u;
	uint32_t textureHandleCD_ = 0u;
	uint32_t textureHandleDonuts_ = 0u;

	//ゲームプレイ効果音
	uint32_t GameDataHandleSE_ = 0;
	uint32_t GameSceneSE_ = 0;
};