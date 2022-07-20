//Χρήστος Ζαχαριουδάκης , 2014030056

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
   int number_of_materials_needed ;// (quantity) ποσότητα μονάδων (μη αρνητικός ακέραιος) από αυτό το είδος που απαιτούνται για τη σύνθεση μίας μονάδας του σύνθετου υλικού.        
};

struct product
{      
   int product_code;  // (code) Αναγνωριστικός Κωδικός του είδους  (>=0) 
   char *name_of_product;//  (name)Το όνομα του είδους (αλφαριθμητικό χωρίς κενά).
   int order_request; // (needed) Αριθμός που ζητήθηκε για την παραγγελία (Αν δεν ζητήθηκε κανένα τότε =0 )
   int number_of_products_in_stock; // (nPieces) Την ποσότητα μονάδων του είδους στην αποθήκη (>=0).      
   struct material *usage; // (usage) Δείχνει σε μια θέση μια διάταξης δομών struct material (αναφέρεται στο είδος και την ποσότητα των υλικών που την αποτελούν)
   int number_of_composite_materials; // (nUses) Έάν είναι πρώτη ύλη τότε number_of_composite_materials = 0
}; 

/*Prototype declaration*/

void free_products_list (struct product * ,int); // Θα αποδεσμεύεσει την μνήμη που δεσμεύτηκε με την malloc
struct product * data_registration (struct product *,FILE *,int) ;  // Εισαγωγή δεδομένων απο αρχείο στη δομή επιστροφή δείκτη που δείχνει στην διάταξη δομών.
void data_output (struct product *,int) ;// Εξαγωγη αρχείου εξόδου
void needed_materials (struct product product,int); // A recursive function that calculates the total number of products needed for the order (dataout # units needed)

