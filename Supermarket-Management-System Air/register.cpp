// Name: registerer.cpp
// Author: 王楠鑫
// Date: 2017-09-13
// Language: C
// Features:

#include "database.h"
#include "register.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email(char email[20]) {
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

void register_result_1() {
  char store[20];
  char name[20];
  char email[20];
  char password[20];
  char user_id_temp[20];
  int temp = 0;

  while (1) {
    printf("\n请输入您的用户名:\n");
    scanf("%s", user_id_temp);
    if (!database_admin_information(user_id_temp, 0)) // 数据库读取, 只读
    {
      printf("\n您可以使用当前用户名.");
      break;
    } else {
      printf("\n当前用户名已被注册，请使用其它用户名.");
      continue; // 读取文件发生格式错误, 返回上一级
    }
  }

  printf("\n请填写您所属的超市:\n");
  scanf("%s", store);

  printf("\n请填写您的姓名:\n");
  scanf("%s", name);

  int i;
  do {
    printf("\n请填写您的邮箱(***@***.***):\n");
    scanf("%s", email);
    i = check_email(email);
    if (i == 2)
      break;
    else {
      printf("\n邮箱格式格式错误, 请检查后重新输入:\n");
      memset(email, 0, sizeof(email));
    }

  } while (i != 2);

  printf("\n请您填写您的密码:\n");
  scanf("%s", password);

  database_admin_information(user_id_temp, 1);

  strcpy(admin_information.shop_id, store);     // 超市名
  strcpy(admin_information.name, name);         // 管理员姓名
  strcpy(admin_information.email, email);       // 邮箱
  strcpy(admin_information.password, password); // 密码

  database_admin_information(user_id_temp, 1);

  printf("\n您已成功注册!\n");
  printf("\n请输入任意字符并按回车键以继续...\n");
  char screen[10];
  scanf("%s", screen); // 延长屏幕显示时间
  return;
  //返回主程序（登陆or注册）
}

void register_result_2() {
  char name[20];
  char sex[20];
  char tel[20];
  char password[20];
  char email[20];
  char address[20];
  char user_id_temp[20];
  char money[100];
  int temp = 0;
  printf("\n请输入您的用户名:\n");

  scanf("%s", user_id_temp);
  if (!database_consumer_information(user_id_temp, 0)) // 数据库读取, 只读
    printf("\n您可以使用当前用户名.");
  else {
    printf("\n当前用户名已被注册, 请使用其它用户名.");
    register_result_2();
  }

  printf("\n请填写您的姓名:\n");
  scanf("%s", name);

  do {
    printf("\n请选择您的性别:\n");
    printf("1. 男\n2. 女\n");
    scanf("%s", sex);
    if (strcmp(sex, "1") != 0 && strcmp(sex, "2") != 0) {
      printf("您的输入格式错误, 请检查后重新输入:\n");
      continue;
    } else
      break;
  } while (1);

  do {
    printf("\n请填写您的电话号码(11位数字)\n");
    scanf("%s", tel);

    if (strlen(tel) != 11) {
      printf("\n电话格式错误, 请检查后重新输入:\n");
      continue;
    }

    temp = 0;

    while (tel[temp] != '\0') {
      if (tel[temp] < '0' || tel[temp] > '9') {
        printf("\n电话格式错误, 请检查后重新输入:\n");
        temp = 0;
        break;
      }
      temp++;
    }
    if (temp == 0)
      continue;
    break;
  } while (1);

  printf("\n请填写您的密码:\n");
  scanf("%s", password);

  int i;
  do {
    printf("\n请填写您的邮箱(***@***.***):\n");
    scanf("%s", email);
    i = check_email(email);
    if (i == 2)
      break;
    else {
      printf("\n邮箱格式格式错误, 请检查后重新输入:\n");
      printf("\n");
      memset(email, 0, sizeof(email));
    }

  } while (i != 2);
  printf("\n请填写您的收货地址:\n");
  scanf("%s", address);

  printf("\n您已成功注册!\n");

  // 输入并检测??额
  double money_num;
  do {
    printf("\n请充值您的余额(上限五万元):\n");
    scanf("%s", money);
    money_num = atof(money);
    if (fabs((int(money_num * 100) - (money_num * 100))) > 0.000001 ||
        money_num == 0) {
      printf("\n输入格式错误, 请检查后重新输入:\n");
      continue;
    } else if (strlen(money) > 8 || atof(money) > 50000) {
      printf("\n每次最多只能充值￥50000, 请检查后重新输入:\n");
      continue;
    }
    break;
  } while (1);

  printf("\n充值成功! 您的充值金额为%0.2f", money_num);
  printf("\n请输入任意字符并按回车键以继续...\n");
  char screen[10];
  scanf("%s", screen); // 延长屏幕显示时间

  database_consumer_information(user_id_temp, 1);

  strcpy(consumer_information.name, name);         // 顾??姓名
  strcpy(consumer_information.sex, sex);           // ???客性别
  strcpy(consumer_information.tel, tel);           // 手机号
  strcpy(consumer_information.password, password); // 密码
  strcpy(consumer_information.email, email);       // 邮箱
  strcpy(consumer_information.address, address);   // 地址
  consumer_information.money = money_num;          // 余额

  database_consumer_information(user_id_temp, 1);

  return;
  //返回主程序（登陆or注册）
}

// 主选项
int register_choose() {
  char choose[10]; // 记录管理员操作时的选择
  int choose_num;

  // 用户界面
  printf("\n---------------请选择您要注册的账户类型---------------\n\n");
  printf("1. 管理员账号.\n2. 顾客账号.\n0. 返回.\n");
  printf("\n--------------------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");

  scanf("%s", choose);

  // 容错判断
  if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
      strcmp(choose, "0") != 0) {
    printf("\n您的输入有误, 请按照操作选项再次输入:\n\n");
    choose_num = register_choose();
  } else
    choose_num = atoi(choose);
  return choose_num;
}

void register_main() {

  int choose = register_choose(); // 用户界面传入指令

  switch (choose) {

  case 1: {
    register_result_1();
    break;
  }

  case 2: {
    register_result_2();
    break;
  }

  // 返回上一层
  case 3: {
    break;
  }
  }
  return;
}
