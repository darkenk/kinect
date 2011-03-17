#include "dataprocessor.h"
#include <opencv/cv.h>
#include <QDebug>

DataProcessor::DataProcessor(QObject *parent) :
    QObject(parent)
{
    m_rgbDepth = IPL_DEPTH_8U;
    m_rgbChannels = 3;
    m_rgbSize = 640*480*3;

    m_rgbResultImage = cvCreateImage(cvSize(640, 480), m_rgbDepth, m_rgbChannels);
    m_grayCurrentImage = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);
    m_grayPrevImage = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);
    m_grayResultImage = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);

    m_firstRun = true;
}

DataProcessor::~DataProcessor()
{
    cvReleaseImage(&m_rgbResultImage);
    cvReleaseImage(&m_grayCurrentImage);
    cvReleaseImage(&m_grayPrevImage);
    cvReleaseImage(&m_grayResultImage);
}

uint8_t* DataProcessor::processImage(uint8_t *image)
{
//    IplImage* cvImage = cvCreateImage(cvSize(640, 480), m_rgbDepth, m_rgbChannels);
//    cvSetData(cvImage, image, cvImage->widthStep);
    cvSetData(m_rgbResultImage, image, m_rgbResultImage->widthStep);
    //swap the images
    IplImage* tmp = m_grayPrevImage;
    m_grayPrevImage = m_grayCurrentImage;
    m_grayCurrentImage = tmp;
    cvCvtColor(m_rgbResultImage, m_grayCurrentImage, CV_RGB2GRAY);
    cvSmooth(m_grayCurrentImage, m_grayCurrentImage, 3);

    if (m_firstRun) {
	m_firstRun = false;
	cvCopy(m_grayCurrentImage, m_grayPrevImage);
    }

    cvAbsDiff(m_grayPrevImage, m_grayCurrentImage, m_grayResultImage);
    cvThreshold(m_grayResultImage, m_grayResultImage, 40, 255, CV_THRESH_BINARY);
    int nonZero = cvCountNonZero(m_grayResultImage);

    cvAddS(m_rgbResultImage, cvScalar(255, 0, 0, 0), m_rgbResultImage, m_grayResultImage);
    //cvSmooth(cvImage, m_rgbResultImage);
    //cvCanny(m_rgbResultImage, m_rgbResultImage, 10, 100);
//    cvReleaseImageHeader(&cvImage);
    qDebug() << Q_FUNC_INFO << " non zero elements " << nonZero;
    return (uint8_t*)m_rgbResultImage->imageData;
}


