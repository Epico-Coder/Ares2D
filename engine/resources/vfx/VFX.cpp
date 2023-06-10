#include "VFX.h"

#include "vfx.h"

namespace Ares2D
{
    /*-------------------------- Public Functions --------------------------*/

    VFX::VFX(float screenWidth, float screenHeight)
        : m_screen_width(screenWidth), m_screen_height(screenHeight)
    {
    }

    VFX::~VFX()
    {
    }

    VFX& VFX::Instance()
    {
        static VFX instance(1280, 720);
        return instance;
    }

    
    void VFX::AddVFX(const std::string& id)
    {
        Instance().i_AddVFX(id);
    }

    void VFX::Start()
    {
        Instance().i_Start();
    }

    void VFX::Apply(const std::string& id, VFX_TYPE type, float x, float y, float width, float height)
    {
        Instance().i_Apply(id, type, x, y, width, height);
    }

    void VFX::End()
    {
        Instance().i_End();
    }

    /*-------------------------- Intenal Functions --------------------------*/


    void VFX::i_AddVFX(const std::string& id)
    {
        if (!m_VFXs.contains(id))
        {
            VFX_ELEMENT* vfx = new VFX_ELEMENT(m_screen_width, m_screen_height);
            m_VFXs[id] = vfx;
        }
    }

    void VFX::i_Start()
    {
        // Binds the first fbo to begin with
        if (!m_VFXs.empty())
        {
            auto currentIter = m_VFXs.begin();
            currentIter->second->Start();

            while (currentIter != m_VFXs.end())
            {
                currentIter->second->SetNoEffect();
                currentIter = std::next(currentIter);
            }
        }
    }

    void VFX::i_Apply(const std::string& id, VFX_TYPE type, float x, float y, float width, float height)
    {
        // Applies region and type of effect
        // TODO: Allows entering custom shader code / type of effect
        auto it = m_VFXs.find(id);
        if (it != m_VFXs.end())
        {
            it->second->Apply(type, x, y, width, height);
        }
    }

    void VFX::i_End()
    {
        if (!m_VFXs.empty())
        {
            auto currentIter = m_VFXs.begin();

            /*
            How it goes:

            Unbinds the current fbo
            Starts the next fbo
            Ends/Draws the current fbo (result gets stored in the next fbo)
            */

            while (currentIter != m_VFXs.end())
            {
                currentIter->second->Unbind();

                auto nextIter = std::next(currentIter);
                if (nextIter != m_VFXs.end())
                {
                    nextIter->second->Start();
                }

                currentIter->second->End();

                currentIter = nextIter;
            }
        }
    }

    /*-------------------------- Child Functions --------------------------*/

    VFX::VFX_ELEMENT::VFX_ELEMENT(float screenWidth, float screenHeight)
        : m_width(screenWidth), m_height(screenHeight)
    {
        m_fbo.Bind();

        m_texture.Bind();
        m_texture.LoadData(GL_RGB, GL_RGB, m_width, m_height, nullptr);
        m_fbo.AttachTexture2D(m_texture, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0);

        m_rbo.Bind();
        m_rbo.storage(GL_DEPTH24_STENCIL8, m_width, m_height);
        m_fbo.AttachRenderBuffer(m_rbo, GL_DEPTH_STENCIL_ATTACHMENT);

        float vertices[4 * 3 * 2] =
        {
            -1.0f, -1.0f, 0.0f, 0.0f,
             1.0f, -1.0f, 1.0f, 0.0f,
             1.0f,  1.0f, 1.0f, 1.0f,

             1.0f,  1.0f, 1.0f, 1.0f,
            -1.0f,  1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f
        };

        m_vbo.SetSize(sizeof(vertices));
        m_vbo.Update(vertices, sizeof(vertices), 0);

        m_vbl.Push<float>(2);
        m_vbl.Push<float>(2);

        m_vao.AddBuffer(m_vbo, m_vbl);

        m_shader.AddVertexShader("engine/resources/vfx/shaders/vert_vfx.shader");
        m_shader.AddFragmentShader("engine/resources/vfx/shaders/frag_vfx.shader");
        m_shader.Create();
    }

    VFX::VFX_ELEMENT::~VFX_ELEMENT()
    {
    }

    void VFX::VFX_ELEMENT::SetNoEffect()
    {
        m_shader.Bind();

        m_shader.SetUniform1i("u_torque", 0);
        m_shader.SetUniform1i("u_wavy", 0);
        m_shader.SetUniform1i("u_grayscale", 0);
        m_shader.SetUniform1i("u_sharpen", 0);
        m_shader.SetUniform1i("u_edges", 0);
        m_shader.SetUniform1i("u_blur", 0);

        m_shader.Unbind();
    }

    void VFX::VFX_ELEMENT::Start()
    {
        m_fbo.Bind();
    }

    void VFX::VFX_ELEMENT::Unbind()
    {
        m_fbo.Unbind();
    }

    void VFX::VFX_ELEMENT::End()
    {
        m_vao.Bind();
        m_shader.Bind();

        unsigned int slot = 0;

        m_shader.SetUniform1i("texFrameBuffer", slot);
        glActiveTexture(GL_TEXTURE0 + slot);
        m_texture.Bind(slot);

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void VFX::VFX_ELEMENT::Apply(VFX_TYPE type, float x, float y, float width, float height)
    {
        m_shader.Bind();

        m_shader.SetUniform1i("u_screen_width", m_width);
        m_shader.SetUniform1i("u_screen_height", m_height);

        m_shader.SetUniform1f("u_RegionX", x);
        m_shader.SetUniform1f("u_RegionY", y);
        m_shader.SetUniform1f("u_RegionWidth", width);
        m_shader.SetUniform1f("u_RegionHeight", height);

        GLfloat move = glfwGetTime();
        m_shader.SetUniform1f("u_time", move);

        switch (type)
        {
        case(VFX_TYPE::EFFECT_NORMAL):
            break;
        case(VFX_TYPE::EFFECT_TORQUE):
            m_shader.SetUniform1i("u_torque", 1);
            break;
        case(VFX_TYPE::EFFECT_WAVY):
            m_shader.SetUniform1i("u_wavy", 1);
            break;
        case(VFX_TYPE::EFFECT_GRAYSCALE):
            m_shader.SetUniform1i("u_grayscale", 1);
            break;
        case(VFX_TYPE::EFFECT_SHARPEN):
            m_shader.SetUniform1i("u_sharpen", 1);
            break;
        case(VFX_TYPE::EFFECT_EDGES):
            m_shader.SetUniform1i("u_edges", 1);
            break;
        case(VFX_TYPE::EFFECT_BLUR):
            m_shader.SetUniform1i("u_blur", 1);
            break;
        default:
            break;
        }

        m_shader.Unbind();
    }

};
