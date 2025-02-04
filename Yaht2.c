#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void instruction(int round);
void roll_dices(int dices[]);
void display_dices(int dices[]);
int Ones(int dices[],int size);
int Twos(int dices[],int size);
int Threes(int dices[],int size);
int Fours(int dices[],int size);
int Fives(int dices[],int size);
int Sixes(int dices[],int size);
int is_Three_of_a_kind(int dices[], int size,bool reroll[]);
int is_Four_of_a_kind(int dices[], int size,bool reroll[]);
int is_Full_House(int dices[], int size);
int is_small_straight(int dices[],int size,bool reroll[]);
int is_large_straight(int dices[],int size);
int is_Chance(int dices[], int size);
int is_YAHTZEE(int dices[], int size);

void  isRerolling_dices(int dices[],int reroll_indices[],int size,int UsedCategory[],char *Categories[],int *moveScore,int *total,int *rerollchoice,bool reroll[]);
void  reroll_dice(int dices[5], int reroll_indices[], int size);
int GameMove(int dices[],int UsedCategory[],char *Categories[],int size,bool reroll[]);
void updateScore(int *total, int moveScore);
int is_ValidCategory(int UsedCategory[],int move);
bool computer_reroll_one(int dices[], int size,int UsedCategoryComp[],bool reroll[]);
bool computer_reroll_two(int dices[], int size, int UsedCategoryComp[],bool reroll[]);
int computerMove(int dices[],int size,int UsedCategoryComp[],bool reroll[]); 
void updateCscore(int *Comtotal,int ComMove);
int Gameround(int round,int *total,int *Comtotal);
int EndGame(int round,int *total,int *Comtotal);
int main()
{
  int round=0;
  int dices[5];
  int reroll_indices[5];
  int size=5;
  int Sts=1;
  int UsedCategory[13]={0};
  int UsedCategoryComp[13]={0};
  int total=0;
  int Comtotal=0;
  int move;

  bool reroll[5]={false};
  
  char *Categories[]={
    "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes", 
    "Three of a Kind", "Four of a Kind", "Full House", 
    "Small Straight", "Large Straight", "Yahtzee", "Chance"
};
srand(time(0));//current time to ensure different sequences of numbers
  
  while(Sts == 1) {
  const char *green = "\033[32m";// green
  const char *reset = "\033[0m";               
  printf("%sPlayer 1%s\n", green, reset);

    // Print "Roll dices when you're ready!" in jet blue
    const char *jet_blue = "\033[38;5;24m";     // Jet blue
    printf("%sRoll dices when you're ready!%s\n", jet_blue, reset);
  for(int j=0;j<13;j++) {
  instruction(round);
  roll_dices(dices);
  display_dices(dices);
  Ones(dices,size);
  Twos(dices,size);
  Threes(dices,size);
  Fours(dices,size);
  Fives(dices,size);
  Sixes(dices,size);
  printf("\n");
  is_Three_of_a_kind(dices,size,reroll);
  is_Four_of_a_kind(dices,size,reroll);
  is_Full_House(dices,size);
  is_small_straight(dices,size,reroll);
  is_large_straight(dices,size);
  is_Chance(dices,size);
  is_YAHTZEE(dices,size);
  int moveScore;
  
  int rerollchoice; //input for rerolling or not
    
    printf("\nChoose to reroll ? \nEnter 1.yes 2.No \n"); //prompt for user input for rerolling
    scanf("%d",&rerollchoice);
    if(rerollchoice != 2) {
       for(int i=0;i<1;i++)  {
      isRerolling_dices(dices,reroll_indices,size,UsedCategory,Categories,&moveScore,&total,&rerollchoice,reroll);
    }
    }
else{
    moveScore=GameMove(dices,UsedCategory,Categories,5,reroll);
    updateScore(&total, moveScore);
}
   printf("\nPlayer 2(computer)\n");
        roll_dices(dices);
        display_dices(dices);
        Ones(dices,size);
          Twos(dices,size);
          Threes(dices,size);
          Fours(dices,size);
          Fives(dices,size);
          Sixes(dices,size);
          printf("\n");
          is_Three_of_a_kind(dices,size,reroll);
          is_Four_of_a_kind(dices,size,reroll);
          is_Full_House(dices,size);
          is_small_straight(dices,size,reroll);
          is_large_straight(dices,size);
          is_Chance(dices,size);
          is_YAHTZEE(dices,size);    
            
            if(computer_reroll_one(dices,size,UsedCategoryComp,reroll)) {
                printf("\nComputer ReRolling dices.......");
            printf("\nReRoll 1\n");
            display_dices(dices);
            Ones(dices,size);
              Twos(dices,size);
              Threes(dices,size);
              Fours(dices,size);
              Fives(dices,size);
              Sixes(dices,size);
              printf("\n");
              is_Three_of_a_kind(dices,size,reroll);
              is_Four_of_a_kind(dices,size,reroll);
              is_Full_House(dices,size);
              is_small_straight(dices,size,reroll);
              is_large_straight(dices,size);
              is_Chance(dices,size);
              is_YAHTZEE(dices,size);}

             if(computer_reroll_two(dices,size,UsedCategoryComp,reroll)) {
              printf("\nReRoll 2\n");
              display_dices(dices);
            Ones(dices,size);
              Twos(dices,size);
              Threes(dices,size);
              Fours(dices,size);
              Fives(dices,size);
              Sixes(dices,size);
              printf("\n");
              is_Three_of_a_kind(dices,size,reroll);
              is_Four_of_a_kind(dices,size,reroll);
              is_Full_House(dices,size);
              is_small_straight(dices,size,reroll);
              is_large_straight(dices,size);
              is_Chance(dices,size);
              is_YAHTZEE(dices,size);}
   
              int ComMove=computerMove(dices,size,UsedCategoryComp,reroll);
              updateCscore(&Comtotal,ComMove); 
      Gameround(round,&total,&Comtotal);
        printf("\nYour Turn Again!\n");
        round++;
  }
  EndGame(round,&total,&Comtotal);
  printf("\nStart a New Game ?\n1.Let's Go 2.Another Time");
  scanf("%d", &Sts);
  }
  if(Sts == 2) {
      Sts++;
  }
    return 0;
  }
  
