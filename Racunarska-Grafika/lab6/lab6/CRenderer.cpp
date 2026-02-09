#include "pch.h"
#include "CRenderer.h"

#include "GL\GL.h"
#include "GL\GLU.h"

CRenderer::CRenderer(void)
{
	m_hrc = NULL;
	this->viewR = 100;

	this->viewAngleXY = 30;
	this->viewAngleXZ = 45;

	this->eyex = 0; this->eyey = 0; this->eyez = 0;
	this->centerx = 0; this->centery = 0; this->centerz = 0;
	this->upx = 0; this->upy = 1; this->upz = 0;
}

CRenderer::~CRenderer(void)
{
}

bool CRenderer::CreateGLContext(CDC* pDC)
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

void CRenderer::PrepareScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	glClearColor(0.8, 0.8, 0.8, 0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);

	CTexture::PrepareTexture(false);
	groundTex.LoadFileForm(CString("download.jfif"));
	truckTex.LoadFileForm(CString("download (1).png"));

	wglMakeCurrent(NULL, NULL);
}

void CRenderer::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez,
		centerx, centery, centerz,
		upx, upy, upz);

	DrawAxis();
	DrawTruck();
	glTranslatef(0, -6, 0);
	DrawGround();

	glFlush();
	SwapBuffers(pDC->m_hDC);
	
	wglMakeCurrent(NULL, NULL);
}


void CRenderer::Reshape(CDC* pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, (double)w / (double)h, 1, 200);

	glMatrixMode(GL_MODELVIEW);
	wglMakeCurrent(NULL, NULL);
}

void CRenderer::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	truckTex.Relase();
	groundTex.Relase();
	wglMakeCurrent(NULL, NULL);
	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}



void CRenderer::DrawGround()
{
	CTexture tex;
	float x = -768 / 8;
	float z = -768 / 8;
	int step = 256 / 8;

	groundTex.Select();


	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);

	glTexCoord2f(3, 0);
	glVertex3f(x, 0, z);
	glTexCoord2f(3, 3);
	glVertex3f(-x, 0, z);
	glTexCoord2f(0, 3);
	glVertex3f(-x, 0, -z);
	glTexCoord2f(0, 0);
	glVertex3f(x, 0, -z);

	glEnd();
	CTexture::BindDefault();
}

void CRenderer::DrawAxis()
{
	CTexture::BindDefault();
	float size = 64;
	glLineWidth(1.0);

	glBegin(GL_LINES);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(size, 0.0, 0.0);


	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, size, 0.0);


	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, size);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
}


