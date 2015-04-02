//==============================================================================================
// 3角形描画クラスファイル
// Author : TOMOHIRO KOUNO
// Create : 2015/4/2
//==============================================================================================

//==============================================================================================
// インクルードガード
//==============================================================================================
#ifndef _VERTEXFORMAT_H_
#define _VERTEXFORMAT_H_

typedef struct POS3_TAG
{

	float x;
	float y;
	float z;
	POS3_TAG(void) : x(0), y(0), z(0){ }
}POS3;

typedef struct TEXCOORD_TAG
{
	float u;
	float v;
	TEXCOORD_TAG(void) :u(0), v(0){}
}TEXCOORD2;

typedef struct COLOR4_TAG
{
	float r;
	float g;
	float b;
	float a;
	COLOR4_TAG(void) : r(0), g(0), b(0), a(0){}
}COLOR4;

#endif
// End of File VERTEXFORMAT_H_