/* @brief instruction fuction- 
instructions to start the game and roll dices*/
void instruction(int round) {
    int roll;

    // ANSI color codes
    const char *purple = "\033[35m";
    const char *light_yellow = "\033[93m";
    const char *light_blue = "\033[94m";
    const char *reset = "\033[0m";

    printf("\n%sEnter 1 for Rolling dices%s\n", purple, reset);
    fflush(stdout);


    scanf("%d", &roll);
    while (roll != 1) {
        printf("\n%sEnter 1 for Rolling dices%s\n", purple, reset);  
        fflush(stdout);
        scanf("%d", &roll);
    }

    printf("\n%s                                     ROUND %d                                     %s\n", light_yellow, round + 1, reset);
    fflush(stdout);
    printf("%sFirst Roll:%s\n\nYour ", light_blue, reset);
    fflush(stdout);
}
/* @brief generate 5 random values between 1 and 6 for dices*/
void roll_dices(int dices[])
{
    int i;
    for(i=0;i<5;i++) {
            dices[i]=(rand()%6)+1; //Random number between 1 and 6
            }    
}
/* @brief display the 5 random values between 1 and 6 for dices*/
void display_dices(int dices[])
{
    int j;
   
     printf("dices : \n");
     for(j=0;j<5;j++) {
    printf("%d\n", dices[j]);
    }
    printf("\n");
}
/* @brief taking user input for whether rerolling dices  */
void  isRerolling_dices(int dices[],int reroll_indices[],int size,int UsedCategory[],char *Categories[],int *moveScore,int *total,int *rerollchoice,bool reroll[])
{
    while(*rerollchoice != 2)
    {
        if(*rerollchoice==1) //if user is rerolling prompt for positions 
        {
            for(int i=0;i<2;i++)
            {
                if(i>=1){
                    if(*rerollchoice==2)
                    {
                        break;
                    }
                }
                printf("Reroll %d\n",i+1);
                reroll_dice(dices,reroll_indices,size);
                display_dices(dices);
                Ones(dices,size);
                Twos(dices,size);
              Threes(dices,size);
              Fours(dices,size);
              Fives(dices,size);
              Sixes(dices,size);
              is_Three_of_a_kind(dices,size,reroll);
              is_Four_of_a_kind(dices,size,reroll);
              is_Full_House(dices,size);
              is_small_straight(dices,size,reroll);
              is_large_straight(dices,size);
              is_Chance(dices,size);
              is_YAHTZEE(dices,size);
                
                if(i<1) {
                    printf("\nChoose to reroll again ? \nEnter 1. Yes 2. No: \n");
                scanf("%d", rerollchoice);
                }
        }
        *moveScore=GameMove(dices,UsedCategory,Categories,5,reroll);
                updateScore(total, *moveScore);
        break;
        }
        else {
            printf("Please choose Yes or No\n");
            scanf("%d",&rerollchoice);
        }
    }   
}
/* @brief taking user input for  indexes to roll dices and generate and display dices values */
void  reroll_dice(int dices[5], int reroll_indices[], int size)
{
    int rolls;
    printf("How many dices to ReRoll ?\n");
    scanf("%d", &rolls);
    if(rolls<0 || rolls>5) {   printf("Please Enter a valid number of dices :\n");
            scanf("%d", &rolls);
            
        }
    if(rolls==5) {
        for(int i=0;i<5;i++){
            dices[i] = (rand() % 6) + 1;
           }
    }
    else {
    printf("Choose the numbers of the dices to ReRoll\n");
    for (int i=0;i<rolls;i++) {
        scanf("%d", &reroll_indices[i]);
        reroll_indices[i]-=1;//adjust input to match array indexing for better user interface
    }
     for (int i = 0; i < rolls; i++)  {
        int index = reroll_indices[i];
        if (index >= 0 && index < 5)  // Validating the index                
        {
            dices[index] = (rand() % 6) + 1;  
        }
    }
    }  
}
/* @brief Keep track of chosen User Categories  */
int is_ValidCategory(int UsedCategory[],int move)
{
    return UsedCategory[move-1]==1;
}
/* @brief Takes user input for the scoring category ,Display available scoress 
return score of the chosen category*/
int GameMove(int dices[],int UsedCategory[],char *Categories[],int size,bool reroll[])
{
    int move;
    int score=0;
    printf("\nChoose your move\n");
  printf("\nUpper Section Combos\n1.Ones\n2.Twos\n3.Threes\n4.Fours\n5.Fives\n6.Sixes\n");
  printf("\nLower Section Combos\n7.Three of a kind\n8.Four of a kind\n9.Full House\n10.Small Straight\n11.Large Straight\n12.Chance\n13.YAHTZEE\n");
  printf("Your Move : ");
  scanf("%d", &move);
  while(move >13 ||  move <1)  {
      printf("Enter a valid Game Move :\n");
      scanf("%d", &move);
  }
  if(is_ValidCategory(UsedCategory,move)) {
          printf("This category has already been used. Please choose another one.\n");
          scanf("%d", &move);
      }
      printf("You chose ");
      
      UsedCategory[move-1]=1;
      switch(move)
      {
          case 1:return Ones(dices,size);
          case 2: return Twos(dices,size);
          case 3:return Threes(dices,size);
          case 4:return Fours(dices,size);
          case 5:return Fives(dices,size);
          case 6: return Sixes(dices,size);
          case 7: return is_Three_of_a_kind(dices,size,reroll);
          case 8:return is_Four_of_a_kind(dices,size,reroll);
          case 9:return is_Full_House(dices,size);
          case 10:return is_small_straight(dices,size,reroll);
          case 11:return is_large_straight(dices,size);
          case 12:return is_Chance(dices,size);
          case 13: return is_YAHTZEE(dices,size);
          default:break;
      }
  printf("\nComputer will roll now ;\n");
  
  return move;
}
/* @brief functions to check the score for each category  
returns score*/

