#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"



//パラメータ表示
class Parameters {
public:
	//初期化
	void Initialize(
	    Model* model, uint32_t textureHandle, uint32_t textureHandleCD,
	    uint32_t textureHandleDonuts, uint32_t textureHandleToufu, uint32_t textureHandleRenga);

	void Start();
	int GetHP() { return HP; }
	int GetSatietyLevel() { return satietylevel; }

	void SetHP(int setHp) { HP = setHp; }
	void SetSatietyLevel(int setsatietylevel) { satietylevel = setsatietylevel; }


	void Update();

	void Move();

private:
	// ワールド変換データ
	WorldTransform worldTransform_[4];
	// モデル
	Model* model_ = nullptr;

	int mx_ = 0;
	int my_ = 0;

	int takeFlag = 0;
	int takeCount = 2;
	int eatFlag = 0;
	int eatTimer = 120;

	int mode = 0;
	int HP = 10;
	int satietylevel = 10;

	int scene = 0;
};
