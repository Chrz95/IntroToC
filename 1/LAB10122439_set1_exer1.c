//Χρήστος Ζαχαριουδάκης , 2014030056

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
	/*Δήλωση μεταβλητών*/
	
	char repeat_or_not , print_or_not ; //Αν θέλει επαναλήψεις repeat_or_not = Υ αν οχι repeat_or_not = Ν . Ομοίως για print_or_not για την εκτύπωση του μυστικού αριθμού.	
	int digit_number , secret_number , guess_number ;  // Αριθμός ψηφίων (n) , Μυστικός αριθμός (secret) , Αριθμος που θα εισάγει ο παίκτης (guess) αντίστοιχα
	int i ;  // Μια μεταβλητή για τον έλεγχο επαναλήψεων ενός for loop
	int attempt_times = 0 ; // Οι φορές που προσπάθησε να μαντέψει ο παίκτης τον μυστικό αριθμό
	char guess_string[NUMBER_SIZE] , secret_string[NUMBER_SIZE] ; // Οι πίνακες οπου θα αποθηκευτουν οι αριθμοί guess και secret , αφου μετατραπούν σε αλφαριθμητικα
	
	/*Αρχικοποίηση της Rand()*/
	
	srand(time(NULL));
	
	/*Καλοσώρισμα παίκτη*/
	
	printf ("Welcome to an amazing game of Mastermind!\n\n");
		
	/*Εισαγωγή αριθμού ψηφίων*/	
	
	printf ("How many digits do you want to use? (You can choose 3,4 or 5) : ");
	do //Ελεγχος σε περίπτωση λανθασμένης τιμής του digit_number (δηλαδη αριθμοι εκτός του 3,4,5)
	{	
		scanf ("%d",&digit_number);									
		if ((digit_number <3) || (digit_number >5)) 
		      printf("Invalid value. Please input 3,4 or 5.\n");
	 			
	} while ((digit_number <3) || (digit_number >5));
	
	/*Ελέγχος για το αν επιτρέπονται οι επαναλήψεις ή οχι*/
    	
	printf ("Do you want to allow duplicate digits? (Y for Yes,N for No):");
	repeat_or_not = error_check_char (repeat_or_not) ; //Εισαγωγή και ελεγχος σε περίπτωση λανθασμένης τιμής repeat_or_not(δηλαδη χαρακτήρες εκτός του Y,N ή αριθμοί κτλ)
    
	/*Δημιουργία μυστικού αριθμου (secret)*/  
			
	do //Ελεγχος επανάληψης ψηφίων στο μυστικό αριθμό (Αν δεν επιτρέπονται διπλα ψηφία αλλά υπάρχουν , τοτε θα παράγεται συνεχως ένας νέος αριθμος μεχρί να προκυψει αριθμός με τα σωστα ψηφια και χωρίς ίδια ψηφία)
    {        
        do // Ο βρόγχος θα επάναλαμβάνεται και θα δημιουργείται ένας νεός secret number μέχρι ο αριθμός να έχει n ψηφια (δηλ :  10^(n-1) < secret <10^n)
        {    
              secret_number = rand()%(power_calc(10,digit_number)) ; // Θα παραχθεί ένας αριθμός μικρότερος του 10^n 
        } while (secret_number< power_calc(10,digit_number-1));
        
    conv_num_to_word (secret_number,secret_string); // Μετατροπή μυστικού αριθμού σε αλφαριθμητικό KAI καταχώρηση του στο πίνακα secret_string
       	 
    } while (duplicate_digits(secret_string) && (repeat_or_not == 'N') ); 

    /*Ερώτηση για εκτύπωση αριθμού*/
	
	printf ("Do you want to print the secret number? (Y for Yes,N for No): ");
	if ((error_check_char (print_or_not)) == 'Y')//Εισαγωγή και ελεγχος σε περίπτωση λανθασμένης τιμής print_or_not(δηλαδη χαρακτήρες εκτός του Y,N ή αριθμοί κτλ)
        printf("The Secret Number is %d. \n",secret_number) ;    

	/*Εισαγωγή αριθμου του παίκτη (guess)*/
    
    do // αυτο το loop θα φροντίσει για την επανάληψη των βημάτων 4,5 (δηλαδή την εισαγωγή και τη σύγκριση του guess με το secret) μέχρι να μαντέψει ο παίκτης τον μυστικό αριθμό
    {
        printf("\nGive a guess! (If you wish to quit,enter a negative number):");
        
        do //Ελεγχος επανάληψης ψηφίων στο εισακτέο αριθμό (Αν δεν επιτρέπονται διπλα ψηφία αλλά υπάρχουν , τοτε θα παράγεται συνεχως ένας νέος αριθμος μεχρί να προκυψει αριθμός με τα σωστα ψηφια και χωρίς ίδια ψηφία)
        {                     
                     
               do // Ελεγχος ψηφίων του εισακτέου αριθμού
               {
                  scanf ("%d",&guess_number);   
                  if (guess_number < 0 ) // Guess number is a negative number (Θέλει να παραιτήθει)   
                  {
                     printf ("\nYou choose to exit the game");
                     printf ("\nThe secret number was %d",secret_number);
                     printf ("\nYou have tried %d times.\n",attempt_times );
                     system ("PAUSE") ; 
                     return 0 ; 
                  }
                    
                  if ((guess_number > power_calc(10,digit_number)) || (guess_number < power_calc(10,digit_number-1))) // Ελέγχος σε περίπτωση που ο guess έχει λάθος ψηφία
                     printf("You have entered a number with wrong digits.\nYou should enter a number with %d digits. Try again.\n",digit_number);
                                       
               } while ((guess_number > power_calc(10,digit_number)) || (guess_number < power_calc(10,digit_number-1))) ; // Μεχρι να έχει τον σωστο αριθμό ψηφίων .
       
               conv_num_to_word (guess_number,guess_string);
               
               if (duplicate_digits(guess_string) && (repeat_or_not == 'N'))
                     printf("You have entered a number with duplicate digits.\nYou choose not to allow duplicate digts. Try again.\n");                                                
                                                       
       } while (duplicate_digits(guess_string) && (repeat_or_not == 'N')); // Μέχρι ο guess να μην έχει διπλά ψηφία αν αυτο δεν επιτρέπεται
   
   	   if (common_char_general(secret_string,guess_string) <= (digit_number /2)) // Μήνυμα ανάλογα με το πόσο καλά μάντεψε ο παίκτης
           printf ("Not so good guess..."); 
       else if ((common_char_general(secret_string,guess_string) > (digit_number /2)) && (common_char_same_place (secret_string,guess_string)<= (digit_number /2)))
           printf ("Good guess!"); 
       else if ((common_char_same_place(secret_string,guess_string) > (digit_number /2)) && (guess_number != secret_number))
           printf ("You are in the right path!"); 
       else if	(guess_number == secret_number)
	       printf ("Excellent! You found it!"); 
            
       printf ("\nThe number of total digits found is : %d.\n", common_char_general(secret_string,guess_string));
	   printf ("The number of total digits found in correct positions is : %d.\n", common_char_same_place(secret_string,guess_string));
	   attempt_times++ ; // Αριθμός προσπάθeιων , ο οποίος αυξάνεται κάθε φορα που ο παίκτης εισάγει ένα αριθμό
	
	} while (guess_number != secret_number); // Mέχρι να μαντέψει ο παίκτης τον σωστό αριθμό
	
    /*Tελικό Αποτέλεσμα*/
		
	printf ("\nThe mystery number is found : %d ",secret_number);
	printf ("\nYou have tried %d times.\n",attempt_times );
	system ("PAUSE");
	return 0 ;
}

