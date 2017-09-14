#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() // 调试
{
  char user_id[30] = "guanli";

  if (database_order_admin_goods(user_id, 0)) {
    printf("文件存在并读取完毕\n");
  } else {
    printf("文件不存在\n");
  }

  printf("%s\n", order_admin_goods[0].goods_id);

  strcat(order_admin_goods[0].goods_id, "com");

  printf("%s\n", order_admin_goods[0].goods_id);
  database_order_admin_goods(user_id, 1);

  return 0;
}
