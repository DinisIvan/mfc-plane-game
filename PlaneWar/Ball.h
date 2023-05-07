#pragma once
#include "GameObject.h"
#include "Resource.h"

//�̶��л�ը�����ٶ�Ϊ20
#define BALL_SPEED 6
//�л��ڵ�ͼ��߶�Ϊ8
#define BALL_HEIGHT 40
#define BALL_WIDTH 15

//�л��ڵ���
class CBall :public CGameObject
{
public:
	//direction��ʾ�л��ڵ�����
	CBall(int x, int y, int direction);
	~CBall(void);

	BOOL Draw(CDC* pDC, BOOL bPause);
	BOOL Draw(CDC *pDC, int passNum, BOOL bPause);

	static BOOL LoadImageUp();
	static BOOL LoadImageDown();

	//����ڵ����ڵľ��ο�
	CRect GetRect()
	{
		return CRect(mPoint, CPoint(mPoint.x + BALL_WIDTH, mPoint.y + BALL_HEIGHT));
	}
	void SetBallSpeed(int ballSpeed)
	{
		this->ballSpeed = ballSpeed;
	}

private:
	//���Ϻ����µĵл��ڵ�
	static CImageList imagesUp;
	static CImageList imagesDown;
	int direction;//����ը���ķ��з���
	int ballSpeed;//ը�����ٶ�
};

