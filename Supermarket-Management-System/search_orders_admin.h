// Name: search_for_orders.h
// Author: 辛逸飞
// Date: 2017-09-12
// Language: C
// Features: 完成"管理员身份-查询订单"功能的模块.
// Modules:
//   - database_order_admin_all.h
//   - databse_order_admin_goods.h
//   - stdio.h
//   - string.h
//   - stdlib.h
//

#include "database_order_admin_all.h"
#include "database_order_admin_goods.h"
#include "database_shop_index.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 对结构体排序时, 需要使用结构体的重构来实现
int cmp_goods_num(const void *a, const void *b) {
  // 注意这里, 这里的"<"标记, 可以更改快速排序结果是升序/降序
  return (*(STU_admin_goods *)a).goods_num < (*(STU_admin_goods *)b).goods_num
             ? 1
             : -1;
}

int cmp_all_price(const void *a, const void *b) {
  return (*(STU_admin_goods *)a).all_price < (*(STU_admin_goods *)b).all_price
             ? 1
             : -1;
}

int cmp_profit(const void *a, const void *b) {
  return (*(STU_admin_goods *)a).profit < (*(STU_admin_goods *)b).profit ? 1
                                                                         : -1;
}

int cmp_goods_in_stock(const void *a, const void *b) {
  return (*(STU_shop_index *)a).goods_in_stock <
                 (*(STU_shop_index *)b).goods_in_stock
             ? 1
             : -1;
}

void order_tool(char user_id[11]) {
  int i; // 循环变量

  int order_num = database_order_admin_goods(user_id); // 数据库传入数组长度
  if (order_num < 0) { // 读取文件发生错误, 返回上一级
    return;
  }

  char choose[10]; // 记录管理员操作时的选择

  int not_over = 1; // 循环尽头指示

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
        turnover += order_admin_goods[i].all_price;
      }
      printf(
          "\n营业期间的总营业额为: %0.2f.\n请输入任意字符并按回车键以继续...\n",
          turnover);
      scanf("%s", choose); // 延迟屏幕显示
      break;
    }

    // 按销量和营业额对商品进行排序
    case 2: {
      qsort(order_admin_goods, order_num, sizeof(order_admin_goods[0]),
            cmp_goods_num);

      printf("\n对销量排序结果如下:\n");
      for (i = 0; i < order_num - 1; i++)
        printf("%s %d %0.2f %0.2f\n", order_admin_goods[i].goods_id,
               order_admin_goods[i].goods_num, order_admin_goods[i].all_price,
               order_admin_goods[i].profit);

      qsort(order_admin_goods, order_num, sizeof(order_admin_goods[0]),
            cmp_all_price);

      printf("\n对营业额排序结果如下:\n");
      for (i = 0; i < order_num - 1; i++)
        printf("%s %d %0.2f %0.2f\n", order_admin_goods[i].goods_id,
               order_admin_goods[i].goods_num, order_admin_goods[i].all_price,
               order_admin_goods[i].profit);

      printf("\n请输入任意字符并按回车键以继续...\n");
      scanf("%s", choose); // 延迟屏幕显示
      break;
    }

    // 输出利润最高的商品和最低的商品
    case 3: {
      qsort(order_admin_goods, order_num, sizeof(order_admin_goods[0]),
            cmp_profit);

      printf("\n对利润排序结果如下:\n");
      for (i = 0; i < order_num - 1; i++)
        printf("%s %d %0.2f %0.2f\n", order_admin_goods[i].goods_id,
               order_admin_goods[i].goods_num, order_admin_goods[i].all_price,
               order_admin_goods[i].profit);
      printf("利润最高的商品为:%s\n利润最低的商品为:%s\n\n",
             order_admin_goods[0].goods_id,
             order_admin_goods[order_num - 2].goods_id);

      printf("请输入任意字符并按回车键以继续...\n");
      scanf("%s", choose); // 延迟屏幕显示
      break;
    }

    //根据库存和销售情况判断商品中哪些需要进货、哪些存在滞销情况
    case 4: {
      printf("iamhere");
      int order_num = database_shop_index(user_id); // 数据库传入数组长度

      if (order_num < 0) { // 读取文件发生错误, 返回上一级
        return;
      }
      break;
    }

    // 返回主程序
    case 5: {
      not_over = 0;
      break;
    }
    }

  } while (not_over);
}

int search_orders_admin(char user_id[11]) {
  int i; // 循环变量

  int order_num = database_order_admin_all(user_id); // 数据库传入数组长度

  if (order_num < 0) { // 读取文件发生错误, 返回上一级
    return 0;
  }

  char choose[10]; // 记录管理员操作时的选择

  // 用户界面
  while (1) {

    printf("\n---------------操作选项---------------\n\n");
    printf("1. 统计顾客订单信息.\n2. 查看顾客订单情况.\n3. 返回.\n");
    printf("\n-------------------------------------\n");
    printf("请按数字键选择要执行的操作:\n");

    scanf("%s", choose);

    // 容错判断
    if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
        strcmp(choose, "3") != 0) {
      printf("\n您的输入有误, 请按照操作选项再次输入:\n\n");
      continue;
    }

    // 管理员: 统计顾客订单信息
    int choose_num = atoi(choose); // 字符串转整数, 便于之后的 switch 操作
    switch (choose_num) {
    case 1: {
      order_tool(user_id);
      break;
    }

    // 管理员: 打印数据
    case 2: {
      printf("\n");
      for (i = 0; i < order_num - 1; i++)

        printf("%s\t%s\t%s\t%d\t%0.2f\t%0.2f\n", order_admin_all[i].order_id,
               order_admin_all[i].consumer_id, order_admin_all[i].sold_time,
               order_admin_all[i].goods_id, order_admin_all[i].goods_num,
               order_admin_all[i].unit_price, order_admin_all[i].all_price);

      printf("\n以上即为您的历史订单.\n请输入任意字符并按回车键以继续...\n");
      scanf("%s", choose); // 延迟屏幕显示
      break;
    }

    // 返回
    case 3: {
      return 0;
    }
    }
  }
}
