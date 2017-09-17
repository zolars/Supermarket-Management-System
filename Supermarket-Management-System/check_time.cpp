/************************************************

Name:
  check_time.cpp
Author:
  - 辛逸飞
Date:
  2017-09-16
Language:
  C
Features:

************************************************/
#include "check_time.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int time_check(int num) { // 传入goods_index中第num行数据
  struct tm begin_tm = {
      0,                                   // 秒
      goods_index[num].time_begin.tm_min,  // 分钟数
      goods_index[num].time_begin.tm_hour, // 小时数
      goods_index[num].time_begin.tm_mday, // 当天在这个月中是第几天
      goods_index[num].time_begin.tm_mon,  // 当前月份是第几个月
      goods_index[num].time_begin.tm_year - 1900, // 从1900年开始至今的年数
      0,                                          // 当天在本周是第几天
      0,                                          // 当天在今年是第几天
      0                                           // 夏令时标记
  };
  time_t begin_tm_t = mktime(&begin_tm); // 将人类看得懂的时间转换为tick类型

  struct tm end_tm = {
      0,                                 // 秒
      goods_index[num].time_end.tm_min,  // 分钟数
      goods_index[num].time_end.tm_hour, // 小时数
      goods_index[num].time_end.tm_mday, // 当天在这个月中是第几天
      goods_index[num].time_end.tm_mon,  // 当前月份是第几个月
      goods_index[num].time_end.tm_year - 1900, // 从1900年开始至今的年数
      0,                                        // 当天在本周是第几天
      0,                                        // 当天在今年是第几天
      0                                         // 夏令时标记
  };
  time_t end_tm_t = mktime(&end_tm); // 将人类看得懂的时间转换为tick类型

  time_t calendar_time_t = time(NULL);
  struct tm *tm_local = localtime(&calendar_time_t); // 传入本地时间
  time_t now_tm_t = mktime(tm_local); // 将人类看得懂的时间转换为tick类型

  if (begin_tm_t <= now_tm_t && end_tm_t >= now_tm_t) {
    return 1;
  }

  return 0;
}
