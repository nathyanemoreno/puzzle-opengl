#include <GL/glut.h>
#include <iostream>
#include <string.h>

#include "src/JigSaw.h"

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

JigsawPiece piece = {
    {true, false},
    {true, true},
    {false, true},
    {false, false},
};

JigsawPosition pos = {
    320,
    320,
    piece};
JigsawPosition pos2 = {
    120,
    320,
    piece};
JigsawPosition pieces[] = {
    pos,
    pos2};

// ============ GLUT FUNCTIONS ============ //
void render(void);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void reshape(int w, int h);
bool isPieceSelected(int x, int y);

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(640, 640);
  glutCreateWindow("Jigsaw");

  glClearColor(0.152, 0.164, 0.207, 1.0);
  glOrtho(0, 640, 0, 640, -1, 1);

  glutDisplayFunc(render);

  glutMainLoop();
  return 0;
}

void drawJigsawPieceEdge(JigsawPieceEdge edge, EdgeType edgeType, float centerX, float centerY)
{
  int i;
  float originX, originY;

  switch (edgeType)
  {
  case TOP:
    if (edge.isFlat)
    {
      glBegin(GL_POLYGON);
      glVertex2i(centerX, centerY);
      glVertex2i(centerX - HALF_PIECE_WIDTH, centerY + HALF_PIECE_WIDTH);
      glVertex2i(centerX + HALF_PIECE_WIDTH, centerY + HALF_PIECE_WIDTH);
      glEnd();
    }
    break;
  case RIGHT:
    if (edge.isFlat)
    {
      glBegin(GL_POLYGON);
      glVertex2i(centerX, centerY);
      glVertex2i(centerX + HALF_PIECE_WIDTH, centerY + HALF_PIECE_WIDTH);
      glVertex2i(centerX + HALF_PIECE_WIDTH, centerY - HALF_PIECE_WIDTH);
      glEnd();
    }
    else
    {
      // Render Curve
      originX = centerX + HALF_PIECE_WIDTH - 7.5f;
      originY = centerY + HALF_PIECE_WIDTH;

      glBegin(GL_POLYGON);
      glVertex2i(centerX, centerY);
      for (i = 0; i < 14; i++)
      {
        glVertex2i(originX + jigsawEdgeCurve[i][1], originY - jigsawEdgeCurve[i][0]);
      }
      glEnd();

      // Blá
      glColor3f(0, 1, 0);
      glBegin(GL_POLYGON);
      glVertex2i(centerX + 177.75, centerY);
      for (i = 13; i < 34; i++)
      {
        glVertex2i(originX + jigsawEdgeCurve[i][1], originY - jigsawEdgeCurve[i][0]);
      }
      glEnd();

      // Blá Blá
      glColor3f(0, 0, 1);
      glBegin(GL_POLYGON);
      glVertex2i(centerX, centerY);
      glVertex2i(originX + jigsawEdgeCurve[13][1], originY - jigsawEdgeCurve[13][0]);
      glVertex2i(centerX + 177.75, centerY);
      glVertex2i(originX + jigsawEdgeCurve[33][1], originY - jigsawEdgeCurve[33][0]);
      glEnd();

      glColor3f(1, 0, 0);
      glBegin(GL_POLYGON);
      glVertex2i(centerX, centerY);
      for (i = 33; i < 46; i++)
      {
        glVertex2i(originX + jigsawEdgeCurve[i][1], originY - jigsawEdgeCurve[i][0]);
      }
      glEnd();
    }
    break;
  case BOTTOM:
    if (edge.isFlat)
    {
      glBegin(GL_POLYGON);
      glVertex2i(centerX, centerY);
      glVertex2i(centerX - HALF_PIECE_WIDTH, centerY - HALF_PIECE_WIDTH);
      glVertex2i(centerX + HALF_PIECE_WIDTH, centerY - HALF_PIECE_WIDTH);
      glEnd();
    }
    else
    {
      if (edge.isMirrorning)
      {
        // Render Curve
        originX = centerX - HALF_PIECE_WIDTH;
        originY = centerY - HALF_PIECE_WIDTH + 7.5f;

        glBegin(GL_POLYGON);
        glVertex2i(centerX, centerY);
        for (i = 0; i < 14; i++)
        {
          glVertex2i(originX + jigsawEdgeCurve[i][0], originY - jigsawEdgeCurve[i][1]);
        }
        glEnd();

        // Blá
        glColor3f(0, 1, 0);
        glBegin(GL_POLYGON);
        glVertex2i(centerX, centerY - 177.75);
        for (i = 13; i < 34; i++)
        {
          glVertex2i(originX + jigsawEdgeCurve[i][0], originY - jigsawEdgeCurve[i][1]);
        }
        glEnd();

        // Blá Blá
        glColor3f(0, 0, 1);
        glBegin(GL_POLYGON);
        glVertex2i(centerX, centerY);
        glVertex2i(originX + jigsawEdgeCurve[13][0], originY - jigsawEdgeCurve[13][1]);
        glVertex2i(centerX, centerY - 177.75);
        glVertex2i(originX + jigsawEdgeCurve[33][0], originY - jigsawEdgeCurve[33][1]);
        glEnd();

        glColor3f(1, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2i(centerX, centerY);
        for (i = 33; i < 46; i++)
        {
          glVertex2i(originX + jigsawEdgeCurve[i][0], originY - jigsawEdgeCurve[i][1]);
        }
        glEnd();
      }
      // } else {
      //   glBegin(GL_POLYGON);
      //   glVertex2i(centerX, centerY);
      //   glVertex2i(centerX - HALF_PIECE_WIDTH, centerY - HALF_PIECE_WIDTH);
      //   glVertex2i(centerX + HALF_PIECE_WIDTH, centerY - HALF_PIECE_WIDTH);
      //   glEnd();
      // }
    }
    break;
  case LEFT:
    if (edge.isFlat)
    {
      glBegin(GL_POLYGON);
      glVertex2i(centerX, centerY);
      glVertex2i(centerX - HALF_PIECE_WIDTH, centerY - HALF_PIECE_WIDTH);
      glVertex2i(centerX - HALF_PIECE_WIDTH, centerY + HALF_PIECE_WIDTH);
      glEnd();
    }
    else
    {
      // Render Curve
      originX = centerX - HALF_PIECE_WIDTH + 7.5f;
      originY = centerY + HALF_PIECE_WIDTH;

      glBegin(GL_POLYGON);
      glVertex2i(centerX, centerY);
      for (i = 0; i < 14; i++)
      {
        glVertex2i(originX + jigsawEdgeCurve[i][1], originY - jigsawEdgeCurve[i][0]);
      }
      glEnd();

      // Blá
      glColor3f(0, 1, 0);
      glBegin(GL_POLYGON);
      glVertex2i(centerX - 177.75, centerY);
      for (i = 13; i < 34; i++)
      {
        glVertex2i(originX + jigsawEdgeCurve[i][1], originY - jigsawEdgeCurve[i][0]);
      }
      glEnd();

      // Blá Blá
      glColor3f(0, 0, 1);
      glBegin(GL_POLYGON);
      glVertex2i(centerX, centerY);
      glVertex2i(originX + jigsawEdgeCurve[13][1], originY - jigsawEdgeCurve[13][0]);
      glVertex2i(centerX - 177.75, centerY);
      glVertex2i(originX + jigsawEdgeCurve[33][1], originY - jigsawEdgeCurve[33][0]);
      glEnd();

      glColor3f(1, 0, 0);
      glBegin(GL_POLYGON);
      glVertex2i(centerX, centerY);
      for (i = 33; i < 46; i++)
      {
        glVertex2i(originX + jigsawEdgeCurve[i][1], originY - jigsawEdgeCurve[i][0]);
      }
      glEnd();
    }
    break;

  default:
    break;
  }
}

void drawJigsawPiece(JigsawPosition position)
{
  // Set Color

  // Draw top
  glColor3f(1, 1, 1);
  drawJigsawPieceEdge(position.piece.top, TOP, position.x, position.y);

  // Draw right
  glColor3f(0, 1, 1);
  drawJigsawPieceEdge(position.piece.right, RIGHT, position.x, position.y);

  // Draw bottom
  glColor3f(1, 0, 1);
  drawJigsawPieceEdge(position.piece.bottom, BOTTOM, position.x, position.y);

  // Draw left
  glColor3f(1, 1, 0);
  drawJigsawPieceEdge(position.piece.left, LEFT, position.x, position.y);
}

void drawJigsawCurve(JigsawPieceEdge edge, EdgeType edgeType, float centerX, float centerY)
{
  int i;
  float originX, originY;

  if (edge.isFlat)
  {
    glBegin(GL_POLYGON);
    glVertex2i(centerX, centerY);
    glVertex2i(centerX + HALF_PIECE_WIDTH, centerY + HALF_PIECE_WIDTH);
    glVertex2i(centerX + HALF_PIECE_WIDTH, centerY + HALF_PIECE_WIDTH);
    glEnd();
  }
  else
  {
  }
}

bool isPieceSelected(int x, int y)
{
  for (int i = 0; i < 2; i++)
  {

    if (x > pieces[i].x - HALF_PIECE_WIDTH && x < pieces[i].x + HALF_PIECE_WIDTH &&
        y > pieces[i].y - HALF_PIECE_WIDTH && y < pieces[i].y + HALF_PIECE_WIDTH)
    {
      current = &pieces[i];
      std::cout << current->x << std::endl;
      return true;
    }
  }
  return false;
}

void render(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  for (int i = 0; i < 2; i++)
  {
    drawJigsawPiece(pieces[i]);
  }

  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);

  glFlush();
}

void mouse(int button, int state, int x, int y)
{
  switch (button)
  {
  case GLUT_LEFT_BUTTON:
    if (state == GLUT_DOWN)
    {
      std::cout << pieceSelected << std::endl;
      pieceSelected = true;
      isPieceSelected(x, y);
    }
    else
    {
      pieceSelected = false;
    }
    break;

  default:
    break;
  }
}

void mouseMotion(int x, int y)
{
  if (pieceSelected)
  {
    current->x = x;
    current->y = 640 - y;

    glutPostRedisplay();
  }
}

void reshape(int w, int h)
{
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
