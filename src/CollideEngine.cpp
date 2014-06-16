#include "CollideEngine.h"
CollideEngine::CollideEngine()
{
    sound = new QSound("./sound/CollideEdge2.wav");
    sound1 = new QSound("./sound/Collide2.wav");
}
CollideEngine::~CollideEngine() {}

bool CollideEngine::DectBallToBallCollision(const Ball& ballA,const Ball& ballB)
{
   if(ballA.getBallState()==STILL && ballB.getBallState()==STILL)
       return false;
   if((DistanceBetween(ballA.getPosition(),ballB.getPosition())-(ballA.getRadius()+ballB.getRadius()))>0.001)
       return false;
   return true;
}

void CollideEngine::ProcessBallToBallCollision(Ball& ballA,Ball& ballB)
{
    Collision c;
    Vector3 pos_tempA,pos_tempB;

    pos_tempA=ballA.getPosition();
    pos_tempB=ballB.getPosition();

    c.CollidePosition=(pos_tempA+pos_tempB)*0.5;
    c._N=GetNormalize(pos_tempA-pos_tempB);

    float extra=(ballA.getRadius()+ballB.getRadius())-DistanceBetween(pos_tempA,pos_tempB);
    Vector3 Extra=c._N*extra*0.5;
    pos_tempA+=Extra;
    pos_tempB+=-Extra;

    ballA.setPosition( pos_tempA);
    ballB.setPosition( pos_tempB);
    //I=-Vn(e+1)/(1/M1+1/M2)
    c.Ra=c.CollidePosition-pos_tempA;
    c.Rb=c.CollidePosition-pos_tempB;
    c.Va=CrossProduct(ballA.getAngleSpeed(),c.Ra)+ballA.getSpeed(); //v+ω×R
    c.Vb=CrossProduct(ballB.getAngleSpeed(),c.Rb)+ballB.getSpeed();
    c.Vr=c.Va-c.Vb;
    c.Vn=DotProduct(c._N,c.Vr);

    if(c.Vn>=-0.0001) return;

    c.Ca=1.0f/M;
    c.Cb=1.0f/M;
    c.In=-c._N*c.Vn*(1+E_BallToBall)/(c.Ca+c.Cb);

    ballA.ApplyImpulse(c.In,c.CollidePosition);
    ballB.ApplyImpulse(-c.In,c.CollidePosition);
    sound1->play();

    c.Vt=(c.Vr-c._N*c.Vn).Length();


    if(c.Vt<=0.0001f) return;

    c._T=-GetNormalize(c.Vr-c._N*c.Vn);

    c.Ca=1.0f/M+DotProduct(c._T, CrossProduct((CrossProduct(c.Ra, c._T) / ballA.getIm()), c.Ra)) ;
    c.Cb=1.0f/M+DotProduct(c._T, CrossProduct((CrossProduct(c.Rb, c._T) / ballB.getIm()), c.Ra)) ;
    //cout<<"c.Ca:"<<c.Ca<<";c.Cb"<<c.Cb<<endl;
    float It;
    It = c.Vt/(c.Ca+c.Cb);
    if (It < F_BallToBall*c.In.Length())
        c.It = c._T*It;
    else
    {
        c.It = c._T*F_BallToBall*c.In.Length();
    }

    ballA.ApplyImpulse(c.It,c.CollidePosition);
    ballB.ApplyImpulse(-c.It,c.CollidePosition);
    return;
}

void CollideEngine::TableCollision(const Table& table,Ball& ball)
{
    bool wallhit,cornerwallhit;

    //detect wall to ball collision
    wallhit=this->WallToBallCollision(table,ball);

    //detect anglewall to ball collision
    cornerwallhit=this->CornerWallToBallCollision(table,ball);

    if(!wallhit && !cornerwallhit)
    {
        this->CornerRadWallToBallCollision(table,ball);
    }

}

