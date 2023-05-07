#include "StdAfx.h"
#include "Ball.h"

//��̬��ͼ����������
CImageList CBall::imagesDown;
CImageList CBall::imagesUp;
//���캯����������ʼλ�ú��˶������˶��ٶ�
CBall::CBall(int x, int y, int direction)
{
	mPoint.x = x;
	mPoint.y = y;
	this->direction = direction;
	this->ballSpeed = BALL_SPEED;
}

CBall::~CBall(void)
{
}
//�����ڵ�ͼ��
BOOL CBall::Draw(CDC *pDC, BOOL bPause)
{
	if (bPause == 0) {
		//�ڵ�������У�ֻ��Ҫ���������꣬��ֻʵ���ڵ����ϵ��·���
		mPoint.y += ballSpeed * this->direction;
		//Boss�ڵ�����仯
		int index = rand() % 5;
		if (direction == 1) {
			imagesDown.Draw(pDC, index, mPoint, ILD_TRANSPARENT);
		}
		else {
			imagesUp.Draw(pDC, index, mPoint, ILD_TRANSPARENT);
		}
		return TRUE;
	}
	else return FALSE;
}
BOOL CBall::Draw(CDC *pDC, int passNum,BOOL bPause)
{
	//�л��ڵ���ؿ��仯
	int index = (passNum - 1) / 2;
	if (bPause == 0) {
		//�ڵ�������У�ֻ��Ҫ���������꣬��ֻʵ���ڵ����ϵ��·���
		mPoint.y += ballSpeed * this->direction;
		if (direction == 1) {
			imagesDown.Draw(pDC, index, mPoint, ILD_TRANSPARENT);
		}
		else {
			imagesUp.Draw(pDC, index, mPoint, ILD_TRANSPARENT);
		}
		return TRUE;
	}
	else return FALSE;
}
//�����ڵ�ͼ��
BOOL CBall::LoadImageUp()
{
	return  CGameObject::LoadImageW(imagesUp,IDB_BMP_BALLUP, RGB(0, 0, 0), BALL_WIDTH, BALL_HEIGHT, 5);
}
//�����ڵ�ͼ��
BOOL CBall::LoadImageDown()
{
	return  CGameObject::LoadImageW(imagesDown, IDB_BMP_BALLDOWN,RGB(0,0,0), BALL_WIDTH, BALL_HEIGHT, 5);
}

