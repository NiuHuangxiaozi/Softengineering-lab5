#include "filetable.h"


//filetable
void LinearFileTable::init_data(std::string eqpath,std::string uneqpath)
{
    //1
    std::ifstream eqfile;
    eqfile.open(eqpath, std::ios::in);
    qDebug()<<QString::fromStdString(eqpath);
    if (!eqfile.is_open())
    {
        qDebug()<<"csv not open!";
        return;
    }

    std::string codepair;
    File * onefile=nullptr;

    std::getline(eqfile, codepair);
    while (std::getline(eqfile, codepair))
    {
            //1
            int separation=0;
            while(codepair[separation]!=',')
                separation++;
            std::string first_pair=codepair.substr(0,separation);
            std::string second_pair=codepair.substr(separation+1,codepair.size()-1);
            onefile=new File(first_pair,second_pair);
            files.push_back(*onefile);
    }
    eqfile.close();


    //2
    std::ifstream uneqfile;
    uneqfile.open(uneqpath, std::ios::in);
    qDebug()<<QString::fromStdString(uneqpath);
    if (!uneqfile.is_open())
    {
        qDebug()<<"csv2 not open!";
        return;
    }

    std::getline(uneqfile, codepair);
    while (std::getline(uneqfile, codepair))
    {
            //1
            int separation=0;
            while(codepair[separation]!=',')
                separation++;
            std::string first_pair=codepair.substr(0,separation);
            std::string second_pair=codepair.substr(separation+1,codepair.size()-1);
            onefile=new File(first_pair,second_pair);
            files.push_back(*onefile);
    }
    uneqfile.close();
}
void LinearFileTable::Get_file_pairs(std::string& s1, std::string& s2,int index)
{
  assert(index<files.size());
  std::vector<std::string> answer=files[index].Getpair();
  qDebug()<<QString::fromStdString(answer[0]);
  s1=answer[0];
  s2=answer[1];
}

void LinearFileTable::save_file_result(std::string sourcepath)
{
    //输出三个csv文件
    std::fstream file_out_eq;
    file_out_eq.open(sourcepath+"/confirm_equal.csv",std::ios::out|std::ios::trunc);

    std::fstream file_out_uneq;
    file_out_uneq.open(sourcepath+"/confirm_unequal.csv",std::ios::out|std::ios::trunc);

    std::fstream file_out_unknown;
    file_out_unknown.open(sourcepath+"/confirm_unknown.csv",std::ios::out|std::ios::trunc);

    if(!file_out_eq.is_open()||!file_out_uneq.is_open()\
            ||!file_out_unknown.is_open())
    {
        qDebug()<<"result file not open!";
        return;
    }

    file_out_unknown<<"file,file\n";
    file_out_uneq<<"file,file\n";
    file_out_eq<<"file,file\n";

    for(int i=0;i<files.size();i++)
    {
        std::vector<std::string> urls=files[i].Getpair();
        qDebug()<<files[i].Get_result();
        switch(files[i].Get_result())
        {
            case 0:
                file_out_unknown<<urls[0]<<","<<urls[1]<<"\n";
                break;
            case 1:
                file_out_eq<<urls[0]<<","<<urls[1]<<"\n";
                break;
            case 2:
                file_out_uneq<<urls[0]<<","<<urls[1]<<"\n";
                break;
        }
    }

    file_out_unknown.close();
    file_out_uneq.close();
    file_out_eq.close();

}
void LinearFileTable::Set_answer(int answer)
{
    files[index].set_result(answer);

}
void LinearFileTable::set_next_index()
{
    index++;
}
int LinearFileTable::Get_index()
{
     return index;
}
bool LinearFileTable::is_over()
{
  return index==files.size()-1;
}
void LinearFileTable::reset()
{
    files.clear();//文件的数据结构
    index=0;//目前在哪一个文件对
}
int LinearFileTable::get_file_nums()
{
 return files.size();
}



//file
void File::set_result(int flag)
{
    is_equal = flag;
}

std::vector<std::string> File::Getpair()
{
    return {url1,url2};
}









