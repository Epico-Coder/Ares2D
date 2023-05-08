#pragma once

#include "dependancies/glew/include/GL/glew.h"

#include "engine/resources/shaders/Shader.h"
#include "engine/resources/textures/Texture.h"

#include <string>
#include <unordered_map>

class Resource
{
public:
	Resource(int tex_width=1280, int tex_height=720);
	~Resource();

	TextureUse AddTexture(const std::string& filepath);
	TextureUse AddTexture(GLenum sformat, GLenum dformat, int width, int height, unsigned char* data);

	void AddShader(const std::string& vert_file_path, const std::string& frag_file_path, int shaderID);

	void BindResource();

	void BindShader(int shaderID);
private:
	ShaderHandler m_sh;
	TextureHandler m_th;
};

class ResourceHandler
{
public:
	ResourceHandler();
	~ResourceHandler();

	// Add
	void AddResource(const std::string& name, int tex_width, int tex_height);

	TextureUse AddTexture(const std::string& name, const std::string& filepath);
	TextureUse AddTexture(const std::string& name, GLenum sformat, GLenum dformat, int width, int height, unsigned char* data);

	void AddShader(const std::string& name, const std::string& vert_file_path, const std::string& frag_file_path, int shaderID);

	// Use
	void BindResource(const std::string& name);

	void BindShader(const std::string& name, int shaderID);

	// Remove
	void RemoveResource(const std::string& name);
private:
	std::unordered_map<std::string, Resource> m_resources;
};

