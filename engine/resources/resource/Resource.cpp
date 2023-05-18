#include "Resource.h"

Resource::Resource(const std::string& resourceID, int tex_width, int tex_height)
	: m_th(tex_width, tex_height, resourceID)
{
	m_th.Init();
}

Resource::~Resource()
{
}

TextureUse Resource::AddTexture(const std::string& filepath, float scale)
{
	return m_th.AddTexture(filepath, scale);
}

TextureUse Resource::AddTexture(GLenum sformat, GLenum dformat, int width, int height, unsigned char* data)
{
	return m_th.AddTexture(sformat, dformat, width, height, data);
}

void Resource::AddShader(const std::string& vert_file_path, const std::string& frag_file_path, int shaderID)
{
	m_sh.AddShader(vert_file_path, frag_file_path, shaderID);
}

TextureUse Resource::FullTexture(int atlasID)
{
	return m_th.FullTexture(atlasID);
}

void Resource::BindShader(int shaderID)
{
	m_sh.BindShader(shaderID);
}

void Resource::BindTexture()
{
	m_th.Bind();
}

void Resource::SetUniform1i(int shaderID, const std::string& name, int v1)
{
	m_sh.SetUniform1f(shaderID, name, v1);
}

void Resource::SetUniform1iv(int shaderID, const std::string& name, unsigned int count, int v1[])
{
	m_sh.SetUniform1iv(shaderID, name, count, v1);
}

void Resource::SetUniform1f(int shaderID, const std::string& name, float v1)
{
	m_sh.SetUniform1f(shaderID, name, v1);
}

void Resource::SetUniform2fv(int shaderID, const std::string& name, const glm::vec2& vec)
{
	m_sh.SetUniform2fv(shaderID, name, vec);
}

void Resource::SetUniform3f(int shaderID, const std::string& name, float v1, float v2, float v3)
{
	m_sh.SetUniform3f(shaderID, name, v1, v2, v3);
}

void Resource::SetUniform4i(int shaderID, const std::string& name, int v1, int v2, int v3, int v4)
{
	m_sh.SetUniform4i(shaderID, name, v1, v2, v3, v4);
}

void Resource::SetUniform4f(int shaderID, const std::string& name, float v1, float v2, float v3, float v4)
{
	m_sh.SetUniform4f(shaderID, name, v1, v2, v3, v4);
}

void Resource::SetUniform4fv(int shaderID, const std::string& name, const glm::vec4& vec)
{
	m_sh.SetUniform4fv(shaderID, name, vec);
}

void Resource::SetUniformMat4f(int shaderID, const std::string& name, const glm::mat4& matrix)
{
	m_sh.SetUniformMat4f(shaderID, name, matrix);
}

ResourceHandler::ResourceHandler()
{
}

ResourceHandler::~ResourceHandler()
{
	for (auto it : m_resources)
	{
		delete(it.second);
	}
}

void ResourceHandler::AddResource(const std::string& resourceID, int tex_width, int tex_height)
{
	if (m_resources.find(resourceID) == m_resources.end()) 
	{
		m_resources[resourceID] = new Resource(resourceID, tex_width, tex_height);
	}
	else 
	{
		std::cout << "Resource" << resourceID << "already created" << std::endl;
	}
}

TextureUse ResourceHandler::AddTexture(const std::string& resourceID, const std::string& filepath, float scale)
{
	auto it = m_resources.find(resourceID);
	if (it != m_resources.end()) 
	{
		return it->second->AddTexture(filepath, scale);
	}
	else
	{
		std::cout << "No resource called: " << resourceID << std::endl;
	}
}

TextureUse ResourceHandler::AddTexture(const std::string& resourceID, GLenum sformat, GLenum dformat, int width, int height, unsigned char* data)
{
	auto it = m_resources.find(resourceID);
	if (it != m_resources.end()) 
	{
		return it->second->AddTexture(sformat, dformat, width, height, data);
	}
	else
	{
		std::cout << "No resource called: " << resourceID << std::endl;
	}
}

void ResourceHandler::AddShader(const std::string& resourceID, int shaderID, const std::string& vert_file_path, const std::string& frag_file_path)
{
	auto it = m_resources.find(resourceID);
	if (it != m_resources.end()) 
	{
		it->second->AddShader(vert_file_path, frag_file_path, shaderID);
	}
	else
	{
		std::cout << "No resource called: " << resourceID << std::endl;
	}
}

