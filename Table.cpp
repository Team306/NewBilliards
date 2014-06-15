// Copyright (C) 2014 Team306

#include "Table.h"

Table::Table()
{
}

Table::~Table()
{
}

void Table::init(Referee& referee)
{
    // init method
    picPosition.setXY(0, 0);
    position.setXY(40, 40);
    picSize.setXY(1120, 700);
    size.setXY(1040, 520);
    pocketRadius = 30;
    lineX = (float)65 / (float)254 * size.getX();

    p0.setXY(position.getX() + 8, position.getY() + 8);
    p1.setXY(position.getX() + size.getX() - 8, position.getY() + 8);
    p2.setXY(position.getX() + 8, position.getY() + size.getY() - 8);
    p3.setXY(position.getX() + size.getX() - 8, position.getY() + size.getY() - 8);
    p4.setXY(picPosition.getX() + picSize.getX() / 2, picPosition.getY() + pocketRadius + 8);
    p5.setXY(picPosition.getX() + picSize.getX() / 2, picPosition.getY() + size.getY() - pocketRadius + position.getY() * 2 - 8);

    if(checkp.size() > 0 || pocketp.size() > 0)
        return;

    checkp.push_back(Vector2(position.getX() + pocketRadius + 28, position.getY() + 15));//topleft_left
    checkp.push_back(Vector2(position.getX() + size.getX() / 2 - pocketRadius - 8, position.getY() + 15));//topleft_right
    checkp.push_back(Vector2(position.getX() + size.getX() / 2 + pocketRadius + 8, position.getY() + 15));//topright_left
    checkp.push_back(Vector2(position.getX() + size.getX() - pocketRadius - 28,position.getY() + 15));//topright_right
    checkp.push_back(Vector2(position.getX() + pocketRadius + 28, position.getY() + size.getY() - 15));//bottomleft_left
    checkp.push_back(Vector2(position.getX() + size.getX() / 2 - pocketRadius - 8, position.getY() + size.getY() - 15));//bottomleft_right
    checkp.push_back(Vector2(position.getX() + size.getX() / 2 + pocketRadius + 8, position.getY() + size.getY() - 15));//bottomright_left
    checkp.push_back(Vector2(position.getX() + size.getX() - pocketRadius - 28, position.getY() + size.getY() - 15));//bottomright_right
    checkp.push_back(Vector2(position.getX() + 15, position.getY() + pocketRadius + 28));//left_top
    checkp.push_back(Vector2(position.getX() + 15, position.getY() + size.getY() - pocketRadius - 28));//left_bottom
    checkp.push_back(Vector2(position.getX() + size.getX() - 15, position.getY() + pocketRadius + 28));//right_top
    checkp.push_back(Vector2(position.getX() + size.getX() - 15, position.getY() + size.getY() - pocketRadius - 28));//right_bottom

    pocketp.push_back(Vector2(position.getX() + pocketRadius + 8, position.getY()));//same position with checkp
    pocketp.push_back(Vector2(position.getX() + size.getX() / 2 - pocketRadius, position.getY()));
    pocketp.push_back(Vector2(position.getX() + size.getX() / 2 + pocketRadius, position.getY()));
    pocketp.push_back(Vector2(position.getX() + size.getX() - pocketRadius - 8,position.getY()));
    pocketp.push_back(Vector2(position.getX() + pocketRadius + 8, position.getY() + size.getY()));
    pocketp.push_back(Vector2(position.getX() + size.getX() / 2 - pocketRadius, position.getY() + size.getY()));
    pocketp.push_back(Vector2(position.getX() + size.getX() / 2 + pocketRadius, position.getY() + size.getY()));
    pocketp.push_back(Vector2(position.getX() + size.getX() - pocketRadius - 8, position.getY() + size.getY()));
    pocketp.push_back(Vector2(position.getX(), position.getY() + pocketRadius + 8));
    pocketp.push_back(Vector2(position.getX(), position.getY() + size.getY() - pocketRadius - 8));
    pocketp.push_back(Vector2(position.getX() + size.getX(), position.getY() + pocketRadius + 8));
    pocketp.push_back(Vector2(position.getX() + size.getX(), position.getY() + size.getY() - pocketRadius - 8));

    T1<<QPoint(pocketp[0].getX(),pocketp[0].getY())<<QPoint(pocketp[1].getX(),pocketp[1].getY())
            <<QPoint(checkp[1].getX(),checkp[1].getY())<<QPoint(checkp[0].getX(),checkp[0].getY());

    T2<<QPoint(pocketp[2].getX(),pocketp[2].getY())<<QPoint(pocketp[3].getX(),pocketp[3].getY())
            <<QPoint(checkp[3].getX(),checkp[3].getY())<<QPoint(checkp[2].getX(),checkp[2].getY());

    T3<<QPoint(pocketp[4].getX(),pocketp[4].getY())<<QPoint(pocketp[5].getX(),pocketp[5].getY())
            <<QPoint(checkp[5].getX(),checkp[5].getY())<<QPoint(checkp[4].getX(),checkp[4].getY());

    T4<<QPoint(pocketp[6].getX(),pocketp[6].getY())<<QPoint(pocketp[7].getX(),pocketp[7].getY())
            <<QPoint(checkp[7].getX(),checkp[7].getY())<<QPoint(checkp[6].getX(),checkp[6].getY());

    T5<<QPoint(pocketp[8].getX(),pocketp[8].getY())<<QPoint(pocketp[9].getX(),pocketp[9].getY())
            <<QPoint(checkp[9].getX(),checkp[9].getY())<<QPoint(checkp[8].getX(),checkp[8].getY());

    T6<<QPoint(pocketp[10].getX(),pocketp[10].getY())<<QPoint(pocketp[11].getX(),pocketp[11].getY())
            <<QPoint(checkp[11].getX(),checkp[11].getY())<<QPoint(checkp[10].getX(),checkp[10].getY());

    loadGLTextures();
}

