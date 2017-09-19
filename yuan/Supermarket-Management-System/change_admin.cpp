/************************************************

Name:
  change_admin.cpp
Author:
  - 王楠鑫
  - 王克淼
Date:
  2017-09-15
Language:
  C
Features:

************************************************/

#include "change_admin.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int change_admin_check_email(char email[20]) {
  int i, j = 0, k = 0, n = 0, m = 0, temp = 0;
  for (i = 0; i < strlen(email); i++) {
    if (email[i] == '@')
      j++, n = i;
  }
  for (i = 0; i < strlen(email); i++) {
    if (email[i] == '.')
      k++, m = i;
  }
  if (k == 1 && j == 1)
    temp++;
  if (n + 1 < m)
    temp++;
  return temp;
}

void change_admin_password(char user_id[11]) {

  printf("\n请输入新的账户密码: ");

  scanf("%s", admin_information.password);

  printf("\n修改成功! ");
  printf("\n请输入任意字符并按回车键以继续...\n");
  char screen[10];
  scanf("%s", screen); // 延长屏幕显示时间

  return;
}

void change_admin_email(char user_id[11]) {

  printf("\n请输入新的邮箱: ");

  scanf("%s", admin_information.email);

  int i;
  i = change_admin_check_email(admin_information.email);
  while (i != 2) {
    printf("\n您的输入格式错误, 请检查后重新输入:");
    printf("\n");
    memset(admin_information.email, 0, sizeof(admin_information.email));
    scanf("%s", admin_information.email);
    i = change_admin_check_email(admin_information.email);
  }

  printf("\n修改成功! ");
  printf("\n请输入任意字符并按回车键以继续...\n");
  char screen[10];
  scanf("%s", screen); // 延长屏幕显示时间

  return;
}

int change_admin_choose() {
  char choose[10]; // 记录管理员操作时的选择
  int choose_num;

  printf("您的个人信息如下:\n");
  printf("超市名   管理员姓名          邮箱        密码\n");

  printf("%s       %s   %s   %s\n",
         admin_information.shop_id, // 超市名
         admin_information.name,    // 管理员姓名
         admin_information.email,   // 邮箱
         admin_information.password // 密码
  );

  // 用户界面
  printf("\n---------------请选择您需要的操作类型---------------\n\n");
  printf("\n1. 修改账户密码.\n2. 修改邮箱\n0. 返回.\n");
  printf("\n-------------------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");

  scanf("%s", choose);

  // 容错判断
  if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
      strcmp(choose, "0") != 0) {
    printf("\n您的输入有误, 请按照操作选项再次输入:\n\n");
    choose_num = change_admin_choose();
  } else
    choose_num = atoi(choose);
  return choose_num;
}

void change_admin(char user_id[11]) {
  if (!database_admin_information(user_id, 0)) { // 数据库读取, 只读
    printf("没有找到文件? 请核查数据库信息.");
    return; // 读取文件发生错误, 返回上一级
  }

  int choose = change_admin_choose(); // 用户界面传入指令

  switch (choose) {
  case 1: {
    printf("\n您正在修改账户密码! ");
    change_admin_password(user_id);
    database_admin_information(user_id, 1); // 入库
    change_admin(user_id);
    break;
  }
  case 2: {
    printf("\n您正在修改邮箱! ");
    change_admin_email(user_id);
    database_admin_information(user_id, 1); // 入库
    change_admin(user_id);
    break;
  }
  case 3: {
    break;
  }
  }

  database_admin_information(user_id, 1); // 入库

  return;
}