int main (void) // Κωρίως τμήμα του προγράμματος
{    
/*Δήλωση μεταβλητών*/
    
char choice_name [MAX_NAME_SIZE] ; // To ονομα του υλικού που θα εισάγει ο χρήστης για να δεί λεπτομέρειες
struct product *list_of_products ; // Δήλωση δομής που θα περιέχει τα υλικά και τα στοιχεία τους
FILE *fp ; // Αρχείο εισόδου
int number_of_products; // Αριθμός προιόντων (πρώτος αριθμός του datain)
int i,j ,menu_choice ,searched_product_place; // Για for loop, Επιλογή μενού, Η θέση του προιόντος που ζήτησε ο χρήστης να δει στο πίνακα δομών   
int open_cnt=0, out_cnt = 0 ,pr_cnt=0, max_materials = 0; // Μετράει πόσες φορές άνοιξε το αρχείο., Μετράει πόσες φορές έγινε η εξαγωγή του αρχείου , Μετρητής για το πίνακα places,Περιέχει τον μέγιστο αριθμό επιμερους προιόντων
int *places; // Ο πίνακας αυτος θα αποθηκεύσει τις θέσεις (i) των προιόντων με φθίνουσα σειρά ανάλογα με τον αριθμό των επιμέρους υλικών τους (δηλ τα τελικά προιόντα πρώτα , μετα ενδιαμεσα , πρώτες ύλες)

if  ((fp = fopen(INPUT_NAME,"r"))== NULL ) // Ανοιγμα το αρχείο product_datain και έλεγχος για πρόβλημα κατα το άνοιγμα
{
   printf ("Error while opening the required file.\n");
   printf ("Check that your file is in the same directory as the executable file.\n");
   system ("PAUSE"); 
   exit (0) ;          
}
fscanf (fp,"%d\n",&number_of_products);  // Αποθηκεύει τον αριθμό των προιόντων
places = (int * ) malloc (number_of_products * sizeof(int)); // Δέσμευση μνήμης για το πίνακα places

/*Δημιουργία μενού*/

printf ("\nWelcome to our official product management software:\n\n");
printf ("===============================================================================\n");
printf ("Choose one of the following options (1-5):\n");
printf ("1.Read the input data file (It must be in the same directory as the executable file\n");
printf ("2.Show all of the available products\n");
printf ("3.Show the composite materials of a specified product\n");
printf ("4.Generate the output file (It is in the same directory as the executable file\n");
printf ("5.Close the software\n"); 
printf ("===============================================================================\n");

while (1) // Το μενου θα επαναλαμβάνεται μέχρι να χρησιμοποιηθεί η πέμπτη επιλογή , δηλαδή η έξοδος απο το πρόγραμμα
{   
   printf ("\nEnter your choice: ");  
   do
   {
      scanf ("%d",&menu_choice); // Επιλογή λειτουργίας  του μενού 
      switch (menu_choice)
      {
         case 1: // Ανάγνωση του αρχείου εισόδου datain.txt
              if (open_cnt==0) // Η ανάγνωση του αρχείου επιτρέπεται να γίνει μία φορά
              {
                 open_cnt++; // Κάθε φορά που θα ανοίγεται το αρχείο 
                 list_of_products = data_registration (list_of_products,fp,number_of_products); // Καταχώρηση δεδομένων απο το αρχείο στις διατάξεις δομών 
                 if (fclose (fp) !=0) // Κλείσιμο του αρχείου εισαγωγής
                 {    
                   printf ("Error while opening the required file.\n");
                   printf ("Check that your file is in the same directory as the executable file\n");
                   system ("PAUSE"); 
                   exit (2) ;        
                 }         
                 printf ("\nReading the file...........................\n");
                 printf ("The import of the input data file is complete!\n");
              }
              else printf ("You have already imported the file.\n"); // Σε περίπτωση που έχει εκτελέστει τουλάχιστον μια φορά η ανάγνωση του αρχείου.   
              break;       
         case 2:  // Εμφάνιση όλων των ειδών υλικού
              if (open_cnt>0) // Αν η εντολή για το άνοιγμα του αρχείου έχει εκτελεστεί μια φορά
              {
                 printf ("The available products are :\n");
                 printf ("Product - Number in stock\n");
                 for (i=0;i<number_of_products;i++)
                    printf ("%s - %d\n",list_of_products[i].name_of_product,list_of_products[i].number_of_products_in_stock);
              } 
              else printf ("You must open the file first by choosing option 1.\n"); // Αν η εντολή για το άνοιγμα του αρχείου έχει εκτελεστεί καμία φορά
              break;   
         case 3: // Εμφάνιση της σύνθεσης ενός είδους υλικού
              if (open_cnt>0) // Αν η εντολή για το άνοιγμα του αρχείου έχει εκτελεστεί μια φορά
              {
                 searched_product_place = -1 ; // Αρχική τιμη του , η οποία θα διατηρηθεί σε περίπτωση που η λέξη που θα εισαχθεί
                 printf ("Input the name of the product you wish to view (The first letter must be capital):");
                 scanf("\n%s",choice_name); // Ανάγνωση της επιλογής του χρήστη (\n%s : Για να διαγραφεί απο το buffer o χαρακτήρας new line που απέμεινε.)                
                 for (i=0;i<number_of_products;i++)
                 {
                     if (strcmp(choice_name,list_of_products[i].name_of_product) ==0) // Αν το ονομα που εισήγαγε ο χρήστης είναι ίδιο με κάποιο  
                     searched_product_place = i ;  // Αποθήκευση της θέσης που βρίσκεται το προιόν , του οποίου το όνομα εισήγαγε ο χρήστης              
                 }                     
                 if (searched_product_place == -1)  // Σε περίπτωση που δεν βρέθηκε το όνομα , η μεταβλητή searched_product_place διατηρεί την τιμη -1
                 { 
                     printf ("No product named %s is found.\n",choice_name);
                     system ("Pause");
                     return 0; 
                 }
                 if (list_of_products[searched_product_place].usage !=NULL) // Αν το προιόν δεν είναι πρώτη ύλη
                 {
                     printf ("%s has the following materials:\n\n",list_of_products[searched_product_place].name_of_product);                          
                     printf ("Product - Quantity available\n");                         
                     for (j=0;j<list_of_products[searched_product_place].number_of_composite_materials;j++)
                     {
                        if (list_of_products[searched_product_place].usage[j].code_ptr != NULL)  // Σε περίπτωση που το επιμέρους προιόν δεν αντιστοιχεί σε κάποιο απο το αρχείο (εχει πάρει τιμή NULL απο την data registration)
                           printf ("%s - %d\n",list_of_products[searched_product_place].usage[j].code_ptr->name_of_product,list_of_products[searched_product_place].usage[j].code_ptr->number_of_products_in_stock);
                     }   
                 }                   
                 else printf ("The %s product has no composite materials.\n",choice_name); // Αν το προιόν είναι πρώτη ύλη
              }
              else printf ("You must open the file first by choosing option 1.\n");          
              break;   
         case 4:  // Δημιουργία του αρχείου εξόδου dataout
              if (open_cnt>0) // Αν η εντολή για το άνοιγμα του αρχείου έχει εκτελεστεί μια φορά
              {                            
                 if (out_cnt == 0) // Αν δεν έχει γίνει εξαγωγή του αρχείου καμία φορά
                 {            
                    out_cnt++; // Αυξάνεται κάθε φορά που πάράγεται το αρχείο εξόδου                                                                    
                    for (i=0;i<number_of_products;i++) // Βρίσκει την μέγιστη τιμή των επιμέρους υλικών (αυτή που έχουν τα τελικά προιόντα)
                       if (max_materials < list_of_products[i].number_of_composite_materials) max_materials = list_of_products[i].number_of_composite_materials;
                                                              
                    while (max_materials>=0) // Θα αποθηκεύσει τις θέσεις (i) των προιόντων στο πίνακα places με φθίνουσα σειρά ανάλογα με τον αριθμό των επιμέρους υλικών(number_of_composite_materials) τους (δηλ τα τελικά προιόντα πρώτα,μετα ενδιαμεσα,πρώτες ύλες)
                    {
                       for (i=0;i<number_of_products;i++)                       
                          if (list_of_products[i].number_of_composite_materials == max_materials)    
                          places[pr_cnt++] = i; 
                       max_materials-- ;      
                    }                    
                   
                    for (pr_cnt=0;pr_cnt<number_of_products;pr_cnt++) // Εκτελεί την αναδρομική συνάρτηση για όλα τα προιόντα ,αλλα πρώτα για τα τελικά προιόντα , και μετά για τα ενδιάμεσα
                       needed_materials (list_of_products[places[pr_cnt]],list_of_products[places[pr_cnt]].number_of_composite_materials-1); 
                                          
                    data_output (list_of_products,number_of_products); // Εξαγωγή του αρχείου εξόδου
                    printf ("The output file is generated.\n");
                    free (places); // Αποδεσμεύει την μνήμη που δεσμεύτηκε για τον πίνακα places
                 }
                 else printf ("The output file is already generated.Check the software folder.\n");
              }
              else printf ("You must open the file first by choosing option 1.\n"); 
              break;
         case 5: // Τερματισμός προγράμματος
              printf ("The software is terminated.\n");
              free_products_list (list_of_products,number_of_products); //  Απελευθέρωση μνήμης που δεσμεύτηκε απο την malloc               
              system ("Pause");
              exit (0) ; 
              break;              
         default: // Περίπτωση που εισάχθηκε λάθος τιμή
              printf ("Enter 1,2,3,4 or 5.\n");
              break;   
       }
} while ((menu_choice<1) || (menu_choice>5)); // Πρέπει η επιλογή του χρήστη να είναι αριθμός απο το 1 εως και το 5.
}
} // Τέλος main

