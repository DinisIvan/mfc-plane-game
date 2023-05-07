#include "StdAfx.h"
#include "Bomb.h"

//CBombʵ��

//����ͼ���������ã��þ�̬
CImageList CBomb::imagesUpdate;//�����ڵ�ͼ��
CImageList CBomb::images;//δ�����ڵ�ͼ��

//���ó�ʼ�ӵ�λ�ã������ٶȣ����з���
CBomb::CBomb(int x, int y, int direction,BOOL isUpdate)
{
	mPoint.x = x;
	mPoint.y = y;
	//����ս���ӵ��ķ����ٶ�
	bombSpeed = BOMB_SPEED;
	this->direction = direction;
	this->isUpdate = isUpdate;
}

CBomb::~CBomb(void)
{
}

//����
BOOL CBomb::Draw(CDC *pDC, BOOL bPause)
{
	if (bPause == 0) {
		//�ӵ�ֻ��Ҫ��������
		mPoint.y -= bombSpeed * direction;//bombSpeed�����ӵ����ٶȣ�Ҳ�����ӵ��ƶ��Ĳ���
		if (isUpdate == TRUE) {
			int index = rand() % 18;
			return imagesUpdate.Draw(pDC, index, mPoint, ILD_TRANSPARENT);
		}
		else {
			int index = rand() % 15;
			return images.Draw(pDC, index, mPoint, ILD_TRANSPARENT);
		}
	}
	else return FALSE;
}

BOOL CBomb::LoadImage()//�������Ϸɵ��ӵ���ͼƬ
{
	CGameObject::LoadImage(images, IDB_BMP_BOMB1, RGB(0, 0, 0), BOMB_WIDTH, BOMB_WIDTH, 15);
	CGameObject::LoadImage(imagesUpdate, IDB_BMP_BOMB, RGB(0, 0, 0), BOMB_WIDTH, BOMB_HEIGHT, 18);
	return TRUE;
}