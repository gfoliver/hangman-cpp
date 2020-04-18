#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>
#include <stdlib.h>

using namespace std;

// ----- VARIABLES ----- //
bool won = false, lost = false;

char gameChars[50], guessedLetters[50], wrongLetters[50], letter;

string GameWord;

int guesses = 0, ok = 0, correctLetters = 0, different = 0, error = 0;


// ------ FUNCTIONS ----- //

//Function to print messages in the Game
void PrintMessage(string msg)
{
	//Centralize the text
	bool side = true;

	for (int i = msg.length(); i < 30; i++) {
		if (side)
			msg = " " + msg;
		else
			msg = msg + " ";

		side = !side;
	}

	cout << msg.c_str();
}

//Function to read the game words and select a word
string SelectWord()
{
	int lines = 0;
	string SelectedWord;
	vector<string> words;

	time_t t;
	srand((unsigned)time(&t));

	//Read the file
	ifstream read("./gamewords.txt");
	if (read.is_open()) {	// if the reader succesfully opened
		while (getline(read, SelectedWord)) {	// while it is able to read the lines
			words.push_back(SelectedWord);
		}

		int wordL = rand() % words.size();	// get a random index inside the size of the vector

		SelectedWord = words.at(wordL);		//Select the word with the random index

		for (int i = 0; i < SelectedWord.length(); i++) {
			if (SelectedWord[i] > 96 && SelectedWord[i] < 123)
				SelectedWord[i] -= 32;
		}
	}

	return SelectedWord;

}

//Function to start or restart the game
void Start()
{
	system("cls");

	won = false;
	lost = false;

	guesses = 0;
	ok = 0;
	correctLetters = 0;
	different = 0;
	error = 0;

	//Set the Game Characters as underscore so they appear hidden
	for (int i = 0; i < GameWord.length(); i++) {
		gameChars[i] = '_';
	}
}

//Function to Draw the Game
void DrawGame()
{

	//Header
	cout << endl;
	PrintMessage("HANGMAN");
	cout << endl << endl;
	cout << "------------------------------" << endl;

	//Errors
	cout << endl;
	cout << "  Wrong Letters: ";
	for (int i = 0; i < error; i++) {
		if (i == 0)
			cout << wrongLetters[i];
		else
			cout << " " << wrongLetters[i];
	}

	cout << endl << endl;
	cout << "------------------------------" << endl;

	//Hangman
	cout << endl;
	switch (error) {
		case 0:
			cout << "      __________              " << endl;
			cout << "     |        ||              " << endl;
			cout << "     |       ----             " << endl;
			cout << "     |                        " << endl;
			cout << "     |                        " << endl;
			cout << "     |                        " << endl;
			cout << "     |                        " << endl;
			cout << "    _|_                       " << endl;
		break;
		case 1:
			cout << "      __________              " << endl;
			cout << "     |        ||              " << endl;
			cout << "     |       ----             " << endl;
			cout << "     |        ()              " << endl;
			cout << "     |                        " << endl;
			cout << "     |                        " << endl;
			cout << "     |                        " << endl;
			cout << "    _|_                       " << endl;
		break;
		case 2:
			cout << "      __________              " << endl;
			cout << "     |        ||              " << endl;
			cout << "     |       ----             " << endl;
			cout << "     |        ()              " << endl;
			cout << "     |        ||              " << endl;
			cout << "     |        ||              " << endl;
			cout << "     |                        " << endl;
			cout << "    _|_                       " << endl;
		break;
		case 3:
			cout << "      __________              " << endl;
			cout << "     |        ||              " << endl;
			cout << "     |       ----             " << endl;
			cout << "     |        ()              " << endl;
			cout << "     |       /||              " << endl;
			cout << "     |      / ||              " << endl;
			cout << "     |                        " << endl;
			cout << "    _|_                       " << endl;
		break;
		case 4:
			cout << "      __________              " << endl;
			cout << "     |        ||              " << endl;
			cout << "     |       ----             " << endl;
			cout << "     |        ()              " << endl;
			cout << "     |       /||\\             " << endl;
			cout << "     |      / || \\            " << endl;
			cout << "     |                        " << endl;
			cout << "    _|_                       " << endl;
		break;
		case 5:
			cout << "      __________              " << endl;
			cout << "     |        ||              " << endl;
			cout << "     |       ----             " << endl;
			cout << "     |        ()              " << endl;
			cout << "     |       /||\\             " << endl;
			cout << "     |      / || \\            " << endl;
			cout << "     |       /                " << endl;
			cout << "    _|_     -                 " << endl;
		break;
		case 6:
			cout << "      __________              " << endl;
			cout << "     |        ||              " << endl;
			cout << "     |       ----             " << endl;
			cout << "     |        ()              " << endl;
			cout << "     |       /||\\             " << endl;
			cout << "     |      / || \\            " << endl;
			cout << "     |       /  \\             " << endl;
			cout << "    _|_     -    -            " << endl;
		break;
	}
	cout << "---|___|----------------------" << endl;
	cout << endl;
	
	//Game Characters
	string characters = " ";

	for (int i = 0; i < GameWord.length(); i++) {
		characters = characters + gameChars[i] + " ";
	}


	PrintMessage(" WORD: ");
	cout << endl << endl;

	PrintMessage(characters);
	cout << endl << endl;

}

//Function for the player input
void Input()
{
	PrintMessage("Type a Letter:");
	cout << endl << "               ";
	cin >> letter;

	//Transform letter in uppercase
	for (int i = 0; i < GameWord.length() - 1; i++) {
		if (letter > 96 && letter < 123) {
			letter -= 32;
		}
	}

	//Store the letter in an array so it can be checked later
	guessedLetters[guesses] = letter;
	guesses++;
}

//Function for game logic
void Logic()
{
	//checks if the typed letter is different than the previous typed letters
	for (int i = 0; i < guesses; i++) {
		
		if (i == 0)
			ok++;
		
		if (letter != guessedLetters[i])
			ok++;
	}

	//if the letter has not been typed before, checks if it matches with any of the letters from the selected word
	if (ok == guesses) {

		for (int i = 0; i < GameWord.length(); i++) {

			if (letter == (char)GameWord[i]) {
				correctLetters++;
				gameChars[i] = GameWord[i];
			}
			else {
				different++;	//counts how many letters the typed letter is different from
			}
		}

		//if the typed letter is different from all of the selected word letters, an error is counted
		if (different == GameWord.length()) {
			wrongLetters[error] = letter;
			error++;
		}

		different = 0;
	}
	
	ok = 0;

	//if all the letters are correct, the player has won
	if (correctLetters == GameWord.length())
		won = true;

	//6 errors equals a loss
	if (error == 6)
		lost = true;
}

int main()
{
	while (true) {
		GameWord = SelectWord();
		Start();

		while (won == false && lost == false) {

			DrawGame();
			Input();
			Logic();
			
			system("cls");
		}

		if (won == true) {
			DrawGame();
			PrintMessage(" YOU WON!");
			cout << endl << endl;
			PrintMessage("Press Any Key to Continue Playing");
			cout << endl;
			system("PAUSE >nul");
			system("cls");
		}

		if (lost == true) {
			DrawGame();
			PrintMessage("YOU LOST :(");
			cout << endl;
			PrintMessage("The Word was " + GameWord);
			cout << endl << endl;
			PrintMessage("Press Any Key to Continue Playing");
			cout << endl;
			system("PAUSE >nul");
			system("cls");
		}
	}

	return 0;
}
