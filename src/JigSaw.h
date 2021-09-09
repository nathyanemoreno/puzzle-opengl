#ifndef JIGSAW_H
#define JIGSAW_H

float jigsawEdgeCurve[46][2] = {
    {0.0f, 7.5f},
    {13.5f, 7.5f},
    {26.5f, 6.5f},
    {40.0f, 5.0f},
    {56.5f, 3.0f},
    {56.5f, 3.0f},
    {68.0f, 1.5f},
    {80.5f, 0.5f},
    {95.0f, 0.0f},
    {102.5f, 0.5f},
    {108.5f, 2.0f},
    {112.5f, 3.0f},
    {116.0f, 8.0f},
    {117.5f, 12.0f},
    {117.0f, 19.0f},
    {115.0f, 26.0f},
    {110.0f, 36.0f},
    {106.5f, 45.0f},
    {106.0f, 55.0f},
    {109.5f, 63.5f},
    {114.0f, 68.5f},
    {121.5f, 73.5f},
    {130.0f, 75.5f},

    {139.5f, 76.5f},

    {149.0f, 75.5f},
    {157.5f, 73.5f},
    {165.0f, 68.5f},
    {169.5f, 63.5f},
    {173.0f, 55.0f},
    {172.5f, 45.0f},
    {169.0f, 36.0f},
    {164.0f, 26.0f},
    {162.0f, 19.0f},
    {161.5f, 12.0f},
    {163.0f, 8.0f},
    {166.5f, 4.0f},
    {171.0f, 2.0f},
    {176.5f, 0.5f},
    {184.0f, 0.0f},
    {198.5f, 0.5f},
    {211.0f, 1.5f},
    {222.5f, 3.0f},
    {239.5f, 5.0f},
    {253.0f, 6.5f},
    {266.0f, 7.5f},
    {279.5f, 7.5f}};

enum EdgeType {
  TOP,
  RIGHT,
  BOTTOM,
  LEFT
};

struct JigsawPieceEdge {
  bool isFlat;
  bool isMirrorning;
};

struct JigsawPiece {
  JigsawPieceEdge top;
  JigsawPieceEdge right;
  JigsawPieceEdge bottom;
  JigsawPieceEdge left;
};

struct JigsawPosition {
  GLfloat x;
  GLfloat y;
  JigsawPiece piece;
};

#endif