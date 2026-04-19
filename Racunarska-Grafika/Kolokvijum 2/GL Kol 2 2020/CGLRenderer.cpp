#include "pch.h"
#include "CGLRenderer.h"
#include "GL/gl.h"
#include "GL/GLU.h"
#include "GL/glaux.h"
#include "GL/glut.h"
#include "DImage.h"
#include <math.h>

#define TO_DEG 180.0f/3.14
#define TO_RAD 3.14/180.0f

CGLRenderer::CGLRenderer(void)
{
}

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

    spider = LoadTexture("spider.png");
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

    glPushMatrix();
    glTranslatef(0, -10, 0);
    glColor3f(1, 1, 1);

    DrawSpider();


    glPopMatrix();

    DrawEnvCube(100);

    glFlush();
    SwapBuffers(pDC->m_hDC);

    wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);

    glDeleteTextures(1, &spider);
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
    glDisable(GL_TEXTURE_2D);


    glBegin(GL_LINES);
    glColor3f(0, 0,1);
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

    float h = a / 2;
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
    glBindTexture(GL_TEXTURE_2D, pozadina[2]);
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
    glEnable(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-h,-h,-h);
    glTexCoord2f(0, 1); glVertex3f(-h,-h,h);
    glTexCoord2f(1, 1); glVertex3f(h,-h,h);
    glTexCoord2f(1, 0); glVertex3f(h,-h,-h);
    glEnd();
}

void CGLRenderer::DrawSphere(double r, int nSeg, double texU, double texV, double texR)
{
    double dAng1 = 3.14 / (double)nSeg;
    double dAng2 = 2 * 3.14 / (double)nSeg;

    double ang1 = -3.14 / 2.0;
    double ang2;

    for (int i = 0; i < nSeg; i++) {

        ang2 = 0;
        
        glBegin(GL_QUAD_STRIP);

        for (int j = 0; j < nSeg + 1; j++) {
            double x1 = r*cos(ang1) * cos(ang2);
            double y1 = r*sin(ang1);
            double z1 = r*cos(ang1) * sin(ang2);

            double x2 = r*cos(ang1 + dAng1) * cos(ang2);
            double y2 = r*sin(ang1 + dAng1);
            double z2 = r*cos(ang1 + dAng1) * sin(ang2);

            double tex1x = texR * x1 / r + texU;
            double tex1y = texR * z1 / r + texV;

            double tex2x = texR * x2 / r + texU;
            double tex2y = texR * z2 / r + texV;

            glTexCoord2f(tex1x, tex1y);
            glVertex3f(x1, y1, z1);
            glTexCoord2f(tex2x, tex2y);
            glVertex3f(x2, y2, z2);

            ang2 += dAng2;
        }

        glEnd();
        ang1 += dAng1;
    }
}

void CGLRenderer::DrawCone(double r, double h, int nSeg, double texU, double texV, double texR)
{
    double dAng1 = 2 * 3.14 / (double)nSeg;
    double ang1 = 0;

    glBegin(GL_TRIANGLE_FAN);

    glTexCoord2f(texU, texV);
    glVertex3f(0, h, 0);

    for (int i = 0; i <= nSeg; i++) {
        double x = r * cos(ang1);
        double y = 0;
        double z = r * sin(ang1);

        double tx = texR * x / r + texU;
        double ty = texR * z / r + texV;

        glTexCoord2f(tx, ty);
        glVertex3f(x, y, z);

        ang1 += dAng1;
    }
    glEnd();
}

void CGLRenderer::DrawLegSegment(double r, double h, int nSeg)
{
    glPushMatrix();

    glTranslatef(0, r, 0);
    DrawSphere(r, nSeg, 0.25, 0.25, 0.24);
    DrawCone(r, h, nSeg, 0.75, 0.75, 0.24);
    
    glPopMatrix();
}

void CGLRenderer::DrawLeg()
{
    glPushMatrix();

    DrawLegSegment(1, 10, 5);
    glTranslatef(0, 10, 0);
    glRotatef(85, 1, 0, 0);
    DrawLegSegment(1, 15, 5);

    glPopMatrix();
}

void CGLRenderer::DrawSpiderBody()
{
    glPushMatrix();

    glPushMatrix();

    glScalef(1, 0.5, 1);
    DrawSphere(3, 10, 0.25, 0.25, 0.24);

    glPopMatrix();


    glPushMatrix();

    glTranslatef(6, 0, 0);
    glScalef(1, 0.8, 1);
    DrawSphere(5, 10, 0.25, 0.25, 0.24);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(-4, 0, 0);
    glScalef(1, 0.5, 1);
    DrawSphere(2, 10, 0.75, 0.25, 0.24);

    glPopMatrix();

    glPopMatrix();
}

void CGLRenderer::DrawSpider()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spider);

    glPushMatrix();

    glTranslatef(0, 5, 0);

    DrawSpiderBody();

    glPushMatrix();


    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();
        glRotatef(i * 30 - 45, 0, 1, 0);
        glRotatef(45, 1, 0, 0);
        DrawLeg();
        glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();

    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();
        glRotatef(i * 30 - 45 + 180, 0, 1, 0);
        glRotatef(45, 1, 0, 0);
        DrawLeg();
        glPopMatrix();
    }
    glPopMatrix();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void CGLRenderer::UpdateCamera()
{
    glTranslatef(0, 0, -cameraDist);
    glRotatef(beta*TO_DEG, 1, 0, 0);
    glRotatef(alpha*TO_DEG, 0, 1, 0);
}
