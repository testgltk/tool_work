#include "DrawTriangleIndex.h"
#include <QGLWidget>
#include <GL/glu.h>
#include "glwidget.h"

void CDrawTriangleIndex::AddPointFlow(const QPointF qPointf)
{
	//�����͌��݃|���S���O���[�v�ԍ���ΏۂƂ��܂��B
	int indexID = 0;
	int addIndexOfID = 0;

	//STEP1 ���łɒ��_���o�^�ʒu�ɋ߂����̂ɂȂ��Ă邩���ׂ�
	bool isNeighbor = false;

	indexID = CheckNeighborPoint(qPointf);

	//STEP2A �߂����_�Ȃ�V���ɒ��_�𐶐����Ȃ�
	if (indexID >= 0)
	{
		addIndexOfID = indexID;
	}

	//STEP2B �߂����_��������Ȃ�������V�������_�f�[�^�Ƃ���
	else
	{
		addIndexOfID = m_NowMaxVertex;

		QPointF uvSetPoint;
		float RateX = ((float)qPointf.x() - GlWidget::ADDPOINT_LIMIT_X_LEFT) / (float)(GlWidget::ADDPOINT_LIMIT_X_RIGHT - GlWidget::ADDPOINT_LIMIT_X_LEFT);
		float RateY = ((float)qPointf.y() - GlWidget::ADDPOINT_LIMIT_Y_UP)   / (float)(GlWidget::ADDPOINT_LIMIT_Y_DOWN - GlWidget::ADDPOINT_LIMIT_Y_UP);
		uvSetPoint.setX(RateX);
		uvSetPoint.setY(RateY);

		m_pVertecies[m_NowMaxVertex].pos.x = qPointf.x();
		m_pVertecies[m_NowMaxVertex].pos.y = qPointf.y();
		m_pVertecies[m_NowMaxVertex].pos.z = 0.0f;

		m_pVertecies[m_NowMaxVertex].col.r = 1.0f;
		m_pVertecies[m_NowMaxVertex].col.g = 1.0f;
		m_pVertecies[m_NowMaxVertex].col.b = 0.0f;
		m_pVertecies[m_NowMaxVertex].col.a = 0.4f;

		m_pVertecies[m_NowMaxVertex].tex.u = RateX;
		m_pVertecies[m_NowMaxVertex].tex.v = RateY;

		m_pVertecies[m_NowMaxVertex].groupID = m_nGroupID;
		m_NowMaxVertex++;

		//indexID = AddPointOfIndex(QPointF qpointf);
	}

	//STEP3�@�V�����C���f�b�N�XID��ǉ�����
	// AddIndex(indexID);


	//���ݒǉ����悤�Ƃ��Ă�O���[�v�̃|���S�����ǂꂾ�����邩����
	int nowGroupPolyVtxCount = getGroupVertexNum(m_nGroupID);
	
	//�O�p�n������ł��ĂȂ��Ƃ��͕ʂ̏���
	if (nowGroupPolyVtxCount <= 3)
	{
		//���̂Ƃ��͒P����1�����_�𑫂��ĉ�����
		m_pIndices[m_NowMaxIndecies] = addIndexOfID;
		m_NowMaxIndecies++;
	}
	else
	{

		//���_�}�����[�h�ɂ���ĕω�������
		bool ManualMode = true;

		//�����}�����[�h(���炩���߂��łɎO�p�`������ꍇ�A���ł����_�����Ƌ߂���2�_���������Ă��̓_���C���f�b�N�X���X�g�ɒǉ����܂��B)
		if(ManualMode)
		{
			//���̂Ƃ��͒P����1�����_�𑫂��ĉ�����
			m_pIndices[m_NowMaxIndecies] = addIndexOfID;
			m_NowMaxIndecies++;
		}

		//�哱�}�����[�h(�K��3�_�����)
		else
		{
			//���̂Ƃ��͍Œ�1���͒��_�����݂��邽�߁A
			//�C���f�b�N�X���X�g�����Z����

			//STEP4 �C���f�b�N�X���X�g3�����K�v�Ȃ��ߓ���O���[�v�̍ł��߂����_��2����������
			int Index2 = 0;
			int Index3 = 0;

			CheckNearVertexID(qPointf, addIndexOfID, &Index2, &Index3);

			m_pIndices[m_NowMaxIndecies] = Index2;
			m_NowMaxIndecies++;
			m_pIndices[m_NowMaxIndecies] = Index3;
			m_NowMaxIndecies++;
			m_pIndices[m_NowMaxIndecies] = addIndexOfID;
			m_NowMaxIndecies++;
		}
	}
}

int CDrawTriangleIndex::CheckNeighborPoint(const QPointF& qpointf)
{
	//���e�덷
	float NX = 10.0f;
	float NY = 10.0f;

	for (int nVertex = 0; nVertex < MAX_VERTEX; nVertex++)
	{
		//�����O���[�v�łȂ���Ύ��̃|���S����
		if (m_pVertecies[nVertex].groupID != m_nGroupID)
		{
			continue;
		}

		VERTEX_3D Vertex = m_pVertecies[nVertex];

		float CX = Vertex.pos.x;
		float CY = Vertex.pos.y;

		float qX = static_cast<float>(qpointf.x());
		float qY = static_cast<float>(qpointf.y());

		if ((CX - NX) < qX && qX < (CX + NX))
		{
			if ((CY - NY) < qY && qY < (CY + NY))
			{
				return nVertex;
			}
		}
	}
	return -1;
}

