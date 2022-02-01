#ifndef _VTGL_MATH_H_
#define _VTGL_MATH_H_

#include <math.h>
#include <stdio.h>

#define VTGL_PI    ((float)  3.141592654f)
#define VTGL_1BYPI ((float)  0.318309886f)

#define VTGL_ToRadian( degree ) ((degree) * (VTGL_PI / 180.0f))
#define VTGL_ToDegree( radian ) ((radian) * (180.0f / VTGL_PI))

bool EqFloat(float lhs, float rhs,float fEpsilon);

struct VTVector2D
{
public:
	float x,y;
public:
    VTVector2D();
    VTVector2D( const float * );
    VTVector2D( const VTVector2D& );
    VTVector2D( float _x, float _y );

    operator float* ();
    operator const float* () const;

    VTVector2D& operator += ( const VTVector2D& );
    VTVector2D& operator -= ( const VTVector2D& );
    VTVector2D& operator *= ( float );
    VTVector2D& operator /= ( float );

    VTVector2D operator + ()const;
    VTVector2D operator - ()const;

    VTVector2D &operator + ( const VTVector2D& ) const;
    VTVector2D &operator - ( const VTVector2D& ) const;
    VTVector2D &operator * ( float ) const;
    VTVector2D &operator / ( float ) const;

    friend VTVector2D &operator * ( float, const VTVector2D& );

	float Length()const;

    bool operator == ( const VTVector2D& ) const;
    bool operator != ( const VTVector2D& ) const;

};


struct VTVector3D
{
public:
	float x,y,z;
public:
    VTVector3D();//Конструктор по умолчанию
    VTVector3D( const float * );//Конструктор принимающий вектор как массив из последовательности координат x y z
    VTVector3D( const VTVector3D& );//Конструктор копии
    VTVector3D( float _x, float _y,float _z );//Конструктор с самими координатами

    operator float* ();//Оператор приведения к типу указателя на float
    operator const float* () const;// Тоже самое 

    VTVector3D& operator += ( const VTVector3D& );//Оператор сложения вектора с присваиванием 
    VTVector3D& operator -= ( const VTVector3D& );//Вычитание вектора с присваиванием
    VTVector3D& operator *= ( float );//Умножение на число вектора с присваиванием
    VTVector3D& operator /= ( float );//Деление на число с присваиванием

    VTVector3D operator + ()const;//Знак + перед вектором
    VTVector3D operator - ()const;//Поворачиваем вектор (со знаком -)

    VTVector3D operator + ( const VTVector3D& ) const;//Простое сложение векторов
    VTVector3D operator - ( const VTVector3D& ) const;//Простое вычитание векторов
    VTVector3D operator * ( float ) const;//Простое умножение на число вектора
    VTVector3D operator / ( float ) const;//Простое деление на число вектора

    friend VTVector3D operator * ( float, const VTVector3D& );//Умножение вектора на число которое слева
	friend float operator * ( const VTVector3D&, const VTVector3D& );//Скалярное произведение

	float Length()const;//Длина вектора 
	bool Normalize();//Нормализация вектора
    bool Cross(const VTVector3D &,const VTVector3D &);//Векторное произведение векторов

    bool operator == ( const VTVector3D& ) const;//Сравнение вектора с вектором текущим (равно)
    bool operator != ( const VTVector3D& ) const;//Тоже самое только не равно

};

class VTMatrix4
{
public:
union
	{
 struct
 {
	        float        f_11, f_12, f_13, f_14;
            float        f_21, f_22, f_23, f_24;
            float        f_31, f_32, f_33, f_34;
            float        f_41, f_42, f_43, f_44;
 };
 float m[4][4];
	};
public:
    VTMatrix4();
    explicit VTMatrix4( float * );
    VTMatrix4( const VTMatrix4& );
    explicit VTMatrix4( float f11, float f12, float f13, float f14,
                float f21, float f22, float f23, float f24,
                float f31, float f32, float f33, float f34,
				float f41, float f42, float f43, float f44);
    //VTMatrix4 &operator=( float * pfMatrix);

    // access grants
    float operator() ( unsigned int Row, unsigned int Col ) const;
	float &operator() ( unsigned int Row, unsigned int Col );

    // casting operators
    //operator float* ();
    //operator const float* () const;

    // assignment operators
    VTMatrix4& operator *= ( const VTMatrix4& );
    VTMatrix4& operator += ( const VTMatrix4& );
    VTMatrix4& operator -= ( const VTMatrix4& );
    VTMatrix4& operator *= ( float );
    VTMatrix4& operator /= ( float );

    // unary operators
    VTMatrix4 operator + () const;
    VTMatrix4 operator - () const;

    // binary operators
	VTVector3D operator * ( const VTVector3D& ) const;/// По ссылке не передавать , объект разрушается после выхода из функции !!!
    VTMatrix4 operator * ( const VTMatrix4& ) const;/// По ссылке не передавать , объект разрушается после выхода из функции !!!
    VTMatrix4 &operator + ( const VTMatrix4& ) const;/// По ссылке не передавать , объект разрушается после выхода из функции !!!
    VTMatrix4 &operator - ( const VTMatrix4& ) const;/// По ссылке не передавать , объект разрушается после выхода из функции !!!
    VTMatrix4 &operator * ( float ) const;/// По ссылке не передавать , объект разрушается после выхода из функции !!!
    VTMatrix4 &operator / ( float ) const;/// По ссылке не передавать , объект разрушается после выхода из функции !!! (распечатать бы себе на стену ))) )

	bool Fill(float * pfMatrix);

    friend VTMatrix4 &operator * ( float, const VTMatrix4& );

    //bool operator == ( const VTMatrix3& ) const;
    //bool operator != ( const VTMatrix3& ) const;
};


VTMatrix4 &VTGL_TranslateXYZ(VTMatrix4 * pOut,float x,float y,float z);
VTMatrix4 &VTGL_RotationX(VTMatrix4 * pOut,float fAngle);
VTMatrix4 &VTGL_RotationY(VTMatrix4 * pOut,float fAngle);
VTMatrix4 &VTGL_RotationZ(VTMatrix4 * pOut,float fAngle);
VTMatrix4 &VTGL_RotationAxis(VTMatrix4 * pOut,VTVector3D * pAxis,float fAngle);

VTMatrix4 &VTGL_Perspective(VTMatrix4 * pOut,float fFOV,float fAspect, float fZNear,float fZFar);


#endif