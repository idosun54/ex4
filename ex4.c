#include <stdio.h>
#include <string.h>


/***************************
******** Menu Items ********
****************************/

#define REVERSE 1
#define PALINDROME 2
#define SENTENCES 3
#define ZIP 4
#define SUDOKU 5
#define EXIT 6


/***************************
*** DIMENSION PARAMETERS ***
****************************/

#define LONGEST_TERM 20
#define LONGEST_SENTENCE 62
#define MAX_NUMBER_OF_TERMS 10

#define ZIP_MAX_GRID_SIZE 20

#define SUDOKU_GRID_SIZE 9
#define SUDOKU_SUBGRID_SIZE 3


/***************************
* USER INTEFACE PROTOTYPES *
****************************/

void task1ReversePhrase();
void task2CheckPalindrome();
void task3GenerateSentences();
void task4SolveZipBoard();
void task5SolveSudoku();


/****************************
* IMPLEMENTATION PROTOTYPES *
*****************************/

void task1ReversePhraseImplementation();
int task2CheckPalindromeImplementation(int);
void task3GenerateSentencesImplementation(char[][LONGEST_TERM+1], int, char[][LONGEST_TERM+1], int,
                                            char[][LONGEST_TERM+1], int);
int task4SolveZipBoardImplementation(int[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                        char[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], int, int, int, int);
int task5SolveSudokuImplementation(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]);


/******************************
* HELPER FUNCTIONS PROTOTYPES *
*******************************/

int readTerms(char[][LONGEST_TERM+1], int, char[]);
void printSudoku(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]);
int task3Help(int, char[][LONGEST_TERM+1]);
int task4HelpBoardFull(int[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], int , int , int);
int task5CanPlace(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int , int , int , int);
int task5TryNum(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int , int , int);
int task5Helper(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int , int);



/******************************
********** MAIN MENU **********
*******************************/

int main()
{
    int task;
    do
    {
        printf("Please choose a task (1-5) or 6 to exit:\n");
        printf("%d. Reverse a phrase\n", REVERSE);
        printf("%d. Check Palindrome\n", PALINDROME);
        printf("%d. Generate sentences\n", SENTENCES);
        printf("%d. Solve Zip Board\n", ZIP);
        printf("%d. Solve Sudoku\n", SUDOKU);
        printf("%d. Exit\n", EXIT);

        scanf(" %d", &task);
        scanf("%*c");
        switch (task)
        {
        case REVERSE:
            task1ReversePhrase();
            break;
        case PALINDROME:
            task2CheckPalindrome();
            break;
        case SENTENCES:
            task3GenerateSentences();
            break;
        case ZIP:
            task4SolveZipBoard();
            break;
        case SUDOKU:
            task5SolveSudoku();
            break;
        case EXIT:
            printf("Goodbye!\n");
            break;
        default:
            printf("Please choose a task number from the list.\n");
            break;
        }
        printf("\n=============================\n\n");
    } while (task != EXIT);

    return 0;
}


/***************************
****** USER INTERFACE ******
****************************/


void task1ReversePhrase()
{
    printf("Please insert the phrase to reverse:\n");
    task1ReversePhraseImplementation();
    printf("\n");
}


void task2CheckPalindrome()
{
    printf("Please insert the phrase length:\n");
    int n;
    scanf("%d", &n);
    printf("Please insert the phrase to check:\n");
    scanf(" ");
    if (task2CheckPalindromeImplementation(n))
        printf("The phrase is a palindrome.\n");
    else
        printf("The phrase is not a palindrome.\n");
}


void task3GenerateSentences()
{
    char subjects[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    char verbs[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    char objects[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    int subjectsCount, verbsCount, objectsCount;

    subjectsCount=readTerms(subjects, MAX_NUMBER_OF_TERMS, "subjects");
    verbsCount=readTerms(verbs, MAX_NUMBER_OF_TERMS, "verbs");
    objectsCount=readTerms(objects, MAX_NUMBER_OF_TERMS, "objects");
    printf("List of Sentences:\n");
    task3GenerateSentencesImplementation(subjects, subjectsCount, verbs, verbsCount, objects, objectsCount);
}


void task4SolveZipBoard()
{
    int size;
    int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};
    char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};
    int row, col;
    int highest=0;
    printf("Please enter the board size:\n");
    scanf("%d", &size);
    if (size < 1 || size > ZIP_MAX_GRID_SIZE)
    {
        printf("Invalid board size.\n");
        return;
    }

    printf("Please enter the grid:\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 1)
            {
                row = i;
                col = j;
            }
            if(board[i][j]>highest){
                highest=board[i][j];
            }
        }
    }
    if (task4SolveZipBoardImplementation(board, solution, size, row, col, highest))
    {
        printf("Solution:\n");
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%c ", solution[i][j] ? solution[i][j] : 'X');
            }
            printf("\n");
        }
    }
    else
    {
        printf("No solution exists.\n");
    }
}