bool CollideEngine::WallToBallCollision(const Table& table,Ball& ball)
{
    if(ball.getBallState()==STILL)
        return false;

    Vector3 col_N;
    float extra;

    //topleft
    extra=ball.getPosition().getY()-(table.getCheckp())[0].getY()-ball.getRadius();
    if(extra<-0.001)
    {
        if(ball.getPosition().getX()>=(table.getCheckp())[0].getX() \
                && ball.getPosition().getX()<=(table.getCheckp())[1].getX())
        {
            //cout<<"!!!"<<extra<<endl;
            col_N=Vector3(0,1,0);
            this->ProcessWallToBallCollision(ball,col_N,-extra);
            return true;
        }
    }

    //topright
    extra=ball.getPosition().getY()-(table.getCheckp())[2].getY()-ball.getRadius();
    if(extra<-0.001)
    {
        if(ball.getPosition().getX()>=(table.getCheckp())[2].getX() \
                && ball.getPosition().getX()<=(table.getCheckp())[3].getX())
        {
            //cout<<"!!!"<<extra<<endl;
            col_N=Vector3(0,1,0);
            this->ProcessWallToBallCollision(ball,col_N,-extra);
            return true;
        }
    }

    //bottomleft
    extra=(table.getCheckp())[4].getY()-ball.getPosition().getY()-ball.getRadius();
    if(extra<-0.001)
    {
        if(ball.getPosition().getX()>=(table.getCheckp())[4].getX() \
                && ball.getPosition().getX()<=(table.getCheckp())[5].getX())
        {
            //cout<<"!!!"<<extra<<endl;
            col_N=Vector3(0,-1,0);
            this->ProcessWallToBallCollision(ball,col_N,-extra);
            return true;
        }
    }

    //bottomright
    extra=(table.getCheckp())[6].getY()-ball.getPosition().getY()-ball.getRadius();
    if(extra<-0.001)
    {
        if(ball.getPosition().getX()>=(table.getCheckp())[6].getX() \
                && ball.getPosition().getX()<=(table.getCheckp())[7].getX())
        {
            //cout<<"!!!"<<extra<<endl;
            col_N=Vector3(0,-1,0);
            this->ProcessWallToBallCollision(ball,col_N,-extra);
            return true;
        }
    }

    //left
    extra=ball.getPosition().getX()-(table.getCheckp())[8].getX()-ball.getRadius();
    if(extra<-0.001)
    {
        if(ball.getPosition().getY()>=(table.getCheckp())[8].getY() \
                && ball.getPosition().getY()<=(table.getCheckp())[9].getY())
        {
            //cout<<"!!!"<<extra<<endl;
            col_N=Vector3(1,0,0);
            this->ProcessWallToBallCollision(ball,col_N,-extra);
            return true;
        }
    }

    //right
    extra=(table.getCheckp())[10].getX()-ball.getPosition().getX()-ball.getRadius();
    if(extra<-0.001)
    {
        if(ball.getPosition().getY()>=(table.getCheckp())[10].getY() \
                && ball.getPosition().getY()<=(table.getCheckp())[11].getY())
        {
            //cout<<"!!!"<<extra<<endl;
            col_N=Vector3(-1,0,0);
            this->ProcessWallToBallCollision(ball,col_N,-extra);
            return true;
        }
    }

    return false;
}

