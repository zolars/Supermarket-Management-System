#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_goods(char id[10], char market[10], int num) {

  database_goods_index(id, 0);

  int i = 0;
  do {
    if (strcmp(market, goods_index[i].shop_id) == 0)
      break;
    else
      i++;
  } while (goods_index[i].in_price != 0);

  if (num > goods_index[i].goods_in_stock) {

    return 0;
  } else {
    return 1;
  }
}

int cart_choose() {
  char choose[10]; // 记录管理???操???时的选择
  int choose_num;
  // 用户界面
  printf("\n---------------操作选项---------------\n\n");
  printf("1. 清空购物车.\n0. 返回.\n");
  printf("\n-------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");
  scanf("%s", choose);
  if (strcmp(choose, "1") != 0 && strcmp(choose, "0") != 0) {
    printf("\n您的输入有误, 请按照操作选项再次输入:\n\n");
    choose_num = cart_choose();
  } else
    choose_num = atoi(choose);

  return choose_num;
}

int cart() {

  int choose = cart_choose(); // 用户界面传入指令
  switch (choose) {
  case 1: {
    int i = 0;
    do {
      if (check_goods(shopping_cart[i].goods_id, shopping_cart[i].shop_id,
                      shopping_cart[i].purchase_num) == 1) {
        //缓存
        shopping_cart[i].purchase_num = -1;
      }
      i++;
    } while (shopping_cart[i].purchase_num != 0);

    return 1;
    break;
  }

  case 0: {
    return 0;
    break;
  }
  }
  return 0;
}

int cart_main(char user_id[30]) {
  int i = 0;

  database_shopping_cart(user_id, 0);

  do {
    printf("%s %s %d\n", shopping_cart[i].goods_id, shopping_cart[i].shop_id,
           shopping_cart[i].purchase_num);
    i++;
  } while (shopping_cart[i].purchase_num != 0);
  if (cart() == 0)
    return 0; // 指用户返回上一级菜单，在主函数里返回一个0

  database_shopping_cart(user_id, 1);
  database_shopping_cart(user_id, 0);

  i = 0;
  do {
    printf("%s %s %d\n", shopping_cart[i].goods_id, shopping_cart[i].shop_id,
           shopping_cart[i].purchase_num);
    i++;
  } while (shopping_cart[i].purchase_num != 0);
  return 1; //指用户清空购物车
}
