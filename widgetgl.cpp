#include "widgetgl.h"
#include <QColor>
#include <QDebug>

WidgetGL::WidgetGL(QWidget *parent) :
    QGLWidget(parent),
    m_animationTimer(new QTimer)
{
    m_kinect = Kinect::instance();

    m_animationTimer->setSingleShot(false);
    connect(m_animationTimer, SIGNAL(timeout()), this, SLOT(animate()));
    m_animationTimer->start(25);

}

WidgetGL::~WidgetGL()
{

}

void WidgetGL::start()
{
    m_kinect->start();
}

void WidgetGL::paintGL()
{
    qDebug() << Q_FUNC_INFO;
    uint8_t* rgb_front = m_kinect->videoBuffer();
    qDebug() << Q_FUNC_INFO << *rgb_front;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gl_rgb_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, rgb_front);

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(255.0f, 255.0f, 255.0f, 255.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(640,0,0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(640,480,0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0,480,0);
    glEnd();

//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
//    glLoadIdentity();
//    qglColor( QColor(255, 0, 0, 0) );

//    glBegin(GL_TRIANGLES);						// Drawing Using Triangles
//	    glVertex3f( 0.0f, 1.0f, 0.0f);				// Top
//	    glVertex3f( -1.0f,-1.0f, 0.0f);				// Bottom Left
//	    glVertex3f( 1.0f,-1.0f, 0.0f);				// Bottom Right
//    glEnd();							//

//    glTranslatef(3.0f,0.0f,0.0f);					// Move Right 3 Units

//    glBegin(GL_QUADS);						// Draw A Quad
//	    glVertex3f(-1.0f, 1.0f, 0.0f);				// Top Left
//	    glVertex3f( 1.0f, 1.0f, 0.0f);				// Top Right
//	    glVertex3f( 1.0f,-1.0f, 0.0f);				// Bottom Right
//	    glVertex3f(-1.0f,-1.0f, 0.0f);				// Bottom Left
//    glEnd();

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//	  QKinect *kinect=QKinect::instance();
////	  if(m_mode ==0)
//	  {
//		  kinect->getRGB(m_rgb);
//	  }
////	  else if(m_mode == 1)
////	  {
////		  kinect->getDepth(m_rgb);
////	  }
//	  glBindTexture(GL_TEXTURE_2D, m_rgbTexture);
//	  glTexImage2D(GL_TEXTURE_2D, 0, 3, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, &m_rgb[0]);
//	  glLoadIdentity();

//	  glEnable(GL_TEXTURE_2D);

//	  glBegin(GL_TRIANGLE_FAN);
//		  glColor4f(255.0f, 255.0f, 255.0f, 255.0f);
//		  glTexCoord2f(0, 0); glVertex3f(0,0,0);
//		  glTexCoord2f(1, 0); glVertex3f(640,0,0);
//		  glTexCoord2f(1, 1); glVertex3f(640,480,0);
//		  glTexCoord2f(0, 1); glVertex3f(0,480,0);
//	  glEnd();
}

void WidgetGL::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
//    glGenTextures(1, &gl_depth_tex);
//    glBindTexture(GL_TEXTURE_2D, gl_depth_tex);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenTextures(1, &gl_rgb_tex);
    glBindTexture(GL_TEXTURE_2D, gl_rgb_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void WidgetGL::resizeGL( int w, int h )
{
    glViewport( 0, 0, (GLint)w, (GLint)h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho (0, 640, 480, 0, -1.0f, 1.0f);
    glMatrixMode( GL_MODELVIEW );
}

void WidgetGL::animate()
{
    updateGL();
}
