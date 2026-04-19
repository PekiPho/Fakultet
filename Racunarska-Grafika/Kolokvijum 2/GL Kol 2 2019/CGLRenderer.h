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

	UINT bager;
	UINT pozadina[6];


	void DrawPolygon(POINTF* points, POINTF* texCoords, int n);
	void DrawExtrudedPolygon(POINTF* points, POINTF* texCoords, int n, float zh, float r, float g, float b);
	void DrawBase();
	void DrawBody();
	void DrawArm(double zh);
	void DrawFork();
	void DrawExcavator();

	float ang1 = 0;
	float ang2 = 90;
	float ang3 = -90;
	float ang4 = -90;

	void DrawEnvCube(double a);

	void UpdateCamera();

	double beta = 0;
	double alpha = 0;
	double cameraDist = 0;

};

