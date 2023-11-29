#include <Novice.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>
#include "Functions.h"

float DotProduct(float AstartX, float AstartY, float AendX, float AendY, float BstartX, float BstartY, float BendX, float BendY) {
	float VectorAX = AendX - AstartX;
	float VectorAY = AendY - AstartY;
	float VectorBX = BendX - BstartX;
	float VectorBY = BendY - BstartY;
	return VectorAX * VectorBX + VectorAY * VectorBY;
}

float CrossProduct(float AstartX, float AstartY, float AendX, float AendY, float BstartX, float BstartY, float BendX, float BendY) {
	float VectorAX = AendX - AstartX;
	float VectorAY = AendY - AstartY;
	float VectorBX = BendX - BstartX;
	float VectorBY = BendY - BstartY;
	return VectorAX * VectorBY - VectorAY * VectorBX;
}

float MAX(float x, float y) {
	if (x > y) {
		return x;
	}
	if (y > x) {
		return y;
	}
	return 0;
}

float pNorm(float x, float y, float p) {
	if (p > 255) {
		x = fabsf((float)x);
		y = fabsf((float)y);
		float norm2 = MAX(x, y);
		return norm2;
	}
	float norm = 0;
	x = sqrtf(x * x);
	y = sqrtf(y * y);
	x = powf(x, p);
	y = powf(y, p);
	norm = x + y;
	norm = powf(norm, 1.0f / p);
	return norm;
}

float GetRadianThree(float AstartX, float AstartY, float AendX, float AendY, float BstartX, float BstartY, float BendX, float BendY) {
	float Dot = DotProduct(AstartX, AstartY, AendX, AendY, BstartX, BstartY, BendX, BendY);
	float VectorAX = AendX - AstartX;
	float VectorAY = AendY - AstartY;
	float Dis1 = pNorm(VectorAX, VectorAY, 2);
	float VectorBX = BendX - BstartX;
	float VectorBY = BendY - BstartY;
	float Dis2 = pNorm(VectorBX, VectorBY, 2);
	float costheta = Dot / (Dis1 * Dis2);
	float radian = acosf(costheta);
	return radian;
}

float GetRadian(float degree) {
	return degree * (float(M_PI) / 180);
}

float GetDegree(float radian) {
	float degree = radian * 180.0f / (float)M_PI;
	return degree;
}

float GetDis(float x1, float y1, float x2, float y2) {
	float DisX = x2 - x1;
	float DisY = y2 - y1;
	return sqrtf(DisX * DisX + DisY * DisY);
}

float Normalize(float startX, float startY, float endX, float endY, int n) {
	float VectorX = endX - startX;
	float VectorY = endY - startY;
	float length = GetDis(startX, startY, endX, endY);
	float normalizedX = 0;
	float normalizedY = 0;
	if (length != 0.0f) {
		normalizedX = VectorX / length;
		normalizedY = VectorY / length;
	}
	if (n == 1) {
 		return normalizedX;
	}
	if (n == 2) {
		return normalizedY;
	}
	return 0;
}

float Clamp(float n, float min, float max) {
	if (n > max) {
		return max;
	}
	if (n < min) {
		return min;
	}
	return n;
}

float isBoxCollisionBeta(float leftTopX1, float leftTopY1, float rightBottomX1, float rightBottomY1, float leftTopX2, float leftTopY2, float rightBottomX2, float rightBottomY2) {
	if (leftTopX2 < rightBottomX1 && leftTopX1 < rightBottomX2) {
		if (rightBottomY2 > leftTopY1 && rightBottomY1 > leftTopY2) {
			return 1;
		}
	}
	return 0;
}

float isCircleCollision(float posX1, float posY1, float posX2, float posY2, int radius1, int radius2) {
	float Dis = GetDis(posX1, posY1, posX2, posY2);
	if (Dis < radius1 + radius2) {
		return 1;
	}
	return 0;
}

float CC(float posY) {
	float worldY = 640;
	return -posY + worldY;
}

float LeftTopX(float posX, float width) {
	return posX - width / 2;
}

float LeftTopY(float posY, float height) {
	return posY - height / 2;
}

float RightBottomX(float posX, float width) {
	return posX + width / 2;
}

float RightBottomY(float posY, float height) {
	return posY + height / 2;
}

float RightTopX(float posX, float width) {
	return posX + width / 2;
}

float RightTopY(float posY, float height) {
	return posY - height / 2;
}

float LeftBottomX(float posX, float width) {
	return posX - width / 2;
}

float LeftBottomY(float posY, float height) {
	return posY + height / 2;
}

