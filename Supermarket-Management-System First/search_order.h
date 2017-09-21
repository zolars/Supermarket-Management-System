/************************************************

Name:
  search_for_order.h
Author:
  辛逸飞
Date:
  2017-09-12
Language:
  C
Features:
  完成"查询订单"功能的模块.
Modules:
  Customize:
    - database.h
    - search_order.h
  Native:
    - stdio.h
    - string.h
    - stdlib.h
Input:
  - user_id
  - user_type
Output:
  成功运行返回"1"

************************************************/

#ifndef _SEARCH_ORDER_H_ // 防止重复调用
#define _SEARCH_ORDER_H_

// 对结构体排序时, 需要使用结构体的重构来实现
extern int cmp_purchase_num(const void *a, const void *b);

extern int cmp_all_price(const void *a, const void *b);

extern int cmp_profit(const void *a, const void *b);

int cmp_goods_in_stock(const void *a, const void *b);

// 统计营业期间的营业额
extern void search_order_admin_result_1_1();

// 按销量和营业额对商品进行排序
extern void search_order_admin_result_1_2();

// 输出利润最高的商品和最低的商品
extern void search_order_admin_result_1_3();

// 根据库存和销售情况判断商品中哪些需要进货、哪些存在滞销情况
extern void search_order_admin_result_1_4();

// 选择菜单用户界面, 返回选项编号
extern int search_order_admin_choose_1();

// 管理员统计数据
extern void search_order_admin_result_1();

// 管理员打印数据
extern void search_order_admin_result_2();

// 管理员主选项
extern int search_order_admin_choose();

// 管理员程序第一层
extern void search_order_admin();

// 管理员查询主程序, 负责读取数据库以及传入下一层级.
extern int search_order_admin_main(char user_id[30]);

// 用户查询主程序, 负责所有
extern int search_order_consumer_main(char user_id[15]);

// 接入主程序
extern int search_order(char user_id[30], int user_type);

#endif /* _SEARCH_ORDER_H_ */
