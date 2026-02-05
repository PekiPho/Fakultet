#include "pch.h"
#include "CMaterial.h"

CMaterial::CMaterial()
{
	mvAmbient[0] = 0.2; mvAmbient[1] = 0.2;
	mvAmbient[2] = 0.2; mvAmbient[3] = 1.0;

	mvDiffuse[0] = 0.2; mvDiffuse[1] = 0.8;
	mvDiffuse[2] = 0.2; mvDiffuse[3] = 1.0;

	mvSpecular[0] = 1.0; mvSpecular[1] = 1.0;
	mvSpecular[2] = 1.0; mvSpecular[3] = 1.0;

	mvEmission[0] = 0.0; mvEmission[1] = 0.0;
	mvEmission[2] = 0.0; mvEmission[3] = 1.0;

	mfShininess = 64.0;
}

void CMaterial::SetFace(GLenum face)
{
	glMaterialfv(face, GL_AMBIENT, mvAmbient);
	glMaterialfv(face, GL_DIFFUSE, mvDiffuse);
	glMaterialfv(face, GL_SPECULAR, mvSpecular);
	glMaterialfv(face, GL_SPECULAR, mvSpecular);
	glMaterialfv(face, GL_EMISSION, mvEmission);
	glMaterialf(face, GL_SHININESS, mfShininess);
}

void CMaterial::SetAmbient(float r, float g, float b, float a)
{
	mvAmbient[0] = r;
	mvAmbient[1] = g;
	mvAmbient[2] = b;
	mvAmbient[3] = a;
}

void CMaterial::SetDiffuse(float r, float g, float b, float a)
{
	mvDiffuse[0] = r;
	mvDiffuse[1] = g;
	mvDiffuse[2] = b;
	mvDiffuse[3] = a;
}

void CMaterial::SetSpecular(float r, float g, float b, float a)
{
	mvSpecular[0] = r;
	mvSpecular[1] = g;
	mvSpecular[2] = b;
	mvSpecular[3] = a;
}

void CMaterial::SetEmission(float r, float g, float b, float a)
{
	mvEmission[0] = r;
	mvEmission[1] = g;
	mvEmission[2] = b;
	mvEmission[3] = a;
}

void CMaterial::SetShininess(float s)
{
	if (s < 0) mfShininess = 0;
	else if (s > 128) mfShininess = 128;
	else mfShininess = s;
}
