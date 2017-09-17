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

int shopping(char user_id[30], char temp_goods_id[10], char temp_shop_id[10],
             int temp_purchase_num) {
  int i = 0;

  if (!database_goods_index(temp_goods_id, 0))
    return 0;

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

    /************************************************
    减掉商品清单中的库存
    数据库: goods_index
    ************************************************/

    goods_index[i].goods_in_stock -= temp_purchase_num;

    /************************************************
    增加管理员订单
    数据库order_admin
    ************************************************/

    database_shop_to_admin(0);

    // 找到该货物所对应的管理员名
    do {
      if (strcmp(temp_shop_id, shop_to_admin[i].shop_id) == 0)
        break;
      else
        i++;
    } while (shop_to_admin[i].mark != 0);

    char temp_admin_id[30];
    strcpy(temp_admin_id, shop_to_admin[i].admin_id);
    if (shop_to_admin[i].mark == 0)
      printf("运行出问题了? 请联系: zolars@outlook.com");

    return 1;
  }

  else
    return -1;

  return 1;
}
