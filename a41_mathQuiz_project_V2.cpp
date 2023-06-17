#include <iostream>
#include <cstdlib>
using namespace std;

/*
* module 1: read data from the user
*/

// data
enum enQuestionLevel {EASY =1, MEDIUM =2, HARD= 3, MIXED = 4};

enum enOpType {ADD = 1, SUBTRACT =2, MULTIPLY =3, DIVIDE =4, MIX = 5};

// operations
int readRange(int from, int to, string message, string warning) {
	int num{};
	bool isCinFailed{};
	do {
		cout << message;
		cin >> num;

		/*
		* validation:
		* ignore strings
		*/

		isCinFailed = cin.fail();
		if (isCinFailed) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << warning;
		}
		else if (num < from || num > to)
			cout << warning;

	} while ((num < from || num > to) || isCinFailed);

	return num;
}

/*
* module 2: generate questions
*/

// data
struct stUser {
	int answer{};
	bool hasRightAnswer{};
};

struct stQuestion {
	int number1{};
	int number2{};
	int answer{};
	enQuestionLevel questionLevel;
	enOpType opType;
};

// operations
enQuestionLevel getQuestionLevel(int userChoice) {
	return (enQuestionLevel)userChoice;
}

int randomNumber(int from, int to) {
	return rand() % (to - from + 1) + from;
}

enOpType getOpType(int userChoice) {
	return (enOpType)userChoice;
}

int calculateAnswer(stQuestion question) {

	switch (question.opType)
	{
	case enOpType::ADD:
		question.answer = question.number1 + question.number2;
		break;
	case enOpType::SUBTRACT:
		question.answer = question.number1 - question.number2;
		break;
	case enOpType::MULTIPLY:
		question.answer = question.number1 * question.number2;
		break;
	default:
		question.answer = question.number1 / question.number2;
	}

	return question.answer;
}

string repeatString(string key, int numOfTimes) {
	string word{""};
	for (int time = 0; time < numOfTimes; time++)
		word += key;
	return word;
}

int getUserAnswer() {
	int answer{};
	cin >> answer;
	return answer;
}

stQuestion generateQuestion(enQuestionLevel level, enOpType opType) {
	stQuestion question;

	cout << "level: " << level << endl;
	cout << "opType: " << opType << endl;

	if (level == enQuestionLevel::MIXED)
		level = getQuestionLevel(randomNumber(1, 3));

	if (opType == enOpType::MIX)
		opType = getOpType(randomNumber(1, 4));

	question.questionLevel = level;
	question.opType = opType;

	cout << "question level AFTER: " << question.questionLevel << endl;
	cout << "question opType AFTER: " << question.opType << endl;

	switch (level)
	{
	case enQuestionLevel::EASY:
		question.number1 = randomNumber(1, 10);
		question.number2 = randomNumber(1, 10);
		break;
	case enQuestionLevel::MEDIUM:
		question.number1 = randomNumber(10, 50);
		question.number2 = randomNumber(10, 50);
		break;
	default:
		question.number1 = randomNumber(50, 100);
		question.number2 = randomNumber(50, 100);
	}

	// answer the question
	question.answer = calculateAnswer(question);
	return question;
}

struct stQuiz {
	// has # of questions
	stQuestion questions[100];
	// has a single user
	stUser user;

	enQuestionLevel questionLevel;
	enOpType opType;

	int numOfQuestions{};
	int numOfRightAnswers{};
	int numOfWrongAnswers{};
	bool isPassed{};
};

void generateQuestions(stQuiz& quiz) {
	
	for (int number = 0; number < quiz.numOfQuestions; number++) {
		quiz.questions[number] = generateQuestion(quiz.questionLevel, quiz.opType);
	}
}

string getOpSymbol(enOpType opType) {
	string symbols[] = { "+","-","*","/" };
	return symbols[opType - 1];
}

void printQuestion(stQuiz quiz, int questionNumber) {
	
	cout << "\nQuestion number [" << questionNumber << "/" << quiz.numOfQuestions << "]\n";
	cout << quiz.questions[questionNumber].number1 << '\n';
	cout << quiz.questions[questionNumber].number2 << '\n';
	cout << "    " << getOpSymbol(quiz.opType) << '\n';
	cout << repeatString("_", 20) << endl;

}

void validateUserAnswer(stQuiz& quiz, int questionNumber) {
	
	quiz.user.answer = getUserAnswer();

	if (quiz.questions[questionNumber].answer == quiz.user.answer) {
		quiz.user.hasRightAnswer = true;
		quiz.numOfRightAnswers++;
	}
	else {
		quiz.user.hasRightAnswer = false;
		quiz.numOfWrongAnswers++;
	}
}

void messageTheUser(stQuiz quiz, int questionNumber) {
	if (quiz.user.answer)
		cout << "\nRight answer :-)\n";
	else {
		cout << "\nWrong answer :-(\n";
		cout << "\nThe right answer is " << quiz.questions[questionNumber].answer << endl;
	}
}











int main()
{
	srand((unsigned)time(NULL));
	stQuiz quiz;
	quiz.numOfQuestions = 2;
	quiz.opType = enOpType::MIX;
	quiz.questionLevel = enQuestionLevel::MEDIUM;

	generateQuestions(quiz); 

	printQuestion(quiz, 1);
	validateUserAnswer(quiz, quiz.numOfQuestions);
	messageTheUser(quiz, 1); 
	
	return 0;
}

