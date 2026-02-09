#include "pch.h"
#include "CTexture.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#pragma comment(lib, "GL\\glut32.lib")
#include "DImage.h"

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
}

void CTexture::LoadFileForm(CString fileName)
{
	DImage img;
	img.Load(fileName);
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());
}

void CTexture::Select()
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void CTexture::Relase()
{
	glDeleteTextures(1, &m_ID);
}

void CTexture::PrepareTexture(bool lightEnabled)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	if (lightEnabled) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	else {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
}

void CTexture::BindDefault()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
