// Name: database.h
// Author: 辛逸飞
// Date: 2017-09-12
// Language: C
// Features: 数据库文件读取, 转存为结构体.
// Modules:
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
  int goods_in_stock;           //存货
  float discount_price;         // 折扣价
  char discount_begin_time[25]; // 折扣开始时间
  char discount_end_time[25];   // 折扣结束时间

} STU_goods_information;

STU_goods_information goods_information[100];

void database(char user_id[11]) {
  // 声明读取文件所需指针
  FILE *fread;

  char file_name[300] = "";                // 该字符串用于处理文件名
  strcat(file_name, "goods_information/"); // 加入路径"goods_information/"

  // 处理文件名
  strcat(file_name, user_id);
  strcat(file_name, ".txt");

  // 打开特定的订单数据文件
  if ((fread =
           fopen("/Users/zolar/Supermarket-Management-System/goods_information/"
                 "KMDM007.txt",
                 "r")) == NULL) // 判断文件是否存在及可读
  {
    printf("You have not sold anything.\n");
    return;
  }

  int i = 0; // 循环变量(注意这里的i一定要定为0)
  while (!feof(fread)) {

    // 读取数据
    fscanf(fread, "%s %f %f %d %d %f %s %s",
           goods_information[i].goods_id,            // 商品编号
           goods_information[i].unit_price,          // 零售价格
           goods_information[i].in_price,            // 进货价格
           goods_information[i].sales_volume,        // 销量
           goods_information[i].goods_in_stock,      // 存货
           goods_information[i].discount_price,      // 折扣价
           goods_information[i].discount_begin_time, // 折扣开始时间
           goods_information[i].discount_end_time    // 折扣结束时间
    );
    i++;
  }
  fclose(fread);
}