int is_Three_of_a_kind(int dices[], int size, bool reroll[]) {
    int sum = 0;

    // Count occurrences of each value
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (dices[i] == dices[j]) {
                count++;
            }
        }

        // Check if we have a Three of a Kind
        if (count >= 3) {
            sum = dices[i] * 3;
            printf("Three of a Kind - %d\n", sum);

            // Mark reroll array
            for (int j = 0; j < size; j++) {
                reroll[j] = (dices[j] != dices[i]); // Reroll if not part of Three of a Kind
            }
            return sum;
        }
    }

    printf("Three of a Kind - 0\n");
    return 0;
}


int is_Four_of_a_kind(int dices[], int size,bool reroll[])
{
    int sum = 0;
    
    // Count occurrences of each die value
    for (int i = 0; i < size; i++)
    {
        int count = 0;
        for (int j = 0; j < size; j++)
        {
            if (dices[i] == dices[j])
            {
                count++;
            }
        }
        
        
        if (count >= 4)
        {
            sum=dices[i]*4;
            printf("Four of a kind - %d \n", sum);
            int target_value = dices[i];
    
    // Loop through all dice to decide which ones to reroll
    for (int j = 0; j < size; j++) {
        if (dices[j] != target_value) {
            reroll[j] = true;  // Reroll dice with different values
        } else {
            reroll[j] = false; // Keep dice with the "Three of a Kind" value
        }
        }
            return sum;
        }
    }
    printf("Four of a Kind-0\n");
    return 0;  
}

