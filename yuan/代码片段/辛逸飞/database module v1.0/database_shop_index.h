// Name: database_shop_index.h
// Author: 辛逸飞
// Date: 2017-09-12
// Language: C
// Features: 数据库"/shop_index/user_id.txt"文件读取,
// 转存为结构体. Modules:
//   - stdio.h
//   - stdlib.h
//   - string.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char goods_id[11];            // 商品编号
  float unit_price;             // 零售价格
  float in_price;               // 进货价格
  int sales_volume;             // 销量
  int goods_in_stock;           // 存货
  float discount_price;         // 折扣价
  char discount_begin_time[25]; // 折扣开始时间
  char discount_end_time[25];   // 折扣结束时间

} STU_shop_index;

STU_shop_index shop_index[100];

int database_shop_index(char user_id[11]) {
  // 声明读取文件所需指针
  FILE *fread;

  char file_name[300] =
      "/Users/zolar/OneDrive - Queen Mary, University of "
      "London/Project/Supermarket-Management-System/"
      "Supermarket-Management-System/database"; // 该字符串用于处理文件名
  strcat(file_name,
         "/shop_index/"); // 加入路径"shop_index/"

  // 处理文件名
  strcat(file_name, user_id);
  strcat(file_name, ".txt");

  // 打开特定的订单数据文件
  if ((fread = fopen(file_name, "r")) == NULL) // 判断文件是否存在及可读
  {
    return -1;
  }

  int i = 0; // 循环变量(注意这里的i一定要定为0)
  while (!feof(fread)) {

    // 读取数据
    fscanf(fread, "%s %f %f %d %d %f %s %s",
           shop_index[i].goods_id,            // 商品编号
           &shop_index[i].unit_price,         // 零售价格
           &shop_index[i].in_price,           // 进货价格
           &shop_index[i].sales_volume,       // 销量
           &shop_index[i].goods_in_stock,     // 存货
           &shop_index[i].discount_price,     // 折扣价
           shop_index[i].discount_begin_time, // 折扣开始时间
           shop_index[i].discount_end_time    // 折扣结束时间
    );
    i++;
  }
  fclose(fread);

  return i; // 保存订单数量
}
