//������� ������������� , 2014030056

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 100 
#define INPUT_NAME "datain.txt" 
#define OUTPUT_NAME "dataout.txt" 

/*Structures declaration*/

struct material
{
   struct product *code_ptr ; // (part) (product code)
   int number_of_materials_needed ;// (quantity) �������� ������� (�� ��������� ��������) ��� ���� �� ����� ��� ����������� ��� �� ������� ���� ������� ��� �������� ������.        
};

struct product
{      
   int product_code;  // (code) �������������� ������� ��� ������  (>=0) 
   char *name_of_product;//  (name)�� ����� ��� ������ (������������� ����� ����).
   int order_request; // (needed) ������� ��� �������� ��� ��� ���������� (�� ��� �������� ������ ���� =0 )
   int number_of_products_in_stock; // (nPieces) ��� �������� ������� ��� ������ ���� ������� (>=0).      
   struct material *usage; // (usage) ������� �� ��� ���� ��� �������� ����� struct material (���������� ��� ����� ��� ��� �������� ��� ������ ��� ��� ���������)
   int number_of_composite_materials; // (nUses) ��� ����� ����� ��� ���� number_of_composite_materials = 0
}; 

/*Prototype declaration*/

void free_products_list (struct product * ,int); // �� ������������� ��� ����� ��� ���������� �� ��� malloc
struct product * data_registration (struct product *,FILE *,int) ;  // �������� ��������� ��� ������ ��� ���� ��������� ������ ��� ������� ���� ������� �����.
void data_output (struct product *,int) ;// ������� ������� ������
void needed_materials (struct product product,int); // A recursive function that calculates the total number of products needed for the order (dataout # units needed)

