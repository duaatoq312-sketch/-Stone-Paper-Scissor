#include<iostream>
#include<cstdlib>
using namespace std;
enum enwinner { Player1 = 1, Computer = 2, Draw = 3 };
enum enplayerchoice { stone = 1, paper = 2, scissor = 3 };

struct stRoundInfo
{
	short Round = 0;
	enplayerchoice Player1Choice;
	enplayerchoice ComputerChoice;
	enwinner RoundWinner;
	string WinnerName = "";
};
struct  stGameResult
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
};

short RoundNumber()
{
	short rounds = 0;
	do
	{
		cout << "How many rounds from 1 to 10 : ";
		cin >> rounds;
	} while (rounds < 1 || rounds >10);
	return rounds;
}

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void SetWinnerScreenColor(enwinner winner)
{

	switch (winner)
	{
	case enwinner::Computer:
		system("color 4F");
		cout << "\a";
		break;

	case enwinner::Player1:
		system("color 2F");
		break;

	case enwinner::Draw:
		system("color 6F");
		break;
	}
}

enplayerchoice GetUserChoice()
{
	short choice;
	do
	{
		cout << "\n Your choice : [1]:stone ,[2]:paper ,[3]:scissor : ";
		cin >> choice;
	} while (choice < 1 || choice>3);
	return enplayerchoice(choice);
}

enplayerchoice GetComputerChoice()
{
	return enplayerchoice(RandomNumber(1, 3));
}

enwinner WhoWinRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.ComputerChoice == RoundInfo.Player1Choice)
	{
		return enwinner::Draw;
	}

	switch (RoundInfo.Player1Choice)
	{
	case enplayerchoice::stone:
		if (RoundInfo.ComputerChoice == paper)
		{
			return enwinner::Computer;
			break;
		}
	case enplayerchoice::paper:
		if (RoundInfo.ComputerChoice == scissor)
		{
			return enwinner::Computer;
			break;
		}
	case enplayerchoice::scissor:
		if (RoundInfo.ComputerChoice == stone)
		{
			return enwinner::Computer;
			break;
		}
	}

	return enwinner::Player1;
}

string GetWinnerName(enwinner RoundWinner)
{
	switch (RoundWinner)
	{
	case enwinner::Computer:
		return "Computer";
		break;
	case enwinner::Player1:
		return "Player1";
		break;
	case enwinner::Draw:
		return "Draw";
	}
	return "";
}

string GetChoiceName(enplayerchoice choice)
{
	switch (choice)
	{
	case enplayerchoice::scissor:
		return "Scissor";
		break;
	case enplayerchoice::stone:
		return "Stone";
		break;
	case enplayerchoice::paper:
		return "Paper";
		break;
	}
	return "";
}

stGameResult FillGameResults(short ComputerWins, short Player1Wins, short DrawTimes, short gamerounds)
{
	stGameResult GameInfo;
	GameInfo.ComputerWinTimes = ComputerWins;
	GameInfo.Player1WinTimes = Player1Wins;
	GameInfo.DrawTimes = DrawTimes;
	GameInfo.GameRounds = gamerounds;
	return GameInfo;
}
enwinner FinalWinner(stGameResult GameResult)
{
	if (GameResult.ComputerWinTimes > GameResult.Player1WinTimes)
	{
		return enwinner::Computer;
	}
	else if (GameResult.Player1WinTimes > GameResult.ComputerWinTimes)
	{
		return enwinner::Player1;
	}
	else
	{
		return enwinner::Draw;
	}
}

string Tabs(short number)
{
	string t = "";
	for (int i = 1; i <= number; i++)
	{
		t = t + "\t";
	}
	return t;
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
	cout << "\n____________ Round [" << RoundInfo.Round << "] ____________\n\n";
	cout << "Player1 Choice: " << GetChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice: " << GetChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
	cout << "_________________________________________\n" << endl;
}
void ShowGameOver()
{
	cout << Tabs(2) << "-------------------------------------------------\n\n";
	cout << Tabs(2) << "                 *** Game Over ***    \n";
	cout << Tabs(2) << "-------------------------------------------------\n\n";

}
void ShowGameResult(stGameResult GameResult)
{
	cout << Tabs(2) << "--------------------[Game Result]-----------------------\n\n";
	cout << Tabs(2) << "Game Rounds: " << GameResult.GameRounds << endl;
	cout << Tabs(2) << "Player1 won times :" << GameResult.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer won times: " << GameResult.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw Times: " << GameResult.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner: ";
	cout << GetWinnerName(FinalWinner(GameResult));
	cout << Tabs(2) << "\n------------------------------------------------------------\n\n";

}

stGameResult PlayGame(short gamerounds)

{
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	for (short round = 1; round <= gamerounds; round++)
	{
		cout << "\nRound [" << round << "] begins : \n";
		RoundInfo.Round = round;
		RoundInfo.Player1Choice = GetUserChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.RoundWinner = WhoWinRound(RoundInfo);
		RoundInfo.WinnerName = GetWinnerName(RoundInfo.RoundWinner);

		if (RoundInfo.RoundWinner == Computer)
		{
			ComputerWinTimes += 1;
		}
		else if (RoundInfo.RoundWinner == Player1)
		{
			Player1WinTimes += 1;
		}
		else
		{
			DrawTimes += 1;
		}

		SetWinnerScreenColor(RoundInfo.RoundWinner);

		PrintRoundResult(RoundInfo);

	}

	return FillGameResults(ComputerWinTimes, Player1WinTimes, DrawTimes, gamerounds);

}


void StartGame()
{
	char PlayAgain = 'y';
	do
	{
		ResetScreen();
		stGameResult GameResult = PlayGame(RoundNumber());
		ShowGameOver();
		ShowGameResult(GameResult);
		cout << "Do you want to play again? (Y|N)  ";
		cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

}