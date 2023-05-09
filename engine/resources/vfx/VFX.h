#pragma once

#include "dependancies/glew/include/GL/glew.h"

#include "engine/rendering/Renderer.h"
#include "engine/resources/shaders/Shader.h"
#include "engine/rendering/geometry/Rect.h"

#include "engine/rendering/storage/FrameBuffer.h"
#include "engine/rendering/storage/RenderBuffer.h"
#include "engine/resources/textures/Texture.h"

#include <unordered_map>
#include <string>

class VFXHandler
{
public:
	VFXHandler(Renderer* renderer);
	~VFXHandler();

	void AddVFX(const std::string& vert_filepath, const std::string& frag_filepath, int VFXID);
	void RemoveVFX(int VFXID);

	void Start(int VFXID);
	void End(int VFXID);

	Texture GetTexture(int VFXID);
private:
	class VFX
	{
	public:
		VFX(const std::string& vert_filepath, const std::string& frag_filepath);
		~VFX();

		void Start();
		void End(Renderer* renderer);

		Texture GetTexture();
	private:
		int m_width = 1280;
		int m_height = 720;

		FrameBuffer m_fbo;
		RenderBuffer m_rbo;
		Texture m_texture;
		Shader m_shader;

		VertexArray m_vao;

		unsigned int m_fboi;
		unsigned int m_texturei;
	};
private:
	std::unordered_map<int, VFX*>m_VFXs;

	Renderer* m_renderer;
	//TextureHandler* m_texture_handler;
};

