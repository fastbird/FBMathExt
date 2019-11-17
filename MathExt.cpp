// FBMathExt.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "MathExt.h"
#include <assert.h>
using namespace fb;

bool PlaneIsInfinite(const glm::vec4& plane)
{
	return Vector4IsInfinite(plane);
}

glm::mat4 fb::MatrixReflect(const glm::vec4& reflectionPlane)
{
	assert(!glm::all(glm::epsilonEqual(reflectionPlane, glm::vec3(0, 0, 0), 0.01f)));
	assert(!XMPlaneIsInfinite(ReflectionPlane));

	static const XMVECTORF32 NegativeTwo = { { { -2.0f, -2.0f, -2.0f, 0.0f } } };

	XMVECTOR P = XMPlaneNormalize(ReflectionPlane);
	XMVECTOR S = XMVectorMultiply(P, NegativeTwo);

	XMVECTOR A = XMVectorSplatX(P);
	XMVECTOR B = XMVectorSplatY(P);
	XMVECTOR C = XMVectorSplatZ(P);
	XMVECTOR D = XMVectorSplatW(P);

	XMMATRIX M;
	M.r[0] = XMVectorMultiplyAdd(A, S, g_XMIdentityR0.v);
	M.r[1] = XMVectorMultiplyAdd(B, S, g_XMIdentityR1.v);
	M.r[2] = XMVectorMultiplyAdd(C, S, g_XMIdentityR2.v);
	M.r[3] = XMVectorMultiplyAdd(D, S, g_XMIdentityR3.v);
	return M;
}
