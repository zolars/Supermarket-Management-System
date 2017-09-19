/************************************************

Name:
  change_consumer.h
Author:
  - 王楠鑫
  - 王克淼
Date:
  2017-09-15
Language:
  C
Features:

************************************************/

#ifndef _CHANGE_CONSUMER_H_ // 防止重复调用
#define _CHANGE_CONSUMER_H_

int change_consumer_check_email(char email[20]);

void change_consumer_tel(char user_id[11]);

void change_consumer_password(char user_id[11]);

void change_consumer_email(char user_id[11]);

void change_consumer_address(char user_id[11]);

int change_consumer_choose();

void change_consumer(char user_id[11]);

#endif /*_CHANGE_CONSUMER_H_*/
