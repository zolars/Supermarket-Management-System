// Name: search_for_order.h
// Author: 辛逸飞
// Date: 2017-09-12
// Language: C
// Features: 完成"管理员身份-查询订单"功能的模块.
// Modules:
//   - database.h
//   - stdio.h
//   - string.h
//   - stdlib.h
//

#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 对结构体排序时, 需要使用结构体的重构来实现
int cmp_purchase_num(const void *a, const void *b) {
  // 注意这里, 这里的"<"标记, 可以更改快速排序结果是升序/降序
  return (*(STU_order_admin_goods *)a).purchase_num <
                 (*(STU_order_admin_goods *)b).purchase_num
             ? 1
             : -1;
}

int cmp_all_price(const void *a, const void *b) {
  return (*(STU_order_admin_goods *)a).all_price <
                 (*(STU_order_admin_goods *)b).all_price
             ? 1
             : -1;
}

int cmp_profit(const void *a, const void *b) {
  return (*(STU_order_admin_goods *)a).profit <
                 (*(STU_order_admin_goods *)b).profit
             ? 1
             : -1;
}

int cmp_goods_in_stock(const void *a, const void *b) {
  return (*(STU_shop_index *)a).goods_in_stock <
                 (*(STU_shop_index *)b).goods_in_stock
             ? 1
             : -1;
}

/*
void order_tool(char user_id[11]) {




  case 1: {

  }

  // 按销量和营业额对商品进行排序
  case 2: {
    qsort(order_admin_goods, order_num, sizeof(order_admin_goods[0]),
          cmp_purchase_num);

    printf("\n对销量排序结果如下:\n");
    printf("商品编号  销量  营业额  利润\n");
    for (i = 0; i < order_num - 1; i++)
      printf("%s\t%4d\t%0.2f\t%0.2f\n", order_admin_goods[i].goods_id,
             order_admin_goods[i].purchase_num, order_admin_goods[i].all_price,
             order_admin_goods[i].profit);

    qsort(order_admin_goods, order_num, sizeof(order_admin_goods[0]),
          cmp_all_price);

    printf("\n对营业额排序结果如下:\n");
    printf("商品编号  销量  营业额  利润\n");
    for (i = 0; i < order_num - 1; i++)
      printf("%s\t%4d\t%0.2f\t%0.2f\n", order_admin_goods[i].goods_id,
             order_admin_goods[i].purchase_num, order_admin_goods[i].all_price,
             order_admin_goods[i].profit);

    printf("\n请输入任意字符并按回车键以继续...\n");
    scanf("%s", choose); // 延长屏幕显示时间
    break;
  }

  // 输出利润最高的商品和最低的商品
  case 3: {
    qsort(order_admin_goods, order_num, sizeof(order_admin_goods[0]),
          cmp_profit);

    printf("\n对利润排序结果如下:\n");
    printf("商品编号  销量  营业额  利润\n");
    for (i = 0; i < order_num - 1; i++)
      printf("%s\t%4d\t%0.2f\t%0.2f\n", order_admin_goods[i].goods_id,
             order_admin_goods[i].purchase_num, order_admin_goods[i].all_price,
             order_admin_goods[i].profit);
    printf("\n利润最高的商品为:%s\n利润最低的商品为:%s\n\n",
           order_admin_goods[0].goods_id,
           order_admin_goods[order_num - 2].goods_id);

    printf("请输入任意字符并按回车键以继续...\n");
    scanf("%s", choose); // 延长屏幕显示时间
    break;
  }

  //根据库存和销售情况判断商品中哪些需要进货、哪些存在滞销情况
  case 4: {
    int order_num = database_shop_index(user_id); // 数据库传入数组长度
    if (order_num < 0) { // 读取文件发生错误, 返回上一级
      return;
    }

    qsort(shop_index, order_num, sizeof(shop_index[0]), cmp_goods_in_stock);

    int temp = 1; // 记录是否为"无"
    printf("\n需要补充库存的商品编号:\n");
    for (i = 0; i < order_num - 1; i++)
      if (shop_index[i].goods_in_stock == 0) {
        printf("%s\n", shop_index[i].goods_id);
        temp = 0;
      }
    if (temp)
      printf("无\n");

    temp = 1;
    printf("\n滞销的商品编号:\n");
    for (i = 0; i < order_num - 1; i++)
      if (shop_index[i].sales_volume == 0) {
        printf("%s\n", shop_index[i].goods_id);
        temp = 0;
      }
    if (temp)
      printf("无\n");

    printf("请输入任意字符并按回车键以继续...\n");
    scanf("%s", choose); // 延长屏幕显示时间
    break;
  }

  // 返回主程序
  case 5: {
    not_over = 0;
    break;
  }
  }
}
while (not_over)
  ;
}

*/

// 统计营业期间的营业额
void search_order_admin_result_1_1() {
  float turnover = 0; // 营业额
  int i = 0;          // 循环变量

  // 遍历求和
  while (order_admin_goods[i].purchase_num != 0) {
    turnover += order_admin_goods[i].all_price;
    printf("%0.2f\n", order_admin_goods[i].all_price);
    i++;
  }
  printf("\n营业期间的总营业额为: "
         "%0.2f.\n\n请输入任意字符并按回车键以继续...\n",
         turnover);
  char screen[10];
  scanf("%s", screen); // 延长屏幕显示时间
  return;
}

