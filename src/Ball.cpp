// Copyright (C) 2014 Team306

#include "Ball.h"
GLfloat mat_Ambient[4] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat mat_Diffuse[4] = { 0.6, 0.6, 0.6, 1.0 };
GLfloat mat_Specular[4] = {1, 1, 1, 1.0};
GLfloat mat_Shininess[]={50};

Ball::Ball()
{
    this->speed=Vector3(0,0,0);
    this->anglespeed=Vector3(0,0,0);
    this->Im=0.4f*M*(this->radius)*(this->radius);
    oriention=Quaternion(1,0,0,0);
    Vector3 anglespeed_temp(-M_PI/2,0,0);
    this->oriention-=this->oriention*anglespeed_temp*0.5f;
    this->oriention.Normalize();
    ballState = STILL;
}
Ball::Ball(const Vector3& position, float radius)
    : position(position), radius(radius)
{
    this->speed=Vector3(0,0,0);
    this->anglespeed=Vector3(0,0,0);
    this->Im=0.4f*M*(this->radius)*(this->radius);
    oriention=Quaternion(1,0,0,0);
    Vector3 anglespeed_temp(-M_PI/2,0,0);
    this->oriention-=this->oriention*anglespeed_temp*0.5f;
    this->oriention.Normalize();
    ballState = STILL;
}

Ball::Ball(const Vector2& position, float radius)
    : position(position), radius(radius)
{
    this->speed=Vector3(0,0,0);
    this->anglespeed=Vector3(0,0,0);
    this->Im=0.4f*M*(this->radius)*(this->radius);
    oriention=Quaternion(1,0,0,0);
    Vector3 anglespeed_temp(-M_PI/2,0,0);
    this->oriention-=this->oriention*anglespeed_temp*0.5f;
    this->oriention.Normalize();
    ballState = STILL;
}

Ball::~Ball()
{
}

void Ball::loadGLTextures()
{
  QImage tex, buf;
  QString s=QString::fromStdString("./textures/BallTex"+this->name+".bmp");
  if ( !buf.load( s ) )
  {
    qWarning( "Could not read image file, using single-color instead." );
    QImage dummy(128,128,QImage::Format_RGB32);
    dummy.fill( Qt::green );
    buf = dummy;
  }
  tex = QGLWidget::convertToGLFormat( buf );

  glGenTextures( 1, &texture[0] );

  glBindTexture( GL_TEXTURE_2D, texture[0] );
  glTexImage2D( GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
      GL_RGBA, GL_UNSIGNED_BYTE, tex.bits() );

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

}

Vector3 Ball::getPosition() const
{
    return this->position;
}

void Ball::setPosition(const Vector2& v)
{
    position = Vector3(v);
}

void Ball::setPosition(const Vector3& v)
{
    position = v;
}

void Ball::setPositionX(float x)
{
    this->position.setX(x);
}

void Ball::setPositionY(float y)
{
    this->position.setY(y);
}

void Ball::setPositionZ(float z)
{
    this->position.setZ(z);
}

Vector3 Ball::getSpeed() const
{
    return this->speed;
}

void Ball::setSpeed(const Vector3& v)
{
    if(v.Length()>0)
        this->ballState=RUNNING;
    this->speed = v;
}
Vector3 Ball::getAngleSpeed() const
{
    return this->anglespeed;
}

void Ball::setAngleSpeed(const Vector3& v)
{
    if(v.Length()>=0)
        this->ballState=RUNNING;
    this->anglespeed = v;
}


float Ball::getRadius() const
{
    return this->radius;
}

void Ball::setRadius(float newRadius)
{
    radius = newRadius;
}

float Ball::getIm() const
{
    return this->Im;
}

int Ball::getBallState() const
{
    return ballState;
}

void Ball::setBallState(int newState)
{
    ballState = (BALL_STATE)newState;
}

std::string Ball::getName() const
{
    return name;
}

void Ball::setName(std::string n)
{
    name = n;
}

void Ball::setColor(QColor c)
{
    color = c;
}

