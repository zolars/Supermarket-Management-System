#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email(char email[20]) {
  int i, j = 0, k = 0, n = 0, m = 0, temp = 0;
  for (i = 0; i < strlen(email); i++) {
    if (email[i] == '@')
      j++, n = i;
  }
  for (i = 0; i < strlen(email); i++) {
    if (email[i] == '.')
      k++, m = i;
  }
  if (k == 1 && j == 1)
    temp++;
  if (n + 1 < m)
    temp++;
  return temp;
}

void changes_admin_password(char user_id[11]) {

  printf("\n请输入新的账户密码: ");

  scanf("%s", admin_information.password);

  printf("\n修改成功! ");
  return;
}

void changes_admin_email(char user_id[11]) {

  printf("\n请输入新的邮箱: ");

  scanf("%s", admin_information.email);

  int i;
  i = check_email(admin_information.email);
  while (i != 2) {
    printf("\n邮箱格式错误, 请检查后重新输入! ");
    printf("\n");
    memset(admin_information.email, 0, sizeof(admin_information.email));
    scanf("%s", admin_information.email);
    i = check_email(admin_information.email);
  }

  printf("\n修改成功! ");
  return;
}

void changes_admin(char user_id[11]) {
  if (!database_admin_information(user_id, 0)) { // 数据库读取, 只读
    printf("没有找到文件? 请核查数据库信息.");
    return; // 读取文件发生错误, 返回上一级
  }

  int temp = 1;
  int choose;
  do {
    printf("1. 修改账户密码\n2. 修改邮箱");
    printf("\n请输入对应操作编号: ");
    printf("\n------------------------------");
    printf("\n");
    scanf("%d", &choose);
    switch (choose) {
    case 1:
      printf("\n您正在修改账户密码! ");
      changes_admin_password(user_id);
      break;
    case 2:
      printf("\n您正在修改邮箱! ");
      changes_admin_email(user_id);
      break;
    default:
      printf("\n您输入的编号无效，请检查后重新输入! ");
      printf("\n");
      temp = 0;
    }
  } while (temp == 0);

  database_admin_information(user_id, 1);

  return;
}

int main() {

  char user_id[11] = "guanli";
  changes_admin(user_id);
  return 0;
}
