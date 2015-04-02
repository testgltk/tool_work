//==============================================================================================
// 3�p�`�`��C���f�b�N�X�N���X�t�@�C��
// Author : TOMOHIRO KOUNO
// Create : 2015/3/23
//==============================================================================================

//==============================================================================================
// �C���N���[�h�K�[�h
//==============================================================================================
#ifndef _CDRAWTRIANGLE_INDEX_H_
#define _CDRAWTRIANGLE_INDEX_H_

//==============================================================================================
// �C���N���[�h
//==============================================================================================
#include <QGLWidget>
#include <QBasicTimer>
#include <QString>
#include <stdio.h>
#include "vertexFormat.h"
#include <QPointF>
class CUVDataManual;


typedef struct VERTEX_3D_TAG
{
	POS3		pos;
	TEXCOORD2	tex;
	COLOR4		col;
	int			groupID;
	VERTEX_3D_TAG::VERTEX_3D_TAG(void) :pos(), tex(), col(),groupID(-1){}
}VERTEX_3D;

//==============================================================================================
// �X�v���C�g�N���X
//==============================================================================================
class CDrawTriangleIndex
{
public:

	static const int MAX_VERTEX = 3000;
	static const int MAX_INDICES = 9000;

	CDrawTriangleIndex(void)
		:m_nGroupID(0), m_Vertecies{}, m_Texcoords{}, m_Color{}
		, m_UseVertexCount(0), m_NowMaxVertex(0), m_NowMaxIndecies(0)
	{
		SetColor(0.9f, 0.9f, 0.4f, 0.4f);

		m_pVertecies = new VERTEX_3D[MAX_VERTEX];
		m_pIndices   = new GLubyte[MAX_INDICES];
	}

	~CDrawTriangleIndex(void)
	{
		delete[] m_pVertecies;

		delete[] m_pIndices;
		m_pIndices = nullptr;
	}

	void AddPointFlow(const QPointF qPointf);

	void SetVertexCount(int nCount){ m_UseVertexCount = nCount; }

	void AddVertexCount(void)
	{
		if (m_UseVertexCount >= MAX_VERTEX)
		{
			return;
		}
		m_UseVertexCount++;
	}

	void DeleteLastVertexCount(void)
	{
		if (m_UseVertexCount <= 0)
		{
			return;
		}
		m_UseVertexCount--;
	}

	void Draw(void);

	void DrawIndex(void);

	void SetVertex(int nIndex, float x, float y, float z)
	{
		m_Vertecies[nIndex].x = x;
		m_Vertecies[nIndex].y = y;
		m_Vertecies[nIndex].z = z;
	}

	void SetTexcoord(int nIndex, float u, float v)
	{
		m_Texcoords[nIndex].u = u;
		m_Texcoords[nIndex].v = v;
	}

	void SetColor(float r, float g, float b, float a)
	{
		m_Color.r = r;
		m_Color.g = g;
		m_Color.b = b;
		m_Color.a = a;
	}

	void SetGroupID(int nID){ m_nGroupID = nID; }


	int GetGroupID(void){ return m_nGroupID; }

	int GetUseVertexCount(void){ return m_UseVertexCount; }

	POS3 GetVertex(int nIndex){ return m_Vertecies[nIndex]; }

	void Save(FILE* pFile)
	{
		//�`�悳��ĂȂ���΃X�L�b�v
		if (m_NowMaxVertex < 3)
		{
			return;
		}


		//fprintf(pFile, "GROUP ID = %d \n", m_nGroupID);
		fprintf(pFile, "MAX VERTEX = %d \n", m_NowMaxVertex);
		fprintf(pFile, "VERTECIES\n");

		for (int i = 0; i < m_NowMaxVertex; i++)
		{
			//fprintf(pFile, "V: %f %f %f T:%f %f \n", m_Vertecies[i].x, m_Vertecies[i].y, m_Vertecies[i].z, m_Texcoords[i].u, m_Texcoords[i].v);
			fprintf(pFile, "V: %f %f %f \n", m_pVertecies[i].pos.x, m_pVertecies[i].pos.y, m_pVertecies[i].pos.z);
		}

		fprintf(pFile, "TEXCOORDS\n");
		for (int i = 0; i < m_NowMaxVertex; i++)
		{
			fprintf(pFile, "T:%f %f \n",m_pVertecies[i].tex.u, m_pVertecies[i].tex.v);
		}

		fprintf(pFile, "MAX INDEX = %d \n", m_NowMaxIndecies);

		for (int i = 0; i < m_NowMaxIndecies; i+=3)
		{
			fprintf(pFile, "GROUP ID %d Index:%d %d %d\n", m_pVertecies[m_pIndices[i + 2]].groupID, m_pIndices[i + 0], m_pIndices[i + 1], m_pIndices[i + 2]);
		}
	}

	int CheckNeighborPoint(const QPointF& qpointf);


	int getGroupVertexNum(const int ID); /// ��������̃O���[�v�̃|���S���͑S���ŉ����邩
	bool CheckNearVertexID(const QPointF& qpointf, int addIndex,int* pOutFirst, int* pOutSecond); //�����������T�����Ă��̃|�C���g����ǂ̒��_�C���f�b�N�X���߂��̂��������� �����ł�����TRUE

protected:

private:

	int		  m_nGroupID;		///> ���̎O�p�`�̃O���[�v�F�����
	GLubyte*   m_pIndices;		///> �C���f�b�N�X���
	VERTEX_3D* m_pVertecies;	///> ���_�\���̔z��

	POS3      m_Vertecies[3];	///> 1�̎O�p�n�̒��_���W���
	TEXCOORD2 m_Texcoords[3];	///> 1�̎O�p�`�̃e�N�X�`�����W���
	COLOR4	  m_Color;			///> ���̃|���S���ɓ��Ă͂߂�F���i�f�t�H���g�F�z���C�g�j
	int		  m_UseVertexCount; ///> ���̃|���S���ɑ΂��ē_������ł�����ł邩(0,1,2,3)

	int		m_NowMaxVertex;		///> ���ݍő咸�_�g�p��
	int		m_NowMaxIndecies;	///> ���ݍő�C���f�b�N�X��
};
#endif