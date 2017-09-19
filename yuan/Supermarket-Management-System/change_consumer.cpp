/************************************************

Name:
  change_consumer.cpp
Author:
  - 王楠鑫
  - 王克淼
Date:
  2017-09-15
Language:
  C
Features:

************************************************/

#include "change_consumer.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int change_consumer_check_email(char email[20]) {
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

void change_consumer_tel(char user_id[11]) {

  int temp = 0;

  do {
    printf("\n请输入您的电话号码(11位数字)\n");
    scanf("%s", consumer_information.tel);

    if (strlen(consumer_information.tel) != 11) {
      printf("\n电话格式格式错误, 请检查后重新输入:\n");
      continue;
    }

    temp = 0;

    while (consumer_information.tel[temp] != '\0') {
      if (consumer_information.tel[temp] < '0' ||
          consumer_information.tel[temp] > '9') {
        printf("\n电话格式格式错误, 请检查后重新输入:\n");
        temp = 0;
        break;
      }
      temp++;
    }
    if (temp == 0)
      continue;
    break;
  } while (1);

  printf("\n修改成功! ");
  printf("\n请输入任意字符并按回车键以继续...\n");
  char screen[10];
  scanf("%s", screen); // 延长屏幕显示时间
  return;
}

void change_consumer_password(char user_id[11]) {

  printf("\n请输入新的账户密码: ");

  scanf("%s", consumer_information.password);
  printf("\n修改成功! ");

  printf("\n请输入任意字符并按回车键以继续...\n");
  char screen[10];
  scanf("%s", screen); // 延长屏幕显示时间

  return;
}

void change_consumer_email(char user_id[11]) {
  printf("\n请输入新的邮箱(***@***.***): ");
  int i;
  scanf("%s", consumer_information.email);
  i = change_consumer_check_email(consumer_information.email);
  while (i != 2) {
    printf("\n您的输入格式错误, 请检查后重新输入:");
    printf("\n");
    memset(consumer_information.email, 0, sizeof(consumer_information.email));
    scanf("%s", consumer_information.email);
    i = change_consumer_check_email(consumer_information.email);
  }

  printf("\n修改成功! ");
  return;
}

void change_consumer_address(char user_id[11]) {

  printf("\n请输入新的收货地址: ");
  scanf("%s", consumer_information.address);
  printf("\n修改成功! ");
  return;
}

int change_consumer_choose() {
  char choose[10]; // 记录管理员操作时的选择
  int choose_num;

  printf("您的个人信息如下:\n");
  printf("姓名  性别  手机号码   密码   邮箱   地址\n");
  printf("%s ", consumer_information.name);       // 顾客姓名
  if (strcmp(consumer_information.sex, "1") == 0) // 顾客性别判断
    printf("男 ");
  else
    printf("女 ");
  printf("%s %s %s %s",
         consumer_information.tel,      // 手机号
         consumer_information.password, // 密码
         consumer_information.email,    // 邮箱
         consumer_information.address   // 地址
  );

  // 用户界面
  printf("\n---------------操作选项---------------\n\n");
  printf("1. 修改电话号码.\n2. 修改账户密码.\n");
  printf("3. 修改邮箱.\n4. 修改收货地址.\n0. 返回.\n");
  printf("\n-------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");

  scanf("%s", choose);

  // 容错判断
  if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
      strcmp(choose, "3") != 0 && strcmp(choose, "4") != 0 &&
      strcmp(choose, "0") != 0) {
    printf("\n您的输入有误, 请按照操作选项再次输入:\n\n");
    choose_num = change_consumer_choose();
  } else
    choose_num = atoi(choose);
  return choose_num;
}

void change_consumer(char user_id[11]) {

  if (!database_consumer_information(user_id, 0)) { // 数据库读取, 只读
    printf("没有找到数据? 请先加入部分订单.");
    return; // 读取文件发生错误, 返回上一级
  }

  int choose = change_consumer_choose();

  int i = 1;
  switch (choose) {
  case 1: {
    printf("\n您正在修改电话号码! ");
    change_consumer_tel(user_id);
    database_consumer_information(user_id, 1); // 入库
    change_consumer(user_id);
    break;
  }
  case 2: {
    printf("\n您正在修改账户密码! ");
    change_consumer_password(user_id);
    database_consumer_information(user_id, 1); // 入库
    change_consumer(user_id);
    break;
  }
  case 3: {
    printf("\n您正在修改邮箱! ");
    change_consumer_email(user_id);
    database_consumer_information(user_id, 1); // 入库
    change_consumer(user_id);
    break;
  }
  case 4: {
    printf("\n您正在修改收货地址! ");
    change_consumer_address(user_id);
    database_consumer_information(user_id, 1); // 入库
    change_consumer(user_id);
    break;
  }

  case 0: {
    break;
  }
  }

  database_consumer_information(user_id, 1); // 入库

  return;
}
