#ifndef METHOD_H
#define METHOD_H

#include<iostream>
#include<string>
#include<vector>
#include<map>
class DSU
{
private:
    int* rank;
    int* parent;
    int count;
    std::map<std::string, int>path_to_index;

    int find(int p);
public:
    DSU(std::vector<std::string>&files);
    int find(std::string s);
    bool isConnected(std::string s1, std::string s2);
    void unionElements(std::string s1, std::string s2);
};

#endif // METHOD_H
