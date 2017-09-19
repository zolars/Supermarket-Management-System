// Name: database.cpp
// Author: 辛逸飞
// Date: 2017-09-13
// Language: C
// Features: 数据库函数: 文件读取, 转存为结构体或写入文件.
// Modules:
//   - stdio.h
//   - stdlib.h
//   - string.h
// 备注:
//  1. 所有注释均写在 "database.h" 头文件中, 目的是便于隐藏具体数据布局,
//     仅仅暴露使用者需要调用的数据接口以及全局变量名.
//  2. 当我们需要遍历全部的结构体时, 找到结构体中的一个非零变量,
//     使用 while 语句检测其是否为零, 即可判断尽头.
//  3. 在头文件中定义结构体, 会使结构体中的具体数据布局暴露,
//     但我暂时不知道有什么更好的解决方案.

#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*************************************************
*************************************************/

char path[300] = "./database/";

/*************************************************
*************************************************/

STU_admin_information admin_information;

int database_admin_information(char user_id[30], int read_type) {

  FILE *fwrite; // 声明读取文件所需指针
  char file_name[300];

  strcpy(file_name, path); // 该字符串用于处理文件名

  strcat(file_name, "admin_information/"); // 加入路径"admin_information/"
  strcat(file_name, user_id);              // 文件名为"user_id"
  strcat(file_name, ".txt");               // 后缀为.txt

  if (!read_type) {

    // 打开特定的订单数据文件
    if ((fwrite = fopen(file_name, "r")) == NULL) // 判断文件是否存在及可读
      return 0;                                   // 不存在, 返回"0"

    // 读取数据
    fscanf(fwrite, "%s %s %s %s",
           admin_information.shop_id, // 超市名
           admin_information.name,    // 管理员姓名
           admin_information.email,   // 邮箱
           admin_information.password // 密码
    );

  } else {

    // 打开特定的订单数据文件
    fwrite = fopen(file_name, "w+");

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
*************************************************/

STU_consumer_information consumer_information;

int database_consumer_information(char user_id[30], int read_type) {

  FILE *fwrite; // 声明读取文件所需指针
  char file_name[300];

  strcpy(file_name, path); // 该字符串用于处理文件名

  strcat(file_name, "consumer_information/"); // 加入路径"consumer_information/"
  strcat(file_name, user_id);                 // 文件名为"user_id"
  strcat(file_name, ".txt");                  // 后缀为.txt

  if (!read_type) {
    // 打开特定的订单数据文件
    if ((fwrite = fopen(file_name, "r")) == NULL) // 判断文件是否存在及可读
      return 0;                                   // 不存在, 返回"0"

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
    // 打开特定的订单数据文件
    fwrite = fopen(file_name, "w+");

    // 写入数据
    fprintf(fwrite, "%s %s %s %s %s %s %0.2f",
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
*************************************************/

STU_goods_index goods_index[100];

int database_goods_index(char user_id[30], int read_type) {

  FILE *fwrite; // 声明读取文件所需指针
  char file_name[300];

  strcpy(file_name, path); // 该字符串用于处理文件名

  strcat(file_name, "goods_index/"); // 加入路径"goods_index/"
  strcat(file_name, user_id);        // 文件名为"user_id"
  strcat(file_name, ".txt");         // 后缀为.txt

  int i = 0;
  if (!read_type) {

    // 打开特定的订单数据文件
    if ((fwrite = fopen(file_name, "r")) == NULL) // 判断文件是否存在及可读
      return 0;                                   // 不存在, 返回"0"

    // 读取数据
    while (!feof(fwrite)) {
      fscanf(fwrite, "%s %f %f %d %d %f %d:%d:%d:%d:%d %d:%d:%d:%d:%d",
             goods_index[i].shop_id,             // 超市ID
             &goods_index[i].unit_price,         // 单价
             &goods_index[i].in_price,           // 进价
             &goods_index[i].sales_volume,       // 销量
             &goods_index[i].goods_in_stock,     // 库存
             &goods_index[i].discount_price,     // 折扣价格
             &goods_index[i].time_begin.tm_year, // 折扣开始时间
             &goods_index[i].time_begin.tm_mon,  // ...
             &goods_index[i].time_begin.tm_mday, // ...
             &goods_index[i].time_begin.tm_hour, // ...
             &goods_index[i].time_begin.tm_min,  // ...
             &goods_index[i].time_end.tm_year,   // 折扣结束时间
             &goods_index[i].time_end.tm_mon,    // ...
             &goods_index[i].time_end.tm_mday,   // ...
             &goods_index[i].time_end.tm_hour,   // ...
             &goods_index[i].time_end.tm_min     // ...
      );
      i++;
    }
  } else {

    // 打开特定的订单数据文件
    fwrite = fopen(file_name, "w+");

    // 写入数据
    for (i = 0; i <= 100; i++)
      fprintf(fwrite,
              "%s %0.2f %0.2f %d %d %0.2f %04d:%02d:%02d:%02d:%02d "
              "%04d:%02d:%02d:%02d:%02d\n",
              goods_index[i].shop_id,            // 超市ID
              goods_index[i].unit_price,         // 单价
              goods_index[i].in_price,           // 进价
              goods_index[i].sales_volume,       // 销量
              goods_index[i].goods_in_stock,     // 库存
              goods_index[i].discount_price,     // 折扣价格
              goods_index[i].time_begin.tm_year, // 折扣开始时间
              goods_index[i].time_begin.tm_mon,  // ...
              goods_index[i].time_begin.tm_mday, // ...
              goods_index[i].time_begin.tm_hour, // ...
              goods_index[i].time_begin.tm_min,  // ...
              goods_index[i].time_end.tm_year,   // 折扣结束时间
              goods_index[i].time_end.tm_mon,    // ...
              goods_index[i].time_end.tm_mday,   // ...
              goods_index[i].time_end.tm_hour,   // ...
              goods_index[i].time_end.tm_min     // ...
      );
  }

  fclose(fwrite);
  return 1; // 成功读写返回"1"
}

/*************************************************
*************************************************/

STU_order_admin_all order_admin_all[100]; // 最多存放100笔订单

int database_order_admin_all(char shop_id[30], int read_type) {
  // 声明读取文件所需指针
  FILE *fwrite;

  char file_name[300];

  strcpy(file_name, path);           // 该字符串用于处理文件名
  strcat(file_name, "order_admin/"); // 加入路径"order_admin/"

  // 处理文件名
  strcat(file_name, shop_id);
  strcat(file_name, "_all.txt");

  int i = 0;
  if (!read_type) {

    // 打开特定订单数量文件
    if ((fwrite = fopen(file_name, "r")) == NULL) // 判断文件是否存在及可读
      return 0;                                   // 不存在, 返回"0"

    // 读取数据
    while (!feof(fwrite)) {
      fscanf(fwrite, "%s %s %d:%d:%d:%d:%d %s %d %f %f",
             order_admin_all[i].order_id,           // 订单编号
             order_admin_all[i].consumer_id,        // 顾客编号
             &order_admin_all[i].sold_time.tm_year, // 购买时间
             &order_admin_all[i].sold_time.tm_mon,  // ...
             &order_admin_all[i].sold_time.tm_mday, // ...
             &order_admin_all[i].sold_time.tm_hour, // ...
             &order_admin_all[i].sold_time.tm_min,  // ...
             order_admin_all[i].goods_name,         // 商品名
             &order_admin_all[i].purchase_num,      // 购买数量
             &order_admin_all[i].unit_price,        // 单价
             &order_admin_all[i].all_price          // 总价
      );
      i++;
    }
  } else {

    // 打开特定的订单数据文件
    fwrite = fopen(file_name, "w+");

    // 写入数据
    while (order_admin_all[i].purchase_num != 0) {
      fprintf(fwrite, "%s %s %04d:%02d:%02d:%02d:%02d %s %d %0.2f %0.2f\n",
              order_admin_all[i].order_id,          // 订单编号
              order_admin_all[i].consumer_id,       // 顾客编号
              order_admin_all[i].sold_time.tm_year, // 购买时间
              order_admin_all[i].sold_time.tm_mon,  // ...
              order_admin_all[i].sold_time.tm_mday, // ...
              order_admin_all[i].sold_time.tm_hour, // ...
              order_admin_all[i].sold_time.tm_min,  // ...
              order_admin_all[i].goods_name,        // 商品名
              order_admin_all[i].purchase_num,      // 购买数量
              order_admin_all[i].unit_price,        // 单价
              order_admin_all[i].all_price          // 总价
      );
      i++;
    }
  }
  fclose(fwrite);
  return 1; // 成功读写返回"1"
}

/*************************************************
*************************************************/

STU_order_admin_consumer order_admin_consumer[100]; // 最多存放100笔订单

int database_order_admin_consumer(char shop_id[30], int read_type) {
  // 声明读取文件所需指针
  FILE *fwrite;

  char file_name[300];

  strcpy(file_name, path);           // 该字符串用于处理文件名
  strcat(file_name, "order_admin/"); // 加入路径"order_admin/"

  // 处理文件名
  strcat(file_name, shop_id);
  strcat(file_name, "_consumer.txt");

  int i = 0;
  if (read_type <= 0) {

    // 打开特定的订单数据文件
    if ((fwrite = fopen(file_name, "r")) == NULL) // 判断文件是否存在及可读
      return 0;                                   // 不存在, 返回"0"

    // 读取数据
    i = 0;

    fscanf(fwrite, "%s %s %d",
           order_admin_consumer[i].consumer_id,  // 顾客ID
           order_admin_consumer[i].goods_name,   //商品名
           &order_admin_consumer[i].purchase_num // 购买数量
    );
    if (read_type == -1) {
      if (order_admin_consumer[i].purchase_num != 0) {
        printf("以下为该超市最受欢迎的商品名, 欢迎选购:\n");
        printf("%s\n", order_admin_consumer[i].goods_name);
      }
    }
  } else {

    // 打开特定的订单数据文件
    fwrite = fopen(file_name, "w+");

    // 写入数据
    while (order_admin_consumer[i].purchase_num != 0) {
      fprintf(fwrite, "%s %s %d\n",
              order_admin_consumer[i].consumer_id, // 顾客ID
              order_admin_consumer[i].goods_name,  //商品名
              order_admin_consumer[i].purchase_num // 购买数量
      );
      i++;
    }
  }
  fclose(fwrite);
  return 1; // 成功读写返回"1"
}

/*************************************************
*************************************************/

STU_order_admin_goods order_admin_goods[100]; // 最多存放100笔订单

int database_order_admin_goods(char shop_id[30], int read_type) {
  // 声明读取文件所需指针
  FILE *fwrite;

  char file_name[300];

  strcpy(file_name, path);           // 该字符串用于处理文件名
  strcat(file_name, "order_admin/"); // 加入路径"order_admin/"
  strcat(file_name, shop_id);
  strcat(file_name, "_goods.txt");

  int i = 0;
  if (!read_type) {

    // 打开特定的订单数据文件
    if ((fwrite = fopen(file_name, "r")) == NULL) // 判断文件是否存在及��读
      return 0;                                   // 不存在, 返回"0"

    // 读取数据
    while (!feof(fwrite)) {
      fscanf(fwrite, "%s %d %f %f",
             order_admin_goods[i].goods_name,    // 商品名
             &order_admin_goods[i].purchase_num, // 购买数量
             &order_admin_goods[i].all_price,    // 营业额
             &order_admin_goods[i].profit        // 利润
      );
      i++;
    }
  } else {

    // 打开特定的订单数据文件
    fwrite = fopen(file_name, "w+");

    // 写入数据

    while (order_admin_goods[i].purchase_num != 0) {
      fprintf(fwrite, "%s %d %0.2f %0.2f\n",
              order_admin_goods[i].goods_name,   // 商品名
              order_admin_goods[i].purchase_num, // 购买数量
              order_admin_goods[i].all_price,    // 营业额
              order_admin_goods[i].profit        // 利润
      );
      i++;
    }
  }

  fclose(fwrite);
  return 1; // 成功读写返回"1"
}

/*************************************************
*************************************************/

STU_order_consumer order_consumer[100]; // 最多存放一百笔订单

int database_order_consumer(char user_id[30], int read_type) {
  // 声明读取文件所需指针
  FILE *fwrite;

  char file_name[300];

  strcpy(file_name, path);              // 该字符串用于处理文件名
  strcat(file_name, "order_consumer/"); // 加入路径"order_consumer/"
  strcat(file_name, user_id);
  strcat(file_name, ".txt");

  int i = 0;
  if (!read_type) {

    // 打开特定的订单数据文件
    if ((fwrite = fopen(file_name, "r")) == NULL) // 判断文件是否存在及可读
      return 0;                                   // 不存在, 返回"0"

    // 读取数据
    while (!feof(fwrite)) {
      fscanf(fwrite, "%s %s %s %d %f %f",
             order_consumer[i].order_id,      // 订单编号
             order_consumer[i].sold_time,     // 购买时间
             order_consumer[i].goods_name,    // 商品名
             &order_consumer[i].purchase_num, // 购买数量
             &order_consumer[i].unit_price,   // 单价
             &order_consumer[i].all_price     // 总价
      );
      i++;
    }
  } else {

    // 打开特定的订单数据文件
    fwrite = fopen(file_name, "w+");

    // 写入数据
    for (i = 0; i <= 100; i++)
      fprintf(fwrite, "%s %s %s %d %0.2f %0.2f\n",
              order_consumer[i].order_id,     // 订单编号
              order_consumer[i].sold_time,    // 购买时间
              order_consumer[i].goods_name,   // 商品名
              order_consumer[i].purchase_num, // 购买数量
              order_consumer[i].unit_price,   // 单价
              order_consumer[i].all_price     // 总价
      );
  }
  fclose(fwrite);
  return 1; // 成功读写返回"1"
}

/*************************************************
*************************************************/

STU_shop_index shop_index[100];

int database_shop_index(char user_id[30], int read_type) {
  // 声明读取文件所需指针
  FILE *fwrite;

  char file_name[300];

  strcpy(file_name, path);          // 该字符串用于处理文件名
  strcat(file_name, "shop_index/"); // 加入路径"shop_index/"
  strcat(file_name, user_id);
  strcat(file_name, ".txt");

  int i = 0;
  if (!read_type) {

    // 打开特定的订单数据文件
    if ((fwrite = fopen(file_name, "r")) == NULL) // 判断文件是否存在及可读
    {
      fclose(fwrite);
      return 0;
    } // 不存在, 返回"0"

    while (!feof(fwrite)) {

      // 读取数据
      fscanf(fwrite, "%s %f %f %d %d %f %d:%d:%d:%d:%d %d:%d:%d:%d:%d",
             shop_index[i].goods_name,  // ����品编号
             &shop_index[i].unit_price, // 零售价格
             &shop_index[i].in_price, // 进货价��������������
             &shop_index[i].sales_volume,       // 销量
             &shop_index[i].goods_in_stock,     // 存货
             &shop_index[i].discount_price,     // 折扣价
             &shop_index[i].time_begin.tm_year, // 折扣开始时间
             &shop_index[i].time_begin.tm_mon,  // ...
             &shop_index[i].time_begin.tm_mday, // ...
             &shop_index[i].time_begin.tm_hour, // ...
             &shop_index[i].time_begin.tm_min,  // ...
             &shop_index[i].time_end.tm_year,   // 折扣结束时间
             &shop_index[i].time_end.tm_mon,    // ...
             &shop_index[i].time_end.tm_mday,   // ...
             &shop_index[i].time_end.tm_hour,   // ...
             &shop_index[i].time_end.tm_min     // ...
      );
      i++;
    }
  } else {

    // 打开特定的订单数据文件
    fwrite = fopen(file_name, "w+");

    // 写入数据
    while (shop_index[i].unit_price != 0) {
      fprintf(fwrite,
              "%s %0.2f %0.2f %d %d %0.2f %04d:%02d:%02d:%02d:%02d "
              "%04d:%02d:%02d:%02d:%02d\n",
              shop_index[i].goods_name,         // 商品名
              shop_index[i].unit_price,         // 零售价格
              shop_index[i].in_price,           // 进货价格
              shop_index[i].sales_volume,       // 销量
              shop_index[i].goods_in_stock,     // 存货
              shop_index[i].discount_price,     // 折扣价
              shop_index[i].time_begin.tm_year, // 折扣开始时间
              shop_index[i].time_begin.tm_mon,  // ...
              shop_index[i].time_begin.tm_mday, // ...
              shop_index[i].time_begin.tm_hour, // ...
              shop_index[i].time_begin.tm_min,  // ...
              shop_index[i].time_end.tm_year,   // 折扣结束时间
              shop_index[i].time_end.tm_mon,    // ...
              shop_index[i].time_end.tm_mday,   // ...
              shop_index[i].time_end.tm_hour,   // ...
              shop_index[i].time_end.tm_min     // ...
      );
      i++;
    }
  }
  fclose(fwrite);
  return 1; // 成功读写返回"1"
}

/*************************************************
*************************************************/

STU_shopping_cart shopping_cart[100]; // 最多存放100笔订单

int database_shopping_cart(char user_id[30], int read_type) {
  // 声明读取文件所需指针
  FILE *fwrite;

  char file_name[300];

  strcpy(file_name, path);             // 该字符串用于处理文件名
  strcat(file_name, "shopping_cart/"); // 加入路径"shopping_cart/"

  // 处理文件名
  strcat(file_name, user_id);
  strcat(file_name, ".txt");

  int i = 0;
  if (!read_type) {

    // 打开特定的订单数据文件
    if ((fwrite = fopen(file_name, "r")) == NULL) // 判断文件是否存在及可读
      return 0;
    // 不存在, 返回"0"

    // 读取数据
    while (!feof(fwrite)) {
      fscanf(fwrite, "%s %s %d",
             shopping_cart[i].goods_name,   // 商品名
             shopping_cart[i].shop_id,      // 管理员ID
             &shopping_cart[i].purchase_num // 购买数量
      );
      i++;
    }
  } else {

    // 打开特定的数据文件

    fwrite = fopen(file_name, "w+");

    // 写入数据
    for (i = 0; i <= 100; i++) {
      if (shopping_cart[i].purchase_num != -1 &&
          shopping_cart[i].purchase_num != 0)
        fprintf(fwrite, "%s %s %d\n",
                shopping_cart[i].goods_name,  // 商品名
                shopping_cart[i].shop_id,     // 管理员ID
                shopping_cart[i].purchase_num // 购买数量
        );
      else
        fprintf(fwrite, "0 0 0\n");
    }
  }
  fclose(fwrite);
  return 1; // 成功读写返回"1"
}

/*************************************************
*************************************************/

void database_all_index(int read_type, char goods_name[30], char shop_id[30]) {
  char file_name[300];

  strcpy(file_name, path); // 该�����符串用于处理文件名
  // 处理文件名
  strcat(file_name, "all_index.txt");

  if (read_type == 1) {
    FILE *fwrite;
    fwrite = fopen(file_name, "a");
    fprintf(fwrite, "%s %s\n", goods_name, shop_id);
    fclose(fwrite);
  } else {
    char goods_name[30];
    char shop_id[30];

    FILE *fwrite;
    fwrite = fopen(file_name, "r");

    int i = 0;
    while (!feof(fwrite)) {
      if (i >= 20)
        break;

      fscanf(fwrite, "%s %s",
             goods_name, // 商品名
             shop_id     // 管理员ID
      );
      if (strcmp(goods_name, "") == 0)
        break;
      printf("%s : %s\n", goods_name, shop_id);
      strcpy(goods_name, "");
      strcpy(shop_id, "");
      i++;
    }
    fclose(fwrite);
  }
  return;
}

/*************************************************
*************************************************/
char name_to_id_goods_id[30];

int database_name_to_id(char goods_name[30], int read_type) {

  // 声明读取文件所需指针
  FILE *fwrite;

  char file_name[300];

  strcpy(file_name, path);          // 该字符串用于处理文件名
  strcat(file_name, "name_to_id/"); // 加入路径"name_to_id/"

  // 处理文件名
  strcat(file_name, goods_name);
  strcat(file_name, ".txt");

  if (!read_type) {
    if ((fwrite = fopen(file_name, "r")) == NULL)
      return 0;
    fscanf(fwrite, "%s", name_to_id_goods_id);
  } else {
    fwrite = fopen(file_name, "w+");
    fprintf(fwrite, "%s\n", name_to_id_goods_id);
  }

  fclose(fwrite);

  return 1;
}
