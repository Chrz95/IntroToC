//������� ������������� , 2014030056

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_SIZE 6

/*Prototype declaration*/

void conv_num_to_word (int,char word[]);
int common_char_general(char word1[],char word2[]);
int common_char_same_place(char word1[],char word2[]);
int duplicate_digits (char a[]);
char error_check_char (char);
int power_calc (int,int) ; 

int main ()
{
	/*������ ����������*/
	
	char repeat_or_not , print_or_not ; //�� ����� ����������� repeat_or_not = � �� ��� repeat_or_not = � . ������ ��� print_or_not ��� ��� �������� ��� �������� �������.	
	int digit_number , secret_number , guess_number ;  // ������� ������ (n) , �������� ������� (secret) , ������� ��� �� ������� � ������� (guess) ����������
	int i ;  // ��� ��������� ��� ��� ������ ����������� ���� for loop
	int attempt_times = 0 ; // �� ����� ��� ���������� �� �������� � ������� ��� ������� ������
	char guess_string[NUMBER_SIZE] , secret_string[NUMBER_SIZE] ; // �� ������� ���� �� ������������ �� ������� guess ��� secret , ���� ����������� �� �������������
	
	/*������������ ��� Rand()*/
	
	srand(time(NULL));
	
	/*����������� ������*/
	
	printf ("Welcome to an amazing game of Mastermind!\n\n");
		
	/*�������� ������� ������*/	
	
	printf ("How many digits do you want to use? (You can choose 3,4 or 5) : ");
	do //������� �� ��������� ����������� ����� ��� digit_number (������ ������� ����� ��� 3,4,5)
	{	
		scanf ("%d",&digit_number);									
		if ((digit_number <3) || (digit_number >5)) 
		      printf("Invalid value. Please input 3,4 or 5.\n");
	 			
	} while ((digit_number <3) || (digit_number >5));
	
	/*������� ��� �� �� ������������ �� ����������� � ���*/
    	
	printf ("Do you want to allow duplicate digits? (Y for Yes,N for No):");
	repeat_or_not = error_check_char (repeat_or_not) ; //�������� ��� ������� �� ��������� ����������� ����� repeat_or_not(������ ���������� ����� ��� Y,N � ������� ���)
    
	/*���������� �������� ������� (secret)*/  
			
	do //������� ���������� ������ ��� ������� ������ (�� ��� ������������ ����� ����� ���� �������� , ���� �� ��������� ������� ���� ���� ������� ����� �� �������� ������� �� �� ����� ����� ��� ����� ���� �����)
    {        
        do // � ������� �� ��������������� ��� �� ������������� ���� ���� secret number ����� � ������� �� ���� n ����� (��� :  10^(n-1) < secret <10^n)
        {    
              secret_number = rand()%(power_calc(10,digit_number)) ; // �� �������� ���� ������� ���������� ��� 10^n 
        } while (secret_number< power_calc(10,digit_number-1));
        
    conv_num_to_word (secret_number,secret_string); // ��������� �������� ������� �� ������������� KAI ���������� ��� ��� ������ secret_string
       	 
    } while (duplicate_digits(secret_string) && (repeat_or_not == 'N') ); 

    /*������� ��� �������� �������*/
	
	printf ("Do you want to print the secret number? (Y for Yes,N for No): ");
	if ((error_check_char (print_or_not)) == 'Y')//�������� ��� ������� �� ��������� ����������� ����� print_or_not(������ ���������� ����� ��� Y,N � ������� ���)
        printf("The Secret Number is %d. \n",secret_number) ;    

	/*�������� ������� ��� ������ (guess)*/
    
    do // ���� �� loop �� ��������� ��� ��� ��������� ��� ������� 4,5 (������ ��� �������� ��� �� �������� ��� guess �� �� secret) ����� �� �������� � ������� ��� ������� ������
    {
        printf("\nGive a guess! (If you wish to quit,enter a negative number):");
        
        do //������� ���������� ������ ��� �������� ������ (�� ��� ������������ ����� ����� ���� �������� , ���� �� ��������� ������� ���� ���� ������� ����� �� �������� ������� �� �� ����� ����� ��� ����� ���� �����)
        {                     
                     
               do // ������� ������ ��� ��������� �������
               {
                  scanf ("%d",&guess_number);   
                  if (guess_number < 0 ) // Guess number is a negative number (����� �� ����������)   
                  {
                     printf ("\nYou choose to exit the game");
                     printf ("\nThe secret number was %d",secret_number);
                     printf ("\nYou have tried %d times.\n",attempt_times );
                     system ("PAUSE") ; 
                     return 0 ; 
                  }
                    
                  if ((guess_number > power_calc(10,digit_number)) || (guess_number < power_calc(10,digit_number-1))) // ������� �� ��������� ��� � guess ���� ����� �����
                     printf("You have entered a number with wrong digits.\nYou should enter a number with %d digits. Try again.\n",digit_number);
                                       
               } while ((guess_number > power_calc(10,digit_number)) || (guess_number < power_calc(10,digit_number-1))) ; // ����� �� ���� ��� ����� ������ ������ .
       
               conv_num_to_word (guess_number,guess_string);
               
               if (duplicate_digits(guess_string) && (repeat_or_not == 'N'))
                     printf("You have entered a number with duplicate digits.\nYou choose not to allow duplicate digts. Try again.\n");                                                
                                                       
       } while (duplicate_digits(guess_string) && (repeat_or_not == 'N')); // ����� � guess �� ��� ���� ����� ����� �� ���� ��� �����������
   
   	   if (common_char_general(secret_string,guess_string) <= (digit_number /2)) // ������ ������� �� �� ���� ���� ������� � �������
           printf ("Not so good guess..."); 
       else if ((common_char_general(secret_string,guess_string) > (digit_number /2)) && (common_char_same_place (secret_string,guess_string)<= (digit_number /2)))
           printf ("Good guess!"); 
       else if ((common_char_same_place(secret_string,guess_string) > (digit_number /2)) && (guess_number != secret_number))
           printf ("You are in the right path!"); 
       else if	(guess_number == secret_number)
	       printf ("Excellent! You found it!"); 
            
       printf ("\nThe number of total digits found is : %d.\n", common_char_general(secret_string,guess_string));
	   printf ("The number of total digits found in correct positions is : %d.\n", common_char_same_place(secret_string,guess_string));
	   attempt_times++ ; // ������� �������e��� , � ������ ��������� ���� ���� ��� � ������� ������� ��� ������
	
	} while (guess_number != secret_number); // M���� �� �������� � ������� ��� ����� ������
	
    /*T����� ����������*/
		
	printf ("\nThe mystery number is found : %d ",secret_number);
	printf ("\nYou have tried %d times.\n",attempt_times );
	system ("PAUSE");
	return 0 ;
}

