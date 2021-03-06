// Math-Practice
//This program allows primary school students to practice addition and subtraction. It will generate problems until the student enters a sentinel value.
//Upon exiting, the progrma will write the user's number of correct & incorrect answers to a file in the program's repository.

#include "stdafx.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <ctime>
using namespace std;

//Function Prototypes

int getProblem(int lvl, char problemType);
double calcResults(int correctAnswers, int wrongAnswers);
void printFile(int right, int wrong, double ratio, string student, string currentDate, int lvl, char type, string file);

int main()
{
	//variables

	string filename = "";
	string name = "";
	string date = "";
	double percentage = 0.0;
	int correct = 0;
	int incorrect = 0;
	int level = 0;
	int guess = 0;
	int answer = 0;
	char operation = ' ';

	//Input items

	cout << "Filename (letters and numbers only): "; //filename
	getline(cin, filename);

	filename = filename + ".txt"; //convert filename to text file

	cout << "Name: "; //student name
	getline(cin, name);

	cout << "Date: "; //current date
	getline(cin, date);

	cout << "Choose Level (1 or 2): ";
	cin >> level;

	while (level != 1 && level != 2) {
		cout << "Invalid Entry. Enter '1' or '2' to choose your level: ";
		cin >> level;
	}//endwhile

	cout << "Select Operation: A)ddition, (S)ubtraction, or (M)ultiplication?: ";
	cin >> operation;

	operation = toupper(operation);

	while (operation != 'A' && operation != 'S' && operation != 'M') {
		cout << "Invalid Entry. Enter 'A' to practice addition, 'S' to practice subtraction, or 'M' to practice multiplication: ";
		cin >> operation;
		operation = toupper(operation);
	}//endwhile

	answer = getProblem(level, operation); //call the function to create the first problem.
	cin >> guess;

	while (guess != -1) {

		while (guess != answer) {

			incorrect++;

			cout << "Incorrect. Please try again: ";
			cin >> guess;
		}//endwhile

		correct++;

		cout << "Correct!" << endl;

		answer = getProblem(level, operation); //calls the next problem in the series.

		cin >> guess;

	}//end while

	 //calculate and display results -- only processes if the user answered at least one question

	if (correct + incorrect > 0) {

		percentage = calcResults(correct, incorrect); //calculate results and return percentage correct
		printFile(correct, incorrect, percentage, name, date, level, operation, filename); //open and write data to file.

	}//endif

	return 0;
}

//****getProblem****

int getProblem(int lvl, char problemType) {

	int correctAnswer = 0;
	int number1 = 0;
	int number2 = 0;

	if (lvl == 1) {

		srand(static_cast<int>(time(0)));

		number1 = 1 + rand() % (10 - 1 + 1);
		number2 = 1 + rand() % (10 - 1 + 1);

	}//endif
	else if (lvl == 2) {
		srand(static_cast<int>(time(0)));

		number1 = 1 + rand() % (100 - 1 + 1);
		number2 = 1 + rand() % (100 - 1 + 1);
	}//end elseif

	if (number2 > number1) {		//ensures that the first number is always equal to or larger the second number
		int temp = number1;
		number1 = number2;
		number2 = temp;
	}//endif

	if (problemType == 'A') {

		correctAnswer = number1 + number2;
		cout << endl << "What is " << number1 << " + " << number2 << "? (-1 to Quit): ";

	}//endif
	else if (problemType == 'S') {

		correctAnswer = number1 - number2;
		cout << endl << "What is " << number1 << " - " << number2 << "? (-1 to Quit): ";
	}
	else if (problemType == 'M') {
		correctAnswer = number1 * number2;
		cout << endl << "What is " << number1 << " * " << number2 << "? (-1 to Quit): ";

	}//end elseif

	return correctAnswer; //returns the problem's correct answer to the main function

}//end getProblem

 //****calcResults****

double calcResults(int correctAnswers, int wrongAnswers) {

	//display results

	cout << endl << "_______________________________________________" << endl;
	cout << endl << "Total Correct: " << correctAnswers << endl;
	cout << "Total Incorrect: " << wrongAnswers << endl;

	double total = correctAnswers + wrongAnswers;
	double pCent = (correctAnswers / total * 100);

	cout << "Percentage Correct: " << fixed << setprecision(0) << pCent << "%" << endl << endl;

	return pCent; //returns the percentage correct to the main function since it is needed in the output file.

} //end calcResults

  //****printFile****
void printFile(int right, int wrong, double ratio, string student, string currentDate, int lvl, char type, string file) {

	string operation = "";

	// if/else decision tree converts operation into string form for output.

	if (type == 'A')
		operation = "Addition";
	else if (type == 'S')
		operation = "Subtraction";

	//endif

	ofstream outFile;
	outFile.open(file, ios::app);

	outFile << "Student: " << student << endl;
	outFile << "Date: " << currentDate << endl << endl;
	outFile << operation << endl;
	outFile << "Level " << lvl << endl << endl;
	outFile << "Correct: " << right << setw(20) << "Incorrect: " << wrong << setw(20) << fixed << setprecision(0) << "Percentage: " << ratio << "%" << endl;
	outFile << "-------------------------------------------------------------------------------------------------------------" << endl << endl;

	outFile.close();  //close file

} //end printFile