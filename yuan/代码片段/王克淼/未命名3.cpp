#include "database.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_information() { return; }

void add_goods() {
  int deep_num = 0; // 循环变量
  // 遍历求深度
  do {
    deep_num += 1;
  } while (shop_index[deep_num].unit_price != 0);

  //输入新商品信息
  printf("请依次输入商品信息: \n");
  printf("超市ID: ");
  scanf("%s", goods_index[deep_num].shop_id);
  printf("商品ID: ");
  scanf("%s", shop_index[deep_num].goods_id);
  printf("单价: ");

  do {
    if (scanf("%s", &shop_index[deep_num].unit_price)) {
      goods_index[deep_num].unit_price = shop_index[deep_num].unit_price;
      break;
    } else {
      printf("Gun nmd SB");
      continue;
    }
  } while (1);
  printf("进价: ");
  scanf("%f", &shop_index[deep_num].in_price);
  goods_index[deep_num].in_price = shop_index[deep_num].in_price;
  shop_index[deep_num].sales_volume = 0;
  goods_index[deep_num].sales_volume = 0;
  printf("库存: ");
  scanf("%d", &shop_index[deep_num].goods_in_stock);
  goods_index[deep_num].goods_in_stock = shop_index[deep_num].goods_in_stock;
  printf("折扣价格: ");
  scanf("%f", &shop_index[deep_num].discount_price);
  goods_index[deep_num].discount_price = shop_index[deep_num].discount_price;
  printf("折扣开始时间: ");
  scanf("%d:%d:%d:%d:%d", &shop_index[deep_num].time_begin.year,
        &shop_index[deep_num].time_begin.month,
        &shop_index[deep_num].time_begin.day,
        &shop_index[deep_num].time_begin.hour,
        &shop_index[deep_num].time_begin.minute);
  goods_index[deep_num].time_begin.year = shop_index[deep_num].time_begin.year;
  goods_index[deep_num].time_begin.month =
      shop_index[deep_num].time_begin.month;
  goods_index[deep_num].time_begin.day = shop_index[deep_num].time_begin.day;
  goods_index[deep_num].time_begin.hour = shop_index[deep_num].time_begin.hour;
  goods_index[deep_num].time_begin.minute =
      shop_index[deep_num].time_begin.minute;
  printf("折扣结束时间: ");
  scanf("%d:%d:%d:%d:%d", &shop_index[deep_num].time_end.year,
        &shop_index[deep_num].time_end.month,
        &shop_index[deep_num].time_end.day, &shop_index[deep_num].time_end.hour,
        &shop_index[deep_num].time_end.minute);
  goods_index[deep_num].time_end.year = shop_index[deep_num].time_end.year;
  goods_index[deep_num].time_end.month = shop_index[deep_num].time_end.month;
  goods_index[deep_num].time_end.day = shop_index[deep_num].time_end.day;
  goods_index[deep_num].time_end.hour = shop_index[deep_num].time_end.hour;
  goods_index[deep_num].time_end.minute = shop_index[deep_num].time_end.minute;

  //对输入的信息进行检查
  check_information();
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

  add_goods();

  database_shop_index(user_id, 1);
  database_goods_index(user_id, 1);
  return 1;
}

int main() {
  char user_id[30] = "guanli";
  add_goods_main(user_id);
  return 0;
}
