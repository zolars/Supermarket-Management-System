// Name: search_for_orders.h
// Author: 辛逸飞
// Date: 2017-09-12
// Language: C
// Features: 完成"管理员身份-查询订单"功能的模块.
// Modules:
//   - qsort.h
//   - stdio.h
//   - string.h
//   - stdlib.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义结构体存放所有数据
typedef struct {
  char order_id[11];    // 订单编号
  char consumer_id[11]; // 顾客编号
  char sold_time[25];   // 购买时间
  char goods_id[11];    // 商品编号
  int goods_num;        // 购买数量
  float unit_price;     // 单价
  float all_price;      // 总价
} STU_all;

// 定义结构体存放商品索引数据
typedef struct {
  char goods_id[11]; // 商品编号
  int goods_num;     // 购买数量
  float all_price;   // 营业额
  float profit;      // 利润
} STU_goods;

// 对结构体排序时, 需要使用结构体的重构来实现
int cmp_goods_num(const void *a, const void *b) {
  // 注意这里, 这里的"<"标记, 可以更改快速排序结果是升序/降序
  return (*(STU_goods *)a).goods_num < (*(STU_goods *)b).goods_num ? 1 : -1;
}

int cmp_all_price(const void *a, const void *b) {
  return (*(STU_goods *)a).all_price < (*(STU_goods *)b).all_price ? 1 : -1;
}

int cmp_profit(const void *a, const void *b) {
  return (*(STU_goods *)a).profit < (*(STU_goods *)b).profit ? 1 : -1;
}

STU_goods order_goods[100]; // 最多存放一百笔订单

void order_tool(char user_id[11]) {
  // 声明读取文件所需指针
  FILE *fread;

  char file_name[300] =
      "/Users/zolar/OneDrive - Queen Mary, University of "
      "London/Project/Supermarket-Management-System/"
      "Supermarket-Management-System/"; // 该字符串用于处理文件名
  strcat(file_name, "order_admin/");    // 加入路径"order_admin/"

  // 处理文件名
  strcat(file_name, user_id);
  strcat(file_name, "_goods.txt");

  // 打开特定的订单数据文件
  if ((fread = fopen(file_name,
                     "r")) == NULL) // 判断文件是否存在及可读
  {
    printf("You have not sold anything.\n");
    return;
  }

  int i = 0; // 循环变量(注意这里的i一定要定为0)
  while (!feof(fread)) {

    // 读取数据
    fscanf(fread, "%s %d %f %f", order_goods[i].goods_id,
           &order_goods[i].goods_num, &order_goods[i].all_price,
           &order_goods[i].profit);

    i++;
  }

  int order_num = i; // 保存订单数量

  char choose[10]; // 记录管理员操作时的选择

  int not_over = true; // 循环尽头指示

  do {

    // 用户界面
    printf("\n---------------操作选项---------------\n\n");
    printf("1. 统计营业期间的营业额.\n2. 对商品进行排序.\n");
    printf("3. 利润最高和最低的商品.\n4. 进货需求与滞销商品查看.\n5. 返回.\n");
    printf("\n-------------------------------------\n");
    printf("请按数字键选择要执行的操作:\n");

    scanf("%s", choose);

    // 容错判断
    if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
        strcmp(choose, "3") != 0 && strcmp(choose, "4") != 0 &&
        strcmp(choose, "5") != 0) {
      printf("\n您的输入有误, 请按照操作选项再次输入:\n\n");
    }

    int choose_num = atoi(choose); // 字符串转整数, 便于之后的 switch 操作

    switch (choose_num) {

    // 统计营业期间的营业额
    case 1: {
      float turnover = 0; // 营业额

      // 遍历求和
      for (i = 0; i < order_num; i++) {
        turnover += order_goods[i].all_price;
      }
      printf(
          "\n营业期间的总营业额为: %0.2f.\n请输入任意字符并按回车键以继续...\n",
          turnover);
      scanf("%s", choose); // 延迟屏幕显示
      break;
    }

    // 按销量和营业额对商品进行排序
    case 2: {
      qsort(order_goods, order_num, sizeof(order_goods[0]), cmp_goods_num);

      printf("\n对销量排序结果如下:\n");
      for (i = 0; i < order_num - 1; i++)
        printf("%s %d %0.2f %0.2f\n", order_goods[i].goods_id,
               order_goods[i].goods_num, order_goods[i].all_price,
               order_goods[i].profit);

      qsort(order_goods, order_num, sizeof(order_goods[0]), cmp_all_price);

      printf("\n对营业额排序结果如下:\n");
      for (i = 0; i < order_num - 1; i++)
        printf("%s %d %0.2f %0.2f\n", order_goods[i].goods_id,
               order_goods[i].goods_num, order_goods[i].all_price,
               order_goods[i].profit);

      printf("\n请输入任意字符并按回车键以继续...\n");
      scanf("%s", choose); // 延迟屏幕显示
      break;
    }

    // 输出利润最高的商品和最低的商品
    case 3: {
      qsort(order_goods, order_num, sizeof(order_goods[0]), cmp_profit);

      printf("\n对利润排序结果如下:\n");
      for (i = 0; i < order_num - 1; i++)
        printf("%s %d %0.2f %0.2f\n", order_goods[i].goods_id,
               order_goods[i].goods_num, order_goods[i].all_price,
               order_goods[i].profit);
      printf("利润最高的商品为:%s\n利润最低的商品为:%s\n\n",
             order_goods[0].goods_id, order_goods[order_num - 2].goods_id);

      printf("请输入任意字符并按回车键以继续...\n");
      scanf("%s", choose); // 延迟屏幕显示
      break;
    }

    //根据库存和销售情况判断商品中哪些需要进货、哪些存在滞销情况
    case 4: {
    }

    // 返回主程序
    case 5: {
      not_over = false;
      break;
    }
    }

  } while (not_over);
}

