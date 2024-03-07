#pragma once
#include "glm/glm.hpp"

class Transform
{
private:
	glm::vec3 _position{ 0.0f, 0.0f, 0.0f };
	glm::vec2 _rotation{ 0.0f, 0.0f };
	glm::vec2 _scale{ 1.0f, 1.0f };

public:
	Transform(glm::vec3 position, glm::vec2 rotation, glm::vec2 scale);

	inline glm::vec3 GetPosition() const { return _position; }
	inline glm::vec2 GetRotation() const { return _rotation; }
	inline glm::vec2 GetScale() const { return _scale; }

	inline void SetPosition(glm::vec3 position) { _position = position; }
	inline void SetRotation(glm::vec2 rotation) { _rotation = rotation; }
	inline void SetScale(glm::vec2 scale) { _scale = scale; }
};

