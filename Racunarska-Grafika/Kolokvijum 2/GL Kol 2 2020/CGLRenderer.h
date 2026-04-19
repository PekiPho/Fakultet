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

	UINT spider;
	UINT pozadina[6];

	void DrawAxes();
	void DrawEnvCube(double a);
	void DrawSphere(double r, int nSeg, double texU, double texV, double texR);
	void DrawCone(double r, double h, int nSeg, double texU, double texV, double texR);
	void DrawLegSegment(double r, double h, int nSeg);
	void DrawLeg();
	void DrawSpiderBody();
	void DrawSpider();


	void UpdateCamera();

	float cameraDist=0;
	float alpha = 0;
	float beta = 0;

};