void task5SolveSudoku()
{
    printf("Please enter the sudoku board:\n");
    int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE] = {0};
    for (int i = 0; i < SUDOKU_GRID_SIZE; i++)
    {
        for (int j = 0; j < SUDOKU_GRID_SIZE; j++)
        {
            scanf("%d", &board[i][j]);
        }
    }
    if (task5SolveSudokuImplementation(board))
    {
        printf("Solution found:\n");
        printSudoku(board);
    }
    else
    {
        printf("No solution exists.\n");
    }
}


/***************************
********* HELPERS **********
****************************/


int readTerms(char terms[][LONGEST_TERM+1], int maxNumOfTerms, char type[]){
    int termsCount;
    printf("Please insert number of %s:\n", type);
    scanf("%d", &termsCount);
    if(termsCount < 1 || termsCount > maxNumOfTerms){
        termsCount = maxNumOfTerms;
    }
    printf("Please insert the list of %s:\n", type);
    for(int i=0;i<termsCount;i++){
        printf("%d. ",i+1);
        scanf(" %[^\n]",terms[i]);
    }
    return termsCount;
}


void printSudoku(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE])
{
    printf("+-------+-------+-------+\n");
    for (int i = 0; i < SUDOKU_GRID_SIZE; i++)
    {
        printf("| ");
        for (int j = 0; j < SUDOKU_GRID_SIZE; j++)
        {
            if (board[i][j] == 0)
                printf(". ");
            printf("%d ", board[i][j]);

            if ((j + 1) % SUDOKU_SUBGRID_SIZE == 0)
                printf("| ");
        }
        printf("\n");
        if ((i + 1) % SUDOKU_SUBGRID_SIZE == 0)
            printf("+-------+-------+-------+\n");
    }
}

//Returns the number of terms in a given array
int task3Help(int i, char terms[][LONGEST_TERM+1])
{
    if((terms[i][0]!='\0')&&(i<MAX_NUMBER_OF_TERMS))
     i= task3Help(i+1, terms);

  return i;
}

//Checks if zip board is full
int task4HelpBoardFull(int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], int size, int rows, int cols)
{
  {
    if (rows >= size) 
        return 1;
    

    if (cols >= size) 
        return task4HelpBoardFull(board, size, rows+1, 0);
    

    if (board[rows][cols] == 0) 
        return 0;
    
    return task4HelpBoardFull(board, size, rows, cols+1);
}
}

//Checks if placement is legal
int task5CanPlace(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int r, int c, int num, int i) 
{
    if (i==SUDOKU_GRID_SIZE) 
        return 1;

    if (board[r][i]==num) 
     return 0;


    if (board[i][c]==num) 
     return 0;

    
    int startRow = r - (r%SUDOKU_SUBGRID_SIZE);
    int startCol = c - (c%SUDOKU_SUBGRID_SIZE);
    if (board[startRow+(i/SUDOKU_SUBGRID_SIZE)][startCol +(i%SUDOKU_SUBGRID_SIZE)]==num) 
        return 0;

    return task5CanPlace(board, r, c, num, i + 1);
}

//Places num on board
int task5TryNum(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int r, int c, int num) 
{
    
    if (num>9) 
     return 0; 
    

    if (task5CanPlace(board, r, c, num, 0)) 
    {
      board[r][c]=num; 
      if (task5SolveSudokuImplementation(board))
       return 1;
        
      board[r][c] = 0;
    }

    return task5TryNum(board, r, c, num+1);
}

//Ties everything together
int task5Helper(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int r, int c)
{
   if (c==SUDOKU_GRID_SIZE) {
    return task5Helper(board, r+1, 0);
   }
    if (r==SUDOKU_GRID_SIZE) 
     return 1;
    

    if (board[r][c]!=0) 
     return task5Helper(board, r, c+1);
    
    return task5TryNum(board, r, c, 1);
}

/***************************
*********** TODO ***********
****************************/


void task1ReversePhraseImplementation(){
    int p=getchar();
    if(p=='\n'){
      printf("The reversed phrase is:\n");
      return;
    }
    task1ReversePhraseImplementation();
    printf("%c", p);
}


int task2CheckPalindromeImplementation(int length)
{   int p1, p2;
    p1=getchar();
    if(length-2==0)
    {
        p2=getchar();
        if(p2==p1)
         return 1;
        return 0;
    }
    else if(length-1==0) {
     return 1;
    }

    else if(task2CheckPalindromeImplementation(length-2))
    {
       int p2=getchar();
       if(p1==p2)
        return 1;
    }
    getchar();
    return 0;
}


