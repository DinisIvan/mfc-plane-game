
// PlaneWarView.cpp : CPlaneWarView ���ʵ��
//

#include "stdafx.h"
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
#include <MMSYSTEM.H>
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "PlaneWar.h"
#endif
   
#include "PlaneWarDoc.h"
#include "PlaneWarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneWarView

IMPLEMENT_DYNCREATE(CPlaneWarView, CView)

BEGIN_MESSAGE_MAP(CPlaneWarView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPlaneWarView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CPlaneWarView ����/����

CPlaneWarView::CPlaneWarView()
{
	//Ĭ��ս�������ٶȡ�ս������ֵ��ս���÷֡��ؿ����Ƿ���ء��Ƿ���ͣ

    // TODO: �ڴ˴���ӹ������
}

CPlaneWarView::~CPlaneWarView()
{
}

BOOL CPlaneWarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPlaneWarView ����
void CPlaneWarView::OnDraw(CDC* pDC)
{
	CPlaneWarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

// CPlaneWarView ��ӡ

void CPlaneWarView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPlaneWarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPlaneWarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPlaneWarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CPlaneWarView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CPlaneWarView ���

#ifdef _DEBUG
void CPlaneWarView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneWarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneWarDoc* CPlaneWarView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneWarDoc)));
	return (CPlaneWarDoc*)m_pDocument;
}
#endif //_DEBUG

//��дʵ��
//����ٶ�
int CPlaneWarView::GetSpeed()
{
	return this->speed;
}
//�����ٶ�
void CPlaneWarView::SetSpeed(int speed)
{
	this->speed = speed;
}

// CPlaneWarView ��Ϣ�������
//��ͼ��������
int CPlaneWarView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	//-----------��ʼ������------------
	//������Ϸ����ͼƬ
	CMyPlane::LoadImage();
	CMyPlane::LoadImageProtect();
	CEnemy::LoadImage();
	CBoss::LoadImage();
	CBall::LoadImageUp();
	CBall::LoadImageDown();
	CBomb::LoadImage();
	CExplosion::LoadImage();
	CBlood::LoadImage();
	//���ر���ͼƬ
	CBitmap startbmp;
	startbmp.LoadBitmapW(IDB_BMP_TITLE);
	startIMG.Create(346, 96, ILC_COLOR24 | ILC_MASK, 1, 0);
	startIMG.Add(&startbmp, RGB(0, 0, 0));
	
	//������ʼ��ʧ��
	if (!scene.InitScene())
	{
		AfxMessageBox(L"ͼƬ��Դ����ʧ��");
		exit(0);
	}

	//������ʼ��
	myplane = new CMyPlane(FALSE);
	isBoss = FALSE;
	speed = DEFAULT_SPEED;
	myLife = DEFAULT_LIFE;
	lifeNum = DEFAULT_LIFE_COUNT;
	lifeCount = 1;
	passScore = 0;
	myScore=0;
	bossLoaded = TRUE;
	passNum = DEFAULT_PASS;
	isPass = 0;
	isPause = FALSE;
	magicCount = 0;
	bloodExist = FALSE;
	bossBlood = BOSS_LIFE;
	isProtect = FALSE;
	isUpdate = FALSE;
	test = FALSE;
	isStop = FALSE;
	boss = NULL;
	isStarted = FALSE;

	SetTimer(4, 40, NULL);//����������ʱ��
	SetMyTimer();
	return 0;
}