Vector2 Table::getSize() const
{
    return size;
}

vector<Vector2> Table::getCheckp() const
{
    return this->checkp;
}

vector<Vector2> Table::getPocketp() const
{
    return this->pocketp;
}

// update and draw
void Table::Update()
{
    // update here
}

void Table::Draw(QPainter& painter)
{
    // draw here
//    QColor brown(91, 29, 28);
//    painter.setBrush(QBrush(brown));
//    painter.setPen(QPen(brown));

//    painter.drawRect(QRectF(0, 600, 1280, 120));

//    painter.drawRect(QRectF(picPosition.getX(), picPosition.getY(), picSize.getX(), picSize.getY()));

//    painter.setPen(QPen(QColor(0, 0, 0)));
//    painter.setBrush(QBrush(QColor(68, 149, 60)));
//    painter.drawRect(QRectF(position.getX(), position.getY(), size.getX(), size.getY()));

//    painter.setPen(QPen(QColor(0, 0, 0)));
//    painter.setBrush(QBrush(QColor(0,0,0)));
//    painter.drawEllipse(QPoint(position.getX() + 8, position.getY() + 8),pocketRadius, pocketRadius);
//    painter.drawEllipse(QPoint(position.getX() + size.getX() - 8, position.getY() + 8), pocketRadius , pocketRadius);
//    painter.drawEllipse(QPoint(position.getX() + 8, position.getY()+size.getY() - 8), pocketRadius,pocketRadius);
//    painter.drawEllipse(QPoint(position.getX() + size.getX() - 8, position.getY() + size.getY() - 8),
//                        pocketRadius,pocketRadius);
//    painter.drawEllipse(QPoint(picPosition.getX() + picSize.getX() / 2, picPosition.getY() + pocketRadius + 8),
//                        pocketRadius, 0.75 * pocketRadius);
//    painter.drawEllipse(QPoint(picPosition.getX() + picSize.getX() / 2, picPosition.getY() + size.getY() - pocketRadius + position.getY() * 2 - 8),
//                        pocketRadius, 0.75 * pocketRadius);

//    painter.setPen(QPen(QColor(255,255,255)));
//    painter.drawLine(position.getX() + lineX, position.getY(), position.getX() + lineX, position.getY() + size.getY());

//    painter.setPen(QPen(QColor(100,100,100)));
//    painter.setBrush(QBrush(QColor(80,149,80)));
//    painter.drawPolygon(T1);
//    painter.drawPolygon(T2);
//    painter.drawPolygon(T3);
//    painter.drawPolygon(T4);
//    painter.drawPolygon(T5);
//    painter.drawPolygon(T6);
}

