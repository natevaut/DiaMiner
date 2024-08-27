#pragma once
// COMP710 GP Framework 2022
#ifndef MATRIX4_H
#define MATRIX4_H

struct Matrix4
{
	float m[4][4];
};

void SetZero(Matrix4 &mat);
void SetIdentity(Matrix4 &mat);
void CreateOrthoProjection(Matrix4 &mat, float width, float height);

#endif //   MATRIX4_H
