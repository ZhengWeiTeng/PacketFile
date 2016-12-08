#pragma once


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <error.h>
#include <direct.h>
using namespace std;

//最多打包文件个数
#define MAX_FILE_COUNT  1024
//最大路径字符长度
#define MAX_PATH   260


//头定义
struct FileHead
{
unsigned int FileCount;//文件个数
unsigned int FileLen[MAX_FILE_COUNT];//文件大小
char FileName[MAX_FILE_COUNT][MAX_PATH];//文件名
};


class CMyCab
{
private:
FileHead fh;//文件头
char ObjectFilePathName[MAX_PATH];//生成打包文件位置及名称


public:
CMyCab(void);
~CMyCab(void);


//添加文件到包内
void AddFile(const char * FilePathName);
//设置打包输出文件
void SetOutPutFile(char * OutFile);
//获取文件大小(传入以二进制方式打开的文件指针)
long GetFileSize(FILE *pf);
//制作打包文件
void DoMakeSFX();
//解包
void DoUnSFX(char *CabFilePathName);


private:
//显示打包内文件信息
void printSFX();
//创建文件夹
void CheckTargetPath(string targetPath);
};