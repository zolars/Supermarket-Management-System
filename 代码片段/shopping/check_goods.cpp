#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_goods(char id[10], char market[10], int num) {
  int i = 0;
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
