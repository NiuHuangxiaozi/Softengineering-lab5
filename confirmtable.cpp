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

                ui->codetextone->clear();
                ui->codetexttwo->clear();
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
}

Confirmtable::~Confirmtable()
{
    delete ui;
}
void Confirmtable::reset()
{
    ui->label->clear();
    ui->result->clear();
    ui->codetextone->clear();
    ui->codetexttwo->clear();

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

    std::string one_line;
    qDebug()<<"A"+QString::fromStdString(file1);


    std::ifstream code_one;
    code_one.open(file1, std::ios::in);
    if (!code_one.is_open())
    {
        qDebug()<<"cpp1 not open!";
        return;
    }
    while (std::getline(code_one, one_line))
    {
        ui->codetextone->append(QString::fromStdString(one_line));
    }
    code_one.close();

    std::ifstream code_two;
    code_two.open(file2, std::ios::in);
    if (!code_two.is_open()){
        qDebug()<<"cpp2 not open!";
        return;
    }

    while (std::getline(code_two, one_line))
    {
        ui->codetexttwo->append(QString::fromStdString(one_line));
    }
    code_two.close();
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
