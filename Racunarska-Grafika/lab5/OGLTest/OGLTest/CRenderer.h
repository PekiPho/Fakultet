#pragma once
#include "CMaterial.h"

#define	VAZA_BOJA_1 1.00, 1.00, 0.00
#define VAZA_BOJA_1_AMBIENT 0.25, 0.25, 0
#define VAZA_BOJA_1_SPECULAR 0.5, 0.5, 0

#define VAZA_BOJA_2 1.00, 0.00, 1.00
#define VAZA_BOJA_2_AMBIENT 0.25, 0.00, 0.25
#define VAZA_BOJA_2_SPECULAR 0.5, 0, 0.5

#define SVETLO_1 0.00, 0.00, 1.00
#define SVETLO_1_SPECULAR 0.0, 0.0, 0.4

#define SVETLO_2 1.00, 0.00, 0.00
#define SVETLO_2_SPECULAR 0.4, 0, 0.0

#define SVETLO_3 0.0, 1.0, 1
#define SVETLO_3_SPECULAR 0.4, 0.4, 0.4

#define LIGHT1_POS -20, 0, 0
#define LIGHT2_POS 20, 0, 0
#define LIGHT3_POS 0, 20, 0

constexpr double R_R1 = 5;
constexpr double R_R2 = 3.5;
constexpr double R_R3 = 2;
constexpr double Height = 1.2;


class CRenderer
{
	HGLRC m_hrc;

	CMaterial vase1, vase2, light1, light2, light3, table, wall;

public:

	bool light3On = true, light2On = true, light1On = true, normalsOn = true;

	double viewAngleXY;
	double viewAngleXZ;
	double viewR;

	double eyex, eyey, eyez;
	double centerx, centery, centerz;
	double upx, upy, upz;

	CRenderer();


	bool CreateGLContext(CDC* pDC);
	void PrepareScene(CDC* pDC);
	void Reshape(CDC* pDC, int w, int h);
	void DrawScene(CDC* pDC);
	void DestroyScene(CDC* pDC);


	void DrawLight(double posX, double posY, double posZ, double r, CMaterial& mat, bool lightOn = true);
	void SetLightPositionAndDirection(GLenum light, double posX, double posY, double posZ, double dirX, double dirY, double dirZ, bool lightOn = true);

	void DrawSphere(double r, int nSegAlpha, int nSegBeta, bool onlyUpperHalf = false);
	void DrawCylinder(double h, double r1, double r2, CMaterial& mat, int nSeg = 40, bool includeBase = false);
	void DrawBase();
	void DrawVase();
	void DrawWallGrid(double h, int nSeg);
	void DrawSideGrid(double h, double w, int nSegH, int nSegW);
	void DrawCube(double h, int nSeg);
	void DrawCuboid(double h, double w, double d, int nSegH, int nSegW, int nSegD);
	void DrawAxis(double width);

	void RotateCamera(double dXY, double dXZ);
	void RecalculateCamera();
	void ZoomCamera(bool direction);
};

