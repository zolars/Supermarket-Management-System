// Name: main.cpp
// Author: 辛逸飞
// Date: 2017-09-12
// Language: C
// Features: 网上超市管理系统主程序.
// Modules:
//   - search_order.h
//   - stdio.h
//   - string.h
//   - stdlib.h

#include "search_order.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int user_type;
  char user_id[30] = "guanli";
  user_type = 1;

  int test = search_order(user_id, user_type);
  if (test)
    printf("All done");

  return 0;
}
