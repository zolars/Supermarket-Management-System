/************************************************

Name:
  search_for_goods.cpp
Author:
  董泽元
Date:
  2017-09-15
Language:
  C
Features:

************************************************/

#include "database.h"
#include "search_for_goods.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char temp_information_market[100][5];
char temp_information_item[7];

// 对结构体排序时, 需要使用结构体的重构来实现
int cmp_sales_volume_goods(const void *a, const void *b) {
  // 注意这里, 这里的"<"标记, 可以更改快速排序结果是升序/降序
  return (*(STU_goods_index *)a).sales_volume >
                 (*(STU_goods_index *)b).sales_volume
             ? -1
             : 1;
}

int cmp_discount_price_goods(const void *a, const void *b) {
  return (*(STU_goods_index *)a).discount_price >
                 (*(STU_goods_index *)b).discount_price
             ? -1
             : 1;
}

void search_goods_result_0(int choise_num) {

  char num_purchase[11],  // 顾客购买的超市编号
      goods_purchase[11]; // 顾客购买的物品数量
  int num_purchase_num,   // 用于将顾客购买的字符串变为数字
      goods_purchase_num, // 用于将顾客购买的物品数量字符串转化为数字
      i = 0,              // 循环变量
      k = 0;

  do {
    printf("\n请选择您想购买的商品(按0返回)\n");
    scanf("%s", num_purchase);

    // 检验输入是否正确
    if (strcmp(num_purchase, "0") == 0)
      return;

    i = 0;
    k = 0;
    while (num_purchase[i] != '\0') {
      if (num_purchase[i] >= '0' && num_purchase[i] <= '9')
        i++;
      else {
        printf("\n您的输入有误，请重新输入\n");
        k = 1;
        break;
      }
    }

    if (k)
      continue;

    num_purchase_num = atoi(num_purchase);

    if (num_purchase_num > choise_num) {
      printf("\n您的输入有误，请重新输入\n");
      continue;
    } else
      break;
  } while (1);

  i = 0;
  k = 0;
  do {
    printf("\n请选择您购买商品的件数(按0返回)\n");
    scanf("%s", goods_purchase);

    if (strcmp(goods_purchase, "0") == 0) {
      printf("%s", goods_purchase);
      return;
    }

    i = 0;
    k = 0;
    while (goods_purchase[i] != '\0') {
      // 检验输入是否正确
      if (goods_purchase[i] >= '0' && goods_purchase[i] <= '9') {
        i++;
      } else {
        printf("\n您的输入有误，请重新输入\n");
        k = 1;
        break;
      }
    }
    if (k)
      continue;
    else {
      break;
    }

  } while (1);

  goods_purchase_num = atoi(goods_purchase);

  i = 0;
  while (shopping_cart[i].purchase_num != 0) {
    i++;
  }

  printf("您的订单为:\n商品编号: %s\n超市编号: %s\n购买数量: %d\n",
         temp_information_item, temp_information_market[num_purchase_num - 1],
         goods_purchase_num);

  printf("\n请输入任意字符并按回车键以继续...\n");
  char screen[10];
  scanf("%s", screen); // 延长屏幕显示时间

  /*

  立即购买

  加入购物车

  */

  strcpy(shopping_cart[i].goods_id,
         temp_information_item); // 商品ID
  strcpy(shopping_cart[i].shop_id,
         temp_information_market[num_purchase_num - 1]); // 商店ID
  shopping_cart[i].purchase_num = goods_purchase_num;    // 购买数量
  return;
}

// 筛选打折的商品
void search_goods_result_1() {
  int i = 0, j = 0; //循环变量
  while (goods_index[i].unit_price != 0) {
    if (fabs(goods_index[i].unit_price - goods_index[i].discount_price) >
        0.000001) //打折后商品价格与原价格不等
    {
      printf("%d %s %10.2f %d %d %10.2f %d:%d:%d:%d:%d %d:%d:%d:%d:%d\n",
             j + 1,                             // 列表序号
             goods_index[i].shop_id,            // 商品编号
             goods_index[i].unit_price,         // 零售价格
             goods_index[i].sales_volume,       // 销量
             goods_index[i].goods_in_stock,     // 存货
             goods_index[i].discount_price,     // 折扣���
             goods_index[i].time_begin.tm_year, // 折扣开始时间
             goods_index[i].time_begin.tm_mon,  // ...
             goods_index[i].time_begin.tm_mday, // ...
             goods_index[i].time_begin.tm_hour, // ...
             goods_index[i].time_begin.tm_min,  // ...
             goods_index[i].time_end.tm_year,   // 折扣结束时间
             goods_index[i].time_end.tm_mon,    // ...
             goods_index[i].time_end.tm_mday,   // ...
             goods_index[i].time_end.tm_hour,   // ...
             goods_index[i].time_end.tm_min     // ...
      );
      strcpy(temp_information_market[j], goods_index[i].shop_id);
      j++;
    }
    i++;
  }
  temp_information_market[j][0] = '\0';

  int choise_num = j;
  search_goods_result_0(choise_num);
  return;
}

