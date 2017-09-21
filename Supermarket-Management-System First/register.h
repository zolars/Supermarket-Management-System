/*************************************************
Name: registerer.h
Author: 王楠鑫
Date: 2017-09-13
Language: C
Features:
*************************************************/

#ifndef _REGISTER_H_ // 防止重复调用
#define _REGISTER_H_

extern int check_email(char email[20]);

extern void register_result_1();

extern void register_result_2();

// 主选项
extern int register_choose();

extern void register_main();

#endif /* _REGISTER_H_*/
