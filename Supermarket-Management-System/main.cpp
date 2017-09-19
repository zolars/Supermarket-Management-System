/************************************************

Name:
  main.cpp
Author:
  辛逸飞
Date:
  2017-09-12
Language:
  C
Features:
  网上超市管理系统主程序.
Modules:
  Customize:
    - database.h

    - register.h

    - login.h

    - search_order.h

    - add_goods.h

    - print_shop_index.h

    - buy_search_all.h
      - search_for_goods.h
      - search_for_market.h

    - change_admin.h

    - change_consumer.h

    - check_time.h

    - shopping.h

  Native:
    - stdio.h
    - string.h
    - stdlib.h

Notes:
  1. 调试指令:
gcc main.cpp database.cpp login.cpp register.cpp search_order.cpp add_goods.cpp
print_shop_index.cpp cart.cpp shopping.cpp buy_search_all.cpp
search_for_goods.cpp search_for_market.cpp change_admin.cpp change_consumer.cpp
check_time.cpp -o a.out

************************************************/

#include "add_goods.h"
#include "buy_search_all.h"
#include "cart.h"
#include "change_admin.h"
#include "change_consumer.h"
#include "check_time.h"
#include "database.h"
#include "login.h"
#include "print_shop_index.h"
#include "register.h"
#include "search_for_goods.h"
#include "search_for_market.h"
#include "search_order.h"
#include "shopping.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************消费者系统********************/

// 消费者主选单
int consumer_choose() {
  char choose[10]; // 记录管理员操作时的选择
  int choose_num;

  // 用户界面
  printf("\n---------------欢迎进入顾客系统!----------------\n");
  printf("\n---------------请选择您需要的操作---------------\n");
  printf("\n1. 商品查询.\n2. 查看购物车\n3. 查看已完成订单.\n"
         "4. 充值与个人信息管理\n0. 退出.\n");
  printf("\n---------------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");

  scanf("%s", choose);

  // 容错判断
  if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
      strcmp(choose, "3") != 0 && strcmp(choose, "4") != 0 &&
      strcmp(choose, "5") != 0 && strcmp(choose, "0") != 0) {
    printf("\n您的输入有误, 请按照操作选项再次输入.\n\n");
    choose_num = consumer_choose();
  } else
    choose_num = atoi(choose);

  // 返回选项
  return choose_num;
}

void consumer(char user_id[30]) {
  int choose = consumer_choose();

  switch (choose) {

  // 商品查询
  case 1: {
    buy_search_all(user_id);
    consumer(user_id);
    break;
  }

  // 查看购物车
  case 2: {
    cart_main(user_id);
    consumer(user_id);
    break;
  }

  // 查看已完成订单
  case 3: {
    search_order(user_id, 0);
    consumer(user_id);
    break;
  }

  // 个人信息管理
  case 4: {
    change_consumer(user_id);
    consumer(user_id);
    break;
  }

  // 返回上一层
  case 0: {
    break;
  }
  }
  return;
}
/*******************消费者系统********************/

/*******************管理员系统********************/

// 管理员第一层第二选单
int admin_choose_2() {
  char choose[10]; // 记录管理员操作时的选择
  int choose_num;

  // 用户界面
  printf("\n---------------请选择您需要的操作---------------\n");
  printf("\n1. 查看现有商品.\n2. 添加新商品.\n0. 返回.\n");
  printf("\n---------------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");

  scanf("%s", choose);

  // 容错判断
  if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
      strcmp(choose, "0") != 0) {
    printf("\n您的输入有误, 请按照操作选项再次输入.\n\n");
    choose_num = admin_choose_2();
  } else
    choose_num = atoi(choose);

  // 返回选项
  return choose_num;
}

// 商品管理
void admin_2(char user_id[30]) {

  int choose = admin_choose_2();

  switch (choose) {

  // 查看现有商品
  case 1: {
    print_shop_index_main(user_id);
    admin_2(user_id);
    break;
  }

  // 添加新商品
  case 2: {
    add_goods_main(user_id);
    admin_2(user_id);
    break;
  }

  // ��回上一层
  case 0: {
    break;
  }
  }
  return;
}

// 管��员主选单
int admin_choose() {
  char choose[10]; // 记录管理员操作时的选择
  int choose_num;

  // 用户界面
  printf("\n---------------欢迎进入管理员系统!--------------\n");
  printf("\n---------------请选择您需要的操作---------------\n");
  printf("\n1. 订单管理.\n2. 商品管理.\n3. 个人信息管理.\n0. 退出.\n");
  printf("\n---------------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");

  scanf("%s", choose);

  // 容错判断
  if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
      strcmp(choose, "3") != 0 && strcmp(choose, "0") != 0) {
    printf("\n您的输入有误, 请按照操作选项再次输入.\n\n");
    choose_num = admin_choose();
  } else
    choose_num = atoi(choose);

  // 返回选项
  return choose_num;
}

// 管理员系统第一层
void admin(char user_id[30], int user_type) {

  int choose = admin_choose();

  switch (choose) {

  // 订单管理
  case 1: {
    search_order(user_id, user_type);
    admin(user_id, user_type);
    break;
  }

  // 商品管理
  case 2: {
    admin_2(user_id);
    admin(user_id, user_type);
    break;
  }

  // 个人信息管理
  case 3: {
    change_admin(user_id);
    admin(user_id, user_type);
    break;
  }

  // 返回上一层
  case 0: {
    break;
  }
  }
  return;
}

/*******************管理员系统********************/

// 登陆与注册选项
int main_choose() {
  char choose[10]; // 记录管理员操作时的选择
  int choose_num;

  // 用户界面
  printf("\n------------欢迎进入网上超市管理系统!------------\n");
  printf("\n---------------请选择您需要的操作---------------\n");
  printf("\n1. 登陆.\n2. 注册.\n0. 退出.\n");
  printf("\n---------------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");

  scanf("%s", choose);

  // 容��判断
  if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
      strcmp(choose, "0") != 0) {
    printf("\n您的输入有误, 请按照操作选项再次输入.\n\n");
    choose_num = main_choose();
  } else
    choose_num = atoi(choose);

  // 返回选项
  return choose_num;
}

// 主程序
int main() {

  int choose = main_choose(); // 用户界面传入指令

  switch (choose) {

  // 登陆
  case 1: {
    if (login_main()) {

      // 从数据库中取出 user_id 以及 user_type
      FILE *flogin;
      char file_name[300];
      strcpy(file_name, path); // 该字符串用于处理文件名
      strcat(file_name, "login_result.txt"); // 文件名为"login_result.txt"
      flogin = fopen(file_name, "r");

      char user_id[30];
      int user_type;
      fscanf(flogin, "%s %d", user_id, &user_type);
      fclose(flogin);

      if (user_type)
        admin(user_id, user_type);
      else
        consumer(user_id);

      break;
    } else {
      main();
      break;
    }
    break;
  }

  // 注册
  case 2: {
    register_main();
    main();
    break;
  }

  // 返回上一层
  case 0: {
    printf("感谢您的使用, 再见.\n");
    printf("程序运行结束.\n");
    break;
  }
  }
  return 0;
}
