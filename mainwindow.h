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

private:
    Ui::MainWindow *ui;
    WidgetGL* m_glwidget;
};

#endif // MAINWINDOW_H