void search_order_admin_result_1_2() {
  int order_num = 0, i = 0;                                // 循环变量
  while (order_admin_goods[order_num].purchase_num != 0) { // 遍历求深度
    order_num += 1;
  }

  printf("%d", order_num);
  qsort(order_admin_goods, order_num, sizeof(order_admin_goods[0]),
        cmp_purchase_num);

  printf("\n对销量排序结果如下:\n");
  printf("商品编号  销量  营业额  利润\n");
  for (i = 0; i < order_num; i++)
    printf("%s\t%4d\t%0.2f\t%0.2f\n",
           order_admin_goods[i].goods_id,     // 商品编号
           order_admin_goods[i].purchase_num, // 销量
           order_admin_goods[i].all_price,    // 营业额
           order_admin_goods[i].profit        // 利润
    );

  qsort(order_admin_goods, order_num, sizeof(order_admin_goods[0]),
        cmp_all_price);

  printf("\n对营业额排序结果如下:\n");
  printf("商品编号  销量  营业额  利润\n");
  for (i = 0; i < order_num; i++)
    printf("%s\t%4d\t%0.2f\t%0.2f\n",
           order_admin_goods[i].goods_id,     // 商品编号
           order_admin_goods[i].purchase_num, // 销量
           order_admin_goods[i].all_price,    // 营业额
           order_admin_goods[i].profit        // 利润
    );

  printf("\n请输入任意字符并按回车键以继续...\n");
  char screen[10];
  scanf("%s", screen); // 延长屏幕显示时间
  return;
}

void search_order_admin_result_1_3() { return; }

// 0_1_4
void search_order_admin_result_1_4() { return; }

int search_order_admin_choose_1() {
  char choose[10]; // 记录管理员操作时的选择
  int choose_num;

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
    choose_num = search_order_admin_choose_1();
  } else
    choose_num = atoi(choose);
  return choose_num;
}

// 0_1 管理员统计数据
void search_order_admin_result_1() {
  int choose = search_order_admin_choose_1();

  switch (choose) {

  case 1: {
    search_order_admin_result_1_1();
    search_order_admin_result_1();
    break;
  }

  case 2: {
    search_order_admin_result_1_2();
    search_order_admin_result_1();
    break;
  }

  case 3: {
    search_order_admin_result_1_3();
    search_order_admin_result_1();
    break;
  }
  case 4: {
    search_order_admin_result_1_4();
    search_order_admin_result_1();
    break;
  }

  // 返回上一层
  case 5: {
    break;
  }
  }
  return;
}

// 0_2 管理员打印数据
void search_order_admin_result_2() {
  int i = 0; // 循环变量
  printf("\n您店内的所有订单如下:\n");
  printf("      订单编号   顾客编号       购买时间   商品编号  购买数量  "
         "单价  总价\n");
  while (order_admin_all[i].purchase_num != 0) {
    printf("%s  %s %d:%d:%d:%d:%d %s        %d    %0.2f  %0.2f\n",
           order_admin_all[i].order_id,         // 订单编号
           order_admin_all[i].consumer_id,      // 顾客编���
           order_admin_all[i].sold_time.year,   // 购买时间
           order_admin_all[i].sold_time.month,  // ...
           order_admin_all[i].sold_time.day,    // ...
           order_admin_all[i].sold_time.hour,   // ...
           order_admin_all[i].sold_time.minute, // ...
           order_admin_all[i].goods_id,         // 商品ID
           order_admin_all[i].purchase_num,     // 购买数量
           order_admin_all[i].unit_price,       // 单价
           order_admin_all[i].all_price         // 总价
    );
    i++;
  }

  printf("\n以���即为您的历史订单.\n请输入任意字符并按回车键以继续...\n");
  char screen[10];
  scanf("%s", screen); // 延长屏幕显示时间
  return;
}

// 主选项
int search_order_admin_choose() {
  char choose[10]; // 记录管理���操���时的选择
  int choose_num;

  // 用户界面
  printf("\n---------------操作选项---------------\n\n");
  printf("1. 统计顾客订单信息.\n2. 查看顾客订单情况.\n3. 返回.\n");
  printf("\n-------------------------------------\n");
  printf("请按数字键选择要执行的操作:\n");

  scanf("%s", choose);

  // 容错判断
  if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
      strcmp(choose, "3") != 0) {
    printf("\n您的输入有误, 请按照操作选项再次输入:\n\n");
    choose_num = search_order_admin_choose();
  } else
    choose_num = atoi(choose);
  return choose_num;
}

// 0
void search_order_admin() {

  int choose = search_order_admin_choose(); // 用户界面传入指令

  switch (choose) {

  case 1: {
    search_order_admin_result_1();
    search_order_admin();
    break;
  }

  case 2: {
    search_order_admin_result_2();
    search_order_admin();
    break;
  }

  // 返回上一层
  case 3: {
    break;
  }
  }
  return;
}

// 主程序, 负责读取数据库以及传入下一层.
int search_order_admin_main(char user_id[30]) {

  if (!database_order_admin_all(user_id, 0)) { // 数据库读取, 只读
    printf("没有找到数据? 请先加入部分订单.");
    return 0; // 读取文件发生错误, 返回上一级
  }

  if (!database_order_admin_goods(user_id, 0)) { // 数据库读取, 只读
    printf("没有找到数据? 请先加入部分订单.");
    return 0; // 读取文件发生错误, 返回上一级
  }

  search_order_admin();

  database_order_admin_all(user_id, 1);
  return 1;
}
