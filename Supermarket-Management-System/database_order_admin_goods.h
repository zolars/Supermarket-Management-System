// Name: database.h
// Author: 辛逸飞
// Date: 2017-09-12
// Language: C
// Features: 数据库"order_admin/{user_id}_goods.txt"文件读取, 转存为结构体.
// Modules:
//   - stdio.h
//   - stdlib.h
//   - string.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义结构体存放商品索引数据
typedef struct {
  char goods_id[11]; // 商品编号
  int goods_num;     // 购买数量
  float all_price;   // 营业额
  float profit;      // 利润
} STU_goods;

STU_goods order_goods[100]; // 最多存放一百笔订单

STU_all order_all[100]; // 最多存放一百笔订单

int database_order_all(char user_id[11]) {
  // 声明读取文件所需指针
  FILE *fread;

  char file_name[300] =
      "/Users/zolar/OneDrive - Queen Mary, University of "
      "London/Project/Supermarket-Management-System/"
      "Supermarket-Management-System/"; // 该字符串用于处理文件名

  strcat(file_name, "order_admin/"); // 加入路径"order_admin/"

  // 处理文件名
  strcat(file_name, user_id);
  strcat(file_name, "_all.txt");

  // 打开特定的订单数据文件
  if ((fread = fopen(file_name,
                     "r")) == NULL) // 判断文件是否存在及可读
  {
    printf("You have not sold anything.\n");
    return -1;
  }

  // 遍历组件, 将所有订单信息存入 order_all 结构体
  int i = 0;
  while (!feof(fread)) {

    // 读取数据
    fscanf(fread, "%s %s %s %s %d %f %f",
           order_all[i].order_id,    // 订单编号
           order_all[i].consumer_id, // 顾客编号
           order_all[i].sold_time,   // 购买时间
           order_all[i].goods_id,    // 商品编号
           &order_all[i].goods_num,  // 购买数量
           &order_all[i].unit_price, // 单价
           &order_all[i].all_price); // 总价

    i++;
  }

  fclose(fread);
  return i; // 保存订单数量
}
