#pragma once
#include "GL/GL.h"
#include "GL/GLU.h"

class CMaterial
{
public:
	CMaterial();

	void SetFace(GLenum face = GL_FRONT_AND_BACK);
	void SetAmbient(float r, float g, float b, float a);
	void SetDiffuse(float r, float g, float b, float a);
	void SetSpecular(float r, float g, float b, float a);
	void SetEmission(float r, float g, float b, float a);
	void SetShininess(float s);

private:
	float mvAmbient[4];
	float mvDiffuse[4];
	float mvSpecular[4];
	float mvEmission[4];
	float mfShininess;
};