/*Συναρτήσεις*/

void conv_num_to_word (int x,char word[]) //Η συνάρτηση αυτή θα μετατρέπει τον (3/4/5 ψήφιο) αριθμό σε αλφαριθμητικό.
{
     int i ,power =4 , cnt = 0 ;  // i : για την for , power o εκθέτης της δύναμης του 10 , cnt μια μεταβλητή που μετράει τον αριθμό των επαναλήψεων
     int divider = power_calc(10,power) ; //Αρχίζουμε να διαιρούμε με το 10^4 = 10000
         
     while (divider > x) // Για να μην εμφανιστούν περιττά 0 στην αρχή του αριθμού , κάθως θα αναλύεται σε ψηφία πρέπει ο αριθμός να διαιρείται με δύναμη του 10 , που είναι μικροτερή του . 
           divider = power_calc (10,--power);
      
      for(i=0;power>=0;i++)//Ξεχωρίζει τα ψηφία του αριθμού 
      {    
           cnt++;                               
           word[i] = (x / divider) + 48 ; // + 48 : Για την μετατροπή του αριθμου στον αντίστοιχο χαρακτήρα του , σύμφωνα με τον κώδικα ASCII.
           x %= divider ; // Δίνει στο χ τιμή ίση με το υπόλοιπο της προηγούμενης διαίρεσης
           divider = power_calc(10,--power); // Μειώνει τον εκθέτη της δύναμης του 10                   
      }
      word [cnt] = '\0';
}

