#include "Transform.h"

Transform::Transform(glm::vec3 position, glm::vec2 rotation, glm::vec2 scale)
{
	_position = position;
	_rotation = rotation;
	_scale = scale;
}
