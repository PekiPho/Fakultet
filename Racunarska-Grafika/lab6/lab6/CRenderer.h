#pragma once
#include "CMaterial.h"
#include "CTexture.h"


class CRenderer
{
public:
	double viewAngleXY;
	double viewAngleXZ;
	double viewR;

	double eyex, eyey, eyez;
	double centerx, centery, centerz;
	double upx, upy, upz;

	CRenderer(void);
	virtual ~CRenderer(void);

	bool CreateGLContext(CDC* pDC);
	void PrepareScene(CDC* pDC);
	void Reshape(CDC* pDC, int w, int h);
	void DrawScene(CDC* pDC);
	void DestroyScene(CDC* pDC);

	void RotateCamera(double dXY, double dXZ);
	void RecalculateCamera();

	/*void SetAngles(float angle_h, float angle_v);
	CPoint GetAngle() {
		return CPoint(angle_v, angle_h);
	}*/

protected:
	HGLRC	 m_hrc; 


	
	void DrawGround();
	void DrawAxis();
	void DrawSide();
	void DrawWheelSide();
	void DrawWheel();

	void DrawTruck();
	void DrawSphere(float radius);

	

	CTexture groundTex, truckTex;
};

