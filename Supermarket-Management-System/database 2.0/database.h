// Name: database.h
// Author: 辛逸飞
// Date: 2017-09-13
// Language: C
// Features: 数据库接口: 文件读取, 转存为结构体或写入文件.
// Modules:
//   - stdio.h
//   - stdlib.h
//   - string.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************************************************
标题:
  STU_time 时间存取结构型
*************************************************/
typedef struct {
  int year;
  int month;
  int day;
  int hour;
  int minute;
} STU_time;

/*************************************************
标题:
  admin_information数据库 管理员信息 可读写

路径:
  ./database/admin_information/

文件名:
  {admin_id}.txt

数据:
  1行4列
  超市名 | 管理员姓名 | 邮箱 | 密码

接收:
  user_id 用户ID
  read_type: 读写类型
    0: 读取
    1: 写入

返回:
  0: 文件不存在
  1: 成功读写数据
*************************************************/

typedef struct {
  char shop_id[10];  // 超市名
  char name[10];     // 管理员姓名
  char email[30];    // 邮箱
  char password[30]; // 密码
} STU_admin_information;

STU_admin_information admin_information;

int database_admin_information(char user_id[10], int read_type) {

  FILE *fwrite; // 声明读取文件所需指针
  char file_name[300] =
      "/Users/zolar/OneDrive - Queen Mary, University of "
      "London/Project/Supermarket-Management-System/"
      "Supermarket-Management-System/database/"; // 该字符串用于处理文件名

  strcat(file_name, "admin_information/"); // 加入路径"order_consumer/"
  strcat(file_name, user_id);              // 文件名为"user_id"
  strcat(file_name, ".txt");               // 后缀为.txt

  // 打开特定的订单数据文件
  if ((fwrite = fopen(file_name, "r+")) == NULL) // 判断文件是否存在及可读
    return 0;                                    // 不存在, 返回"0"

  if (!read_type) {
    // 读取数据
    fscanf(fwrite, "%s %s %s %s",
           admin_information.shop_id, // 超市名
           admin_information.name,    // 管理员姓名
           admin_information.email,   // 邮箱
           admin_information.password // 密码
    );

  } else {
    // 写入数据
    fprintf(fwrite, "%s %s %s %s",
            admin_information.shop_id, // 超市名
            admin_information.name,    // 管理员姓名
            admin_information.email,   // 邮箱
            admin_information.password // 密码
    );
  }

  fclose(fwrite);
  return 1; // 成功读写返回"1"
}

/*************************************************
标题:
  consumer_information数据库 顾客信息 可读写

路径:
  ./database/consumer_information/

文件名:
  {consumer_id}.txt

数据:
  1行7列
  顾客姓名 | 性别(男性 : 1, 女性: 2) | 手机号 | 密码 | 邮箱 | 地址 | 余额

接收:
  user_id 用户ID
  read_type: 读写类型
    0: 读取
    1: 写入

返回:
  0: 文件不存在
  1: 成功读写数据
*************************************************/

typedef struct {
  char name[10];     // 顾客姓名
  char sex[10];      // 顾客性别
  char tel[20];      // 手机号
  char password[30]; // 密码
  char email[30];    // 邮箱
  char address[50];  // 地址
  float money;       // 余额
} STU_consumer_information;

STU_consumer_information consumer_information;

int database_consumer_information(char user_id[10], int read_type) {

  FILE *fwrite; // 声明读取文件所需指针
  char file_name[300] =
      "/Users/zolar/OneDrive - Queen Mary, University of "
      "London/Project/Supermarket-Management-System/"
      "Supermarket-Management-System/database/"; // 该字符串用于处理文件名

  strcat(file_name, "consumer_information/"); // 加入路径"order_consumer/"
  strcat(file_name, user_id);                 // 文件名为"user_id"
  strcat(file_name, ".txt");                  // 后缀为.txt

  // 打开特定的订单数据文件
  if ((fwrite = fopen(file_name, "r+")) == NULL) // 判断文件是否存在及可读
    return 0;                                    // 不存在, 返回"0"

  if (!read_type) {
    // 读取数据
    fscanf(fwrite, "%s %s %s %s %s %s %f",
           consumer_information.name,     // 顾客姓名
           consumer_information.sex,      // 顾客性别
           consumer_information.tel,      // 手机号
           consumer_information.password, // 密码
           consumer_information.email,    // 邮箱
           consumer_information.address,  // 地址
           &consumer_information.money    // 余额
    );

  } else {
    // 写入数据
    fprintf(fwrite, "%s %s %s %s %s %s %f",
            consumer_information.name,     // 顾客姓名
            consumer_information.sex,      // 顾客性别
            consumer_information.tel,      // 手机号
            consumer_information.password, // 密码
            consumer_information.email,    // 邮箱
            consumer_information.address,  // 地址
            consumer_information.money     // 余额
    );
  }

  fclose(fwrite);
  return 1; // 成功读写返回"1"
}