int main (void) // ������ ����� ��� ������������
{    
/*������ ����������*/
    
char choice_name [MAX_NAME_SIZE] ; // To ����� ��� ������ ��� �� ������� � ������� ��� �� ��� ������������
struct product *list_of_products ; // ������ ����� ��� �� �������� �� ����� ��� �� �������� ����
FILE *fp ; // ������ �������
int number_of_products; // ������� ��������� (������ ������� ��� datain)
int i,j ,menu_choice ,searched_product_place; // ��� for loop, ������� �����, � ���� ��� ��������� ��� ������ � ������� �� ��� ��� ������ �����   
int open_cnt=0, out_cnt = 0 ,pr_cnt=0, max_materials = 0; // ������� ����� ����� ������ �� ������., ������� ����� ����� ����� � ������� ��� ������� , �������� ��� �� ������ places,�������� ��� ������� ������ ��������� ���������
int *places; // � ������� ����� �� ����������� ��� ������ (i) ��� ��������� �� �������� ����� ������� �� ��� ������ ��� ��������� ������ ���� (��� �� ������ �������� ����� , ���� ��������� , ������ ����)

if  ((fp = fopen(INPUT_NAME,"r"))== NULL ) // ������� �� ������ product_datain ��� ������� ��� �������� ���� �� �������
{
   printf ("Error while opening the required file.\n");
   printf ("Check that your file is in the same directory as the executable file.\n");
   system ("PAUSE"); 
   exit (0) ;          
}
fscanf (fp,"%d\n",&number_of_products);  // ���������� ��� ������ ��� ���������
places = (int * ) malloc (number_of_products * sizeof(int)); // �������� ������ ��� �� ������ places

/*���������� �����*/

printf ("\nWelcome to our official product management software:\n\n");
printf ("===============================================================================\n");
printf ("Choose one of the following options (1-5):\n");
printf ("1.Read the input data file (It must be in the same directory as the executable file\n");
printf ("2.Show all of the available products\n");
printf ("3.Show the composite materials of a specified product\n");
printf ("4.Generate the output file (It is in the same directory as the executable file\n");
printf ("5.Close the software\n"); 
printf ("===============================================================================\n");

while (1) // �� ����� �� ��������������� ����� �� �������������� � ������ ������� , ������ � ������ ��� �� ���������
{   
   printf ("\nEnter your choice: ");  
   do
   {
      scanf ("%d",&menu_choice); // ������� �����������  ��� ����� 
      switch (menu_choice)
      {
         case 1: // �������� ��� ������� ������� datain.txt
              if (open_cnt==0) // � �������� ��� ������� ����������� �� ����� ��� ����
              {
                 open_cnt++; // ���� ���� ��� �� ��������� �� ������ 
                 list_of_products = data_registration (list_of_products,fp,number_of_products); // ���������� ��������� ��� �� ������ ���� ��������� ����� 
                 if (fclose (fp) !=0) // �������� ��� ������� ���������
                 {    
                   printf ("Error while opening the required file.\n");
                   printf ("Check that your file is in the same directory as the executable file\n");
                   system ("PAUSE"); 
                   exit (2) ;        
                 }         
                 printf ("\nReading the file...........................\n");
                 printf ("The import of the input data file is complete!\n");
              }
              else printf ("You have already imported the file.\n"); // �� ��������� ��� ���� ���������� ����������� ��� ���� � �������� ��� �������.   
              break;       
         case 2:  // �������� ���� ��� ����� ������
              if (open_cnt>0) // �� � ������ ��� �� ������� ��� ������� ���� ���������� ��� ����
              {
                 printf ("The available products are :\n");
                 printf ("Product - Number in stock\n");
                 for (i=0;i<number_of_products;i++)
                    printf ("%s - %d\n",list_of_products[i].name_of_product,list_of_products[i].number_of_products_in_stock);
              } 
              else printf ("You must open the file first by choosing option 1.\n"); // �� � ������ ��� �� ������� ��� ������� ���� ���������� ����� ����
              break;   
         case 3: // �������� ��� �������� ���� ������ ������
              if (open_cnt>0) // �� � ������ ��� �� ������� ��� ������� ���� ���������� ��� ����
              {
                 searched_product_place = -1 ; // ������ ���� ��� , � ����� �� ���������� �� ��������� ��� � ���� ��� �� ��������
                 printf ("Input the name of the product you wish to view (The first letter must be capital):");
                 scanf("\n%s",choice_name); // �������� ��� �������� ��� ������ (\n%s : ��� �� ��������� ��� �� buffer o ���������� new line ��� ��������.)                
                 for (i=0;i<number_of_products;i++)
                 {
                     if (strcmp(choice_name,list_of_products[i].name_of_product) ==0) // �� �� ����� ��� �������� � ������� ����� ���� �� ������  
                     searched_product_place = i ;  // ���������� ��� ����� ��� ��������� �� ������ , ��� ������ �� ����� �������� � �������              
                 }                     
                 if (searched_product_place == -1)  // �� ��������� ��� ��� ������� �� ����� , � ��������� searched_product_place �������� ��� ���� -1
                 { 
                     printf ("No product named %s is found.\n",choice_name);
                     system ("Pause");
                     return 0; 
                 }
                 if (list_of_products[searched_product_place].usage !=NULL) // �� �� ������ ��� ����� ����� ���
                 {
                     printf ("%s has the following materials:\n\n",list_of_products[searched_product_place].name_of_product);                          
                     printf ("Product - Quantity available\n");                         
                     for (j=0;j<list_of_products[searched_product_place].number_of_composite_materials;j++)
                     {
                        if (list_of_products[searched_product_place].usage[j].code_ptr != NULL)  // �� ��������� ��� �� ��������� ������ ��� ����������� �� ������ ��� �� ������ (���� ����� ���� NULL ��� ��� data registration)
                           printf ("%s - %d\n",list_of_products[searched_product_place].usage[j].code_ptr->name_of_product,list_of_products[searched_product_place].usage[j].code_ptr->number_of_products_in_stock);
                     }   
                 }                   
                 else printf ("The %s product has no composite materials.\n",choice_name); // �� �� ������ ����� ����� ���
              }
              else printf ("You must open the file first by choosing option 1.\n");          
              break;   
         case 4:  // ���������� ��� ������� ������ dataout
              if (open_cnt>0) // �� � ������ ��� �� ������� ��� ������� ���� ���������� ��� ����
              {                            
                 if (out_cnt == 0) // �� ��� ���� ����� ������� ��� ������� ����� ����
                 {            
                    out_cnt++; // ��������� ���� ���� ��� ��������� �� ������ ������                                                                    
                    for (i=0;i<number_of_products;i++) // ������� ��� ������� ���� ��� ��������� ������ (���� ��� ����� �� ������ ��������)
                       if (max_materials < list_of_products[i].number_of_composite_materials) max_materials = list_of_products[i].number_of_composite_materials;
                                                              
                    while (max_materials>=0) // �� ����������� ��� ������ (i) ��� ��������� ��� ������ places �� �������� ����� ������� �� ��� ������ ��� ��������� ������(number_of_composite_materials) ���� (��� �� ������ �������� �����,���� ���������,������ ����)
                    {
                       for (i=0;i<number_of_products;i++)                       
                          if (list_of_products[i].number_of_composite_materials == max_materials)    
                          places[pr_cnt++] = i; 
                       max_materials-- ;      
                    }                    
                   
                    for (pr_cnt=0;pr_cnt<number_of_products;pr_cnt++) // ������� ��� ���������� ��������� ��� ��� �� �������� ,���� ����� ��� �� ������ �������� , ��� ���� ��� �� ���������
                       needed_materials (list_of_products[places[pr_cnt]],list_of_products[places[pr_cnt]].number_of_composite_materials-1); 
                                          
                    data_output (list_of_products,number_of_products); // ������� ��� ������� ������
                    printf ("The output file is generated.\n");
                    free (places); // ����������� ��� ����� ��� ���������� ��� ��� ������ places
                 }
                 else printf ("The output file is already generated.Check the software folder.\n");
              }
              else printf ("You must open the file first by choosing option 1.\n"); 
              break;
         case 5: // ����������� ������������
              printf ("The software is terminated.\n");
              free_products_list (list_of_products,number_of_products); //  ������������ ������ ��� ���������� ��� ��� malloc               
              system ("Pause");
              exit (0) ; 
              break;              
         default: // ��������� ��� ��������� ����� ����
              printf ("Enter 1,2,3,4 or 5.\n");
              break;   
       }
} while ((menu_choice<1) || (menu_choice>5)); // ������ � ������� ��� ������ �� ����� ������� ��� �� 1 ��� ��� �� 5.
}
} // ����� main

