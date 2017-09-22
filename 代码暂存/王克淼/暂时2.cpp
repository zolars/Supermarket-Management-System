// Name: add_goods_admin.h
// Author: 王克淼
// Date: 2017-09-13
// Language: C
// Features: 完成"商品添加"功能的模块.
// Modules:
//   - stdio.h
//   - string.h
//   - stdlib.h
//   - ctype.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void log_out();
void check_information();
char new_shop_id[11];             // 新商品超市编号 
char new_goods_id[11];            // 新商品商品编号
float new_unit_price;             // 新商品零售价格
float new_in_price;               // 新商品进货价格
int new_sales_volume;             // 新商品销量
int new_goods_in_stock;           // 新商品存货
float new_discount_price;         // 新商品折扣价
char new_discount_begin_time[25]; // 新商品折扣开始时间
char new_discount_end_time[25];   // 新商品折扣结束时间 
		
typedef struct {
  char goods_id[11];            // 商品编号
  float unit_price;             // 零售价格
  float in_price;               // 进货价格
  int sales_volume;             // 销量
  int goods_in_stock;           // 存货
  float discount_price;         // 折扣价
  char discount_begin_time[25]; // 折扣开始时间
  char discount_end_time[25];   // 折扣结束时间 
		
} STU_add_goods;


 STU_add_goods add_goods[100];
  int database_add_goods(char user_id[11]) {
  // 声明读取文件所需指针
  FILE *fread;

  char file_name[300] =
      "/Users/zolar/OneDrive - Queen Mary, University of "
      "London/Project/Supermarket-Management-System/"
      "Supermarket-Management-System/database"; // 该字符串用于处理文件名

  strcat(file_name, "/shop_index/"); // 加入路径"/goods_information/"

  // 处理文件名
  strcat(file_name, user_id);
 
  // 打开特定的订单数据文件
  if ((fread = fopen(file_name, "a+")) == NULL) // 判断文件是否存在及可读
  {
    printf("You have not sold anything.\n");
    return -1;
  }

  // 输入商品信息
  while(1){
    check_information();
   	 
    //进一步确认信息 
     int op1;
     int op2;
     int i;
    do {
    printf("\n------------------------------\n");
    printf("1. 确认发布商品信息\n2. 重新修改商品信息\n3. 取消添加商品信息\n");
    printf("请输入对应操作编号: ");
    scanf("%d", &op1);
    printf("\n------------------------------\n");
    switch (op1) {
    	
	case 1:
    fprintf(fread, "%s %f %f %d %d %f %s %s",
           new_goods_id,            // 商品编号
           new_unit_price,          // 零售价格
           new_in_price,            // 进货价格
           new_sales_volume,        // 销量
           new_goods_in_stock,      // 存货
           new_discount_price,      // 折扣价
           new_discount_begin_time, // 折扣开始时间
           new_discount_end_time    // 折扣结束时间
    );
    printf("添加商品信息成功! \n");
    printf("是否继续添加商品? \n"); 
    printf("1.是       2.否\n");
    do{
		printf("1.是       2.否\n");
		scanf("%d",&op2);
		printf("\n------------------------------\n");
		switch(op2){
			case 1:
			  break;
			case 2:
			  log_out();
			break;
			  default:
        	  printf("输入编号无效，请重新输入! \n");        //纠错机制 		
	          		}
       }while(1);
    
    
      break;
           
    case 2:
                  
      break;            //重新回到输入信息页面
      
    case 3:
      log_out();         //进入退出页面
      break;
      
    default:
      printf("输入编号无效，请重新输入! \n"); //纠错机制 
    
    }
  } while (1);
}
    	
 
  }



//退出页面
void log_out() {
  printf("\n------------------------------\n");
  printf("感谢您本次的使用，再见! ");
  printf("\n------------------------------\n");

  return;
}


//输入信息并判断是否正确
void check_information() {

    printf("请依次输入新增商品信息\n");
    
    
    printf("商品编号: \n");                // 输入商品编号并纠错 
    scanf("%s",new_goods_id);
    
    
    	while(1)
	{
		int i=0;
		int n=1;
		int s,t;
		
		for(i=0;new_goods_id[i]!='\0';i++) 
		{
		  s=isalpha(new_goods_id[i]);
		  t=isdigit(new_goods_id[i]);
		  if(i==0||i==1) 
			{
				if(s==0)
				n=0;
			} 
		  else if(i==2||i==3||i==4||i==5) 
			{
				if(t==0)
				n=0;
			} 
	      else
			n=0;
		}
		
		if(i==6&&n==1)
		break;
		else
		{
		printf("您输入的商品编号不合法，请重新输入: \n");
		scanf("%s",new_goods_id);
	    }
	}    
	
	
    int i = 0;                             
    while (!feof(fread)) {                     //检查商品是否重复 

    fscanf(fread, "%s %f %f %d %d %f %s %s",         // 读取数据
           add_goods[i].goods_id,                    // 商品编号
           &add_goods[i].unit_price,                  // 单价
           &add_goods[i].in_price,                    // 进价
           &add_goods[i].sales_volume,                // 销量
           &add_goods[i].goods_in_stock,              // 存货
           &add_goods[i].discount_price,              // 折扣价
           add_goods[i].discount_begin_time,         // 折扣开始时间
           add_goods[i].discount_end_time            // 折扣结束时间
    );
    
    if(add_goods[i].goods_id==new_goods_id){
   		printf("您输入的商品已经存在，请重新输入: ");
    	scanf("%s",new_goods_id);
		i=-1;                                          //重新开始循环 
        }
    i++;
  }

    printf("零售价格: \n");            // 输入单价并纠错 
    scanf("%f",new_unit_price);
         while (new_unit_price<=0)		 { 			
         printf("您输入的价格不合法，请重新输入: ");
         scanf("%f",new_unit_price);        
		 }
    
    printf("进货价格: \n");          // 输入进价并纠错 
    scanf("%f",new_in_price);
         while (new_in_price<=0){			
         printf("您输入的价格不合法，请重新输入: ");
         scanf("f",new_in_price);
 		 }
 		 
    printf("销量: \n");                // 输入销量并纠错 
    scanf("%d",&new_sales_volume);
    while (new_sales_volume<0){			
         printf("您输入的销量不合法，请重新输入: ");
         scanf("%d",&new_sales_volume);
         } 
         
    printf("存货: \n");                 // 输入存货并纠错 
    scanf("%d",&new_goods_in_stock);
         while (new_goods_in_stock<=0){			
         printf("您输入的价格不合法，请重新输入: ");
         scanf("f",&new_goods_in_stock);
 		 }
    printf("折扣价: \n");               // 输入折扣价格并纠错 
    scanf("%f",new_discount_price);
         while (new_discount_price<=0){			
         printf("您输入的价格不合法，请重新输入: ");
         scanf("%f",new_discount_price);
 		 }
    printf("折扣开始时间: \n");        // 输入折扣开始时间并纠错 
    printf("折扣结束时间: \n");         // 输入折扣结束时间并纠错 
}         