/*�����������*/

void conv_num_to_word (int x,char word[]) //� ��������� ���� �� ���������� ��� (3/4/5 �����) ������ �� �������������.
{
     int i ,power =4 , cnt = 0 ;  // i : ��� ��� for , power o ������� ��� ������� ��� 10 , cnt ��� ��������� ��� ������� ��� ������ ��� �����������
     int divider = power_calc(10,power) ; //��������� �� ��������� �� �� 10^4 = 10000
         
     while (divider > x) // ��� �� ��� ����������� ������� 0 ���� ���� ��� ������� , ����� �� ��������� �� ����� ������ � ������� �� ���������� �� ������ ��� 10 , ��� ����� ��������� ��� . 
           divider = power_calc (10,--power);
      
      for(i=0;power>=0;i++)//��������� �� ����� ��� ������� 
      {    
           cnt++;                               
           word[i] = (x / divider) + 48 ; // + 48 : ��� ��� ��������� ��� ������� ���� ���������� ��������� ��� , ������� �� ��� ������ ASCII.
           x %= divider ; // ����� ��� � ���� ��� �� �� �������� ��� ������������ ���������
           divider = power_calc(10,--power); // ������� ��� ������ ��� ������� ��� 10                   
      }
      word [cnt] = '\0';
}

int common_char_general(char word1[],char word2[]) //� ��������� ���� �� ������� : ������� ���������� ��� ��� ���������������� , word1 : secret , word2 : guess
{ 
    int i,j,common_digits = 0 ; // common_digits : ������� ������ ������
    int digits1 [10] = {0,0,0,0,0,0,0,0,0,0}  ; 
    int digits2[10] = {0,0,0,0,0,0,0,0,0,0}  ; 
       
    for (i=0;word1[i] != '\0';i++) // ������� ����� ����� ������� ���� ����� (0,1,2,....9) ��� ��������� ��� ������ ��� ����� ��� ���������� ���� ��� ������ digits1
    { // �.� �� 9 ������� 3 ����� ���� ������ 29499 , ��� digits1[9] = 3 ;   
           for (j=0 ; j <10 ; j++)
           {
               if (word1[i] == (j+48)) // j + 48 : o ���������� ���������� ��� ������� j
               digits1[j]++; 
           }   
    }
    
    for (i=0;word2[i] != '\0';i++) // ������� ����� ����� ������� ���� ����� (0,1,2,....9) ��� ��������� ��� ������ ��� ����� ��� ���������� ���� ��� ������ digits2
    {    
           for (j=0 ; j <10 ; j++)
           {
               if (word2[i] == (j+48))
               digits2[j]++; 
           }   
    } 
    
    for (i=0 ; i<10 ; i++) // ��������� ��� ����� ��� ��� �������
    {
           if ((digits1[i] != 0) && (digits2[i] != 0)) // �� ��� �� ��� ������� ����� ���� �� ����� ����������� ��� ����
           {
              if (digits1[i] > digits2[i])
                 common_digits += digits2[i] ; 
              else if (digits2[i] > digits1[i])
                 common_digits += digits1[i] ;
              else               
                 common_digits += digits2[i] ;                            
           }       
    }         
    return common_digits ;
}

