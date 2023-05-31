#pragma once

#include "engine/rendering/Renderable.h"
#include "engine/rendering/Renderer.h"

#include "engine/resources/shaders/Shader.h"
#include "engine/resources/textures/Texture.h"

#include "engine/resources/resource/Resource.h"

#include "engine/rendering/geometry/Rect.h"

#include "engine/utils/math/Math.h"
#include "engine/utils/color/Color.h"

#include "dependancies/glm/gtc/matrix_transform.hpp"

#include <functional>

const std::string resource_name = "__ui";

namespace Ares2D
{
    class UI : public Renderable
    {
    public:
        static struct Character
        {
            TextureUse texture_use;  // Texture
            glm::ivec2   Size;       // Size of glyph
            glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
            unsigned int Advance;    // Offset to advance to next glyph
        };
    public:
        static class Font
        {
            friend class UI;
        public:
            Font(const std::string& filepath, int size);
            ~Font();

            std::string GetFilepath();
        protected:
            std::map<char, Character> m_characters;

            int m_font_size;
            std::string m_filepath;
        };
    public:
        static class Button
        {
            friend class UI;
        public:
            Button(Font& font, const std::string& text, const Position& position, const Color& text_color, const Color& button_color,
                std::function<void()> on_hover = default_button_event, std::function<void()> on_click = default_button_event);
        protected:
            Rect m_rect;
        private:
            Font& font;
            std::string text;
            Position position;
            Color text_color;
            Color button_color;
            std::function<void()> on_hover;
            std::function<void()> on_click;

            static void default_button_event();

        };
    public:
        static UI& Instance();

        UI(UI const&) = delete;
        void operator=(UI const&) = delete;

        static void Init();

        static std::string GetResourceID();

        static void RenderText(Font& font, const std::string& text, float x, float y, Color text_color, float scale = 1.0f, float ln_width = 1, float ln_height = 1);
        static void RenderButton(Button& button);
    private:
        UI();
        ~UI();
    private:
        void i_Init();

        std::string i_GetResourceID();

        void i_RenderText(Font& font, const std::string& text, float x, float y, Color text_color, float scale = 1.0f, float ln_width = 1, float ln_height = 1);
        void i_RenderButton(Button& button);
    private:
        Shader m_shader;
        glm::mat4 m_projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    };
};