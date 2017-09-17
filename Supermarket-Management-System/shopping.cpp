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
  Native:
    - stdio.h
    - string.h
    - stdlib.h
Input:

Output:

************************************************/

#include "database.h"
#include "shopping.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shopping(char id[10], char market[10], int num) {
  int i = 0;

  if (!database_goods_index(id, 0))
    return 0;

  do {
    if (strcmp(market, goods_index[i].shop_id) == 0)
      break;
    else
      i++;
  } while (goods_index[i].in_price != 0);

  if (num > goods_index[i].goods_in_stock) {
    return 0;
  } else {
    return 1;
  }
}
