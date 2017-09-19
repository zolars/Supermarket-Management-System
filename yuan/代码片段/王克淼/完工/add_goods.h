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

extern int sub_shop_index; // 用于减掉由于文件末尾空行导致的录入错误
extern int sub_goods_index; // 这个细节要万分注意

// 选项1，确认发布
extern void add_goods_result_1(int deep_num_shop);

// 选项2，取消发布
extern void add_goods_result_2();

// 选项3，修改
// 未完工
extern void add_goods_result_3();

//检查商品ID
extern int check_goods_id(int deep_num_shop);

//检查单价
extern void check_unit_price(int deep_num_shop, int deep_num_goods);

//检查进价
extern void check_in_price(int deep_num_shop, int deep_num_goods);

//检查库存
extern void check_goods_in_stock(int deep_num_shop, int deep_num_goods);

//检查折扣价格
extern void check_discount_price(int deep_num_shop, int deep_num_goods);

//检查折扣开始时间
extern void check_begin_time(int deep_num_shop, int deep_num_goods);

extern void check_end_time(int deep_num_shop, int deep_num_goods);

//输入新商品信息
extern void check_information();

/************************************************/

extern int add_goods_choose();

extern void add_goods(char user_id[30]);

// 主程序, 负责读取数据库以及传入下一层.
extern int add_goods_main(char user_id[30]);

#endif /*_ADD_GOODS_H_*/
