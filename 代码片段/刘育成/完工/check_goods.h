#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_goods(char id[10], char market[10], int num) {
  int temp;
  int i = 0;
  temp = database_goods_index(id, 0);
  do {
    if (strcmp(market, goods_index[i].shop_id) == 0)
      break;
    else
      i++;
  } while (goods_index[i].in_price != 0);

  printf("%d %s", i, goods_index[i].shop_id);

  if (num > goods_index[i].goods_in_stock) {
    /*  printf("\n抱歉. 库存不足,无法购买. \n");
      printf("请输入任意字符并按回车键以继续...\n");
      char screen;
      scanf("%s", screen); // 延长屏幕显示时间*/
    return 0;
  } else {
    /*printf("购买成功!");*/
    return 1;
  }
}
