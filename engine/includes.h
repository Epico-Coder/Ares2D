#include "dependancies/glew/include/GL/glew.h"
#include "dependancies/glfw/include/GLFW/glfw3.h"
#include "dependancies/fmod/inc/fmod.hpp"
#include "dependancies/freetype/include/ft2build.h"
#include FT_FREETYPE_H
#include "dependancies/glm/glm.hpp"
#include "dependancies/imgui/lib/imgui.h"

#include "utils/error/ErrorHandling.h"
#include "utils/color/Color.h"
#include "utils/input/Input.h"
#include "utils/math/Math.h"

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>

#include "engine/rendering/storage/VertexBuffer.h"
#include "engine/rendering/storage/VertexBufferLayout.h"
#include "engine/rendering/storage/VertexArray.h"
#include "engine/rendering/storage/IndexBuffer.h"
#include "engine/rendering/storage/FrameBuffer.h"
#include "engine/rendering/storage/RenderBuffer.h"

