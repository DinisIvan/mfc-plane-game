#pragma once
#include "GameObject.h"
#include "Resource.h"
#include "stdafx.h"

//�л��ĸ߶�
#define ENEMY_HEIGHT 90
//�л��Ŀ��
#define ENEMY_WIDTH 120
//�л������ٶ�
#define ENEMY_SPEED 3
//�л�Ѫ��
#define ENEMY_LIFE 2

//Ĭ�ϵȴ�ʱ��
#define WAIT 0

//�л���
class CEnemy :public CGameObject
{
public:
	//ָ���л����з���
	CEnemy(int direction,int WINDOWS_WIDTH,int WINDOWS_HEIGHT);
	~CEnemy(void);
	//����
	BOOL Draw(CDC* pDC, BOOL bPause);
	BOOL Draw(CDC *pDC, int passNum, BOOL bPause);

	//���صл�ͼ��
	static BOOL LoadImage();

	//��ȡ�л�����
	CRect GetRect()
	{
			return CRect(mPoint, CPoint(mPoint.x + ENEMY_HEIGHT, mPoint.y + ENEMY_HEIGHT));
	}

	int GetDirection() const
	{
		return direction;
	}
	void SetDirection(int direction)
	{
		this->direction = direction;
	}
	void SetSpeed(int speed)
	{
	this->speed = speed;
	}

	//�Ƿ���Կ������ӵ�
	BOOL isFire();

protected:
	static CImageList imagesUp;//���Ϸɵл�ͼ��
	static CImageList imagesDown;//���·ɵл�ͼ��
	int    direction;//���� 1->���� 0->ֹͣ -1->����
	 //ͼ������
	int imageIndex;//ȡ0�������·ɵĵл���Ϊ1�������Ϸɵĵл�
	//�л����ٶ�
	int speed;
	int  wait;//������ʱ
	int WINDOWS_WIDTH;//���ڿ�
	int WINDOWS_HEIGHT;//���ڸ�
public :
	int life;//�л�������ֵ
};
