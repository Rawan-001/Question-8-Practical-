#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

enum enQuestionLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, MixLevel = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

struct sQuestion {
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct sQuizz {
    sQuestion QuestionList[100];
    short NumberOfQuestion = 0;
    enOperationType OpType;
    enQuestionLevel QuestionLevel;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswer = 0;
    bool isPass = false;
};

int RandomNumber(int From, int To) {
    return (rand() % (To - From + 1)) + From;
}

int ReadHowManyQuestions() {
    short NumberOfQuestions;
    do {
        cout << "How many Questions do you want to answer ? ";
        cin >> NumberOfQuestions;
    } while (NumberOfQuestions < 1 || NumberOfQuestions > 10);
    return NumberOfQuestions;
}

enQuestionLevel ReadQuestionsLevel() {
    short QuestionLevel = 0;
    do {
        cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);
    return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOpType() {
    short OpType = 0;
    do {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);
    return (enOperationType)OpType;
}

int SimpleCalculate(int Number1, int Number2, enOperationType OperationType) {
    switch (OperationType) {
    case enOperationType::Add: return Number1 + Number2;
    case enOperationType::Sub: return Number1 - Number2;
    case enOperationType::Mult: return Number1 * Number2;
    case enOperationType::Div: return Number1 / Number2;
    default: return Number1 + Number2;
    }
}

enOperationType GetRandomOperationType() {
    short Op = RandomNumber(1, 4);
    return (enOperationType)Op;
}

sQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OpType) {
    sQuestion Question;
    if (QuestionLevel == enQuestionLevel::MixLevel)
        QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
    if (OpType == enOperationType::MixOp)
        OpType = GetRandomOperationType();
    Question.OperationType = OpType;

    switch (QuestionLevel) {
    case enQuestionLevel::EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        break;
    case enQuestionLevel::MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        break;
    case enQuestionLevel::HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        break;
    default:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        break;
    }

    Question.CorrectAnswer = SimpleCalculate(Question.Number1, Question.Number2, Question.OperationType);
    Question.QuestionLevel = QuestionLevel;
    return Question;
}

void GenerateQuizzQuestions(sQuizz& Quizz) {
    for (short Question = 0; Question < Quizz.NumberOfQuestion; Question++)
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
}

string GetOpTypeSymbol(enOperationType OpType) {
    switch (OpType) {
    case enOperationType::Add: return "+";
    case enOperationType::Sub: return "-";
    case enOperationType::Mult: return "x";
    case enOperationType::Div: return "/";
    default: return "Mix";
    }
}

void PrintTheQuestion(sQuizz Quizz, short QuestionNumber) {
    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestion << "] \n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << " "
        << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
    cout << endl << "________\n";
}

int ReadQuestionAnswer() {
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

void SetScreenColor(bool Right) {
    if (Right)
        system("color 2F");
    else {
        system("color 4F");
        cout << "\a";
    }
}

void CorrectTheQuestionAnswer(sQuizz& Quizz, short QuestionNumber) {
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer) {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;
        cout << "Wrong Answer :-( \n";
        cout << "The Right Answer is: " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << "\n";
    }
    else {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswer++;
        cout << "Right Answer :-) \n";
    }
    cout << endl;
    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(sQuizz& Quizz) {
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestion; QuestionNumber++) {
        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }
    Quizz.isPass = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultText(bool Pass) {
    if (Pass) return "PASS :-)";
    else return "FAIL :-(";
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel) {
    string arrQuestionLevel[4] = { "Easy", "Med", "Hard", "Mix" };
    return arrQuestionLevel[QuestionLevel - 1];
}

string GetOpTypeSymbol2(enOperationType OpType) {
    switch (OpType) {
    case enOperationType::Add: return "+";
    case enOperationType::Sub: return "-";
    case enOperationType::Mult: return "*";
    case enOperationType::Div: return "/";
    default: return "Mix";
    }
}

void PrintQuizzResult(sQuizz Quizz) {
    cout << "\n";
    cout << "__________________________\n\n";
    cout << "Final Result is " << GetFinalResultText(Quizz.isPass);
    cout << "\n__________________________\n\n";
    cout << "Number of Question: " << Quizz.NumberOfQuestion << endl;
    cout << "Question Level    : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
    cout << "Operation Type    : " << GetOpTypeSymbol2(Quizz.OpType) << endl;
    cout << "Number of Right Answer: " << Quizz.NumberOfRightAnswer << endl;
    cout << "Number of Wrong Answer: " << Quizz.NumberOfWrongAnswers << endl;
    cout << "__________________________\n";
}

void ResetScreen() {
    system("cls");
    system("color 0F");
}

void PlayMathGame() {
    sQuizz Quizz;
    Quizz.NumberOfQuestion = ReadHowManyQuestions();
    Quizz.QuestionLevel = ReadQuestionsLevel();
    Quizz.OpType = ReadOpType();
    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionListAnswers(Quizz);
    PrintQuizzResult(Quizz);
}

void StartGame() {
    char PlayAgain = 'Y';
    do {
        ResetScreen();
        PlayMathGame();
        cout << "\nDo you want to play again? Y/N? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main() {
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}