// 打印不打折的商品
void search_goods_result_2() {
  int i = 0; //循环变量
  while (goods_index[i].unit_price != 0) {

    printf("%d %s %10.2f %d %d %10.2f %d:%d:%d:%d:%d %d:%d:%d:%d:%d\n",
           i + 1,                             // 列表序号
           goods_index[i].shop_id,            // 商品编号
           goods_index[i].unit_price,         // 零售价格
           goods_index[i].sales_volume,       // 销量
           goods_index[i].goods_in_stock,     // 存货
           goods_index[i].discount_price,     // 折扣价
           goods_index[i].time_begin.tm_year, // 折扣开始时间
           goods_index[i].time_begin.tm_mon,  // ...
           goods_index[i].time_begin.tm_mday, // ...
           goods_index[i].time_begin.tm_hour, // ...
           goods_index[i].time_begin.tm_min,  // ...
           goods_index[i].time_end.tm_year,   // 折扣结束时间
           goods_index[i].time_end.tm_mon,    // ...
           goods_index[i].time_end.tm_mday,   // ...
           goods_index[i].time_end.tm_hour,   // ...
           goods_index[i].time_end.tm_min     // ...
    );
    strcpy(temp_information_market[i], goods_index[i].shop_id);

    i++;
  }
  temp_information_market[i][0] = '\0';

  int choise_num = i;
  search_goods_result_0(choise_num);
  return;
}

void search_goods_result_3() {
  int i = 0; //循环变量

  // 深度探测
  while (goods_index[i].unit_price != 0) {
    i++;
  }

  // 针对销量进行排序
  qsort(goods_index, i, sizeof(goods_index[0]), cmp_sales_volume_goods);

  i = 0;
  while (goods_index[i].unit_price != 0) {
    printf("%d %s %10.2f %d %d %10.2f %d:%d:%d:%d:%d %d:%d:%d:%d:%d\n",
           i + 1,                             // 列表序号
           goods_index[i].shop_id,            // 商品编号
           goods_index[i].unit_price,         // 零售价格
           goods_index[i].sales_volume,       // 销量
           goods_index[i].goods_in_stock,     // 存货
           goods_index[i].discount_price,     // 折扣价
           goods_index[i].time_begin.tm_year, // 折扣开始时间
           goods_index[i].time_begin.tm_mon,  // ...
           goods_index[i].time_begin.tm_mday, // ...
           goods_index[i].time_begin.tm_hour, // ...
           goods_index[i].time_begin.tm_min,  // ...
           goods_index[i].time_end.tm_year,   // 折扣结束时间
           goods_index[i].time_end.tm_mon,    // ...
           goods_index[i].time_end.tm_mday,   // ...
           goods_index[i].time_end.tm_hour,   // ...
           goods_index[i].time_end.tm_min     // ...
    );
    strcpy(temp_information_market[i], goods_index[i].shop_id);

    i++;
  }
  temp_information_market[i][0] = '\0';

  int choise_num = i;
  search_goods_result_0(choise_num);
  return;
}

void search_goods_result_4() {
  int i = 0; //循环变量

  // 深度探测
  while (goods_index[i].unit_price != 0) {
    i++;
  }

  // 针对销量进行排序
  qsort(goods_index, i, sizeof(goods_index[0]), cmp_discount_price_goods);

  i = 0;
  while (goods_index[i].unit_price != 0) {
    printf("%d %s %10.2f %d %d %10.2f %d:%d:%d:%d:%d %d:%d:%d:%d:%d\n",
           i + 1,                         // 列表序号
           goods_index[i].shop_id,        // 商品编��
           goods_index[i].unit_price,     // ���售�������
           goods_index[i].sales_volume,   // 销量
           goods_index[i].goods_in_stock, // 存货
           goods_index[i].discount_price, // 折扣价
           goods_index[i].time_begin.tm_year, // 折扣开始时间
           goods_index[i].time_begin.tm_mon,  // ...
           goods_index[i].time_begin.tm_mday, // ...
           goods_index[i].time_begin.tm_hour, // ...
           goods_index[i].time_begin.tm_min,  // ...
           goods_index[i].time_end.tm_year,   // 折扣结束时间
           goods_index[i].time_end.tm_mon,    // ...
           goods_index[i].time_end.tm_mday,   // ...
           goods_index[i].time_end.tm_hour,   // ...
           goods_index[i].time_end.tm_min     // ...
    );
    strcpy(temp_information_market[i], goods_index[i].shop_id);

    i++;
  }
  temp_information_market[i][0] = '\0';

  int choise_num = i;
  search_goods_result_0(choise_num);
  return;
}

