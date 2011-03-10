#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_glwidget(new WidgetGL)

{
    ui->setupUi(this);
    ui->verticalLayout->addWidget(m_glwidget);

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
