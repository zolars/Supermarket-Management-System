/************************************************

Name:
  add_goods.cpp
Author:
  王克淼
Date:
  2017-09-15
Language:
  C
Features:

************************************************/

#include "add_goods.h"
#include "database.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sub_shop_index; // 用于减掉由于文件末尾空行导致的录入错误
int sub_goods_index; // 这个细节要万分注意

// 选项1，确认发布
void add_goods_result_1(int deep_num_shop) {

  // 覆盖shop_index数据库
  database_shop_index(admin_information.shop_id, 1);

  // 覆盖goods_index数据库
  database_goods_index(shop_index[deep_num_shop].goods_id, 1);

  return;
}

// 选项2，取消发布
void add_goods_result_2() { return; }

//检查商品ID
int check_goods_id(int deep_num_shop) {
  char temp_goods_id[10];

  do {
    scanf("%s", temp_goods_id);

    int i = 0, k, check_num = 1;

    for (i = 0; temp_goods_id[i] != '\0'; i++) {
      k = isdigit(temp_goods_id[i]);
      if (i == 0 || i == 1) {
        if (temp_goods_id[i] < 'A' || temp_goods_id[i] > 'Z')
          check_num = 0;
      } else if (i >= 2 && i <= 5) {
        if (!k)
          check_num = 0;
      } else
        check_num = 0;
    }

    if (i == 6 && check_num == 1)
      break;
    else {
      printf("您输入的商品ID不合法，请重新输入: \n");
      printf("请输入商品ID: \n");
    }
  } while (1);

  if (!database_goods_index(temp_goods_id, 0)) { // 数据库读取, 只读
    database_goods_index(temp_goods_id, 1); // 如果没有该文档, 新建一个
    sub_goods_index = 1;
  }

  strcpy(shop_index[deep_num_shop].goods_id, temp_goods_id);

  int deep_num_goods = 0; // 结构体深度
  // 遍历求深度
  do {
    deep_num_goods += 1;
  } while (goods_index[deep_num_goods].unit_price != 0);
  deep_num_goods -= sub_goods_index;

  strcpy(goods_index[deep_num_goods].shop_id, admin_information.shop_id);

  return (deep_num_goods);
}

//检查单价
void check_unit_price(int deep_num_shop, int deep_num_goods) {
  float price = 0;

  do {
    char price_str[10];
    scanf("%s", price_str);

    price = 0;
    price = atof(price_str); // 字符串转浮点型

    if ((int(price * 100) != (price * 100)) || price == 0) {
      printf("\n您的输入不合法，请重新输入:\n");
      printf("请输入单价: \n");
      continue;
    } else if (strlen(price_str) > 8 || atof(price_str) > 50000) {
      printf("\n售价不得超过五万, 请检查后重新输入!\n");
      printf("请输入单价: \n");
      continue;
    }
    break;
  } while (1);

  shop_index[deep_num_shop].unit_price = price;
  goods_index[deep_num_goods].unit_price = price;
  return;
}

//检查进价
void check_in_price(int deep_num_shop, int deep_num_goods) {
  float price = 0;
  do {
    char price_str[10];
    scanf("%s", price_str);

    price = 0;
    price = atof(price_str); // 字符串转浮点型

    if ((int(price * 100) != (price * 100)) || price == 0) {
      printf("\n您的输入不合法，请重新输入:\n");
      printf("请输入进价: \n");
      continue;
    } else if (strlen(price_str) > 8 || atof(price_str) > 50000) {
      printf("\n进价不得超过五万, 请检查后重新输入!\n");
      printf("请输入进价: \n");
      continue;
    }
    break;
  } while (1);

  shop_index[deep_num_shop].in_price = price;
  goods_index[deep_num_goods].in_price = price;
  return;
}

