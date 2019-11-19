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

glm::vec4 PlaneNormalize(const glm::vec4& plane)
{
	float fLengthSq = glm::length(glm::vec3(plane));
	// Prevent divide by zero
	if (fLengthSq > 0)
	{
		fLengthSq = 1.0f / fLengthSq;
	}
	glm::vec4 vResult = plane * fLengthSq;
	return vResult;
}

glm::mat4 fb::MatrixReflect(const glm::vec4& reflectionPlane)
{
	assert(!glm::all(glm::epsilonEqual(glm::vec3(reflectionPlane), glm::vec3(0, 0, 0), 0.01f)));
	assert(!PlaneIsInfinite(reflectionPlane));

	static const glm::vec4 NegativeTwo{ -2.0f, -2.0f, -2.0f, 0.0f };

	glm::vec4 P = PlaneNormalize(reflectionPlane);
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

glm::mat4 fb::MatrixShadow(const glm::vec4& shadowPlane, const glm::vec4& toLightDir)
{
	auto normalizedP = PlaneNormalize(shadowPlane);
	float d = shadowPlane.w;
	float nDotL = glm::dot(normalizedP, toLightDir);
	normalizedP = -normalizedP;
	auto row0 = glm::vec4(normalizedP.x, normalizedP.x, normalizedP.x, normalizedP.x) * toLightDir;
	row0[0] += nDotL;
	auto row1 = glm::vec4(normalizedP.y, normalizedP.y, normalizedP.y, normalizedP.y) * toLightDir;
	row1[1] += nDotL + d * toLightDir.w;
	auto row2 = glm::vec4(normalizedP.z, normalizedP.z, normalizedP.z, normalizedP.z) * toLightDir;
	row2[2] += nDotL + d * toLightDir.w;
	auto row3 = -glm::vec4(toLightDir) * d;
	row3[3] = nDotL;

	// rows go to columns
	return glm::mat4(row0, row1, row2, row3);
}