void task3GenerateSentencesImplementation(char subjects[][LONGEST_TERM+1], int subjectsCount,
                                            char verbs[][LONGEST_TERM+1], int verbsCount,
                                            char objects[][LONGEST_TERM+1], int objectsCount)
{
char arr[LONGEST_SENTENCE+1]={};
     int i=0;
     int k=0;
    
     //Logic for the count
    int totalSub = task3Help(0, subjects);
    int totalVerb = task3Help(0, verbs);
    int totalObj = task3Help(0, objects);
   
    int tempSub = totalSub - subjectsCount; 
    int tempVerb = totalVerb - verbsCount;
    int tempObj = totalObj - objectsCount;

    int fakeCount = (tempSub * totalVerb * totalObj) + (tempVerb * totalObj) + (tempObj + 1);
    int count = (totalSub * totalVerb * totalObj) - fakeCount + 1;

        if(objectsCount>1){
           strcat(arr, subjects[subjectsCount-1]);
           strcat(arr, " ");
           strcat(arr, verbs[verbsCount-1]);
           strcat(arr, " ");
           strcat(arr, objects[objectsCount-1]);
          task3GenerateSentencesImplementation(subjects, subjectsCount, verbs, verbsCount, objects, objectsCount-1);
          k++;
         }

        if(verbsCount>1&&k==0){
          strcat(arr, subjects[subjectsCount-1]);
          strcat(arr, " ");
          strcat(arr, verbs[verbsCount-1]);
          strcat(arr, " ");
          strcat(arr, objects[objectsCount-1]);

           if(objectsCount==1){
            objectsCount=task3Help(objectsCount-1, objects);
          }
          task3GenerateSentencesImplementation(subjects, subjectsCount, verbs, verbsCount-1, objects, objectsCount);
          i++;
         }
          
        if(subjectsCount>1&&i==0&&k==0){
           strcat(arr, subjects[subjectsCount-1]);
           strcat(arr, " ");
           strcat(arr, verbs[verbsCount-1]);
           strcat(arr, " ");
           strcat(arr, objects[objectsCount-1]);
           if(objectsCount==1){
            objectsCount=task3Help(objectsCount-1, objects);
            }
           if(verbsCount==1){
            verbsCount=task3Help(verbsCount-1, verbs);
            }
           task3GenerateSentencesImplementation(subjects, subjectsCount-1, verbs, verbsCount, objects, objectsCount);
          }

         if(subjectsCount==1&&objectsCount==1&&verbsCount==1)
         { 
           strcat(arr, subjects[subjectsCount-1]);
           strcat(arr, " ");
           strcat(arr, verbs[verbsCount-1]);
           strcat(arr, " ");
           strcat(arr, objects[objectsCount-1]);
         }

          printf("%d. ", count);
          printf("%s\n", arr);
          return;
}



int task4SolveZipBoardImplementation(int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                    char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                    int size, int startR, int startC, int highest)
{
    //checks if board is filled correctly
    if (board[startR][startC]==highest) 
    {
        if (task4HelpBoardFull(board, size, 0, 0)) {
            return 1; 
        }
        return 0;
    }
   
    //checks if next number is close
   if(startR>0&&board[startR][startC]+1==board[startR-1][startC])
     {
       solution[startR][startC]='U';
       if(task4SolveZipBoardImplementation(board, solution, size, startR-1, startC, highest))
        return 1;
       solution[startR][startC]='X';
     }

   if(startR<size-1&&board[startR][startC]+1==board[startR+1][startC])
   {
     solution[startR][startC]='D';
     if(task4SolveZipBoardImplementation(board, solution, size, startR+1, startC, highest))
        return 1;
       solution[startR][startC]='X';
   }

   if(startC>0&&board[startR][startC]+1==board[startR][startC-1])
   {
     solution[startR][startC]='L';
     if(task4SolveZipBoardImplementation(board, solution, size, startR, startC-1, highest))
        return 1;
       solution[startR][startC]='X';
   }

   if(startC<size-1&&board[startR][startC]+1==board[startR][startC+1])
   {
     solution[startR][startC]='R';
     if(task4SolveZipBoardImplementation(board, solution, size, startR, startC+1, highest))
        return 1;
       solution[startR][startC]='X';
   }
   
   //checks for empty spaces and moves with priority
   if(startR>0&&board[startR-1][startC]==0)
   {
     board[startR-1][startC]=board[startR][startC];
     solution[startR][startC]='U';
     if(task4SolveZipBoardImplementation(board, solution, size, startR-1, startC, highest))
        return 1;
     board[startR-1][startC]=0;
     solution[startR][startC]='X';
   }

  if(startR<size-1&&board[startR+1][startC]==0)
   {
     board[startR+1][startC]=board[startR][startC];
     solution[startR][startC]='D';
     if(task4SolveZipBoardImplementation(board, solution, size, startR+1, startC, highest))
        return 1;
     board[startR+1][startC]=0;
     solution[startR][startC]='X';
   }

   if(startC>0&&board[startR][startC-1]==0)
   {
     board[startR][startC-1]=board[startR][startC];
     solution[startR][startC]='L';
     if(task4SolveZipBoardImplementation(board, solution, size, startR, startC-1, highest))
        return 1;
     board[startR][startC-1]=0;
     solution[startR][startC]='X';
   }

   if(startC<size-1&&board[startR][startC+1]==0)
   {
     board[startR][startC+1]=board[startR][startC];
     solution[startR][startC]='R';
     if(task4SolveZipBoardImplementation(board, solution, size, startR, startC+1, highest))
        return 1;
     board[startR][startC+1]=0;
     solution[startR][startC]='X';
   }

    return 0;
}

int task5SolveSudokuImplementation(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE])
{
  if(task5Helper(board, 0, 0))
    return 1;

  return 0;
}