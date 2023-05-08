#include "Resource.h"

Resource::Resource(int tex_width, int tex_height)
	: m_th(tex_width, tex_height)
{
}

Resource::~Resource()
{
}

TextureUse Resource::AddTexture(const std::string& filepath)
{
	return m_th.AddTexture(filepath);
}

TextureUse Resource::AddTexture(GLenum sformat, GLenum dformat, int width, int height, unsigned char* data)
{
	return m_th.AddTexture(sformat, dformat, width, height, data);
}

void Resource::AddShader(const std::string& vert_file_path, const std::string& frag_file_path, int shaderID)
{
	m_sh.AddShader(vert_file_path, frag_file_path, shaderID);
}

void Resource::BindResource()
{

}

void Resource::BindShader(int shaderID)
{
	m_sh.BindShader(shaderID);
}

ResourceHandler::ResourceHandler()
{
}

ResourceHandler::~ResourceHandler()
{
}

void ResourceHandler::AddResource(const std::string& name, int tex_width, int tex_height)
{
	if (m_resources.find(name) == m_resources.end()) 
	{
		m_resources[name] = Resource(tex_width, tex_height);
	}
	else 
	{
		std::cout << "Resource" << name << "already created" << std::endl;
	}
}

TextureUse ResourceHandler::AddTexture(const std::string& name, const std::string& filepath)
{
	auto it = m_resources.find(name);
	if (it != m_resources.end()) 
	{
		return it->second.AddTexture(filepath);
	}
	else
	{
		std::cout << "No resource called" << name << std::endl;
	}
}

TextureUse ResourceHandler::AddTexture(const std::string& name, GLenum sformat, GLenum dformat, int width, int height, unsigned char* data)
{
	auto it = m_resources.find(name);
	if (it != m_resources.end()) 
	{
		return it->second.AddTexture(sformat, dformat, width, height, data);
	}
	else
	{
		std::cout << "No resource called" << name << std::endl;
	}
}

void ResourceHandler::AddShader(const std::string& name, const std::string& vert_file_path, const std::string& frag_file_path, int shaderID)
{
	auto it = m_resources.find(name);
	if (it != m_resources.end()) 
	{
		it->second.AddShader(vert_file_path, frag_file_path, shaderID);
	}
	else
	{
		std::cout << "No resource called" << name << std::endl;
	}
}

void ResourceHandler::BindResource(const std::string& name)
{
	auto it = m_resources.find(name);
	if (it != m_resources.end()) 
	{
		it->second.BindResource();
	}
	else
	{
		std::cout << "No resource called" << name << std::endl;
	}
}

void ResourceHandler::BindShader(const std::string& name, int shaderID)
{
	auto it = m_resources.find(name);
	if (it != m_resources.end()) 
	{
		it->second.BindShader(shaderID);
	}
	else
	{
		std::cout << "No resource called" << name << std::endl;
	}
}

void ResourceHandler::RemoveResource(const std::string& name)
{
	auto it = m_resources.find(name);
	if (it != m_resources.end()) 
	{
		m_resources.erase(it);
	}
	else
	{
		std::cout << "No resource called" << name << std::endl;
	}
}