float CenterC(float leftTopX, float leftTopY, float width, float height, int n) {
	float centerX = 0;
	float centerY = 0;
	centerX = leftTopX + width / 2;
	centerY = leftTopY + height / 2;
	if (n == 1) {
		return centerX;
	}
	if (n == 2) {
		return centerY;
	}
	else {
		return 0;
	}
}

float isBoxCollision(float posX1, float posY1, float posX2, float posY2, float width, float height, float width2, float height2) {
	float leftTopX1 = LeftTopX(posX1, width);
	float leftTopY1 = LeftTopY(posY1, height);
	float leftTopX2 = LeftTopX(posX2, width2);
	float leftTopY2 = LeftTopY(posY2, height2);
	float rightBottomX1 = RightBottomX(posX1, width);
	float rightBottomY1 = RightBottomY(posY1, height);
	float rightBottomX2 = RightBottomX(posX2, width2);
	float rightBottomY2 = RightBottomY(posY2, height2);
	if (leftTopX2 < rightBottomX1 && leftTopX1 < rightBottomX2) {
		if (rightBottomY2 > leftTopY1 && rightBottomY1 > leftTopY2) {
			return 1;
		}
	}
	return 0;
}

float IsOutOfScreen(float posX, float posYn, int ScreenSizeX, int ScreenSizeY) {
	if (posX<0 || posX>ScreenSizeX || posYn<0 || posYn>ScreenSizeY) {
		return 1;
	}
	else {
		return 0;
	}
}

float BoxPointCollision(float BoxLtX, float BoxLtY, float BoxRbX, float BoxRbY, int pointX, int pointY) {
	if (BoxLtX<pointX && BoxRbX>pointX) {
		if (BoxLtY<pointY && BoxRbY>pointY) {
			return 1;
		}
	}
	return 0;
}


void CalculateVertex(Vertex& vertex) {
	vertex.LeftTop.x = vertex.center.x - vertex.width / 2;
	vertex.LeftTop.y = vertex.center.y - vertex.height / 2;
	vertex.LeftBottom.x = vertex.center.x - vertex.width / 2;
	vertex.LeftBottom.y = vertex.center.y + vertex.height / 2;
	vertex.RightTop.x = vertex.center.x + vertex.width / 2;
	vertex.RightTop.y = vertex.center.y - vertex.height / 2;
	vertex.RightBottom.x = vertex.center.x + vertex.width / 2;
	vertex.RightBottom.y = vertex.center.y + vertex.height / 2;
}

void CalculatePlayerVertex(Player& player) {
	player.screenVertex.LeftTop.x = player.screenVertex.center.x - player.vertex.width / 2;
	player.screenVertex.LeftTop.y = player.screenVertex.center.y - player.vertex.height / 2;
	player.screenVertex.LeftBottom.x = player.screenVertex.center.x - player.vertex.width / 2;
	player.screenVertex.LeftBottom.y = player.screenVertex.center.y + player.vertex.height / 2;
	player.screenVertex.RightTop.x = player.screenVertex.center.x + player.vertex.width / 2;
	player.screenVertex.RightTop.y = player.screenVertex.center.y - player.vertex.height / 2;
	player.screenVertex.RightBottom.x = player.screenVertex.center.x + player.vertex.width / 2;
	player.screenVertex.RightBottom.y = player.screenVertex.center.y + player.vertex.height / 2;
}

void CalculatePlayerWorldVertex(Player& player) {
	player.worldVertex.LeftTop.x = player.worldVertex.center.x - player.vertex.width / 2;
	player.worldVertex.LeftTop.y = player.worldVertex.center.y - player.vertex.height / 2;
	player.worldVertex.LeftBottom.x = player.worldVertex.center.x - player.vertex.width / 2;
	player.worldVertex.LeftBottom.y = player.worldVertex.center.y + player.vertex.height / 2;
	player.worldVertex.RightTop.x = player.worldVertex.center.x + player.vertex.width / 2;
	player.worldVertex.RightTop.y = player.worldVertex.center.y - player.vertex.height / 2;
	player.worldVertex.RightBottom.x = player.worldVertex.center.x + player.vertex.width / 2;
	player.worldVertex.RightBottom.y = player.worldVertex.center.y + player.vertex.height / 2;
}

void CalculatePlayerVertexPrevious(Player& player) {
	player.preVertex.LeftTop.x = player.preVertex.center.x - player.vertex.width / 2;
	player.preVertex.LeftTop.y = player.preVertex.center.y - player.vertex.height / 2;
	player.preVertex.LeftBottom.x = player.preVertex.center.x - player.vertex.width / 2;
	player.preVertex.LeftBottom.y = player.preVertex.center.y + player.vertex.height / 2;
	player.preVertex.RightTop.x = player.preVertex.center.x + player.vertex.width / 2;
	player.preVertex.RightTop.y = player.preVertex.center.y - player.vertex.height / 2;
	player.preVertex.RightBottom.x = player.preVertex.center.x + player.vertex.width / 2;
	player.preVertex.RightBottom.y = player.preVertex.center.y + player.vertex.height / 2;
}

