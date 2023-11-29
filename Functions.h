#pragma once

struct Matrix2x2 {
	float matrix[2][2];
};

struct Vector2 {
	float x;
	float y;
};

struct intPos {
	int x;
	int y;
};

struct MapChip {
	intPos LeftTop;
	intPos LeftBottom;
	intPos RightTop;
	intPos RightBottom;
};

struct Vertex {
	Vector2 LeftTop;
	Vector2 LeftBottom;
	Vector2 RightTop;
	Vector2 RightBottom;
	Vector2 center;
	float width;
	float height;
};

struct Where {
	bool isX;
	bool isY;
};

struct Player {
	Vertex vertexTmp;
	Vertex preVertex;
	Vertex vertex;
	Vertex worldVertex;
	Vertex screenVertex;
	MapChip mapnum;
	MapChip preMapnum;
	MapChip mapnumTmp;
	Vector2 dir;
	Vector2 velocity;
	Vector2 velocityTmp;
	Vector2 move;
	intPos centerMapNum;
	Where LT;
	Where RT;
	Where LB;
	Where RB;
};
struct Matrix3x3 {
	float matrix[3][3];
};

struct Vector2Array {
	float vector2[2];
};

Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2);
Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2);
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2);
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);
Vector2Array MultiplyV(Matrix2x2 matrix1, Vector2Array vector2);
Vector2Array Transform(Vector2Array vector, Matrix3x3 matrix);
Matrix3x3 MakeScaleMatrix(Vector2Array scale);
Matrix3x3 MakeTranslateMatrix(Vector2Array translate);
Matrix3x3 MakeRotateMatrix(float theta);
Matrix3x3 MakeAffineMatrix(Vector2Array scale, float theta, Vector2Array translate);



float DotProduct(float AstartX, float AstartY, float AendX, float AendY, float BstartX, float BstartY, float BendX, float BendY);
float CrossProduct(float AstartX, float AstartY, float AendX, float AendY, float BstartX, float BstartY, float BendX, float BendY);
float MAX(float x, float y);
float pNorm(float x, float y, float p);
float GetRadianThree(float AstartX, float AstartY, float AendX, float AendY, float BstartX, float BstartY, float BendX, float BendY);
float GetRadian(float degree);
float GetDegree(float radian);
float GetDis(float x1, float y1, float x2, float y2);
float Normalize(float startX, float startY, float endX, float endY, int n);
float Clamp(float n, float min, float max);
float isBoxCollisionBeta(float leftTopX1, float leftTopY1, float rightBottomX1, float rightBottomY1, float leftTopX2, float leftTopY2, float rightBottomX2, float rightBottomY2);
float isCircleCollision(float posX1, float posY1, float posX2, float posY2, int radius1, int radius2);
float CC(float posY);
float LeftTopX(float posX, float width);
float LeftTopY(float posY, float height);
float LeftBottomX(float posX, float width);
float LeftBottomY(float posY, float height);
float RightTopX(float posX, float width);
float RightTopY(float posY, float height);
float RightBottomX(float posX, float width);
float RightBottomY(float posY, float height);
float CenterC(float leftTopX, float leftTopY, float width, float height, int n);
float isBoxCollision(float posX1, float posY1, float posX2, float posY2, float width, float height, float width2, float height2);
float IsOutOfScreen(float posX, float posYn, int ScreenSizeX, int ScreenSizeY);
float BoxPointCollision(float BoxLtX, float BoxLtY, float BoxRbX, float BoxRbY, int pointX, int pointY);
void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix);
void CalculateVertex(Vertex& vertex);
void CalculatePlayerVertex(Player& player);
void CalculatePlayerWorldVertex(Player& player);
void CalculatePlayerVertexTmp(Player& player);
void newDrawQuad(Player player, int textureHandle);
void CalculateQuadMapMapNumber(Player& player, const int MapChipSize);
void CalculateQuadMapMapNumberTmp(Player& player, const int MapChipSize);
void VertexScreenPrintf(Player player, int x, int y);
void VertexDrawEllipse(Player player);
void VertexDrawEllipseTmp(Player player);
void CalculatePlayerVertexPrevious(Player& player);
void CalculateQuadMapNumberPrevious(Player& player, const int MapChipSize);
void VDrawQuad(Vector2Array lt, Vector2Array rt, Vector2Array lb, Vector2Array rb, int Tex);