#include "confirmtable.h"
#include "ui_confirmtable.h"

Confirmtable::Confirmtable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Confirmtable)
{
    ui->setupUi(this);
    this->setFixedSize(1200,800);
    this->setWindowIconText("等价确认");
    ui->result->setText("未确认");

    //按钮的connect
    //1下一个
    connect(ui->btn_next,&QPushButton::clicked,[=](){
        if(temp_result==-1)//没有点击确认
        {
            QMessageBox::warning( this, tr("Warning"), \
            tr("没有做出判断"),\
            QMessageBox::Yes);
        }
        else
        {
            if(!files->is_over()){
                //1设置结果
                files->Set_answer(temp_result);
                files->set_next_index();
                int nextindex=files->Get_index();

                //qDebug()<<"The next index is "<<nextindex;

                leftshow->clear();
                rightshow->clear();
                code_one_lines.clear();
                code_two_lines.clear();
                show_files(nextindex);


                ui->label->setText(QString::number(nextindex+1)+"/"\
                     +QString::number(files->get_file_nums()));
                temp_result=-1;
                ui->result->setText("未确认");

            }
            else
            {
                files->Set_answer(temp_result);
                QMessageBox::warning( this, tr("Noticing"), \
                tr("全部判断完毕"),\
                QMessageBox::Yes);
            }
        }
    });

    //2等价
    connect(ui->btn_eq,&QPushButton::clicked,[=](){
        temp_result=1;
        ui->result->setText("等价");
    });

    //3不等价
    connect(ui->btn_uneq,&QPushButton::clicked,[=](){
        temp_result=2;
        ui->result->setText("不等价");
    });

    //4存疑
    connect(ui->btn_unknown,&QPushButton::clicked,[=](){
        temp_result=0;
        ui->result->setText("存疑");
    });

    //5返回的按钮
    connect(ui->btn_back,&QPushButton::clicked,[=](){
        reset();
        emit back();
    });

    //6
    connect(ui->btn_out,&QPushButton::clicked,[=](){
         if(files->is_over())
         {
             files->save_file_result(sourcepath);
             QMessageBox::warning( this, tr("Noticing"), \
             tr("导出成功"),\
             QMessageBox::Yes);
         }
         else
         {
             QMessageBox::warning( this, tr("Warning"), \
             tr("还有未判断的等价对"),\
             QMessageBox::Yes);
         }
    });



    //
    leftshow=new CodeEditor(this);
    rightshow=new CodeEditor(this);

    leftlight=new Highlighttext(leftshow->document());
    rightlight=new Highlighttext(rightshow->document());

    leftshow->setGeometry(30,50,470,700);
    rightshow->setGeometry(530,50,470,700);

    QFont f;
    f.setPointSize(15);
    leftshow->setFont(f);
    rightshow->setFont(f);
}

Confirmtable::~Confirmtable()
{
    delete ui;
}
void Confirmtable::reset()
{
    ui->label->clear();
    ui->result->clear();
    leftshow->clear();
    rightshow->clear();

    files->reset();
}

void Confirmtable::setsourcefile(std::string s)
{
    sourcepath=s;
    int i=s.length()-1;
    while(s[i]!='/')
        i--;
    sourcepath_csv=s.substr(0,i);


    files=new LinearFileTable();
}
void Confirmtable::show_files(int index)
{

    std::string file1; std::string file2;
    files->Get_file_pairs(file1,file2,index);

    global_file1=file1;
    global_file2=file2;

    file1=sourcepath_csv+"/"+file1;
    file2=sourcepath_csv+"/"+file2;

    std::string one_line;std::string two_line;
    qDebug()<<"A"+QString::fromStdString(file1);


    std::ifstream code_one;
    code_one.open(file1, std::ios::in);
    if (!code_one.is_open())
    {
        qDebug()<<"cpp1 not open!";
        return;
    }
    std::ifstream code_two;
    code_two.open(file2, std::ios::in);
    if (!code_two.is_open()){
        qDebug()<<"cpp2 not open!";
        return;
    }

    while (std::getline(code_one, one_line))
    {
        if(one_line!="")
        {
            //qDebug()<<"input1:"<<QString::fromStdString(one_line);
            code_one_lines.push_back(one_line);
        }
    }
    while (std::getline(code_two, two_line))
    {
       if(two_line!="")
       {
            //qDebug()<<"input2:"<<QString::fromStdString(two_line);
            code_two_lines.push_back(two_line);
       }
    }
    code_one.close();
    code_two.close();

    Show_diff();
}
void Confirmtable::Show_diff()
{
    int indexone=0;
    int indextwo=0;

    for(;indexone<code_one_lines.size();indexone++)
    {
        if(code_one_lines[indexone]==code_two_lines[indextwo])
        {
          addline(leftshow,QString::fromStdString(code_one_lines[indexone]),
                  QColor("white"));
          addline(rightshow,QString::fromStdString(code_two_lines[indextwo]),
                  QColor("white"));
          indextwo++;
        }
        else
        {
            int is_find=false;
            int find_location=indextwo;
            for(int i=indextwo;i<code_two_lines.size();i++)
            {
                if(code_two_lines[i]==code_one_lines[indexone])
                {
                    find_location=i;is_find=true;break;
                }
            }
            if(is_find)
            {
                  for(;indextwo<find_location;indextwo++)
                  {
                      addline(leftshow," ",QColor("white"));
                      addline(rightshow,QString::fromStdString(code_two_lines[indextwo]),
                              QColor("lightgreen"));
                  }
                  addline(leftshow,QString::fromStdString(code_one_lines[indexone]),
                          QColor("white"));
                  addline(rightshow,QString::fromStdString(code_two_lines[indextwo]),
                          QColor("white"));
                  indextwo++;
            }
            else//没找到
            {
                QColor color;
                color.setRed(250);
                addline(leftshow,QString::fromStdString(code_one_lines[indexone]),
                        color);
                addline(rightshow," ",QColor("white"));
            }
        }

    }
    for(;indextwo<code_two_lines.size();indextwo++)
    {
        addline(rightshow,QString::fromStdString(code_two_lines[indextwo]),
                QColor("lightgreen"));
    }
}
void Confirmtable::addline(CodeEditor* pt,QString text, QColor backColor)
{
    QTextCharFormat fmt;
    //字体色
    //fmt.setForeground(QBrush(fontColor));
    //fmt.setUnderlineColor("red");

    //背景色
    fmt.setBackground(QBrush(backColor));

    //文本框使用以上设定
    pt->setCurrentCharFormat(fmt);
    //文本框添加文本
    pt->appendPlainText(text);
}



void Confirmtable::set()
{
    files->init_data(sourcepath+"/equal.csv",sourcepath+"/inequal.csv");



    //展示第一个要判断的文件对
    show_files(0);

    int num=files->get_file_nums();
    ui->label->setText(QString::number(1)+"/"+QString::number(num));

    ui->result->setText("未确认");
}


























void Confirmtable::paintEvent(QPaintEvent *)
{
    QPainter mypainter(this);
    QPixmap pix;
    pix.load(":/photo/background.png");
    mypainter.drawPixmap(0,0,this->width(),this->height(),pix);

}
