/************************************************

Name:
  print_shop_index.cpp
Author:
  王楠鑫
Date:
  2017-09-15
Language:
  C
Features:

************************************************/

#include "database.h"
#include "print_shop_index.h"
#include <stdio.h>
#include <string.h>

int print_shop_index_main(char user_id[30]) {
  int i = 0;

  if (!database_admin_information(user_id, 0)) { // 数据库读取, 只读
    return 0; // 读取文件发生错误, 返回上一级
  }

  if (!database_shop_index(admin_information.shop_id, 0)) { // 数据库读取, 只读
    printf("您的库存中还没有商品, 请先添加部分商品.\n");
    return 0; // 读取文件发生错误, 返回上一级
  }
  printf("商品ID   单价   进价  销量  库存   折扣价格        "
         "折扣开始时间        折扣结束时间\n");

  while (shop_index[i].unit_price != 0) {
    printf("%s  %0.2f  %0.2f    %d   %d     %0.2f        "
           "%04d:%02d:%02d:%02d:%02d   "
           "%04d:%02d:%02d:%02d:%02d\n",
           shop_index[i].goods_id,          // 商品编号
           shop_index[i].unit_price,        // 零售价格
           shop_index[i].in_price,          // 进货价格
           shop_index[i].sales_volume,      // 销量
           shop_index[i].goods_in_stock,    // 存货
           shop_index[i].discount_price,    // 折扣价
           shop_index[i].time_begin.year,   // 折扣开始时间
           shop_index[i].time_begin.month,  // ...
           shop_index[i].time_begin.day,    // ...
           shop_index[i].time_begin.hour,   // ...
           shop_index[i].time_begin.minute, // ...
           shop_index[i].time_end.year,     // 折扣结束时间
           shop_index[i].time_end.month,    // ...
           shop_index[i].time_end.day,      // ...
           shop_index[i].time_end.hour,     // ...
           shop_index[i].time_end.minute    // ...
    );
    i++;
  }
  printf("\n请输入任意字符并按回车键以继续...\n");
  char screen[10];
  scanf("%s", screen); // 延长屏幕显示时间
  return 0;
}
