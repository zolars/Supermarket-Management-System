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

//根据超市名称进行查询
void search_market() {
  int num_purchase;          // 顾客购买的物品序号
  int goods_purchace_number; // 顾客购买的物品数量
  char search_id_market[5];  // 顾客搜索的超市ID

  // 检查输入是否合法

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

  // 检查是否存在该超市

  int i = 0, searched_result_num;
  searched_result_num = database_shop_index(search_id_market, 0);
  if (searched_result_num != 1) {
    printf("抱歉, 没有该店铺, 请重新搜索.\n");
    return;
  }

  printf("faaaaaaaak");
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
}

int main() {

  search_market();
  return 1;
}
