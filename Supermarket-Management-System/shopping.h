/************************************************

Name:
  shopping.cpp
Author:
  - 辛逸飞
Date:
  2017-09-16
Language:
  C
Features:
  完成购买入库的接口
Modules:
  Customize:
    - database.h
  Native:
    - stdio.h
    - string.h
    - stdlib.h
Input:

Output:

************************************************/

#ifndef _SHOPPING_H_ // 防止重复调用
#define _SHOPPING_H_

extern int shopping(char id[10], char market[10], int num);

#endif /*_SHOPPING_H_*/
