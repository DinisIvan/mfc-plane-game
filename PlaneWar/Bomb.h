#pragma once
#include "GameObject.h"
#include "Resource.h"

//ս���ӵ��߶�Ϊ20
#define BOMB_HEIGHT 60

//ս���ӵ���
#define BOMB_WIDTH 30

//�ӵ������ٶ�
#define BOMB_SPEED 30

//ս���ӵ���
class CBomb :public CGameObject
{
public:
	CBomb(int x, int y, int direction,int isUpdate);
	~CBomb(void);

	//����
	BOOL Draw(CDC* pDC, BOOL bPause);

	//���ط������ϵ��ڵ�ͼ��
	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(mPoint, CPoint(mPoint.x + BOMB_WIDTH, mPoint.y + BOMB_HEIGHT));
	}
	//��ȡը���ĸ߶�
	int GetBombHeight()
	{
		return BOMB_HEIGHT;
	}
	//��ȡը���Ŀ��
	int GetBombWidth()
	{
		return BOMB_WIDTH;
	}
	void SetDirection(int direction)
	{
		this->direction = direction;
	}
	int GetDirection()
	{
		return direction;
	}
	void SetBombSpeed(int bombSpeed)
	{
		this->bombSpeed = bombSpeed;
	}
	int GetBombSpeed()
	{
		return this->bombSpeed;
	}
private:
	//ս���ӵ�ͼ������
	static CImageList imagesUpdate;
	static CImageList images;
	int direction;//ȡֵ1���ϣ�-1����
	int bombSpeed;//�����ӵ��ķ����ٶ�
	BOOL isUpdate;//����Ƿ�Ϊ�����ڵ�
};
