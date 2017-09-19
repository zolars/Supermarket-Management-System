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

// 检查商品ID
char *check_goods_name(char *temp_goods_name) {
  do {
    scanf("%s", temp_goods_name);

    int i = 0, k, check_num = 1;

    for (i = 0; temp_goods_name[i] != '\0'; i++) {
      k = isdigit(temp_goods_name[i]);
      if (i == 0 || i == 1) {
        if (temp_goods_name[i] < 'A' || temp_goods_name[i] > 'Z')
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
      printf("您的输入格式错误, 请检查后重新输入:\n");
      printf("请输入商品ID(2位大写字母+4位数字): \n");
    }
  } while (1);

  return temp_goods_name;
}

// 检查单价
float check_unit_price() {
  float price = 0;

  do {
    char price_str[10];
    scanf("%s", price_str);

    int i, j, k = 0, dot_num = 0; // 检测是否出现非数字字符以及小数点的规范
    for (i = 0; price_str[i] != '\0'; i++) {
      j = isdigit(price_str[i]);
      if (price_str[0] == '.') {
        k = k + 1;
        printf("\n您的输入格式错误, 请检查后重新输入:\n");
        printf("请输入单价: \n");
        break;
      }
      if (price_str[i + 1] == '\0' && price_str[i] == '.') {
        k = k + 1;
        printf("\n您的输入格式错误, 请检查后重新输入:\n");
        printf("请输入单价: \n");
        break;
      }
      if (price_str[i] == '.')
        dot_num = dot_num + 1;
      if (dot_num == 2) {
        k = k + 1;
        printf("\n您的输入格式错误, 请检查后重新输入:\n");
        printf("请输入单价: \n");
        break;
      }
      if (!j && price_str[i] != '.') {
        k = k + 1;
        printf("\n您的输入格式错误, 请检查后重新输入:\n");
        printf("请输入单价: \n");
        break;
      }
    }

    if (k == 1)
      continue;

    price = 0;
    price = atof(price_str); // 字符串转浮点型

    if ((int(price * 100) != (price * 100)) || price == 0) {
      printf("\n您的输入格式错误, 请检查后重新输入:\n");
      printf("请输入单价: \n");
      continue;
    } else if (strlen(price_str) > 8 || atof(price_str) > 50000) {
      printf("\n售价不得超过50000, 请检查后重新输入!\n");
      printf("请输入单价: \n");
      continue;
    }
    break;
  } while (1);

  return price;
}

// 检查进价
float check_in_price() {
  float price = 0;
  do {
    char price_str[10];
    scanf("%s", price_str);

    int i, j, k = 0, dot_num = 0; // 检测是否出现非数字字符以及小数点的规范
    for (i = 0; price_str[i] != '\0'; i++) {
      j = isdigit(price_str[i]);
      if (price_str[0] == '.') {
        k = k + 1;
        printf("\n您的输入格式错误, 请检查后重新输入:\n");
        printf("请输入进价: \n");
        break;
      }
      if (price_str[i + 1] == '\0' && price_str[i] == '.') {
        k = k + 1;
        printf("\n您的输入格式错误, 请检查后重新输入:\n");
        printf("请输入进价: \n");
        break;
      }
      if (price_str[i] == '.')
        dot_num = dot_num + 1;
      if (dot_num == 2) {
        k = k + 1;
        printf("\n您的输入格式错误, 请检查后重新输入:\n");
        printf("请输入进价: \n");
        break;
      }
      if (!j && price_str[i] != '.') {
        k = k + 1;
        printf("\n您的输入格式错误, 请检查后重新输入:\n");
        printf("请输入进价: \n");
        break;
      }
    }

    if (k == 1)
      continue;

    price = 0;
    price = atof(price_str); // 字符串转浮点型

    if ((int(price * 100) != (price * 100)) || price == 0) {
      printf("\n您的输入格式错误, 请检查后重新输入:\n");
      printf("请输入进价: \n");
      continue;
    } else if (strlen(price_str) > 8 || atof(price_str) > 50000) {
      printf("\n进价不得超过50000, 请检查后重新输入!\n");
      printf("请输入进价: \n");
      continue;
    }
    break;
  } while (1);

  return price;
}

// 检查库存
int check_goods_in_stock() {
  int goods_in_stock;

  do {
    char goods_in_stock_str[10];
    scanf("%s", goods_in_stock_str);

    int i, j, k = 0; // 检测是否出现非数字字符
    for (i = 0; goods_in_stock_str[i] != '\0'; i++) {
      j = isdigit(goods_in_stock_str[i]);
      if (!j) {
        k = k + 1;
        printf("\n您的输入格式错误, 请检查后重新输入:\n");
        printf("请输入库存: \n");
        break;
      }
    }
    if (k == 1)
      continue;

    goods_in_stock = atoi(goods_in_stock_str);
    if (goods_in_stock <= 0 && k == 0) {
      printf("\n您的输入格式错误, 请检查后重新输入:\n");
      printf("请输入库存: \n");
      continue;
    }
    break;
  } while (1);

  return goods_in_stock;
}

// 检查折扣价格
float check_discount_price() {
  float price = 0;

  do {
    char price_str[10];
    scanf("%s", price_str);

    int i, j, k = 0, dot_num = 0; // 检测是否出现非数字字符以及小数点的规范
    for (i = 0; price_str[i] != '\0'; i++) {
      j = isdigit(price_str[i]);
      if (price_str[0] == '.') {
        k = k + 1;
        printf("\n您的输入格式错误, 请检查后重新输入:\n");
        printf("请输入折扣价格: \n");
        break;
      }
      if (price_str[i + 1] == '\0' && price_str[i] == '.') {
        k = k + 1;
        printf("\n您的输入格式错误, 请检查后重新输入:\n");
        printf("请输入折扣价格: \n");
        break;
      }
      if (price_str[i] == '.')
        dot_num = dot_num + 1;
      if (dot_num == 2) {
        printf("\n您的输入格式错误, 请检查后重新输入:\n");
        k = k + 1;
        printf("请输入折扣价格: \n");
        break;
      }
      if (!j && price_str[i] != '.') {
        k = k + 1;
        printf("\n您的输入格式错误, 请检查后重新输入:\n");
        printf("请输入折扣价格: \n");
        break;
      }
    }
    if (k == 1)
      continue;
    price = atof(price_str); // 字符串转浮点型

    if ((int(price * 100) != (price * 100)) || price == 0) {
      printf("\n您的输入格式错误, 请检查后重新输入:\n");
      printf("请输入折扣价格: \n");
      continue;
    } else if (strlen(price_str) > 8 || atof(price_str) > 50000) {
      printf("\n折扣价不得超过50000, 请检查后重新输入!\n");
      printf("请输入折扣价格: \n");
      continue;
    }
    break;
  } while (1);

  return price;
}

// 检查时间
int *check_time() {
  int i, j, k;
  static int temp_time[6];

  int time_temp = 0;
  do {
    printf("年份: ");
    char time_str[10];
    scanf("%s", time_str);

    i = 0;
    k = 0; // 检测是否出现非数字字符
    for (i = 0; time_str[i] != '\0'; i++) {
      j = isdigit(time_str[i]);
      if (!j) {
        k = k + 1;
        printf("\n您的输入格式错误, 请检查后重新输入: \n");
        break;
      }
    }

    if (k == 1)
      continue;

    time_temp = atoi(time_str);
    if (time_temp < 1000 || time_temp > 9999) {
      printf("\n您的输入格式错误, 请检查后重新输入:\n");
      continue;
    }
    break;
  } while (1);

  temp_time[1] = time_temp;

  time_temp = 0;
  do {
    printf("月份: ");
    char time_str[10];
    scanf("%s", time_str);

    i = 0;
    k = 0; // 检测是否出现非数字字符
    for (i = 0; time_str[i] != '\0'; i++) {
      j = isdigit(time_str[i]);
      if (!j) {
        k = k + 1;
        printf("\n您的输入格式错误, 请检查后重新输入:\n");
        break;
      }
    }

    if (k == 1)
      continue;

    time_temp = atoi(time_str);
    if (time_temp < 1 || time_temp > 12) {
      printf("\n您的输入格式错误, 请检查后重新输入:\n");
      continue;
    }
    break;
  } while (1);

  temp_time[2] = time_temp;

  time_temp = 0;
  do {

    printf("日期: ");
    char time_str[10];
    scanf("%s", time_str);

    i = 0;
    k = 0; // 检测是否出现非数字字符
    for (i = 0; time_str[i] != '\0'; i++) {
      j = isdigit(time_str[i]);
      if (!j) {
        k = k + 1;
        printf("\n您的输入格式错误, 请检查后重新输入:\n");
        break;
      }
    }

    if (k == 1)
      continue;

    time_temp = atoi(time_str);
    if (time_temp < 1 || time_temp > 31) {
      printf("\n您的输入格式错误, 请检查后重新输入:\n");
      continue;
    }
    break;
  } while (1);

  temp_time[3] = time_temp;

  time_temp = 0;
  do {
    printf("小时: ");
    char time_str[10];
    scanf("%s", time_str);

    i = 0;
    k = 0; // 检测是否出现非数字字符
    for (i = 0; time_str[i] != '\0'; i++) {
      j = isdigit(time_str[i]);
      if (!j) {
        k = k + 1;
        printf("\n您的输入格式错误, 请检查后重新输入:\n");
        break;
      }
    }

    if (k == 1)
      continue;

    time_temp = atoi(time_str);
    if (time_temp < 0 || time_temp > 24) {
      printf("\n您的输入格式错误, 请检查后重新输入:\n");
      continue;
    }
    break;
  } while (1);

  temp_time[4] = time_temp;

  time_temp = 0;
  do {
    printf("分钟: ");
    char time_str[10];
    scanf("%s", time_str);

    i = 0;
    k = 0; // 检测是否出现非数字字符
    for (i = 0; time_str[i] != '\0'; i++) {
      j = isdigit(time_str[i]);
      if (!j) {
        k = k + 1;
        printf("\n您的输入格式错误, 请检查后重新输入:\n");
        break;
      }
    }

    if (k == 1)
      continue;

    time_temp = atoi(time_str);
    if (time_temp < 0 || time_temp > 60) {
      printf("\n您的输入格式错误, 请检查后重新输入:\n");
      continue;
    }
    break;
  } while (1);

  temp_time[5] = time_temp;

  return temp_time;
}
/************************************************/

int add_goods_choose_2() {

  char choose[10]; // 记录管理员操作时的选择
  int choose_num;

  // 用户界面
  printf("\n---------------操作选项---------------\n\n");
  printf("1. 确认发布.\n2. 修改信息.\n3. 取消发布.\n");
  printf("\n-------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");

  scanf("%s", choose);

  // 容错判断
  if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0) {
    printf("\n您的输入有误, 请按照操作选项再次输入:\n\n");
    choose_num = add_goods_choose_2();
  } else
    choose_num = atoi(choose);
  return choose_num;
}