void Table::loadGLTextures()
{
  QImage tex, buf;
  if ( !buf.load( "./data/table.jpg" ) )
  {
    qWarning( "Could not read image file, using single-color instead." );
    QImage dummy(128,128,QImage::Format_RGB32);
    dummy.fill( Qt::green );
    buf = dummy;
  }
  tex = QGLWidget::convertToGLFormat( buf );
  glGenTextures( 3, &texture[0] );
  glBindTexture( GL_TEXTURE_2D, texture[0] );
  glTexImage2D( GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
      GL_RGBA, GL_UNSIGNED_BYTE, tex.bits() );

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  if ( !buf.load( "./data/table2.bmp" ) )
  {
    qWarning( "Could not read image file, using single-color instead." );
    QImage dummy(128,128,QImage::Format_RGB32);
    dummy.fill( Qt::green );
    buf = dummy;
  }
  tex = QGLWidget::convertToGLFormat( buf );
  glBindTexture( GL_TEXTURE_2D, texture[1] );

  glTexImage2D( GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
      GL_RGBA, GL_UNSIGNED_BYTE, tex.bits() );

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  if ( !buf.load( "./data/table3.bmp" ) )
  {
    qWarning( "Could not read image file, using single-color instead." );
    QImage dummy(128,128,QImage::Format_RGB32);
    dummy.fill( Qt::green );
    buf = dummy;
  }
  tex = QGLWidget::convertToGLFormat( buf );
  glBindTexture( GL_TEXTURE_2D, texture[2] );

  glTexImage2D( GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
      GL_RGBA, GL_UNSIGNED_BYTE, tex.bits() );

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

}

