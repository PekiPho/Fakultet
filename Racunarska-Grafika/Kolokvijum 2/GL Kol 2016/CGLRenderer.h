#pragma once
#include "DImage.h"

class CGLRenderer
{
public:
	CGLRenderer(void);
	virtual ~CGLRenderer(void);

	bool CreateGLContext(CDC* pDC);
	void PrepareScene(CDC* pDC);
	void Reshape(CDC* pDC, int w, int h);
	void DrawScene(CDC* pDC);
	void DestroyScene(CDC* pDC);


	HGLRC m_hrc;

	UINT LoadTexture(char* filename);

	UINT brick;
	UINT bg;

	void DrawCube(double a);
	void DrawTube(double r1, double r2, double h, int n);
	void DrawCone(double r, double h, int n);
	void DrawPaddle(double length, double width);


	void UpdateCamera();

	double camDist = 0;
	double camAlpha = 0;
	double camBeta = 0;

	double ang = 0;
};

