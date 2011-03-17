#include "widgetgl.h"
#include <QColor>
#include <QDebug>

WidgetGL::WidgetGL(QWidget *parent) :
    QGLWidget(parent),
    m_animationTimer(new QTimer),
    m_dataProcessor(new DataProcessor)
{
    m_kinect = Kinect::instance();

    m_animationTimer->setSingleShot(false);
    connect(m_animationTimer, SIGNAL(timeout()), this, SLOT(animate()));
    m_animationTimer->start(25);
    setFixedSize(1280, 480);

    connect(m_dataProcessor, SIGNAL(nonZerosPixelsChanged(int)), this, SIGNAL(nonZeroPixelChanged(int)));
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
    //qDebug() << Q_FUNC_INFO;
    uint8_t* rgb_front = m_kinect->videoBuffer();
    uint8_t* depth_front = m_kinect->depthBuffer();
    //qDebug() << Q_FUNC_INFO << *rgb_front;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gl_rgb_tex);
    uint8_t* rgbImage = m_dataProcessor->processImage(rgb_front);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, rgbImage);

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(255.0f, 255.0f, 255.0f, 255.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0,0,0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(640,0,0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(640,480,0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0,480,0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, gl_depth_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, depth_front);

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(255.0f, 255.0f, 255.0f, 255.0f);
    glTexCoord2f(0, 0); glVertex3f(640,0,0);
    glTexCoord2f(1, 0); glVertex3f(1280,0,0);
    glTexCoord2f(1, 1); glVertex3f(1280,480,0);
    glTexCoord2f(0, 1); glVertex3f(640,480,0);
    glEnd();
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
    glGenTextures(1, &gl_depth_tex);
    glBindTexture(GL_TEXTURE_2D, gl_depth_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
    glOrtho (0, 1280, 480, 0, -1.0f, 1.0f);
    glMatrixMode( GL_MODELVIEW );
}

void WidgetGL::animate()
{
    updateGL();
}