void ResourceHandler::BindResource(const std::string& resourceID, int shaderID)
{
	auto it = m_resources.find(resourceID);
	if (it != m_resources.end())
	{
		it->second->BindShader(shaderID);
		it->second->BindTexture();
	}
	else
	{
		std::cout << "No resource called: " << resourceID << std::endl;
	}
}

TextureUse ResourceHandler::FullTexture(const std::string& resourceID, int atlasID)
{
	auto it = m_resources.find(resourceID);
	if (it != m_resources.end())
	{
		return it->second->FullTexture(atlasID);
	}
	else
	{
		std::cout << "No resource called: " << resourceID << std::endl;
	}
}

void ResourceHandler::SetUniform1i(const std::string& resourceID, int shaderID, const std::string& name, int v1)
{
	auto it = m_resources.find(resourceID);
	if (it != m_resources.end())
	{
		it->second->SetUniform1i(shaderID, name, v1);
	}
	else
	{
		std::cout << "No resource called: " << resourceID << std::endl;
	}
}

void ResourceHandler::SetUniform1iv(const std::string& resourceID, int shaderID, const std::string& name, unsigned int count, int v1[])
{
	auto it = m_resources.find(resourceID);
	if (it != m_resources.end())
	{
		it->second->SetUniform1iv(shaderID, name, count, v1);
	}
	else
	{
		std::cout << "No resource called: " << resourceID << std::endl;
	}
}

void ResourceHandler::SetUniform1f(const std::string& resourceID, int shaderID, const std::string& name, float v1)
{
	auto it = m_resources.find(resourceID);
	if (it != m_resources.end())
	{
		it->second->SetUniform1f(shaderID, name, v1);
	}
	else
	{
		std::cout << "No resource called: " << resourceID << std::endl;
	}
}

void ResourceHandler::SetUniform2fv(const std::string& resourceID, int shaderID, const std::string& name, const glm::vec2& vec)
{
	auto it = m_resources.find(resourceID);
	if (it != m_resources.end())
	{
		it->second->SetUniform2fv(shaderID, name, vec);
	}
	else
	{
		std::cout << "No resource called: " << resourceID << std::endl;
	}
}

void ResourceHandler::SetUniform3f(const std::string& resourceID, int shaderID, const std::string& name, float v1, float v2, float v3)
{
	auto it = m_resources.find(resourceID);
	if (it != m_resources.end())
	{
		it->second->SetUniform3f(shaderID, name, v1, v2, v3);
	}
	else
	{
		std::cout << "No resource called: " << resourceID << std::endl;
	}
}

void ResourceHandler::SetUniform4i(const std::string& resourceID, int shaderID, const std::string& name, int v1, int v2, int v3, int v4)
{
	auto it = m_resources.find(resourceID);
	if (it != m_resources.end())
	{
		it->second->SetUniform4i(shaderID, name, v1, v2, v3, v4);
	}
	else
	{
		std::cout << "No resource called: " << resourceID << std::endl;
	}
}

void ResourceHandler::SetUniform4f(const std::string& resourceID, int shaderID, const std::string& name, float v1, float v2, float v3, float v4)
{
	auto it = m_resources.find(resourceID);
	if (it != m_resources.end())
	{
		it->second->SetUniform4f(shaderID, name, v1, v2, v3, v4);
	}
	else
	{
		std::cout << "No resource called: " << resourceID << std::endl;
	}
}

void ResourceHandler::SetUniform4fv(const std::string& resourceID, int shaderID, const std::string& name, const glm::vec4& vec)
{
	auto it = m_resources.find(resourceID);
	if (it != m_resources.end())
	{
		it->second->SetUniform4fv(shaderID, name, vec);
	}
	else
	{
		std::cout << "No resource called: " << resourceID << std::endl;
	}
}

void ResourceHandler::SetUniformMat4f(const std::string& resourceID, int shaderID, const std::string& name, const glm::mat4& matrix)
{
	auto it = m_resources.find(resourceID);
	if (it != m_resources.end())
	{
		it->second->SetUniformMat4f(shaderID, name, matrix);
	}
	else
	{
		std::cout << "No resource called: " << resourceID << std::endl;
	}
}

void ResourceHandler::RemoveResource(const std::string& resourceID)
{
	auto it = m_resources.find(resourceID);
	if (it != m_resources.end()) 
	{
		m_resources.erase(it);
	}
	else
	{
		std::cout << "No resource called: " << resourceID << std::endl;
	}
}
