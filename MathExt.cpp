// FBMathExt.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "MathExt.h"
#include <assert.h>
#include <cmath>
using namespace fb;

bool PlaneIsInfinite(const glm::vec4& plane)
{
	return !std::isfinite(plane.x) ||
		!std::isfinite(plane.y) ||
		!std::isfinite(plane.z) ||
		!std::isfinite(plane.w);
}

//glm::vec4 PlaneNormalize(const glm::vec4& plane)
//{
//	float fLengthSq = glm::length(plane);
//	// Prevent divide by zero
//	if (fLengthSq > 0)
//	{
//		fLengthSq = 1.0f / fLengthSq;
//	}
//	glm::vec4 vResult = plane * fLengthSq;
//	return vResult;
//}

glm::mat4 fb::MatrixReflect(const glm::vec4& reflectionPlane)
{
	assert(!glm::all(glm::epsilonEqual(glm::vec3(reflectionPlane), glm::vec3(0, 0, 0), 0.01f)));
	assert(!PlaneIsInfinite(reflectionPlane));

	static const glm::vec4 NegativeTwo{ -2.0f, -2.0f, -2.0f, 0.0f };

	glm::vec4 P = glm::normalize(reflectionPlane);
	glm::vec4 S = P * NegativeTwo;

	glm::vec4 A(P.x, P.x, P.x, P.x);
	glm::vec4 B(P.y, P.y, P.y, P.y);
	glm::vec4 C(P.z, P.z, P.z, P.z);
	glm::vec4 D(P.w, P.w, P.w, P.w);

	glm::mat4 M;
	M[0] = A * S + glm::identity<glm::mat4>()[0];
	M[1] = B * S + glm::identity<glm::mat4>()[1];
	M[2] = C * S + glm::identity<glm::mat4>()[2];
	M[3] = D * S + glm::identity<glm::mat4>()[3];
	M = glm::transpose(M);
	return M;
}
