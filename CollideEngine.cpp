#include "CollideEngine.h"
CollideEngine::CollideEngine() {}
CollideEngine::~CollideEngine() {}

bool CollideEngine::DectBallToBallCollision(const Ball& ballA,const Ball& ballB)
{
   if(ballA.getBallState()==STILL && ballB.getBallState()==STILL)
       return false;
   if(DistanceBetween(ballA.getPosition(),ballB.getPosition())>=(ballA.getRadius()+ballB.getRadius()))
       return false;
   return true;
}

void CollideEngine::ProcessBallToBallCollision(Ball& ballA,Ball& ballB)
{
    Collision c;
    c.CollidePosition=(ballA.getPosition()+ballB.getPosition())*0.5;
    c._N=GetNormalize(ballA.getPosition()-ballB.getPosition());

    float extra=(ballA.getRadius()+ballB.getRadius())-DistanceBetween(ballA.getPosition(),ballB.getPosition());
    Vector3 Extra=c._N*extra*0.5;
    ballA.setPosition(ballA.getPosition()+Extra);
    ballB.setPosition(ballB.getPosition()-Extra);

    //I=-Vn(e+1)/(1/M1+1/M2)
    c.Ra=c.CollidePosition-ballA.getPosition();
    c.Rb=c.CollidePosition-ballB.getPosition();
    c.Va=CrossProduct(ballA.getAngleSpeed(),c.Ra)+ballA.getSpeed(); //v+ω×R
    c.Vb=CrossProduct(ballB.getAngleSpeed(),c.Rb)+ballB.getSpeed();
    c.Vr=c.Va-c.Vb;
    c.Vn=DotProduct(c._N,c.Vr);

    if(c.Vn>=0) return;

    c.Ca=1.0f/M;
    c.Cb=1.0f/M;
    c.In=-c._N*c.Vn*(1+E_BallToBall)/(c.Ca+c.Cb);

    ballA.ApplyImpulse(c.In,c.CollidePosition);
    ballB.ApplyImpulse(-c.In,c.CollidePosition);

    c.Vt=(c.Vr-c._N*c.Vn).Length();


    if(c.Vt<=0.0f) return;

    c._T=-GetNormalize(c.Vr-c._N*c.Vn);
    //Vector3 Temp=Vector3(c._N*c.Vn);
    //cout<<"C.Vr:"<<c.Vr[0]<<","<<c.Vr[1]<<","<<c.Vr[2]<<endl;
    //cout<<"C.Temp:"<<Temp[0]<<","<<Temp[1]<<","<<Temp[2]<<endl<<endl;

    c.Ca=1.0f/M+DotProduct(c._T, CrossProduct((CrossProduct(c.Ra, c._T) / ballA.getIm()), c.Ra)) ;
    c.Cb=1.0f/M+DotProduct(c._T, CrossProduct((CrossProduct(c.Rb, c._T) / ballB.getIm()), c.Rb)) ;
    float It;
    It = c.Vt/(c.Ca+c.Cb);
    if (It < F_BallToBall*c.In.Length())
        c.It = c._T*It;
    else
        c.It = c._T*F_BallToBall*c.In.Length();

    ballA.ApplyImpulse(c.It,c.CollidePosition);
    ballB.ApplyImpulse(-c.It,c.CollidePosition);
    return;
}