int search_goods_choose() {
  char choose[10]; // 记录顾客操作��项
  int choose_num;

  // 用户界面
  printf("\n---------------操作选项---------------\n\n");
  printf("1. 隐藏不打折的商品.\n");
  printf("2. 显示全部相关商品.\n");
  printf("3. 按超市销量排序.\n");
  printf("4. 按打折后价格排序.\n");
  printf("0. 返回\n");
  printf("\n-------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");

  scanf("%s", choose);
  if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
      strcmp(choose, "3") != 0 && strcmp(choose, "4") != 0 &&
      strcmp(choose, "0") != 0) {
    printf("\n您的输入有误, 请按照操作选项再次输入:\n\n");
    choose_num = search_goods_choose();
  } else
    choose_num = atoi(choose);
  return choose_num;
}

// search_goods所使用的选择函数
void search_goods() {
  int choose = search_goods_choose();

  switch (choose) {
  case 1: {
    search_goods_result_1();
    search_goods();
    break;
  }
  case 2: {
    search_goods_result_2();
    search_goods();
    break;
  }
  case 3: {
    search_goods_result_3();
    search_goods();
    break;
  }
  case 4: {
    search_goods_result_4();
    search_goods();
    break;
  }
  case 5: {
    break;
  }
  }

  return;
}

//根据超市名称进行查询
void search_goods_begin(char user_id[30]) {

  if (!database_shopping_cart(user_id, 0)) { // 数据库读取, 只读
    database_shopping_cart(user_id, 1);
  }

  char search_id_goods[10]; // 顾客搜索的商品ID

  // 用户界面
  printf("请输入您所要查询的商品名称(两位大写字母+四位数字):");

  while (1) //查询输入的超市编号是否合法
  {
    scanf("%s", search_id_goods);
    if (search_id_goods[0] <= 'Z' && search_id_goods[0] >= 'A' &&
        search_id_goods[1] <= 'Z' && search_id_goods[1] >= 'A' &&
        search_id_goods[2] <= '9' && search_id_goods[2] >= '0' &&
        search_id_goods[3] <= '9' && search_id_goods[3] >= '0' &&
        search_id_goods[4] <= '9' && search_id_goods[4] >= '0' &&
        search_id_goods[5] <= '9' && search_id_goods[5] >= '0' &&
        search_id_goods[6] == '\0')
      break;
    else
      printf("\n请重新输入:");
  }

  // 检查是否存在该商品

  int i = 0, searched_result_num;
  searched_result_num = database_goods_index(search_id_goods, 0);
  if (searched_result_num != 1) {
    printf("抱歉, 没有该商品, 请搜索其他信息.\n");
    return;
  }
  strcpy(temp_information_item, search_id_goods);

  printf("您的查询结果如下:\n");

  while (goods_index[i].unit_price != 0) {
    printf("%d. %s %10.2f %d %d %10.2f %d:%d:%d:%d:%d %d:%d:%d:%d:%d\n",
           i + 1,                             // 列表序号
           goods_index[i].shop_id,            // 超市编号
           goods_index[i].unit_price,         // 零售价格
           goods_index[i].sales_volume,       // 销量
           goods_index[i].goods_in_stock,     // 存货
           goods_index[i].discount_price,     // 折扣价
           goods_index[i].time_begin.tm_year, // 折扣开始时间
           goods_index[i].time_begin.tm_mon,  // ...
           goods_index[i].time_begin.tm_mday, // ...
           goods_index[i].time_begin.tm_hour, // ...
           goods_index[i].time_begin.tm_min,  // ...
           goods_index[i].time_end.tm_year,   // 折扣结束时间
           goods_index[i].time_end.tm_mon,    // ...
           goods_index[i].time_end.tm_mday,   // ...
           goods_index[i].time_end.tm_hour,   // ...
           goods_index[i].time_end.tm_min     // ...
    );
    i++;
  }

  printf("\n请输入任意字符并按回车键以继续...\n");
  char screen[10];
  scanf("%s", screen); // 延长屏幕显示时间

  search_goods();

  database_shopping_cart(user_id, 1);
  return;
}