int common_char_same_place(char word1[],char word2[]) //� ��������� ���� �� ������� ���� ������� ���������� ���� ���� ���� , word1 : secret , word2 : guess
{ 
    int i,j,cnt= 0 ; 
    for (i=0;word1[i] != '\0';i++)
    {
           if (word1[i] == word2[i]) // ������ �� ����������� ������ ��� ������� �� ����� ����
              cnt++ ;             
    }
return cnt;
}

int duplicate_digits (char word[]) // �� ������� ��� ������ (�������������) , ��� �� ��� ���� ����� ����� ��� �� ���������� 1 �� ���� ��� 0 �� ��� ���� 
{
    int i,j;
    for (i=0 ; word[i] != '\0' ; i++)
    {
            for (j=i+1;word[j] != '\0';j++)
            {
               if (word[i] == word[j])
               return 1;             
            }     
    }
    return 0; 
}

char error_check_char (char b) // ��������� ���� �� b , � �������� ������ �� ����� ��� (Y) � ��� (N)
{
    do //������� �� ��������� ����������� ����� (������ ���������� ����� ��� Y,N � ������� ���)
	{	
		    scanf ("\n%c",&b); // \n%c :����������� � ���������� \n ��� �� buffer ,���� ��������� ��� ��� ����������� scanf ��� ���� ������������ � ���������� ��� ���������
		    if ((b != 'Y') && (b != 'N')) 
               printf("Invalid value. Please input Y or N.\n");		    
	} while ((b != 'Y') && (b != 'N'));
	return b;
}   

int power_calc (int base ,int power) // ����������� �������� �� �� �������� ������
{
    int i ,result = base ; 
        
    if (power > 0) 
    {
       for (i=1 ;i<power;i++)
          result *= base ; 
    }
    else if (power == 0)
       return 1;
        
    return result ;
}    


