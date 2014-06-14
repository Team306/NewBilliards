#include "MyMath.h"
//Vector2
//============================================================================
Vector2::Vector2(float x, float y)
    : x(x), y(y)
{
//	this->x = x;
//	this->y = y;
}

Vector2::~Vector2()
{
}

// get and set methods
float Vector2::getX() const
{
    return x;
}

float Vector2::getY() const
{
    return y;
}

void Vector2::setXY(float x, float y)
{
    this->x = x;
    this->y = y;
}

// override operators
Vector2 Vector2::operator+(Vector2& v) const
{
    Vector2 result;
    result.x = this->x + v.getX();
    result.y = this->y + v.getY();
    return result;
}

Vector2 Vector2::operator-(Vector2& v) const
{
    Vector2 opposite(-v.getX(), -v.getY());
    Vector2 result = *this + opposite;
    return result;
}

Vector2 Vector2::operator*(float f) const
{
    Vector2 result = *this;
    result.x *= f;
    result.y *= f;
    return result;
}

float Vector2::dotProduct(Vector2& v) const
{
    float result = this->x * v.getX() + this->y * v.getY();
    return result;
}

Vector2& Vector2::operator+=(Vector2& v)
{
    //Vector2 result = *this + v;
    this->x += v.getX();
    this->y += v.getY();
    return *this;
}

Vector2& Vector2::operator-=(Vector2& v)
{
    //Vector2 result = *this - v;
    this->x += v.getX();
    this->y += v.getY();
    return *this;
}

Vector2& Vector2::operator*=(float f)
{
    this->x*=f;
    this->y*=f;
    return *this;
}

Vector2 Vector2::operator/(float f) const
{
    assert(f!=0.0f);
    return Vector2(this->x/f,this->y/f);
}

Vector2& Vector2::operator/=(float f)
{
    assert(f!=0.0f);
    this->x/=f;
    this->y/=f;
    return *this;
}

float Vector2::Length() const
{
    return sqrt(x * x + y * y);
}

float Vector2::distanceBetween(Vector2& v) const
{
    Vector2 distance = (*this) - v;
    return distance.Length();
}

Vector2 Vector2::getNormalize() const
{
    Vector2 result(x / Length(), y / Length());
    return result;
}

Vector2 Vector2::getVertical() const
{
    Vector2 result(-y, x);
    return result;
}

//Vector3
//================================================================================
Vector3::Vector3(float x,float y,float z)
{
    this->x=x;
    this->y=y;
    this->z=z;
}

Vector3::Vector3(const Vector2& v)
{
    this->x=v.getX();
    this->y=v.getY();
    this->z=0.0f;
}


Vector3::~Vector3(){}

float Vector3::operator[](int i) const
{
    assert(i>=0 && i<=2);
    if(i==0) return this->x;
    else if(i==1) return this->y;
    else return this->z;
}

void Vector3::setX(float x)
{
    this->x=x;
}

void Vector3::setY(float y)
{
    this->y=y;
}
void Vector3::setZ(float z)
{
    this->z=z;
}

float Vector3::getX() const
{
    return this->x;
}

float Vector3::getY() const
{
    return this->y;
}

void Vector3::setXY(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector3 Vector3::operator+(const Vector3& v) const
{
    return Vector3(this->x+v[0],this->y+v[1],this->z+v[2]);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
    return Vector3(this->x-v[0],this->y-v[1],this->z-v[2]);
}

Vector3& Vector3::operator+=(const Vector3& v)
{
    this->x+=v[0];
    this->y+=v[1];
    this->z+=v[2];
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
    this->x-=v[0];
    this->y-=v[1];
    this->z-=v[2];
    return *this;
}

Vector3 Vector3::operator*(float f) const
{
    return Vector3(this->x*f,this->y*f,this->z*f);
}

Vector3& Vector3::operator*=(float f)
{
    this->x*=f;
    this->y*=f;
    this->z*=f;
    return *this;
}

Vector3 Vector3::operator/(float f) const
{
    assert(f!=0.0f);
    return Vector3(this->x/f,this->y/f,this->z/f);
}

Vector3& Vector3::operator/=(float f)
{
    assert(f!=0.0f);
    this->x/=f;
    this->y/=f;
    this->z/=f;
    return *this;
}

Vector3 Vector3::operator-()
{
    return Vector3(-this->x,-this->y,-this->z);
}

float Vector3::Length2() const
{
    return (this->x * this->x)+(this->y * this->y)+(this->z * this->z);
}

float Vector3::Length() const
{
    float L=this->Length2();
    if(L>0.0f)
        return sqrt(this->Length2());
    else
        return 0.0f;
}

void Vector3::Normalize()
{
    float L=this->Length();
    if(L>0.0f)
    {
        (*this) *= (1/L);
    }
}

float Vector3::DistanceTo(const Vector3& v) const
{
    return sqrt( (this->x-v[0])*(this->x-v[0]) \
                 +(this->y-v[1])*(this->y-v[1]) \
                 +(this->z-v[2])*(this->z-v[2]) );
}

float DotProduct(const Vector3& v1,const Vector3& v2)
{
    return (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2]);
}

Vector3 CrossProduct(const Vector3& v1,const Vector3& v2)
{
    return Vector3(v1[1]*v2[2] - v1[2]*v2[1],
        v1[2]*v2[0] - v1[0]*v2[2],
        v1[0]*v2[1] - v1[1]*v2[0]);
}

float DistanceBetween(const Vector3& v1,const Vector3& v2)
{
    return sqrt( (v1[0]-v2[0])*(v1[0]-v2[0]) \
                 +(v1[1]-v2[1])*(v1[1]-v2[1]) \
                 +(v1[2]-v2[2])*(v1[2]-v2[2]) );
}

Vector3 GetNormalize(const Vector3& v)
{
    Vector3 res=v;
    res.Normalize();
    return res;
}


//Line
//===============================================================================
Line::Line(float k, float b)
{
    this->k=k;
    this->b=b;
}

Line::Line(const Vector2& pa,const Vector2& pb)
{
    assert(pa.getX()!=pb.getX());

    //(k,b)
    this->k=(pa.getY()-pb.getY())/(pa.getX()-pb.getX());
    this->b=pa.getY()-k*pa.getX();
}

Line::~Line(){}

float Line::getK() const
{
    return this->k;
}

float Line::getB() const
{
    return this->b;
}

void Line::Move(float dx, float dy)
{
     this->b = this->b+ dy - this->k * dx;
}

void Line::Rotate(const Vector2& a, float angle)
{
     this->k = tan(atan(k) + angle);
     this->b = a.getY() - a.getX();
}

bool Line::Contains(const Vector2& a)
{
     return (a.getY() == this->k * a.getX() + this->b);
}

bool Line::operator ==(const Line& y)
{
     return (this->k == y.getK()) && (this->b == y.getB());
}

bool Line::operator !=(const Line& y)
{
     return (this->k != y.getK()) || (this->b != y.getB());
}

Line GetLine(const Vector2& pa,const Vector2& pb)
{
    assert(pa.getX()!=pb.getX());

    //(k,b)
    float k=(pa.getY()-pb.getY())/(pa.getX()-pb.getX());
    float b=pa.getY()-k*pa.getX();
    return Line(k,b);
}

float PointToLineDistance(const Vector2& point,const Line& line)
{
    return fabs(line.getK()*point.getX()-point.getY()+line.getB()) \
            /sqrt(line.getK()*line.getK()+1);
}
