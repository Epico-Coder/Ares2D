#include "VFX.h"

VFXHandler::VFXHandler(Renderer* renderer, TextureHandler* texture_handler)
    : m_renderer(renderer), m_texture_handler(texture_handler)
{

}

VFXHandler::~VFXHandler()
{
}

void VFXHandler::AddVFX(const std::string& vert_filepath, const std::string& frag_filepath, int VFXID)
{
    m_VFXs[VFXID] = new VFX(vert_filepath, frag_filepath);
}

void VFXHandler::RemoveVFX(int VFXID)
{
    auto iter = m_VFXs.find(VFXID);
    if (iter == m_VFXs.end()) {
        std::cout << "VFX with ID " << VFXID << " does not exist" << std::endl;
    }
    else
    {
        m_VFXs.erase(iter);
    }
}

void VFXHandler::Start(int VFXID)
{
    auto iter = m_VFXs.find(VFXID);
    if (iter != m_VFXs.end())
    {
        iter->second->Start();
    }
}

void VFXHandler::End(int VFXID)
{
    auto iter = m_VFXs.find(VFXID);
    if (iter != m_VFXs.end())
    {
        iter->second->End(m_renderer);
    }
}

Texture VFXHandler::GetTexture(int VFXID)
{
    auto iter = m_VFXs.find(VFXID);
    if (iter != m_VFXs.end())
    {
        return iter->second->GetTexture();
    }
}

VFXHandler::VFX::VFX(const std::string& vert_filepath, const std::string& frag_filepath)
    : m_texture(m_width, m_height, nullptr)
{
    m_shader.AddVertexShader(vert_filepath);
    m_shader.AddFragmentShader(frag_filepath);
    m_shader.Create();

    m_rbo.Bind();
    m_rbo.storage(GL_DEPTH24_STENCIL8, m_width, m_height);

    m_fbo.Bind();
    m_fbo.AttachTexture2D(m_texture, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0);
    m_fbo.AttachRenderBuffer(m_rbo, GL_DEPTH_STENCIL_ATTACHMENT);
    auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete: " << std::to_string(fboStatus) << std::endl;

    m_fbo.Unbind();
}

VFXHandler::VFX::~VFX()
{
}

void VFXHandler::VFX::Start()
{
    // Save current framebuffer

    m_fbo.Bind();
    m_texture.Unbind();
    glEnable(GL_DEPTH_TEST);

    // Set viewport and clear framebuffer
    

    // Use shader program
}

void VFXHandler::VFX::End(Renderer* renderer)
{
    // Restore previous framebuffer
    m_fbo.Unbind();
    glDisable(GL_DEPTH_TEST);
    
    /*
    m_texture_handler->AddTexture()
    m_shader.Bind();
    Rect rect(640, 360, 1280, 720, 3, 0);
    rect.Draw(*renderer, 640, 360);
    */

    // Quad covering the screen
    const float quadVertices[24]
    {
            -1.0f,  1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
             1.0f, -1.0f, 1.0f, 0.0f,

            -1.0f,  1.0f, 0.0f, 1.0f,
             1.0f, -1.0f, 1.0f, 0.0f,
             1.0f,  1.0f, 1.0f, 1.0f
    };

    VertexBuffer vbo(&quadVertices, sizeof(quadVertices));
    VertexArray vao;
    vao.Bind();
    VertexBufferLayout vbl;
    vbl.Push<GLfloat>(2);
    vbl.Push<GLfloat>(2);
    vao.AddBuffer(vbo, vbl);

    m_texture.Bind();
    m_shader.Bind();
    vao.Bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

Texture VFXHandler::VFX::GetTexture()
{
    return m_texture;
}
