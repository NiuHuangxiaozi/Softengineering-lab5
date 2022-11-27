#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <string>
#include <QMessageBox>
#include <fstream>
#include <iostream>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    ~MainWindow();
    QLabel theme;

private:
    Ui::MainWindow *ui;
    void Deal_with_wrong();//处理错误

};
#endif // MAINWINDOW_H