int is_YAHTZEE(int dices[], int size)
{
    int sum=0;
    for(int i=0;i<size;i++)
    {
        sum+=dices[i];
    }
    for(int i=0;i<size;i++)
    {
        int count=0;
        int yahtzee=50;
        for(int j=0;j<size;j++)
        {
            if(dices[i]==dices[j])
            {
                count++;
            }
            if(count>=5)
            {
               
            printf("YAHTZEE - %d \n",yahtzee);
            return 50;
            }
        }
    }
    printf("YAHTZEE-0\n");
    return 0;
}
int is_Full_House(int dices[], int size)
{
    int sum=0;
    int fullhouse=25;
    int counts[6]={0};
    for(int i=0;i<size;i++)
    {
        sum+=dices[i];
    }
    for(int i=0;i<size;i++)
    {
        counts[dices[i]-1]++;
    }
    int istri=0;
    int isto=0;
    
    for(int i=0;i<6;i++)
    {
        if(counts[i]==3)
        {
            istri=1;
        }
        if(counts[i]==2)
        {
            isto=1;
        }
    }
    
    if(isto && istri)
    {
        printf("Full House - %d \n", fullhouse);
        return fullhouse;
    }
    printf("Full House-0\n");
    return 0;
}
int is_Chance(int dices[], int size)
{
    int sum=0;
    for(int i=0;i<size;i++)
    {
        sum+=dices[i];
    }
    
    printf("Chance - %d \n",sum);
    return sum;
}
int is_small_straight(int dices[],int size,bool reroll[]) {
    // Array to mark which values are present
    int values[7] = {0}; // Index 0 unused for simplicity

    // Mark dice values in values_present
    for (int i = 0; i < size; i++) {
        if (dices[i] >= 1 && dices[i] <= 6) {
            values[dices[i]] = 1;
        }
    }
 if (values[1] && values[2] && values[3] && values[4]) {
    int seen[7] = {0}; // To track dice values already contributing to the straight
printf("Small Straight-30 \n"); 
    for (int i = 0; i < size; i++) {
        if (dices[i] >= 1 && dices[i] <= 4) {
            if (seen[dices[i]] == 0) {
                // Mark the value as used in the straight
                seen[dices[i]] = 1;
                reroll[i] = false; // Keep this dice
            } else {
                // Duplicate value, mark for reroll
                reroll[i] = true;
            }
        } else {
            // Values outside the straight, mark for reroll
            reroll[i] = true;
        }
    }

    return 30; // Small straight detected
}
    if (values[2] && values[3] && values[4] && values[5]) {
        printf("Small Straight-30 \n"); 
    int seen[7] = {0}; // To track dice values already contributing to the straight

    for (int i = 0; i < size; i++) {
        if (dices[i] >= 2 && dices[i] <= 5) {
            if (seen[dices[i]] == 0) {
                // Mark the value as used in the straight
                seen[dices[i]] = 1;
                reroll[i] = false; // Keep this dice
            } else {
                // Duplicate value, mark for reroll
                reroll[i] = true;
            }
        } else {
            // Values outside the straight, mark for reroll
            reroll[i] = true;
        }
    }

    return 30; // Small straight detected
}
if (values[3] && values[4] && values[5] && values[6]) {
    printf("Small Straight-30 \n"); 
    int seen[7] = {0}; // To track dice values already contributing to the straight

    for (int i = 0; i < size; i++) {
        if (dices[i] >= 3 && dices[i] <= 6) {
            if (seen[dices[i]] == 0) {
                // Mark the value as used in the straight
                seen[dices[i]] = 1;
                reroll[i] = false; // Keep this dice
            } else {
                // Duplicate value, mark for reroll
                reroll[i] = true;
            }
        } else {
            // Values outside the straight, mark for reroll
            reroll[i] = true;
        }
    }

    return 30; // Small straight detected
}

    printf("Small Straight-0\n");
    for (int i = 0; i < size; i++) {
        reroll[i] = true;
    }
    return 0; // No small straight found
}
int is_large_straight(int dices[],int size) {
    // Array to mark which values are present
    int values[7] = {0}; // Index 0 unused for simplicity

    // Mark dice values in values_present
    for (int i = 0; i < size; i++) {
        if (dices[i] >= 1 && dices[i] <= 6) {
            values[dices[i]] = 1;
        }
    }

    // Check for large straight patterns
    if ((values[1] && values[2] && values[3] && values[4] && values[5]) ||
        (values[2] && values[3] && values[4] && values[5] && values[6])) {
             printf("Large Straight- %d \n",40); 
        return 40; // Large straight found
        }
    
     printf("Large Straight-0\n");
    return 0; // No large straight found
}
int Ones(int dices[],int size)
{
    int count=0;
    int sum=1;
    
    for(int i=0;i<size;i++)
    {
        if(dices[i]==1)
        {
            count++;
        }
    }
    sum=count*1;
    printf("Ones - %d\n",sum);
    
    return sum;
}
int Twos(int dices[],int size)
{
    int count=0;
    int sum=1;
    for(int i=0;i<size;i++)
    {
        if(dices[i]==2)
        {
            count++;
        }
    }
    sum=count*2;
    printf("Twos - %d\n",sum);
    
    return sum;
}
int Threes(int dices[],int size)
{
    int count=0;
    int sum=1;
    for(int i=0;i<size;i++)
    {
        if(dices[i]==3)
        {
            count++;
        }
    }
    sum=count*3;
    printf("Threes - %d\n",sum);
    
    return sum;
}
int Fours(int dices[],int size)
{
    int count=0;
    int sum=1;
    for(int i=0;i<size;i++)
    {
        if(dices[i]==4)
        {
            count++;
        }
    }
    sum=count*4;
    printf("Fours - %d\n",sum);
    
    return sum;
}
int Fives(int dices[],int size)
{
    int count=0;
     int sum=1;
    for(int i=0;i<size;i++)
    {
        if(dices[i]==5)
        {
            count++;
        }
    }
    sum=count*5;
    printf("Fives - %d\n",sum);
    
    return sum;
}
int Sixes(int dices[],int size)
{
    int count=0;
    int sum=1;
    for(int i=0;i<size;i++)
    {
        if(dices[i]==6)
        {
            count++;
        }
    }
    sum=count*6;
    printf("Sixes - %d\n",sum);
    return sum;
    printf("\n");
    

}
/* @brief Computer Strategy for rerolling dices
keeps same value dices and reroll others*/
bool computer_reroll_one(int dices[], int size, int UsedCategoryComp[], bool reroll[]) {
    printf("\n");
    int values[7] = {0};

    // Check for specific categories and update reroll array
    if (is_YAHTZEE(dices, size) && UsedCategoryComp[12] == 0) {
        for (int i = 0; i < size; i++) {
            reroll[i] = false; // Keep all dice
        }; // Mark Yahtzee as used
        printf("h\n");
        return false;
    }

    if (is_large_straight(dices, size) && UsedCategoryComp[10] == 0) {
        for (int i = 0; i < size; i++) {
            reroll[i] = false; // Keep all dice
        }
        return false;
    }

    if (is_Full_House(dices, size) > 0 && UsedCategoryComp[8] == 0) {
        for (int i = 0; i < size; i++) {
            reroll[i] = false; // Keep all dice
        }
        return false;
    }
    for (int i = 0; i < size; i++) {
        if (dices[i] >= 1 && dices[i] <= 6) {
            values[dices[i]] = 1;
        }
    }
if(UsedCategoryComp[10] == 0 || UsedCategoryComp[11] == 0) {
       if (values[1] && values[2] && values[3] && values[4]) {
    int seen[7] = {0}; // To track dice values already contributing to the straight
printf("Small Straight-30 \n"); 
    for (int i = 0; i < size; i++) {
        if (dices[i] >= 1 && dices[i] <= 4) {
            if (seen[dices[i]] == 0) {
                // Mark the value as used in the straight
                seen[dices[i]] = 1;
                reroll[i] = false; // Keep this dice
            } else {
                // Duplicate value, mark for reroll
                reroll[i] = true;
            }
        } else {
            // Values outside the straight, mark for reroll
            reroll[i] = true;
        }
    }
   }
 else if (values[2] && values[3] && values[4] && values[5]) {
        printf("Small Straight-30 \n"); 
    int seen[7] = {0}; // To track dice values already contributing to the straight

    for (int i = 0; i < size; i++) {
        if (dices[i] >= 2 && dices[i] <= 5) {
            if (seen[dices[i]] == 0) {
                // Mark the value as used in the straight
                seen[dices[i]] = 1;
                reroll[i] = false; // Keep this dice
            } else {
                // Duplicate value, mark for reroll
                reroll[i] = true;
            }
        } else {
            // Values outside the straight, mark for reroll
            reroll[i] = true;
        }
    }
}
else if (values[3] && values[4] && values[5] && values[6]) {
    printf("Small Straight-30 \n"); 
    int seen[7] = {0}; // To track dice values already contributing to the straight

    for (int i = 0; i < size; i++) {
        if (dices[i] >= 3 && dices[i] <= 6) {
            if (seen[dices[i]] == 0) {
                // Mark the value as used in the straight
                seen[dices[i]] = 1;
                reroll[i] = false; // Keep this dice
            } else {
                // Duplicate value, mark for reroll
                reroll[i] = true;
            }
        } else {
            // Values outside the straight, mark for reroll
            reroll[i] = true;
        }
    }
}
 else if (values[1] && values[2] && values[3]) {
    int seen[7] = {0}; // To track dice values already contributing to the straight

    for (int i = 0; i < size; i++) {
        if (dices[i] >= 1 && dices[i] <= 3) {
            if (seen[dices[i]] == 0) {
                // Mark the value as used in the straight
                seen[dices[i]] = 1;
                reroll[i] = false; // Keep this dice
            } else {
                // Duplicate value, mark for reroll
                reroll[i] = true;
            }
        } else {
            // Values outside the straight, mark for reroll
            reroll[i] = true;
        }
    }

}
   else if (values[2] && values[3] && values[4]) {
    int seen[7] = {0}; // To track dice values already contributing to the straight

    for (int i = 0; i < size; i++) {
        if (dices[i] >= 2 && dices[i] <= 4) {
            if (seen[dices[i]] == 0) {
                // Mark the value as used in the straight
                seen[dices[i]] = 1;
                reroll[i] = false; // Keep this dice
            } else {
                // Duplicate value, mark for reroll
                reroll[i] = true;
            }
        } else {
            // Values outside the straight, mark for reroll
            reroll[i] = true;
        }
    } }
else if (values[3] && values[4] && values[5]) {
    int seen[7] = {0}; // To track dice values already contributing to the straight

    for (int i = 0; i < size; i++) {
        if (dices[i] >= 3 && dices[i] <= 5) {
            if (seen[dices[i]] == 0) {
                // Mark the value as used in the straight
                seen[dices[i]] = 1;
                reroll[i] = false; // Keep this dice
            } else {
                // Duplicate value, mark for reroll
                reroll[i] = true;
            }
        } else {
            // Values outside the straight, mark for reroll
            reroll[i] = true;
        }
    }
}
else if (values[4] && values[5] && values[6]) {
    int seen[7] = {0}; // To track dice values already contributing to the straight

    for (int i = 0; i < size; i++) {
        if (dices[i] >= 4 && dices[i] <= 6) {
            if (seen[dices[i]] == 0) {
                // Mark the value as used in the straight
                seen[dices[i]] = 1;
                reroll[i] = false; // Keep this dice
            } else {
                // Duplicate value, mark for reroll
                reroll[i] = true;
            }
        } else {
            // Values outside the straight, mark for reroll
            reroll[i] = true;
        }
    } } 
 // If no category detected, apply general reroll logic
   else { 
       int occurrences[6] = {0};

    // Count occurrences of each dice value
    for (int i = 0; i < size; i++) {
        occurrences[dices[i] - 1]++; // Increment the count for the dice value
    }

    // Decide which dice to reroll
    for (int i = 0; i < size; i++) {
        reroll[i] = (occurrences[dices[i] - 1] < 2); // Reroll dice with fewer than 2 matches
    }
   } }
   
   else { 
       int occurrences[6] = {0};

    // Count occurrences of each dice value
    for (int i = 0; i < size; i++) {
        occurrences[dices[i] - 1]++; // Increment the count for the dice value
    }

    // Decide which dice to reroll
    for (int i = 0; i < size; i++) {
        reroll[i] = (occurrences[dices[i] - 1] < 2); // Reroll dice with fewer than 2 matches
    }
   }

    // Re-roll marked dice
    for (int i = 0; i < size; i++) {
        if (reroll[i]) {
            dices[i] = (rand() % 6) + 1;
        }
    }
   return true;
}
bool computer_reroll_two(int dices[], int size, int UsedCategoryComp[],bool reroll[]) {
    printf("\n");
    
    int values[7] = {0};
        if (is_YAHTZEE(dices, size) && UsedCategoryComp[12] == 0) {
        for (int i = 0; i < size; i++) {
            reroll[i] = false; // Keep all dice
        } // Mark Yahtzee as used
        return false;
    }

    if (is_large_straight(dices, size) && UsedCategoryComp[10] == 0) {
        for (int i = 0; i < size; i++) {
            reroll[i] = false; // Keep all dice
        } // Mark large straight as used
        return false;
    }

    if (is_Full_House(dices, size) > 0 && UsedCategoryComp[8] == 0) {
        for (int i = 0; i < size; i++) {
            reroll[i] = false; // Keep all dice
        } // Mark full house as used
        return false;
    }
    if (UsedCategoryComp[8] == 1 && is_Full_House(dices, size) > 1) {
        for(int i=0;i<size;i++) {
        reroll[i]=false;} 
    }
    printf("\n");
    if (is_YAHTZEE(dices, size) && UsedCategoryComp[12] == 1) {
          for(int i=0;i<size;i++) {
        reroll[i]=false;}   
        }
    if (is_large_straight(dices, size) && UsedCategoryComp[10] == 1) {
            for(int i=0;i<size;i++) {
            reroll[i]=false;} 
        }
        
        for (int i = 0; i < size; i++) {
        if (dices[i] >= 1 && dices[i] <= 6) {
            values[dices[i]] = 1;
        }
    }
       if (UsedCategoryComp[10] == 0 || UsedCategoryComp[11] == 0) {
       if (values[1] && values[2] && values[3] && values[4]) {
    int seen[7] = {0}; // To track dice values already contributing to the straight
printf("Small Straight-30 \n"); 
    for (int i = 0; i < size; i++) {
        if (dices[i] >= 1 && dices[i] <= 4) {
            if (seen[dices[i]] == 0) {
                // Mark the value as used in the straight
                seen[dices[i]] = 1;
                reroll[i] = false; // Keep this dice
            } else {
                // Duplicate value, mark for reroll
                reroll[i] = true;
            }
        } else {
            // Values outside the straight, mark for reroll
            reroll[i] = true;
        }
    }
   }
 else if (values[2] && values[3] && values[4] && values[5]) {
        printf("Small Straight-30 \n"); 
    int seen[7] = {0}; // To track dice values already contributing to the straight

    for (int i = 0; i < size; i++) {
        if (dices[i] >= 2 && dices[i] <= 5) {
            if (seen[dices[i]] == 0) {
                // Mark the value as used in the straight
                seen[dices[i]] = 1;
                reroll[i] = false; // Keep this dice
            } else {
                // Duplicate value, mark for reroll
                reroll[i] = true;
            }
        } else {
            // Values outside the straight, mark for reroll
            reroll[i] = true;
        }
    }
}
else if (values[3] && values[4] && values[5] && values[6]) {
    printf("Small Straight-30 \n"); 
    int seen[7] = {0}; // To track dice values already contributing to the straight

    for (int i = 0; i < size; i++) {
        if (dices[i] >= 3 && dices[i] <= 6) {
            if (seen[dices[i]] == 0) {
                // Mark the value as used in the straight
                seen[dices[i]] = 1;
                reroll[i] = false; // Keep this dice
            } else {
                // Duplicate value, mark for reroll
                reroll[i] = true;
            }
        } else {
            // Values outside the straight, mark for reroll
            reroll[i] = true;
        }
    }
}
 else if (values[1] && values[2] && values[3]) {
    int seen[7] = {0}; // To track dice values already contributing to the straight

    for (int i = 0; i < size; i++) {
        if (dices[i] >= 1 && dices[i] <= 3) {
            if (seen[dices[i]] == 0) {
                // Mark the value as used in the straight
                seen[dices[i]] = 1;
                reroll[i] = false; // Keep this dice
            } else {
                // Duplicate value, mark for reroll
                reroll[i] = true;
            }
        } else {
            // Values outside the straight, mark for reroll
            reroll[i] = true;
        }
    }

}
   else if (values[2] && values[3] && values[4]) {
    int seen[7] = {0}; // To track dice values already contributing to the straight

    for (int i = 0; i < size; i++) {
        if (dices[i] >= 2 && dices[i] <= 4) {
            if (seen[dices[i]] == 0) {
                // Mark the value as used in the straight
                seen[dices[i]] = 1;
                reroll[i] = false; // Keep this dice
            } else {
                // Duplicate value, mark for reroll
                reroll[i] = true;
            }
        } else {
            // Values outside the straight, mark for reroll
            reroll[i] = true;
        }
    } }
else if (values[3] && values[4] && values[5]) {
    int seen[7] = {0}; // To track dice values already contributing to the straight

    for (int i = 0; i < size; i++) {
        if (dices[i] >= 3 && dices[i] <= 5) {
            if (seen[dices[i]] == 0) {
                // Mark the value as used in the straight
                seen[dices[i]] = 1;
                reroll[i] = false; // Keep this dice
            } else {
                // Duplicate value, mark for reroll
                reroll[i] = true;
            }
        } else {
            // Values outside the straight, mark for reroll
            reroll[i] = true;
        }
    }
}
else if (values[4] && values[5] && values[6]) {
    int seen[7] = {0}; // To track dice values already contributing to the straight

    for (int i = 0; i < size; i++) {
        if (dices[i] >= 4 && dices[i] <= 6) {
            if (seen[dices[i]] == 0) {
                // Mark the value as used in the straight
                seen[dices[i]] = 1;
                reroll[i] = false; // Keep this dice
            } else {
                // Duplicate value, mark for reroll
                reroll[i] = true;
            }
        } else {
            // Values outside the straight, mark for reroll
            reroll[i] = true;
        }
    } }

    // If no category detected, apply general reroll logic
   else { 
       int occurrences[6] = {0};

    // Count occurrences of each dice value
    for (int i = 0; i < size; i++) {
        occurrences[dices[i] - 1]++; // Increment the count for the dice value
    }

    // Decide which dice to reroll
    for (int i = 0; i < size; i++) {
        reroll[i] = (occurrences[dices[i] - 1] < 2); // Reroll dice with fewer than 2 matches
    }
   }
       }
        else { 
       int occurrences[6] = {0};

    // Count occurrences of each dice value
    for (int i = 0; i < size; i++) {
        occurrences[dices[i] - 1]++; // Increment the count for the dice value
    }

    // Decide which dice to reroll
    for (int i = 0; i < size; i++) {
        reroll[i] = (occurrences[dices[i] - 1] < 2); // Reroll dice with fewer than 2 matches
    }
   }
    for (int i = 0; i < size; i++) {
        if (reroll[i]) {
            dices[i] = (rand() % 6) + 1;
        }
    }
    return true;
}
/* @brief Updares and display User Score */
void updateScore(int *total, int moveScore) {
    *total += moveScore;
     printf("Your Score : %d\n",*total);

}

