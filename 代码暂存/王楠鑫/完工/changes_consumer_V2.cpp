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

void changes_consumer_tel(char user_id[11]) {

  int temp = 0;

  do {
    printf("\n请输入新的电话号码: \n");
    scanf("%s", consumer_information.tel);
    long tel_num = atol(consumer_information.tel);
    if (strlen(consumer_information.tel) != 11 || tel_num < 10000000000 ||
        tel_num > 99999999999) {
      printf("\n电话号码为11位数字, 请检查后重新输入!\n");
      continue;
    }
    break;
  } while (1);

  printf("\n修改成功! ");
  return;
}

void changes_consumer_password(char user_id[11]) {

  printf("\n请输入新的账户密码: ");
  scanf("%s", consumer_information.password);
  printf("\n修改成功! ");
  return;
}

void changes_consumer_email(char user_id[11]) {
  printf("\n请输入新的邮箱: ");
  int i;
  scanf("%s", consumer_information.email);
  i = check_email(consumer_information.email);
  while (i != 2) {
    printf("\n邮箱格式错误, 请检查后重新输入! ");
    printf("\n");
    memset(consumer_information.email, 0, sizeof(consumer_information.email));
    scanf("%s", consumer_information.email);
    i = check_email(consumer_information.email);
  }

  printf("\n修改成功! ");
  return;
}

void changes_consumer_address(char user_id[11]) {

  printf("\n请输入新的收货地址: ");
  scanf("%s", consumer_information.address);
  printf("\n修改成功! ");
  return;
}

void changes_consumer(char user_id[11]) {

  if (!database_consumer_information(user_id, 0)) { // 数据库读取, 只读
    printf("没有找到数据? 请先加入部分订单.");
    return; // 读取文件发生错误, 返回上一级
  }

  int choose;
  int i = 1;

  do {
    printf("1. 修改电话号码\n2. 修改账户密码\n3. 修改邮箱\n4. 修改收货地址");
    printf("\n请输入对应操作编号: ");
    printf("\n------------------------------");
    printf("\n");
    scanf("%d", &choose);
    switch (choose) {
    case 1:
      printf("\n您正在修改电话号码! ");
      changes_consumer_tel(user_id);
      break;
    case 2:
      printf("\n您正在修改账户密码! ");
      changes_consumer_password(user_id);
      break;
    case 3:
      printf("\n您正在修改邮箱! ");
      changes_consumer_email(user_id);
      break;
    case 4:
      printf("\n您正在修改收货地址! ");
      changes_consumer_address(user_id);
      break;
    default:
      printf("\n您输入的编号无效，请检查后重新输入! ");
      printf("\n");
      i = 0;
    }
  } while (i == 0);

  database_consumer_information(user_id, 1); // 入库

  return;
}

int main() {

  char user_id[11] = "guke";
  changes_consumer(user_id);

  return 0;
}
