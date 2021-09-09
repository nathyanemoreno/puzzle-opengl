#include <GL/glut.h>
#include <iostream>
#include <string.h>
#include <time.h>

#include "../include/upng/upng.h"
#include "JigSaw.h"

float PIECE_WIDTH = 279.5f;
float HALF_PIECE_WIDTH = PIECE_WIDTH / 2.0f;

int WINDOW_WIDTH = 640;
int WINDOW_HEIGHT = 640;

JigsawPosition *current;
bool pieceSelected = false;

float originX = 0;
float originY = 0;

float scaleX = 1;
float scaleY = 1;

float jigSawPuzzleSize = 80;

upng_t *upng;
GLuint texture;

// JigsawPiece piece = {
//     {true, false},
//     {true, true},
//     {false, true},
//     {false, false},
// };

const float PUZZLE_PIECES_COUNT = 1;
JigsawPosition puzzlePieces[144];

// ============ GLUT FUNCTIONS ============ //
void render(void);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void reshape(int w, int h);
bool isPieceSelected(int x, int y);

void initTexture() {
  upng = upng_new_from_file("src/images/puzzle01.png");
  upng_decode(upng);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, upng_get_width(upng), upng_get_height(upng), 0, GL_RGBA, GL_UNSIGNED_BYTE, upng_get_buffer(upng));
}

void initJigsawPuzzle() {
  /* initialize random seed: */
  srand (time(NULL));
  
  for (int r = 0; r < 9; r++) {
    for (int c = 0; c < 16; c++) {
      std::cout << rand() % 10;
      puzzlePieces[c + r * 16] = {
          320,
          320,
          {// TOP
           {r == 0, r > 0 ? !puzzlePieces[c + (r - 1) * 16].piece.bottom.isMirroring : (rand() % 10 < 5)},
           // RIGHT
           {c == 15, (rand() % 10 < 5)},
           // BOTTOM
           {r == 8, (rand() % 10 < 5)},
           // LEFT
           {c == 0, c > 0 ? !puzzlePieces[(c - 1) + r * 16].piece.right.isMirroring : (rand() % 10 < 5)}}
          // break line
      };
    }
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_STENCIL);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(640, 640);
  glutCreateWindow("JigSaw Puzzle OpenGL");

  glClearColor(0.152, 0.164, 0.207, 1.0);
  glOrtho(0, 640, 640, 0, -1, 1);

  glutDisplayFunc(render);

  initJigsawPuzzle();
  initTexture();

  glutMainLoop();
  return 0;
}

