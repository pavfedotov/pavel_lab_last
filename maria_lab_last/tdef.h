
#include <math.h>
#include <stdio.h>
#include <windows.h>

#define S_DIMS 3
#define ALL_PT         30         // число  точек 

// цвета объектов
#define  RED           0
#define  GREEN         1
#define  BLUE          2
#define  WHITE         3
#define  SUN           4
#define  EARTH           5
#define  MARS           6
#define  MERK           7
#define  VEN           8


 // координаты
struct CVect {
	double x, y;
};


// матрица преобразования 
struct CMatr {
	double m[S_DIMS][S_DIMS];
};


void Delay(UINT nMiliseconds);
void trans_coor(CVect* pvOld, CVect* pvNew, int all_pt, CMatr& mpr);
CMatr  make_matr_pr(RECT& cp);
void draw_polygon(HDC hDc, CVect* pVect, int nPoints);


// обнуление матрицы
void MatrZero(CMatr& m_);

// установка единичной матрицы
void MatrIdentity(CMatr& m_);

// установка матрицы масштабирования
void MatrScale(CMatr& m_, double kx, double ky);

// установка матрицы перемещения
void MatrTransl(CMatr& m_,
	const CVect& v_);

// установка матрицы поворота
void MatrRot(CMatr& m_,
	const double& dAng_);




// умножение матриц
CMatr operator * (const CMatr& m1_,
	const CMatr& m2_);

// умножение вектора на матрицу
CVect operator * (const CVect& v_,
	const CMatr& m_);

// печать в строку
void MatrPrint(const CMatr& m1_, LPSTR pcBuff);
