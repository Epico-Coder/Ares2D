#include "Resource.h"

namespace Ares2D
{
	Resource::Resource()
	{
	}

	Resource::~Resource()
	{
		for (auto it : m_resources)
		{
			delete(it.second);
		}
	}

	/*-------------------------- Public Functions --------------------------*/

	Resource& Resource::Instance()
	{
		static Resource instance;
		return instance;
	}

	void Resource::AddResource(const std::string& resourceID, int tex_width, int tex_height)
	{
		Instance().i_AddResource(resourceID, tex_width, tex_height);
	}

	void Resource::BindResource(const std::string& resourceID, int shaderID)
	{
		Instance().i_BindResource(resourceID, shaderID);
	}

	void Resource::RemoveResource(const std::string& resourceID)
	{
		Instance().i_RemoveResource(resourceID);
	}

	TextureUse Resource::AddTexture(const std::string& resourceID, const std::string& filepath, float scale)
	{
		return Instance().i_AddTexture(resourceID, filepath, scale);
	}

	TextureUse Resource::AddTexture(const std::string& resourceID, GLenum sformat, GLenum dformat, int width, int height, unsigned char* data)
	{
		return Instance().i_AddTexture(resourceID, sformat, dformat, width, height, data);
	}

	TextureUse Resource::FullTexture(const std::string& resourceID, int atlasID)
	{
		return Instance().i_FullTexture(resourceID, atlasID);
	}

	void Resource::AddShader(const std::string& resourceID, int shaderID, const std::string& vert_file_path, const std::string& frag_file_path)
	{
		Instance().i_AddShader(resourceID, shaderID, vert_file_path, frag_file_path);
	}

	void Resource::SetUniform1i(const std::string& resourceID, int shaderID, const std::string& name, int v1)
	{
		Instance().i_SetUniform1i(resourceID, shaderID, name, v1);
	}

	void Resource::SetUniform1iv(const std::string& resourceID, int shaderID, const std::string& name, unsigned int count, int v1[])
	{
		Instance().i_SetUniform1iv(resourceID, shaderID, name, count, v1);
	}

	void Resource::SetUniform1f(const std::string& resourceID, int shaderID, const std::string& name, float v1)
	{
		Instance().i_SetUniform1f(resourceID, shaderID, name, v1);
	}

	void Resource::SetUniform2fv(const std::string& resourceID, int shaderID, const std::string& name, const glm::vec2& vec)
	{
		Instance().i_SetUniform2fv(resourceID, shaderID, name, vec);
	}

	void Resource::SetUniform3f(const std::string& resourceID, int shaderID, const std::string& name, float v1, float v2, float v3)
	{
		Instance().i_SetUniform3f(resourceID, shaderID, name, v1, v2, v3);
	}

	void Resource::SetUniform4i(const std::string& resourceID, int shaderID, const std::string& name, int v1, int v2, int v3, int v4)
	{
		Instance().i_SetUniform4i(resourceID, shaderID, name, v1, v2, v3, v4);
	}

	void Resource::SetUniform4f(const std::string& resourceID, int shaderID, const std::string& name, float v1, float v2, float v3, float v4)
	{
		Instance().i_SetUniform4f(resourceID, shaderID, name, v1, v2, v3, v4);
	}

	void Resource::SetUniform4fv(const std::string& resourceID, int shaderID, const std::string& name, const glm::vec4& vec)
	{
		Instance().i_SetUniform4fv(resourceID, shaderID, name, vec);
	}

	void Resource::SetUniformMat4f(const std::string& resourceID, int shaderID, const std::string& name, const glm::mat4& matrix)
	{
		Instance().i_SetUniformMat4f(resourceID, shaderID, name, matrix);
	}

	/*-------------------------- Internal Functions --------------------------*/

