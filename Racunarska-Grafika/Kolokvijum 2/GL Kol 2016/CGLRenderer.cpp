#include "pch.h"
#include "CGLRenderer.h"
#include "GL/gl.h"
#include "GL/GLU.h"
#include "GL/glaux.h"
#include "GL/glut.h"

#include <math.h>

#define TO_RAD 3.14 / 180.0f
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

    return true; ;
}

void CGLRenderer::PrepareScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);
    
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);

    brick = LoadTexture("brick.png");
    bg = LoadTexture("env.png");


    wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Reshape(CDC* pDC, int w, int h)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);
    
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, (double)w / (double)h, 0.1, 2000);
    glMatrixMode(GL_MODELVIEW);

    wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);
    

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    UpdateCamera();

    glEnable(GL_LIGHTING);

    GLfloat lightpos[] = { 1.0f,1.0f,0.0f,0.0f };
    GLfloat lightWhite[] = { 1.0f,1.0f,1.0f,1.0f };
    GLfloat lightAmbient[] = { 0.3f,0.3f,0.3f,1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightWhite);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightWhite);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glEnable(GL_LIGHT0);

    GLfloat matWhite[] = { 1.0f,1.0f,1.0f,1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matWhite);
    glMaterialfv(GL_FRONT, GL_AMBIENT, matWhite);

    glColor3f(1, 1, 1);

    glTranslated(0, -10, 0);

    DrawTube(2.5, 3.5, 10, 32);
    glTranslated(0, 10, 0);


    DrawCone(3.8, 2, 32);

    glPushMatrix();

    glRotatef(90, 1, 0, 0);
    glTranslatef(0, 3.8, 0);
    glRotatef(ang, 0, 1, 0);

    for (int i = 0; i < 4; i++) {
        glPushMatrix();

        glRotatef(i * 90, 0, 1, 0);
        glRotatef(90, 1, 0, 0);
        DrawPaddle(8, 1.5);

        glPopMatrix();
    }

    glPopMatrix();

    glDisable(GL_LIGHTING);
    glTranslated(0, 20, 0);

    DrawCube(60);

    glFlush();
    SwapBuffers(pDC->m_hDC);

    wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);

    glDeleteTextures(1, &brick);
    glDeleteTextures(1, &bg);


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
    DImage tekstura;

    tekstura.Load(CString(filename));


    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glGenTextures(1, &idTeksture);

    glBindTexture(GL_TEXTURE_2D, idTeksture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, tekstura.Width(), tekstura.Height(), GL_RGBA, GL_UNSIGNED_BYTE, tekstura.GetDIBBits());

    return idTeksture;
}

