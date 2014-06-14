#include "glwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Quaternion u(2,1,2,3);
    Quaternion v(3,2,4,5);
    std::cout<<u.getScalar()<<" "<<u.getVector3()[0]<<" "<<u.getVector3()[1]<<" "<<u.getVector3()[2]<<endl;
    std::cout<<v.getScalar()<<" "<<v.getVector3()[0]<<" "<<v.getVector3()[1]<<" "<<v.getVector3()[2]<<endl;
    u*=v;
    std::cout<<u.getScalar()<<" "<<u.getVector3()[0]<<" "<<u.getVector3()[1]<<" "<<u.getVector3()[2]<<endl;
    GLWindow w;
    w.show();
    return a.exec();
}
