#pragma once
#include "GameObject.h"
#include "Resource.h"

//��ըͼ����
#define EXPLOSION_WIDTH 66
//��ըͼ������
#define EXPLOSION_NUM 8
//��ը��ͼ���±�
#define EXPLOSION_START 0

//��ը����״̬���
#define EXPLOSION_STATUS_SUCCESS 11
#define EXPLOSION_STATUS_PAUSE 12
#define EXPLOSION_STATUS_STOP 13

//��ը��
class CExplosion :public CGameObject
{
public:
	CExplosion(int x, int y);
	~CExplosion(void);

	int Draw(CDC* pDC, BOOL bPause);

	//����ͼ��
	static BOOL LoadImage();

	//��ȡ��ը����
	CRect GetRect()
	{
		return CRect(mPoint, CPoint(mPoint.x + EXPLOSION_WIDTH, mPoint.y + EXPLOSION_WIDTH));
	}

	void SetBossDie(BOOL bossDie) {
		this->bossDie = bossDie;
	}
	BOOL GetBossDie() {
		return this->bossDie;
	}
private:
	//ը����ͼƬ�б�
	static CImageList images;
	//ͼ�������Ĳ�������
	int   imagesIndex;//ȡֵΪ0-7
	BOOL bossDie;//��Ǹñ�ը��Boss������ը
};