int search_for_orders_admin(char user_id[11]) {

  // 声明读取文件所需指针
  FILE *fread;

  char file_name[300] =
      "/Users/zolar/OneDrive - Queen Mary, University of "
      "London/Project/Supermarket-Management-System/"
      "Supermarket-Management-System/"; // 该字符串用于处理文件名
  char choose[10];                      // 记录管理员操作时的选择

  strcat(file_name, "order_admin/"); // 加入路径"order_admin/"

  // 处理文件名
  strcat(file_name, user_id);
  strcat(file_name, "_all.txt");

  // 打开特定的订单数据文件
  if ((fread = fopen(file_name,
                     "r")) == NULL) // 判断文件是否存在及可读
  {
    printf("You have not sold anything.\n");
    return 0;
  }

  STU_all order_all[100]; // 最多存放一百笔订单

  // 遍历组件, 将所有订单信息存入 order_all 结构体
  int i = 0;

  while (!feof(fread)) {

    // 读取数据
    fscanf(fread, "%s %s %s %s %d %f %f", order_all[i].order_id,
           order_all[i].consumer_id, order_all[i].sold_time,
           order_all[i].goods_id, &order_all[i].goods_num,
           &order_all[i].unit_price, &order_all[i].all_price);

    i++;
  }

  int order_num = i; // 保存订单数量

  // 用户界面
  while (1) {

    printf("\n---------------操作选项---------------\n\n");
    printf("1. 统计顾客订单信息.\n2. 查看顾客订单情况.\n3. 返回.");
    printf("\n-------------------------------------\n");
    printf("请按数字键选择要执行的操作:\n");

    scanf("%s", choose);

    // 容错判断
    if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0) {
      printf("\n您的输入有误, 请按照操作选项再次输入:\n\n");
      continue;
    }

    // 管理员: 统计顾客订单信息
    int choose_num = atoi(choose); // 字符串转整数, ��于之后的 switch 操作
    switch (choose_num) {
    case 1: {
      order_tool(user_id);
      break;
    }

    // 管理员: 打印数据
    case 2: {
      printf("\n");
      for (i = 0; i < order_num - 1; i++)

        printf("%s\t%s\t%s\t%d\t%0.2f\t%0.2f\n", order_all[i].order_id,
               order_all[i].consumer_id, order_all[i].sold_time,
               order_all[i].goods_id, order_all[i].goods_num,
               order_all[i].unit_price, order_all[i].all_price);

      printf("\n以上即为您的历史订单.\n请输入任意字符并按回车键以继续...\n");
      scanf("%s", choose); // 延迟屏幕显示
      break;
    }

    // 返回
    case 3: {
      fclose(fread);
      return 0;
    }
    }
  }
}