void CalculatePlayerVertexTmp(Player& player) {
	player.vertexTmp.LeftTop.x = player.vertexTmp.center.x - player.vertex.width / 2;
	player.vertexTmp.LeftTop.y = player.vertexTmp.center.y - player.vertex.height / 2;
	player.vertexTmp.LeftBottom.x = player.vertexTmp.center.x - player.vertex.width / 2;
	player.vertexTmp.LeftBottom.y = player.vertexTmp.center.y + player.vertex.height / 2;
	player.vertexTmp.RightTop.x = player.vertexTmp.center.x + player.vertex.width / 2;
	player.vertexTmp.RightTop.y = player.vertexTmp.center.y - player.vertex.height / 2;
	player.vertexTmp.RightBottom.x = player.vertexTmp.center.x + player.vertex.width / 2;
	player.vertexTmp.RightBottom.y = player.vertexTmp.center.y + player.vertex.height / 2;
}

void newDrawQuad(Player player, int textureHandle) {
	Novice::DrawQuad(int(player.screenVertex.LeftTop.x), int(player.screenVertex.LeftTop.y), int(player.screenVertex.RightTop.x), int(player.screenVertex.RightTop.y), int(player.screenVertex.LeftBottom.x), int(player.screenVertex.LeftBottom.y), int(player.screenVertex.RightBottom.x), int(player.screenVertex.RightBottom.y), 0, 0, int(player.vertex.width), int(player.vertex.height), textureHandle, 0xFFFFFFFF);
}

void CalculateQuadMapMapNumber(Player& player, const int MapChipSize) {
	player.mapnum.LeftTop.x = int(player.worldVertex.LeftTop.x) / MapChipSize;
	player.mapnum.LeftTop.y = int(player.worldVertex.LeftTop.y) / MapChipSize;
	player.mapnum.LeftBottom.x = int(player.worldVertex.LeftBottom.x) / MapChipSize;
	player.mapnum.LeftBottom.y = int((player.worldVertex.LeftBottom.y - 1)) / MapChipSize;
	player.mapnum.RightTop.x = int((player.worldVertex.RightTop.x - 1)) / MapChipSize;
	player.mapnum.RightTop.y = int(player.worldVertex.RightTop.y) / MapChipSize;
	player.mapnum.RightBottom.x = int((player.worldVertex.RightBottom.x - 1)) / MapChipSize;
	player.mapnum.RightBottom.y = int((player.worldVertex.RightBottom.y - 1)) / MapChipSize;
}

void CalculateQuadMapNumberPrevious(Player& player, const int MapChipSize) {
	player.preMapnum.LeftTop.x = int(player.preVertex.LeftTop.x) / MapChipSize;
	player.preMapnum.LeftTop.y = int(player.preVertex.LeftTop.y) / MapChipSize;
	player.preMapnum.LeftBottom.x = int(player.preVertex.LeftBottom.x) / MapChipSize;
	player.preMapnum.LeftBottom.y = int((player.preVertex.LeftBottom.y - 1)) / MapChipSize;
	player.preMapnum.RightTop.x = int((player.preVertex.RightTop.x - 1)) / MapChipSize;
	player.preMapnum.RightTop.y = int(player.preVertex.RightTop.y) / MapChipSize;
	player.preMapnum.RightBottom.x = int((player.preVertex.RightBottom.x - 1)) / MapChipSize;
	player.preMapnum.RightBottom.y = int((player.preVertex.RightBottom.y - 1)) / MapChipSize;
}

void CalculateQuadMapMapNumberTmp(Player& player, const int MapChipSize) {
	player.mapnumTmp.LeftTop.x = int(player.vertexTmp.LeftTop.x / MapChipSize);
	player.mapnumTmp.LeftTop.y = int(player.vertexTmp.LeftTop.y / MapChipSize);
	player.mapnumTmp.LeftBottom.x = int(player.vertexTmp.LeftBottom.x / MapChipSize);
	player.mapnumTmp.LeftBottom.y = int((player.vertexTmp.LeftBottom.y - 1) / MapChipSize);
	player.mapnumTmp.RightTop.x = int((player.vertexTmp.RightTop.x - 1) / MapChipSize);
	player.mapnumTmp.RightTop.y = int(player.vertexTmp.RightTop.y / MapChipSize);
	player.mapnumTmp.RightBottom.x = int((player.vertexTmp.RightBottom.x - 1) / MapChipSize);
	player.mapnumTmp.RightBottom.y = int((player.vertexTmp.RightBottom.y - 1) / MapChipSize);
}

