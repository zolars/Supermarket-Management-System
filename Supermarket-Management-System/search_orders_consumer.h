// Name: search_for_orders.h
// Author: 辛逸飞
// Date: 2017-09-12
// Language: C
// Features: 完成"顾客身份-查询订单"功能的模块.
// Modules:
//   - stdio.h
//   - string.h
//   - stdlib.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义结构体存放所有数据
typedef struct {
  char order_id[11];  // 订单编号
  char sold_time[25]; // 购买时间
  char goods_id[11];  // 商品编号
  int goods_num;      // 购买数量
  float unit_price;   // 单价
  float all_price;    // 总价
} STU_consumer;

STU_consumer order_consumer[100]; // 最多存放一百笔订单

int search_orders_consumer(char user_id[15]) {
  // 声明读取文件所需指针
  FILE *fread;

  char file_name[300] = ""; // 该字符串用于处理文件名
  char choose[10];          // 记录管理员操作时的选择

  strcat(file_name, "order_consumer/"); // 加入路径"order_consumer/"
  // 处理文件名
  strcat(file_name, user_id);
  strcat(file_name, ".txt");

  // 打开特定的订单数据文件
  if ((fread = fopen("/Users/zolar/Supermarket-Management-System/"
                     "order_consumer/AB1234.txt",
                     "r")) == NULL) // 判断文件是否存在及可读
  {
    printf("You have not bought anything.\n");
    return 0;
  }

  int i; // 循环变量

  while (!feof(fread)) {

    // 读取数据
    fscanf(fread, "%s %s %s %d %f %f", order_consumer[i].order_id,
           order_consumer[i].sold_time, order_consumer[i].goods_id,
           &order_consumer[i].goods_num, &order_consumer[i].unit_price,
           &order_consumer[i].all_price);

    i++;
  }

  int order_num = i; // 保存订单数量

  // 顾客: 打印数据
  printf("\n");
  for (i = 0; i < order_num - 1; i++)
    printf("%s\t%s\t%s\t%d\t%0.2f\t%0.2f\n", order_consumer[i].order_id,
           order_consumer[i].sold_time, order_consumer[i].goods_id,
           order_consumer[i].goods_num, order_consumer[i].unit_price,
           order_consumer[i].all_price);

  printf("\n以上即为您的历史订单.\n请输入任意字符并按回车键以继续...\n");
  scanf("%s", choose); // 延迟屏幕显示
  fclose(fread);
  return 0;
}
