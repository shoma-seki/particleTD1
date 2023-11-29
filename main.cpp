#include <Novice.h>
#include "Functions.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ImGuiManager.h>

const int kParticleMax = 700;

struct Emitter {
	Vector2Array translate;
	Vector2Array scale;
	Vector2 direction1;
	Vector2 direction2;
	Vector2 direction3;
	Vector2 direction4;
	Vector2 range;
	int aliveRange;
	int aliveTime;
	int alpha;
	int amount;
	int scaleRange;
	int scaleRangeUnder;
	float velocity;
	float velocityRange;
	float velocityRangeUnder;
	float acceleration;
	float x;
	float theta;
	float directionThetaX;
	float directionTheta;
	float directionThetaRange;
	float thetaDirection;
	float thetaDirectionX;
	float tx;
	float ty;
	bool isActive;
	bool isAll;
	bool isMapCollisionIsActive;
	bool isVelocityRandom;
	bool isRotate;
	bool isScaleRandom;
	bool isAccelerating;
	bool isGravity;
};

struct Particle {
	Vector2Array translate[kParticleMax];
	Vector2Array scale[kParticleMax];
	Vector2 direction[kParticleMax];
	float velocity[kParticleMax];
	float acceleration[kParticleMax];
	float x[kParticleMax];
	float theta[kParticleMax];
	float directionThetaX[kParticleMax];
	float directionTheta[kParticleMax];
	int aliveRange[kParticleMax];
	int aliveTime[kParticleMax];
	int alpha[kParticleMax];
	int count[kParticleMax];
	bool isActive[kParticleMax];
	unsigned int color[kParticleMax];
	unsigned int colorN[kParticleMax];
	Matrix3x3 AffineMatrix[kParticleMax];
	Vector2Array leftTop[kParticleMax];
	Vector2Array rightTop[kParticleMax];
	Vector2Array leftBottom[kParticleMax];
	Vector2Array rightBottom[kParticleMax];
	Vector2Array worldLeftTop[kParticleMax];
	Vector2Array worldRightTop[kParticleMax];
	Vector2Array worldLeftBottom[kParticleMax];
	Vector2Array worldRightBottom[kParticleMax];
};

struct ClampMaxMin {
	float xMax;
	float yMax;
	float xMin;
	float yMin;
};

const int MapSizeX = 40;
const int MapSizeY = 22;

void Emit(Emitter& emit, Particle& par);
void Move(Particle& par, Emitter& emit, int Map[MapSizeY][MapSizeX]);
void Display(Particle par, const int texture);

const char kWindowTitle[] = "学籍番号";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	srand(unsigned int(time(nullptr)));

	int Map[MapSizeY][MapSizeX]{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	};

	Emitter emit{};
	Particle par{};
	ClampMaxMin clamp{};
	clamp.xMax = 0.5f;
	clamp.xMin = -0.5f;
	clamp.yMax = 1;
	clamp.yMin = 0.7f;

	emit.range = { 2500,-20 };
	emit.amount = 1;
	emit.scaleRange = 1;
	emit.aliveRange = 100;
	emit.directionThetaRange = 1;
	emit.velocityRange = 1;
	emit.velocityRangeUnder = 1;
	emit.scaleRange = 1;
	emit.scaleRangeUnder = 1;
	for (int i = 0; i < kParticleMax; i++) {
		par.color[i] = 0xFFFFFF;
		par.isActive[i] = false;
	}

	int mouX = 0;
	int mouY = 0;

	//const int kWhiteTex = Novice::LoadTexture("white1x1.png");
	const int kParTex1 = Novice::LoadTexture("./player3.png");

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///		
		Novice::GetMousePosition(&mouX, &mouY);
		emit.translate.vector2[0] = float(mouX);
		emit.translate.vector2[1] = float(mouY);
		emit.isActive = true;
		Emit(emit, par);
		Move(par, emit, Map);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		for (int i = 0; i < MapSizeX; i++) {
			for (int j = 0; j < MapSizeY; j++) {
				if (Map[j][i] == 1) {
					Novice::DrawBox(i * 32, j * 32, 32, 32, 0.0f, 0xDDAAAAFF, kFillModeSolid);
				}
			}
		}
		Display(par, kParTex1);

		//IMGUI
		ImGui::Begin("Particle");
		ImGui::SliderInt("aliveRange", &emit.aliveRange, 0, 1000);
		ImGui::SliderInt("scaleRange", &emit.scaleRange, 1, 10);
		ImGui::SliderInt("scaleRangeUnder", &emit.scaleRangeUnder, 1, 10);
		ImGui::SliderFloat("velocity", &emit.velocity, 1, 10);
		ImGui::SliderFloat("velocityRange", &emit.velocityRange, 1, 10);
		ImGui::SliderFloat("velocityRangeUnder", &emit.velocityRangeUnder, 1, 10);
		ImGui::SliderInt("amount", &emit.amount, 1, 10);
		ImGui::SliderFloat("thetaRange", &emit.directionThetaRange, 1, 36);
		ImGui::SliderFloat("thetaDirection", &emit.thetaDirectionX, 0, 1);
		ImGui::SliderInt("aliveRange", &emit.aliveRange, 1, 360);
		ImGui::SliderFloat("acceleration", &emit.acceleration, -3, 3);
		ImGui::Checkbox("isVelocityRandom", &emit.isVelocityRandom);
		ImGui::Checkbox("isScaleRandom", &emit.isScaleRandom);
		ImGui::Checkbox("isAll", &emit.isAll);
		ImGui::Checkbox("isRotate", &emit.isRotate);
		ImGui::Checkbox("isAccelerating", &emit.isAccelerating);
		ImGui::Checkbox("isGravity", &emit.isGravity);
		ImGui::End();

		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