void CDrawTriangleIndex::Draw(void)
{
	//�����Ȃ���΃X�L�b�v
	if (m_UseVertexCount < 3)
	{
		return;
	}

	//���W�n��ݒ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 650.0, 650.0, 0);
	glBegin(GL_TRIANGLES);

	//�`��
	glColor4f(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	glTexCoord2f(-m_Texcoords[0].u, -m_Texcoords[0].v);
	glVertex3f(m_Vertecies[0].x, m_Vertecies[0].y, m_Vertecies[0].z);
	glColor4f(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	glTexCoord2f(-m_Texcoords[1].u, -m_Texcoords[1].v);
	glVertex3f(m_Vertecies[1].x, m_Vertecies[1].y, m_Vertecies[1].z);
	glColor4f(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	glTexCoord2f(-m_Texcoords[2].u, -m_Texcoords[2].v);
	glVertex3f(m_Vertecies[2].x, m_Vertecies[2].y, m_Vertecies[2].z);

	glEnd();
}

void CDrawTriangleIndex::DrawIndex(void)
{
	//�O�p�`�����Ȃ��Ȃ�I��
	if (m_NowMaxVertex < 3)
	{
		return;
	}

	//���W�n��ݒ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 650.0, 650.0, 0);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	//glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glVertexPointer(3, GL_FLOAT, sizeof(VERTEX_3D), &m_pVertecies[0].pos);	//���W
	//glNormalPointer(GL_FLOAT, 0, Normal);		//�@��
	//glColorPointer(3, GL_FLOAT, 0, colors);	//�F
	glColorPointer(4, GL_FLOAT,sizeof(VERTEX_3D),&m_pVertecies[0].col);		//�F

	//����f�[�^���z��������̓C���f�b�N�X�̏ꍇ�ɂ��Ă�glBegin glEnd�͕K�v�Ȃ��B
	//glDrawArrays(GL_QUADS, 0, 4 * 1);	//�`��(4���_*1��)�@(��C���f�b�N�X���z��n��)
	///glDrawElements(GL_QUADS, 4 /*���ݒ��_��*/, GL_UNSIGNED_BYTE, indices);

	//test
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices2);
	glDrawElements(GL_TRIANGLES, m_NowMaxIndecies, GL_UNSIGNED_BYTE, m_pIndices);
	glFlush();

	glBindTexture(GL_TEXTURE_2D, 0);

	//������
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

int CDrawTriangleIndex::getGroupVertexNum(const int ID)
{
	int nResult = 0;
	for (int nVertex = 0; nVertex < MAX_VERTEX; nVertex++)
	{
		if (m_pVertecies[nVertex].groupID == ID)
		{
			nResult++;
		}
	}
	return nResult;
}

bool CDrawTriangleIndex::CheckNearVertexID(const QPointF& qpointf,int addIndex, int* pOutFirst, int* pOutSecond)
{
	float dx = 0;
	float dy = 0;
	float qX = static_cast<float>(qpointf.x());
	float qY = static_cast<float>(qpointf.y());

	float length = 0.0f;
	float lengthMin = 9999999999.0f;
	float lengthMinSecond = 9999999999.0f;
	int MinID = -1;
	int MinSecondID = -1;

	//�ŏ��̃��[�v�ōł��߂�ID���擾
	for (int nVertex = 0; nVertex < MAX_VERTEX; nVertex++)
	{
		if (m_pVertecies[nVertex].groupID != m_nGroupID)
		{
			continue;
		}

		if (nVertex == addIndex)
		{
			continue;
		}

		dx = qX - m_pVertecies[nVertex].pos.x;
		dy = qX - m_pVertecies[nVertex].pos.y;
		
		length = (dx*dx) + (dy*dy);

		//�ł��߂��_��ID�����炤�B
		if (lengthMin > length)
		{
			lengthMin = length;
			MinID = nVertex;
		}
	}

	//���̃��[�v��2�Ԗڂɋ߂�ID���擾
	for (int nVertex = 0; nVertex < MAX_VERTEX; nVertex++)
	{
		if (m_pVertecies[nVertex].groupID != m_nGroupID)
		{
			continue;
		}

		if (nVertex == MinID)
		{
			continue;
		}

		if (nVertex == addIndex)
		{
			continue;
		}

		dx = qX - m_pVertecies[nVertex].pos.x;
		dy = qX - m_pVertecies[nVertex].pos.y;

		length = (dx*dx) + (dy*dy);

		//�ł��߂��_��ID�����炤�B
		if (lengthMinSecond > length)
		{
			lengthMinSecond = length;
			MinSecondID = nVertex;
		}
	}


	//���ʂ�ԋp
	*pOutFirst  = MinID;
	*pOutSecond = MinSecondID;
	return (MinID >=0 && MinSecondID >= 0) ? true:false;
}
