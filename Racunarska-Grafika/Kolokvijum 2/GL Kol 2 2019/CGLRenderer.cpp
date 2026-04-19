#include "pch.h"
#include "CGLRenderer.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glaux.h"
#include "GL\glut.h"
#include "DImage.h"

#define TO_RAD 3.14 /180.0f
#define TO_DEG 180/3.14


CGLRenderer::CGLRenderer(void) {

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

    bager = LoadTexture("excavator.png");

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
    gluPerspective(55, (double)w / (double)h, 0.1, 2000);
    glMatrixMode(GL_MODELVIEW);

    wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    UpdateCamera();

    //axes

    glLineWidth(4);
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 10, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 10);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(10, 0, 0);

    glEnd();

    glTranslatef(-4, 0, -2.5);

    DrawExcavator();

    glTranslatef(4, 50, 2.5);

    DrawEnvCube(100);

    glFlush();
    SwapBuffers(pDC->m_hDC);


    wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);

    glDeleteTextures(1, &bager);
    glDeleteTextures(6, pozadina);

    wglMakeCurrent(NULL, NULL);

    if (m_hrc) {
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

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S ,GL_REPEAT );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T ,GL_REPEAT );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER ,GL_LINEAR_MIPMAP_LINEAR );

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV, GL_MODULATE);

    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, slika.Width(), slika.Height(), GL_BGRA_EXT,GL_UNSIGNED_BYTE, slika.GetDIBBits());

    return idTeksture;
}

void CGLRenderer::DrawPolygon(POINTF* points, POINTF* texCoords, int n)
{
    glBegin(GL_TRIANGLE_FAN);

    for (int i = 0; i < n; i++) {
        glTexCoord2f(texCoords[i].x, texCoords[i].y);
        glVertex2f(points[i].x, points[i].y);
    }

    glEnd();
}

void CGLRenderer::DrawExtrudedPolygon(POINTF* points, POINTF* texCoords, int n, float zh, float r, float g, float b)
{
    glEnable(GL_TEXTURE_2D);

    glColor3f(1, 1, 1);
    DrawPolygon(points, texCoords, n);

    glPushMatrix();
    glTranslatef(0, 0, zh);
    DrawPolygon(points, texCoords, n);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glColor3f(r, g, b);

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= n; i ++ ) {
        
        int ind = i % n;
        glVertex3f(points[ind].x, points[ind].y, 0);
        glVertex3f(points[ind].x, points[ind].y, zh);
    }
    glEnd();
}

void CGLRenderer::DrawBase()
{
    POINTF points[8] = {
        {0.0f, 1.5f},
        {0.5f, 2.0f},
        {7.5f, 2.0f},
        {8.0f, 1.5f},
        {8.0f, 0.5f},
        {7.5f, 0.0f},
        {0.5f, 0.0f},
        {0.0f, 0.5f}

    };

    POINTF texCoords[8] = {
        {0 / 16.0f,  13 / 16.0f},
        {1 / 16.0f,  12 / 16.0f},
        {15 / 16.0f, 12 / 16.0f},
        {16 / 16.0f, 13 / 16.0f},
        {16 / 16.0f, 15 / 16.0f},
        {15 / 16.0f, 16 / 16.0f},
        {1 / 16.0f,  16 / 16.0f},
        {0 / 16.0f,  15 / 16.0f}
    };

    glBindTexture(GL_TEXTURE_2D, bager);
    DrawExtrudedPolygon(points, texCoords, 8, 5.0f, 0, 0, 0);
}

void CGLRenderer::DrawBody()
{
    POINTF points[5] = {
        {0.0f,4.0f},
        {2.0f,4.0f},
        {4.0f,2.0f},
        {4.0f,0.0f},
        {0.0f,0.0f}
    };

    POINTF texCoords[5] = {
        {8 / 16.0f,  0 / 16.0f},
        {12 / 16.0f, 0 / 16.0f},
        {16 / 16.0f, 4 / 16.0f},
        {16 / 16.0f, 8 / 16.0f},
        {8 / 16.0f,  8 / 16.0f}
    };

    glBindTexture(GL_TEXTURE_2D, bager);
    DrawExtrudedPolygon(points, texCoords, 5, 4.0f, 0.96f, 0.5f, 0.12f);

}

void CGLRenderer::DrawArm(double zh)
{
    POINTF points[6] = {
        {0.5f,2.0f},
        {8.0f,1.5f},
        {8.0f,0.5f},
        {0.5f,0.0f},
        {0.0f,0.5f},
        {0.0f,1.5f}
    };

    POINTF texCoords[6] = {
        {1 / 16.0f,  8 / 16.0f},
        {16 / 16.0f, 9 / 16.0f},
        {16 / 16.0f, 11 / 16.0f},
        {1 / 16.0f,  12 / 16.0f},
        {0 / 16.0f,  11 / 16.0f},
        {0 / 16.0f,  9 / 16.0f}
    };

    glBindTexture(GL_TEXTURE_2D, bager);
    DrawExtrudedPolygon(points, texCoords, 6, (float)zh, 0.96f, 0.5f, 0.12f);
}

void CGLRenderer::DrawFork()
{
    POINTF points[6] = {
        {0.5f,3.0f},
        {3.5f,3.0f},
        {4.0f,2.5f},
        {4.0f,0.0f},
        {0.0f,0.0f},
        {0.0f,2.5f}
    };

    POINTF texCoords[6] = {
        {1 / 16.0f, 0 / 16.0f},
        {7 / 16.0f, 0 / 16.0f},
        {8 / 16.0f, 1 / 16.0f},
        {8 / 16.0f, 6 / 16.0f},
        {0 / 16.0f, 6 / 16.0f},
        {0 / 16.0f, 1 / 16.0f}
    };

    glBindTexture(GL_TEXTURE_2D, bager);
    DrawExtrudedPolygon(points, texCoords, 6, 1.0f, 0.7f, 0.7f, 0.7f);
}

void CGLRenderer::DrawExcavator()
{

    glPushMatrix();

    DrawBase();

    glTranslatef(2, 2, 0.5);

    glTranslatef(2, 0, 2);
    glRotatef(ang1, 0, 1, 0);
    glTranslatef(-2, 0, -2);
    DrawBody();

    glTranslatef(4, 0, 1.5);

    glTranslatef(1, 1, 0);
    glRotatef(ang2, 0, 0, 1);
    glTranslatef(-1, -1, 0);
    DrawArm(1);

    glTranslatef(6.5, 0, -0.25);

    glTranslatef(1, 1, 0);
    glRotatef(ang3, 0, 0, 1);
    glTranslatef(-1, -1, 0);
    DrawArm(1.5);

    glTranslatef(6.5, 0, 0.25);

    glTranslatef(1, 1, 0);
    glRotatef(ang4, 0, 0, 1);
    glTranslatef(-1, -1, 0);
    DrawFork();

    glPopMatrix();
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
    glTexCoord2f(1,1); glVertex3f(h,-h,-h);
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

    glDisable(GL_TEXTURE_2D);
}

void CGLRenderer::UpdateCamera()
{
    glTranslatef(0, 0, cameraDist);
    glRotatef(beta * TO_DEG, 1, 0, 0);
    glRotatef(alpha * TO_DEG, 0, 1, 0);
}
