#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"


// 自キャラ
class Card2 {
public:
	// 初期化
	void Initialize(Model* model, uint32_t textureHandel);

	

	int GetMode() { return mode; }
	int GetTakeFlag() { return takeFlag; }
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
	WorldTransform worldTransform_[3];
	// モデル
	Model* model_ = nullptr;

	int selectedCardIndex_ = -1;
	float originePos = 0.64f;

	int Mid = 0;
	int Right = 0;
	int Left = 0;
	
	float Left1 = -0.4f;
	float Right1 = 0.0f;
	float Mid1 = 0.4f;

	int mode = 0;
	int select = 0;
	int cardFlag = 0;
	
	int mx_ = 0;
	int my_ = 0;

	float speed = 0.04f;
	float viewSpeed = 0.025f;
	
	int takeFlag = 0;
	int takeCount = 2;


	Input* input_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};