#include "kinect.h"
#include <QDebug>

Kinect* Kinect::m_instance = 0;

Kinect* Kinect::instance()
{
    if (!m_instance) {
	m_instance = new Kinect();
    }
    return m_instance;

}


Kinect::Kinect(QObject *parent) :
    QThread(parent)
{
    Q_ASSERT(freenect_init(&m_ctx, NULL) >= 0);
    freenect_set_log_level(m_ctx, FREENECT_LOG_DEBUG);
    int devices = freenect_num_devices(m_ctx);
    qDebug() << "Number of devices " << devices;

    Q_ASSERT(freenect_open_device(m_ctx, &m_dev, 1) >= 0);

    m_backVideoBuffer = new uint8_t[640*480*3];
    m_midVideoBuffer = new uint8_t[640*480*3];
    m_frontVideoBuffer = new uint8_t[640*480*3];

}

Kinect::~Kinect()
{
    freenect_close_device(m_dev);
    freenect_shutdown(m_ctx);
}

uint8_t* Kinect::videoBuffer()
{
    QMutexLocker locker(&m_mutex);
    return m_midVideoBuffer;
}

void Kinect::videoCallback(freenect_device *dev, void *rgb, uint32_t timestamp)
{
    qDebug() << Q_FUNC_INFO;
    QMutexLocker locker (&m_mutex);

    // swap buffers
    //assert (rgb_back == rgb);
    m_backVideoBuffer = m_midVideoBuffer;
    freenect_set_video_buffer(dev, m_backVideoBuffer);
    m_midVideoBuffer = (uint8_t*)rgb;
}

void Kinect::depthCallback(freenect_device *dev, void *rgb, uint32_t timestamp)
{
}



void Kinect::video_cb(freenect_device *dev, void *rgb, uint32_t timestamp)
{
    m_instance->videoCallback(dev, rgb, timestamp);
}

void Kinect::depth_cb(freenect_device *dev, void *v_depth, uint32_t timestamp)
{
    qDebug() << Q_FUNC_INFO;
}

void Kinect::run()
{
    freenect_set_tilt_degs(m_dev, 0);
    freenect_set_led(m_dev,LED_RED);
    freenect_set_depth_callback(m_dev, depth_cb);
    freenect_set_video_callback(m_dev, video_cb);
    freenect_set_video_format(m_dev, FREENECT_VIDEO_RGB);
    freenect_set_depth_format(m_dev, FREENECT_DEPTH_11BIT);
    freenect_set_video_buffer(m_dev, m_backVideoBuffer);

    freenect_start_depth(m_dev);
    freenect_start_video(m_dev);

    bool die = false;

    while (!die && freenect_process_events(m_ctx) >= 0) {
	    //Throttle the text output
//	    if (accelCount++ >= 2000)
//	    {
//		    accelCount = 0;
//		    freenect_raw_tilt_state* state;
//		    freenect_update_tilt_state(f_dev);
//		    state = freenect_get_tilt_state(f_dev);
//		    double dx,dy,dz;
//		    freenect_get_mks_accel(state, &dx, &dy, &dz);
//		    printf("\r raw acceleration: %4d %4d %4d  mks acceleration: %4f %4f %4f", state->accelerometer_x, state->accelerometer_y, state->accelerometer_z, dx, dy, dz);
//		    fflush(stdout);
//	    }

//	    if (requested_format != current_format) {
//		    freenect_stop_video(f_dev);
//		    freenect_set_video_format(f_dev, requested_format);
//		    freenect_start_video(f_dev);
//		    current_format = requested_format;
//	    }
    }

    freenect_stop_depth(m_dev);
    freenect_stop_video(m_dev);


}


