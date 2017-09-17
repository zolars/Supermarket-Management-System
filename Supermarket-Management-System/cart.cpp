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
    printf("\n您的输入有误, 请按照操作选项再次输入:\n\n");
    choose_num = cart_choose();
  } else
    choose_num = atoi(choose);

  return choose_num;
}

int cart(char user_id[30]) {

  int choose = cart_choose(); // 用户界面传入指令

  switch (choose) {
  case 1: {

    int i = 0, k = 0; // 记录是否有购买完成
    printf("以下为购买状态(商品ID : 超市ID : 购买数量)\n");

    do {
      if (shopping(shopping_cart[i].goods_id, shopping_cart[i].shop_id,
                   shopping_cart[i].purchase_num) == 1) {
        printf("%s : %s : %d\n购买成功!\n", shopping_cart[i].goods_id,
               shopping_cart[i].shop_id, shopping_cart[i].purchase_num);

        //缓存
        k += 1;
        shopping_cart[i].purchase_num = -1;
      } else if (shopping(shopping_cart[i].goods_id, shopping_cart[i].shop_id,
                          shopping_cart[i].purchase_num) == 0) {
        printf("%s : %s : %d\n存货不足.\n", shopping_cart[i].goods_id,
               shopping_cart[i].shop_id, shopping_cart[i].purchase_num);
      } else {
        printf("%s : %s : %d\n余额不足.\n", shopping_cart[i].goods_id,
               shopping_cart[i].shop_id, shopping_cart[i].purchase_num);
      }

      i++;
    } while (shopping_cart[i].purchase_num != 0);

    if (k != 0)
      printf("%d种商品购买完成, "
             "谢谢惠顾!\n详细信息请前往\"主菜单-查看已完成订单\".\n",
             k);
    else
      printf("抱歉, 您所要购买的商品存货均不足, 请先删除或更改部分订单.");

    char screen[10];
    printf("\n请输入任意字符并按回车键以继续...\n");
    scanf("%s", screen); // 延长屏幕显示时间

    //存入结构体

    return 1;
    break;
  }

  case 2: {
    printf("查看详情");
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

  while (shopping_cart[i].purchase_num != 0) {
    printf("%s %s %d\n", shopping_cart[i].goods_id, shopping_cart[i].shop_id,
           shopping_cart[i].purchase_num);
    i++;
  }

  cart(user_id);

  database_shopping_cart(user_id, 1);
  database_shopping_cart(user_id, 0);

  return 1; //指用户已经结算购物车
}
