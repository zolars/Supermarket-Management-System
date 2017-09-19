/************************************************

Name:
  login.h
Author:
  刘育成
Date:
  2017-09-13
Language:
  C
Features:

************************************************/

#ifndef _LOGIN_H_ // 防止重复调用
#define _LOGIN_H_

// 主选项
extern int login_choose();

// 第零层
extern int login();

// 主程序, 负责读取数据库以及传入下一层.
extern int login_main();

#endif /*_LOGIN_H_*/