void drawJigsawCurve(JigsawPieceEdge edge, EdgeType edgeType, float centerX, float centerY) {
  int i;
  float curveOriginX, curveOriginY;

  bool drawVertically = edgeType == TOP || edgeType == BOTTOM;

  // T: -1 / R: 1 / B: 1 / L: -1
  int scaleAux = 1;
  int scaleX = edgeType == LEFT ? -1 : 1;
  // T: -1 / R: -1 / B: -1 / L: -1
  int scaleY = edgeType == TOP ? 1 : -1;

  int pX = !drawVertically ? 1 : 0;
  int pY = !drawVertically ? 0 : 1;

  int limit1 = edge.isMirroring ? 24 : 14;
  int limit2 = edge.isMirroring ? 23 : 33;

  std::cout << "---- Drawing Piece Edge ----" << std::endl;
  std::cout << "drawVertically: ";
  std::cout << drawVertically << std::endl;
  std::cout << "scaleX: ";
  std::cout << scaleX << std::endl;
  std::cout << "scaleY: ";
  std::cout << scaleY << std::endl;

  // T: -1 / R: 1 / B: -1 / L: -1
  curveOriginX = centerX + HALF_PIECE_WIDTH * (edgeType == RIGHT ? 1 : -1);
  // T: 1 / R: 1 / B: -1 / L: 1
  curveOriginY = centerY + HALF_PIECE_WIDTH * (edgeType == BOTTOM ? -1 : 1);

  // mirror curve
  if (edge.isMirroring) {
    if (drawVertically) {
      scaleY *= -1;
    } else {
      scaleX *= -1;
      scaleAux = -1;
    }
  }

  // fix origin tranlation
  if (drawVertically) {
    curveOriginY -= scaleY * 7.5f;
  } else {
    curveOriginX -= scaleX * 7.5f;
  }

  glBegin(GL_POLYGON);
  if (edge.isMirroring) {
    glVertex2i(
        centerX - 70 * (!drawVertically ? edgeType == LEFT ? 1 : -1 : 1),
        centerY - scaleAux * 70 * (drawVertically ? edgeType == BOTTOM ? 1 : -1 : 1)
        // break line
    );
  } else {
    glVertex2i(centerX, centerY);
  }
  for (i = 0; i < limit1; i++) {
    glVertex2i(
        curveOriginX + scaleX * jigsawEdgeCurve[i][pX],
        curveOriginY + scaleY * jigsawEdgeCurve[i][pY]
        // break line
    );
  }
  glEnd();

  glBegin(GL_POLYGON);
  if (edge.isMirroring) {
    glVertex2i(
        centerX + 70 * scaleAux * (!drawVertically ? edgeType == LEFT ? 1 : -1 : 1),
        centerY - 70 * (drawVertically ? edgeType == BOTTOM ? 1 : -1 : 1)
        // break line
    );
  } else {
    glVertex2i(centerX, centerY);
  }
  for (i = limit2; i < 46; i++) {
    glVertex2i(
        curveOriginX + scaleX * jigsawEdgeCurve[i][pX],
        curveOriginY + scaleY * jigsawEdgeCurve[i][pY]
        // break line
    );
  }
  glEnd();

  // Fill empty space
  if (!edge.isMirroring) {
    glBegin(GL_POLYGON);
    glVertex2i(centerX, centerY);
    glVertex2i(
        curveOriginX + scaleX * jigsawEdgeCurve[13][pX],
        curveOriginY + scaleY * jigsawEdgeCurve[13][pY]
        // break line
    );
    glVertex2i(
        centerX - 177.75 * (!drawVertically ? edgeType == LEFT ? 1 : -1 : 0),
        centerY - 177.75 * (drawVertically ? edgeType == BOTTOM ? 1 : -1 : 0)
        // break line
    );
    glVertex2i(
        curveOriginX + scaleX * jigsawEdgeCurve[33][pX],
        curveOriginY + scaleY * jigsawEdgeCurve[33][pY]
        // break line
    );
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(
        centerX - 177.75 * (!drawVertically ? edgeType == LEFT ? 1 : -1 : 0),
        centerY - 177.75 * (drawVertically ? edgeType == BOTTOM ? 1 : -1 : 0)
        // break line
    );
    for (i = 13; i < 34; i++) {
      glVertex2i(
          curveOriginX + scaleX * jigsawEdgeCurve[i][pX],
          curveOriginY + scaleY * jigsawEdgeCurve[i][pY]
          // break line
      );
    }
    glEnd();
  } else {
    glBegin(GL_POLYGON);
    glVertex2i(centerX, centerY);
    glVertex2i(
        centerX - 70 * (!drawVertically ? edgeType == LEFT ? 1 : -1 : 1),
        centerY - 70 * scaleAux * (drawVertically ? edgeType == BOTTOM ? 1 : -1 : 1)
        // break line
    );
    glVertex2i(
        centerX - 72 * (!drawVertically ? edgeType == LEFT ? 1 : -1 : 0),
        centerY - 72 * (drawVertically ? edgeType == BOTTOM ? 1 : -1 : 0)
        // break line
    );
    glVertex2i(
        centerX + 70 * scaleAux * (!drawVertically ? edgeType == LEFT ? 1 : -1 : 1),
        centerY - 70 * (drawVertically ? edgeType == BOTTOM ? 1 : -1 : 1)
        // break line
    );
    glEnd();
  }
}

