#pragma once

#include "ErrorHandler.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <unordered_map>
#include "glm/glm.hpp"

class Shader
{
private:

	std::string m_FilePath;
	std::unordered_map<std::string, int> m_UniformLocationCache;
	unsigned int m_RendererID;


	std::array<std::string, 2> ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	int GetUniformLocation(const std::string& name);

public:
	Shader(const std::string& filename);
	~Shader();

	void Bind() const;
	void Unbind() const;
	
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform3f(const std::string& name, glm::vec3 vector);

	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
};