void CRenderer::DrawSide()
{
	float step = 4;
	const float texStep = 0.0625;
	glColor3f(1, 1, 1);

	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);

	glTexCoord2f(0, 6 * texStep); glVertex3f(0, 0, 0);
	glTexCoord2f(0, 2 * texStep); glVertex3f(0, 4 * step, 0);
	glTexCoord2f(texStep, texStep); glVertex3f(step, 5 * step, 0);
	glTexCoord2f(texStep, 6 * texStep); glVertex3f(step, 0, 0);

	glTexCoord2f(texStep, 5 * texStep); glVertex3f(step, step, 0);
	glTexCoord2f(texStep, texStep); glVertex3f(step, 5 * step, 0);
	glTexCoord2f(2 * texStep, 0); glVertex3f(2 * step, 6 * step, 0);
	glTexCoord2f(2 * texStep, 4 * texStep); glVertex3f(2 * step, 2 * step, 0);

	glTexCoord2f(2 * texStep, 4 * texStep); glVertex3f(2 * step, 2 * step, 0);
	glTexCoord2f(2 * texStep, 0); glVertex3f(2 * step, 6 * step, 0);
	glTexCoord2f(3 * texStep, 0); glVertex3f(3 * step, 6 * step, 0);
	glTexCoord2f(3 * texStep, 4 * texStep); glVertex3f(3 * step, 2 * step, 0);

	glTexCoord2f(3 * texStep, 4 * texStep); glVertex3f(3 * step, 2 * step, 0);
	glTexCoord2f(3 * texStep, 0); glVertex3f(3 * step, 6 * step, 0);
	glTexCoord2f(4 * texStep, 0); glVertex3f(4 * step, 6 * step, 0);
	glTexCoord2f(4 * texStep, 5 * texStep); glVertex3f(4 * step, 1 * step, 0);

	glTexCoord2f(4 * texStep, 7 * texStep);
	glVertex3f(4 * step, 0, 0);
	glTexCoord2f(4 * texStep, 4 * texStep);
	glVertex3f(4 * step, 3 * step, 0);
	glTexCoord2f(5 * texStep, 4 * texStep);
	glVertex3f(5 * step, 3 * step, 0);
	glTexCoord2f(5 * texStep, 7 * texStep);
	glVertex3f(5 * step, 0, 0);

	glTexCoord2f(5 * texStep, 6 * texStep);
	glVertex3f(5 * step, 1 * step, 0);
	glTexCoord2f(5 * texStep, 4 * texStep);
	glVertex3f(5 * step, 3 * step, 0);
	glTexCoord2f(6 * texStep, 4 * texStep);
	glVertex3f(6 * step, 3 * step, 0);
	glTexCoord2f(6 * texStep, 5 * texStep);
	glVertex3f(6 * step, 2 * step, 0);

	glTexCoord2f(6 * texStep, 5 * texStep); 
	glVertex3f(6 * step, 2 * step, 0);
	glTexCoord2f(6 * texStep, 4 * texStep); 
	glVertex3f(6 * step, 3 * step, 0);
	glTexCoord2f(7 * texStep, 4 * texStep); 
	glVertex3f(7 * step, 3 * step, 0);
	glTexCoord2f(7 * texStep, 5 * texStep); 
	glVertex3f(7 * step, 2 * step, 0);

	glTexCoord2f(7 * texStep, 5 * texStep);
	glVertex3f(7 * step, 2 * step, 0);
	glTexCoord2f(7 * texStep, 4 * texStep);
	glVertex3f(7 * step, 3 * step, 0);
	glTexCoord2f(8 * texStep, 4 * texStep);
	glVertex3f(8 * step, 3 * step, 0);
	glTexCoord2f(8 * texStep, 6 * texStep);
	glVertex3f(8 * step, 1 * step, 0);

	glTexCoord2f(8 * texStep, 7 * texStep);
	glVertex3f(8 * step, 0, 0);
	glTexCoord2f(8 * texStep, 4 * texStep);
	glVertex3f(8 * step, 3 * step, 0);
	glTexCoord2f(13 * texStep, 4 * texStep);
	glVertex3f(13 * step, 3 * step, 0);
	glTexCoord2f(13 * texStep, 7 * texStep);
	glVertex3f(13 * step, 0, 0);

	glEnd();
}

void CRenderer::DrawWheelSide()
{
	const float RAD = 3.14 / 180;
	const float step = RAD * (360. / 16.);
	const float texStep = 0.0625;
	const float radius = 6;
	const float texRadius = 0.0625 * 1.5;

	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 0, 1);
	glTexCoord2f(10 * texStep, 1.5 * texStep);
	glVertex3f(0, 0, 0);
	for (int i = 0; i <= 16; i++) {
		glTexCoord2f(10 * texStep + texRadius * cos(step * i), 1.5 * texStep + texRadius * sin(step * i));
		glVertex3f(radius * cos(step * i), radius * sin(step * i), 0);
	}
	glEnd();
}

void CRenderer::DrawWheel()
{
	const float RAD = 3.14 / 180;
	const float step = RAD * (360. / 16.);
	const float radius = 6;

	glPushMatrix();
	glTranslatef(0, 0, -2);
	DrawWheelSide();
	glTranslatef(0, 0, 4);
	DrawWheelSide();
	glTranslatef(0, 0, -2);
	glBegin(GL_QUADS);
	for (int i = 0; i <= 16; i++) {
		glVertex3f(radius * cos(step * i), radius * sin(step * i), 2);
		glVertex3f(radius * cos(step * i), radius * sin(step * i), -2);
		glVertex3f(radius * cos(step * (i + 1)), radius * sin(step * (i + 1)), -2);
		glVertex3f(radius * cos(step * (i + 1)), radius * sin(step * (i + 1)), 2);
	}
	glEnd();
	glPopMatrix();

}

