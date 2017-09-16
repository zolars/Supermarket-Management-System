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
#include "check_goods.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int time_check(int num) { // 传入goods_index中第num行数据
  struct tm begin_tm = {
      0,                                   // 秒
      goods_index[num].time_begin.tm_min,  // 分钟数
      goods_index[num].time_begin.tm_hour, // 小时数
      goods_index[num].time_begin.tm_mday, // 当天在这个月中是第几天
      goods_index[num].time_begin.tm_mon,  // 当前月份是第几个月
      goods_index[num].time_begin.tm_year - 1900, // 从1900年开始至今的年数
      0,                                          // 当天在本周是第几天
      0,                                          // 当天在今年是第几天
      0                                           // 夏令时标记
  };
  time_t begin_tm_t = mktime(&begin_tm); // 将人类看得懂的时间转换为tick类型

  struct tm end_tm = {
      0,                                 // 秒
      goods_index[num].time_end.tm_min,  // 分钟数
      goods_index[num].time_end.tm_hour, // 小时数
      goods_index[num].time_end.tm_mday, // 当天在这个月中是第几天
      goods_index[num].time_end.tm_mon,  // 当前月份是第几个月
      goods_index[num].time_end.tm_year - 1900, // 从1900年开始至今的年数
      0,                                        // 当天在本周是第几天
      0,                                        // 当天在今年是第几天
      0                                         // 夏令时标记
  };
  time_t end_tm_t = mktime(&end_tm); // 将人类看得懂的时间转换为tick类型

  time_t calendar_time_t = time(NULL);
  struct tm *tm_local = localtime(&calendar_time_t); // 传入本地时间
  time_t now_tm_t = mktime(tm_local); // 将人类看得懂的时间转换为tick类型

  if (begin_tm_t <= now_tm_t && end_tm_t >= now_tm_t) {
    printf("bt: %ld\nnt: %ld\tet: %ld\n", begin_tm_t, now_tm_t, end_tm_t);
    return 1;
  }

  printf("bt: %ld\nnt: %ld\tet: %ld\n", begin_tm_t, now_tm_t, end_tm_t);
  printf("none");
  return 0;
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

    // 计算是否透支余额
    int i = 0, j;
    float temp_price = 0; // 价格累加器

    do {
      j = 0;
      database_goods_index(shopping_cart[i].goods_id, 0);
      do {
        if (strcmp(shopping_cart[i].shop_id, goods_index[j].shop_id) == 0)
          break;
        else
          j++;
      } while (goods_index[j].unit_price != 0);

      if (time_check(j)) // 传入goods_index中第j行数据
        temp_price +=
            shopping_cart[i].purchase_num * goods_index[j].discount_price;
      else
        temp_price += shopping_cart[i].purchase_num * goods_index[j].unit_price;

      i++;
    } while (shopping_cart[i].purchase_num != 0);

    database_consumer_information(user_id, 0);

    if (temp_price > consumer_information.money) {
      printf("您的余额不足以购买所有物品, 请先充值或删除部分订单.");
      printf("\n请输入任意字符并按回车键以继续...\n");
      char screen[10];
      scanf("%s", screen); // 延长屏幕显示时间
      return (cart(user_id));
    }

    i = 0;
    do {
      if (check_goods(shopping_cart[i].goods_id, shopping_cart[i].shop_id,
                      shopping_cart[i].purchase_num) == 1) {
        //缓存
        shopping_cart[i].purchase_num = -1;
      }
      i++;
    } while (shopping_cart[i].purchase_num != 0);

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

  printf("\n请输入任意字符并按回车键以继续...\n");

  scanf("%s", screen); // 延长屏幕显示时间

  if (cart(user_id) == 0) {
    return 0; // 指用户返回上一级菜单，在主函数里返回一个0
  }

  database_shopping_cart(user_id, 1);
  database_shopping_cart(user_id, 0);

  printf("购买完成, 谢谢惠顾!\n");
  printf("以下为本次购买物品清单, 详细信息请前往\"主菜单-查看已完成订单\". ");

  i = 0;
  do {
    printf("%s %s %d\n", shopping_cart[i].goods_id, shopping_cart[i].shop_id,
           shopping_cart[i].purchase_num);
    i++;
  } while (shopping_cart[i].purchase_num != 0);

  printf("\n请输入任意字符并按回车键以继续...\n");
  scanf("%s", screen); // 延长屏幕显示时��
  return 1;            //指用户清空购物车
}
