#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "kinect.h"
#include <QDebug>
#include <QPalette>
#include <QColorGroup>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_glwidget(new WidgetGL)

{
    ui->setupUi(this);
    ui->verticalLayout->addWidget(m_glwidget);
    ui->thresholdLevel->setValue(m_glwidget->thresholdLevel());
    connect(m_glwidget, SIGNAL(nonZeroPixelChanged(int)), this, SLOT(onNonZeroPixelChanged(int)));

    m_alarmLevel = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    m_glwidget->start();
}

void MainWindow::on_pushButton_clicked()
{
}

void MainWindow::on_captureButton_clicked()
{
    m_glwidget->start();
}

void MainWindow::on_ledComboBox_currentIndexChanged(int index)
{
    qDebug() << Q_FUNC_INFO << " " << index;
    Kinect::instance()->setLedColor((freenect_led_options)index);
}

void MainWindow::on_thresholdLevel_valueChanged(int value)
{
    m_glwidget->setThresholdLevel(value);
}

void MainWindow::on_alarmLevel_valueChanged(int value)
{
    m_alarmLevel = value;
}

void MainWindow::onNonZeroPixelChanged(int pixels)
{
    ui->nonZerosPixelsLCD->display(pixels);
    QPalette palette = ui->nonZerosPixelsLCD->palette();
    if (m_alarmLevel < pixels) {
	palette.setColor(QPalette::Normal, QPalette::Background, Qt::red);
    } else {
	palette.setColor(QPalette::Normal, QPalette::Background, Qt::green);
    }
    ui->nonZerosPixelsLCD->setPalette(palette);
    ui->nonZerosPixelsLCD->repaint();
}


