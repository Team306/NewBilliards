#ifndef COLLIDEENGINE_H
#define COLLIDEENGINE_H

#include "MyMath.h"
#include "Ball.h"
#include "Table.h"
#include <vector>
#include <QSound>

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
const float E_WallToBall = 0.65f;
const float F_BallToBall = 0.2f;
const float F_WallToBall = 0.4f;

class CollideEngine
{
private:
    QSound *sound,*sound1;
public:
    CollideEngine();
    ~CollideEngine();
    bool DectBallToBallCollision(const Ball& ballA,const Ball& ballB);
    void ProcessBallToBallCollision(Ball& ballA,Ball& ballB);
    void TableCollision(const Table& table,Ball& ball);
    bool WallToBallCollision(const Table& table,Ball& ball);
    bool CornerWallToBallCollision(const Table& table,Ball& ball);
    void CornerRadWallToBallCollision(const Table& table,Ball& ball);
    void ProcessWallToBallCollision(Ball& ball,const Vector3& col_N,float extra);
};

#endif // COLLIDEENGINE_H
