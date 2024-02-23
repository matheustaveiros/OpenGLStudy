#pragma once
#include "glm/glm.hpp"

class Transform
{
private:
	glm::vec3 _position;
	glm::vec3 _rotation;
	glm::vec3 _scale;

public:
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	inline const glm::vec3 GetPosition() const { return _position; }
	inline const glm::vec3 GetRotation() const { return _position; }
	inline const glm::vec3 GetScale() const { return _position; }

	inline void SetPosition(glm::vec3 position) { _position = position; }
	inline void SetRotation(glm::vec3 rotation) { _rotation = rotation; }
	inline void SetScale(glm::vec3 scale) { _scale = scale; }
};

