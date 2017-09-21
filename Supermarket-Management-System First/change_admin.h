/************************************************

Name:
  change_admin.h
Author:
  - 王楠鑫
  - 王克淼
Date:
  2017-09-15
Language:
  C
Features:

************************************************/

#ifndef _CHANGE_ADMIN_H_ // 防止重复调用
#define _CHANGE_ADMIN_H_

extern int change_admin_check_email(char email[20]);

extern void change_admin_password(char user_id[11]);

extern void change_admin_email(char user_id[11]);

extern int change_admin_choose();

extern void change_admin(char user_id[11]);

#endif /*_CHANGE_ADMIN_H_*/
