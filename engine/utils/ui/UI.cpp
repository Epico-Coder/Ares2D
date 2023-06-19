#include "UI.h"
#include <iostream>

namespace Ares2D
{
    UI::UI()
    {
    }

    UI::~UI()
    {
    }

    /*-------------------------- Public Functions --------------------------*/

    UI& UI::Instance()
    {
        static UI instance;
        return instance;
    }

    void UI::Init()
    {
        Instance().i_Init();
    }

    std::string UI::GetResourceID()
    {
        return Instance().i_GetResourceID();
    }

    void UI::RenderText(Font& font, const std::string& text, float x, float y, Ares2D::Color4 text_color, float scale, float ln_width, float ln_height)
    {
        Instance().i_RenderText(font, text, x, y, text_color, scale, ln_width, ln_height);
    }

    void UI::RenderButton(Button& button)
    {
        Instance().i_RenderButton(button);
    }

    /*-------------------------- Internal Functions --------------------------*/

    void UI::i_Init()
    {
        Ares2D::Resource::AddResource(resource_name, 1000, 1000);
        Ares2D::Resource::AddShader(resource_name, 1, "engine/utils/ui/shaders/vert_ui.shader", "engine/utils/ui/shaders/frag_ui.shader");
        Ares2D::Resource::BindResource(resource_name, 1);
        //Ares2D::Resource::SetUniformMat4f(resource_name, 1, "u_MVP", m_projection);
    }

    std::string UI::i_GetResourceID()
    {
        return resource_name;
    }

    void UI::i_RenderText(Font& font, const std::string& text, float x, float y, Ares2D::Color4 text_color, float scale, float ln_width, float ln_height)
    {
        Ares2D::Resource::BindResource(resource_name, 1);
        Ares2D::Resource::SetUniformMat4f(resource_name, 1, "u_MVP", m_projection);

        float currentX = x;
        float currentY = y;
        float lineHeight = ((font.m_font_size / 24) * scale * 20.0f) + (scale * ln_height * 10.0f);

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
            Rect rect(Ares2D::Float4{ xpos,ypos,w,h }, text_color, ch.texture_use);
            Ares2D::Renderer::AddRenderable(&rect);

            // Move to the next character position
            currentX += ((ch.Advance >> 6) * scale) + ln_width;
        }

        Ares2D::Renderer::Draw();
    }

    void UI::i_RenderButton(Button& button)
    {
        Ares2D::Renderer::AddRenderable(&button.m_rect);
        RenderText(button.font, button.text, button.position.x, button.position.y, button.text_color);
    }


    /*-------------------------- Child 1 Functions --------------------------*/

    UI::Font::Font(const std::string& filepath, int size)
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

            TextureUse texture_use = Ares2D::Resource::AddTexture(resource_name, GL_ALPHA, GL_ALPHA, face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer);

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

    UI::Font::~Font()
    {
    }

    std::string UI::Font::GetFilepath()
    {
        return m_filepath;
    }

    /*-------------------------- Child 2 Functions --------------------------*/

    UI::Button::Button(Font& font, const std::string& text, const Ares2D::Float4& position, const Ares2D::Color4& text_color, const Ares2D::Color4& button_color, std::function<void()> on_hover, std::function<void()> on_click)
        : font(font), text(text), position(position), text_color(text_color), button_color(button_color),
        on_hover(on_hover), on_click(on_click), m_rect(Rect(position, button_color))
    {
    }

    void UI::Button::default_button_event()
    {
    }
};