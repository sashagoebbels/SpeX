#include "draw_gl.H"

void drawcube(int wire) {
  // glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
  //   glColor3ub(0,0,255);
  //   v3f(v0); v3f(v1); v3f(v2); v3f(v3);
  //   glEnd();
  //   glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
  //   glColor3ub(0,255,255); v3f(v4); v3f(v5); v3f(v6); v3f(v7);
  //   glEnd();
  //   glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
  //   glColor3ub(255,0,255); v3f(v0); v3f(v1); v3f(v5); v3f(v4);
  //   glEnd();
  //   glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
  //   glColor3ub(255,255,0); v3f(v2); v3f(v3); v3f(v7); v3f(v6);
  //   glEnd();
  //   glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
  //   glColor3ub(0,255,0); v3f(v0); v3f(v4); v3f(v7); v3f(v3);
  //   glEnd();
  //   glBegin(wire ? GL_LINE_LOOP : GL_POLYGON);
  //   glColor3ub(255,0,0); v3f(v1); v3f(v2); v3f(v6); v3f(v5);
  //   glEnd();
}

void cube_box::draw() {
  lasttime = lasttime+speed;
  if (!valid()) {
    glLoadIdentity();
    glViewport(0,0,w(),h());
    glEnable(GL_DEPTH_TEST);
    glFrustum(-1,1,-1,1,2,10000);
    glTranslatef(0,0,-10);
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glRotatef(float(lasttime*1.6),0,0,1);
  glRotatef(float(lasttime*4.2),1,0,0);
  glRotatef(float(lasttime*2.3),0,1,0);
  glTranslatef(-1.0, 1.2f, -1.5);
  glScalef(float(size),float(size),float(size));
  drawcube(wire);
  glPopMatrix();
}
