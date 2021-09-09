#ifndef CURVE_H
#define CURVE_H

#include <math.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdio.h>

#include "main.h"

namespace Curve
{
  static int numPoints = 0;
  static GLfloat points[1000][3];
  static int selectedPoint = -1;
  struct Point
  {
    GLdouble x;
    GLdouble y;
    GLdouble z;
  };

  struct Curve
  {
    GLboolean isInverted;
    GLboolean isMirrored;
    GLboolean isFlat;
  };

  struct JigSawPiece
  {
    Curve top;
    Curve bottom;
    Curve left;
    Curve right;
  };

  GLdouble *getPosition(Point point);
  GLuint renderPieces();

  Point piece[48] = {
      {0.0, 7.5, 0.0},
      {13.5, 7.5, 0.0},
      {26.5, 6.5, 0.0},
      {40.0, 5.0, 0.0},
      {56.5, 3.0, 0.0},
      {56.5, 3.0, 0.0},
      {68.0, 1.5, 0.0},
      {80.5, 0.5, 0.0},
      {95.0, 0.0, 0.0},
      {102.5, 0.5, 0.0},
      {108.5, 2.0, 0.0},
      {112.5, 3.0, 0.0},
      {116.0, 8.0, 0.0},
      {117.5, 12.0, 0.0},
      {117.0, 19.0, 0.0},
      {115.0, 26.0, 0.0},
      {110.0, 36.0, 0.0},
      {106.5, 45.0, 0.0},
      {106.0, 55.0, 0.0},
      {109.5, 63.5, 0.0},
      {114.0, 68.5, 0.0},
      {121.5, 73.5, 0.0},
      {130.0, 75.5, 0.0},

      {139.5, 76.5, 0.0},

      {149.0, 75.5, 0.0},
      {157.5, 73.5, 0.0},
      {165.0, 68.5, 0.0},
      {169.5, 63.5, 0.0},
      {173.0, 55.0, 0.0},
      {172.5, 45.0, 0.0},
      {169.0, 36.0, 0.0},
      {164.0, 26.0, 0.0},
      {162.0, 19.0, 0.0},
      {161.5, 12.0, 0.0},
      {163.0, 8.0, 0.0},
      {166.5, 4.0, 0.0},
      {171.0, 2.0, 0.0},
      {176.5, 0.5, 0.0},
      {184.0, 0.0, 0.0},
      {198.5, 0.5, 0.0},
      {211.0, 1.5, 0.0},
      {222.5, 3.0, 0.0},
      {239.5, 5.0, 0.0},
      {253.0, 6.5, 0.0},
      {266.0, 7.5, 0.0},
      {279.5, 7.5, 0.0},

      {280.0, -15.0, 0.0},
      {0.0, -15.0, 0.0},
  };

  // Point piece[46] = {
  //     {0.0, 7.5},
  //     {13.5, 7.5},
  //     {26.5, 6.5},
  //     {40.0, 5.0},
  //     {56.5, 3.0},
  //     {68.0, 1.5},
  //     {80.5, 0.5},
  //     {95.0, 0.0},
  //     {102.5, 0.5},
  //     {108.5, 2.0},
  //     {112.5, 4.0},
  //     {116.0, 8.0},
  //     {117.5, 12.0},
  //     {117.0, 19.},
  //     {115.0, 26.0},
  //     {110.0, 36.0},
  //     {106.5, 45.0},
  //     {106.0, 55.0},
  //     {109.5, 63.5},
  //     {114.0, 68.5},
  //     {121.5, 73.5},
  //     {130.0, 75.5},

  //     {139.5, 76.5},

  //     {149.0, 75.5},
  //     {157.5, 73.5},
  //     {165.0, 68.5},
  //     {169.5, 63.5},
  //     {173.0, 55.0},
  //     {172.5, 45.0},
  //     {169.0, 36.0},
  //     {164.0, 26.0},
  //     {162.0, 19.},
  //     {161.5, 12.0},
  //     {163.0, 8.0},
  //     {166.5, 4.0},
  //     {171.0, 2.0},
  //     {176.5, 0.5},
  //     {184.0, 0.0},
  //     {198.5, 0.5},
  //     {211.0, 1.5},
  //     {222.5, 3.0},
  //     {239.5, 5.0},
  //     {253.0, 6.5},
  //     {266.0, 7.5},
  //     {279.5, 7.5},

  //     {60.0, -100.0},
  // };

  // Point piece[46] = {
  //     {0.0f, 7.5f},
  //     {13.5f, 7.5f},
  //     {26.5f, 6.5f},
  //     {40.0f, 5.0f},
  //     {56.5f, 3.0f},
  //     {68.0f, 1.5f},
  //     {80.5f, 0.5f},
  //     {95.0f, 0.0f},
  //     {102.5f, 0.5f},
  //     {108.5f, 2.0f},
  //     {112.5f, 4.0f},
  //     {116.0f, 8.0f},
  //     {117.5f, 12.0f},
  //     {117.0f, 19.f},
  //     {115.0f, 26.0f},
  //     {110.0f, 36.0f},
  //     {106.5f, 45.0f},
  //     {106.0f, 55.0f},
  //     {109.5f, 63.5f},
  //     {114.0f, 68.5f},
  //     {121.5f, 73.5f},
  //     {130.0f, 75.5f},

  //     {139.5f, 76.5f},

