#ifndef MYMATH_H
#define MYMATH_H

#include <iostream>
#include <math.h>
#include "assert.h"
using namespace std;

class Line;
class Vector2
{
private:
    float x;
    float y;

public:
    Vector2(float x = 0.0f, float y = 0.0f);
    ~Vector2();

    // get and set methods
    float getX() const;
    float getY() const;
    void setXY(float, float);

    // override operators
    Vector2 operator+(Vector2 &) const;
    Vector2 operator-(Vector2 &) const;
    Vector2 operator*(float f) const;
    Vector2 operator/(float f) const;
    float dotProduct(Vector2 &) const;
    // Vector2 crossProduct(Vector2 &);

    Vector2& operator+=(Vector2 &);
    Vector2& operator-=(Vector2 &);
    Vector2& operator*=(float f);
    Vector2& operator/=(float f);
    Vector2 operator-();

    float Length() const; // length
    float distanceBetween(Vector2 &) const;

    Vector2 getNormalize() const;
    Vector2 getVertical() const;
    friend Line GetLine(const Vector2& a,const Vector2& b);
    friend float PointToLineDistance(const Vector2& point,const Line& line);
};

//use for qt!!!!!!!!!!!!
inline Vector2 specialAntiRotate90(const Vector2& v)
{
    return Vector2(v.getY(),-v.getX());
}

inline Vector2 AntiRotate90(const Vector2& v)
{
    return Vector2(-v.getY(),v.getX());
}

class Vector3
{
private:
    float x,y,z;
public:
    Vector3(float x=0.0f,float y=0.0f,float z=0.0f);
    Vector3(const Vector2& v);
    ~Vector3();
    float operator[](int i) const;
    void setX(float x);
    void setY(float y);
    void setZ(float z);

    float getX() const;
    float getY() const;
    void setXY(float, float);

    Vector3 operator+(const Vector3& v) const;
    Vector3 operator-(const Vector3& v) const;
    Vector3& operator+=(const Vector3& v);
    Vector3& operator-=(const Vector3& v);
    Vector3 operator*(float f) const;
    Vector3 operator/(float f) const;
    Vector3& operator*=(float f);
    Vector3& operator/=(float f);
    Vector3 operator-() const;

    friend Vector3 operator*(float f,const Vector3& v);
    float Length2() const;
    float Length() const;
    void Normalize();
    float DistanceTo(const Vector3& v) const;

    friend float DotProduct(const Vector3& v1,const Vector3& v2);
    friend Vector3 CrossProduct(const Vector3& v1,const Vector3& v2);
    friend float DistanceBetween(const Vector3& v1,const Vector3& v2);
    friend Vector3 GetNormalize(const Vector3& v);
};

class Line
{
private:
    float k;
    float b;
public:
    Line(float k=0, float b=0);
    Line(const Vector2& a,const Vector2& b);
    ~Line();

    float getK() const;
    float getB() const;

    void Move(float dx, float dy);
    void Rotate(const Vector2& a, float angle);
    bool Contains(const Vector2& a);
    bool operator ==(const Line& y) const;
    bool operator !=(const Line& y) const;
    friend Line GetLine(const Vector2& a,const Vector2& b);
    friend float PointToLineDistance(const Vector2& point,const Line& line);
};


class Matrix3
{
private:
    float e[9];
public:
    Matrix3(float e11,float e12,float e13,\
            float e21,float e22,float e23,\
            float e31,float e32,float e33);
    float operator[](int i) const;
};

class Quaternion
{
private:
    float n;
    Vector3 v;
public:
    Quaternion();
    Quaternion(const float n,float vx,float vy,float vz);
    Quaternion(const float n,const Vector3& v);

    float Mag2() const;
    float Mag() const;
    void Normalize();
    float getScalar() const;
    Vector3 getVector3() const;
    void setScalar(float s);
    void setVector3(const Vector3& v);
    Quaternion& operator +=(const Quaternion& q);
    Quaternion& operator -=(const Quaternion& q);
    Quaternion& operator *=(const Quaternion& q);
    Quaternion& operator *=(const Vector3& v);
    Quaternion& operator *=(const float d);
    Quaternion& operator /=(const float d);

    Quaternion  operator -() const;

    friend Quaternion operator +(const Quaternion& u, const Quaternion& v);
    friend Quaternion operator -(const Quaternion& u, const Quaternion& v);
    friend Quaternion operator *(const Quaternion& u, const Quaternion& v);
    friend Quaternion operator *(const float s,const Quaternion& u);
    friend Quaternion operator *(const Quaternion& u, const float s);
    friend Quaternion operator *(const Quaternion& u,const Vector3& v);
    friend Quaternion operator *(const Vector3& v,const Quaternion& u);
    friend Quaternion operator /(const Quaternion& u, const float s);

    Matrix3 MakeMatrix3FromQ();
};



#endif // MYMATH_H