void CRenderer::DrawTruck()
{
	float step = 4;
	float width = 16;


	truckTex.Select();

	glPushMatrix();
	glTranslatef(-6.5 * step, 0, 0);

	glTranslatef(0, 0, -width);
	DrawSide();
	glTranslatef(0, 0, 2 * width);
	DrawSide();
	glTranslatef(0, 0, -width);


	CTexture::BindDefault();
	glBegin(GL_QUADS);
	{
		glColor3f(0.29, 0.29, 0.18);
		glVertex3f(0, 0, width);
		glVertex3f(0, 0, -width);
		glVertex3f(0, 4 * step, -width);
		glVertex3f(0, 4 * step, width);

		glColor3f(97 / 255., 97 / 255., 61 / 255.);
		glVertex3f(0, 4 * step, -width);
		glVertex3f(0, 4 * step, width);
		glVertex3f(2 * step, 6 * step, width);
		glVertex3f(2 * step, 6 * step, -width);

		glColor3f(136. / 255., 136. / 255., 86. / 255.);
		glVertex3f(2 * step, 6 * step, width);
		glVertex3f(2 * step, 6 * step, -width);
		glVertex3f(4 * step, 6 * step, -width);
		glVertex3f(4 * step, 6 * step, width);

		glColor3f(97 / 255., 97 / 255., 61 / 255.);
		glVertex3f(4 * step, 6 * step, width);
		glVertex3f(4 * step, 6 * step, -width);
		glVertex3f(4 * step, 3 * step, -width);
		glVertex3f(4 * step, 3 * step, width);

		glColor3f(136. / 255., 136. / 255., 86. / 255.);
		glVertex3f(4 * step, 3 * step, -width);
		glVertex3f(4 * step, 3 * step, width);
		glVertex3f(13 * step, 3 * step, width);
		glVertex3f(13 * step, 3 * step, -width);

		glColor3f(97 / 255., 97 / 255., 61 / 255.);
		glVertex3f(13 * step, 3 * step, width);
		glVertex3f(13 * step, 3 * step, -width);
		glVertex3f(13 * step, 0, -width);
		glVertex3f(13 * step, 0, width);

		glColor3f(0.29, 0.29, 0.18);
		glVertex3f(13 * step, 0, -width);
		glVertex3f(13 * step, 0, width);
		glVertex3f(8 * step, 0, width);
		glVertex3f(8 * step, 0, -width);

		glVertex3f(8 * step, 0, -width);
		glVertex3f(8 * step, 0, width);
		glVertex3f(8 * step, 1 * step, width);
		glVertex3f(8 * step, 1 * step, -width);

		glColor3f(97 / 255., 97 / 255., 61 / 255.);
		glVertex3f(8 * step, 1 * step, -width);
		glVertex3f(8 * step, 1 * step, width);
		glVertex3f(7 * step, 2 * step, width);
		glVertex3f(7 * step, 2 * step, -width);

		glColor3f(136. / 255., 136. / 255., 86. / 255.);
		glVertex3f(7 * step, 2 * step, -width);
		glVertex3f(7 * step, 2 * step, width);
		glVertex3f(6 * step, 2 * step, width);
		glVertex3f(6 * step, 2 * step, -width);

		glColor3f(97 / 255., 97 / 255., 61 / 255.);
		glVertex3f(6 * step, 2 * step, -width);
		glVertex3f(6 * step, 2 * step, width);
		glVertex3f(5 * step, 1 * step, width);
		glVertex3f(5 * step, 1 * step, -width);

		glColor3f(136. / 255., 136. / 255., 86. / 255.);
		glVertex3f(5 * step, 1 * step, -width);
		glVertex3f(5 * step, 1 * step, width);
		glVertex3f(5 * step, 0, width);
		glVertex3f(5 * step, 0, -width);

		glColor3f(97 / 255., 97 / 255., 61 / 255.);
		glVertex3f(5 * step, 0, -width);
		glVertex3f(5 * step, 0, width);
		glVertex3f(4 * step, 0, width);
		glVertex3f(4 * step, 0, -width);

		glColor3f(136. / 255., 136. / 255., 86. / 255.);
		glVertex3f(4 * step, 0, -width);
		glVertex3f(4 * step, 0, width);
		glVertex3f(4 * step, 1 * step, width);
		glVertex3f(4 * step, 1 * step, -width);

		glColor3f(97 / 255., 97 / 255., 61 / 255.);
		glVertex3f(4 * step, 1 * step, -width);
		glVertex3f(4 * step, 1 * step, width);
		glVertex3f(3 * step, 2 * step, width);
		glVertex3f(3 * step, 2 * step, -width);

		glColor3f(136. / 255., 136. / 255., 86. / 255.);
		glVertex3f(3 * step, 2 * step, -width);
		glVertex3f(3 * step, 2 * step, width);
		glVertex3f(2 * step, 2 * step, width);
		glVertex3f(2 * step, 2 * step, -width);

		glColor3f(97 / 255., 97 / 255., 61 / 255.);
		glVertex3f(2 * step, 2 * step, -width);
		glVertex3f(2 * step, 2 * step, width);
		glVertex3f(1 * step, 1 * step, width);
		glVertex3f(1 * step, 1 * step, -width);

		glColor3f(136. / 255., 136. / 255., 86. / 255.);
		glVertex3f(1 * step, 1 * step, -width);
		glVertex3f(1 * step, 1 * step, width);
		glVertex3f(1 * step, 0, width);
		glVertex3f(1 * step, 0, -width);

		glColor3f(97 / 255., 97 / 255., 61 / 255.);
		glVertex3f(1 * step, 0, -width);
		glVertex3f(1 * step, 0, width);
		glVertex3f(0, 0, width);
		glVertex3f(0, 0, -width);

	}
	glEnd();
	truckTex.Select();

	glPushMatrix();
	glTranslatef(2.5 * step, 0, -width + 2);
	DrawWheel();
	glTranslatef(4 * step, 0, 0);
	DrawWheel();
	glPopMatrix();

	glTranslatef(2.5 * step, 0, width - 2);
	DrawWheel();
	glTranslatef(4 * step, 0, 0);
	DrawWheel();

	glPopMatrix();

	CTexture::BindDefault();


	//glColor3f(1.0f, 1.0f, 1.0f);
	truckTex.Select();

	glPushMatrix();

	glTranslatef(8, 4 * 4.5, 0);
	glScalef(1.5, 0.5, 1);
	glRotatef(180, 0, 1, 0);

	//glDisable(GL_TEXTURE_2D);
	//glColor3f(1, 1, 1);
	//glColor3f(140 / 255.0f, 140 / 255.0f, 25 / 255.0f);
	DrawSphere(12);
	//glEnable(GL_TEXTURE_2D);

	glPopMatrix();

	CTexture::BindDefault();

}

