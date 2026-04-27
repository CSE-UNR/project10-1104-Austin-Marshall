// Austin Marshall tries to make WORDLE wait i mean Twordle
// Using the new knowledge of 2d arrays and eventually arrays of arrays

#include <stdio.h>
#define CAP 40

void WordCheck(char Guess[CAP]); //Checks word for invalid characters

void UserFailed(char Guess[CAP], int lFailure, int cFailure); //Prompts user for reentering guess when needed

void WordWork(char Guess[CAP]); //Makes to word all lowercase for easier comparisons later

int GuessIntializing(char Guess[CAP], int GuessNumber, char Board[][CAP], char MysteryWord[]); //Gets word and figures out how the user did

void ClearBoard(char Board[][CAP]); //Makes the board not JUNK!

_Bool WinCheck(char MysteryWord[], char Guess[]); //Checks if the user won

int main()
{
		
	char MysteryWord[CAP];
	char Guess[CAP], Board[CAP][CAP];
	int GuessNumber = 0;
	_Bool Win = 0;

	
	
	FILE* Fileptr;
	Fileptr = fopen("mystery.txt", "r");
	
	if(Fileptr == NULL) //Check whether file works
	{
		return 0;
	}	
	
	fscanf(Fileptr, "%s", MysteryWord);
	printf("%s\n", MysteryWord);
	
	fclose(Fileptr);
	
	ClearBoard(Board);
	
	Win = GuessIntializing(Guess, GuessNumber, Board, MysteryWord);

	
	if(Win)
	{
		printf("================================\n");
		printf("                SOUND           \n");
		printf("        You won in   guesses!   \n");
		printf("                Nice!           \n");
	}


	
	return 0;
}

void WordCheck(char Guess[CAP]) //Checks word for invalid characters
{
	int lFailure = 0, cFailure = 0; //lFailure = length error, cFailure = character error
	int i = 0;
	
	for(i = 0; i < 5; i++) //Check all characters for bad characters or spaces
	{
		printf("%c\n", Guess[i]);
		
		if(Guess[i] >= 'A' && Guess[i] <= 'Z')
		{

		}
		else if(Guess[i] >= 'a' && Guess[i] <= 'z')
		{
		
		}
		else if(Guess[i] == ' ')
		{
			lFailure = 1;
		}
		else if(Guess[i] == '\0')
		{
			lFailure = 1;
		}
		else 
		{
			cFailure = 1;
		}
	}
	
	if(Guess[i] != '\0') //Does word end at 5 letters?
	{
		lFailure = 1;
	}
	
	printf("WordCheck\n");
	UserFailed(Guess, lFailure, cFailure); //Checks if user entered an invalid word and prompts for new one
}

void UserFailed(char Guess[CAP], int lFailure, int cFailure)
{
	if(lFailure == 1 && cFailure == 0) //Not exactly 5 letters or spaces
	{
		printf("Your guess must be 5 letters long.\n");
		printf("Please try again: ");
		scanf("%s", Guess);
		WordCheck(Guess);
	}
	else if(lFailure == 0 && cFailure == 1) //Weird characters
	{
		printf("Your guess must contain only letters.\n");
		printf("Please try again: ");
		scanf("%s", Guess);
		WordCheck(Guess);
	}
	else if(lFailure == 1 && cFailure == 1) //Not exactly 5 letters or spaces and Weird characters
	{
		printf("Your guess must be 5 letters long.Your guess must contain only letters.\n");
		printf("Please try again: ");
		scanf("%s", Guess);
		WordCheck(Guess);
	}
	else //WORD IS GOOD
	{
	
	}
}

void WordWork(char Guess[CAP]) //Makes to word all lowercase for easier comparisons later
{
	for(int i = 0; i < 5; i++)
	{
		if(Guess[i] >= 'A' && Guess[i] <= 'Z')
		{
			Guess[i] = Guess[i] + ('a' - 'A');
		}
		else
		{
		
		}
	}
}

int GuessIntializing(char Guess[CAP], int GuessNumber, char Board[][CAP], char MysteryWord[]) //Gets word and figures out how the user did
{
		
	_Bool Win = 0;	
		
	printf("GUESS %d! Enter your guess: ", GuessNumber);
	scanf("%s", Guess);
	printf("%s\n", Guess);
	WordCheck(Guess);
	WordWork(Guess);
	printf("%s\n", Guess);
	
	Win = WinCheck(MysteryWord, Guess); //Does user win, if so stop
	if(Win)
	{
		return Win;
	}

	
	return 0;

}

void ClearBoard(char Board[][CAP]) //Makes the board not JUNK!
{
	printf("BoardClearing");
	for(int rI = 0; rI < CAP; rI++)
	{
		for(int cI = 0; cI < CAP; cI++)
		{
			Board[rI][cI] = '\0';
		}
	}
	
}

_Bool WinCheck(char MysteryWord[], char Guess[]) //Checks if the user won
{
	printf("Check");
	int CheckCounter = 0;
	_Bool Win = 0;
	for(int I = 0; MysteryWord[I] != '\0'; I++) //Go till words end. Both are both 5 letter words by this point so no need for wordlength
	{
		if((MysteryWord[I] = Guess[I])) //Checks each letter for match
		{
			CheckCounter++;
			printf("%d\n", CheckCounter);
		}
		
		if(CheckCounter == 5) // Do all letters match?
		{
			Win = 1;
		}
	}
	
	return Win; //Returns whether user wins or not 
	
}

