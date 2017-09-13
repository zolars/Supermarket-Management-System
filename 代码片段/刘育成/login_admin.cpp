#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//管理员登录页面
int login_admin() {
  char user_id[11];  //输入的用户名
  char password[11]; //输入的密码
  do {
    printf("\n请输入用户名或者按'0'加回车返回: ");
    scanf("%s", user_id);

    if (strcmp(user_id, "0") == 0)
      break;
    if (database_admin_information(user_id) < 0) {
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
  } while (1);

  return 0;
}

int main() {
  int login_result = login_admin();
  return 0;
}