//检查库存
void check_goods_in_stock(int deep_num_shop, int deep_num_goods) {
  int goods_in_stock;

  do {
    char goods_in_stock_str[10];
    scanf("%s", goods_in_stock_str);

    goods_in_stock = atoi(goods_in_stock_str);
    if (goods_in_stock <= 0) {
      printf("\n您的输入不合法，请重新输入: \n");
      printf("请输入库存: \n");
      continue;
    }
    break;
  } while (1);

  goods_index[deep_num_goods].goods_in_stock = goods_in_stock;
  shop_index[deep_num_shop].goods_in_stock = goods_in_stock;

  return;
}

//检查折扣价格
void check_discount_price(int deep_num_shop, int deep_num_goods) {
  float price = 0;

  do {
    char price_str[10];
    scanf("%s", price_str);

    price = atof(price_str); // 字符串转浮点型

    if ((int(price * 100) != (price * 100)) || price == 0) {
      printf("\n您的输入不合法，请重新输入:\n");
      printf("请输入折扣价格: \n");
      continue;
    } else if (strlen(price_str) > 8 || atof(price_str) > 50000) {
      printf("\n折扣价不得超过五万, 请检查后重新输入!\n");
      printf("请输入折扣价格: \n");
      continue;
    }
    break;
  } while (1);

  goods_index[deep_num_goods].discount_price = price;
  shop_index[deep_num_shop].discount_price = price;
  return;
}

//检查折扣开始时间
void check_begin_time(int deep_num_shop, int deep_num_goods) {

  int time_temp = 0;
  do {
    printf("年份: ");
    char time_str[10];
    scanf("%s", time_str);

    time_temp = atoi(time_str);
    if (time_temp < 1000 || time_temp > 9999) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);
  goods_index[deep_num_goods].time_begin.tm_year = time_temp;
  shop_index[deep_num_shop].time_begin.tm_year = time_temp;

  time_temp = 0;
  do {
    printf("月份: ");
    char time_str[10];
    scanf("%s", time_str);

    time_temp = atoi(time_str);
    if (time_temp < 1 || time_temp > 12) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);

  goods_index[deep_num_goods].time_begin.tm_mon = time_temp;
  shop_index[deep_num_shop].time_begin.tm_mon = time_temp;

  time_temp = 0;
  do {
    printf("日期: ");
    char time_str[10];
    scanf("%s", time_str);

    time_temp = atoi(time_str);
    if (time_temp < 1 || time_temp > 31) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);

  goods_index[deep_num_goods].time_begin.tm_mday = time_temp;
  shop_index[deep_num_shop].time_begin.tm_mday = time_temp;

  time_temp = 0;
  do {
    printf("小时: ");
    char time_str[10];
    scanf("%s", time_str);

    time_temp = atoi(time_str);
    if (time_temp < 0 || time_temp > 23) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);

  goods_index[deep_num_goods].time_begin.tm_hour = time_temp;
  shop_index[deep_num_shop].time_begin.tm_hour = time_temp;

  time_temp = 0;
  do {
    printf("分钟: ");
    char time_str[10];
    scanf("%s", time_str);

    time_temp = atoi(time_str);
    if (time_temp < 0 || time_temp > 60) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);

  goods_index[deep_num_goods].time_begin.tm_min = time_temp;
  shop_index[deep_num_shop].time_begin.tm_min = time_temp;

  return;
}

