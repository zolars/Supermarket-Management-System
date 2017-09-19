/************************************************

Name:
  cart.cpp
Author:
  - 刘育成
  - 王楠鑫
Date:
  2017-09-15
Language:
  C
Features:

************************************************/

#include "cart.h"
#include "check_time.h"
#include "database.h"
#include "shopping.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cart_choose_2() {
  char choose[10]; // 记录管理员操作时的选择
  int choose_num;
  // 用户界面
  printf("\n---------------操作选项---------------\n");
  printf("\n1. 购买.\n2. 移除.\n0. 返回.\n");
  printf("\n-------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");
  scanf("%s", choose);
  if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
      strcmp(choose, "0") != 0) {
    printf("\n您的输入有误, 请按照操作选项再次输入:\n\n");
    choose_num = cart_choose_2();
  } else
    choose_num = atoi(choose);

  return choose_num;
}
void cart_result_2(char user_id[30]) {
  int i = 0, k = 0;
  printf("您的购物车信息如下:\n");
  printf("序号   商品名   超市名     购买数量\n");
  while (shopping_cart[i].purchase_num != 0) {
    printf("%d.      %-8s %-15s %4d\n", i + 1, shopping_cart[i].goods_name,
           shopping_cart[i].shop_id, shopping_cart[i].purchase_num);
    i++;
  }
  int choise_num = i;
  char choose_str[10];
  int choose_num;

  do {
    printf("\n请选择您想查看的商品(按0返回)\n");
    scanf("%s", choose_str);

    // 检验输入是否正确
    if (strcmp(choose_str, "0") == 0)
      return;

    i = 0;
    k = 0;
    while (choose_str[i] != '\0') {
      if (choose_str[i] >= '0' && choose_str[i] <= '9')
        i++;
      else {
        printf("\n您的输入有误，请重新输入\n");
        k = 1;
        break;
      }
    }

    if (k)
      continue;

    choose_num = atoi(choose_str);

    if (choose_num > choise_num) {
      printf("\n您的输入有误，请重新输入\n");
      continue;
    } else
      break;
  } while (1);

  choose_num -= 1;

  printf("您查看的信息为:\n");
  printf("商品名: %s\n超市编号: %s\n购买数量: %d\n",
         shopping_cart[choose_num].goods_name,  // 货物ID
         shopping_cart[choose_num].shop_id,     // 超市ID
         shopping_cart[choose_num].purchase_num //购买数量
  );

  int choose_num_2 = cart_choose_2();

  if (choose_num_2 == 1) {
    int temp_return = shopping(user_id, shopping_cart[choose_num].goods_name,
                               shopping_cart[choose_num].shop_id,
                               shopping_cart[choose_num].purchase_num);

    if (temp_return == 1) {
      shopping_cart[choose_num].purchase_num = -1;
      database_shopping_cart(user_id, 1);
      database_shopping_cart(user_id, 0);

      printf("您的商品购买完成, "
             "谢谢惠顾!\n详细信息请前往\"主菜单-查看已完成订单\".\n");
    } else if (temp_return == 0)
      printf("抱歉, 您选择的商品存货不足, 请选择其他商品.");
    else
      printf("抱歉, 您的余额不足, 请先充值.");

    char screen[10];
    printf("\n请输入任意字符并按回车键以继续...\n");
    scanf("%s", screen); // 延长屏幕显示时间
  }
  if (choose_num_2 == 2) {
    shopping_cart[choose_num].purchase_num = -1;
    database_shopping_cart(user_id, 1);
    database_shopping_cart(user_id, 0);
    return;
  }
  return;
}
int cart_choose() {
  char choose[10]; // 记录管理员操作时的选择
  int choose_num;
  // 用户界面
  printf("\n---------------操作选项---------------\n");
  printf("\n1. 全部购买.\n2. 查看详情.\n0. 返回.\n");
  printf("\n-------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");
  scanf("%s", choose);
  if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
      strcmp(choose, "0") != 0) {
    printf("\n您的输入有误, 请按照���作选项再次输入:\n\n");
    choose_num = cart_choose();
  } else
    choose_num = atoi(choose);

  return choose_num;
}

int cart(char user_id[30]) {

  int choose = cart_choose(); // 用户界面传入指令
  int i = 0, k = 0;           // 记录是否有购买完成

  switch (choose) {
  case 1: {

    i = 0;
    k = 0;
    printf("以下为购买状态(商品名 : 超市ID : 购买数量)\n");

    do {

      int temp_return =
          shopping(user_id, shopping_cart[i].goods_name,
                   shopping_cart[i].shop_id, shopping_cart[i].purchase_num);
      if (temp_return == 1) {
        if (shopping_cart[i].purchase_num != 0)
          printf("%s : %s : %d\n购买成功!\n", shopping_cart[i].goods_name,
                 shopping_cart[i].shop_id, shopping_cart[i].purchase_num);

        //缓存
        k += 1;
        shopping_cart[i].purchase_num = -1;
      } else if (temp_return == 0) {
        if (shopping_cart[i].purchase_num != 0)
          printf("%s : %s : %d\n存货不足.\n", shopping_cart[i].goods_name,
                 shopping_cart[i].shop_id, shopping_cart[i].purchase_num);
      } else {
        if (shopping_cart[i].purchase_num != 0)
          printf("%s : %s : %d\n余额不足.\n", shopping_cart[i].goods_name,
                 shopping_cart[i].shop_id, shopping_cart[i].purchase_num);
      }

      i++;
    } while (shopping_cart[i].purchase_num != 0);

    if (k != 0)
      printf("%d种商品购买完成, "
             "谢谢惠顾!\n详细信息请前往\"主菜单-查看已完成订单\".\n",
             k);
    else
      printf("抱歉, 您选择的商品均无法购买, 请先充值或删除部分订单.");

    char screen[10];
    printf("\n请输入任意字符并按回车键以继续...\n");
    scanf("%s", screen); // 延长屏幕显示时间

    //存入结构体

    return 1;
    break;
  }

  case 2: {
    cart_result_2(user_id);
    cart(user_id);
    break;
  }

  case 0: {
    break;
  }
  }
  return 0;
}

int cart_main(char user_id[30]) {
  int i = 0;
  char screen[10]; // 屏显字符串

  database_shopping_cart(user_id, 0);
  if (shopping_cart[0].purchase_num == 0) {
    printf("您暂时没有购物车信息, 请先添加部分订单.\n");
    printf("\n请输入任意字符并按回车键以继续...\n");
    scanf("%s", screen); // 延长屏幕显示时间
    return 0;
  }

  printf("您的购物车信息如下:\n");
  printf("商品名     超市名       购买数量\n");
  while (shopping_cart[i].purchase_num != 0) {
    printf("%-12s %-16s %4d\n", shopping_cart[i].goods_name,
           shopping_cart[i].shop_id, shopping_cart[i].purchase_num);
    i++;
  }

  cart(user_id);

  database_shopping_cart(user_id, 1);
  database_shopping_cart(user_id, 0);

  return 1; //指用户已经结算购物车
}
