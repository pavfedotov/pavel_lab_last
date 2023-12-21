
#include "tdef.h"


/*--------------------------------*/
/*  Описание класса GO_SHAPE      */
/*--------------------------------*/
class GO_SHAPE
{

	CMatr  ms, mr, mt;

public:

	double dx, dy, ang, k_scale_x, k_scale_y, dim_x;
	int    all_pt_shape, color;

	CVect  vt, kvadro[ALL_PT], kvadro_win[ALL_PT];

	// методы 
	GO_SHAPE(CVect[], int, double, double,
		double, double, double, double
		, double, int, double);

	void move(void);
};

//--------------------------------
// Конструктор класса GO_SHAPE
//--------------------------------

GO_SHAPE::GO_SHAPE(CVect  shape[], int all_pt,
	double dx1, double dy1,
	double ang1,
	double kx, double ky,
	double x_start,
	double y_start,
	int    color_set,
	double x_len
)
{
	int i;

	dx = dx1;
	dy = dy1;
	ang = ang1;
	k_scale_x = kx;
	k_scale_y = ky;
	dim_x = x_len;

	all_pt_shape = all_pt;
	vt.x = x_start;
	vt.y = y_start;
	color = color_set;

	for (i = 0; i < all_pt_shape; i++)
		kvadro[i] = shape[i];

}

/****************************************************/
/*             GO_SHAPE::move                       */
/*             ==============                       */
/*  Перемещение  фигуры  на один шаг                */
/****************************************************/

void GO_SHAPE::move()
{
	CMatr  msum;

	extern HDC hdc;

	extern CMatr mpr;

	extern HBRUSH 	hbr[], hbr_prv;



	MatrScale(ms, k_scale_x, k_scale_y);
	MatrRot(mr, ang);
	MatrTransl(mt, vt);

	msum = ms * mr * mt * mpr;

	for (int i = 0; i < all_pt_shape; i++)
		kvadro_win[i] = kvadro[i] * msum;

	hbr_prv = (HBRUSH)SelectObject(hdc, hbr[color]);
	draw_polygon(hdc, kvadro_win, 4);

	

	if (vt.x > dim_x || vt.x < 0)
	{
		dx = -dx;
		dy = -dy;
	}

	vt.x += dx;
	vt.y += dy;

	SelectObject(hdc, hbr_prv);

}


// обнуление матрицы
void MatrZero(CMatr& m_)
{
	ZeroMemory(&m_, sizeof(m_));
}  //func MatrZero

 // установка единичной матрицы
void MatrIdentity(CMatr& m_)
{
	MatrZero(m_);
	m_.m[0][0] = m_.m[1][1] = m_.m[2][2] = 1;
}  //func MatrIdentity

// установка матрицы масштабирования
void MatrScale(CMatr& m_, double kx, double ky)
{
	MatrZero(m_);
	m_.m[0][0] = kx;
	m_.m[1][1] = ky;
	m_.m[2][2] = 1;
}  //func MatrScale

 // установка матрицы перемещения
void MatrTransl(CMatr& m_,
	const CVect& v_)
{
	MatrIdentity(m_);
	m_.m[2][0] = v_.x;
	m_.m[2][1] = v_.y;
}  //func MatrTransl

 // установка матрицы поворота
void MatrRot(CMatr& m_,
	const double& dAng_)
{
	MatrIdentity(m_);
	m_.m[0][0] = m_.m[1][1] = cos(dAng_);
	m_.m[1][0] = -sin(dAng_);
	m_.m[0][1] = sin(dAng_);
}  //func MatrRot


 // умножение матриц
CMatr operator * (const CMatr& m1_,
	const CMatr& m2_)
{
	int i, j, k;
	CMatr mRes;
	MatrZero(mRes);
	for (i = 0; i < S_DIMS; i++)
		for (j = 0; j < S_DIMS; j++)
			for (k = 0; k < S_DIMS; k++)
				mRes.m[i][j] += m1_.m[i][k] * m2_.m[k][j];
	return mRes;
}  //operator * (CMatr, CMatr)


 // умножение вектора на матрицу
CVect operator * (const CVect& v_,
	const CMatr& m_)
{
	CVect vRes;
	vRes.x = v_.x * m_.m[0][0] + v_.y * m_.m[1][0] + m_.m[2][0];
	vRes.y = v_.x * m_.m[0][1] + v_.y * m_.m[1][1] + m_.m[2][1];
	return vRes;
}  //operator * (CVect, CMatr)

//matr MatrPrint


