#include "StdAfx.h"
#include "Explosion.h"

//��ը��ʵ��

//��̬ͼ���б�
CImageList CExplosion::images;
//���ñ�ը��λ�á���ʼ�±�
CExplosion::CExplosion(int x, int y) :imagesIndex(EXPLOSION_START)
{
	bossDie = FALSE;
	mPoint.x = x;
	mPoint.y = y;
}

CExplosion::~CExplosion(void)
{
}
//���ƣ���˳����ʾ��ը�İ˸�ͼ���γɶ���Ч��
int CExplosion::Draw(CDC *pDC, BOOL bPause)
{
	if (bPause == 0) {
		if (imagesIndex < EXPLOSION_NUM) {
			BOOL b = images.Draw(pDC, imagesIndex, mPoint, ILD_TRANSPARENT);
			/*if (!b)
				return b;*/
			imagesIndex++;
			return EXPLOSION_STATUS_SUCCESS;
		}
		else return EXPLOSION_STATUS_STOP;
	}
	else return EXPLOSION_STATUS_PAUSE;
}
//���ر�ըͼ��
BOOL CExplosion::LoadImage()
{
	return  CGameObject::LoadImage(images, IDB_BMP_EXPLOSION, RGB(0, 0, 0), EXPLOSION_WIDTH, EXPLOSION_WIDTH, EXPLOSION_NUM);
}