void CRenderer::DrawSphere(float radius)
{
	float texStep = 0.0625;

	const float RAD = 3.14 / 180;
	float redovi = (180 * RAD) / 8;
	float kolone = (360 * RAD) / 16;

	int k1 = 16;

	//glColor3f(1, 1, 1);


	glBegin(GL_QUADS);
	
	for (int i = -4; i < 4; i++)
	{
		for (int j = 0; j <= 16; j++)
		{
			glNormal3f(cos(i * redovi) * cos(j * kolone), sin(i * redovi), cos(i * redovi) * sin(j * kolone));
			glTexCoord2f(16 - j * texStep, k1 * texStep);
			glVertex3f(radius * cos(i * redovi) * cos(j * kolone), radius * sin(i * redovi), radius * cos(i * redovi) * sin(j * kolone));

			glNormal3f(cos((i + 1) * redovi) * cos(j * kolone), sin((i + 1) * redovi), cos((i + 1) * redovi) * sin(j * kolone));
			glTexCoord2f(16 - j * texStep, (k1 - 1) * texStep);
			glVertex3f(radius * cos((i + 1) * redovi) * cos(j * kolone), radius * sin((i + 1) * redovi), radius * cos((i + 1) * redovi) * sin(j * kolone));

			glNormal3f(cos((i + 1) * redovi) * cos((j + 1) * kolone), sin((i + 1) * redovi), cos((i + 1) * redovi) * sin((j + 1) * kolone));
			glTexCoord2f(16 - (j + 1) * texStep, (k1 - 1) * texStep);
			glVertex3f(radius * cos((i + 1) * redovi) * cos((j + 1) * kolone), radius * sin((i + 1) * redovi), radius * cos((i + 1) * redovi) * sin((j + 1) * kolone));

			glNormal3f(cos(i * redovi) * cos((j + 1) * kolone), sin(i * redovi), cos(i * redovi) * sin((j + 1) * kolone));
			glTexCoord2f(16 - (j + 1) * texStep, k1 * texStep);
			glVertex3f(radius * cos(i * redovi) * cos((j + 1) * kolone), radius * sin(i * redovi), radius * cos(i * redovi) * sin((j + 1) * kolone));
		}
		k1 -= 1;
	}

	glEnd();

}


void CRenderer::RotateCamera(double dXY, double dXZ)
{
	this->viewAngleXY += dXY;
	this->viewAngleXZ += dXZ;

	viewAngleXY = min(90, viewAngleXY);
	viewAngleXY = max(-90, viewAngleXY);

	this->RecalculateCamera();
}

void CRenderer::RecalculateCamera()
{
	double dWXY = this->viewAngleXY * 3.141592 / 180;
	double dWXZ = this->viewAngleXZ * 3.141592 / 180;

	this->eyex = this->viewR * cos(dWXY) * cos(dWXZ);
	this->eyey = 0 + this->viewR * sin(dWXY);
	this->eyez = this->viewR * cos(dWXY) * sin(dWXZ);

	this->upy = signbit(cos(dWXY)) ? -1 : 1;
}


