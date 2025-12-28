#pragma once
using namespace std;
#include <iostream>

class Figura
{
protected:
	float x;
	float y;
public:
	Figura();
	Figura(float a, float b);
	virtual void Upis(float a, float b) = 0;
	virtual void Cita() = 0;
	virtual float Povrsina() = 0;
	virtual float Obim() = 0;
};

