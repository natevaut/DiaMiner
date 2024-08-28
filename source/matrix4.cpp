// COMP710 GP Framework 2022

#include "matrix4.h"
void SetZero(Matrix4 &mat)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			mat.m[i][j] = 0.0f;
}
void SetIdentity(Matrix4 &mat)
{
	SetZero(mat);

	for (int i = 0; i < 4; i++)
		mat.m[i][i] = 1.0f;
}

void CreateOrthoProjection(Matrix4 &mat, float width, float height)
{
	SetZero(mat);
	float size = 1.0;

	mat.m[0][0] = size / width;
	mat.m[1][1] = -size / height;
	mat.m[2][2] = -1.0f;

	mat.m[3][0] = -1.0f;
	mat.m[3][1] = 1.0f;
	mat.m[3][2] = 0.0f;
	mat.m[3][3] = 1.0f;
}