bool CollideEngine::CornerWallToBallCollision(const Table& table,Ball& ball)
{
    if(ball.getBallState()==STILL)
        return false;

    vector<Vector3> col_N;
    vector<float> extra;
    Vector3 vp; //vertical point
    float k;

    //init
    col_N.push_back(GetNormalize(Vector3(specialAntiRotate90(table.getPocketp()[0]-table.getCheckp()[0]))));
    col_N.push_back(GetNormalize(Vector3(specialAntiRotate90(table.getCheckp()[1]-table.getPocketp()[1]))));
    col_N.push_back(GetNormalize(Vector3(specialAntiRotate90(table.getPocketp()[2]-table.getCheckp()[2]))));
    col_N.push_back(GetNormalize(Vector3(specialAntiRotate90(table.getCheckp()[3]-table.getPocketp()[3]))));
    col_N.push_back(GetNormalize(Vector3(specialAntiRotate90(table.getCheckp()[4]-table.getPocketp()[4]))));
    col_N.push_back(GetNormalize(Vector3(specialAntiRotate90(table.getPocketp()[5]-table.getCheckp()[5]))));
    col_N.push_back(GetNormalize(Vector3(specialAntiRotate90(table.getCheckp()[6]-table.getPocketp()[6]))));
    col_N.push_back(GetNormalize(Vector3(specialAntiRotate90(table.getPocketp()[7]-table.getCheckp()[7]))));
    col_N.push_back(GetNormalize(Vector3(specialAntiRotate90(table.getCheckp()[8]-table.getPocketp()[8]))));
    col_N.push_back(GetNormalize(Vector3(specialAntiRotate90(table.getPocketp()[9]-table.getCheckp()[9]))));
    col_N.push_back(GetNormalize(Vector3(specialAntiRotate90(table.getPocketp()[10]-table.getCheckp()[10]))));
    col_N.push_back(GetNormalize(Vector3(specialAntiRotate90(table.getCheckp()[11]-table.getPocketp()[11]))));

    /*for(unsigned i=0;i<col_N.size();i++)
    {
        //cout<<i<<":"<<col_N[i][0]<<","<<col_N[i][1]<<","<<col_N[i][2]<<endl;
    }*/


    Vector2 pos(ball.getPosition()[0],ball.getPosition()[1]);
    for(unsigned i=0;i<col_N.size();i++)
    {
        extra.push_back(PointToLineDistance(pos,Line(table.getPocketp()[i],table.getCheckp()[i]))-ball.getRadius());
    }

    for(unsigned i=0;i<col_N.size();i++)
    {
        if(extra[i]<-0.001)
        {
            vp=ball.getPosition()-col_N[i]*extra[i]-col_N[i]*ball.getRadius();
            k=DistanceBetween(vp,Vector3(table.getPocketp()[i]))\
                    /DistanceBetween(Vector3(table.getCheckp()[i]),Vector3(table.getPocketp()[i]));
            if(k<=1)
            {
                //col_N[i].setY(-col_N[i].getY());
                this->ProcessWallToBallCollision(ball,col_N[i],-extra[i]);
                return true;
            }
        }
    }
    return false;
}

// 1 px , 2 degree
// -> 58px r
void CollideEngine::CornerRadWallToBallCollision(const Table& table,Ball& ball)
{
    if(ball.getBallState()==STILL)
        return;

    const float r=58;
    //pointp closer to corner
    vector<Vector2> pointp,pointw,pointmiddle;
    vector<Vector2> middleline;
    vector<Vector2> centre;
    Vector3 col_N;
    vector<float> extra;
    double d;

    //init
    for(unsigned i=0;i<table.getCheckp().size();i++)
    {
        Vector2 offset=(table.getPocketp()[i]-table.getCheckp()[i]).getNormalize()*1.0f;
        pointp.push_back(table.getCheckp()[i]+offset);
        if(i<4)
            pointp.back().setXY(pointp.back().getX(),pointp.back().getY()-0.4);
        else if(i<8)
            pointp.back().setXY(pointp.back().getX(),pointp.back().getY()+0.4);
        else if(i<10)
            pointp.back().setXY(pointp.back().getX()-0.4,pointp.back().getY());
        else
            pointp.back().setXY(pointp.back().getX()+0.4,pointp.back().getY());
        //assert(offset.Length()==1);
    }

    pointw.push_back(Vector2(table.getCheckp()[0].getX()+1,table.getCheckp()[0].getY()));
    pointw.push_back(Vector2(table.getCheckp()[1].getX()-1,table.getCheckp()[1].getY()));
    pointw.push_back(Vector2(table.getCheckp()[2].getX()+1,table.getCheckp()[2].getY()));
    pointw.push_back(Vector2(table.getCheckp()[3].getX()-1,table.getCheckp()[3].getY()));
    pointw.push_back(Vector2(table.getCheckp()[4].getX()+1,table.getCheckp()[4].getY()));
    pointw.push_back(Vector2(table.getCheckp()[5].getX()-1,table.getCheckp()[5].getY()));
    pointw.push_back(Vector2(table.getCheckp()[6].getX()+1,table.getCheckp()[6].getY()));
    pointw.push_back(Vector2(table.getCheckp()[7].getX()-1,table.getCheckp()[7].getY()));
    pointw.push_back(Vector2(table.getCheckp()[8].getX(),table.getCheckp()[8].getY()+1));
    pointw.push_back(Vector2(table.getCheckp()[9].getX(),table.getCheckp()[9].getY()-1));
    pointw.push_back(Vector2(table.getCheckp()[10].getX(),table.getCheckp()[10].getY()+1));
    pointw.push_back(Vector2(table.getCheckp()[11].getX(),table.getCheckp()[11].getY()-1));

    for(unsigned i=0;i<table.getCheckp().size();i++)
    {
        pointmiddle.push_back((pointp[i]+pointw[i])/2);
    }


    middleline.push_back((specialAntiRotate90(pointp[0]-pointw[0])).getNormalize());
    middleline.push_back((specialAntiRotate90(pointw[1]-pointp[1])).getNormalize());
    middleline.push_back((specialAntiRotate90(pointp[2]-pointw[2])).getNormalize());
    middleline.push_back((specialAntiRotate90(pointw[3]-pointp[3])).getNormalize());
    middleline.push_back((specialAntiRotate90(pointw[4]-pointp[4])).getNormalize());
    middleline.push_back((specialAntiRotate90(pointp[5]-pointw[5])).getNormalize());
    middleline.push_back((specialAntiRotate90(pointw[6]-pointp[6])).getNormalize());
    middleline.push_back((specialAntiRotate90(pointp[7]-pointw[7])).getNormalize());
    middleline.push_back((specialAntiRotate90(pointw[8]-pointp[8])).getNormalize());
    middleline.push_back((specialAntiRotate90(pointp[9]-pointw[9])).getNormalize());
    middleline.push_back((specialAntiRotate90(pointp[10]-pointw[10])).getNormalize());
    middleline.push_back((specialAntiRotate90(pointw[11]-pointp[11])).getNormalize());


    for(unsigned i=0;i<table.getCheckp().size();i++)
    {
        //centre.push_back(Vector2(pointmiddle[i].getX()+middleline[i].getX()*(-r),\
                            //     pointmiddle[i].getY()+middleline[i].getY()*(-r)));
        Vector2 v=middleline[i]*(-r);
        v = v + pointmiddle[i];
        centre.push_back(v);
    }

    for(unsigned i=0;i<table.getCheckp().size();i++)
    {
        extra.push_back(DistanceBetween(Vector3(centre[i]),ball.getPosition())-r-ball.getRadius());
    }


    for(unsigned i=0;i<extra.size();i++)
    {
        if(extra[i]<-0.01)
        {
            d=(double)DotProduct(ball.getPosition()-Vector3(centre[i]),Vector3(table.getCheckp()[i])-Vector3(centre[i]));
            d/=(ball.getPosition()-Vector3(centre[i])).Length()*(Vector3(table.getCheckp()[i])-Vector3(centre[i])).Length();
            d=acos(d);
            if(d<=(2/180.0*M_PI))
            {
                col_N=GetNormalize(ball.getPosition()-Vector3(centre[i]));
                this->ProcessWallToBallCollision(ball,col_N,-extra[i]);
            }
            return;
        }
    }
}