	void Resource::i_AddResource(const std::string& resourceID, int tex_width, int tex_height)
	{
		if (m_resources.find(resourceID) == m_resources.end())
		{
			m_resources[resourceID] = new Resource_Element(resourceID, tex_width, tex_height);
		}
		else
		{
			std::cout << "Resource" << resourceID << "already created" << std::endl;
		}
	}

	TextureUse Resource::i_AddTexture(const std::string& resourceID, const std::string& filepath, float scale)
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

	TextureUse Resource::i_AddTexture(const std::string& resourceID, GLenum sformat, GLenum dformat, int width, int height, unsigned char* data)
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

	void Resource::i_AddShader(const std::string& resourceID, int shaderID, const std::string& vert_file_path, const std::string& frag_file_path)
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

	void Resource::i_BindResource(const std::string& resourceID, int shaderID)
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

	TextureUse Resource::i_FullTexture(const std::string& resourceID, int atlasID)
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

	void Resource::i_SetUniform1i(const std::string& resourceID, int shaderID, const std::string& name, int v1)
	{
		auto it = m_resources.find(resourceID);
		if (it != m_resources.end())
		{
			it->second->BindShader(shaderID);
			it->second->SetUniform1i(shaderID, name, v1);
		}
		else
		{
			std::cout << "No resource called: " << resourceID << std::endl;
		}
	}

	void Resource::i_SetUniform1iv(const std::string& resourceID, int shaderID, const std::string& name, unsigned int count, int v1[])
	{
		auto it = m_resources.find(resourceID);
		if (it != m_resources.end())
		{
			it->second->BindShader(shaderID);
			it->second->SetUniform1iv(shaderID, name, count, v1);
		}
		else
		{
			std::cout << "No resource called: " << resourceID << std::endl;
		}
	}

	void Resource::i_SetUniform1f(const std::string& resourceID, int shaderID, const std::string& name, float v1)
	{
		auto it = m_resources.find(resourceID);
		if (it != m_resources.end())
		{
			it->second->BindShader(shaderID);
			it->second->SetUniform1f(shaderID, name, v1);
		}
		else
		{
			std::cout << "No resource called: " << resourceID << std::endl;
		}
	}

	void Resource::i_SetUniform2fv(const std::string& resourceID, int shaderID, const std::string& name, const glm::vec2& vec)
	{
		auto it = m_resources.find(resourceID);
		if (it != m_resources.end())
		{
			it->second->BindShader(shaderID);
			it->second->SetUniform2fv(shaderID, name, vec);
		}
		else
		{
			std::cout << "No resource called: " << resourceID << std::endl;
		}
	}

	void Resource::i_SetUniform3f(const std::string& resourceID, int shaderID, const std::string& name, float v1, float v2, float v3)
	{
		auto it = m_resources.find(resourceID);
		if (it != m_resources.end())
		{
			it->second->BindShader(shaderID);
			it->second->SetUniform3f(shaderID, name, v1, v2, v3);
		}
		else
		{
			std::cout << "No resource called: " << resourceID << std::endl;
		}
	}

	void Resource::i_SetUniform4i(const std::string& resourceID, int shaderID, const std::string& name, int v1, int v2, int v3, int v4)
	{
		auto it = m_resources.find(resourceID);
		if (it != m_resources.end())
		{
			it->second->BindShader(shaderID);
			it->second->SetUniform4i(shaderID, name, v1, v2, v3, v4);
		}
		else
		{
			std::cout << "No resource called: " << resourceID << std::endl;
		}
	}

	void Resource::i_SetUniform4f(const std::string& resourceID, int shaderID, const std::string& name, float v1, float v2, float v3, float v4)
	{
		auto it = m_resources.find(resourceID);
		if (it != m_resources.end())
		{
			it->second->BindShader(shaderID);
			it->second->SetUniform4f(shaderID, name, v1, v2, v3, v4);
		}
		else
		{
			std::cout << "No resource called: " << resourceID << std::endl;
		}
	}