void VertexScreenPrintf(Player player, int x, int y) {
	int xTmp = 60;
	int yTmp = 25;
	Novice::ScreenPrintf(x, y, "%d", int(player.mapnum.LeftTop.x));
	Novice::ScreenPrintf(x + xTmp, y, "%d", int(player.mapnum.LeftTop.y));
	Novice::ScreenPrintf(x, y + yTmp, "%d", int(player.mapnum.LeftBottom.x));
	Novice::ScreenPrintf(x + xTmp, y + yTmp, "%d", int(player.mapnum.LeftBottom.y));
	Novice::ScreenPrintf(x, y + yTmp * 2, "%d", int(player.mapnum.RightTop.x));
	Novice::ScreenPrintf(x + xTmp, y + yTmp * 2, "%d", int(player.mapnum.RightTop.y));
	Novice::ScreenPrintf(x, y + yTmp * 3, "%d", int(player.mapnum.RightBottom.x));
	Novice::ScreenPrintf(x + xTmp, y + yTmp * 3, "%d", int(player.mapnum.RightBottom.y));
}

void VertexDrawEllipse(Player player) {
	Novice::DrawEllipse(int(player.vertex.LeftTop.x), int(player.vertex.LeftTop.y), 5, 5, 0.0f, BLUE, kFillModeSolid);
	Novice::DrawEllipse(int(player.vertex.LeftBottom.x), int(player.vertex.LeftBottom.y), 5, 5, 0.0f, BLUE, kFillModeSolid);
	Novice::DrawEllipse(int(player.vertex.RightTop.x), int(player.vertex.RightTop.y), 5, 5, 0.0f, BLUE, kFillModeSolid);
	Novice::DrawEllipse(int(player.vertex.RightBottom.x), int(player.vertex.RightBottom.y), 5, 5, 0.0f, BLUE, kFillModeSolid);
}

void VertexDrawEllipseTmp(Player player) {
	Novice::DrawEllipse(int(player.vertexTmp.LeftTop.x), int(player.vertexTmp.LeftTop.y), 5, 5, 0.0f, BLUE, kFillModeSolid);
	Novice::DrawEllipse(int(player.vertexTmp.LeftBottom.x), int(player.vertexTmp.LeftBottom.y), 5, 5, 0.0f, BLUE, kFillModeSolid);
	Novice::DrawEllipse(int(player.vertexTmp.RightTop.x), int(player.vertexTmp.RightTop.y), 5, 5, 0.0f, BLUE, kFillModeSolid);
	Novice::DrawEllipse(int(player.vertexTmp.RightBottom.x), int(player.vertexTmp.RightBottom.y), 5, 5, 0.0f, BLUE, kFillModeSolid);
}
Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 result;
	for (int row = 0; row < 2; ++row) {
		for (int column = 0; column < 2; ++column) {
			result.matrix[row][column] = matrix1.matrix[row][column] + matrix2.matrix[row][column];
		}
	}
	return result;
}
Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 result;
	for (int row = 0; row < 2; ++row) {
		for (int column = 0; column < 2; ++column) {
			result.matrix[row][column] = matrix1.matrix[row][column] - matrix2.matrix[row][column];
		}
	}
	return result;
}
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 result;
	result.matrix[0][0] =
		matrix1.matrix[0][0] * matrix2.matrix[0][0] + matrix1.matrix[0][1] * matrix2.matrix[1][0];
	result.matrix[0][1] =
		matrix1.matrix[0][0] * matrix2.matrix[0][1] + matrix1.matrix[0][1] * matrix2.matrix[1][1];
	result.matrix[1][0] =
		matrix1.matrix[1][0] * matrix2.matrix[0][0] + matrix1.matrix[1][1] * matrix2.matrix[1][0];
	result.matrix[1][1] =
		matrix1.matrix[1][0] * matrix2.matrix[0][1] + matrix1.matrix[1][1] * matrix2.matrix[1][1];
	return result;
}

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 result{};
	for (int rows = 0; rows < 3; rows++) {
		for (int cols = 0; cols < 3; cols++) {
			for (int a = 0; a < 3; a++) {
				result.matrix[rows][cols] += matrix1.matrix[rows][a] * matrix2.matrix[a][cols];
			}
		}
	}
	return result;
}

