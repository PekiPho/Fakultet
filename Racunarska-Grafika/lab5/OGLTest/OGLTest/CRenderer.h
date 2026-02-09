#pragma once
#include "CMaterial.h"
#include <lab6/CTexture.h>


class CRenderer
{
	CRenderer(void);
	virtual ~CRenderer(void);

	bool CreateGLContext(CDC* pDC);
	void PrepareScene(CDC* pDC);
	void Reshape(CDC* pDC, int w, int h);
	void DrawScene(CDC* pDC);
	void DestroyScene(CDC* pDC);

	void SetAngles(float angle_h, float angle_v);
	CPoint GetAngle() {
		return CPoint(angle_v, angle_h);
	}

protected:
	HGLRC	 m_hrc; 

	float angle_v;
	float angle_h;
	void DrawGround();
	void DrawAxis();
	void DrawSide();
	void DrawWheelSide();
	void DrawWheel();

	void DrawTruck();
	void DrawSphere(float radius);

	CTexture groundTex, truckTex;
};

