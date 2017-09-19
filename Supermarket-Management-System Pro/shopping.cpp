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

  - temp_goods_name

  - temp_shop_id

  - temp_purchase_num

Output:
  - 1: 购买成功

  - 0: 存货不足

  - (-1): 余额不足

************************************************/

#include "check_time.h"
#include "database.h"
#include "shopping.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int shopping(char user_id[30], char temp_goods_name[10], char temp_shop_id[10],
             int temp_purchase_num) {
  int i = 0;

  if (!database_goods_index(temp_goods_name, 0)) {
    return 0;
  }

  database_consumer_information(user_id, 0);

  while (goods_index[i].in_price != 0) {
    if (strcmp(temp_shop_id, goods_index[i].shop_id) == 0)
      break;
    else
      i++;
  }

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

  float temp_profit;
  temp_profit = temp_price - goods_index[i].in_price;

  if (temp_price * temp_purchase_num <= consumer_information.money) {

    /************************************************
    减掉顾客余额
    数据库: consumer_information
    ************************************************/

    consumer_information.money -= temp_price * temp_purchase_num;
    database_consumer_information(user_id, 1);

    /************************************************
    减掉商品清单中的库存, 销量加1
    数据库: goods_index
    ************************************************/

    goods_index[i].goods_in_stock -= temp_purchase_num;
    goods_index[i].sales_volume += 1;
    database_goods_index(temp_goods_name, 1);

    /************************************************
    减掉商店清单中的库存, 销量加1
    数据库: shop_index
    ************************************************/

    database_shop_index(temp_shop_id, 0);

    while (shop_index[i].in_price != 0) {
      if (strcmp(temp_goods_name, shop_index[i].goods_name) == 0)
        break;
      else
        i++;
    }
    shop_index[i].goods_in_stock -= temp_purchase_num;
    shop_index[i].sales_volume += 1;

    database_shop_index(temp_shop_id, 1);

    /************************************************
    增加管理员订单all
    数据库: order_admin_all
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
    tm_local->tm_year += 1900; // 处理tm类型偏差
    tm_local->tm_mon += 1;     // 处理tm类型偏差
    sprintf(time_str, "%04d:%02d:%02d:%02d:%02d", tm_local->tm_year,
            tm_local->tm_mon, tm_local->tm_mday, tm_local->tm_hour,
            tm_local->tm_min);

    strcpy(order_admin_all[i].order_id, user_id); // 订单编号
    strcat(order_admin_all[i].order_id, "|");
    strcat(order_admin_all[i].order_id, time_str);
    strcpy(time_str, "");

    order_admin_all[i].sold_time.tm_year = tm_local->tm_year; // 记录购买时间
    order_admin_all[i].sold_time.tm_mon = tm_local->tm_mon;   // ...
    order_admin_all[i].sold_time.tm_mday = tm_local->tm_mday; // ...
    order_admin_all[i].sold_time.tm_hour = tm_local->tm_hour; // ...
    order_admin_all[i].sold_time.tm_min = tm_local->tm_min;   // ...

    strcpy(order_admin_all[i].consumer_id, user_id);        // 顾客ID
    strcpy(order_admin_all[i].goods_name, temp_goods_name); // 商品名
    order_admin_all[i].unit_price = temp_price;             // 单价
    order_admin_all[i].purchase_num = temp_purchase_num;    // 购买数量
    order_admin_all[i].all_price = temp_price * temp_purchase_num; // 总价

    database_order_admin_all(temp_shop_id, 1);

    /************************************************
    增加管理员订单_goods
    数据库: order_admin_goods
    ************************************************/

    if (!database_order_admin_goods(temp_shop_id, 0))
      database_order_admin_goods(temp_shop_id, 1);

    i = 0;
    while (order_admin_goods[i].purchase_num != 0) {
      if (strcmp(temp_goods_name, order_admin_goods[i].goods_name) == 0)
        break;
      else
        i++;
    }
    if (order_admin_goods[i].purchase_num == 0) {
      strcpy(order_admin_goods[i].goods_name, temp_goods_name); // 商品名
      order_admin_goods[i].purchase_num = temp_purchase_num;    // 销量
      order_admin_goods[i].all_price = temp_price * temp_purchase_num; // 总价
      order_admin_goods[i].profit = temp_profit * temp_purchase_num;   // 利润
    } else {
      order_admin_goods[i].purchase_num += temp_purchase_num; // 销量
      order_admin_goods[i].all_price += temp_price * temp_purchase_num; // 总价
      order_admin_goods[i].profit += temp_profit * temp_purchase_num; // 利润
    }

    database_order_admin_goods(temp_shop_id, 1);

    /************************************************
    增加管理员订单_consumer
    数据库: order_admin_consumer
    ************************************************/

    if (!database_order_admin_consumer(temp_shop_id, 0))
      database_order_admin_consumer(temp_shop_id, 1);

    i = 0;
    while (order_admin_consumer[i].purchase_num != 0) {
      if (strcmp(user_id, order_admin_consumer[i].consumer_id) == 0)
        break;
      else
        i++;
    }

    if (order_admin_consumer[i].purchase_num == 0 ||
        order_admin_consumer[i].purchase_num < temp_purchase_num) {
      strcpy(order_admin_consumer[i].consumer_id, user_id);
      strcpy(order_admin_consumer[i].goods_name, temp_goods_name);
      order_admin_consumer[i].purchase_num = temp_purchase_num;
    }

    database_order_admin_consumer(temp_shop_id, 1);

    /************************************************
    增加顾客订单
    数据库: order_consumer
    ************************************************/
    if (!database_order_consumer(user_id, 0))
      database_order_consumer(user_id, 1);

    // 深度探测
    i = 0;
    while (order_consumer[i].purchase_num != 0)
      i++;

    // 找到目前的时间信息并存入字符串
    calendar_time = time(NULL);
    struct tm *tm_local2 = localtime(&calendar_time);
    tm_local2->tm_year += 1900; // 处理tm类型偏差
    tm_local2->tm_mon += 1;     // 处理tm类型偏差
    sprintf(time_str, "%04d:%02d:%02d:%02d:%02d", tm_local2->tm_year,
            tm_local2->tm_mon, tm_local2->tm_mday, tm_local2->tm_hour,
            tm_local2->tm_min);

    strcpy(order_consumer[i].order_id, order_admin_all[i].order_id); // 订单编号
    strcpy(order_consumer[i].sold_time, time_str);         // 购买时间
    strcpy(order_consumer[i].goods_name, temp_goods_name); // 商品名
    order_consumer[i].purchase_num = temp_purchase_num;    // 购买数量
    order_consumer[i].unit_price = temp_price;             // 单价
    order_consumer[i].all_price = temp_price * temp_purchase_num; // 总价

    database_order_consumer(user_id, 1);

    return 1;
  }

  else
    return -1;

  return 1;
}
