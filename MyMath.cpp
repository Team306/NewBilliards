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
    this->x += v.getX();
    this->y += v.getY();
    return *this;
}

Vector2& Vector2::operator-=(Vector2& v)
{
    this->x -= v.getX();
    this->y -= v.getY();
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

Vector2 Vector2::operator-()
{
    return Vector2(-this->x,-this->y);
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
Vector3 operator*(float f,const Vector3& v)
 {
     return v*f;
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

Vector3 Vector3::operator-() const
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

bool Line::operator ==(const Line& y) const
{
     return (this->k == y.getK()) && (this->b == y.getB());
}

bool Line::operator !=(const Line& y) const
{
     return (this->k != y.getK()) || (this->b != y.getB());
}

Line GetLine(const Vector2& pa,const Vector2& pb)
{
    assert(pa.x!=pb.x);

    //(k,b)
    float k=(pa.y-pb.y)/(pa.y-pb.y);
    float b=pa.y-k*pa.x;
    return Line(k,b);
}

float PointToLineDistance(const Vector2& point,const Line& line)
{
    return fabs(line.k*point.x-point.y+line.b) \
            /sqrt(line.k*line.k+1);
}

//Matrix3
//===============================================================================
Matrix3::Matrix3(float e11=1,float e12=0,float e13=0,\
        float e21=0,float e22=1,float e23=0,\
        float e31=0,float e32=0,float e33=1)
{
    this->e[0]=e11;this->e[1]=e12;this->e[2]=e13;
    this->e[3]=e21;this->e[4]=e22;this->e[5]=e23;
    this->e[6]=e31;this->e[7]=e32;this->e[8]=e33;
}

float Matrix3::operator[](int i) const
{
    assert(i>=0 && i<=8);
    return this->e[i];
}

//Quaternion
//===============================================================================
Quaternion::Quaternion()
{
    this->n=0;
    this->v=Vector3(0,0,0);
}
Quaternion::Quaternion(const float n,float vx,float vy,float vz)
{
    this->n=n;
    this->v=Vector3(vx,vy,vz);
}

Quaternion::Quaternion(const float n,const Vector3& v)
{
    this->n=n;
    this->v=v;
}

float Quaternion::Mag2() const
{
    return (this->n*this->n+this->v.Length2());
}

float Quaternion::Mag() const
{
    float m=this->Mag2();
    if(m!=0)
        return sqrt(this->Mag2());
    else
        return 0;
}

void Quaternion::Normalize()
{
    float m=this->Mag();
    if(m!=0)
    {
        this->n/=m;
        this->v/=m;
    }
}

float Quaternion::getScalar() const
{
    return this->n;
}

Vector3 Quaternion::getVector3() const
{
    return this->v;
}

void Quaternion::setScalar(float s)
{
    this->n=s;
}

void Quaternion::setVector3(const Vector3& v)
{
    this->v=v;
}

Quaternion& Quaternion::operator+=(const Quaternion& q)
{
    this->n+=q.getScalar();
    this->v+=q.getVector3();
    return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& q)
{
    this->n-=q.n;
    this->v-=q.v;
    return *this;
}

Quaternion& Quaternion::operator*=(const float d)
{
    this->n*=d;
    this->v*=d;
    return *this;
}

Quaternion& Quaternion::operator *=(const Quaternion& q)
{
    *this=(*this)*q;
    return *this;
}

Quaternion& Quaternion::operator *=(const Vector3& v)
{
    *this=(*this)*Quaternion(0,v);
    return *this;
}

Quaternion& Quaternion::operator/=(const float d)
{
    assert(d!=0);
    this->n/=d;
    this->v/=d;
    return *this;
}

Quaternion  Quaternion::operator -() const
{
    return Quaternion(-this->n,-this->v);
}

Quaternion operator+(const Quaternion& u, const Quaternion& v)
{
    return Quaternion(u.n+v.n,u.v+v.v);
}

Quaternion operator-(const Quaternion& u, const Quaternion& v)
{
    return Quaternion(u.n-v.n,u.v-v.v);
}

Quaternion operator*(const Quaternion& u, const Quaternion& v)
{
    return Quaternion(u.n*v.n-DotProduct(u.v,v.v),u.n*v.v+v.n*u.v+CrossProduct(u.v,v.v));
}

Quaternion operator*(const float s,const Quaternion& u)
{
    return Quaternion(s*u.n,s*u.v);
}

Quaternion operator*(const Quaternion& u, const float s)
{
    return Quaternion(s*u.n,s*u.v);
}

Quaternion operator *(const Quaternion& u,const Vector3& v)
{
    return u*Quaternion(0,v);
}
Quaternion operator *(const Vector3& v,const Quaternion& u)
{
    return u*Quaternion(0,v);
}

Quaternion operator/(const Quaternion& u, const float s)
{
    assert(s!=0);
    return Quaternion(u.n/s,u.v/s);
}

Matrix3 Quaternion::MakeMatrix3FromQ()
{
    float e11=n*n+v[0]*v[0]-v[1]*v[1]-v[2]*v[2],\
          e21=2*v[0]*v[1]+2*n*v[2],\
          e31=2*v[2]*v[0]-2*n*v[1],\
          e12=2*v[0]*v[1]-2*n*v[2],\
          e22=n*n-v[0]*v[0]+v[1]*v[1]-v[2]*v[2],\
          e32=2*v[2]*v[1]+2*n*v[0],\
          e13=2*v[0]*v[2]+2*n*v[1],\
          e23=2*v[1]*v[2]-2*n*v[0],\
          e33=n*n-v[0]*v[0]-v[1]*v[1]+v[2]*v[2];
    return Matrix3(e11,e12,e13,e21,e22,e23,e31,e32,e33);
}