	void Resource::i_SetUniform4fv(const std::string& resourceID, int shaderID, const std::string& name, const glm::vec4& vec)
	{
		auto it = m_resources.find(resourceID);
		if (it != m_resources.end())
		{
			it->second->BindShader(shaderID);
			it->second->SetUniform4fv(shaderID, name, vec);
		}
		else
		{
			std::cout << "No resource called: " << resourceID << std::endl;
		}
	}

	void Resource::i_SetUniformMat4f(const std::string& resourceID, int shaderID, const std::string& name, const glm::mat4& matrix)
	{
		auto it = m_resources.find(resourceID);
		if (it != m_resources.end())
		{
			it->second->BindShader(shaderID);
			it->second->SetUniformMat4f(shaderID, name, matrix);
		}
		else
		{
			std::cout << "No resource called: " << resourceID << std::endl;
		}
	}

	void Resource::i_RemoveResource(const std::string& resourceID)
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

	/*-------------------------- Child Functions --------------------------*/

	Resource::Resource_Element::Resource_Element(const std::string& resourceID, int tex_width, int tex_height)
		: m_th(tex_width, tex_height, resourceID)
	{
		m_th.Init();
	}

	Resource::Resource_Element::~Resource_Element()
	{
	}

	TextureUse Resource::Resource_Element::AddTexture(const std::string& filepath, float scale)
	{
		return m_th.AddTexture(filepath, scale);
	}

	TextureUse Resource::Resource_Element::AddTexture(GLenum sformat, GLenum dformat, int width, int height, unsigned char* data)
	{
		return m_th.AddTexture(sformat, dformat, width, height, data);
	}

	void Resource::Resource_Element::AddShader(const std::string& vert_file_path, const std::string& frag_file_path, int shaderID)
	{
		m_sh.AddShader(vert_file_path, frag_file_path, shaderID);
	}

	TextureUse Resource::Resource_Element::FullTexture(int atlasID)
	{
		return m_th.FullTexture(atlasID);
	}

	void Resource::Resource_Element::BindShader(int shaderID)
	{
		m_sh.BindShader(shaderID);
	}

	void Resource::Resource_Element::BindTexture()
	{
		m_th.Bind();
	}

	void Resource::Resource_Element::SetUniform1i(int shaderID, const std::string& name, int v1)
	{
		m_sh.SetUniform1f(shaderID, name, v1);
	}

	void Resource::Resource_Element::SetUniform1iv(int shaderID, const std::string& name, unsigned int count, int v1[])
	{
		m_sh.SetUniform1iv(shaderID, name, count, v1);
	}

	void Resource::Resource_Element::SetUniform1f(int shaderID, const std::string& name, float v1)
	{
		m_sh.SetUniform1f(shaderID, name, v1);
	}

	void Resource::Resource_Element::SetUniform2fv(int shaderID, const std::string& name, const glm::vec2& vec)
	{
		m_sh.SetUniform2fv(shaderID, name, vec);
	}

	void Resource::Resource_Element::SetUniform3f(int shaderID, const std::string& name, float v1, float v2, float v3)
	{
		m_sh.SetUniform3f(shaderID, name, v1, v2, v3);
	}

	void Resource::Resource_Element::SetUniform4i(int shaderID, const std::string& name, int v1, int v2, int v3, int v4)
	{
		m_sh.SetUniform4i(shaderID, name, v1, v2, v3, v4);
	}

	void Resource::Resource_Element::SetUniform4f(int shaderID, const std::string& name, float v1, float v2, float v3, float v4)
	{
		m_sh.SetUniform4f(shaderID, name, v1, v2, v3, v4);
	}

	void Resource::Resource_Element::SetUniform4fv(int shaderID, const std::string& name, const glm::vec4& vec)
	{
		m_sh.SetUniform4fv(shaderID, name, vec);
	}

	void Resource::Resource_Element::SetUniformMat4f(int shaderID, const std::string& name, const glm::mat4& matrix)
	{
		m_sh.SetUniformMat4f(shaderID, name, matrix);
	}
};
