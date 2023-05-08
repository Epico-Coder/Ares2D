#pragma once

#include "engine/rendering/Renderable.h"
#include "engine/rendering/Renderer.h"

#include "engine/resources/shaders/Shader.h"
#include "engine/resources/textures/Texture.h"

#include "engine/rendering/geometry/Rect.h"

#include "engine/utils/math/Math.h"
#include "engine/utils/color/Color.h"

#include "dependancies/glm/gtc/matrix_transform.hpp"

struct Character {
    TextureUse texture_use;  // Texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class Font
{
    friend class UI;
public:
    Font(TextureHandler& texture_handler, const std::string& filepath, int size);
    ~Font();
protected:
    std::map<char, Character> m_characters;
    int m_font_size;
};

class UI : public Renderable
{
public:
    UI(Renderer* renderer);
	~UI();

    void Init();

    void RenderText(Renderer& renderer, Font font, const std::string& text, float x, float y, Color text_color, float scale=1.0f, float ln_width=1, float ln_height=1);

private:
    Renderer* m_renderer;

    Shader m_shader;
    glm::mat4 m_projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
};

