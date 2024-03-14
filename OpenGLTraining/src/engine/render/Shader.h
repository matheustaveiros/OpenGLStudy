#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader();
	~Shader();

	void SetUniform1i(const std::string& name, int value);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	int GetUniformLocation(const std::string& name);

	void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetID() const { return _rendererID; }

private:
	unsigned int _rendererID;

	std::unordered_map<std::string, int> _locations;

	void checkCompileErrors(unsigned int object, const std::string& type) const;
};