void drawJigsawPieceEdge(JigsawPieceEdge edge, EdgeType edgeType, float centerX, float centerY) {
  if (!edge.isFlat) {
    drawJigsawCurve(edge, edgeType, centerX, centerY);
    return;
  }

  switch (edgeType) {
  case TOP:
    glBegin(GL_POLYGON);
    glVertex2i(centerX, centerY);
    glVertex2i(centerX - HALF_PIECE_WIDTH, centerY + HALF_PIECE_WIDTH);
    glVertex2i(centerX + HALF_PIECE_WIDTH, centerY + HALF_PIECE_WIDTH);
    glEnd();
    break;
  case RIGHT:
    glBegin(GL_POLYGON);
    glVertex2i(centerX, centerY);
    glVertex2i(centerX + HALF_PIECE_WIDTH, centerY + HALF_PIECE_WIDTH);
    glVertex2i(centerX + HALF_PIECE_WIDTH, centerY - HALF_PIECE_WIDTH);
    glEnd();
    break;
  case BOTTOM:
    glBegin(GL_POLYGON);
    glVertex2i(centerX, centerY);
    glVertex2i(centerX - HALF_PIECE_WIDTH, centerY - HALF_PIECE_WIDTH);
    glVertex2i(centerX + HALF_PIECE_WIDTH, centerY - HALF_PIECE_WIDTH);
    glEnd();
    break;
  case LEFT:
    glBegin(GL_POLYGON);
    glVertex2i(centerX, centerY);
    glVertex2i(centerX - HALF_PIECE_WIDTH, centerY - HALF_PIECE_WIDTH);
    glVertex2i(centerX - HALF_PIECE_WIDTH, centerY + HALF_PIECE_WIDTH);
    glEnd();
    break;

  default:
    break;
  }
}

void drawJigsawPiece(JigsawPosition position) {
  // Draw: piece
  glStencilOp(GL_FALSE, GL_FALSE, GL_REPLACE);
  glStencilFunc(GL_ALWAYS, 1, 0xFF);

  JigsawPiece piece = position.piece;

  // Draw TOP (white)
  drawJigsawPieceEdge(piece.top, TOP, position.x, position.y);

  // Draw RIGHT (cyan)
  // glColor3f(0, 1, 1);
  drawJigsawPieceEdge(piece.right, RIGHT, position.x, position.y);

  // Draw BOTTOM (magenta)
  // glColor3f(1, 0, 1);
  drawJigsawPieceEdge(piece.bottom, BOTTOM, position.x, position.y);

  // Draw LEFT (yellow)
  // glColor3f(1, 1, 0);
  drawJigsawPieceEdge(piece.left, LEFT, position.x, position.y);

  // Draw: texure
  // Set Texture
  glEnable(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, texture);

  glStencilOp(GL_FALSE, GL_FALSE, GL_KEEP);
  glStencilFunc(GL_EQUAL, 1, 0xFF);
  // glEnable(GL_BLEND);
  // glBlendFunc(GL_DST_COLOR, GL_ZERO);
  glBegin(GL_POLYGON);

  glTexCoord2f(0.0, 0.0);
  glVertex2i(100, 100);

  glTexCoord2f(1.0, 0.0);
  glVertex2i(540, 100);

  glTexCoord2f(1.0, 1.0);
  glVertex2i(540, 540);

  glTexCoord2f(0.0, 1.0);
  glVertex2i(100, 540);

  glEnd();
  glDisable(GL_TEXTURE_2D);
}

bool isPieceSelected(int x, int y) {
  for (int i = 0; i < PUZZLE_PIECES_COUNT; i++) {
    JigsawPosition position = puzzlePieces[i];
    if (x > position.x - HALF_PIECE_WIDTH && x < position.x + HALF_PIECE_WIDTH &&
        y > position.y - HALF_PIECE_WIDTH && y < position.y + HALF_PIECE_WIDTH) {
      current = &position;
      std::cout << current->x << std::endl;
      return true;
    }
  }
  return false;
}

void render(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  glEnable(GL_STENCIL_TEST);
  for (int i = 0; i < PUZZLE_PIECES_COUNT; i++) {
    drawJigsawPiece(puzzlePieces[i]);
  }

  glFlush();
}

void mouse(int button, int state, int x, int y) {
  switch (button) {
  case GLUT_LEFT_BUTTON:
    if (state == GLUT_DOWN) {
      std::cout << pieceSelected << std::endl;
      pieceSelected = true;
      isPieceSelected(x, y);
    } else {
      pieceSelected = false;
    }
    break;

  default:
    break;
  }
}

void mouseMotion(int x, int y) {
  if (pieceSelected) {
    current->x = x;
    current->y = 640 - y;

    glutPostRedisplay();
  }
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glLoadIdentity();
  glOrtho(0, w, h, 0, -1, 1);

  WINDOW_WIDTH = w;
  WINDOW_HEIGHT = h;

  scaleX = w / 640.0f;
  scaleY = h / 640.0f;

  jigSawPuzzleSize = std::min(scaleX, scaleY) * 80 - 9;

  originX = (w - 8 * jigSawPuzzleSize) / 2.0f;
  originY = (h - 8 * jigSawPuzzleSize) / 2.0f;

  glutPostRedisplay();
}