/*Συναρτήσεις*/

void needed_materials (struct product product,int number_of_comp_materials) // A recursive function that calculates the total number of products needed for the order (dataout # units needed)
{
if (product.usage != NULL) // Αν δεν είναι πρώτη υλη
{                     
   if (number_of_comp_materials < 0);  // Μη αναδρομική περίπτωση 
   else
   {
      if (product.usage[number_of_comp_materials].code_ptr != NULL)  // Σε περίπτωση που το επιμέρους προιόν δεν αντιστοιχεί σε κάποιο απο το αρχείο (εχει πάρει τιμή NULL απο την data registration)
         product.usage[number_of_comp_materials].code_ptr->order_request += product.order_request * (product.usage[number_of_comp_materials].number_of_materials_needed);  
      
      needed_materials (product,number_of_comp_materials-1);       
   }
}     
}        

struct product * data_registration (struct product *product_data,FILE *fp,int number_of_products ) // Εισαγωγή δεδομένων απο αρχείο στη δομή επιστροφή δείκτη διάταξης δομών.
{     
int number_of_orders,order_code ; // number_of_orders πρώτος αριθμός δευτερου μέρους του datain (ποσα προιόντα εχουν παραγγελθεί) ,Ο αποθηκεύει προσωρινά τον αριθμό της κάθε παραγγελίας
int choice,i,j,ptr_cnt=0,cnt=0,nul_cnt=0; // number_of_products αριθμός όλων των προιόντων , choice επιλογη στο μενου ι,j για for loops , μετρητής για τον πίνακα temp_codes_ptr , μετρητής για τον πίνακα temp_codes 
int temp_codes[200] ; // Αποθηκεύει προσωρινά τους κωδικους των επιμέρους προιόντων πχ 2 3 (Wheel) 4 5 (Engine) 6 7 1 (Car)
struct product * temp_ptr_codes[200]; // Αποθηκεύει προσωρινά τους δεικτες των επιμέρους προιόντων (part)
char buf_name [MAX_NAME_SIZE]; // Προσωρινή αποθήκευση του ονόματος του προιόντος

product_data = (struct product *) malloc (number_of_products * sizeof(struct product)) ; // Δημιουργία της διάταξης δομών που θα περιέχει τα στοιχεία των υλικών
for (i=0;i<number_of_products;i++) // Για κάθε τιμη του i εχουμε μια γραμμή.
{
   fscanf (fp,"%d %s %d %d",&product_data[i].product_code,buf_name,&product_data[i].number_of_products_in_stock,&product_data[i].number_of_composite_materials);
   product_data[i].name_of_product = (char *) malloc ((strlen(buf_name)+1) * sizeof(char)) ;
   strcpy (product_data[i].name_of_product,buf_name) ; 
   product_data[i].usage = (struct material *) malloc (product_data[i].number_of_composite_materials * sizeof(struct material)) ;  // Δημιουργία της διάταξης δομών που θα περιέχει τα στοιχεία των πρώτων υλών / επιμέρους προιόντων που αποτελούν το υλικό
   if (product_data[i].number_of_composite_materials != 0 ) //  Εαν το υλικό δεν είναι πρώτη ύλη 
   {
      for (j=0;j<product_data[i].number_of_composite_materials;j++) // Διαβάζει την δυαδα κωδικος - ποσότητα                                                       
         fscanf (fp," %d %d",&temp_codes[cnt++],&product_data[i].usage[j].number_of_materials_needed); // Αποθήκευση των κωδικών των ενδιάμεσων προιόντων σε πίνακα          
                   
      fscanf (fp,"\n"); // Θα αλλάζει σειρά στο αρχείο                    
   }
   else // Εαν είναι πρώτη υλη τότε :
   {
      product_data[i].usage = NULL ; // Ο δείκτης usage δεν χρειάζεται να δείχνει πουθενα      
      fscanf (fp,"\n"); // Η πρώτη fscanf αρκει για την ανάγνωση όλων των δεδομένων του , άρα απλώς πάμε στο επόμενο υλικό αλλάζοντας σειρά    
   }
}
for (i=0;i<cnt;i++) // 'Μετατροπη' σε κωδικών σε δείκτες και σειριακή εισαγωγή τους σε ένα πίνακα
{
   nul_cnt = 0 ;// Μετράει τις φορές που ο κωδικός διαφέρει απο αυτούς των πινάκων . Αν διαφέρει με όλους nul_cnt = number_of_products , δηλαδη ο κωδικός του επιμέρους υλικού δεν υπάρχει στο αρχείο.
   for (j=0;j<number_of_products;j++)
   {
      if (temp_codes[i] == product_data[j].product_code) temp_ptr_codes[ptr_cnt++]= &product_data[j]; // Αν ο κωδικός του temp_codes[i] είναι ίσος με ενός προιόντος , τότε αποθηκέυεται η διεύθυνση του προιόντος στον temp_ptr_codes
      else if (temp_codes[i] != product_data[j].product_code) nul_cnt++;
      if (nul_cnt == number_of_products) temp_ptr_codes[ptr_cnt++] = NULL;
   }
}

ptr_cnt=0;
for (i=0;i<number_of_products;i++) // Εισαγωγή των δεικτών απο τον πίνακα στους δείκτες code_ptr των διατάξεων δομων usage
{
   if (product_data[i].number_of_composite_materials !=0) // Προσπερνάμε τις πρώτες ύλες  
      for (j=0;j<product_data[i].number_of_composite_materials;j++) product_data[i].usage[j].code_ptr = temp_ptr_codes[ptr_cnt++]; // Καταχώρηση των δεικτω΄ν στην διάταξη δομών (Είναι σημαντικό ότι πάντα με την ίδια σειρά που αποθηκεύονται τα προιόντα στη διάταξη δομών , αποθηκεύονται και στον πίνακα)                                                 
}

for (j=0;j<number_of_products;j++) product_data[j].order_request = 0 ; // θέτει αρχική τιμή 0 σε όλα τα πεδία order_request (needed)

fscanf (fp,"%d\n",&number_of_orders); // Διαβάζει και αποθηκευει τον αριθμό των παραγγελιών

for (i=0;i<number_of_orders;i++) // Αποθήκευση των παραγγελιών , δηλαδη των order_request
{
   fscanf(fp,"%d ",&order_code); // Ανάγνωση του κωδικου και συγκρισή του με τους κωδικους της διάταξης δομών  
   for (j=0;j<number_of_products;j++)   
      if (order_code == product_data[j].product_code) fscanf(fp,"%d\n",&product_data[j].order_request);
}
return product_data;   
}

void data_output (struct product *product_data,int number_of_products) // Εξαγωγη αρχείου εξόδου
{
FILE *fp2 ; 
int i ; 

if ((fp2 = fopen (OUTPUT_NAME,"w"))== NULL) // Ανοιγμα του αρχείου για εγγραφή
{
   printf ("Error while creating the required file.\n");
   printf ("Check that your hard drive has the required space.\n");
   system ("PAUSE"); 
   exit (1) ;          
}   
fprintf (fp2,"Number of material types: %d\n",number_of_products); 
for (i=0;i<number_of_products;i++) 
    fprintf (fp2,"%d/%s - %d units in stock - %d units needed\n",product_data[i].product_code,product_data[i].name_of_product,product_data[i].number_of_products_in_stock,product_data[i].order_request);    

if (fclose (fp2) !=0) // Κλείσιμο του αρχείου 
{    
    printf ("Error while opening the required file.(You may have to run the software with administrator rights.)\n");
    printf ("Check that your file is in the same directory as the executable file.\n");
    system ("PAUSE"); 
    exit (2) ;        
}
}

void free_products_list (struct product *product_data,int size) // Θα αποδεσμεύεσει την μνήμη που δεσμεύτηκε με την malloc
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




