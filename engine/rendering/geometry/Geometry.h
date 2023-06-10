#pragma once

#include "dependancies/glew/include/GL/glew.h"
#include "engine/utils/color/Color.h"
#include "engine/utils/math/Math.h"
#include "engine/rendering/Renderable.h"

#include <vector>

enum class GEOMETRY_TYPE
{
	POINT,
	LINE,
	TRIANGLE,
	RECT,
	POLYGON,
	CIRCLE
};

class Geometry : public Renderable
{
	friend class Renderer;
public:
	virtual void Translate(float x, float y) {}
	virtual void Scale(float x, float y) {}
	virtual void Rotate(float angle) {}
protected:
private:
	GEOMETRY_TYPE m_type;
};

