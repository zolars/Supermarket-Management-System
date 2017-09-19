/************************************************

Name:
  search_for_goods.h
Author:
  董泽元
Date:
  2017-09-15
Language:
  C
Features:

************************************************/

#ifndef _SEARCH_FOR_GOODS_H_ // 防止重复调用
#define _SEARCH_FOR_GOODS_H_

extern char temp_information_market[100][30];

extern char temp_information_item[30];

// 对结构体排序时, 需要使用结构体的重构来实现
extern int cmp_sales_volume_goods(const void *a, const void *b);

extern int cmp_discount_price_goods(const void *a, const void *b);

extern void search_goods_result_0(char user_id[30], int choise_num);

// 筛选打折的商品
extern void search_goods_result_1(char user_id[30]);

// 打印不打折的商品
extern void search_goods_result_2(char user_id[30]);

extern void search_goods_result_3(char user_id[30]);

extern void search_goods_result_4(char user_id[30]);

extern int search_goods_choose();

// search_goods所使用的选择函数
extern void search_goods(char user_id[30]);

//根据超市名称进行查询
extern void search_goods_begin(char user_id[30]);

#endif /*_SEARCH_FOR_GOODS_H_*/