void Table::Draw3D()
{
    float va = 5;
       float hy = 700 / (2 * tan(va / 2 * M_PI / 180) * 0.1);
       float z = 1000;

       glLoadIdentity();
       glBegin(GL_QUADS);
       glColor3f(1,1,1);

       glVertex3f((picPosition.getX() - 560) * z / hy /0.1, (-picPosition.getY() + 350) * z / hy / 0.1, -z);
       glVertex3f((picPosition.getX() - 560) *z/ hy /0.1, (-picPosition.getY() - picSize.getY() + 350) *z/ hy/0.1, -z);
       glVertex3f((picPosition.getX() +picSize.getX() - 560) * z / hy / 0.1, (-picPosition.getY() - picSize.getY() + 350) *z/ hy/0.1, -z);
       glVertex3f((picPosition.getX() +picSize.getX() - 560) * z / hy/0.1 , (-picPosition.getY() + 350) * z / hy/0.1, -z);
       glEnd();

       glEnable(GL_COLOR_MATERIAL);
       glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

       glEnable(GL_TEXTURE_2D);
       glBindTexture( GL_TEXTURE_2D, texture[0] );

       glBegin(GL_QUADS);
       glTexCoord2f(0.0, 0.0);glVertex3f((picPosition.getX() - 560)*z/hy/0.1,(-picPosition.getY()-40+350)*z/hy/0.1,-z);
       glTexCoord2f(1.0, 0.0);glVertex3f((picPosition.getX()+picSize.getX() - 560)*z/hy/0.1,(-picPosition.getY()-40+350)*z/hy/0.1,-z);
       glTexCoord2f(1.0, 1.0);glVertex3f((picPosition.getX()+picSize.getX() - 560)*z/hy/0.1,(-picPosition.getY()+350)*z/hy/0.1,-z);
       glTexCoord2f(0.0, 1.0);glVertex3f((picPosition.getX() - 560)*z/hy/0.1,(-picPosition.getY()+350)*z/hy/0.1,-z);

       glTexCoord2f(1.0, 1.0);glVertex3f((picPosition.getX() - 560)*z/hy/0.1,(-picPosition.getY()-size.getY()-80+350)*z/hy/0.1,-z);
       glTexCoord2f(0.0, 1.0);glVertex3f((picPosition.getX()+picSize.getX() - 560)*z/hy/0.1,(-picPosition.getY()-size.getY()-80+350)*z/hy/0.1,-z);
       glTexCoord2f(0.0, 0.0);glVertex3f((picPosition.getX()+picSize.getX() - 560)*z/hy/0.1,(-picPosition.getY()-size.getY()-40+350)*z/hy/0.1,-z);
       glTexCoord2f(1.0, 0.0);glVertex3f((picPosition.getX() - 560)*z/hy/0.1,(-picPosition.getY()-size.getY()-40+350)*z/hy/0.1,-z);

       glTexCoord2f(1.0, 1.0);glVertex3f((position.getX()-40 - 560)*z/hy/0.1,(-position.getY()+350)*z/hy/0.1,-z);
       glTexCoord2f(0.0, 1.0);glVertex3f((position.getX()-40 - 560)*z/hy/0.1,(-position.getY()-size.getY()+350)*z/hy/0.1,-z);
       glTexCoord2f(0.0, 0.0);glVertex3f((position.getX() - 560)*z/hy/0.1,(-position.getY()-size.getY()+350)*z/hy/0.1,-z);
       glTexCoord2f(1.0, 0.0);glVertex3f((position.getX() - 560)*z/hy/0.1,(-position.getY()+350)*z/hy/0.1,-z);

       glTexCoord2f(0.0, 0.0);glVertex3f((position.getX()+size.getX() - 560)*z/hy/0.1,(-position.getY()+350)*z/hy/0.1,-z);
       glTexCoord2f(1.0, 0.0);glVertex3f((position.getX()+size.getX() - 560)*z/hy/0.1,(-position.getY()-size.getY()+350)*z/hy/0.1,-z);
       glTexCoord2f(1.0, 1.0);glVertex3f((position.getX()+size.getX()+40 - 560)*z/hy/0.1,(-position.getY()-size.getY()+350)*z/hy/0.1,-z);
       glTexCoord2f(0.0, 1.0);glVertex3f((position.getX()+size.getX()+40 - 560)*z/hy/0.1,(-position.getY()+350)*z/hy/0.1,-z);

       glEnd();
       glDisable(GL_TEXTURE_2D);

       glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D, texture[1]);
       glBegin(GL_QUADS);
       z=1100;
       glTexCoord2f(0.0, 0.0);glVertex3f((position.getX() - 560) * z / hy /0.1, (-position.getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(1.0, 0.0);glVertex3f((position.getX() - 560) *z/ hy /0.1, (-position.getY() - size.getY() + 350) *z/ hy/0.1, -z);
       glTexCoord2f(1.0, 1.0);glVertex3f((position.getX() +size.getX() - 560) * z / hy / 0.1, (-position.getY() - size.getY() + 350) *z/ hy/0.1, -z);
       glTexCoord2f(0.0, 1.0);glVertex3f((position.getX() +size.getX() - 560) * z / hy/0.1 , (-position.getY() + 350) * z / hy/0.1, -z);
       glEnd();
       glDisable(GL_TEXTURE_2D);

       glBegin(GL_LINES);
       glColor3f(1,1,1);
       glVertex3f((position.getX()+lineX-560)*z/hy/0.1,(-position.getY()+350)*z/hy/0.1,-z);
       glVertex3f((position.getX()+lineX-560)*z/hy/0.1,(-position.getY()-size.getY()+350)*z/hy/0.1,-z);
       glEnd();

       glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D, texture[2]);
       glBegin(GL_QUADS);
       glTexCoord2f(0.0, 0.0);glVertex3f((pocketp[1].getX() - 560) * z / hy / 0.1, (-pocketp[1].getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(1.0, 0.0);glVertex3f((pocketp[0].getX() - 560) * z / hy / 0.1, (-pocketp[0].getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(1.0, 1.0);glVertex3f((checkp[0].getX() - 560) * z / hy / 0.1, (-checkp[0].getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(0.0, 1.0);glVertex3f((checkp[1].getX() - 560) * z / hy / 0.1, (-checkp[1].getY() + 350) * z / hy / 0.1, -z);

       glTexCoord2f(0.0, 0.0);glVertex3f((pocketp[3].getX() - 560) * z / hy / 0.1, (-pocketp[3].getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(1.0, 0.0);glVertex3f((pocketp[2].getX() - 560) * z / hy / 0.1, (-pocketp[2].getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(1.0, 1.0);glVertex3f((checkp[2].getX() - 560) * z / hy / 0.1, (-checkp[2].getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(0.0, 1.0);glVertex3f((checkp[3].getX() - 560) * z / hy / 0.1, (-checkp[3].getY() + 350) * z / hy / 0.1, -z);

       glTexCoord2f(0.0, 0.0);glVertex3f((pocketp[4].getX() - 560) * z / hy / 0.1, (-pocketp[4].getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(1.0, 0.0);glVertex3f((pocketp[5].getX() - 560) * z / hy / 0.1, (-pocketp[5].getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(1.0, 1.0);glVertex3f((checkp[5].getX() - 560) * z / hy / 0.1, (-checkp[5].getY() + 350) * z/ hy / 0.1, -z);
       glTexCoord2f(0.0, 1.0);glVertex3f((checkp[4].getX() - 560) * z / hy / 0.1, (-checkp[4].getY() + 350) * z/ hy / 0.1, -z);

       glTexCoord2f(0.0, 0.0);glVertex3f((pocketp[6].getX() - 560) * z / hy / 0.1, (-pocketp[6].getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(1.0, 0.0);glVertex3f((pocketp[7].getX() - 560) * z / hy / 0.1, (-pocketp[7].getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(1.0, 1.0);glVertex3f((checkp[7].getX() - 560) * z / hy / 0.1, (-checkp[7].getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(0.0, 1.0);glVertex3f((checkp[6].getX() - 560) * z / hy / 0.1, (-checkp[6].getY() + 350) * z / hy / 0.1, -z);

       glTexCoord2f(0.0, 0.0);glVertex3f((pocketp[8].getX() - 560) * z / hy / 0.1, (-pocketp[8].getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(1.0, 0.0);glVertex3f((pocketp[9].getX() - 560) * z / hy / 0.1, (-pocketp[9].getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(1.0, 1.0);glVertex3f((checkp[9].getX() - 560) * z / hy / 0.1, (-checkp[9].getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(0.0, 1.0);glVertex3f((checkp[8].getX() - 560) * z / hy / 0.1, (-checkp[8].getY() + 350) * z / hy / 0.1, -z);

       glTexCoord2f(0.0, 0.0);glVertex3f((pocketp[11].getX() - 560) * z / hy / 0.1, (-pocketp[11].getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(1.0, 0.0);glVertex3f((pocketp[10].getX() - 560) * z / hy / 0.1, (-pocketp[10].getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(1.0, 1.0);glVertex3f((checkp[10].getX() - 560) * z / hy / 0.1, (-checkp[10].getY() + 350) * z / hy / 0.1, -z);
       glTexCoord2f(0.0, 1.0);glVertex3f((checkp[11].getX() - 560) * z / hy / 0.1, (-checkp[11].getY() + 350) * z / hy / 0.1, -z);

       glEnd();
       glDisable(GL_TEXTURE_2D);

       int n = 1000;

       glColor3f(0,0,0);
       glLoadIdentity();
       glTranslatef((p0.getX() - 560) * z / hy / 0.1, (-p0.getY() + 350) * z / hy / 0.1, -z);
       glBegin(GL_TRIANGLE_FAN);
       for(int i=0; i<n; ++i)
           glVertex3f(pocketRadius * z / hy / 0.1 * cos(2*M_PI/n*i), pocketRadius * z / hy / 0.1 *sin(2*M_PI/n*i), 0);
       glEnd();

       glLoadIdentity();
       glTranslatef((p1.getX() - 560) * z / hy / 0.1, (-p1.getY() + 350) * z / hy / 0.1, -z);
       glBegin(GL_TRIANGLE_FAN);
       for(int i=0; i<n; ++i)
           glVertex3f(pocketRadius * z / hy / 0.1 * cos(2*M_PI/n*i), pocketRadius * z / hy / 0.1 *sin(2*M_PI/n*i), 0);
       glEnd();

       glLoadIdentity();
       glTranslatef((p2.getX() - 560) * z / hy / 0.1, (-p2.getY() + 350) * z / hy / 0.1, -z);
       glBegin(GL_TRIANGLE_FAN);
       for(int i=0; i<n; ++i)
           glVertex3f(pocketRadius * z / hy / 0.1 * cos(2*M_PI/n*i), pocketRadius * z / hy / 0.1 *sin(2*M_PI/n*i), 0);
       glEnd();

       glLoadIdentity();
       glTranslatef((p3.getX() - 560) * z / hy / 0.1, (-p3.getY() + 350) * z / hy / 0.1, -z);
       glBegin(GL_TRIANGLE_FAN);
       for(int i=0; i<n; ++i)
           glVertex3f(pocketRadius * z / hy / 0.1 * cos(2*M_PI/n*i), pocketRadius * z / hy / 0.1 *sin(2*M_PI/n*i), 0);
       glEnd();

       glLoadIdentity();
       glTranslatef((p4.getX() - 560) * z / hy / 0.1, (-p4.getY() + 350) * z / hy / 0.1, -z);
       glBegin(GL_TRIANGLE_FAN);
       for(int i=0; i<n; ++i)
           glVertex3f(pocketRadius * z / hy / 0.1 * cos(2*M_PI/n*i), pocketRadius * 0.75 * z / hy / 0.1 *sin(2*M_PI/n*i), 0);
       glEnd();

       glLoadIdentity();
       glTranslatef((p5.getX() - 560) * z / hy / 0.1, (-p5.getY() + 350) * z / hy / 0.1, -z);
       glBegin(GL_TRIANGLE_FAN);
       for(int i=0; i<n; ++i)
           glVertex3f(pocketRadius * z / hy / 0.1 * cos(2*M_PI/n*i), pocketRadius * 0.75 * z / hy / 0.1 *sin(2*M_PI/n*i), 0);
       glEnd();

       glLoadIdentity();
       glBegin(GL_QUADS);
       glColor3f(0.35686,0.11373,0.10980);

       glVertex3f((picPosition.getX() - 560) * z / hy /0.1, (-picPosition.getY()-size.getY()-80 + 350) * z / hy / 0.1, -z);
       glVertex3f((picPosition.getX() - 560) *z/ hy /0.1, (-picPosition.getY() - picSize.getY() + 350) *z/ hy/0.1, -z);
       glVertex3f((picPosition.getX() +picSize.getX() - 560) * z / hy / 0.1, (-picPosition.getY() - picSize.getY() + 350) *z/ hy/0.1, -z);
       glVertex3f((picPosition.getX() +picSize.getX() - 560) * z / hy/0.1 , (-picPosition.getY() -size.getY()-80+ 350) * z / hy/0.1, -z);
       glEnd();

       glDisable(GL_COLOR_MATERIAL);
}

bool Table::positionIsLegal(Vector2 p,Referee &referee)
{
    Vector3 V(p.getX(),p.getY(),0);
    if( (p.getX() > checkp[9].getX() + referee.getBallRadius()) && (p.getX() < position.getX() + lineX) &&
            (p.getY() > checkp[0].getY() + referee.getBallRadius()) &&
            (p.getY() < checkp[5].getY() - referee.getBallRadius()))
        {
                return true;
        }
    return false;
}

bool Table::positionIsIN(Vector2 p, Referee &referee)
{
    Vector3 V(p.getX(),p.getY(),0);
    if( (p.getX() > checkp[9].getX() + referee.getBallRadius()) && (p.getX() < checkp[11].getX() - referee.getBallRadius()) &&
            (p.getY() > checkp[0].getY() + referee.getBallRadius()) &&
            (p.getY() < checkp[5].getY() - referee.getBallRadius()))
        {
                return true;
        }
    return false;
}

bool Table::checkPockets(Ball& ball)
{
    // if the ball is in the pocket return true;
    if((ball.getPosition().DistanceTo(p0) <= pocketRadius )||
            (ball.getPosition().DistanceTo(p1) <= pocketRadius )||
            (ball.getPosition().DistanceTo(p2) <= pocketRadius )||
            (ball.getPosition().DistanceTo(p3) <= pocketRadius )||
            (ball.getPosition().DistanceTo(p4) <= 0.75 * pocketRadius )||
            (ball.getPosition().DistanceTo(p5) <= 0.75 * pocketRadius ))
        return true;
    return false;
}

