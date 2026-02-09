#pragma once
class CTexture
{
private:
	unsigned int m_ID;

public:
	CTexture();
	~CTexture();
	void LoadFileForm(CString fileName);
	void Select();
	void Relase();
	static void PrepareTexture(bool lightEnabled);
	static void BindDefault();
};

