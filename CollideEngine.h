#ifndef COLLIDEENGINE_H
#define COLLIDEENGINE_H

#include "MyMath.h"
#include "Ball.h"

struct Collision
{
    Vector3 CollidePosition;
    Vector3 Vr;
    Vector3 _N;
    Vector3 _T;
    Vector3  Ra;
    Vector3  Va;
    Vector3  Rb;
    Vector3  Vb;
    float Vn;
    float Vt;

    Vector3 In;
    Vector3 It;
    float  Ca;
    float  Cb;

};

const float E_BallToBall = 0.9f;
const float E_WallToBall = 0.7f;
const float F_BallToBall = 0.1f;
const float F_WallToBall = 0.5f;

class CollideEngine
{
public:
    CollideEngine();
    ~CollideEngine();
    bool DectBallToBallCollision(const Ball& ballA,const Ball& ballB);
    void ProcessBallToBallCollision(Ball& ballA,Ball& ballB);
};

#endif // COLLIDEENGINE_H
