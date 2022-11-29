#ifndef CONFIRMTABLE_H
#define CONFIRMTABLE_H

#include <QMainWindow>
#include <QPainter>
#include <filetable.h>
#include <QMessageBox>
#include<codeedit.h>
#include<highlighttext.h>
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
    void Show_diff();//展示不同
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


    //展示的视图
    CodeEditor *leftshow=nullptr;
    CodeEditor *rightshow=nullptr;

    //语法高亮
    Highlighttext * leftlight=nullptr;
    Highlighttext * rightlight=nullptr;
    //
    std::vector<std::string>code_one_lines;
    std::vector<std::string>code_two_lines;
     //funcs
    void reset();

    void addline(CodeEditor* pt,QString text, QColor backColor);
signals:
    void back();
};

#endif // CONFIRMTABLE_H
