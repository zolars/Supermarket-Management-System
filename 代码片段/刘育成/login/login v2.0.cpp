#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//首先声明用户需要输入的参数
void login_admin();
void login_customer();
void exit();
char choose[2]; //操作者输入的编号指令
int user_type;
//顾客信息提取
typedef struct {
  char customer_name[20];
  int sex;
  char tel_num[12];
  char customer_password[11];
  char customer_mail_address[30];
  char address[100];
  float balance;
} STU_customer_information;

STU_customer_information customer_information;

int database_customer_information(char user_id[11]) {
  char password[11]; //输入的密码
  FILE *fread;

  char file_name[300] = "/Users/zolar/OneDrive - Queen Mary, University of "
                        "London/Project/Supermarket-Management-System/"
                        "Supermarket-Management-System/database";
  strcat(file_name, "/customer_information/");

  strcat(file_name, user_id);
  strcat(file_name, ".txt");

  if ((fread = fopen(file_name, "r")) == NULL) {
    fclose(fread);
    return -1;
  }

  fscanf(fread, "%s %d %s %s %s %0.2f", customer_information.customer_name,
         customer_information.sex, customer_information.tel_num,
         customer_information.customer_password,
         customer_information.customer_mail_address,
         customer_information.address, customer_information.balance);

  fclose(fread);
  return 0;
}
//管理员信息提取
typedef struct {
  char supermaket_id[11];
  char admin_name[20];
  char admin_mail_address[50];
  char admin_password[20];
} STU_admin_information;

STU_admin_information admin_information;

int database_admin_information(char user_id[11]) {
  char password[11]; //输入的密码
  FILE *fread;

  char file_name[300] = "/Users/zolar/OneDrive - Queen Mary, University of "
                        "London/Project/Supermarket-Management-System/"
                        "Supermarket-Management-System/database";
  strcat(file_name, "/admin_information/");

  strcat(file_name, user_id);
  strcat(file_name, ".txt");

  if ((fread = fopen(file_name, "r")) == NULL) {
    fclose(fread);
    return -1;
  }

  fscanf(fread, "%s %s %s %s", admin_information.supermaket_id,
         admin_information.admin_name, admin_information.admin_mail_address,
         admin_information.admin_password);

  fclose(fread);
  return 0;
}

//登录页面
int login_authentication() {
  char user_id[11];  //输入的用户名
  char password[11]; //输入的密码
  int temp;
  do {
    printf("\n请输入用户名或者按'0'加回车返回: ");
    scanf("%s", user_id);
    if (strcmp(user_id, "0") == 0)
      break;
    if (user_type == 0) {
      temp = database_customer_information(user_id);
      if (temp < 0) {
        printf("\n您还没有注册, 请注册. \n");
        printf("请输入任意字符并按回车键以继续...\n");
        scanf("%s", password); // 延长屏幕显示时间
        return 0;
      }

      printf("请输入密码:  ");
      scanf("%s", password);

      if (strcmp(password, customer_information.customer_password) ==
          0) //比对用户名与密码是否正确
      {
        printf("\n登录成功! ");
        return 1;
      } else
        printf("\n用户名或密码错误! 请重新登陆! ");
    }
    if (user_type == 1) {
      temp = database_admin_information(user_id);
      if (temp < 0) {
        printf("\n您还没有注册, 请注册. \n");
        printf("请输入任意字符并按回车键以继续...\n");
        scanf("%s", password); // 延长屏幕显示时间
        return 0;
      }

      printf("请输入密码:  ");
      scanf("%s", password);

      if (strcmp(password, admin_information.admin_password) ==
          0) //比对用户名与密码是否正确
      {
        printf("\n登录成功! ");
        return 1;
      } else
        printf("\n用户名或密码错误! 请重新登陆! ");
    }
  } while (1);

  return 0;
}

//退出页面
void exit() {
  printf("\n------------------------------\n");
  printf("感谢您本次的使用，再见! ");
  printf("\n------------------------------\n");

  return;
}

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
      i = 0;
    }

    int choose_num = atoi(choose); // 字符串转整数, 便于之后的 switch 操作

    switch (choose_num) {
    case 1:
      printf("欢迎进入管理员系统! ");
      printf("\n\n------------------------------\n");
      user_type = 1;
      if (login_authentication())
        ; //进入管理员登录页面
      break;
    case 2:
      printf("欢迎进入消费者系统! ");
      printf("\n\n------------------------------\n");
      user_type = 0;
      login_authentication(); //进入消费者登录页面
      break;
    case 3:
      exit(); //进入退出页面

      break;
    default:
      printf("输入编号无效，请重新输入!\n"); //纠错重循环
      i = 1;
    }
  } while (i == 1);
  return;
}

int main() {
  login();
  return 0;
}
