/************************************************

Name:
  check_time.h
Author:
  - 辛逸飞
Date:
  2017-09-16
Language:
  C
Features:
  完成购买前的时间检查操作, 以便于记录是否采纳了折扣价格.
Modules:
  Customize:
    - check_time.h
    - database.h
  Native:
    - stdio.h
    - stdlib.h
    - time.h
Input:
  - num
    传入"goods_index"数据库中第num行数据
Output:
  - 1
    采纳折扣价格
  - 0
    不采纳折扣价格, 使用单价

************************************************/
#ifndef _CHECK_TIME_H_ // 防止重复调用
#define _CHECK_TIME_H_

// 传入goods_index中第num行数据
extern int check_time(int num);

#endif /*_CHECK_TIME_H_*/
