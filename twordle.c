// Austin Marshall tries to make WORDLE wait i mean Twordle
// Using the new knowledge of 2d arrays and eventually arrays of arrays

#include <stdio.h>
#define CAP 40 //Max word length for guess
#define LENGTH 5 //Max word length
#define MAX 6 //Max Guesses

void WordCheck(char Guess[CAP]); //Checks word for invalid characters

void UserFailed(char Guess[CAP], int lFailure, int cFailure); //Prompts user for reentering guess when needed

void WordWork(char Guess[CAP]); //Makes to word all lowercase for easier comparisons later

int GuessIntializing(char Guess[CAP], int GuessNumber, char Board[][CAP], char MysteryWord[]); //Gets word and figures out how the user did

void ClearBoard(char Board[][CAP]); //Makes the board not JUNK!

_Bool WinCheck(char MysteryWord[], char Guess[]); //Checks if the user won

void RightSpot(char MysteryWord[], char Guess[], char Board[][CAP], int GuessNumber); //Will capitalize if the letter is correct in that spot

void RightLetter(char MysteryWord[], char Guess[], char Board[][CAP], int GuessNumber); //Will add the character underneath if this letter is in the word

void ResetMystery(char MysteryWord[]); //Mystery word may have been capitalize to not double up on comparisons, so reset it back to lowercase

void DisplayBoard(char Board[][CAP], int GuessNumber); //Displays all their guesses and tell thems how close they are

int main()
{
		
	char MysteryWord[CAP];
	char capMysteryWord[CAP];
	char Guess[CAP], Board[CAP][CAP];
	int I = 0, GuessNumber = 0;
	_Bool Win = 0;

	
	
	FILE* Fileptr;
	Fileptr = fopen("mystery.txt", "r");
	
	if(Fileptr == NULL) //Check whether file works
	{
		return 0;
	}	
	
	fscanf(Fileptr, "%s", MysteryWord);
	
	fclose(Fileptr);
	
	for(I = 0; MysteryWord[I] != '\0'; I++) //Makes winning text string
	{
		capMysteryWord[I] = (MysteryWord[I] - ('a' - 'A'));
	}
	
	ClearBoard(Board);
	
	for(I = 0; I < MAX; I++) //Playing the game
	{
		GuessNumber = I;
		Win = GuessIntializing(Guess, GuessNumber, Board, MysteryWord);
		
		ResetMystery(MysteryWord);
		
		if(Win) //If they win they win!!!!!!!
		{
			printf("                %s           \n", capMysteryWord);
			
			if(GuessNumber ==  0)
			{
			printf("        You won in %d guess!     \n", GuessNumber + 1);
			}
			else
			{
			printf("        You won in %d guesses!   \n", GuessNumber + 1);
			}
			
			switch(GuessNumber) //Determines Hype
			{
				case 0: printf("                GOATED!         \n");
				break;
				case 1:
				case 2: printf("                Awesome!        \n");
				break;
				case 3:
				case 4: printf("                Nice!           \n");
				break;
				case 5: printf("                                \n");
				break;			
			}
			
			return 0; //End function if the user guesses correctly
		}
	
		DisplayBoard(Board, GuessNumber);
		
	}

	
	
	return 0;
}

void WordCheck(char Guess[CAP]) //Checks word for invalid characters
{
	int lFailure = 0, cFailure = 0; //lFailure = length error, cFailure = character error
	int i = 0;
	
	for(i = 0; i < 5; i++) //Check all characters for bad characters or spaces
	{
		
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
	for(int i = 0; i < LENGTH; i++)
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
		
	if(GuessNumber < 5)
	{
	printf("GUESS %d! Enter your guess: ", GuessNumber + 1);
	scanf("%s", Guess);
	}
	else
	{
	printf("FINAL GUESS : ");
	scanf("%s", Guess);
	}
	WordCheck(Guess);
	WordWork(Guess);
	
	printf("================================\n");
	
	for(int cI = 0; cI < LENGTH; cI++)
	{
		Board[GuessNumber * 2][cI] = Guess[cI];	  //Puts guess in board and then modifies it later based on correctness
		Board[((GuessNumber * 2) + 1)][cI] = ' '; //Sets up board for easier displaying

	}
	
	Win = WinCheck(MysteryWord, Guess); //Does user win, if so stop
	if(Win)
	{
		return Win;
	}
	
	RightSpot(MysteryWord, Guess, Board, GuessNumber);

	RightLetter(MysteryWord, Guess, Board, GuessNumber);
	
	return Win;

}

void ClearBoard(char Board[][CAP]) //Makes the board not JUNK!
{

	for(int rI = 0; rI < CAP; rI++)
	{
		for(int cI = 0; cI < CAP; cI++)
		{
			Board[rI][cI] = '\0'; //No junk plus should be easier to display
		}
	}
	
}

_Bool WinCheck(char MysteryWord[], char Guess[]) //Checks if the user won
{
	int CheckCounter = 0;
	_Bool Win = 0;
	for(int I = 0; MysteryWord[I] != '\0'; I++) //Go till words end. Both are both 5 letter words by this point so no need for wordlength
	{
		
		if((MysteryWord[I] == Guess[I])) //Checks each letter for match
		{
			CheckCounter++;
		}

	}
	
		
	if(CheckCounter == LENGTH) // Do all letters match?
	{
		Win = 1;
	}
	else 
	{
		Win = 0;
	}
	
	return Win; //Returns whether user wins or not 
	
}

void RightSpot(char MysteryWord[], char Guess[], char Board[][CAP], int GuessNumber) //Will capitalize if the letter is correct in that spot
{
	
	for(int rI = 0; MysteryWord[rI] != '\0'; rI++) 
	{
		if(MysteryWord[rI] == Guess[rI]) //if guess letter is right and in the right spot
		{
			Board[GuessNumber*2][rI] = (Guess[rI] - ('a' - 'A')); //then capitalize
			MysteryWord[rI] = (MysteryWord[rI] - ('a' -'A')); //Makes it a capital so that when checking for correct letters in wrong spot it doesn't work for this letter.
		}
	}
	
}

void RightLetter(char MysteryWord[], char Guess[], char Board[][CAP], int GuessNumber) //Will add the character underneath if this letter is in the word
{


	for(int I = 0; Guess[I] != '\0'; I++)
	{
		for(int rI = 0; MysteryWord[rI] != '\0'; rI++)
		{
			if(MysteryWord[rI] == Guess[I])
			{
				Board[(GuessNumber * 2) + 1][I] = '^'; //If that first appearence of a letter in a word is in the mystery word tell them
				MysteryWord[rI] = (MysteryWord[rI] - ('a' - 'A')); //Makes this letter unabled to be compared too because it's a capital now
			}
		}
	}
}

void ResetMystery(char MysteryWord[]) //Mystery word may have been capitalize to not double up on comparisons, so reset it back to lowercase
{
	for(int I = 0; MysteryWord[I] != '\0'; I++)
	{
		if(MysteryWord[I] >= 'A' && MysteryWord[I] < 'Z')
		{
			MysteryWord[I] = (MysteryWord[I] + ('a' - 'A'));
		}
	}
}

void DisplayBoard(char Board[][CAP], int GuessNumber) //Displays all their guesses and tell thems how close they are
{
	for(int rI = 0; rI < ((GuessNumber * 2) + 2); rI++)
	{
		printf("%s\n", Board[rI]); //Hopefully this works
	}
}
