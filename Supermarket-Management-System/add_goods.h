/************************************************

Name:
  add_goods.h
Author:
  王克淼
Date:
  2017-09-15
Language:
  C
Features:

************************************************/
#ifndef _ADD_GOODS_H_ // 防止重复调用
#define _ADD_GOODS_H_

// 选项1，确认发布
extern void add_goods_result_1();

// 选项2，取消发布
extern void add_goods_result_2();

//检查商品ID
extern char *check_goods_id(char *temp_goods_id);

// 检查单价
extern float check_unit_price();

// 检查进价
extern float check_in_price();

// 检查库存
extern int check_goods_in_stock();

// 检查折扣价格
extern float check_discount_price();

// 检查时间
extern int *check_time();

/************************************************/

extern int add_goods_choose();

extern void add_goods(char user_id[30]);

// 主程序, 负责读取数据库以及传入下一层.
extern int add_goods_main(char user_id[30]);

#endif /*_ADD_GOODS_H_*/