Vector2Array MultiplyV(Matrix2x2 matrix1, Vector2Array vector2) {
	Vector2Array result;
	result.vector2[0] =
		matrix1.matrix[0][0] * vector2.vector2[0] + matrix1.matrix[1][0] * vector2.vector2[1];
	result.vector2[1] =
		matrix1.matrix[0][1] * vector2.vector2[0] + matrix1.matrix[1][1] * vector2.vector2[1];
	return result;
}

Vector2Array Transform(Vector2Array vector, Matrix3x3 matrix) {
	Vector2Array result;
	result.vector2[0] = vector.vector2[0] * matrix.matrix[0][0] +
		vector.vector2[1] * matrix.matrix[1][0] + 1.0f * matrix.matrix[2][0];
	result.vector2[1] = vector.vector2[0] * matrix.matrix[0][1] +
		vector.vector2[1] * matrix.matrix[1][1] + 1.0f * matrix.matrix[2][1];
	float w = vector.vector2[0] * matrix.matrix[0][2] + vector.vector2[1] * matrix.matrix[1][2] +
		1.0f * matrix.matrix[2][2];
	assert(w != 0.0f);
	result.vector2[0] /= w;
	result.vector2[1] /= w;
	return result;
}

void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix) {
	for (int row = 0; row < 2; ++row) {
		for (int column = 0; column < 2; ++column) {
			Novice::ScreenPrintf(x + column * 2, y + row * 2, "%.02f", matrix.matrix[row][column]);
		}
	}
}

void Vector2ScreenPrintf(int x, int y, Vector2Array vector2) {
	Novice::ScreenPrintf(x, y, "%.02f", vector2.vector2[0]);
	Novice::ScreenPrintf(x + 50, y, "%.02f", vector2.vector2[1]);
}

Matrix3x3 MakeScaleMatrix(Vector2Array scale) {
	Matrix3x3 result{};
	result.matrix[0][0] = scale.vector2[0];
	result.matrix[0][1] = 0.0f;
	result.matrix[0][2] = 0.0f;
	result.matrix[1][0] = 0.0f;
	result.matrix[1][1] = scale.vector2[1];
	result.matrix[1][2] = 0.0f;
	result.matrix[2][0] = 0.0f;
	result.matrix[2][1] = 0.0f;
	result.matrix[2][2] = 1.0f;
	return result;
}

Matrix3x3 MakeTranslateMatrix(Vector2Array translate) {
	Matrix3x3 result{};
	result.matrix[0][0] = 1.0f;
	result.matrix[0][1] = 0.0f;
	result.matrix[0][2] = 0.0f;
	result.matrix[1][0] = 0.0f;
	result.matrix[1][1] = 1.0f;
	result.matrix[1][2] = 0.0f;
	result.matrix[2][0] = translate.vector2[0];
	result.matrix[2][1] = translate.vector2[1];
	result.matrix[2][2] = 1.0f;
	return result;
}

Matrix3x3 MakeRotateMatrix(float theta) {
	Matrix3x3 result{};
	result.matrix[0][0] = cosf(theta);
	result.matrix[0][1] = sinf(theta);
	result.matrix[0][2] = 0.0f;
	result.matrix[1][0] = -sinf(theta);
	result.matrix[1][1] = cosf(theta);
	result.matrix[1][2] = 0.0f;
	result.matrix[2][0] = 0.0f;
	result.matrix[2][1] = 0.0f;
	result.matrix[2][2] = 1.0f;
	return result;
}

Matrix3x3 MakeAffineMatrix(Vector2Array scale, float theta, Vector2Array translate) {
	Matrix3x3 result{};
	result.matrix[0][0] = scale.vector2[0] * cosf(theta);
	result.matrix[0][1] = scale.vector2[0] * sinf(theta);
	result.matrix[0][2] = 0.0f;
	result.matrix[1][0] = -scale.vector2[1] * sinf(theta);
	result.matrix[1][1] = scale.vector2[0] * cosf(theta);
	result.matrix[1][2] = 0.0f;
	result.matrix[2][0] = translate.vector2[0];
	result.matrix[2][1] = translate.vector2[1];
	result.matrix[2][2] = 1.0f;
	return result;
}

void VDrawQuad(Vector2Array lt, Vector2Array rt, Vector2Array lb, Vector2Array rb, int Tex) {
	Novice::DrawQuad(
		int(lt.vector2[0]), int(lt.vector2[1]), int(rt.vector2[0]), int(rt.vector2[1]),
		int(lb.vector2[0]), int(lb.vector2[1]), int(rb.vector2[0]), int(rb.vector2[1]), 0, 0, 48,
		48, Tex, 0xFFFFFFFF);
}