void CollideEngine::ProcessWallToBallCollision(Ball& ball,const Vector3& col_N,float extra)
{
    Collision c;
    Vector3 pos_temp=ball.getPosition();

    sound->play();

    pos_temp+=col_N*extra;
    ball.setPosition( pos_temp);

    c.CollidePosition=pos_temp-col_N*ball.getRadius();
    c._N=col_N;

    //I=-Vn(e+1)/(1/M)
    c.Ra=c.CollidePosition-pos_temp;
    c.Va=CrossProduct(ball.getAngleSpeed(),c.Ra)+ball.getSpeed(); //v+ω×R
    c.Vr=c.Va;
    c.Vn=DotProduct(c._N,c.Vr);

    if(c.Vn>=-0.0001f) return;

    c.Ca=1.0f/M;
    c.In=-c._N*c.Vn*(1+E_WallToBall)/(c.Ca);

    ball.ApplyImpulse(c.In,c.CollidePosition);

    c.Vt=(c.Vr-c._N*c.Vn).Length();
    if(c.Vt<=0.0001f) return;

    c._T=-GetNormalize(c.Vr-c._N*c.Vn);
    c.Ca=1.0f/M+DotProduct(c._T, CrossProduct((CrossProduct(c.Ra, c._T) / ball.getIm()), c.Ra)) ;
    //cout<<"c.Ca:"<<c.Ca<<endl;
    float It;
    It = c.Vt/(c.Ca);
    //cout<<"It:"<<It<<";F:"<<F_WallToBall*c.In.Length()<<endl;
    if (It < F_WallToBall*c.In.Length())
        c.It = c._T*It;
    else
        c.It = c._T*F_WallToBall*c.In.Length();

    ball.ApplyImpulse(c.It,c.CollidePosition);

    return;
}


