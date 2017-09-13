#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() // 调试
{
  char user_id[10] = "shangpin";

  int list_num = database_goods_index(user_id, -1);
  if (list_num) {
    printf("文件存在并读取完毕\n");
  } else {
    printf("文件不存在\n");
  }

  printf("%d", goods_index[3].time_end.year);
  goods_index[3].time_end.year = goods_index[3].time_end.year * 2 + 1;
  printf("%d", list_num);
  database_goods_index(user_id, list_num - 1);

  return 0;
}
