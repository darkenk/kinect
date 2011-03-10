#ifndef KINECT_H
#define KINECT_H

#include <libfreenect.h>
#include <QObject>
#include <QMutex>
#include <QThread>

class Kinect : public QThread
{
    Q_OBJECT
public:
    ~Kinect();

    static Kinect* instance();

    static void video_cb(freenect_device *dev, void *rgb, uint32_t timestamp);
    static void depth_cb(freenect_device *dev, void *v_depth, uint32_t timestamp);



    void setLedColor(freenect_led_options ledColor);
    uint8_t* videoBuffer();
    uint8_t* depthBuffer();

signals:

public slots:

protected:
    void run();

private:
    Kinect(QObject *parent = 0);
    void videoCallback(freenect_device *dev, void *rgb, uint32_t timestamp);
    void depthCallback(freenect_device *dev, void *depth, uint32_t timestamp);

    freenect_context* m_ctx;
    freenect_device* m_dev;
    QMutex m_mutex;
    uint8_t* m_backVideoBuffer;
    uint8_t* m_midVideoBuffer;
    uint8_t* m_frontVideoBuffer;

    uint8_t* m_midDepth;
    uint8_t* m_frontDepth;

    static Kinect* m_instance;
};

#endif // KINECT_H
