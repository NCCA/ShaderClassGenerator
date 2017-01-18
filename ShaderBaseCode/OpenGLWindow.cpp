  /*
 * Basic GL Window modified from the example here
 * http://qt-project.org/doc/qt-5.0/qtgui/openglwindow.html
 * adapted to use NGL
 */
#include "OpenGLWindow.h"
#include <QKeyEvent>
#include <QApplication>
#include <iostream>
#include <array>




void OpenGLWindow::createQuad()
{
  // a simple quad object
  std::array<float,18> vert;
  const static float s=0.8f;
  vert[0] =-s; vert[1] =  s; vert[2] =-1.0;
  vert[3] = s; vert[4] =  s; vert[5] =-1.0;
  vert[6] = -s; vert[7] = -s; vert[8]= -1.0;

  vert[9] =-s; vert[10]= -s; vert[11]=-1.0;
  vert[12] =s; vert[13]= -s; vert[14]=-1.0;
  vert[15] =s; vert[16]= s; vert[17]=-1.0;
  // allocate a VertexArray
  glGenVertexArrays(1, &m_vaoID);
  // now bind a vertex array object for our verts
  glBindVertexArray(m_vaoID);
  // now we are going to bind this to our vbo
  GLuint vboID;
  glGenBuffers(1, &vboID);
  // now bind this to the VBO buffer
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  // allocate the buffer datra
  glBufferData(GL_ARRAY_BUFFER, 18*sizeof(GLfloat), &vert[0], GL_STATIC_DRAW);
  // now fix this to the attribute buffer 0
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  // enable and bind this attribute (will be inPosition in the shader)
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

}


OpenGLWindow::OpenGLWindow()
{
  setTitle("First Shaders in OpenGL 3.2");

}

OpenGLWindow::~OpenGLWindow()
{
}



void OpenGLWindow::initializeGL()
{
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);			   // Grey Background

  std::cerr << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;

  // create the Quad
  createQuad();
  // load the shaders
  m_shader=BasicShader::getShader();
  m_shader->bind();
  BasicShader::setBaseColour(1.0f,0.0f,0.0f);
  std::cout<<"ID on new instance "<<BasicShader::getProgramID()<<'\n';
}


void OpenGLWindow::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // set the first attrib (1) to 1,0,0 red
  //glVertexAttrib3f(1,1,0,0);
  glViewport(0,0,m_width,m_height);
  glBindVertexArray(m_vaoID);		// select first bind the array
  glDrawArrays(GL_TRIANGLES, 0, 6);	// draw object
}



void OpenGLWindow::resizeGL(int _w , int _h)
{
  m_width  = static_cast<int>( _w * devicePixelRatio() );
  m_height = static_cast<int>( _h * devicePixelRatio() );
}

void OpenGLWindow::keyPressEvent(QKeyEvent *_event)
{
  switch (_event->key())
  {
   case Qt::Key_Escape : QApplication::exit(EXIT_SUCCESS); break;
   case Qt::Key_W : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
   case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;
   case Qt::Key_1 : glVertexAttrib3f(1,1,0,0); break;
   case Qt::Key_2 : glVertexAttrib3f(1,0,1,0); break;
   case Qt::Key_3 : glVertexAttrib3f(1,0,0,1); break;
  }
  update();
}