/*�����������*/

void needed_materials (struct product product,int number_of_comp_materials) // A recursive function that calculates the total number of products needed for the order (dataout # units needed)
{
if (product.usage != NULL) // �� ��� ����� ����� ���
{                     
   if (number_of_comp_materials < 0);  // �� ���������� ��������� 
   else
   {
      if (product.usage[number_of_comp_materials].code_ptr != NULL)  // �� ��������� ��� �� ��������� ������ ��� ����������� �� ������ ��� �� ������ (���� ����� ���� NULL ��� ��� data registration)
         product.usage[number_of_comp_materials].code_ptr->order_request += product.order_request * (product.usage[number_of_comp_materials].number_of_materials_needed);  
      
      needed_materials (product,number_of_comp_materials-1);       
   }
}     
}        

struct product * data_registration (struct product *product_data,FILE *fp,int number_of_products ) // �������� ��������� ��� ������ ��� ���� ��������� ������ �������� �����.
{     
int number_of_orders,order_code ; // number_of_orders ������ ������� �������� ������ ��� datain (���� �������� ����� �����������) ,� ���������� ��������� ��� ������ ��� ���� �����������
int choice,i,j,ptr_cnt=0,cnt=0,nul_cnt=0; // number_of_products ������� ���� ��� ��������� , choice ������� ��� ����� �,j ��� for loops , �������� ��� ��� ������ temp_codes_ptr , �������� ��� ��� ������ temp_codes 
int temp_codes[200] ; // ���������� ��������� ���� �������� ��� ��������� ��������� �� 2 3 (Wheel) 4 5 (Engine) 6 7 1 (Car)
struct product * temp_ptr_codes[200]; // ���������� ��������� ���� ������� ��� ��������� ��������� (part)
char buf_name [MAX_NAME_SIZE]; // ��������� ���������� ��� �������� ��� ���������

product_data = (struct product *) malloc (number_of_products * sizeof(struct product)) ; // ���������� ��� �������� ����� ��� �� �������� �� �������� ��� ������
for (i=0;i<number_of_products;i++) // ��� ���� ���� ��� i ������ ��� ������.
{
   fscanf (fp,"%d %s %d %d",&product_data[i].product_code,buf_name,&product_data[i].number_of_products_in_stock,&product_data[i].number_of_composite_materials);
   product_data[i].name_of_product = (char *) malloc ((strlen(buf_name)+1) * sizeof(char)) ;
   strcpy (product_data[i].name_of_product,buf_name) ; 
   product_data[i].usage = (struct material *) malloc (product_data[i].number_of_composite_materials * sizeof(struct material)) ;  // ���������� ��� �������� ����� ��� �� �������� �� �������� ��� ������ ���� / ��������� ��������� ��� ��������� �� �����
   if (product_data[i].number_of_composite_materials != 0 ) //  ��� �� ����� ��� ����� ����� ��� 
   {
      for (j=0;j<product_data[i].number_of_composite_materials;j++) // �������� ��� ����� ������� - ��������                                                       
         fscanf (fp," %d %d",&temp_codes[cnt++],&product_data[i].usage[j].number_of_materials_needed); // ���������� ��� ������� ��� ���������� ��������� �� ������          
                   
      fscanf (fp,"\n"); // �� ������� ����� ��� ������                    
   }
   else // ��� ����� ����� ��� ���� :
   {
      product_data[i].usage = NULL ; // � ������� usage ��� ���������� �� ������� �������      
      fscanf (fp,"\n"); // � ����� fscanf ����� ��� ��� �������� ���� ��� ��������� ��� , ��� ����� ���� ��� ������� ����� ���������� �����    
   }
}
for (i=0;i<cnt;i++) // '���������' �� ������� �� ������� ��� �������� �������� ���� �� ��� ������
{
   nul_cnt = 0 ;// ������� ��� ����� ��� � ������� �������� ��� ������ ��� ������� . �� �������� �� ����� nul_cnt = number_of_products , ������ � ������� ��� ��������� ������ ��� ������� ��� ������.
   for (j=0;j<number_of_products;j++)
   {
      if (temp_codes[i] == product_data[j].product_code) temp_ptr_codes[ptr_cnt++]= &product_data[j]; // �� � ������� ��� temp_codes[i] ����� ���� �� ���� ��������� , ���� ������������ � ��������� ��� ��������� ���� temp_ptr_codes
      else if (temp_codes[i] != product_data[j].product_code) nul_cnt++;
      if (nul_cnt == number_of_products) temp_ptr_codes[ptr_cnt++] = NULL;
   }
}

ptr_cnt=0;
for (i=0;i<number_of_products;i++) // �������� ��� ������� ��� ��� ������ ����� ������� code_ptr ��� ��������� ����� usage
{
   if (product_data[i].number_of_composite_materials !=0) // ����������� ��� ������ ����  
      for (j=0;j<product_data[i].number_of_composite_materials;j++) product_data[i].usage[j].code_ptr = temp_ptr_codes[ptr_cnt++]; // ���������� ��� �������� ���� ������� ����� (����� ��������� ��� ����� �� ��� ���� ����� ��� ������������� �� �������� ��� ������� ����� , ������������� ��� ���� ������)                                                 
}

for (j=0;j<number_of_products;j++) product_data[j].order_request = 0 ; // ����� ������ ���� 0 �� ��� �� ����� order_request (needed)

fscanf (fp,"%d\n",&number_of_orders); // �������� ��� ���������� ��� ������ ��� �����������

for (i=0;i<number_of_orders;i++) // ���������� ��� ����������� , ������ ��� order_request
{
   fscanf(fp,"%d ",&order_code); // �������� ��� ������� ��� �������� ��� �� ���� �������� ��� �������� �����  
   for (j=0;j<number_of_products;j++)   
      if (order_code == product_data[j].product_code) fscanf(fp,"%d\n",&product_data[j].order_request);
}
return product_data;   
}