/*************************************************
标题:
  goods_index数据库 按商品种类索引的商品清单 可读写

路径
  ./database/goods_index/

文件名
  {goods_id}.txt

存放数据
  n行8列
  超市ID | 单价 | 进价 | 销量 | 库存 | 折扣价格 | 折扣开始时间 |折扣结束时间

接收:
  goods_id: 商品种类
  list_num: 读写类型 & 结构体数组长度
    -1: 读取
    整形数: 写入

返回:
  0: 文件不存在
  list_num: 返回结构体数组长度
*************************************************/

typedef struct {
  char shop_id[10];       // 超市ID
  float unit_price;       // 单价
  float in_price;         // 进价
  int sales_volume;       // 销量
  int goods_num_in_stock; // 库存
  float discount_price;   // 折扣价格
  STU_time time_begin;    // 折扣开始时间
  STU_time time_end;      //折扣结束时间
} STU_goods_index;

STU_goods_index goods_index[100];

int database_goods_index(char user_id[10], int list_num) {

  FILE *fwrite; // 声明读取文件所需指针
  char file_name[300] =
      "/Users/zolar/OneDrive - Queen Mary, University of "
      "London/Project/Supermarket-Management-System/"
      "Supermarket-Management-System/database/"; // 该字符串用于处理文件名

  strcat(file_name, "goods_index/"); // 加入路径"order_consumer/"
  strcat(file_name, user_id);        // 文件名为"user_id"
  strcat(file_name, ".txt");         // 后缀为.txt

  int i = -1;
  if (list_num == -1) {

    // 打开特定的订单数据文件
    if ((fwrite = fopen(file_name, "r+")) == NULL) // 判断文件是否存在及可读
      return 0;                                    // 不存在, 返回"0"

    // 遍历组件, 读取数据
    while (!feof(fwrite)) {
      // 记得时间
      i++;
      fscanf(fwrite, "%s %f %f %d %d %f %d:%d:%d:%d:%d %d:%d:%d:%d:%d",
             goods_index[i].shop_id,             // 超市ID
             &goods_index[i].unit_price,         // 单价
             &goods_index[i].in_price,           // 进价
             &goods_index[i].sales_volume,       // 销量
             &goods_index[i].goods_num_in_stock, // 库存
             &goods_index[i].discount_price,     // 折扣价格
             &goods_index[i].time_begin.year, &goods_index[i].time_begin.month,
             &goods_index[i].time_begin.day, &goods_index[i].time_begin.hour,
             &goods_index[i].time_begin.minute, &goods_index[i].time_end.year,
             &goods_index[i].time_end.month, &goods_index[i].time_end.day,
             &goods_index[i].time_end.hour, &goods_index[i].time_end.minute);
    }
  } else {

    // 打开特定的订单数据文件
    if ((fwrite = fopen(file_name, "w+")) == NULL) // 判断文件是否存在及可读
      return 0;                                    // 不存在, 返回"0"

    // 写入数据
    i = 0;
    while (goods_index[i].time_begin.year != 0) {
      fprintf(fwrite,
              "%s %0.2f %0.2f %d %d %0.2f %d:%d:%d:%d:%d %d:%d:%d:%d:%d\n",
              goods_index[i].shop_id,            // 超市ID
              goods_index[i].unit_price,         // 单价
              goods_index[i].in_price,           // 进价
              goods_index[i].sales_volume,       // ��量
              goods_index[i].goods_num_in_stock, // 库存
              goods_index[i].discount_price,     // 折扣价格
              goods_index[i].time_begin.year, goods_index[i].time_begin.month,
              goods_index[i].time_begin.day, goods_index[i].time_begin.hour,
              goods_index[i].time_begin.minute, goods_index[i].time_end.year,
              goods_index[i].time_end.month, goods_index[i].time_end.day,
              goods_index[i].time_end.hour, goods_index[i].time_end.minute);
      i++;
    }
  }
  fclose(fwrite);
  return i; // 成功读写返回"1"
}