  //     {149.0f, 75.5f},
  //     {157.5f, 73.5f},
  //     {165.0f, 68.5f},
  //     {169.5f, 63.5f},
  //     {173.0f, 55.0f},
  //     {172.5f, 45.0f},
  //     {169.0f, 36.0f},
  //     {164.0f, 26.0f},
  //     {162.0f, 19.f},
  //     {161.5f, 12.0f},
  //     {163.0f, 8.0f},
  //     {166.5f, 4.0f},
  //     {171.0f, 2.0f},
  //     {176.5f, 0.5f},
  //     {184.0f, 0.0f},
  //     {198.5f, 0.5f},
  //     {211.0f, 1.5f},
  //     {222.5f, 3.0f},
  //     {239.5f, 5.0f},
  //     {253.0f, 6.5f},
  //     {266.0f, 7.5f},
  //     {279.5f, 7.5f},

  //     {60.0f, -100.0f},
  // };

  Point flatPiece[2] = {{0.f, 7.5f}, {0.f, 139.5f}};

  GLuint renderPieces()
  {
    GLuint id = glGenLists(1);  // create a display list
    if(!id) return id;          // failed to create a list, return 0

    GLUtesselator *tess = gluNewTess(); // create a tessellator
    if(!tess) return 0;  // failed to create tessellation object, return 0

    GLdouble quad1[4][3] = { {-1,3,0}, {0,0,0}, {1,3,0}, {0,2,0} };

       // register callback functions
    gluTessCallback(tess, GLU_TESS_BEGIN, (void(CALLBACK *)())Callbacks::tessBeginCB);
    gluTessCallback(tess, GLU_TESS_END, (void(CALLBACK *)())Callbacks::tessEndCB);
    gluTessCallback(tess, GLU_TESS_ERROR, (void(CALLBACK *)())Callbacks::tessErrorCB);
    gluTessCallback(tess, GLU_TESS_VERTEX, (void(CALLBACK *)())Callbacks::tessVertexCB);
    // gluTessCallback(tess, GLU_TESS_COMBINE, (void (__stdcall*)(void))Callbacks::tessCombineCB);

    glNewList(id, GL_COMPILE);
    glColor3f(1, 1, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINTS);
    gluTessBeginPolygon(tess, 0);
    gluTessBeginContour(tess);

    // for (int i = 0; i < 46; i++)
    // {
      gluTessVertex(tess, quad1[0], quad1[0]);
      gluTessVertex(tess, quad1[1], quad1[1]);
      gluTessVertex(tess, quad1[2], quad1[2]);
      gluTessVertex(tess, quad1[3], quad1[3]);
      // gluTessVertex(tess, piece[i], piece[i]);
      // gluTessVertex(tess, getPosition(piece[i]), getPosition(piece[i]));
      // glVertex2i(piece[i].x + 100, piece[i].y + 100);
      // std::cout << piece[i].x << std::endl;
    // }
    gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    glEndList();
    gluDeleteTess(tess);
    // glFlush();

    return id;
  }

  GLdouble *getPosition(Point point)
  {
    return new GLdouble[3]{point.x, point.y, point.z};
  }

  void invertPiece(JigSawPiece jsPiece)
  {
  }

  void mirrorPiece(JigSawPiece jsPiece)
  {
  }

  void draw()
  {
    int i;
    GLfloat x[7], y[7];
    GLfloat xt[200], yt[200], t;

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(.94f, .94f, .94f, .0f);

    x[0] = 100;
    x[1] = 150;
    x[2] = 200;

    x[3] = 100;
    x[4] = 200;
    x[5] = 300;
    x[6] = 350;

    y[0] = 45;
    y[1] = 20;
    y[2] = 45;

    y[3] = 400;
    y[4] = 120;
    y[5] = 0;
    y[6] = 400;

    // for (t = 0, i = 0; t < 1; i++, t = t + 0.006)
    // {
    //   // xt[i] = (1 - t) * x[0] + t * x[1];
    //   // yt[i] = (1 - t) * y[0] + t * y[1];
    //   xt[i] = pow(1 - t, 2) * x[0] + 2 * t * (1 - t) * x[1] + pow(t, 2) * x[2];
    //   yt[i] = pow(1 - t, 2) * y[0] + 2 * t * (1 - t) * y[1] + pow(t, 2) * y[2];
    // }

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(5);
    glBegin(GL_POINTS);

    for (i = 0; i < 200; i++)
    {
      glVertex2i(xt[i], yt[i]);
    }

    for (t = 0, i = 0; t < 1; i++, t = t + 0.006)
    {
      xt[i] = pow(1 - t, 3) * x[3] + 3 * t * pow(1 - t, 2) * x[4] + 3 * pow(t, 2) * (1 - t) * x[5] + pow(t, 3) * x[6];
      yt[i] = pow(1 - t, 3) * y[3] + 3 * t * pow(1 - t, 2) * y[4] + 3 * pow(t, 2) * (1 - t) * y[5] + pow(t, 3) * y[6];
    }

    for (i = 0; i < 200; i++)
    {
      glVertex2i(xt[i], yt[i]);
    }

    glColor3f(.96f, .325f, .325f);
    // glVertex2i(x[2], y[2]);

    for (i = 0; i < 6; i++)
    {
      glVertex2i(x[i], y[i]);
    }

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(5);
    glBegin(GL_POINTS);
    for (i = 0; i < 200; i++)
    {
      glVertex2i(xt[i], yt[i]);
      // std::cout << xt[i] << std::endl;
    }

    glColor3f(.96f, .325f, .325f);
    // glVertex2i(x[2], y[2]);

    for (i = 0; i < 6; i++)
    {
      glVertex2i(x[i], y[i]);
    }
    glEnd();
    glFlush();
  }

  void init()
  {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
  }
}

#endif
