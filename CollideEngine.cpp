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

void CollideEngine::WallToBallCollision(const Table& table,Ball& ball)
{
    Vector3 col_N;
    float extra;
    QRect wall;

    if(ball.getBallState()==STILL)
        return;

    //topleft
    wall=table.GetWall(1);
    extra=ball.getPosition().getY()-wall.topLeft().y()-ball.getRadius();
    if(extra<0)
    {
        if(ball.getPosition().getX()>=wall.topLeft().x() && ball.getPosition().getX()<=wall.topRight().x())
        {
            col_N=Vector3(0,1,0);
            this->ProcessWallToBallCollision(ball,col_N,-extra);
            return;
        }
    }

    //topright
    wall=table.GetWall(2);
    extra=ball.getPosition().getY()-wall.topLeft().y()-ball.getRadius();
    if(extra<0)
    {
        if(ball.getPosition().getX()>=wall.topLeft().x() && ball.getPosition().getX()<=wall.topRight().x())
        {
            col_N=Vector3(0,1,0);
            this->ProcessWallToBallCollision(ball,col_N,-extra);
            return;
        }
    }

    //bottomleft
    wall=table.GetWall(3);
    extra=wall.bottomLeft().y()-ball.getPosition().getY()-ball.getRadius();
    if(extra<0)
    {
        if(ball.getPosition().getX()>=wall.bottomLeft().x() && ball.getPosition().getX()<=wall.bottomRight().x())
        {
            col_N=Vector3(0,-1,0);
            this->ProcessWallToBallCollision(ball,col_N,-extra);
            return;
        }
    }

    //bottomright
    wall=table.GetWall(4);
    extra=wall.bottomLeft().y()-ball.getPosition().getY()-ball.getRadius();
    if(extra<0)
    {
        if(ball.getPosition().getX()>=wall.bottomLeft().x() && ball.getPosition().getX()<=wall.bottomRight().x())
        {
            col_N=Vector3(0,-1,0);
            this->ProcessWallToBallCollision(ball,col_N,-extra);
            return;
        }
    }

    //left
    wall=table.GetWall(5);
    extra=ball.getPosition().getX()-wall.topLeft().x()-ball.getRadius();
    if(extra<0)
    {
        if(ball.getPosition().getY()>=wall.topLeft().y() && ball.getPosition().getY()<=wall.bottomLeft().y())
        {
            col_N=Vector3(1,0,0);
            this->ProcessWallToBallCollision(ball,col_N,-extra);
            return;
        }
    }

    //right
    wall=table.GetWall(6);
    extra=wall.topRight().x()-ball.getPosition().getX()-ball.getRadius();
    if(extra<0)
    {
        if(ball.getPosition().getY()>=wall.topRight().y() && ball.getPosition().getY()<=wall.bottomRight().y())
        {
            col_N=Vector3(-1,0,0);
            this->ProcessWallToBallCollision(ball,col_N,-extra);
            return;
        }
    }

    return;
}

void CollideEngine::ProcessWallToBallCollision(Ball& ball,const Vector3& col_N,float extra)
{
    Collision c;

    ball.getPosition()+=col_N*extra;

    c.CollidePosition=ball.getPosition()-col_N*ball.getRadius();
    c._N=col_N;

    //I=-Vn(e+1)/(1/M)
    c.Ra=c.CollidePosition-ball.getPosition();
    c.Va=CrossProduct(ball.getAngleSpeed(),c.Ra)+ball.getSpeed(); //v+ω×R
    c.Vr=c.Va;
    c.Vn=DotProduct(c._N,c.Vr);

    if(c.Vn>=0) return;

    c.Ca=1.0f/M;
    c.In=-c._N*c.Vn*(1+E_BallToBall)/(c.Ca);

    ball.ApplyImpulse(c.In,c.CollidePosition);

    c._T=-GetNormalize(c.Vr-c._N*c.Vn);
    c.Ca=1.0f/M+DotProduct(c._T, CrossProduct((CrossProduct(c.Ra, c._T) / ball.getIm()), c.Ra)) ;
    float It;
    It = c.Vt/(c.Ca);
    if (It < F_BallToBall*c.In.Length())
        c.It = c._T*It;
    else
        c.It = c._T*F_BallToBall*c.In.Length();

    ball.ApplyImpulse(c.It,c.CollidePosition);

    return;
}