void CGLRenderer::DrawCube(double a)
{

    double h = a / 2.0;


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, bg);
    glColor3f(1, 1, 1);


    //front
    glBegin(GL_QUADS);
    glTexCoord2f(1.0 / 4, 0.0); glVertex3f(-h, h, -h);
    glTexCoord2f(1.0 / 4, 1.0 / 3); glVertex3f(-h, -h, -h);
    glTexCoord2f(2.0 / 4, 1.0 / 3); glVertex3f(h, -h, -h);
    glTexCoord2f(2.0 / 4, 0); glVertex3f(h, h, -h);
    glEnd();

    //left
    glBegin(GL_QUADS);
    glTexCoord2f(1.0 / 4, 1.0 / 3);		glVertex3f(-h, -h, -h);
    glTexCoord2f(1.0 / 4, 2.0 / 3);		glVertex3f(-h, -h, h);
    glTexCoord2f(0.0, 2.0 / 3);			glVertex3f(-h, h, h);
    glTexCoord2f(0.0, 1.0 / 3);			glVertex3f(-h, h, -h);
    glEnd();

    //right
    glBegin(GL_QUADS);
    glTexCoord2f(2.0 / 4, 1.0 / 3);		glVertex3f(h, -h, -h);
    glTexCoord2f(2.0 / 4, 2.0 / 3);		glVertex3f(h, -h, h);
    glTexCoord2f(3.0/4, 2.0 / 3);			glVertex3f(h, h, h);
    glTexCoord2f(3.0/4, 1.0 / 3);			glVertex3f(h, h, -h);
    glEnd();

    //back
    glBegin(GL_QUADS);
    glTexCoord2f(1.0 / 4, 2.0 / 3);		glVertex3f(-h, -h, h);
    glTexCoord2f(1.0 / 4, 3.0 / 3);		glVertex3f(-h, h, h);
    glTexCoord2f(2.0 / 4, 3.0 / 3);			glVertex3f(h, h, h);
    glTexCoord2f(2.0 / 4, 2.0 / 3);			 glVertex3f(h, -h, h);
    glEnd();


    //gore
    glBegin(GL_QUADS);
    glTexCoord2f(3.0 / 4, 1.0 / 3);		glVertex3f(h, h, -h);
    glTexCoord2f(3.0 / 4, 2.0 / 3);		glVertex3f(h, h, h);
    glTexCoord2f(4.0 / 4, 2.0 / 3);			glVertex3f(-h, h, h);
    glTexCoord2f(4.0 / 4, 1.0 / 3);			 glVertex3f(-h, h, -h);
    glEnd();


    //dole
    glBegin(GL_QUADS);
    glTexCoord2f(1.0 / 4, 1.0 / 3);		glVertex3f(-h, -h, -h);
    glTexCoord2f(1.0 / 4, 2.0 / 3);		glVertex3f(-h, -h, h);
    glTexCoord2f(2.0 / 4, 2.0 / 3);			glVertex3f(h, -h, h);
    glTexCoord2f(2.0 / 4, 1.0 / 3);			 glVertex3f(h, -h, -h);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void CGLRenderer::DrawTube(double r1, double r2, double h, int n)
{
    double step = 3.14159 * 2 / n;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, brick);
    glColor3f(1, 1, 1);

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= n; i++) {
        double ugao = i * step;

        double x1 = r1 * cos(ugao);
        double z1 = r1 * sin(ugao);

        double x2 = r2 * cos(ugao);
        double z2 = r2 * sin(ugao);

        double x = cos(ugao);
        double z = sin(ugao);

        double u = (double)i / n;

        glNormal3f(x, 0, z);

        glTexCoord2f(u, 1.0);
        glVertex3f(x1, h, z1);

        glTexCoord2f(u, 0.0);
        glVertex3f(x2, 0, z2);
    }

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void CGLRenderer::DrawCone(double r, double h, int n)
{

    double step = 3.14159 * 2 / n;

    double nY = r / sqrt(r * r + h * h);
    double nXZ = h / sqrt(r * r + h * h);

    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0, 1, 0);
    glVertex3f(0, h, 0);

    for (int i = 0; i <= n; i++) {
        double ugao = i * step;

        double x = r * cos(ugao);
        double z = r * sin(ugao);

        double nX = cos(ugao) * nXZ;
        double nZ = sin(ugao) * nXZ;

        glNormal3f(nX, nY, nZ);
        glVertex3f(x, 0, z);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, -1, 0);
    glVertex3f(0, 0, 0);

    for (int i = n; i >= 0; i--) {
        double ugao = i * step;
        glVertex3f(r * cos(ugao), 0, r * sin(ugao));
    }
    glEnd();
}

void CGLRenderer::DrawPaddle(double length, double width)
{
    int ew = width / 8.0;

    double x0 = 0;
    double x1 = length / 8.0;
    double x2 = length / 4.0;
    double x3 = length;

    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);

    glVertex3f(x0, 0, 0);
    glVertex3f(x1, 0, 0);
    glVertex3f(x1, ew, 0);
    glVertex3f(x0, ew, 0);

    glVertex3f(x1, 0, 0);
    glVertex3f(x2, 0, 0);
    glVertex3f(x2, width, 0);
    glVertex3f(x1, ew, 0);

    glVertex3f(x2, 0, 0);
    glVertex3f(x3, 0, 0);
    glVertex3f(x3, width, 0);
    glVertex3f(x2, width, 0);

    glEnd();


    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);

    glVertex3f(x0, ew, 0);
    glVertex3f(x1, ew, 0);
    glVertex3f(x1, 0, 0);
    glVertex3f(x0, 0, 0);

    glVertex3f(x1, ew, 0);
    glVertex3f(x2, width, 0);
    glVertex3f(x2, 0, 0);
    glVertex3f(x1, 0, 0);

    glVertex3f(x2, width, 0);
    glVertex3f(x3, width, 0);
    glVertex3f(x3, 0, 0);
    glVertex3f(x2, 0, 0);

    glEnd();
}

void CGLRenderer::UpdateCamera()
{
    glTranslatef(0, 0, -camDist);
    glRotatef(camBeta * TO_DEG, 1, 0, 0);
    glRotatef(camAlpha * TO_DEG, 0, 1, 0);
}
