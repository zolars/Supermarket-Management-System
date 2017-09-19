/************************************************

Name:
  login.cpp
Author:
  刘育成
Date:
  2017-09-13
Language:
  C
Features:

************************************************/

#include "database.h"
#include "login.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 主选项
int login_choose() {

  char choose[10]; // 记录操作者的选择

  int choose_num;

  // 用户界面
  printf("\n---------------请选择您的用户类型---------------\n\n");
  printf("1. 管理员\n2. 顾客\n0. 返回\n");
  printf("\n---------------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");
  scanf("%s", choose);

  // 容错判断
  if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
      strcmp(choose, "0") != 0) {
    printf("\n您的输入有误, 请按照操作选项再次输入:\n\n");
    choose_num = login_choose();
  } else
    choose_num = atoi(choose);
  return choose_num;
}
// 0
int login() {
  int choose = login_choose(); // 用户界面传入指令

  switch (choose) {
  case 1: {
    return 1;
  }

  case 2: {
    return 0;
  }

  // 返回上一层

  case 0: {
    return -1;
  }
  }
  return -1;
}

// 主程序, 负责读取数据库以及传入下一层.
int login_main() {
  int user_type;
  char user_id[30];

  user_type = login();
  if (user_type == -1)
    return 0;

  char password[11]; //输入的密码
  int temp;
  do {
    printf("\n请输入用户名或者按\"0\"返回: ");
    scanf("%s", user_id);
    if (strcmp(user_id, "0") == 0)
      break;
    if (user_type == 0) {
      temp = database_consumer_information(user_id, 0);
      if (temp == 0) {
        printf("\n您还没有注册, 请注册. \n");
        printf("请输入任意字符并按回车键以继续...\n");
        scanf("%s", password); // 延长屏幕显示时间
        return 0;
      }

      printf("请输入密码:  ");
      scanf("%s", password);

      if (strcmp(password, consumer_information.password) ==
          0) //比对用户名与密码是否正确
      {
        printf("\n登录成功!");

        // 数据存取
        FILE *flogin;
        char file_name[300];
        strcpy(file_name, path); // 该字符串用于处理文件名
        strcat(file_name, "login_result.txt"); // 文件名为"login_result.txt"

        flogin = fopen(file_name, "w+");

        fprintf(flogin, "%s %d", user_id, user_type);
        fclose(flogin);
        return 1;
      } else
        printf("\n用户名或密码错误! 请重新登陆!\n");
    }
    if (user_type == 1) {
      temp = database_admin_information(user_id, 0);
      if (temp == 0) {
        printf("\n您还没有注册, 请注册. \n");
        printf("请输入任意字符并按回车键以继续...\n");
        scanf("%s", password); // 延长屏幕显示时间
        return 0;
      }

      printf("请输入密码:  ");
      scanf("%s", password);

      if (strcmp(password, admin_information.password) ==
          0) //比对用户名与密码是否正确
      {
        printf("\n登录成功! ");

        // 数据存取
        FILE *flogin;
        char file_name[300];
        strcpy(file_name, path); // 该字符串用于处理文件名
        strcat(file_name, "login_result.txt"); // 文件名为"login_result.txt"

        flogin = fopen(file_name, "w+");

        fprintf(flogin, "%s %d", user_id, user_type);
        fclose(flogin);

        return 1;
      } else
        printf("\n用户名或密码错误! 请重新登陆! ");
    }
  } while (1);

  return 0;
}
