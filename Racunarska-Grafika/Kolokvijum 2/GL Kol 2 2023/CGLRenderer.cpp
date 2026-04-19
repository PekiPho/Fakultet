#include "pch.h"
#include "CGLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#include "DImage.h"

#define TO_DEG 180.0f / 3.14


CGLRenderer::CGLRenderer(void){}

CGLRenderer::~CGLRenderer(void)
{
}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);

	if (nPixelFormat == 0) return false;

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);

	if (!bResult) return false;

	m_hrc = wglCreateContext(pDC->m_hDC);

	if (!m_hrc) return false;

	return true;
}

void CGLRenderer::PrepareScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	
	lampa = LoadTexture("lamp.jpg");
	pozadina[0] = LoadTexture("front.jpg");
	pozadina[1] = LoadTexture("back.jpg");
	pozadina[2] = LoadTexture("left.jpg");
	pozadina[3] = LoadTexture("right.jpg");
	pozadina[4] = LoadTexture("top.jpg");
	pozadina[5] = LoadTexture("bot.jpg");

	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Reshape(CDC* pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, (double)w / (double)h, 0.1, 2000);
	glMatrixMode(GL_MODELVIEW);


	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	UpdateCamera();

	glColor3f(1, 1, 1);

	glPushMatrix();

	//glTranslatef(0, -50, 0);
	DrawAxes();
	glColor3f(1, 1, 1);

	DrawLamp();

	glTranslatef(0, 50, 0);
	DrawEnvCube(200);


	glPopMatrix();

	glFlush();
	SwapBuffers(pDC->m_hDC);

	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	
	glDeleteTextures(1, &lampa);
	glDeleteTextures(6, pozadina);

	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

UINT CGLRenderer::LoadTexture(char* filename)
{
	UINT idTeksture;
	DImage slika;

	slika.Load(CString(filename));

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, &idTeksture);

	glBindTexture(GL_TEXTURE_2D, idTeksture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, slika.Width(), slika.Height(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, slika.GetDIBBits());

	return idTeksture;
}

void CGLRenderer::DrawAxes()
{ 
	glLineWidth(4);
	
	glBegin(GL_LINES);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(50, 0, 0);

	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 50, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 50);

	glEnd();
}

