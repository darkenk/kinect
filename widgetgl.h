#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include "kinect.h"
#include "dataprocessor.h"

class WidgetGL : public QGLWidget
{
    Q_OBJECT

public:
    WidgetGL(QWidget* parent = 0);
    virtual ~WidgetGL();
    void start();

    void setThresholdLevel(int thresholdLevel) { m_dataProcessor->setThresholdLevel(thresholdLevel); }
    int thresholdLevel() { return m_dataProcessor->thresholdLevel(); }

signals:
    void nonZeroPixelChanged(int nonZeroPixels);

protected:
    void paintGL();
    void initializeGL();
    void resizeGL(int w, int h);

protected slots:
    void animate();

private:
    std::vector<uint8_t> m_rgb;
    GLuint m_rgbTexture;
    Kinect* m_kinect;
    GLuint gl_rgb_tex;
    GLuint gl_depth_tex;

    QTimer* m_animationTimer;
    DataProcessor* m_dataProcessor;

};

#endif // GLWIDGET_H
