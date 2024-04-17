#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPainter>
#include <cmath>
#include <algorithm>
#include <QTransform>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_loadbut_clicked();

    void on_savebut_clicked();

    void on_Filterbox_activated(int index);

    void on_Apply_clicked();

    void on_Filterbox_currentIndexChanged(int index);

    void on_typebox_activated(int index);

    void on_typebox_destroyed();

    void on_ratio_valueChanged(double arg1);

    void on_load2_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
