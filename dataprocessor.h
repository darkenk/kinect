#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <opencv/cv.h>
#include <QObject>

class DataProcessor : public QObject
{
    Q_OBJECT
public:
    explicit DataProcessor(QObject *parent = 0);
    virtual ~DataProcessor();

    uint8_t* processImage(uint8_t* image);

signals:

public slots:

private:
    int m_rgbDepth;
    int m_rgbChannels;
    int m_rgbSize;

    IplImage* m_rgbResultImage;
    IplImage* m_grayCurrentImage;
    IplImage* m_grayPrevImage;
    IplImage* m_grayResultImage;

    bool m_firstRun;

};

#endif // DATAPROCESSOR_H