void data_output (struct product *product_data,int number_of_products) // ������� ������� ������
{
FILE *fp2 ; 
int i ; 

if ((fp2 = fopen (OUTPUT_NAME,"w"))== NULL) // ������� ��� ������� ��� �������
{
   printf ("Error while creating the required file.\n");
   printf ("Check that your hard drive has the required space.\n");
   system ("PAUSE"); 
   exit (1) ;          
}   
fprintf (fp2,"Number of material types: %d\n",number_of_products); 
for (i=0;i<number_of_products;i++) 
    fprintf (fp2,"%d/%s - %d units in stock - %d units needed\n",product_data[i].product_code,product_data[i].name_of_product,product_data[i].number_of_products_in_stock,product_data[i].order_request);    

if (fclose (fp2) !=0) // �������� ��� ������� 
{    
    printf ("Error while opening the required file.(You may have to run the software with administrator rights.)\n");
    printf ("Check that your file is in the same directory as the executable file.\n");
    system ("PAUSE"); 
    exit (2) ;        
}
}

void free_products_list (struct product *product_data,int size) // �� ������������� ��� ����� ��� ���������� �� ��� malloc
{     
   int i;   
   for (i = 0; i < product_data[i].number_of_composite_materials; ++i)
   {    
      if (product_data[i].usage != NULL)
         free(product_data[i].usage);
   }
   
   for (i = 0; i < size; ++i) // size = number_of_materials
   {    
      if (product_data[i].name_of_product != NULL)
         free(product_data[i].name_of_product);
   }    
   free(product_data);   
}




