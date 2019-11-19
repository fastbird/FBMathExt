#pragma once
#include "../FBCommon/glm.h"

namespace fb
{
	glm::mat4 MatrixReflect(const glm::vec4& reflectionPlane);
	// toLightDir.w == 0 for Directional light, otherwise its for PointLights.
	glm::mat4 MatrixShadow(const glm::vec4& shadowPlane, const glm::vec4& toLightDir);
}