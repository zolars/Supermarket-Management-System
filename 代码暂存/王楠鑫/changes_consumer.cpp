#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义结构体存放商品索引数据
typedef struct {
  char name[10];
  char sex[5];
  char tel[20];
  char password[20];
  char email[20];
  char address[20];
} STU_consumer_information;

char file_name_global[300];
STU_consumer_information consumer_information;

void database_consumer_information(char user_id[11]) {
  // 声明读取文件所需指针
  FILE *fread;

  char file_name[300] =
      "/Users/zolar/OneDrive - Queen Mary, University of "
      "London/Project/Supermarket-Management-System/"
      "Supermarket-Management-System/database"; // 该字符串用于处理文件名

  strcat(file_name,
         "/consumer_information/"); // 加入路径"consumer_information/"

  // 处理文件名
  strcat(file_name, user_id);
  strcat(file_name, ".txt");

  // 打开特定的订单数据文件
  fread = fopen(file_name, "r");

  // 读取数据,将信息存入 consumer_information 结构体
  fscanf(fread, "%s %s %s %s %s %s", consumer_information.name,
         consumer_information.sex, consumer_information.tel,
         consumer_information.password, consumer_information.email,
         consumer_information.address);

  fclose(fread);

  strcpy(file_name_global, file_name);
  return;
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

void changes_consumer_tel(char user_id[11]) {
  FILE *fp;
  int temp = 0;

  database_consumer_information(user_id); // 数据库传入file_name

  do {
    printf("\n请输入新的电话号码: ");
    scanf("%s", consumer_information.tel);
    if (strlen(consumer_information.tel) == 11)
      break;
    else {
      printf("\n电话号码为11位数字, 请检查后重新输入! ");
      temp = 1;
    }
  } while (temp);

  fp = fopen(file_name_global, "w+");

  fprintf(fp, "%s %s %s %s %s %s", consumer_information.name,
          consumer_information.sex, consumer_information.tel,
          consumer_information.password, consumer_information.email,
          consumer_information.address);
  fclose(fp);
  printf("\n修改成功! ");
  return;
}

void changes_consumer_password(char user_id[11]) {
  FILE *fp;

  database_consumer_information(user_id); // 数据库传入file_name
  printf("\n请输入新的账户密码: ");
  scanf("%s", consumer_information.password);
  fp = fopen(file_name_global, "w+");
  fprintf(fp, "%s %s %s %s %s %s", consumer_information.name,
          consumer_information.sex, consumer_information.tel,
          consumer_information.password, consumer_information.email,
          consumer_information.address);
  fclose(fp);
  printf("\n修改成功! ");
  return;
}

void changes_consumer_email(char user_id[11]) {
  /*
  FILE *fp;

    database_consumer_information(user_id); // 数据库传入file_name
  printf("\n请输入新的邮箱: ");
  int i;
  gets(email);
  i = check_email(email);
  while (i != 2) {
    printf("\n邮箱格式错误, 请检查后重新输入! ");
    memset(consumer_information.email, 0, sizeof(email));
    gets(email);
    i = check_email(email);
  }
  return;

  fp = fopen(file_name_global, "w+");
  fprintf(fp, "%s %s %s %s %s %s", consumer_information.name,
          consumer_information.sex, consumer_information.tel,
          consumer_information.password, consumer_information.email,
          consumer_information.address);
  fclose(fp);
  printf("\n修改成功! ");
  return;*/
  return;
}

void changes_consumer_address(char user_id[11]) {
  FILE *fp;

  database_consumer_information(user_id); // 数据库传入file_name
  printf("\n请输入新的收货地址: ");
  scanf("%s", consumer_information.address);
  fp = fopen(file_name_global, "w+");
  fprintf(fp, "%s %s %s %s %s %s", consumer_information.name,
          consumer_information.sex, consumer_information.tel,
          consumer_information.password, consumer_information.email,
          consumer_information.address);
  fclose(fp);
  printf("\n修改成功! ");
  return;
}

void changes_consumer(char user_id[11]) {

  int choose;
  int i = 1;

  do {
    printf("1. 修改电话号码\n2. 修改账户密码\n3. 修改邮箱\n4. 修改收货地址");
    printf("\n请输入对应操作编号: ");
    printf("\n------------------------------");
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
      i = 0;
    }
  } while (i == 0);

  return;
}

int main() {

  char user_id[11] = "AB1234";
  changes_consumer(user_id);
  return 0;
}
