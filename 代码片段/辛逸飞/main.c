// Name: main.cpp
// Author: 辛逸飞
// Date: 2017-09-12
// Language: C
// Features: 网上超市管理系统主程序.
// Modules:
//   - database_order_admin_all.h
//   - databse_order_admin_goods.h
//   - stdio.h
//   - string.h
//   - stdlib.h

#include "search_orders_admin.h"
#include "search_orders_consumer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int user_type;
  char user_id[15] = "KMDM007";
  user_type = 0;

  if (user_type)
    search_orders_admin(user_id);
  else
    search_orders_consumer(user_id);
  return 0;
}
