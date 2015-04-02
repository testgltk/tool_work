#include "DrawTriangleIndex.h"
#include <QGLWidget>
#include <GL/glu.h>
#include "glwidget.h"

void CDrawTriangleIndex::AddPointFlow(const QPointF qPointf)
{
	//検索は現在ポリゴングループ番号を対象とします。
	int indexID = 0;
	int addIndexOfID = 0;

	//STEP1 すでに頂点が登録位置に近いものになってるか調べる
	bool isNeighbor = false;

	indexID = CheckNeighborPoint(qPointf);

	//STEP2A 近い頂点なら新たに頂点を生成しない
	if (indexID >= 0)
	{
		addIndexOfID = indexID;
	}

	//STEP2B 近い頂点が見つからなかったら新しい頂点データとする
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

	//STEP3　新しいインデックスIDを追加する
	// AddIndex(indexID);


	//現在追加しようとしてるグループのポリゴンがどれだけあるか調査
	int nowGroupPolyVtxCount = getGroupVertexNum(m_nGroupID);
	
	//三角系が一つもできてないときは別の処理
	if (nowGroupPolyVtxCount <= 3)
	{
		//このときは単純に1つずつ頂点を足して加える
		m_pIndices[m_NowMaxIndecies] = addIndexOfID;
		m_NowMaxIndecies++;
	}
	else
	{

		//頂点挿入モードによって変化が発生
		bool ManualMode = true;

		//自動挿入モード(あらかじめすでに三角形がある場合、今打った点部分と近くの2点を検索してその点をインデックスリストに追加します。)
		if(ManualMode)
		{
			//このときは単純に1つずつ頂点を足して加える
			m_pIndices[m_NowMaxIndecies] = addIndexOfID;
			m_NowMaxIndecies++;
		}

		//主導挿入モード(必ず3点を入力)
		else
		{
			//このときは最低1個数は頂点が存在するため、
			//インデックスリストを加算する

			//STEP4 インデックスリスト3つ分が必要なため同一グループの最も近い頂点他2つを検索する
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
	//許容誤差
	float NX = 10.0f;
	float NY = 10.0f;

	for (int nVertex = 0; nVertex < MAX_VERTEX; nVertex++)
	{
		//同じグループでなければ次のポリゴンへ
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
	//かけなければスキップ
	if (m_UseVertexCount < 3)
	{
		return;
	}

	//座標系を設定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 650.0, 650.0, 0);
	glBegin(GL_TRIANGLES);

	//描画
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
	//三角形が少ないなら終了
	if (m_NowMaxVertex < 3)
	{
		return;
	}

	//座標系を設定
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


	glVertexPointer(3, GL_FLOAT, sizeof(VERTEX_3D), &m_pVertecies[0].pos);	//座標
	//glNormalPointer(GL_FLOAT, 0, Normal);		//法線
	//glColorPointer(3, GL_FLOAT, 0, colors);	//色
	glColorPointer(4, GL_FLOAT,sizeof(VERTEX_3D),&m_pVertecies[0].col);		//色

	//送るデータが配列もしくはインデックスの場合についてはglBegin glEndは必要ない。
	//glDrawArrays(GL_QUADS, 0, 4 * 1);	//描画(4頂点*1面)　(非インデックスかつ配列渡し)
	///glDrawElements(GL_QUADS, 4 /*存在頂点数*/, GL_UNSIGNED_BYTE, indices);

	//test
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices2);
	glDrawElements(GL_TRIANGLES, m_NowMaxIndecies, GL_UNSIGNED_BYTE, m_pIndices);
	glFlush();

	glBindTexture(GL_TEXTURE_2D, 0);

	//無効化
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

	//最初のループで最も近いIDを取得
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

		//最も近い点のIDをもらう。
		if (lengthMin > length)
		{
			lengthMin = length;
			MinID = nVertex;
		}
	}

	//次のループで2番目に近いIDを取得
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

		//最も近い点のIDをもらう。
		if (lengthMinSecond > length)
		{
			lengthMinSecond = length;
			MinSecondID = nVertex;
		}
	}


	//結果を返却
	*pOutFirst  = MinID;
	*pOutSecond = MinSecondID;
	return (MinID >=0 && MinSecondID >= 0) ? true:false;
}
