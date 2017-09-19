/************************************************

Name:
  buy_search_all.cpp
Author:
  董泽元
Date:
  2017-09-15
Language:
  C
Features:

************************************************/

#include "buy_search_all.h"
#include "database.h"
#include "search_for_goods.h"
#include "search_for_market.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int buy_search_all_choose() {
  char choose[10]; // 记录管理员操作时的选择
  int choose_num;

  // 用户界面
  printf("\n---------------操作选项---------------\n\n");
  printf("1. 搜索商品名.\n2. 搜索超市名.\n0. 返回.\n");
  printf("\n-------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");

  scanf("%s", choose);

  // 容错判断
  if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
      strcmp(choose, "0") != 0) {
    printf("\n您的输入有误, 请按照操作选项再次输入:\n\n");
    choose_num = buy_search_all_choose();
  } else
    choose_num = atoi(choose);
  return choose_num;
}

int buy_search_all(char user_id[30]) {
  printf("\n以下为我们推荐的部分商品清单(商品名 : 超市名), "
         "您可以参考其ID进行更准确的搜索, 祝您购物愉快.\n");

  char temp_a[5] = "true", temp_b[6] = "false";
  database_all_index(0, temp_a, temp_b);

  int choose = buy_search_all_choose(); // 用户界面传入指令

  switch (choose) {

  case 1: {
    search_goods_begin(user_id);
    buy_search_all(user_id);
    break;
  }

  case 2: {
    search_market_begin(user_id);
    buy_search_all(user_id);
    break;
  }

  // 返回上一层
  case 3: {
    break;
  }
  }
  return 1;
}
