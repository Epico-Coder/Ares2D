#pragma once

#include <string>
#include <unordered_map>
#include "dependancies/glm/glm.hpp"

struct ShaderType
{
	const std::string filePath;
};

class Shader
{
public:
	Shader();
	Shader(const std::string& vert_file_path, const std::string& frag_file_path);
	~Shader();

	void AddVertexShader(std::string filepath = "engine/resources/shaders/shaders/VertexShader.shader");
	void AddFragmentShader(std::string filepath = "engine/resources/shaders/shaders/FragmentShader.shader");

	void Create();

	void GetUniformData();

	void SetUniform1i(const std::string& name, int v1);
	void SetUniform1iv(const std::string& name, unsigned int count, int v1[]);
	void SetUniform1f(const std::string& name, float v1);
	void SetUniform3f(const std::string& name, float v1, float v2, float v3);
	void SetUniform4i(const std::string& name, int v1, int v2, int v3, int v4);
	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	void Bind();
	void Unbind();

private:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	std::string ParseShader(std::string filepath);
	int GetUniformLocation(const std::string& name);
private:
	unsigned int m_buffer;
	std::string m_vertexShader = "";
	std::string m_fragmentShader = "";
	std::unordered_map<std::string, int> m_uniformLocationCache;
	int count;
};