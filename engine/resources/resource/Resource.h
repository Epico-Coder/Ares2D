#pragma once

#include "dependancies/glew/include/GL/glew.h"

#include "engine/resources/shaders/Shader.h"
#include "engine/resources/textures/Texture.h"

#include <string>
#include <unordered_map>

namespace Ares2D
{
	class Resource
	{
	public:
		static Resource& Instance();

		Resource(Resource const&) = delete;
		void operator=(Resource const&) = delete;

		static void AddResource(const std::string& resourceID, int tex_width, int tex_height);
		static void BindResource(const std::string& resourceID, int shaderID);
		static void RemoveResource(const std::string& resourceID);

		static TextureUse AddTexture(const std::string& resourceID, const std::string& filepath, float scale = 1.0f);
		static TextureUse AddTexture(const std::string& resourceID, GLenum sformat, GLenum dformat, int width, int height, unsigned char* data);

		static TextureUse FullTexture(const std::string& resourceID, int atlasID);


		static void AddShader(const std::string& resourceID, int shaderID, const std::string& vert_file_path = "engine/resources/resource/shaders/vert_default.shader", const std::string& frag_file_path = "engine/resources/resource/shaders/frag_default.shader");

		static void SetUniform1i(const std::string& resourceID, int shaderID, const std::string& name, int v1);
		static void SetUniform1iv(const std::string& resourceID, int shaderID, const std::string& name, unsigned int count, int v1[]);
		static void SetUniform1f(const std::string& resourceID, int shaderID, const std::string& name, float v1);
		static void SetUniform2fv(const std::string& resourceID, int shaderID, const std::string& name, const glm::vec2& vec);
		static void SetUniform3f(const std::string& resourceID, int shaderID, const std::string& name, float v1, float v2, float v3);
		static void SetUniform4i(const std::string& resourceID, int shaderID, const std::string& name, int v1, int v2, int v3, int v4);
		static void SetUniform4f(const std::string& resourceID, int shaderID, const std::string& name, float v1, float v2, float v3, float v4);
		static void SetUniform4fv(const std::string& resourceID, int shaderID, const std::string& name, const glm::vec4& vec);
		static void SetUniformMat4f(const std::string& resourceID, int shaderID, const std::string& name, const glm::mat4& matrix);
	private:
		Resource();
		~Resource();
	private:
		void i_AddResource(const std::string& resourceID, int tex_width, int tex_height);
		void i_BindResource(const std::string& resourceID, int shaderID);
		void i_RemoveResource(const std::string& resourceID);

		TextureUse i_AddTexture(const std::string& resourceID, const std::string& filepath, float scale = 1.0f);
		TextureUse i_AddTexture(const std::string& resourceID, GLenum sformat, GLenum dformat, int width, int height, unsigned char* data);

		TextureUse i_FullTexture(const std::string& resourceID, int atlasID);


		void i_AddShader(const std::string& resourceID, int shaderID, const std::string& vert_file_path = "engine/resources/resource/shaders/vert_default.shader", const std::string& frag_file_path = "engine/resources/resource/shaders/frag_default.shader");

		void i_SetUniform1i(const std::string& resourceID, int shaderID, const std::string& name, int v1);
		void i_SetUniform1iv(const std::string& resourceID, int shaderID, const std::string& name, unsigned int count, int v1[]);
		void i_SetUniform1f(const std::string& resourceID, int shaderID, const std::string& name, float v1);
		void i_SetUniform2fv(const std::string& resourceID, int shaderID, const std::string& name, const glm::vec2& vec);
		void i_SetUniform3f(const std::string& resourceID, int shaderID, const std::string& name, float v1, float v2, float v3);
		void i_SetUniform4i(const std::string& resourceID, int shaderID, const std::string& name, int v1, int v2, int v3, int v4);
		void i_SetUniform4f(const std::string& resourceID, int shaderID, const std::string& name, float v1, float v2, float v3, float v4);
		void i_SetUniform4fv(const std::string& resourceID, int shaderID, const std::string& name, const glm::vec4& vec);
		void i_SetUniformMat4f(const std::string& resourceID, int shaderID, const std::string& name, const glm::mat4& matrix);
	private:
		class Resource_Element
		{
		public:
			Resource_Element(const std::string& name, int tex_width = 1280, int tex_height = 720);
			~Resource_Element();

			TextureUse AddTexture(const std::string& filepath, float scale = 1.0f);
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
	private:
		std::unordered_map<std::string, Resource_Element*> m_resources;
	};
};