#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glm/glm.hpp"
#include "dependancies/glm/gtc/matrix_transform.hpp"

#include "engine/rendering/Renderer.h"
#include "engine/resources/resource/Resource.h"
#include "engine/resources/shaders/Shader.h"
#include "engine/rendering/geometry/Rect.h"

#include "engine/rendering/storage/FrameBuffer.h"
#include "engine/rendering/storage/RenderBuffer.h"
#include "engine/resources/textures/Texture.h"

#include <unordered_map>
#include <map>
#include <string>

namespace Ares2D
{
    enum class VFX_TYPE
    {
        EFFECT_NORMAL,
        EFFECT_TORQUE,
        EFFECT_WAVY,
        EFFECT_GRAYSCALE,
        EFFECT_SHARPEN,
        EFFECT_EDGES,
        EFFECT_BLUR,
    };

    class VFX
    {
    public:
        static VFX& Instance();

        static void AddVFX(const std::string& id);
        static void Start();
        static void Apply(const std::string& id, VFX_TYPE type, float x, float y, float width, float height);
        static void End();
    private:
        VFX(float screenWidth, float screenHeight);
        ~VFX();
    private:
        void i_AddVFX(const std::string& id);
        void i_Start();
        void i_Apply(const std::string& id, VFX_TYPE type, float x, float y, float width, float height);
        void i_End();
    private:
        class VFX_ELEMENT
        {
        public:
            VFX_ELEMENT(float screenWidth, float screenHeight);
            ~VFX_ELEMENT();

            void Start();
            void Unbind();
            void End();
            void SetNoEffect();
            void Apply(VFX_TYPE type, float x, float y, float width, float height);

        private:
            const float m_width, m_height;

            FrameBuffer m_fbo;
            RenderBuffer m_rbo;
            Texture m_texture;

            VertexBuffer m_vbo;
            VertexBufferLayout m_vbl;

            VertexArray m_vao;
            Shader m_shader;
        };
    private:
        const float m_screen_width;
        const float m_screen_height;

        std::map<std::string, VFX_ELEMENT*> m_VFXs;
    };
};