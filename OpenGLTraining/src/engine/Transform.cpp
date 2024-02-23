#include "Transform.h"

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	_position = position;
	_rotation = rotation;
	_scale = scale;
}