//��ʱ������
void CPlaneWarView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//˫����
	CDC *pDC = GetDC();
	if (pDC == NULL) {
		CView::OnTimer(nIDEvent);
		return;
	}
	//��ÿͻ�����������
	GetClientRect(&rect);
	//�ڴ滺��CDC
	CDC cdc;

	//�ڴ��г�����ʱͼ��Ļ���λͼ
	CBitmap* cacheBitmap = new CBitmap;
	//�õ�ǰ�豸CDC��ʼ������CDC
	cdc.CreateCompatibleDC(pDC);
	//��pDC�ͻ���λͼ�Ĺ�ϵ��cdc�����������λͼ�У�������֮����һ���Խ�����λͼ�������Ļ
	cacheBitmap->CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	//�滻cdcԭ���Ļ�����Ϊ����λͼ������cdc��������ݾ�д���˻���λͼ��
	CBitmap *pOldBit = cdc.SelectObject(cacheBitmap);

	/*
	//�ù̶��Ĺ���ɫ����ı����ο�
	cdc.FillSolidRect(rect, RGB(51, 255, 255));
	//��ӱ���ͼƬλͼ
	CBitmap bitmap_BackGround;
	//���ر���λͼ
	if(passNum==1)
		bitmap_BackGround.LoadBitmap(IDB_BMP_BACKGROUND1);
	else if(passNum==2)
		bitmap_BackGround.LoadBitmap(IDB_BMP_BACKGROUND2);
	else if(passNum==3)
		bitmap_BackGround.LoadBitmap(IDB_BMP_BACKGROUND3);
	BITMAP bimap_Background;//����λͼͼ��
	bitmap_BackGround.GetBitmap(&bimap_Background);
	CDC cdc_BackGround;//�������cdc������������
	cdc_BackGround.CreateCompatibleDC(&cdc);//��ʼ����������
	//�����������壬����ͼ����Ϊ��������Ļ�����������ԭ���ݾ��Ǳ���ͼ������Ҫ�������
	CBitmap*Old = cdc_BackGround.SelectObject(&bitmap_BackGround);
	*/

	//�������
	if (isStarted == FALSE)
		scene.StickScene(&cdc, -1, rect);
	else
		scene.StickScene(&cdc, passNum, rect);
	if (nIDEvent == 4) {
		//��������
		scene.MoveBg();
	}
	//��ӭ����
	if (isStarted == FALSE) {
		startIMG.Draw(&cdc, 0, CPoint(rect.right/2-173, 100), ILD_TRANSPARENT);
		HFONT textFont;
		textFont = CreateFont(12, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(textFont);
		cdc.SetTextColor(RGB(128, 128, 0));
		//����͸������
		cdc.SetBkMode(TRANSPARENT);
		cdc.TextOutW(rect.right/2-120, 210, _T("������ƣ��������ASDW�����"));
		cdc.TextOutW(rect.right/ 2 - 120, 225, _T("������ո����������"));
		cdc.TextOutW(rect.right / 2 - 120, 240, _T("��ͣ��Z��"));
		cdc.TextOutW(rect.right / 2 - 120, 255, _T("���У�X��"));
		cdc.TextOutW(rect.right / 2 - 120, 270, _T("�����֣�C��"));
		cdc.TextOutW(rect.right / 2 - 120, 285, _T("ս��������V��"));
		cdc.TextOutW(rect.right / 2 - 120, 300, _T("�޵�ģʽ��Y��"));
		cdc.TextOutW(rect.right / 2 - 120, 315, _T("��ʼ����ֵ��10"));
		cdc.TextOutW(rect.right / 2 - 120, 330, _T("��ʼħ��ֵ��0"));
		cdc.TextOutW(rect.right / 2 - 120, 345, _T("�л�����ֵ��2"));
		cdc.TextOutW(rect.right / 2 - 120, 360, _T("����һ���л���1�֣���������ﵽҪ�󼴿ɽ���Bossģʽ����ӮBoss���ɽ�����һ�ء�"));
		cdc.TextOutW(rect.right / 2 - 120, 375, _T("ħ��ֵ������Ϸ�������ӣ���ͨ��ʹ��ħ��ֵʹ�÷����֡�ս��������ս�����е�ʹ�á�"));
		cdc.TextOutW(rect.right / 2 - 120, 390, _T("��Ϸ�����л���һ���̶ȵ�Ѫ�������Իָ�����ֵ��"));
		cdc.TextOutW(rect.right / 2 - 120, 405, _T("���Źؿ����࣬�л����ڵ��ٶȺ����������ӣ�ͨ��10�ؼ���ͨ�أ�"));
		HFONT tipFont;
		tipFont = CreateFont(24, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(tipFont);
		cdc.SetTextColor(RGB(255, 0, 0));
		cdc.TextOutW(rect.right / 2 - 120, 420, _T("�����������ո����ʼ��Ϸ"));
		//����������cdc�е��������͵�һ��������pDC�У����������Ļ��
		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &cdc, 0, 0, SRCCOPY);
		//�ͷŶ���cdc
		cdc.DeleteDC();
		//�ͷŻ���λͼ
		cacheBitmap->DeleteObject();
		//�ͷ�һ��pDC
		ReleaseDC(pDC);
		CView::OnTimer(nIDEvent);
		return;
	}
	//��ʾ��ͣ��Ϣ
	if (myplane != NULL&&isPause == TRUE&&isStop==FALSE) {
		HFONT textFont;
		textFont = CreateFont(24, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(textFont);
		cdc.SetTextColor(RGB(255, 0, 0));
		//����͸������
		cdc.SetBkMode(TRANSPARENT);
		cdc.TextOutW(rect.right / 2 - 10, 150, _T("��ͣ"));
		////����������cdc�е��������͵�һ��������pDC�У����������Ļ��
		//pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &cdc, 0, 0, SRCCOPY);
		////�ͷŶ���cdc
		//cdc.DeleteDC();
		////�ͷŻ���λͼ
		//cacheBitmap->DeleteObject();
		////�ͷ�һ��pDC
		//ReleaseDC(pDC);
		//CView::OnTimer(nIDEvent);
		//return;
	}

	//ˢ����ʾս��
	if (myplane != NULL) {
		//reDraw(myplane, TRUE);
		myplane->Draw(&cdc,FALSE,isProtect);
	}
	//�����ӵл�,�л��������ը������ʱ�л��ٶ��������͹ؿ��й�
	if (myplane != NULL && isPause == 0&&isBoss==FALSE)
	{
		//�л�������ʱ������
		if (nIDEvent == 2) {
			//���ݹؿ��������л�
			if (passNum <=5) {
				//ǰ���ֻ��һ������ĵл�
				int direction = 1;//���õл��ķ��򣬴��Ϸ��ɳ�
				CEnemy *enemy = new CEnemy(direction, rect.right, rect.bottom);
				enemyList.AddTail(enemy);//��������л�
			}
			else if (passNum >5) {//�����֮����������ĵл�
				int direction1 = 1;	//���õл��ķ��򣬴��Ϸ��ɳ�		
				CEnemy *enemy1 = new CEnemy(direction1,rect.right,rect.bottom);
				enemy1->SetSpeed(ENEMY_SPEED+(rand() % 2 + passNum-1));
				enemyList.AddTail(enemy1);//��������л�
				int direction2 = -1;//���õл��ķ��򣬴��·��ɳ�	
				CEnemy *enemy2 = new CEnemy(direction2, rect.right, rect.bottom);
				enemy2->SetSpeed(ENEMY_SPEED + (rand() % 2 + passNum - 1));
				enemyList.AddTail(enemy2);//��������л�
			}
		}

		//�����߽�ĵл���������
		POSITION stPos = NULL, tPos = NULL;
		stPos = enemyList.GetHeadPosition();
		int direction = 1;
		while (stPos != NULL)
		{
			tPos = stPos;
			CEnemy *enemy = (CEnemy *)enemyList.GetNext(stPos);
			//�жϵл��Ƿ����
			if (enemy->GetPoint().x<rect.left || enemy->GetPoint().x>rect.right
				|| enemy->GetPoint().y<rect.top || enemy->GetPoint().y>rect.bottom)
			{
				enemyList.RemoveAt(tPos);
				delete enemy;
			}//if
			else
			{
				//û���磬����
				enemy->Draw(&cdc,passNum, FALSE);
				//�л�ը��������ʱ������
				if (nIDEvent == 3) {
					//���ö�ʱ�������л�ը��
					PlaySound((LPCTSTR)IDR_WAV_BALL, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
					CBall * ball = new CBall(enemy->GetPoint().x + ENEMY_HEIGHT / 2, enemy->GetPoint().y + ENEMY_HEIGHT, enemy->GetDirection());
					ball->SetBallSpeed(BALL_SPEED + (passNum - 1) ); 
					ballList.AddTail(ball);
				}
			}//else
		}//while

		 //�жϲ����ĵл�ը���Ƿ���磬���Ѿ����磬��ɾ���õл�ը��
		POSITION stBallPos=NULL, tBallPos=NULL;
		stBallPos = ballList.GetHeadPosition();
		while (stBallPos != NULL)
		{
			tBallPos = stBallPos;
			ball = (CBall *)ballList.GetNext(stBallPos);
			if (ball->GetPoint().x<rect.left || ball->GetPoint().x>rect.right
				|| ball->GetPoint().y<rect.top || ball->GetPoint().y>rect.bottom)
			{
				ballList.RemoveAt(tBallPos);
				delete  ball;
			}//if
			else
			{
				ball->Draw(&cdc,passNum, FALSE);
			}//else
		}//while
	}
	//Boss�����ڵ�
	if (myplane != NULL && isPause == 0 && isBoss == TRUE) {
		//Boss�����ӵ�
		//�л�ը��������ʱ������
		if (nIDEvent == 3) {
			//���ö�ʱ�������л�ը��
			PlaySound((LPCTSTR)IDR_WAV_BALL, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
			CBall * ball1 = new CBall(boss->GetPoint().x + BOSS_WIDTH / 2, boss->GetPoint().y + BOSS_HEIGHT, 1);
			ball1->SetBallSpeed(BALL_SPEED + (passNum - 1) * 2);
			ballList.AddTail(ball1);
			CBall * ball2 = new CBall(boss->GetPoint().x +5, boss->GetPoint().y + BOSS_HEIGHT, 1);
			ball2->SetBallSpeed(BALL_SPEED + (passNum - 1) * 2);
			ballList.AddTail(ball2);
			CBall * ball3 = new CBall(boss->GetPoint().x + BOSS_WIDTH -5, boss->GetPoint().y + BOSS_HEIGHT,1);
			ball3->SetBallSpeed(BALL_SPEED + (passNum - 1) * 2);
			ballList.AddTail(ball3);
			CBall * ball4 = new CBall(boss->GetPoint().x + BOSS_WIDTH / 2+85, boss->GetPoint().y + BOSS_HEIGHT, 1);
			ball4->SetBallSpeed(BALL_SPEED + (passNum - 1) * 2);
			ballList.AddTail(ball4);
			CBall * ball5 = new CBall(boss->GetPoint().x + BOSS_WIDTH / 2-85, boss->GetPoint().y + BOSS_HEIGHT, 1);
			ball5->SetBallSpeed(BALL_SPEED + (passNum - 1) * 2);
			ballList.AddTail(ball5);
		}
		//��ʾBossը��
		//�жϲ����ĵл�ը���Ƿ���磬���Ѿ����磬��ɾ���õл�ը��
		POSITION stBallPos = NULL, tBallPos = NULL;
		stBallPos = ballList.GetHeadPosition();
		while (stBallPos != NULL)
		{
			tBallPos = stBallPos;
			ball = (CBall *)ballList.GetNext(stBallPos);
			if (ball->GetPoint().x<rect.left || ball->GetPoint().x>rect.right
				|| ball->GetPoint().y<rect.top || ball->GetPoint().y>rect.bottom)
			{
				ballList.RemoveAt(tBallPos);
				delete  ball;
			}//if
			else
			{
				ball->Draw(&cdc, FALSE);
			}//else
		}//while
	}

	//ս�������ӵ�
	if (myplane != NULL&& isPause == 0)
	{
		//����ս���ӵ�λ��
		POSITION posBomb = NULL, tBomb = NULL;
		posBomb = bombList.GetHeadPosition();
		while (posBomb != NULL)
		{
			tBomb = posBomb;
			bomb = (CBomb *)bombList.GetNext(posBomb);
			if (bomb->GetPoint().x<rect.left || bomb->GetPoint().x>rect.right
				|| bomb->GetPoint().y<rect.top || bomb->GetPoint().y>rect.bottom)
			{
				//ɾ��Խ����ӵ�
				bombList.RemoveAt(tBomb);
				delete  bomb;
			}//if
			else
				bomb->Draw(&cdc, FALSE);
		}//while
	}//if

	//��1����ӱ�ըЧ����ս���ӵ����ел�
	if (myplane != NULL&& isPause == 0)
	{
		//����ս���ӵ�λ�ã��л�λ��
		POSITION bombPos, bombTemp, enemyPos, enemyTemp;
		for (bombPos = bombList.GetHeadPosition(); (bombTemp = bombPos) != NULL;)
		{
			bomb = (CBomb *)bombList.GetNext(bombPos);
			for (enemyPos = enemyList.GetHeadPosition(); (enemyTemp = enemyPos) != NULL;)
			{
				enemy = (CEnemy *)enemyList.GetNext(enemyPos);
				//���ս���ӵ��ľ�������
				CRect bombRect = bomb->GetRect();
				//��õл��ľ�������
				CRect enemyRect = enemy->GetRect();
				//�ж��������������Ƿ��н���
				CRect tempRect;
				if (tempRect.IntersectRect(&bombRect, enemyRect))
				{
					//����ը������ӵ���ը������
					CExplosion *explosion = new CExplosion((bomb->GetPoint().x + BOMB_WIDTH / 2 - EXPLOSION_WIDTH / 2), (bomb->GetPoint().y + BOMB_HEIGHT / 2 - EXPLOSION_WIDTH / 2));
					explosionList.AddTail(explosion);
					PlaySound((LPCTSTR)IDR_WAV_EXPLOSION, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
					//��ը��ɾ���ӵ�
					bombList.RemoveAt(bombTemp);
					delete  bomb;
					//ָ����һ��
					bomb = NULL;
					//�л�����ֵ����
					enemy->life -= (1 + isUpdate);
					if (enemy->life <= 0) {
						//���ӵ÷�
						passScore++;
						//ɾ���л�
						enemyList.RemoveAt(enemyTemp);
						delete  enemy;
					}
					//�ڵ���ɾ����ֱ��������ѭ��
					break;
				}
			}

			if (isBoss == TRUE&&bomb != NULL) {
				//���ս���ӵ��ľ�������
				CRect bombRect = bomb->GetRect();
				//���Boss�ľ�������
				CRect bossRect = boss->GetRect();
				//�ж��������������Ƿ��н���
				CRect tempRect;
				if (tempRect.IntersectRect(&bombRect, bossRect))
				{
					//����ը������ӵ���ը������
					CExplosion *explosion = new CExplosion((bomb->GetPoint().x + BOMB_WIDTH / 2 - EXPLOSION_WIDTH / 2), (bomb->GetPoint().y + BOMB_HEIGHT / 2 - EXPLOSION_WIDTH / 2));
					explosionList.AddTail(explosion);
					PlaySound((LPCTSTR)IDR_WAV_EXPLOSION, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
					//��ը��ɾ���ӵ�
					bombList.RemoveAt(bombTemp);
					delete  bomb;
					bomb = NULL;
					//��Boss����ɾ���л���ֻ��Ѫ
					bossBlood -= (1 + isUpdate);
					if (bossBlood <= 0) {
						CExplosion *explosion1 = new CExplosion(boss->GetPoint().x , boss->GetPoint().y );
						explosionList.AddTail(explosion1);
						CExplosion *explosion2 = new CExplosion((boss->GetPoint().x + BOSS_WIDTH ), (boss->GetPoint().y + BOSS_HEIGHT ));
						explosionList.AddTail(explosion2);
						CExplosion *explosion3 = new CExplosion((boss->GetPoint().x + BOSS_WIDTH ), (boss->GetPoint().y ));
						explosionList.AddTail(explosion3);
						CExplosion *explosion4 = new CExplosion((boss->GetPoint().x ), (boss->GetPoint().y + BOSS_HEIGHT ));
						explosionList.AddTail(explosion4);
						CExplosion *explosion5 = new CExplosion((boss->GetPoint().x + BOSS_WIDTH / 2 - EXPLOSION_WIDTH / 2), (boss->GetPoint().y + BOSS_HEIGHT / 2 - EXPLOSION_WIDTH / 2));
						explosion5->SetBossDie(TRUE);//������һ��ը����ը��֮��������һ��
						explosionList.AddTail(explosion5);
						PlaySound((LPCTSTR)IDR_WAV_EXPLOSION, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
						
						delete boss;
						boss = NULL;
						//���صı�־����
						//isPause = TRUE;
						//CMyPlane* temp = myplane;
						//myplane = new CMyPlane(FALSE);
						delete  myplane;
						myplane = NULL;
						isPass = 1;
						isBoss = FALSE;
					}
				}
			}
		}//for
	}//if
   //��2����ӱ�ըЧ�����л�ը������ս��
	if (myplane != NULL&& isPause == 0)
	{
		//�����л�ը��λ�����꣬ս��λ��myPlanePos
		POSITION ballPos, ballTemp;
		for (ballPos = ballList.GetHeadPosition(); (ballTemp = ballPos) != NULL;)
		{
			ball = (CBall *)ballList.GetNext(ballPos);
			//��õл�ը���ľ�������
			CRect ballRect = ball->GetRect();
			//���ս���ľ�������
			CRect myPlaneRect = myplane->GetRect();
			//�ж��������������Ƿ��н���
			CRect tempRect;
			//����л�ը������ս������ʹս����ը
			if (tempRect.IntersectRect(&ballRect, myPlaneRect))
			{
				//����ը������뱬ը������
				CExplosion *explosion = new CExplosion((ball->GetPoint().x + BALL_WIDTH / 2 - EXPLOSION_WIDTH / 2), (ball->GetPoint().y + BALL_HEIGHT / 2 - EXPLOSION_WIDTH / 2));
				PlaySound((LPCTSTR)IDR_WAV_EXPLOSION, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				explosionList.AddTail(explosion);
				if (isProtect == FALSE&&test == FALSE)
					//ս������ֵ��1
					myLife--;
				//ɾ���л�ը��
				ballList.RemoveAt(ballTemp);
				delete  ball;
				//��Ϸ����
				if (myLife == 0)
				{
					lifeNum--;
					if (lifeNum <= 0) {
						//ɾ��ս������
						//isPause = TRUE;
						CMyPlane* temp = myplane;
						myplane = NULL;
						//myplane = new CMyPlane(FALSE);
						delete  temp;
						temp = NULL;
						gameOver(pDC,cdc, cacheBitmap);
						break;
					}
					else {
						myLife = DEFAULT_LIFE;
					}
				}//if
			}//if
		}//for
	}//if
	//��3����ӱ�ըЧ�����л���ս����ײ
	if (myplane != NULL&& isPause == 0)
	{
		//���ս���ľ�������
		CRect myPlaneRect = myplane->GetRect();
		POSITION enemyPos, enemyTemp;
		for (enemyPos = enemyList.GetHeadPosition(); (enemyTemp = enemyPos) != NULL;)
		{
			enemy = (CEnemy *)enemyList.GetNext(enemyPos);
			//��õл��ľ�������
			CRect enemyRect = enemy->GetRect();
			//�ж��������������Ƿ��н���
			CRect tempRect;
			if (tempRect.IntersectRect(&enemyRect, myPlaneRect))
			{
				CExplosion *explosion = new CExplosion(myplane->GetPoint().x + PLANE_WIDTH / 2 - EXPLOSION_WIDTH / 2, myplane->GetPoint().y + PLANE_HEIGHT / 2 - EXPLOSION_WIDTH / 2);
				PlaySound((LPCTSTR)IDR_WAV_EXPLOSION, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				explosionList.AddTail(explosion);
				if (isProtect == FALSE&&test == FALSE)
					//ս������ֵ��1
					myLife--;
				//�л�����ֵ����
				enemy->life--;
				if (enemy->life <= 0) {
					//�÷�
					passScore++;
					//ɾ���л�
					enemyList.RemoveAt(enemyTemp);
					delete  enemy;
				}
				//��Ϸ����
				if (myLife == 0)
				{
					lifeNum--;
					if (lifeNum <= 0) {
						//isPause = TRUE;
						//ɾ��ս������			
						CMyPlane* temp = myplane;
						myplane = NULL;
						//myplane = new CMyPlane(FALSE);
						delete  temp;
						temp = NULL;
						gameOver(pDC,cdc, cacheBitmap);
						break;
					}
					else {
						myLife = DEFAULT_LIFE;
					}
				}//if
			}//if
		}//for
		//Boss��ս����ײ
		if (isBoss == TRUE) {
			myPlaneRect = myplane->GetRect();
			//���Boss�ľ�������
			CRect bossRect = boss->GetRect();
			//�ж��������������Ƿ��н���
			CRect tempRect;
			if (tempRect.IntersectRect(&myPlaneRect, bossRect))
			{
				//����ը������ӵ���ը������
				CExplosion *explosion = new CExplosion(myplane->GetPoint().x + PLANE_WIDTH / 2 - EXPLOSION_WIDTH / 2, myplane->GetPoint().y + PLANE_HEIGHT / 2 - EXPLOSION_WIDTH / 2);
				explosionList.AddTail(explosion);
				PlaySound((LPCTSTR)IDR_WAV_EXPLOSION, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				if (isProtect == FALSE&&test == FALSE)
					//ս������ֵ��1
					myLife--;
				//��Boss����ɾ���л���ֻ��Ѫ
				bossBlood--;
				myplane->SetPoint(PLANE_X, PLANE_Y);
				if (bossBlood <= 0) {
					CExplosion *explosion1 = new CExplosion(boss->GetPoint().x, boss->GetPoint().y);
					explosionList.AddTail(explosion1);
					CExplosion *explosion2 = new CExplosion((boss->GetPoint().x + BOSS_WIDTH), (boss->GetPoint().y + BOSS_HEIGHT));
					explosionList.AddTail(explosion2);
					CExplosion *explosion3 = new CExplosion((boss->GetPoint().x + BOSS_WIDTH), (boss->GetPoint().y));
					explosionList.AddTail(explosion3);
					CExplosion *explosion4 = new CExplosion((boss->GetPoint().x), (boss->GetPoint().y + BOSS_HEIGHT));
					explosionList.AddTail(explosion4);
					CExplosion *explosion5 = new CExplosion((boss->GetPoint().x + BOSS_WIDTH / 2 - EXPLOSION_WIDTH / 2), (boss->GetPoint().y + BOSS_HEIGHT / 2 - EXPLOSION_WIDTH / 2));
					explosion5->SetBossDie(TRUE);//������һ��ը����ը��֮��������һ��
					explosionList.AddTail(explosion5);
					PlaySound((LPCTSTR)IDR_WAV_EXPLOSION, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);

					delete boss;
					boss = NULL;
					//���صı�־����
					//isPause = TRUE;
					//CMyPlane* temp = myplane;
					//myplane = new CMyPlane(FALSE);
					delete  myplane;
					myplane = NULL;
					isPass = 1;
					isBoss = FALSE;
				}
				//��Ϸ����
				if (myLife == 0)
				{
					lifeNum--;
					if (lifeNum <= 0) {
						//isPause = TRUE;
						//ɾ��ս������			
						CMyPlane* temp = myplane;
						myplane = NULL;
						//myplane = new CMyPlane(FALSE);
						delete  temp;
						temp = NULL;
						
						gameOver(pDC,cdc,cacheBitmap);
					}
					else {
						myLife = DEFAULT_LIFE;
						//ɾ��ԭս������			
					}
				}//if
			}
		}//if
	}
	//��4����ӱ�ըЧ����ս���ӵ����ел�ը��
	if (myplane != NULL&& isPause == 0)
	{
		//����ս���ӵ�λ�ã��л�λ��
		POSITION bombPos, bombTemp, ballPos, ballTemp;
		for (bombPos = bombList.GetHeadPosition(); (bombTemp = bombPos) != NULL;)
		{
			bomb = (CBomb *)bombList.GetNext(bombPos);
			//���ս���ӵ��ľ�������
			CRect bombRect = bomb->GetRect();
			for (ballPos = ballList.GetHeadPosition(); (ballTemp = ballPos) != NULL;)
			{
				ball = (CBall *)ballList.GetNext(ballPos);
				//��õл�ը���ľ�������
				CRect ballRect = ball->GetRect();
				//�ж��������������Ƿ��н���
				CRect tempRect;
				if (tempRect.IntersectRect(&bombRect, ballRect))
				{
					//����ը������ӵ���ը������
					CExplosion *explosion = new CExplosion((ball->GetPoint().x + BALL_WIDTH /2-EXPLOSION_WIDTH/2), (ball->GetPoint().y + BOMB_HEIGHT/2 - EXPLOSION_WIDTH / 2));
					explosionList.AddTail(explosion);
					PlaySound((LPCTSTR)IDR_WAV_EXPLOSION, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
					//��ը��ɾ��ս���ӵ�
					bombList.RemoveAt(bombTemp);
					delete  bomb;
					//ɾ���л�ը��
					ballList.RemoveAt(ballTemp);
					delete  ball;
					//����л��ڵ����ӷ�
					//myScore++;
					//ս���ڵ��ͷţ�ֱ��������ѭ��
					break;
				}//if
			}//for
		}//for
	}//if
	 //��5����Ӽ�ѪЧ����ս���Ե�Ѫ��
	if (myplane != NULL&& isPause == 0)
	{
		//����Ѫ��λ��
		POSITION bloodPos, bloodTemp;
		for (bloodPos = bloodList.GetHeadPosition(); (bloodTemp = bloodPos) != NULL;)
		{
			blood = (CBlood *)bloodList.GetNext(bloodPos);
			//���Ѫ������
			CRect bloodbRect = blood->GetRect();
			//���ս������
			CRect planeRect = myplane->GetRect();
			//�ж��������������Ƿ��н���
			CRect tempRect;
			if (tempRect.IntersectRect(&bloodbRect, planeRect))
			{
				//��ѪЧ��
				myLife += 5;
				if (myLife > DEFAULT_LIFE)
					myLife = DEFAULT_LIFE;
				// TODO ����
				PlaySound((LPCTSTR)IDR_WAV_BLOOD, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				//��Ѫ��Ѫ��ɾ��
				bloodList.RemoveAt(bloodTemp);
				delete  blood;
				break;
			}//if
		}//for
	}//if

	//��ʾ��ըЧ��
	if (myplane != NULL&&isPause == FALSE) {
		POSITION explosionPos, explosionTemp;
		explosionPos = explosionList.GetHeadPosition();
		//������ը�����ǿ�ʱ������λ����ʾ
		while (explosionPos != NULL)
		{
			explosionTemp = explosionPos;
			explosion = (CExplosion *)explosionList.GetNext(explosionPos);
			BOOL flag = explosion->Draw(&cdc, FALSE);
			//��ը8֡������ɾ����ը����
			if (flag == EXPLOSION_STATUS_STOP) {
				//ɾ����ը����
				explosionList.RemoveAt(explosionTemp);
				delete explosion;
			}
		}//while
	}

	//����Ѫ��
	if (myplane != NULL && myLife > 0)
	{
		//�ؿ���������֮һ����֮��������Ѫ��
		if (passScore > (PASS_SCORE + passNum * 5)*lifeCount/3)
		{
			//����Ļ����δ�Ե���Ѫ������β�����Ѫ��
			if (bloodExist == FALSE) {
				lifeCount++;
				//����Ѫ��
				blood = new CBlood(rect.right,rect.bottom);
				bloodList.AddTail(blood);
				bloodExist = TRUE;
				SetTimer(6, 10000, NULL);
			}else lifeCount++;
		}
	}
	//Ѫ����ʱ����10���Ѫ����ʧ
	if (nIDEvent == 6&&isPause==0) {
		KillTimer(6);
		bloodExist = FALSE;
		//����Ѫ��λ��
		POSITION bloodPos, bloodTemp;
		for (bloodPos = bloodList.GetHeadPosition(); (bloodTemp = bloodPos) != NULL;)
		{
			blood = (CBlood *)bloodList.GetNext(bloodPos);
			bloodList.RemoveAt(bloodTemp);
			delete  blood;
		}
	}
	//��ʾѪ��
	if (myplane != NULL&&isPause == FALSE) 
	{
		POSITION bloodPos;
		bloodPos = bloodList.GetHeadPosition();
		//����Ѫ�������ǿ�ʱ������λ����ʾ
		while (bloodPos != NULL)
		{
			blood = (CBlood *)bloodList.GetNext(bloodPos);
			blood->Draw(&cdc, FALSE);
		}//while
	}

	//��Ϸ�����������Ϸ��ǰ��Ϣ
	if (myplane != NULL)
	{
		HFONT font;
		font = CreateFont(15, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(font);
		CString str;
		cdc.SetTextColor(RGB(255, 0, 0));
		//����͸������
		cdc.SetBkMode(TRANSPARENT);
		str.Format(_T("��ǰ�ؿ�:%d"), passNum);
		cdc.TextOutW(10, 0, str);
		str.Format(_T("��ǰ����:%d"), lifeNum);
		cdc.TextOutW(110, 0, str);
		str.Format(_T("��ǰ�÷�:%d"), passScore);
		cdc.TextOutW(10, 15, str);
		if (test == TRUE) {
			cdc.TextOutW(10, 200, _T("�޵�ģʽ������"));
		}

		HFONT font1;
		font1 = CreateFont(8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(font);
		cdc.SetTextColor(RGB(255,0,0));
		cdc.TextOutW(rect.right- 12 * DEFAULT_LIFE-45, 0, _T("Ѫ����"));
		//���Ѫ��
		CBrush brush;
		brush.CreateSolidBrush(RGB(255, 0, 0));//��ɫˢ
		CBrush* oldBrush = cdc.SelectObject(&brush);
		int leftPos, topPos = 0, rightPos, buttomPos = 12;
		leftPos = rect.right-12* DEFAULT_LIFE;
		rightPos = leftPos + 12*myLife;
		cdc.Rectangle(leftPos, topPos, rightPos, buttomPos);
		brush.DeleteObject();

		HFONT font2;
		font2 = CreateFont(8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(font);
		cdc.SetTextColor(RGB(0, 255, 0));
		cdc.TextOutW(rect.right - 12 * DEFAULT_LIFE - 45, 15, _T("ħ����"));
		CBrush magicBrush;
		magicBrush.CreateSolidBrush(RGB(0, 255, 0));//��ɫˢ
		cdc.SelectObject(&magicBrush);
		//���ħ��ֵ
		topPos = 15, buttomPos = 27;
		leftPos = rect.right - 12 * DEFAULT_LIFE;
		rightPos = leftPos + 12 * magicCount;
		cdc.Rectangle(leftPos, topPos, rightPos, buttomPos);
		magicBrush.DeleteObject();

		//���BossѪ��
		if (isBoss == TRUE) {
			CBrush bossBrush;
			bossBrush.CreateSolidBrush(RGB(128, 0, 128));//��ɫˢ
			cdc.SelectObject(&bossBrush);
			topPos = 2, buttomPos = 12;
			leftPos = rect.right / 2 - 100;
			rightPos = leftPos + bossBlood/(boss->life /10)*20;
			cdc.Rectangle(leftPos, topPos, rightPos, buttomPos);
			bossBrush.DeleteObject();
		}
		cdc.SelectObject(&oldBrush);//��ˢ�Ӹ�ԭԭ��������

		//���Ѫ���е���ϸѪֵ
		HFONT textFont;
		textFont = CreateFont(12, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(textFont);
		cdc.SetTextColor(RGB(255,255,255));
		str.Format(_T("%d/%d"), DEFAULT_LIFE, myLife);
		cdc.TextOutW(rect.right - 12 * DEFAULT_LIFE+12*4, 0, str);
		str.Format(_T("%d/%d"), DEFAULT_LIFE, magicCount);
		cdc.TextOutW(rect.right - 12 * DEFAULT_LIFE+12*4, 15, str);
		if (isBoss == TRUE) {
			str.Format(_T("%d/%d"), boss->life, bossBlood);
			cdc.TextOutW(rect.right / 2 - 20, 2, str);
		}

		//��ʾ��ǰ�ܷ����ĵ���
		HFONT toolFont;
		toolFont = CreateFont(24, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(toolFont);
		cdc.SetTextColor(RGB(255, 255, 255));
		if (magicCount > 0) {
			str.Format(_T("��C�ɴ򿪷�����"));
			cdc.TextOutW(0, rect.bottom - 100, str);
			str.Format(_T("��V������ս��"));
			cdc.TextOutW(0, rect.bottom - 70, str);
		}
		if (magicCount >= 10) {
			str.Format(_T("��X��ʹ��ս������"));
			cdc.TextOutW(0, rect.bottom - 40, str);
		}
	}//if

	if (isStop == FLAG_RESTART) {
		HFONT textFont;
		textFont = CreateFont(18, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(textFont);
		//����͸������
		cdc.SetBkMode(TRANSPARENT);
		cdc.SetTextColor(RGB(255, 255, 255));
		cdc.TextOutW(rect.right/2-150, rect.bottom/2-30, _T("�ۣ���ϲ����ͨ�أ��Ƿ����¿�ʼ��Y/N"));
	}
	else if (isStop == FLAG_STOP) {
		HFONT textFont;
		textFont = CreateFont(18 , 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		cdc.SelectObject(textFont);
		//����͸������
		cdc.SetBkMode(TRANSPARENT);
		cdc.SetTextColor(RGB(255, 255, 255));
		//��ʾ�����
		CString str;
		cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 - 30, _T("GAME OVER��"));
		str.Format(_T("���ĵ÷�Ϊ��%d"), myScore);
		cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 - 10, str);
		cdc.TextOutW(rect.right / 2 - 100, rect.bottom / 2 +10, _T("COME ON �����¿�ʼ��Y/N"));
	}

	//����ħ��ֵ
	if (nIDEvent == 5) {
		if (myplane != NULL&&isPause == 0) {
			//�����ֺ�ս������û�򿪣�ħ��ֵ����
			if (isProtect==FALSE&&isUpdate==FALSE) {
				magicCount++;
				if (magicCount > 10)
					magicCount = 10;
			}
			//�ж��Ƿ�򿪷�����
			if (isProtect == TRUE) {
				//����������ħ��ֵ�ݼ�
				magicCount --;
				if (magicCount <= 0) {
					magicCount = 0;
					isProtect = FALSE;
				}
			}
			//�ж��Ƿ�����ս��
			if (isUpdate == TRUE) {
				//ս��������ħ��ֵ�ݼ�
				magicCount--;
				if (magicCount <= 0) {
					magicCount = 0;
					isUpdate = FALSE;
					myplane->SetIsUpdate(isUpdate);
				}
			}
		}
	}

	// ������һ�ؽ���
	int pScore = PASS_SCORE + passNum * 5;
	// TODO��������
	//if (myplane != NULL && passScore >= 3 && isPause == 0&&isBoss==FALSE)
	if (myplane != NULL && passScore >= pScore && isPause == 0 && isBoss == FALSE)
	{
		//����Boss
		isBoss = TRUE;
		boss = new CBoss(1, rect.right, rect.bottom);
		boss->SetSpeed(BOSS_SPEED+passNum-1);
		boss->life = BOSS_LIFE + passNum * 50;//Boss��Ѫ��
		bossBlood= BOSS_LIFE + passNum * 50;//��ǰBossѪ��
		//Boss��������ͣ��Ϸ
		bossLoaded = FALSE;

		//��������Boss���ӵ�����Ƶ�ʣ���ǿBoss�ӵ�����Ƶ��
		KillTimer(3);
		SetTimer(3, 2000 - passNum * 180, NULL); 
	}

	//��ʾBoss
	if (myplane != NULL &&boss!=NULL&& isPause == 0 && isBoss == TRUE) {
		BOOL status = boss->Draw(&cdc,passNum, FALSE);
		if (status == TRUE)
			bossLoaded = TRUE;
	}

	if (isPass == 1)
	{
		isPass = FALSE;
		if (passNum ==10)//10��
		{
			//���³�ʼ������
			KillTimer(1);
			KillTimer(2);
			KillTimer(3);
			//KillTimer(4);
			KillTimer(5);
			myplane = new CMyPlane(FALSE);
			isPause = TRUE;
			
			isStop = FLAG_RESTART;
			//����
			CBitmap* tCache = cacheBitmap;
			cacheBitmap = new CBitmap;
			cacheBitmap->CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
			cdc.SelectObject(cacheBitmap);
			delete tCache;
		}//if
		else
		{
			KillTimer(1);
			KillTimer(2);
			KillTimer(3);
			//KillTimer(4);
			KillTimer(5);
			isPause = TRUE;	
			//������������
			int tScore = myScore + passScore;
			int tPassNum = passNum + 1;
			int tTest = test;
			int magic = magicCount;
			//���¿�ʼ��Ϸ
			Restart();
			myScore = tScore;
			passNum = tPassNum;
			magicCount = magic;
			test = tTest;
		}//else
	}//if

	//����������cdc�е��������͵�һ��������pDC�У����������Ļ��
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &cdc, 0, 0, SRCCOPY);
	//�ͷŶ���cdc
	cdc.DeleteDC();
	//�ͷŻ���λͼ
	cacheBitmap->DeleteObject();
	//�ͷ�һ��pDC
	ReleaseDC(pDC);
	CView::OnTimer(nIDEvent);
}

//���̰��¼���
void CPlaneWarView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (myplane != NULL && (GetKeyState(VK_UP) < 0 || GetKeyState('W') < 0) && isPause == 0) {
		//�Ϸ����
		int y = myplane->GetPoint().y - speed;
		if (y < 0)
			y = 0;
		myplane->SetPoint(myplane->GetPoint().x, y);
	}
	else if (myplane != NULL && (GetKeyState(VK_DOWN) < 0 || GetKeyState('S') < 0) && isPause == 0) {
		//�·����
		int y = myplane->GetPoint().y + speed;
		if (y >rect.bottom-1)
			y = rect.bottom -1;
		myplane->SetPoint(myplane->GetPoint().x, y);
	}
	else if (myplane != NULL && (GetKeyState(VK_LEFT) < 0 || GetKeyState('A') < 0) && isPause == 0 ) {
		//�����
		int x = myplane->GetPoint().x - speed;
		if (x < 0)
			x = 0;
		myplane->SetPoint(x, myplane->GetPoint().y);
	}
	else if (myplane != NULL && (GetKeyState(VK_RIGHT) < 0 || GetKeyState('D') < 0) && isPause == 0 ) {
		//�ҷ����
		int x = myplane->GetPoint().x + speed;
		if (x >rect.right - 1)
			x = rect.right - 1;
		myplane->SetPoint(x, myplane->GetPoint().y);
	}
	else if (myplane != NULL && (GetKeyState(VK_SPACE) < 0) && isPause == 0 && bossLoaded == TRUE) {
		//�ո�������ӵ�
		CBomb *Bomb1 = new CBomb(myplane->GetPoint().x+20, myplane->GetPoint().y, 1,isUpdate);
		PlaySound((LPCTSTR)IDR_WAV_BOMB, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		bombList.AddTail(Bomb1);
		CBomb *Bomb2 = new CBomb(myplane->GetPoint().x + PLANE_WIDTH-50, myplane->GetPoint().y, 1, isUpdate);
		bombList.AddTail(Bomb2);
		//�ӵ��Զ����У���Timer�л���
	}
	else if (myplane != NULL&&GetKeyState('Z') < 0)
	{
		//��ͣ��Ϸ����ʼ��Ϸ
		if (isPause == TRUE)
			isPause = FALSE;
		else {
			Pause();
		} 
	}//if
	else if (myplane != NULL&&GetKeyState('X') < 0 && isPause == 0 && bossLoaded == TRUE)
	{
		//ս��������
		if (magicCount >= 10) {
			magicCount -= 10;
				//��յл�
				POSITION enemyPos, enemyTemp;
				for (enemyPos = enemyList.GetHeadPosition(); (enemyTemp = enemyPos) != NULL;)
				{
					enemy = (CEnemy *)enemyList.GetNext(enemyPos);
					//����ը������ӵ���ը������
					CExplosion *explosion = new CExplosion((enemy->GetPoint().x + ENEMY_WIDTH / 2), (enemy->GetPoint().y + ENEMY_HEIGHT / 2));
					explosionList.AddTail(explosion);
					PlaySound((LPCTSTR)IDR_WAV_DAZHAO, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);

					//ɾ���л�
					enemyList.RemoveAt(enemyTemp);
					delete  enemy;
					//���ӵ÷�
					passScore++;
				}//for
			if(isBoss==TRUE) {
				//����ը������ӵ���ը������
				CExplosion *explosion = new CExplosion(boss->GetPoint().x + BOSS_WIDTH / 2, boss->GetPoint().y + BOSS_HEIGHT / 2);
				explosionList.AddTail(explosion);
				PlaySound((LPCTSTR)IDR_WAV_DAZHAO, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				bossBlood -= 50;
				if (bossBlood <= 0) {
					//boss��������
					//���صı�־����
					delete boss;
					boss = NULL;
					//���صı�־����
					isPause = TRUE;
					CMyPlane* temp = myplane;
					myplane = new CMyPlane(FALSE);
					delete  temp;
					temp = NULL;
					isPass = 1;
					isBoss = FALSE;
				}
			}
			 //��յл��ڵ�
			POSITION ballPos, ballTemp;
			for (ballPos = ballList.GetHeadPosition(); (ballTemp = ballPos) != NULL;)
			{
				ball = (CBall *)ballList.GetNext(ballPos);
				//ɾ���л��ڵ�
				ballList.RemoveAt(ballTemp);
				delete  ball;
			}//for
		}
	}//if
	else if (myplane != NULL&&GetKeyState('C') < 0 && isPause == 0) {
		//����������
		isProtect = TRUE;
		PlaySound((LPCTSTR)IDR_WAV_PROTECT, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
	}
	else if (myplane != NULL&&GetKeyState('V') < 0 && isPause == 0) {
		//ս������
		isUpdate = TRUE;
		myplane->SetIsUpdate(isUpdate);
		PlaySound((LPCTSTR)IDR_WAV_UPDATE, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
	}
	else if (GetKeyState('Y') < 0 ) {
		if (isStop == FALSE) {
			//�޵�ģʽ����
			if (test == FALSE)
				test = TRUE;
			else test = FALSE;
		}
		else {
			isStop = FALSE;
			Restart();
		}
	}
	else if (GetKeyState('N') < 0) {
		if (isStop!=FALSE) {
			MyDialog dialog;
			dialog.DoModal(); 
		}
	}
	//���ո������Ϸ
	if (isStarted == FALSE && (GetKeyState(VK_SPACE) < 0)) {
		isStarted = TRUE;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//����ƶ�����������ս��λ��
void CPlaneWarView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (myplane!=NULL && isPause == 0 ) {
		//��������Ϸ����
		myplane->SetPoint(point.x,point.y);
	}
	CView::OnMouseMove(nFlags, point);
}

//��������������
void CPlaneWarView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (myplane!=NULL&&isPause == 0 && bossLoaded == TRUE)
	{
		CBomb *Bomb1 = new CBomb(myplane->GetPoint().x, myplane->GetPoint().y, 1, isUpdate);
		PlaySound((LPCTSTR)IDR_WAV_BOMB, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		bombList.AddTail(Bomb1);
		CBomb *Bomb2 = new CBomb(myplane->GetPoint().x + BOMB_DISTANCE, myplane->GetPoint().y, 1, isUpdate);
		bombList.AddTail(Bomb2);
		//�ӵ��Զ����У���Timer�л���
	}
	if (isStarted == FALSE) {
		isStarted = TRUE;
	}

	CView::OnLButtonDown(nFlags, point);
}

//����Ҽ�����
void CPlaneWarView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	/*ClientToScreen(&point);
	OnContextMenu(this, point);*/

	/*myplane = new CMyPlane();
	myplane->Draw(GetDC(), TRUE);*/
}

//��������

//��������
void CPlaneWarView::OnDestroy()
{
	// ����ָ����Դ
	if (myplane != NULL)
		delete myplane;
	if (boss != NULL)
		delete boss;
	/*if (enemy != NULL)
		delete enemy;
	if (bomb != NULL)
		delete bomb;
	if (ball != NULL)
		delete ball;
	if (explosion != NULL)
		delete explosion;*/

		//�ͷ��ڴ���Դ
	scene.ReleaseScene();

	CView::OnDestroy();
}

//��Ϸ���¿�ʼ
void CPlaneWarView::Restart()
{
	// TODO: �ڴ˴������Ϸ���¿�ʼ��ʼ������
	//ս�����¼���
	myplane = new CMyPlane(FALSE);

	//��յл�����
	if (enemyList.GetCount() > 0)
		enemyList.RemoveAll();
	//���ս������
	if (meList.GetCount() > 0)
		meList.RemoveAll();
	//���ս���ӵ�����
	if (bombList.GetCount() > 0)
		bombList.RemoveAll();
	//��յл�ը������
	if (ballList.GetCount() > 0)
		ballList.RemoveAll();
	//��ձ�ը����
	if (explosionList.GetCount() > 0)
		explosionList.RemoveAll();
	//���Ѫ���б�
	if (bloodList.GetCount() > 0)
		bloodList.RemoveAll();

	//�������³�ʼ��
	myLife = DEFAULT_LIFE;
	lifeNum = DEFAULT_LIFE_COUNT;
	myScore = 0;
	passScore = 0;
	passNum = DEFAULT_PASS;
	isPass = 0;
	isPause = 0;
	lifeCount = 1;
	magicCount = 0;
	bloodExist = FALSE;
	bossBlood = BOSS_LIFE;
	isBoss = FALSE;
	bossLoaded = TRUE;
	isProtect = FALSE;
	isUpdate = FALSE;
	test = FALSE;
	boss = NULL;
	//isStarted = FALSE;
	SetMyTimer();
}

//��Ϸ��ͣ
void CPlaneWarView::Pause()
{
	// TODO: �ڴ˴������Ϸ��ͣ����
	isPause = TRUE;
	Sleep(1000);
}

// ����ֵ���㣬��Ϸ����
void CPlaneWarView::gameOver(CDC* pDC,CDC& cdc,CBitmap* cacheBitmap)
{
	//������Ϸ����
	//�ͷż�ʱ��
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	//KillTimer(4);
	KillTimer(5);
	//�������÷�
	myScore += passScore;
	//������Ϸ��������
	PlaySound((LPCTSTR)IDR_WAV_GAMEOVER, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
	//����
	CBitmap* tCache = cacheBitmap;
	cacheBitmap = new CBitmap;
	cacheBitmap->CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	cdc.SelectObject(cacheBitmap);
	//�ڴ��г�����ʱͼ��Ļ���λͼ
	delete tCache;
	isStop = FLAG_STOP;
}

//���ü�ʱ��
void CPlaneWarView::SetMyTimer()
{
	SetTimer(1, 17, NULL);//ˢ�½��涨ʱ��
	SetTimer(2, 400-passNum*30, NULL);//�����л���ʱ��
	SetTimer(3, 2000- passNum * 100, NULL);//�����л��ڵ�Ƶ��
	
	SetTimer(5, 2000, NULL);//����ħ��ֵ�仯Ƶ��
}

//void CPlaneWarView::OnClose()
//{
//	isPause = TRUE;
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	KillTimer(1);
//	KillTimer(2);
//	KillTimer(3);
//	KillTimer(4);
//	KillTimer(5 );
//	CView::OnClose();
//}