void Emit(Emitter& emit, Particle& par) {
	if (emit.isActive == true) {
		for (int i = 0; i < emit.amount; i++) {
			emit.aliveRange;
			emit.isMapCollisionIsActive;
			emit.isVelocityRandom;
			emit.scaleRange;
			emit.direction1.x = 1;
			emit.direction1.y = 1;
			if (emit.isAll == false) {
				emit.directionThetaRange;
				emit.directionThetaX = (float)rand() / RAND_MAX;
				emit.directionTheta = emit.directionThetaX * 180.0f / float(M_PI);
				emit.direction3.x = emit.direction1.x * cosf(emit.directionTheta) - emit.direction1.y * sinf(emit.directionTheta);
				emit.direction3.y = emit.direction1.x * sinf(emit.directionTheta) + emit.direction1.y * cosf(emit.directionTheta);
				emit.direction3.x = Normalize(0, 0, emit.direction3.x, emit.direction3.y, 1);
				emit.direction3.y = Normalize(0, 0, emit.direction3.x, emit.direction3.y, 2);
				emit.thetaDirectionX;
				emit.thetaDirection = emit.thetaDirectionX * 180.0f / float(M_PI);
				emit.direction4.x = emit.direction3.x * cosf(emit.thetaDirection) - emit.direction3.y * sinf(emit.thetaDirection);
				emit.direction4.y = emit.direction3.x * sinf(emit.thetaDirection) + emit.direction3.y * cosf(emit.thetaDirection);
				emit.direction4.x = Normalize(0, 0, emit.direction4.x, emit.direction4.y, 1);
				emit.direction4.y = Normalize(0, 0, emit.direction4.x, emit.direction4.y, 2);
			}
			else {
				emit.directionThetaX = float(rand() % 360 + 1);
				emit.directionTheta = emit.directionThetaX * 180.0f / float(M_PI);
				emit.direction2.x = emit.direction1.x * cosf(emit.directionTheta) - emit.direction1.y * sinf(emit.directionTheta);
				emit.direction2.y = emit.direction1.x * sinf(emit.directionTheta) + emit.direction1.y * cosf(emit.directionTheta);
				emit.direction2.x = Normalize(0, 0, emit.direction2.x, emit.direction2.y, 1);
				emit.direction2.y = Normalize(0, 0, emit.direction2.x, emit.direction2.y, 2);
				emit.direction4.x = emit.direction2.x;
				emit.direction4.y = emit.direction2.y;
			}
			if (emit.isVelocityRandom == true) {
				emit.velocity = rand() % int(emit.velocityRange) + emit.velocityRangeUnder;
			}
			else {
				emit.velocity;
			}
			emit.alpha = unsigned int(rand() % 30 + 170);
			emit.acceleration;
			if (emit.isScaleRandom == true) {
				emit.scale.vector2[0] = float(rand() % emit.scaleRange + emit.scaleRangeUnder);
			}
			else {
				emit.scale.vector2[0] = float(emit.scaleRangeUnder);
			}
			emit.scale.vector2[1] = emit.scale.vector2[0];
			emit.x = float(rand() % 100 / 100);
			emit.theta = emit.x * 180.0f / float(M_PI);
			for (int j = 0; j < kParticleMax; j++) {
				if (par.isActive[j] == false) {
					par.translate[j].vector2[0] = emit.translate.vector2[0];
					par.translate[j].vector2[1] = emit.translate.vector2[1];
					par.direction[j].x = emit.direction4.x;
					par.direction[j].y = emit.direction4.y;
					par.velocity[j] = emit.velocity;
					par.acceleration[j] = emit.acceleration;
					par.aliveRange[j] = emit.aliveRange;
					par.color[j] = 0xFFFFFF;
					par.color[j] = par.color[j] << 8;
					par.alpha[j] = emit.alpha;
					par.count[j] = 1;
					par.scale[j] = emit.scale;
					par.x[j] = 0;
					par.theta[j] = par.x[j] * 180.0f / float(M_PI);
					par.aliveTime[j] = emit.aliveRange;
					par.isActive[j] = true;
					break;
				}
			}
		}
	}
}

