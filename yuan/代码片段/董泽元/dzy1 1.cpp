#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char market[11]; // 顾客选择的超市
  char id[11];     // 顾客选择的商品
  int num;         // 顾客购买的数量

} STU_temp_choise;

STU_temp_choise temp_choise;

/*
void search_market_goods() // 根据超市名称进行查询
{
  int num_purchase;          // 顾客购买的物品序号
  int goods_purchace_number; // 顾客购买的物品数量
  char search_id_market[5];  // 顾客搜索的超市ID

  while (1) {
    printf("\n------------------------------\n");

    printf("请输入您所要查询的超市名称(四位大写字母):");

    while (1) //查询输入的超市编号是否合法
    {
      scanf("%s", search_id_market);
      if (search_id_market[0] <= 'Z' && search_id_market[0] >= 'A' &&
          search_id_market[1] <= 'Z' && search_id_market[1] >= 'A' &&
          search_id_market[2] <= 'Z' && search_id_market[2] >= 'A' &&
          search_id_market[3] <= 'Z' && search_id_market[3] >= 'A' &&
          search_id_market[4] == '\0')
        break;
      else
        printf("\n请重新输入:");
    }
    int i,
        searched_result_num =
            database_shop_index(search_id_market); // 在屏幕上打印超市货物信息
    if (searched_result_num < 0) {
      printf("抱歉, 没有该店铺, 请重新搜索.\n");
      return;
    }

    for (i = 0; i < searched_result_num - 1; i++)
      printf("%d %s %0.2f %0.2f %d %d %0.2f %s %s\n", i + 1,
             shop_index[i].goods_id,            // 商品编号
             shop_index[i].unit_price,          // 零售价格
             shop_index[i].in_price,            // 进货价格
             shop_index[i].sales_volume,        // 销量
             shop_index[i].goods_in_stock,      // 存货
             shop_index[i].discount_price,      // 折扣价
             shop_index[i].discount_begin_time, // 折扣开始时间
             shop_index[i].discount_end_time    // 折扣结束时间"
      );

    printf("请选择您想购买的商品（按0返回）");
    scanf("%d", &num_purchase);

    if (num_purchase != 0) {
      printf("请输入购买件数");
      scanf("%d", &goods_purchace_number);
      temp_choise.num = goods_purchace_number;
      break;
    }
  }
  int j;
  for (j = 0; j <= 5; j++)
    temp_choise.id[j] = shop_index[num_purchase - 1].goods_id[j];
  for (j = 0; j <= 3; j++)
    temp_choise.market[j] = search_id_market[j];
}
*/

//
void search_market_result_0(int choise_num) {
  char num_purchase[11],  // 顾客购买的物品序号
      goods_purchase[11]; // 顾客购买的物品数量
  int num_purchase_num,   // 用于将顾客购买的字符串变为数字
      goods_purchase_number, // 用于将顾客购买的物品数量字符串转化为数字
      i = 0,                 // 循环变量，用于检验顾客输入
      j = 0,                 // 循环变量 用于储存购买结果
      k = 1;                 // 检验开关

  do {
    printf("\n请选择您想购买的商品(按0返回)\n");
    scanf("%s", &num_purchase);

    // 检验输入是否正确
    if (strcmp(num_purchase, "0") == 0)
      return;

    while (i <= 11) {
      if (num_purchase[i] >= '0' && num_purchase[i] <= '9')
        i++;
      else {
        printf("\n您的输入有误，请重新输入\n");
        continue;
      }
      num_purchase_num = atoi(num_purchase);

      if (num_purchase_num > choise_num)
        continue;
    }
    k = 0;
  } while (k);

  i = 0;
  j = 0;
  k = 1;

  do {
    printf("\n请输入您想购买的商品件数(按0返回)\n");
    scanf("%s", &goods_purchase);

    // 检验输入是否正确
    if (strcmp(goods_purchase, "0") == 0) {
      search_market_result_0();
      return;
    }

    while (i <= 11) {
      if (goods_purchase[i] >= '0' && goods_purchase[i] <= '9')
        i++;
      else {
        printf("\n您的输入有误，请重新输入\n");

        continue;
      }
    }
    k = 0;
  } while (k);

  num_purchase_num = atoi(num_purchase);

  i = 0; // 遍历组件
  while (shopping_cart[i].purchase_num != 0) {
    i++;
  }
  /*
    shopping_cart[i].goods_id =         // 商品ID
    shopping_cart[i].admin_id =     // 管理员ID
    shopping_cart[i].purchase_num = // 购买数量
  */
}

// 筛选打折的商品
void search_market_result_1() {
  int i = 0; //循环变量
  while (shop_index[i].unit_price != 0) {
    if (shop_index[i].goods_id !=
        shop_index[i].discount_price) //打折后商品价格与原价格不等
      printf("\n%s %0.2f %0.2f %d %d %0.2f %d:%d:%d:%d:%d %d:%d:%d:%d:%d\n",
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

  int choise_num = i;
  search_market_result_0(choise_num);
  return;
}

int search_market_choose() {
  char choose[10] ； // 记录顾客操作选项
      int choose_num;

  // 用户界面
  printf("\n---------------操作选项---------------\n\n");
  printf("1.隐藏不打折的商品\n");
  printf("2.显示全部相关商品\n");
  printf("3.按销量排序\n");
  printf("4.按价格排序\n");
  printf("5.返回\n");
  printf("\n-------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");

  scanf("%s", choose);
  if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
      strcmp(choose, "3") != 0 && strcmp(choose, "4") != 0 &&
      strcmp(choose, "5") != 0) {
    printf("\n您的输入有误, 请按照操作选项再次输入:\n\n");
    choose_num = search_market_choose();
  } else
    choose_num = atoi(choose);
  return choose_num;
}

// search_market所使用的选择函数
void search_market() {
  int choose = search_market_choose();

  switch (choose) {
  case 1: {
    search_market_result_1();
    search_market();
    break;
  }
  case 2: {
    printf("\n"); // 仍然显示当前商品
    break;
  }
  case 3: {
    printf("3"); // it`s your showtime
    break;
  }
  case 4: {
    printf("4"); // it`s your showtime
    break;
  }
  case 5: {
    break;
  }
  }

  return;
}

//根据超市名称进行查询
void search_market_begin() {

  if (!database_shopping_cart(user_id, 0)) { // 数据库读取, 只读
    database_shopping_cart(user_id, 1);
  }

  char search_id_market[5]; // 顾客搜索的超市ID

  // 用户界面
  printf("请输入您所要查询的超市名称(四位大写字母):");

  while (1) //查询输入的超市编号是否合法
  {
    scanf("%s", search_id_market);
    if (search_id_market[0] <= 'Z' && search_id_market[0] >= 'A' &&
        search_id_market[1] <= 'Z' && search_id_market[1] >= 'A' &&
        search_id_market[2] <= 'Z' && search_id_market[2] >= 'A' &&
        search_id_market[3] <= 'Z' && search_id_market[3] >= 'A' &&
        search_id_market[4] == '\0')
      break;
    else
      printf("\n请重新输入:");
  }

  // 检查是否存在该超市

  int i = 0, searched_result_num;
  searched_result_num = database_shop_index(search_id_market, 0);
  if (searched_result_num != 1) {
    printf("抱歉, 没有该店铺, 请重新搜索.\n");
    return;
  }

  while (shop_index[i].unit_price != 0) {
    printf("%s %0.2f %0.2f %d %d %0.2f %d:%d:%d:%d:%d %d:%d:%d:%d:%d\n",
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
  search_market();

  database_shopping_cart(user_id, 1);
  return;
}
