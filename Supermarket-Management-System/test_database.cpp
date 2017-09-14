#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() // 调试
{
  char user_id[30] = "guke";

  if (database_shopping_cart(user_id, 0)) {
    printf("文件存在并读取完毕\n");
  } else {
    printf("文件不存在\n");
  }

  printf("%d\n", shopping_cart[2].purchase_num);

  shopping_cart[2].purchase_num = -1;
  printf("%d\n", shopping_cart[2].purchase_num);
  database_shopping_cart(user_id, 1);

  return 0;
}
