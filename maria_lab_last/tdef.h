
#include <math.h>
#include <stdio.h>
#include <windows.h>

#define S_DIMS 3
#define ALL_PT         30         // �����  ����� 

// ����� ��������
#define  RED           0
#define  GREEN         1
#define  BLUE          2
#define  WHITE         3
#define  SUN           4
#define  EARTH           5
#define  MARS           6
#define  MERK           7
#define  VEN           8


 // ����������
struct CVect {
	double x, y;
};


// ������� �������������� 
struct CMatr {
	double m[S_DIMS][S_DIMS];
};


void Delay(UINT nMiliseconds);
void trans_coor(CVect* pvOld, CVect* pvNew, int all_pt, CMatr& mpr);
CMatr  make_matr_pr(RECT& cp);
void draw_polygon(HDC hDc, CVect* pVect, int nPoints);


// ��������� �������
void MatrZero(CMatr& m_);

// ��������� ��������� �������
void MatrIdentity(CMatr& m_);

// ��������� ������� ���������������
void MatrScale(CMatr& m_, double kx, double ky);

// ��������� ������� �����������
void MatrTransl(CMatr& m_,
	const CVect& v_);

// ��������� ������� ��������
void MatrRot(CMatr& m_,
	const double& dAng_);




// ��������� ������
CMatr operator * (const CMatr& m1_,
	const CMatr& m2_);

// ��������� ������� �� �������
CVect operator * (const CVect& v_,
	const CMatr& m_);

// ������ � ������
void MatrPrint(const CMatr& m1_, LPSTR pcBuff);
