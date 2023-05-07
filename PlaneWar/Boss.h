#pragma once
#include "Enemy.h"

//Boss�ĸ߶�
#define BOSS_HEIGHT 250
//Boss�Ŀ��
#define BOSS_WIDTH 360
//Boss�����ٶ�
#define BOSS_SPEED 3
//Ĭ��Boss����
#define BOSS_LIFE 100

//Boss��
class CBoss :
	public CEnemy
{
public:
	CBoss(int direction, int WINDOWS_WIDTH, int WINDOWS_HEIGHT);
	~CBoss();
	//����
	BOOL Draw(CDC* pDC, BOOL bPause);
	BOOL Draw(CDC *pDC, int passNum, BOOL bPause);

	//���صл�ͼ��
	static BOOL LoadImage();
	//��ȡ�л�����
	CRect GetRect()
	{
			return CRect(mPoint, CPoint(mPoint.x + BOSS_WIDTH, mPoint.y + BOSS_HEIGHT));
	}

	//�Ƿ���Կ������ӵ�
	BOOL isFire();
private:
	BOOL bossLoadOK;//Boss�Ƿ�������
	//Bossͼ��
	static CImageList imagesBoss;
};

