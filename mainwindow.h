#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <widgetgl.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void start();

private slots:
    void on_pushButton_clicked();

    void on_captureButton_clicked();

    void on_ledComboBox_currentIndexChanged(int index);

    void on_thresholdLevel_valueChanged(int value);

    void on_alarmLevel_valueChanged(int value);

    void onNonZeroPixelChanged(int pixels);

private:
    Ui::MainWindow *ui;
    WidgetGL* m_glwidget;

    int m_alarmLevel;
};

#endif // MAINWINDOW_H