int common_char_general(char word1[],char word2[]) //Η συνάρτηση αυτή θα βρίσκει : κοινούς χαρακτήρες των δύο αναλφαριθμητικών , word1 : secret , word2 : guess
{ 
    int i,j,common_digits = 0 ; // common_digits : Αριθμός κοινών ψηφίων
    int digits1 [10] = {0,0,0,0,0,0,0,0,0,0}  ; 
    int digits2[10] = {0,0,0,0,0,0,0,0,0,0}  ; 
       
    for (i=0;word1[i] != '\0';i++) // Βρίσκει πόσες φορές υπάρχει κάθε ψηφίο (0,1,2,....9) και καταχωρεί τον αριθμό των φορών στο αντίστοιχη θέση του πίνακα digits1
    { // Π.Χ το 9 υπάρχει 3 φορές στον αριθμο 29499 , άρα digits1[9] = 3 ;   
           for (j=0 ; j <10 ; j++)
           {
               if (word1[i] == (j+48)) // j + 48 : o αντίστιχος χαρακτηρας του αριθμού j
               digits1[j]++; 
           }   
    }
    
    for (i=0;word2[i] != '\0';i++) // Βρίσκει πόσες φορές υπάρχει κάθε ψηφίο (0,1,2,....9) και καταχωρεί τον αριθμό των φορών στο αντίστοιχη θέση του πίνακα digits2
    {    
           for (j=0 ; j <10 ; j++)
           {
               if (word2[i] == (j+48))
               digits2[j]++; 
           }   
    } 
    
    for (i=0 ; i<10 ; i++) // Συγκρίνει τις τιμές των δύο πινάκων
    {
           if ((digits1[i] != 0) && (digits2[i] != 0)) // Αν και οι δύο πίνακες έχουν αυτό το ψηφίο τουλάχιστον μιά φορα
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

int common_char_same_place(char word1[],char word2[]) //Η συνάρτηση αυτή θα βρίσκει τους κοινούς χαρακτήρες στην ιδια θέση , word1 : secret , word2 : guess
{ 
    int i,j,cnt= 0 ; 
    for (i=0;word1[i] != '\0';i++)
    {
           if (word1[i] == word2[i]) // Πρέπει οι αντίστοιχες θέσεις των πινάκων να είναι ίσες
              cnt++ ;             
    }
return cnt;
}

int duplicate_digits (char word[]) // Θα ελέγχει τον αριθμό (αλφαριθμητικό) , για το εαν εχει διπλά ψηφία και θα επιστρέφει 1 αν εχεί και 0 αν δεν έχει 
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

char error_check_char (char b) // Φρόντίζει ώστε το b , η απάντηση δηλάδη να είναι ναι (Y) ή όχι (N)
{
    do //Ελεγχος σε περίπτωση λανθασμένης τιμής (δηλαδη χαρακτήρες εκτός του Y,N ή αριθμοί κτλ)
	{	
		    scanf ("\n%c",&b); // \n%c :διαγράφεται ο χαρακτήρας \n απο το buffer ,όπου εισάχθηκε απο την προηγόυμενη scanf και μετα καταχωρείται ο χαρακτήρας που εισάγεται
		    if ((b != 'Y') && (b != 'N')) 
               printf("Invalid value. Please input Y or N.\n");		    
	} while ((b != 'Y') && (b != 'N'));
	return b;
}   

int power_calc (int base ,int power) // Υπολογισμός δυνάμεων με μη αρνητικό εκθέτη
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


