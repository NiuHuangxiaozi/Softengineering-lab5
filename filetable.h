#ifndef FILETABLE_H
#define FILETABLE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <QDebug>
#include<method.h>
#include<set>
#include <QMessageBox>
class File
{
private:
    int is_equal;
    std::string url1;
    std::string url2;
public:
    File(std::string new_url1, std::string new_url2)
    {
        url1 = new_url1;
        url2 = new_url2;
    }
    void set_result(int flag);
    int Get_result(){return is_equal;}
    std::vector<std::string> Getpair();
};



class FileTable
{
public:
    virtual void Get_file_pairs(std::string& s1, std::string& s2,int index) {};
    //virtual void Add_file_pairs(std::string& s1, std::string& s2) {};
    //virtual bool is_empty() {return true;};
    virtual void save_file_result(std::string s) {};
    virtual void init_data(std::string s,std::string answerfile) {};
    virtual void Set_answer(int answer){};
    virtual int Get_index(){return 1;};
    virtual bool is_over(){return true;};
    virtual void reset(){};//恢复原态
    virtual int get_file_nums(){return 0;};
    virtual void set_next_index(){};
    virtual ~FileTable(){};

};
class LinearFileTable:public FileTable
{

private:
    std::vector<File> files;//文件的数据结构
    int index=0;//目前在哪一个文件对
    std::set<std::string>files_names;//所有文件的名称
    DSU * dsu=nullptr;
public:
    ~LinearFileTable()
    {
        delete  dsu;
    }
    void init_data(std::string eqpath,std::string uneqpath);
    void Get_file_pairs(std::string& s1, std::string& s2,int index);
    void Set_answer(int answer);
    int Get_index();
    bool is_over();
    void reset();//恢复原态
    int get_file_nums();
    void save_file_result(std::string s);
    void set_next_index();


};
#endif // FILETABLE_H