int add_goods_choose() {

  char choose[10]; // 记录管理员操作时的选择
  int choose_num;

  // 用户界面
  printf("\n---------------操作选项---------------\n\n");
  printf("1. 确认发布.\n2. 修改信息.\n3. 取消发布.\n");
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

  // 输入信息并进行检查

  printf("请依次输入商品信息: \n");

  // 读取商店ID
  database_admin_information(user_id, 0);
  char temp_shop_id[30];
  strcpy(temp_shop_id, admin_information.shop_id);

  // 输入商品ID并检查
  printf("请输入商品ID(2位大写字母+4位数字): \n");
  char temp_goods_id[30];
  char goods_id[30];
  strcpy(goods_id, check_goods_name(temp_goods_id));

  char temp_goods_name[30];
  char goods_name[30];
  printf("请输入商品名: \n");
  scanf("%s", temp_goods_name);
  strcpy(goods_name, temp_goods_name);

  if (!database_name_to_id(goods_name, 0))
    database_name_to_id(goods_name, 1);
  strcpy(name_to_id_goods_id, goods_id);
  database_name_to_id(goods_name, 1);

  // 输入单价并检查
  printf("请输入单价: \n");
  float temp_unit_price = check_unit_price();

  // 输入进价并检查
  printf("请输入进价: \n");
  float temp_in_price = check_in_price();

  // 输入销量，因为是新货， 销量默认为0
  int temp_sales_volume = 0;

  // 输入库存并检查
  printf("请输入库存: \n");
  int temp_goods_in_stock = check_goods_in_stock();

  // 输入折扣价格��检查
  printf("请输入折扣价格: \n");
  float temp_discount_price = check_discount_price();

  int *point; // 接收返回指针
  int i;      // 循环变量

  // 输入折扣开始时间并检查
  printf("请输入折扣开始时间: \n");
  point = check_time();
  int temp_time_begin[6];
  for (i = 1; i <= 5; i++)
    temp_time_begin[i] = *(point + i);

  // 输入折扣结束时间并检��
  printf("请输入折扣结束时间: \n");
  point = check_time();
  int temp_time_end[6];
  for (i = 1; i <= 5; i++)
    temp_time_end[i] = *(point + i);

  // 打印
  printf("您要发布的商品信息如下, 请确认:\n");
  printf(
      "超市名       商品名          单价     折扣价   进价      库存   销量  "
      "      折扣开始时间      折扣结束时间\n");
  printf("%6s     %10s %10.2f %10.2f %10.2f    %4d %4d      "
         "%04d:%02d:%02d:%02d:%02d       "
         "%04d:%02d:%02d:%02d:%02d\n",
         temp_shop_id,        //
         temp_goods_name,     //
         temp_unit_price,     //
         temp_discount_price, //
         temp_in_price,       //
         temp_goods_in_stock, //
         temp_sales_volume,   //
         temp_time_begin[1],  //
         temp_time_begin[2],  //
         temp_time_begin[3],  //
         temp_time_begin[4],  //
         temp_time_begin[5],  //
         temp_time_end[1],    //
         temp_time_end[2],    //
         temp_time_end[3],    //
         temp_time_end[4],    //
         temp_time_end[5]     //
  );
  printf("\n请输入任意字符并按回车键以继续...\n");
  char screen[10];
  scanf("%s", screen); // 延长屏幕显示时间

  // 进一步操作
  int choose = add_goods_choose();

  switch (choose) {

  // 选项1: 确认发布
  case 1: {
    int i_shop = 1, i_goods; // 深度测量
    int i;                   // 循环变量

    // 打开或建立新数据库
    if (!database_shop_index(temp_shop_id, 0)) {
      database_shop_index(temp_shop_id, 1);
      i_shop = 0;
    }

    if (i_shop) {
      i = 0;
      while (shop_index[i].unit_price != 0)
        i++;
      i_shop = i;
    }

    strcpy(shop_index[i_shop].goods_name, temp_goods_name);     // 商品名
    shop_index[i_shop].unit_price = temp_unit_price;            // 零售价格
    shop_index[i_shop].in_price = temp_in_price;                // 进货价格
    shop_index[i_shop].sales_volume = temp_sales_volume;        // 销量
    shop_index[i_shop].goods_in_stock = temp_goods_in_stock;    // 存货
    shop_index[i_shop].discount_price = temp_discount_price;    // 折扣价
    shop_index[i_shop].time_begin.tm_year = temp_time_begin[1]; // 开始时间
    shop_index[i_shop].time_begin.tm_mon = temp_time_begin[2];  // ...
    shop_index[i_shop].time_begin.tm_mday = temp_time_begin[3]; // ...
    shop_index[i_shop].time_begin.tm_hour = temp_time_begin[4]; // ...
    shop_index[i_shop].time_begin.tm_min = temp_time_begin[5];  // ...
    shop_index[i_shop].time_end.tm_year = temp_time_end[1];     // 结束时间
    shop_index[i_shop].time_end.tm_mon = temp_time_end[2];      // ...
    shop_index[i_shop].time_end.tm_mday = temp_time_end[3];     // ...
    shop_index[i_shop].time_end.tm_hour = temp_time_end[4];     // ...
    shop_index[i_shop].time_end.tm_min = temp_time_end[5];      // ...

    database_shop_index(temp_shop_id, 1);

    // 打开或建立新数据库
    if (!database_goods_index(temp_goods_name, 0)) {
      // 清���结构体
      for (i = 0; i < 100; i++) {
        strcpy(goods_index[i].shop_id, "");    // 超市ID
        goods_index[i].unit_price = 0;         // 单价
        goods_index[i].in_price = 0;           // 进价
        goods_index[i].sales_volume = 0;       // 销量
        goods_index[i].goods_in_stock = 0;     // 库存
        goods_index[i].discount_price = 0;     // 折扣价格
        goods_index[i].time_begin.tm_year = 0; // 折扣开始时间
        goods_index[i].time_begin.tm_mon = 0;  // ...
        goods_index[i].time_begin.tm_mday = 0; // ...
        goods_index[i].time_begin.tm_hour = 0; // ...
        goods_index[i].time_begin.tm_min = 0;  // ...
        goods_index[i].time_end.tm_year = 0;   // 折扣结束时间
        goods_index[i].time_end.tm_mon = 0;    // ...
        goods_index[i].time_end.tm_mday = 0;   // ...
        goods_index[i].time_end.tm_hour = 0;   // ...
        goods_index[i].time_end.tm_min = 0;    // ...}
      }
      database_goods_index(temp_goods_name, 1);
    }

    i = 0;
    while (goods_index[i].unit_price != 0)
      i++;
    i_goods = i;

    strcpy(goods_index[i_goods].shop_id, temp_shop_id);        // 超市编号
    goods_index[i_goods].unit_price = temp_unit_price;         // 零售价格
    goods_index[i_goods].in_price = temp_in_price;             // 进货价格
    goods_index[i_goods].sales_volume = temp_sales_volume;     // 销量
    goods_index[i_goods].goods_in_stock = temp_goods_in_stock; // 存货
    goods_index[i_goods].discount_price = temp_discount_price; // 折扣价
    goods_index[i_goods].time_begin.tm_year = temp_time_begin[1]; // 开始���间
    goods_index[i_goods].time_begin.tm_mon = temp_time_begin[2];  // ...
    goods_index[i_goods].time_begin.tm_mday = temp_time_begin[3]; // ...
    goods_index[i_goods].time_begin.tm_hour = temp_time_begin[4]; // ...
    goods_index[i_goods].time_begin.tm_min = temp_time_begin[5];  // ...
    goods_index[i_goods].time_end.tm_year = temp_time_end[1]; // 结束时间
    goods_index[i_goods].time_end.tm_mon = temp_time_end[2];  // ...
    goods_index[i_goods].time_end.tm_mday = temp_time_end[3]; // ...
    goods_index[i_goods].time_end.tm_hour = temp_time_end[4]; // ...
    goods_index[i_goods].time_end.tm_min = temp_time_end[5];  // ...

    database_goods_index(temp_goods_name, 1);

    database_all_index(1, temp_goods_name, temp_shop_id);

    break;
  }

  // 选项2: 修改信息(已完成)
  case 2: {
    int choose_2 = add_goods_choose_2();

    break;
  }

  // 选项3: 取消发布
  case 3: {
    break;
  }

    return;
  }
}

// 主程序, 负责读取数据库以及传入下一层.
int add_goods_main(char user_id[30]) {

  add_goods(user_id);

  return 1; // 程序运行成功返回"1"
}