void Move(Particle& par, Emitter& emit, int Map[MapSizeY][MapSizeX]) {
	for (int i = 0; i < kParticleMax; i++) {
		if (par.isActive[i] == true) {
			par.colorN[i] = par.color[i] + par.alpha[i];
			if (emit.isMapCollisionIsActive == true) {
				if (Map[int(par.worldLeftTop[i].vector2[1] / 32)][int(par.worldLeftTop[i].vector2[0] / 32)] == 1) {
					par.velocity[i] = 0;
					par.direction[i].x = 0;
					par.direction[i].y = 0;
					par.x[i] = 0;
					par.alpha[i]--;
				}
			}
			if (emit.isGravity == true) {
				emit.ty = 0.03f;
				par.direction[i].y = (1.0f - emit.ty) * par.direction[i].y + emit.ty * 1.0f;
				emit.tx = 0.03f;
				par.direction[i].x = (1.0f - emit.tx) * par.direction[i].x + emit.tx * 0.0f;
			}
			else if (emit.isAccelerating == false) {
				emit.acceleration = 0;
			}
			par.velocity[i] += par.acceleration[i];
			par.translate[i].vector2[0] += par.direction[i].x * par.velocity[i];
			par.translate[i].vector2[1] += par.direction[i].y * par.velocity[i];
			par.colorN[i] = par.color[i] + par.alpha[i];
			if (emit.isRotate == true) {
				if (i % 2 == 0) {
					par.x[i] += 0.002f;
				}
				else {
					par.x[i] -= 0.002f;
				}
			}
			par.theta[i] = par.x[i] * 180.0f / float(M_PI);
			par.AffineMatrix[i] = MakeAffineMatrix(par.scale[i], par.theta[i], par.translate[i]);
			par.leftTop[i] = { 0,0 };
			par.leftBottom[i] = { 0,par.scale[i].vector2[1] };
			par.rightTop[i] = { par.scale[i].vector2[0],0 };
			par.rightBottom[i] = { par.scale[i].vector2[0],par.scale[i].vector2[1] };
			par.worldLeftTop[i] = Transform(par.leftTop[i], par.AffineMatrix[i]);
			par.worldLeftBottom[i] = Transform(par.leftBottom[i], par.AffineMatrix[i]);
			par.worldRightTop[i] = Transform(par.rightTop[i], par.AffineMatrix[i]);
			par.worldRightBottom[i] = Transform(par.rightBottom[i], par.AffineMatrix[i]);
		}
		par.aliveRange[i]--;
		if (par.aliveRange[i] <= 0) {
			par.isActive[i] = false;
		}
	}
}

void Display(Particle par, const int texture) {
	for (int i = 0; i < kParticleMax; i++) {
		if (par.isActive[i] == true) {
			VDrawQuad(par.worldLeftTop[i], par.worldLeftBottom[i], par.worldRightTop[i], par.worldRightBottom[i], texture);
		}
	}
}