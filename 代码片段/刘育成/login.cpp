#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//首先声明用户需要输入的参数
void login_admin();
void login_customer();
void exit();
char choose[2]; //操作者输入的编号指令

void login() {
  int i = 0;
  //欢迎页面
  printf("\n------------------------------\n\n");
  printf("欢迎使用网上超市商品管理系统! ");
  printf("\n\n------------------------------\n");

  //循环+ 选择
  do {
    printf("\n\n---------------操作选项---------------\n");
    printf("1. 管理员系统\n2. 消费者系统\n3. 退出\n");
    printf("请输入对应操作编号: ");
    scanf("%s", choose);
    printf("\n------------------------------\n\n");

    if (strcmp(choose, "1") != 0 && strcmp(choose, "2") != 0 &&
        strcmp(choose, "3") != 0) {
      printf("\n您的输入有误, 请按照操作选项再次输入:\n\n");
      continue;
    }

    int choose_num = atoi(choose); // 字符串转整数, 便于之后的 switch 操作

    switch (choose_num) {
    case 1:
      printf("欢迎进入管理员系统! ");
      printf("\n\n------------------------------\n");
      login_admin(); //进入管理员登录页面

      break;
    case 2:
      printf("欢迎进入消费者系统! ");
      printf("\n\n------------------------------\n");
      login_customer(); //进入消费者登录页面

      break;
    case 3:
      exit(); //进入退出页面

      break;
    default:
      printf("输入编号无效，请重新输入!\n"); //纠错重循环
      i = 1;
    }
  } while (i == 1);
}

//退出页面
void exit() {
  printf("\n------------------------------\n");
  printf("感谢您本次的使用，再见! ");
  printf("\n------------------------------\n");

  return;
}

int main() {
  login();
  return 0;
}