void Ball::ApplyImpulse(const Vector3& impulse,const Vector3& collideposition)
{
    this->speed += (impulse/M);
    //std::cout<<"speed"<<speed[0]<<","<<speed[1]<<","<<speed[2]<<endl;
    //??
    if(impulse[2]!=0.0 && fabs(impulse[2])>1)
    {
        this->speed.setX(this->speed[0]/impulse[2]);
        this->speed.setY(this->speed[1]/impulse[2]);
    }
    this->speed.setZ(0.0f);
    this->anglespeed+= CrossProduct(collideposition-this->position,impulse)/this->Im;
    cout<<speed[0]<<","<<speed[1]<<","<<speed[2]<<endl;
    cout<<anglespeed[0]<<","<<anglespeed[1]<<","<<anglespeed[2]<<endl;
    if(this->speed.Length()>0 || this->anglespeed.Length()>0)
        this->ballState=RUNNING;
}

void Ball::Move()
{
    if(this->ballState==STILL)
        return;
    Vector3 rollspeed;
    Vector3 wholespeed;

    rollspeed=CrossProduct(this->anglespeed,Vector3(0,0,this->radius)); //(ωy*r,-ωx*r,0)
    wholespeed=rollspeed+this->speed;

    assert(this->position.getY()==this->position.getY());
    if(rollspeed.Length()<Froll_Threshold && this->speed.Length()<Froll_Threshold)
    {
        if(fabs(this->anglespeed[2])<Frotate_Threshold)
        {
            this->ballState=STILL;
            this->speed=Vector3(0,0,0);
            this->anglespeed=Vector3(0,0,0);
        }
        else
        {
            if (this->anglespeed[2]>0)
                this->anglespeed.setZ(this->anglespeed[2]-Frotate_GroundToBall) ;
            else
                this->anglespeed.setZ(this->anglespeed[2]+Frotate_GroundToBall);
        }
    }
    else
    {
        if(wholespeed.Length()<Fslip_Threshold) //gundong
        {
            this->ApplyImpulse(GetNormalize(this->speed)*(-M * Froll_GroundToBall), this->position);
            this->anglespeed.setX(this->speed[1] / this->radius );
            this->anglespeed.setY(-this->speed[0] / this->radius );
        }
        else
        {
            this->ApplyImpulse(GetNormalize(wholespeed)*(-M * Fslip_GroundToBall ), (this->position+Vector3(0, 0, this->radius)));//去除对ωz影响
        }
        if(fabs(this->anglespeed[2])<Frotate_Threshold)
        {
            this->anglespeed.setZ(0);
        }
        else
        {
            if (this->anglespeed[2]>0)
                this->anglespeed.setZ(this->anglespeed[2]-Frotate_GroundToBall);
            else
                this->anglespeed.setZ(this->anglespeed[2]+Frotate_GroundToBall);

        }
    }
    this->position += (this->speed * 1.0f);
    Vector3 anglespeed_temp(this->anglespeed[0],-this->anglespeed[1],-this->anglespeed[2]);
    this->oriention-=this->oriention*anglespeed_temp*0.5f;
    this->oriention.Normalize();
}

void Ball::Draw3D()
{
    if (ballState == ON_THE_POCKET)
    {
        return;
    }
    glLoadIdentity();
    double fovy=5;
    double hy=2*tan(fovy/2.0*M_PI/180.0)*0.1;
    double hx=2*tan(fovy/2.0*M_PI/180.0)*0.1*(1120.0/700.0);
    double z=1000-19.5;
    Matrix3 m=this->oriention.MakeMatrix3FromQ();
    GLfloat GLm[16]={m[0],m[1],m[2],0,\
                     m[3],m[4],m[5],0,\
                     m[6],m[7],m[8],0,\
                     0,0,0,1};

     glTranslatef((this->position.getX()-560.0)/1120.0*hx*z/0.1,(-this->position.getY()+350.0)/700.0*hy*z/0.1,-z);
     glMultMatrixf(GLm);
     glMaterialfv(GL_FRONT,GL_AMBIENT,mat_Ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_Diffuse);
     glMaterialfv(GL_FRONT,GL_SPECULAR,mat_Specular);
     glMaterialfv(GL_FRONT,GL_SHININESS,mat_Shininess);
     quadratic=gluNewQuadric();
     gluQuadricNormals(quadratic, GLU_SMOOTH);
     gluQuadricTexture(quadratic, GL_TRUE);
     glEnable(GL_TEXTURE_2D); // open texture

     glBindTexture(GL_TEXTURE_2D, texture[0]);
     gluSphere(quadratic,this->radius/700.0*hy*z/0.1,32,32);


     gluQuadricTexture(quadratic,GLU_TRUE);
     gluQuadricDrawStyle(quadratic,GLU_FILL);  //fill texture

     glDisable(GL_TEXTURE_2D);
     glEnd();
}

