#include "UI.h"
#include <iostream>

Font::Font(ResourceHandler& resource_handler, const std::string& filepath, int size)
    : m_font_size(size), m_filepath(filepath)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    FT_Face face;
    if (FT_New_Face(ft, filepath.c_str(), 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }

    //FT_Set_Char_Size(face, 0, size * 64, 0, size);
    FT_Set_Pixel_Sizes(face, 0, size);


    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // All the readable ascii
    for (unsigned char c = 32; c <= 126; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        TextureUse texture_use = resource_handler.AddTexture(resource_name, GL_ALPHA, GL_ALPHA, face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer);
        
        Character character = 
        {
            texture_use,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        m_characters.insert(std::pair<char, Character>(c, character));
    }

    // Back to default
   glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

Font::~Font()
{
}

std::string Font::GetFilepath()
{
    return m_filepath;
}

UI::UI(Renderer* renderer, ResourceHandler* resource_handler)
    : m_renderer(renderer), m_rh(resource_handler)
{
}

UI::~UI()
{
    delete(m_renderer);
}

void UI::Init()
{
    m_rh->AddResource(resource_name, 600, 600);
    m_rh->AddShader(resource_name, 1, "engine/utils/ui/shaders/vert_ui.shader", "engine/utils/ui/shaders/frag_ui.shader");
    m_rh->BindResource(resource_name, 1);
    m_rh->SetUniformMat4f(resource_name, 1, "u_MVP", m_projection);
}

std::string UI::GetResourceID()
{
    return resource_name;
}

void UI::RenderText(Font& font, const std::string& text, float x, float y, Color text_color, float scale, float ln_width, float ln_height)
{
    m_rh->BindResource(resource_name, 1);
    m_rh->SetUniformMat4f(resource_name, 1, "u_MVP", m_projection);
        
    float currentX = x;
    float currentY = y;
    float lineHeight = ((font.m_font_size/24) * scale * 20.0f) + (scale * ln_height * 10.0f);

    for (auto c : text)
    {
        if (c == '\n')
        {
            currentX = x;
            currentY -= lineHeight;
            continue;
        }

        Character ch = font.m_characters[c];

        float xpos = currentX + ch.Bearing.x * scale;
        float ypos = currentY - (ch.Size.y - ch.Bearing.y) * scale;
        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        // Render glyph texture over quad
        Rect fuck(Position{ xpos,ypos,w,h }, text_color, ch.texture_use);
        fuck.Add(*m_renderer);

        // Move to the next character position
        currentX += ((ch.Advance >> 6) * scale) + ln_width;
    }

    m_renderer->Draw();
}
