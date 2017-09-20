/************************************************

Name:
  register.h
Author:
  - 王楠鑫
Date:
  2017-09-14
Language:
  C
Features:
用户输入新的用户名以后会检测该用户名是否已经被注册
自带电话号码及电子邮箱输入检测
Modules:
database.h
register.h
math.h
stdio.h
stdlib.h
string.h

************************************************/

#ifndef _REGISTER_H_ // 防止重复调用
#define _REGISTER_H_

extern int check_email(char email[20]);

extern void register_result_1();

extern void register_result_2();

// 主选项
extern int register_choose();

extern void register_main();

#endif /* _REGISTER_H_*/
