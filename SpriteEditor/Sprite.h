#ifndef _SPRITE_H_
#define _SPRITE_H_

class CSprite
{
public:
	CSprite(void)
		:m_X(0.0f), m_Y(0.0f), m_Width(1.0f), m_Height(1.0f)
	{}
	virtual ~CSprite(void){}
	void SetX(float fX){ m_X = fX; }
	void SetY(float fY){ m_Y = fY; }
	float GetX(void){ return m_X; }
	float GetY(void){ return m_Y; }
	float SetWidth(float fW){ m_Width = fW; }
	float SetHeight(float fH){ m_Height = fH; }
	float GetWidth(void){ return m_Width; }
	float GetHeight(void){ return m_Height; }
	void Draw(void);

protected:

private:
	float m_X;
	float m_Y;
	float m_Width;
	float m_Height;
};

#endif