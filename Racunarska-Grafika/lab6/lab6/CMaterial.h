#pragma once
#include "GL/GL.h"
#include "GL/GLU.h"

class CMaterial
{
	CMaterial();
	~CMaterial();

	void Select();

	void SetAmbient(float r, float g, float b, float a);
	void SetDiffuse(float r, float g, float b, float a);
	void SetSpecular(float r, float g, float b, float a);
	void SetEmission(float r, float g, float b, float a);
	void SetShininess(float s);

protected:
	float mvAmbient[4];
	float mvDiffuse[4];
	float mvSpecular[4];
	float mvEmission[4];
	float mfShininess;
};