void CGLRenderer::DrawEnvCube(double a)
{
	double h = a / 2;

	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);


	//front
	glBindTexture(GL_TEXTURE_2D, pozadina[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-h,h,-h);
	glTexCoord2f(0, 1); glVertex3f(-h,-h,-h);
	glTexCoord2f(1, 1); glVertex3f(h,-h,-h);
	glTexCoord2f(1, 0); glVertex3f(h,h,-h);
	glEnd();


	//left
	glBindTexture(GL_TEXTURE_2D, pozadina[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-h,h,h);
	glTexCoord2f(0, 1); glVertex3f(-h,-h,h);
	glTexCoord2f(1, 1); glVertex3f(-h,-h,-h);
	glTexCoord2f(1, 0); glVertex3f(-h,h,-h);
	glEnd();

	//right
	glBindTexture(GL_TEXTURE_2D, pozadina[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(h,h,-h);
	glTexCoord2f(0, 1); glVertex3f(h,-h,-h);
	glTexCoord2f(1, 1); glVertex3f(h,-h,h);
	glTexCoord2f(1, 0); glVertex3f(h,h,h);
	glEnd();

	//back
	glBindTexture(GL_TEXTURE_2D, pozadina[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(h,h,h);
	glTexCoord2f(0, 1); glVertex3f(h,-h,h);
	glTexCoord2f(1, 1); glVertex3f(-h,-h,h);
	glTexCoord2f(1, 0); glVertex3f(-h,h,h);
	glEnd();

	//top
	glBindTexture(GL_TEXTURE_2D, pozadina[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-h,h,h);
	glTexCoord2f(0, 1); glVertex3f(-h,h,-h);
	glTexCoord2f(1, 1); glVertex3f(h,h,-h);
	glTexCoord2f(1, 0); glVertex3f(h,h,h);
	glEnd();

	//bottom
	glBindTexture(GL_TEXTURE_2D, pozadina[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-h,-h,-h);
	glTexCoord2f(0, 1); glVertex3f(-h,-h,h);
	glTexCoord2f(1, 1); glVertex3f(h,-h,h);
	glTexCoord2f(1, 0); glVertex3f(h,-h,-h);
	glEnd();
}

void CGLRenderer::DrawCylinder(double r1, double r2, double h, int nSeg, int texMode, bool bIsOpen)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, lampa);
	glColor3f(1, 1, 1);
	

	float gore, dole;
	if (texMode == 0) {
		dole = 0.0f;
		gore = 0.5f;
	}
	else {
		dole = 0.5f;
		gore = 1.0f;
	}

	double dAng = 2 * 3.14 / nSeg;

	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= nSeg; i++) {
		double ang = i * dAng;

		double x = cos(ang);
		double z = sin(ang);
		float u = (float)i / (float)nSeg;

		glTexCoord2f(u, gore);
		glVertex3f(r2 * x, h, r2 * z);

		glTexCoord2f(u, dole);
		glVertex3f(r1 * x, 0, r1 * z);
	}
	glEnd();

	if (!bIsOpen) {
		glBegin(GL_TRIANGLE_FAN);

		glTexCoord2f(0.5f, 0.25f);
		glVertex3f(0, 0, 0);

		for (int i = 0; i <= nSeg; i++) {
			double ang = i * dAng;
			double x = cos(ang);
			double z = sin(ang);

			float u = 0.5f + 0.5f * x;
			float v = 0.25f + 0.25f * z;

			glTexCoord2f(u, v);
			glVertex3f(r1 * x, 0, r1 * z);
		}
		glEnd();


		glTexCoord2f(0.5f, 0.25f);
		glVertex3f(0, h, 0);

		for (int i = 0; i <= nSeg; i++) {
			double ang = i * dAng;
			double x = cos(ang);
			double z = sin(ang);

			float u = 0.5f + 0.5f * x;
			float v = 0.25f + 0.25f * z;

			glTexCoord2f(u, v);
			glVertex3f(r1 * x, h, r1 * z);
		}
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
}

void CGLRenderer::DrawLampBase()
{
	DrawCylinder(8, 7, 2, 10, 1, false);
}

void CGLRenderer::DrawLampArm()
{
	glPushMatrix();

	DrawCylinder(3, 3, 2, 10, 1, false);
	glRotated(90, 1, 0, 0);
	glTranslated(0, 3, -1);
	DrawCylinder(1, 1, 15, 10, 1, false);

	glPopMatrix();
}

void CGLRenderer::DrawLampHead()
{
	glPushMatrix();

	DrawCylinder(2, 2, 2, 10, 1, false);
	glTranslatef(-1.5, 0, 0);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, -2.5, -1);
	DrawCylinder(3, 3, 5, 10, 1, false);

	glTranslated(0, 5, 0);
	DrawCylinder(3, 6, 5, 10, 0, true);

	glTranslated(0, -6, 0);
	DrawCylinder(2, 3, 1, 10, 1, false);

	glPopMatrix();
}

void CGLRenderer::DrawLamp()
{
	glPushMatrix();

	DrawLampBase();
	glRotated(90, 1, 0, 0);
	glRotated(ang1, 0, 1, 0);
	DrawLampArm();

	glTranslated(0, 0, 18);
	glRotated(ang2, 0, 1, 0);
	DrawLampArm();

	glTranslated(0, 0, 18);
	glRotatef(ang3, 0, 1, 0);
	DrawLampHead();

	glPopMatrix();

	glPopMatrix();
}

void CGLRenderer::UpdateCamera()
{
	glTranslatef(0, 0, -cameraDist);
	glRotatef(beta*TO_DEG, 1, 0, 0);
	glRotatef(alpha*TO_DEG, 0, 1, 0);
}
