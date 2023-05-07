#include "StdAfx.h"
#include "Enemy.h"

//CEnemyʵ��
//��̬ͼ���б�
CImageList CEnemy::imagesUp;
CImageList CEnemy::imagesDown;
//ָ���л�λ�ã����з��򣬵ȴ�ʱ�䣬�ٶ�
CEnemy::CEnemy(int direction , int WINDOWS_WIDTH, int WINDOWS_HEIGHT) : wait(WAIT), speed(ENEMY_SPEED)
{
	this->direction = direction;
	this->WINDOWS_WIDTH = WINDOWS_WIDTH;
	this->WINDOWS_HEIGHT = WINDOWS_HEIGHT;
	this->life = ENEMY_LIFE;
	//�������ڴ��ڿ�Χ��
	mPoint.x = rand() % WINDOWS_WIDTH;
	//�������ڴ��ڸ߷�Χ��
	if (direction == -1)//���Ƶл��ٶȷ���л����Ϸ�
	{
		mPoint.y = WINDOWS_HEIGHT;
		imageIndex = 1;
	}
	else//�л����·�
	{
		mPoint.y = 0;
		imageIndex = 0;
	}
}

CEnemy::~CEnemy(void)
{
}

//Boss�·���FALSE��ʾBoss���ڳ�������ʱս�����ܽ��й���
//���Ƶ�ǰ�л�λ��
BOOL CEnemy::Draw(CDC *pDC, int passNum,BOOL bPause)
{
	if (bPause == 0) {
		int index = passNum % 5;
		//�л�λ������仯,ֻ�ı������꣬�����Ϊ���õл������ٷ���
		//+ rand() % 10
		mPoint.y += (speed)*direction;
		//imageIndexΪ0�������·ɵĵл���Ϊ1�������Ϸɵĵл�
		if (imageIndex == 0)
			imagesDown.Draw(pDC, index, mPoint, ILD_TRANSPARENT);
		else imagesUp.Draw(pDC, index, mPoint, ILD_TRANSPARENT);
		return TRUE;
	}
	else return FALSE;
}

BOOL CEnemy::Draw(CDC *pDC, BOOL bPause) {
	if (bPause == 0) {
		//�л�λ������仯,ֻ�ı������꣬�����Ϊ���õл������ٷ���
		//+ rand() % 10
		mPoint.y += (speed)*direction;
		//Ϊ0�������·ɵĵл���Ϊ1�������Ϸɵĵл�
		if (imageIndex == 0)
			imagesDown.Draw(pDC, 0, mPoint, ILD_TRANSPARENT);
		else imagesUp.Draw(pDC, 0, mPoint, ILD_TRANSPARENT);
		return TRUE;
	}
	else return FALSE;
}

//����ͼ��
BOOL CEnemy::LoadImage()
{
	//������Ϸ�����ͼ�����
	CBitmap enemy1;
	if (!enemy1.LoadBitmapW(IDB_BMP_ENEMYDOWN))
		return FALSE;
	//����CImageList����
	if (!imagesDown.Create(ENEMY_WIDTH, ENEMY_HEIGHT, ILC_COLOR24 | ILC_MASK, 5, 0))//nInitial��ʼ����
		return FALSE;//cx,cy ͼƬ�Ŀ��
	//ͼ�������м�������Ӧ��ͼ�����֮��ֱ��ͨ�����������ͼ�����
	imagesDown.Add(&enemy1, RGB(0,0,0));

	CBitmap enemy2;
	if (!enemy2.LoadBitmapW(IDB_BMP_ENEMYUP))
		return FALSE;
	if (!imagesUp.Create(ENEMY_WIDTH, ENEMY_HEIGHT, ILC_COLOR24 | ILC_MASK, 5, 0))//nInitial��ʼ����
		return FALSE;//cx,cy ͼƬ�Ŀ��
	imagesUp.Add(&enemy2, RGB(0,0,0));
	return TRUE;
}

//�л��Ƿ񿪻�
BOOL CEnemy::isFire()
{
	return TRUE;
}