void check_end_time(int deep_num_shop, int deep_num_goods) {
  int time_temp;

  time_temp = 0;
  do {
    printf("年份: ");
    char time_str[10];
    scanf("%s", time_str);

    time_temp = atoi(time_str);
    if (time_temp < 1000 || time_temp > 9999) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);

  goods_index[deep_num_goods].time_end.tm_year = time_temp;
  shop_index[deep_num_shop].time_end.tm_year = time_temp;

  time_temp = 0;
  do {
    printf("月份: ");
    char time_str[10];
    scanf("%s", time_str);

    time_temp = atoi(time_str);
    if (time_temp < 1 || time_temp > 12) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);

  goods_index[deep_num_goods].time_end.tm_mon = time_temp;
  shop_index[deep_num_shop].time_end.tm_mon = time_temp;

  time_temp = 0;
  do {
    printf("日期: ");
    char time_str[10];
    scanf("%s", time_str);

    time_temp = atoi(time_str);
    if (time_temp < 1 || time_temp > 31) {
      printf("\n您的输入不合法，请重��输入: \n");
      continue;
    }
    break;
  } while (1);

  goods_index[deep_num_goods].time_end.tm_mday = time_temp;
  shop_index[deep_num_shop].time_end.tm_mday = time_temp;

  time_temp = 0;
  // 小���
  do {
    printf("小时: ");
    char time_str[10];
    scanf("%s", time_str);

    time_temp = atoi(time_str);
    if (time_temp < 0 || time_temp > 24) {
      printf("\n���的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);

  goods_index[deep_num_goods].time_end.tm_hour = time_temp;
  shop_index[deep_num_shop].time_end.tm_hour = time_temp;

  time_temp = 0;
  do {
    printf("分钟: ");
    char time_str[10];
    scanf("%s", time_str);

    time_temp = atoi(time_str);
    if (time_temp < 0 || time_temp > 60) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);

  goods_index[deep_num_goods].time_end.tm_min = time_temp;
  shop_index[deep_num_shop].time_end.tm_min = time_temp;

  return;
}

//输入新商品信息
void check_information() {
  int deep_num_shop = 0; // 结构体深度
  // 遍历求深度
  do {
    deep_num_shop += 1;
  } while (shop_index[deep_num_shop].unit_price != 0);
  deep_num_shop -= sub_shop_index;

  printf("请依次输入商品信息: \n");

  //输入商品ID并检查
  printf("请输入商品ID: \n");
  int deep_num_goods = check_goods_id(deep_num_shop);

  //输入单价并检查
  printf("请输入单价: \n");
  check_unit_price(deep_num_shop, deep_num_goods);

  //输入进价并检查
  printf("请输入进价: \n");
  check_in_price(deep_num_shop, deep_num_goods);

  //输入销量，因为是新货， 销量默认为0
  shop_index[deep_num_shop].sales_volume = 0;
  goods_index[deep_num_goods].sales_volume = 0;

  //输入库存并检查
  printf("请输入库存: \n");
  check_goods_in_stock(deep_num_shop, deep_num_goods);

  //输入折扣价格并检查
  printf("请输入折扣价格: \n");
  check_discount_price(deep_num_shop, deep_num_goods);

  //输入折扣开始时间并检查
  printf("请输入折扣开始时间: \n");
  check_begin_time(deep_num_shop, deep_num_goods);

  //输入折扣结束时间并检查
  printf("请输入折扣结束时间: \n");
  check_end_time(deep_num_shop, deep_num_goods);
}

/************************************************/

int add_goods_choose() {

  char choose[10]; // 记录管理员操作时的选择
  int choose_num;

  // 用户界面
  printf("\n---------------操作选项---------------\n\n");
  printf("1. 确认发布.\n2. 取消发布.\n");
  printf("\n-------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");

  scanf("%s", choose);

  // 容错判断
  if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0) {
    printf("\n您的输入有误, 请按照操作选项再次输入:\n\n");
    choose_num = add_goods_choose();
  } else
    choose_num = atoi(choose);
  return choose_num;
}

void add_goods(char user_id[30]) {

  //输入信息并进行检查
  check_information();

  //进一步操作
  int choose = add_goods_choose();

  switch (choose) {

  case 1: {
    int deep_num_shop;
    // 遍历求深度
    while (shop_index[deep_num_shop].unit_price != 0) {
      deep_num_shop += 1;
    }
    deep_num_shop -= 1;

    add_goods_result_1(deep_num_shop);
    break;
  }

  case 2: {
    add_goods_result_2();
    break;
  }

    return;
  }
}

// 主程序, 负责读取数据库以及传入下一层.
int add_goods_main(char user_id[30]) {

  database_admin_information(user_id, 0);

  if (!database_shop_index(admin_information.shop_id,
                           0)) { // 数据库读取, 只读
    database_shop_index(admin_information.shop_id,
                        1); // 如果没��该文档, 新建一个
    sub_shop_index = 1;
  }

  add_goods(user_id);

  return 1;
}
