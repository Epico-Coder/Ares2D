#pragma once

#include "dependancies/glew/include/GL/glew.h"

#include "engine/rendering/Renderer.h"

#include "engine/resources/shaders/Shader.h"
#include "engine/resources/textures/Texture.h"

#include <string>
#include <unordered_map>

class Resource
{
	friend class ResourceHandler;
public:
	Resource(const std::string& name, int tex_width=1280, int tex_height=720);
	~Resource();

	TextureUse AddTexture(const std::string& filepath);
	TextureUse AddTexture(GLenum sformat, GLenum dformat, int width, int height, unsigned char* data);

	TextureUse FullTexture(int atlasID);

	void AddShader(const std::string& vert_file_path, const std::string& frag_file_path, int shaderID);

	void BindShader(int shaderID);
	void BindTexture();


	void SetUniform1i(int shaderID, const std::string& name, int v1);
	void SetUniform1iv(int shaderID, const std::string& name, unsigned int count, int v1[]);
	void SetUniform1f(int shaderID, const std::string& name, float v1);
	void SetUniform2fv(int shaderID, const std::string& name, const glm::vec2& vec);
	void SetUniform3f(int shaderID, const std::string& name, float v1, float v2, float v3);
	void SetUniform4i(int shaderID, const std::string& name, int v1, int v2, int v3, int v4);
	void SetUniform4f(int shaderID, const std::string& name, float v1, float v2, float v3, float v4);
	void SetUniform4fv(int shaderID, const std::string& name, const glm::vec4& vec);
	void SetUniformMat4f(int shaderID, const std::string& name, const glm::mat4& matrix);
private:
	ShaderHandler m_sh;
	TextureHandler m_th;
};

class ResourceHandler
{
public:
	ResourceHandler(Renderer* renderer);
	~ResourceHandler();

	void AddResource(const std::string& resourceID, int tex_width, int tex_height);
	void BindResource(const std::string& resourceID, int shaderID);
	void RemoveResource(const std::string& resourceID);

	TextureUse AddTexture(const std::string& resourceID, const std::string& filepath);
	TextureUse AddTexture(const std::string& resourceID, GLenum sformat, GLenum dformat, int width, int height, unsigned char* data);

	TextureUse FullTexture(const std::string& resourceID, int atlasID);


	void AddShader(const std::string& resourceID, const std::string& vert_file_path, const std::string& frag_file_path, int shaderID);

	void SetUniform1i(    const std::string& resourceID, int shaderID, const std::string& name, int v1                                 );
	void SetUniform1iv(   const std::string& resourceID, int shaderID, const std::string& name, unsigned int count, int v1[]           );
	void SetUniform1f(    const std::string& resourceID, int shaderID, const std::string& name, float v1                               );
	void SetUniform2fv(   const std::string& resourceID, int shaderID, const std::string& name, const glm::vec2& vec                   );
	void SetUniform3f(    const std::string& resourceID, int shaderID, const std::string& name, float v1, float v2, float v3           );
	void SetUniform4i(    const std::string& resourceID, int shaderID, const std::string& name, int v1, int v2, int v3, int v4         );
	void SetUniform4f(    const std::string& resourceID, int shaderID, const std::string& name, float v1, float v2, float v3, float v4 );
	void SetUniform4fv(   const std::string& resourceID, int shaderID, const std::string& name, const glm::vec4& vec                   );
	void SetUniformMat4f( const std::string& resourceID, int shaderID, const std::string& name, const glm::mat4& matrix                );
private:
	std::unordered_map<std::string, Resource*> m_resources;

	Renderer* m_renderer;
};

