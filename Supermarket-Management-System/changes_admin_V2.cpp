#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义结构体存放商品索引数据
typedef struct {
  char store[20];    // 商品编号
  char name[20];     // 购买数量
  char email[20];    // 营业额
  char password[20]; // 利润
} STU_admin_information;

STU_admin_information admin_information;

char file_name_global[300];

void database_admin_information(char user_id[11]) {
  // 声明读取文件所需指针
  FILE *fread;

  char file_name[300] =
      "/Users/zolar/OneDrive - Queen Mary, University of "
      "London/Project/Supermarket-Management-System/"
      "Supermarket-Management-System/database"; // 该字符串用于处理文件名

  strcat(file_name, "/admin_information/"); // 加入路径"admin_information/"

  // 处理文件名
  strcat(file_name, user_id);
  strcat(file_name, ".txt");

  // 打开特定的订单数据文件
  fread = fopen(file_name, "r");

  fscanf(fread, "%s %s %s %s", admin_information.store, admin_information.name,
         admin_information.email, admin_information.password);

  fclose(fread);

  strcpy(file_name_global, file_name);
  return; // 保存订单数量
}

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
  FILE *fp;

  database_admin_information(user_id); // 数据库传入file_name_global
  printf("\n请输入新的账户密码: ");
  scanf("%s", admin_information.password);
  fp = fopen(file_name_global, "w+");
  fprintf(fp, "%s %s %s %s", admin_information.store, admin_information.name,
          admin_information.email, admin_information.password);
  fclose(fp);
  printf("\n修改成功! ");
  return;
}

void changes_admin_email(char user_id[11]) {
  FILE *fp;
  database_admin_information(user_id); // 数据库传入file_name
  printf("\n请输入新的邮箱: ");
  int i;
  scanf("%s", admin_information.email);
  i = check_email(admin_information.email);
  while (i != 2) {
    printf("\n邮箱格式错误, 请检查后重新输入! ");
    printf("\n");
    memset(admin_information.email, 0, sizeof(admin_information.email));
    scanf("%s", admin_information.email);
    i = check_email(admin_information.email);
  }

  fp = fopen(file_name_global, "w+");
  fprintf(fp, "%s %s %s %s", admin_information.store, admin_information.name,
          admin_information.email, admin_information.password);
  fclose(fp);
  printf("\n修改成功! ");
  return;
}

void changes_admin(char user_id[11]) {
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

  return;
}

int main() {

  char user_id[11] = "guanli";
  changes_admin(user_id);
  return 0;
}
