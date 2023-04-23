#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include "dependancies/glm/glm.hpp"

class Shader
{
public:
	Shader();
	Shader(const std::string& vert_file_path, const std::string& frag_file_path);
	~Shader();

	void AddVertexShader(const std::string& filepath = "engine/resources/shaders/shaders/VertexShader.shader");
	void AddFragmentShader(const std::string& filepath = "engine/resources/shaders/shaders/FragmentShader.shader");

	void Create();

	void GetUniformData(const std::string& name);
	void GetAttribData(const std::string& name);
	std::string GetData();

	void SetUniform1i(const std::string& name, int v1);
	void SetUniform1iv(const std::string& name, unsigned int count, int v1[]);
	void SetUniform1f(const std::string& name, float v1);
	void SetUniform1fv(const std::string& name, unsigned int count, float v1[]);
	void SetUniform2fv(const std::string& name, const glm::vec2& vec);
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
	std::map<std::string, int> m_uniformLocationCache;
	int count;
};


class ShaderHandler
{
public:
	ShaderHandler();
	~ShaderHandler();

	void AddShader(const std::string& vert_file_path, const std::string& frag_file_path, int shaderID);
	void RemoveShader(int shaderID);

	void BindShader(int shaderID);

	void CreateUniform1i(int shaderID, const std::string& name);
	void CreateUniform1iv(int shaderID, const std::string& name);
	void CreateUniform1f(int shaderID, const std::string& name);
	void CreateUniform3f(int shaderID, const std::string& name);
	void CreateUniform4i(int shaderID, const std::string& name);
	void CreateUniform4f(int shaderID, const std::string& name);
	void CreateUniformMat4f(int shaderID, const std::string& name);

	void SetUniform1i(int shaderID, const std::string& name, int v1);
	void SetUniform1iv(int shaderID, const std::string& name, unsigned int count, int v1[]);
	void SetUniform1f(int shaderID, const std::string& name, float v1);
	void SetUniform3f(int shaderID, const std::string& name, float v1, float v2, float v3);
	void SetUniform4i(int shaderID, const std::string& name, int v1, int v2, int v3, int v4);
	void SetUniform4f(int shaderID, const std::string& name, float v1, float v2, float v3, float v4);
	void SetUniformMat4f(int shaderID, const std::string& name, const glm::mat4& matrix);

	void GetUniformData(int shaderID, const std::string& name);
	void GetAttribData(int shaderID, const std::string& name);

	std::string GetData(int shaderID);
private:
	std::unordered_map<int, Shader*> m_Shaders;
};