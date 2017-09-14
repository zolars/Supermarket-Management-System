#include <stdio.h>
#include <string.h>
//首先声明用户需要输入的参数
void log_in_admin();
void log_in_customer();
void exit();
int op;
int i = 0;
void log_in() {

  //欢迎页面
  printf("\n------------------------------\n\n");
  printf("欢迎使用网上超市商品管理系统! ");
  printf("\n\n------------------------------\n");

  //循环+ 选择
  do {
    printf("1. 管理员系统\n2. 消费者系统\n3. 退出\n");
    printf("请输入对应操作编号: ");
    scanf("%d", &op);
    printf("\n------------------------------\n");
    switch (op) {
    case 1:
      printf("欢迎进入管理员系统! ");
      log_in_admin(); //进入管理员登录页面
      break;
    case 2:
      printf("欢迎进入消费者系统! ");
      log_in_customer(); //进入消费者登录页面
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

//管理员登录页面
void log_in_admin() {
  char name[10];      //输入的用户名
  char rname[10];     //正确用户名
  char password[10];  //输入的密码
  char rpassword[10]; //正确密码
  printf("\n请输入用户名: ");
  scanf("%s", &name);
  printf("请输入密码: ");
  scanf("%s", &password);
  if ((strcmp(name, rname) == 0) &&
      (strcmp(password, rpassword) == 0)) //比对用户名与密码是否正确
  {
    printf("\n登录成功! ");

  } else {
    printf("\n用户名或密码错误! 请重新登陆! ");
    log_in(); //调用初始登录页面
  }
}

//消费者登录页面
void log_in_customer() {
  char cname[10];      //输入的用户名
  char rcname[10];     //正确用户名
  char cpassword[10];  //输入的密码
  char rcpassword[10]; //正确密码
  printf("\n请输入用户名: ");
  scanf("%s", &cname);
  printf("请输入密码: ");
  scanf("%s", &cpassword);
  if ((strcmp(cname, rcname) == 0) &&
      (strcmp(cpassword, rcpassword) == 0)) //比对用户名与密码是否正确
  {
    printf("\n登录成功! ");

  } else {
    printf("\n用户名或密码错误! 请重新登陆! ");
    log_in(); //调用初始登录页面
  }
}

//退出页面
void exit() {
  printf("\n------------------------------\n");
  printf("感谢您本次的使用，再见! ");
  printf("\n------------------------------\n");

  return;
}

int main() { log_in(); }
