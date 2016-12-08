// PacketFile.cpp : 定义控制台应用程序的入口点。


#include "stdafx.h"
#include "SerchAllFile.h"
#include "MyCab.h"


int _tmain(int argc, _TCHAR* argv[])
{
vector<string> vec_file;
vector<string>::iterator itemFileName;
char filePacketPath[MAX_PATH] = "F:\\PacketFile\\test";
char filePutPath[MAX_PATH] = "F:\\PacketFile\\output\\my.sfx";
CSerchAllFile::getInstance()->get_filelist(filePacketPath, vec_file);




//--------------------打包过程--------------------
//声明对象
CMyCab mc;
//设置输出文件
mc.SetOutPutFile(filePutPath);
//添加要打包的文件
for (itemFileName=vec_file.begin(); itemFileName<vec_file.end(); itemFileName++)
{
  mc.AddFile((*itemFileName).c_str());
}
//执行打包
mc.DoMakeSFX();


/*
//--------------------解包过程--------------------
//声明对象
CMyCab umc;
//执行解包
umc.DoUnSFX(filePutPath);
*/

cin.clear();
cin.get();


return 0;
}