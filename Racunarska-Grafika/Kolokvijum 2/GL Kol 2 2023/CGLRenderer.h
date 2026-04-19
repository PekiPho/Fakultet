#pragma once
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
	void DrawAxes();

	UINT lampa;
	UINT pozadina[6];

	void DrawEnvCube(double a);
	void DrawCylinder(double r1, double r2, double h, int nSeg, int texMode, bool bIsOpen);
	void DrawLampBase();
	void DrawLampArm();
	void DrawLampHead();
	void DrawLamp();

	void UpdateCamera();

	double cameraDist = 0;
	double beta = 0;
	double alpha = 0;


	float ang1 = 140.0f;
	float ang2 = 85.0f;
	float ang3 = 90.0f;
};

