#ifndef CONFIRMTABLE_H
#define CONFIRMTABLE_H

#include <QMainWindow>
#include <QPainter>
#include <filetable.h>
#include <QMessageBox>
namespace Ui {
class Confirmtable;
}

class Confirmtable : public QMainWindow
{
    Q_OBJECT

public:
    explicit Confirmtable(QWidget *parent = nullptr);
    ~Confirmtable();
    void paintEvent(QPaintEvent *);
    void setsourcefile(std::string s);
    void set();//初始化一些参数
    void show_files(int index);//展示第几对文件
private:
    //vars
    Ui::Confirmtable *ui;
    FileTable * files;

    std::string  sourcepath;
    std::string  sourcepath_csv;//每一个csv的前缀

    int temp_result=-1;//本次判断的结果
    //0 表示存疑，1表示等价，2表示不等价，-1表示没有确定

    //表示当前是哪一个文件对
    std::string global_file1;
    std::string global_file2;

     //funcs
    void reset();
signals:
    void back();
};

#endif // CONFIRMTABLE_H
