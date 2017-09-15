#include "database.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 选项1，确认发布
void add_goods_result_1(char user_id[30]) {

  // 覆盖shop_index数据库
  database_shop_index(user_id, 1);

  // 覆盖goods_index数据库
  database_goods_index(user_id, 1);
  return;
}

// 选项2，取消发布
void add_goods_result_2() { return; }

// 选项3，修改
void add_goods_result_3() { return; }

/************************************************/

//检查超市ID
void check_shop_id(int deep_num) {

  do {
    scanf("%s", goods_index[deep_num].shop_id);

    int i = 0, j, check_num = 1;
    for (i = 0; (goods_index[deep_num].shop_id[i] = '\0'); i++) {
      j = isalpha(goods_index[deep_num].shop_id[i]);
      if (i >= 0 && i <= 3) {
        if (!j)
          check_num = 0;
      }
      if (i == 4 && check_num == 1)
        break;
      else {
        printf("您输入的超市ID不合法，请重新输入: \n");
      }
    }
  } while (1);
  return;
}

//检查商品ID
void check_goods_id(int deep_num) {

  do {
    scanf("%s", shop_index[deep_num].goods_id);

    int i = 0, j, k, check_num = 1;
    for (i = 0; shop_index[deep_num].goods_id[i] != '\0'; i++) {
      j = isalpha(shop_index[deep_num].goods_id[i]);
      k = isdigit(shop_index[deep_num].goods_id[i]);
      if (i == 0 || i == 1) {
        if (!j)
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
    }
  } while (1);
  return;
}

//检查单价
void check_unit_price(int deep_num) {
  do {
    char price_str[10];
    scanf("%s", price_str);

    double price;
    price = atof(price_str); // 字符串转浮点型

    if ((int(price * 100) != (price * 100)) || price == 0) {
      printf("\n您的输入不合法，请重新输入:\n");
      continue;
    } else if (strlen(price_str) > 8 || atof(price_str) > 50000) {
      printf("\n售价不得超过五万, 请检查后重新输入!\n");
      continue;
    }
    break;
  } while (1);

  float price;

  shop_index[deep_num].unit_price = price;
  goods_index[deep_num].unit_price = price;
  return;
}

//检查进价
void check_in_price(int deep_num) {
  do {
    char price_str[10];
    scanf("%s", price_str);

    double price;
    price = atof(price_str); // 字符串转浮点型

    if ((int(price * 100) != (price * 100)) || price == 0) {
      printf("\n您的输入不合法，请重新输入:\n");
      continue;
    } else if (strlen(price_str) > 8 || atof(price_str) > 50000) {
      printf("\n进价不得超过五万, 请检查后重新输入!\n");
      continue;
    }
    break;
  } while (1);

  float price;

  shop_index[deep_num].in_price = price;
  goods_index[deep_num].in_price = price;
  return;
}

//检查库存
void check_goods_in_stock(int deep_num) {
  do {
    char goods_in_stock_str[10];
    scanf("%s", goods_in_stock_str);

    int goods_in_stock = atoi(goods_in_stock_str);
    if (goods_in_stock <= 0) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);

  int goods_in_stock;

  goods_index[deep_num].goods_in_stock = goods_in_stock;
  shop_index[deep_num].goods_in_stock = goods_in_stock;

  return;
}

//检查折扣价格
void check_price(int deep_num) {
  do {
    char price_str[10];
    scanf("%s", price_str);

    double price;
    price = atof(price_str); // 字符串转浮点型

    if ((int(price * 100) != (price * 100)) || price == 0) {
      printf("\n您的输入不合法，请重新输入:\n");
      continue;
    } else if (strlen(price_str) > 8 || atof(price_str) > 50000) {
      printf("\n进价不得超过五万, 请检查后重新输入!\n");
      continue;
    }
    break;
  } while (1);

  float price;

  goods_index[deep_num].discount_price = price;
  shop_index[deep_num].discount_price = price;
  return;
}

//检查折扣开始时间
void check_begin_time(int deep_num) {

  do {
    printf("年份: ");
    scanf("%s", shop_index[deep_num].time_begin.year);
    goods_index[deep_num].time_begin.year =
        shop_index[deep_num].time_begin.year;
    long time_begin.year = atol(shop_index[deep_num].time_begin.year);
    if (time_begin.year < 1000 || time_begin.year > 9999) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);

  do {
    printf("月份: ");
    scanf("%s", shop_index[deep_num].time_begin.month);
    goods_index[deep_num].time_begin.month =
        shop_index[deep_num].time_begin.month;
    long time_begin.month = atol(shop_index[deep_num].time_begin.month);
    if (time_begin.year < 1 || time_begin.year > 12) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);

  do {
    printf("日期: ");
    scanf("%s", shop_index[deep_num].time_begin.day);
    goods_index[deep_num].time_begin.day = shop_index[deep_num].time_begin.day;
    long time_begin.day = atol(shop_index[deep_num].time_begin.day);
    if (time_begin.day < 1 || time_begin.day > 31) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);

  do {
    printf("小时: ");
    scanf("%s", shop_index[deep_num].time_begin.hour);
    goods_index[deep_num].time_begin.hour =
        shop_index[deep_num].time_begin.hour;
    long time_begin.hour = atol(shop_index[deep_num].time_begin.hour);
    if (time_begin.hour < 1 || time_begin.hour > 24) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);

  do {
    printf("分钟: ");
    scanf("%s", shop_index[deep_num].time_begin.minute);
    goods_index[deep_num].time_begin.minute =
        shop_index[deep_num].time_begin.minute;
    long time_begin.minute = atol(shop_index[deep_num].time_begin.minute);
    if (time_begin.minute < 1 || time_begin.minute > 60) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);
  return;
}

//检查折扣结束时间
void check_end_time(int deep_num) {
  do {
    printf("年份: ");
    scanf("%s", shop_index[deep_num].time_end.year);
    goods_index[deep_num].time_end.year = shop_index[deep_num].time_end.year;
    long time_end.year = atol(shop_index[deep_num].time_end.year);
    if (time_end.year < 1000 || time_end.year > 9999) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);

  do {
    printf("月份: ");
    scanf("%s", shop_index[deep_num].time_end.month);
    goods_index[deep_num].time_end.month = shop_index[deep_num].time_end.month;
    long time_end.month = atol(shop_index[deep_num].time_end.month);
    if (time_end.year < 1 || time_end.year > 12) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);

  do {
    printf("日期: ");
    scanf("%s", shop_index[deep_num].time_end.day);
    goods_index[deep_num].time_end.day = shop_index[deep_num].time_end.day;
    long time_end.day = atol(shop_index[deep_num].time_end.day);
    if (time_end.day < 1 || time_end.day > 31) {
      printf("\n您的输入不合法，请重�����输入: \n");
      continue;
    }
    break;
  } while (1);

  do {
    printf("小��: ");
    scanf("%s", shop_index[deep_num].time_end.hour);
    goods_index[deep_num].time_end.hour = shop_index[deep_num].time_end.hour;
    long time_end.hour = atol(shop_index[deep_num].time_end.hour);
    if (time_end.hour < 1 || time_end.hour > 24) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);

  do {
    printf("分钟: ");
    scanf("%s", shop_index[deep_num].time_end.minute);
    goods_index[deep_num].time_end.minute =
        shop_index[deep_num].time_end.minute;
    long time_end.minute = atol(shop_index[deep_num].time_end.minute);
    if (time_end.minute < 1 || time_end.minute > 60) {
      printf("\n您的输入不合法，请重新输入: \n");
      continue;
    }
    break;
  } while (1);

  return;
}

//��入新商品信息
void check_information() {
  int deep_num = 0; // 循环变量
  // 遍历求深度
  do {
    deep_num += 1;
  } while (shop_index[deep_num].price != 0);

  printf("请依次输入商品信息: \n");

  //输入超市ID并检查
  printf("超市ID: ");
  check_shop_id(deep_num);

  //输入商品ID并检查
  printf("商品ID: ");
  check_goods_id(deep_num);

  //输入单价并检查
  printf("单价: ");
  check_price(deep_num);

  //输入进价并检查
  printf("进价: ");
  check_price(deep_num);

  //输入销量，因为是新货， 销量默认为0
  shop_index[deep_num].sales_volume = 0;
  goods_index[deep_num].sales_volume = 0;

  //输入库存并检查
  printf("库存: ");
  check_goods_in_stock(deep_num);

  //输入折扣价格并检查
  printf("折扣价格: ");
  check_price(deep_num);

  //输入折扣开始时间并检查
  printf("折扣开始时间: \n");
  check_begin_time(deep_num);

  //输入折扣结束时间并检查
  printf("折扣结束时间: \n");
  check_end_time(deep_num);
}

/************************************************/

void check_information() { return; }

int add_goods_choose() {

  char choose[10]; // 记录管理员操作时的选择
  int choose_num;

  // 用户界面
  printf("\n---------------操作选项---------------\n\n");
  printf("1. 确认发布.\n2. 取消发布.\n");
  printf("3. 修改信息.\n");
  printf("\n-------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");

  scanf("%s", choose);

  // 容错判断
  if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
      strcmp(choose, "3") != 0) {
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
    add_goods_result_1(user_id);
    break;
  }

  case 2: {
    add_goods_result_2();
    break;
  }

  case 3: {
    add_goods_result_3();
    add_goods(user_id);
    break;
  }
  }

  return;
}

// 主程序, 负责读取数据库以及传入下一层.
int add_goods_main(char user_id[30]) {

  if (!database_shop_index(user_id, 0)) { // 数据库读取, 只读
    database_shop_index(user_id, 1);      // 如果没有该文档, 新建一个
  }

  if (!database_goods_index(user_id, 0)) { // 数据库读取, 只读
    database_goods_index(user_id, 1); // 如果没有该文档, 新建一个
  }

  add_goods(user_id);

  return 1;
}

int main() {
  char user_id[30] = "guanli";
  add_goods_main(user_id);
  return 0;
}
