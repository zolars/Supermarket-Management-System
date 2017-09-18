/************************************************

Name:
  shopping.cpp
Author:
  - 辛逸飞
Date:
  2017-09-16
Language:
  C
Features:
  完成购买入库的接口
Modules:
  Customize:
    - database.h
    - shopping.h
    - check_time.h
  Native:
    - stdio.h
    - string.h
    - stdlib.h
Input:
  - user_id

  - temp_goods_id

  - temp_shop_id

  - temp_purchase_num

Output:
  - 1

  - 0

  - (-1)

************************************************/

#include "check_time.h"
#include "database.h"
#include "shopping.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int shopping(char user_id[30], char temp_goods_id[10], char temp_shop_id[10],
             int temp_purchase_num) {
  int i = 0;

  if (!database_goods_index(temp_goods_id, 0)) {
    return 0;
  }

  database_consumer_information(user_id, 0);

  do {
    if (strcmp(temp_shop_id, goods_index[i].shop_id) == 0)
      break;
    else
      i++;
  } while (goods_index[i].in_price != 0);

  if (goods_index[i].in_price == 0)
    printf("运行出问题了? 请联系: zolars@outlook.com");

  if (temp_purchase_num > goods_index[i].goods_in_stock) {
    printf("%d %d", temp_purchase_num, goods_index[i].goods_in_stock);
    return 0;
  }

  // 判断时间

  int price_choice = check_time(i);

  float temp_price;
  if (price_choice)
    temp_price = goods_index[i].discount_price;
  else
    temp_price = goods_index[i].unit_price;

  if (temp_price * temp_purchase_num <= consumer_information.money) {

    /************************************************
    减掉顾客余额
    数据库: consumer_information
    ************************************************/

    consumer_information.money -= temp_price * temp_purchase_num;
    database_consumer_information(user_id, 1);

    /************************************************
    减掉商品清单中的库存
    数据库: goods_index
    ************************************************/

    goods_index[i].goods_in_stock -= temp_purchase_num;
    database_goods_index(temp_goods_id, 1);

    /************************************************
    增加管理员订单
    数据库order_admin
    ************************************************/

    // 找到该货物所对应的超市名并存入订单
    if (!database_order_admin_all(temp_shop_id, 0))
      database_order_admin_all(temp_shop_id, 1);

    // 深度探测
    i = 0;
    while (order_admin_all[i].purchase_num != 0)
      i++;

    // 找到目前的时间信息并存入字符串
    time_t calendar_time = time(NULL);
    struct tm *tm_local = localtime(&calendar_time);
    char time_str[30];
    sprintf(time_str, "%04d:%02d:%02d:%02d:%02d", tm_local->tm_year + 1900,
            tm_local->tm_mon + 1, tm_local->tm_mday, tm_local->tm_hour,
            tm_local->tm_min);

    strcpy(order_admin_all[i].order_id, user_id);
    strcat(order_admin_all[i].order_id, "|");
    strcat(order_admin_all[i].order_id, time_str);

    printf("%s %s %04d:%02d:%02d:%02d:%02d %s %d %f %f",
           order_admin_all[i].order_id,          // 订单编号
           order_admin_all[i].consumer_id,       // 顾客编号
           order_admin_all[i].sold_time.tm_year, // 购买时间
           order_admin_all[i].sold_time.tm_mon,  // ...
           order_admin_all[i].sold_time.tm_mday, // ...
           order_admin_all[i].sold_time.tm_hour, // ...
           order_admin_all[i].sold_time.tm_min,  // ...
           order_admin_all[i].goods_id,          // 商品ID
           order_admin_all[i].purchase_num,      // 购买数量
           order_admin_all[i].unit_price,        // 单价
           order_admin_all[i].all_price          // 总价
    );

    printf("alldone");
    return 1;
  }

  else
    return -1;

  return 1;
}
