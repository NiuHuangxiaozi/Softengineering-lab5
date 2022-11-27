#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    this->setFixedSize(1200,800);

    connect(ui->btn_code,&QPushButton::clicked,[=](){
      QString eq_path = QFileDialog::getExistingDirectory(\
                  this,QStringLiteral("选择路径"),"./");
      ui->line_code->setText(eq_path);
    });

    connect(ui->btn_start,&QPushButton::clicked,[=](){
        //检错环节
        try{
             Deal_with_wrong();
        }
        catch(int error_num)
        {
           switch(error_num)
           {
              case 0:
                 QMessageBox::warning( this, tr("Warning"), \
                 tr("有文件夹没有选择。"),\
                 QMessageBox::Yes);
                 break;
               case 1:
                  QMessageBox::warning( this, tr("Warning"), \
                  tr("无法打开相应的cpp文件"),\
                  QMessageBox::Yes);
                  break;
           }
           return;
        }

        //进入判断环节



    });
}
void MainWindow::Deal_with_wrong()
{

    std::string code=ui->line_code->text().toStdString();


    if(code=="")
        throw 0;
    //1
    std::string one_csv;
    std::ifstream file;
    file.open(code+"/equal.csv", std::ios::in);
    if (!file.is_open())
    {
        qDebug()<<"csv not open!";
        return;
    }
    file>>one_csv;
    file>>one_csv;

    file.close();
    int length=0;
    while(one_csv[length]!=',')
        length++;

    std::string one_file=one_csv.substr(0,length);

    //2
    int loc=code.size()-1;
    while(code[loc]!='/')
        loc--;
    code=code.substr(0,loc);


    std::ifstream codefile;
    qDebug()<<QString::fromStdString(code+"/"+one_file);
    codefile.open(code+"/"+one_file, std::ios::in);
    if (!codefile.is_open())
        throw 1;

    codefile.close();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{

    QPainter mypainter(this);
    QPixmap pix;
    pix.load(":/photo/background.png");
    mypainter.drawPixmap(0,0,this->width(),this->height(),pix);
}