/* @brief Choose Computer scoring caregory
returns score*/
int computerMove(int dices[],int size,int UsedCategoryComp[],bool reroll[]) {
    int ComMove;
    printf("\n");
    
    if(is_YAHTZEE(dices, size)>1 && UsedCategoryComp[12] == 0)
            {   printf("Computer chose-YAHTZEE-50");
                UsedCategoryComp[12] = 1;
                return 50;
            }
    if(is_Four_of_a_kind(dices, size,reroll)>=8 && UsedCategoryComp[7] == 0){
        printf("Computer chose-");
             UsedCategoryComp[7] = 1;
            return is_Four_of_a_kind(dices, size,reroll);
        }
    if(is_large_straight(dices,size)>1 && UsedCategoryComp[10]==0 ) {
        printf("Computer chose-Large Straight-40");
        UsedCategoryComp[10] = 1;
        return 40;
    }
     if(is_Full_House(dices, size)>1 && UsedCategoryComp[8] == 0){
        printf("Computer chose-Full House-25");
        UsedCategoryComp[8] = 1;
        return 25;
        }
    if(is_small_straight(dices,size,reroll)>1 && UsedCategoryComp[9]==0 ) {
        printf("Computer chose-Small Straight-30");
        UsedCategoryComp[9] = 1;
        return 30;
    }
    if((is_Three_of_a_kind(dices, size,reroll))>=12 && UsedCategoryComp[6] == 0){
        printf("Computer chose-");
        UsedCategoryComp[6] = 1;
        return is_Three_of_a_kind(dices, size,reroll);
    }
  else {
    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
    int sum=0;
    for (int i = 0; i < 5; i++) {
        if(dices[i]==6) { a++;}
        if(dices[i]==5) { b++;}
        if(dices[i]==4) { c++;}
        if(dices[i]==3) {d++;}
        if(dices[i]==2) { e++;}
        if(dices[i]==1) { f++;}
        
        sum+=dices[i];
        
    }
    printf("Computer chose-");
    if (a >= b && a >= c && a >= d && a >= e && a >= f && UsedCategoryComp[5] == 0) {
        UsedCategoryComp[5] = 1;
        ComMove = (6 * a);
        printf("Sixes-");
    }
    else if (b >= c && b >= d && b >= e && b >= f && UsedCategoryComp[4] == 0) {
         UsedCategoryComp[4] = 1;
        ComMove = (5 * b); 
        printf("Fives-");
    }
    else if (c >= d && c >= e && c >= f && UsedCategoryComp[3] == 0) {
         UsedCategoryComp[3] = 1;
        ComMove = (4 * c); 
        printf("Fours-");
    }
    else if (sum>=19 && UsedCategoryComp[11] == 0) {
        UsedCategoryComp[11] = 1;
        return is_Chance(dices,size);
    }
    else if (d >= e && d >= f && UsedCategoryComp[2] == 0) {
         UsedCategoryComp[2] = 1;
        ComMove = (3 * d); 
        printf("Threes-");
    }
    else if (e >= f && UsedCategoryComp[1] == 0) {
         UsedCategoryComp[1] = 1;
        ComMove = (2 * e);  
        printf("Twos-");
    }
    else if(UsedCategoryComp[0] == 0) {
         UsedCategoryComp[0] = 1;
        ComMove = (1 * f);
        printf("Ones-");
    }
    else if(UsedCategoryComp[11] == 1) {
        if(UsedCategoryComp[12] == 0) {
            return is_YAHTZEE(dices, size);
           // printf("YAHTZEE-0\n");
            UsedCategoryComp[12] = 1;
        }
        if(UsedCategoryComp[10] == 0) {
            return is_large_straight(dices,size);
            //printf("Large Straight-0\n");
            UsedCategoryComp[10] =1;
        }
        if(UsedCategoryComp[7] == 0) {
            return is_Four_of_a_kind(dices, size,reroll);
            //printf("Four of a Kind-0\n");
            UsedCategoryComp[7] = 1;
        }
        
        if(UsedCategoryComp[9] == 0) {
            return is_small_straight(dices,size,reroll);
            //printf("Small Straight-0\n");
            UsedCategoryComp[9] ==1;
        }
    }
}
printf("%d",ComMove);
return ComMove;
}
/* @brief Updares and display Computer Score */
void updateCscore(int *Comtotal,int ComMove)
{
    *Comtotal+=ComMove;
    printf("\nComputer Score : %d\n",*Comtotal);
}
/* @brief display scores of a single gameround */
int Gameround(int round,int *total,int *Comtotal)
{
    printf("\nRound %d Score-        You:%d             vs      Computer:%d\n",round+1,*total,*Comtotal);
}
/* @brief Display Final Scores */
int EndGame(int round,int *total,int *Comtotal)
{
    printf("Calculating Final Scores....\n");
    printf("Final Score:        You:%d             vs      Computer:%d",*total,*Comtotal);
    
    if(*Comtotal>*total) {
        printf("\nCOMPUTER WINS BY %d",(*Comtotal-*total));
    }
    else {
        printf("YOU WIN BY %d",(*total-*Comtotal));
    }
}