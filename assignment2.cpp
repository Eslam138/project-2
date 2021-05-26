#include <iostream>
#include <utility>
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>
#include<iterator>
//Ahmed Mohamed Abdel Rashied  20180028;
//Moamen Eid Mahmoud		   20180299;
//Eslam Nasser Ghoneim         20180047;
//Mohamed Khaled Mohamed       20180438;
using namespace std;
static int MCQRightAnswer;
static int tf = 0, complete = 0, mcq = 0;//to count the questions
static bool takeQuiz = false; // to know if the player take quiz 
static int Counter = 0;// we will use this to check in quiz class
int ar[4];//we will save in this array random values to print question answers with random order
static int MCQRightAnswers = 0, MCQFalseANswer = 0, CompleteAnswer = 0, TFRightAnswer = 0, TFFalseANswer = 0;
//to save the right answers and wrong answers 
//in this variables we will save the quiz answer;
//bool TFQ[1000000] = { false }, MCQQ[1000000] = { false }, CQ[1000000] = { false };
// this arrays is used to know if the question was printed or was not
void randomValues() // to generate random values for MCQ answers
{
	bool arr[5] = { 0 };
	for (int i = 0; i < 4; ++i)
	{
		int r = rand() % 4;
		if (!arr[r])
			ar[i] = r;
		else
			i--;
		arr[r] = true;
	}
}
class User
{
protected:
	pair<string, string>UserData;
	string FirstName;
	string SecondName;

public:
	User()
	{
		UserData.first = "User";
		UserData.second = "000000";
		SecondName = "user";
		FirstName = "user";
	}
	User(string username, string password, string FirstName, string SecondName)
	{
		UserData.first = username;
		UserData.second = password;
		this->FirstName = FirstName;
		this->SecondName = SecondName;
	}
};
class Admin :public User
{
public:
	Admin()
	{
		UserData.first = "User";
		UserData.second = "000000";
		SecondName = "user";
		FirstName = "user";
	}
	Admin(string username, string password, string FirstName, string SecondName)
	{
		UserData.first = username;
		UserData.second = password;
		this->FirstName = FirstName;
		this->SecondName = SecondName;
	}
	void updateName(string FirstName, string SecondName)
	{
		this->FirstName = FirstName;
		this->SecondName = SecondName;
		cout << "if you wont to add new password enter new password if you do not enter your password\n";
		cin >> UserData.second;
	}
	friend ostream& operator <<(ostream& out, const Admin& admin)
	{
		out << admin.FirstName << "\t\t" << admin.SecondName << "\t\t";
		out << admin.UserData.first << "\t\t" << "  Admin\n";
		return out;
	}
	friend bool operator==(pair <string, string>Newuser, Admin& admin)
	{
		if (Newuser.first == admin.UserData.first)
		{
			return true;
		}
		else
			return false;
	}
	void adminMenu()
	{
		cout << "Welcome " << FirstName << " " << SecondName << " (ADMIN), please choose from the following options:\n";
		cout << "[1] Switch accounts\n[2] Update your name\n[3] View all users\n[4] Add new user\n[5] View all questions\n[6] Add new question\n[7] Load questions from file\n[8] Exit the program\n";
		cout << "My choice: _\n";
	}
	bool checkAdmin(pair <string, string>Newuser)//we will use this func. to check if the user enter the right user name and password
	{
		if (Newuser.first == this->UserData.first && Newuser.second == this->UserData.second)
		{
			return true;
		}
		else
			return false;
	}


};
class Player :public User
{
	vector<pair<int, int>>MCQAnswers;// in this array we will save true and false answer for MCQ questions 
	vector<pair<int, int>>TFAnswer;// in this array we will save true or false answer for TF questions
	vector<int>Canswer;//in this array we will save 1 if player wrote the true answer or 0 if false for Complete questions
	vector<int>grade;// in this array we will save grade for each quiz

public:
	void playerMenu()
	{
		cout << "Welcome " << FirstName << " " << SecondName << " (Player), please choose from the following options:\n";
		cout << "[1] Switch accounts\n[2] Update your name\n[3] Start a new quiz\n[4] Display your scores statistics\n[5] Display all your scores\n[6] Exit the program\n";
		cout << "My choice: _\n";
	}
	Player()
	{
		UserData.first = "User";
		UserData.second = "000000";
		SecondName = "user";
		FirstName = "user";
	}
	Player(string username, string password, string FirstName, string SecondName)
	{
		UserData.first = username;
		UserData.second = password;
		this->FirstName = FirstName;
		this->SecondName = SecondName;
	}
	void updateName(string FirstName, string SecondName)
	{
		this->FirstName = FirstName;
		this->SecondName = SecondName;
		cout << "if you wont to add new password enter new password if you do not enter your password\n";
		cin >> UserData.second;
	}
	friend ostream& operator <<(ostream& out, const Player& player)
	{
		out << player.FirstName << "\t\t" << player.SecondName << "\t\t";
		out << player.UserData.first << "\t\t" << "Player\n";
		return out;
	}
	friend bool operator==(pair <string, string>Newuser, Player& player)
	{
		if (Newuser.first == player.UserData.first)
		{
			return true;
		}
		else
			return false;
	}
	void setMCQAnswer(int RigtANswer = 0, int FalseANswer = 0)
	{
		MCQAnswers.push_back(make_pair(RigtANswer, FalseANswer));
	}
	void setTFAnswer(int RightAnswer = 0, int FalseANswer = 0)
	{
		TFAnswer.push_back(make_pair(RightAnswer, FalseANswer));
	}
	void setCompleteANswer(int answer)
	{
		Canswer.push_back(answer);
	}
	void calculateGrade(int MCQRightanswerss, int TFRightAnswerss, int CRightAnswerss)
	{
		int calculateGrade = MCQRightanswerss + (TFRightAnswerss * 2) + (CRightAnswerss * 3);
		grade.push_back(calculateGrade);
	}
	void scoreStatistics()
	{
		if (Canswer.size() > 0)
		{
			double Average = 0;
			int sum = 0;
			cout << "Your score statistics per quiz:\n";
			cout << "Number of Quizzes taken: " << Canswer.size() << endl;
			cout << "Highest quiz score:";
			cout << *max_element(grade.begin(), grade.end()) << "/10" << endl;
			cout << "Lowest quiz score" << *min_element(grade.begin(), grade.end()) << "/10" << endl;
			for (auto it : grade)
			{
				sum += it;
			}

			Average = sum / Canswer.size();
			cout << "Average quiz score:" << Average << "/10" << endl;
			cout << "Your score statistics per question type:\n";
			cout << "Number of MC questions:" << 3 * Canswer.size() << endl;
			cout << "Number of Complete questions" << Canswer.size() << endl;
			cout << "Number of T/F Questions: " << 2 * Canswer.size() << endl;
			double MCQAverage = 0, TFAverage = 0, CAverage = 0;
			for (auto it : MCQAnswers)
			{
				MCQAverage += it.first;
			}
			MCQAverage = MCQAverage / (3 * Canswer.size());
			for (auto it : TFAnswer)
			{
				TFAverage += it.first;
			}

			TFAverage = TFAverage / (2 * Canswer.size());
			for (auto it : Canswer)
			{
				CAverage += it;
			}
			CAverage = CAverage / Canswer.size();
			cout << "Average grade for MC questions:" << MCQAverage << "/1" << endl;
			cout << "Average grade for T/F questions:" << TFAverage << "/2" << endl;
			cout << "Average grade for Complete questions:" << CAverage << "/3" << endl;

		}
		else
		{
			cout << "you should take quiz \n";
		}
	}
	void allScore()
	{
		if (Canswer.size() > 0)
		{
			int z = 0;
			for (size_t i = 1; i <= Canswer.size(); i++)
			{
				cout << "Quiz Number: " << i << endl;
				cout << "MCQ right answers:" << MCQAnswers[z].first << endl;
				cout << "T/F right answers:" << TFAnswer[z].first << endl;
				cout << "Complete right answers:" << Canswer[z] << endl;
				cout << "your grade:" << grade[z] << endl;
				z++;
			}
		}
		else
		{
			cout << "you should take a quiz\n";
		}
	}

	int quizNumber()
	{
		return Canswer.size();
	}
	bool checkPlayer(pair <string, string>Newuser)//we will use this func. to check if the user enter the right user name and password
	{
		if (Newuser.first == this->UserData.first && Newuser.second == this->UserData.second)
			return true;
		else
			return false;
	}
};
class MCQQuestion
{
	string Question = " ";
	string answers[4];
public:
	MCQQuestion(string Question, string answers[4])
	{
		this->Question = Question;
		for (size_t i = 0; i < 4; i++)
		{
			this->answers[i] = answers[i];
		}
	}
	friend ostream& operator<<(ostream& out, const MCQQuestion& Question)
	{
		randomValues();
		int RightAnswer = ar[0];
		string c = "abcd";
		string RandomAnswers[4];
		out << Question.Question << endl;
		for (size_t i = 0; i < 4; i++)
		{
			RandomAnswers[ar[i]] = Question.answers[i];
		}
		for (size_t i = 0; i < 4; i++)
		{
			if (i == RightAnswer)
			{
				out << "*";
			}
			cout << "[" << c[i] << "]";
			out << RandomAnswers[i] << "\t";
		}
		out << endl;
		return out;
	}
	void printQuestion()
	{
		cout << Question << endl;
		randomValues();
		string c = "abcd";
		string RandomAnswers[4];
		for (size_t i = 0; i < 4; i++)
		{
			RandomAnswers[ar[i]] = answers[i];
		}
		for (size_t i = 0; i < 4; i++)
		{
			cout << "[" << c[i] << "]" << RandomAnswers[i] << "\t";
		}
		cout << "\n";
		MCQRightAnswer = ar[0];
	}
	string getAnswer()
	{
		return this->answers[0];
	}
	string getQuestion()
	{
		return this->Question;
	}

};
class TFQuestion
{
	string Question = " ";
	bool answer;
	string Answer;
public:
	TFQuestion(string Question, bool answer)
	{
		this->Question = Question;
		this->answer = answer;
		if (answer)
		{
			Answer = "true";
		}
		else
		{
			Answer = "false";
		}
	}
	friend ostream& operator<<(ostream& out, const TFQuestion& q)
	{
		out << q.Question << "  answer:" << q.Answer << endl;
		return out;
	}
	void printQuestion()
	{
		cout << Question << endl;
	}
	bool getAnswer()
	{
		return this->answer;
	}
	string getQuestion()
	{
		return this->Question;
	}

};
class CompleteQuestion
{
	string Question = "  ";
	string answer;
public:
	CompleteQuestion(string Question, string answer)
	{
		this->Question = Question;
		this->answer = answer;
	}
	friend ostream& operator<<(ostream& out, const CompleteQuestion& Q)
	{
		out << Q.Question << "  answer:" << Q.answer << endl;
		return out;
	}
	void printQuestion()
	{
		cout << Question << endl;
	}
	string getAnswer()
	{
		return this->answer;
	}
	string getQuestion()
	{
		return this->Question;
	}


};
class Quiz
{
	vector<MCQQuestion>MCQ;
	vector<TFQuestion>TF;
	vector<CompleteQuestion>Complete;
	ifstream file;
public:
	void setQuestions(string FileName)//to receive from file
	{
		string QuestionType, Question, QuestionAnswer;
		string MCQAnswes[4];
		bool TFAnswer;
		file.open(FileName.c_str());
		if (!file)
		{
			cerr << "file does not exist/n";
		}
		else
		{
			while (getline(file, QuestionType))
			{
				bool checkDuplicate = false;
				if (QuestionType == "MCQ")
				{
					getline(file, Question);
					for (size_t i = 0; i < 4; i++)
					{
						getline(file, MCQAnswes[i]);
					}
					if (Counter > 0)
					{
						if (!checkDuplicate)
						{
							for (size_t i = 0; i < MCQ.size(); i++)
							{
								if (MCQ[i].getQuestion() == Question)
								{
									checkDuplicate = true;
									break;
								}

							}
						}
					}
					else
						MCQ.push_back(MCQQuestion(Question, MCQAnswes));


				}
				else if (QuestionType == "COMPLETE")
				{
					getline(file, Question);
					getline(file, QuestionAnswer);
					if (Counter > 0)
					{
						for (size_t i = 0; i < Complete.size(); i++)
						{
							if (Complete[i].getQuestion() == Question)
							{
								checkDuplicate = true;
								break;
							}

						}
						if (!checkDuplicate)
						{
							Complete.push_back(CompleteQuestion(Question, QuestionAnswer));

						}
					}
					else
						Complete.push_back(CompleteQuestion(Question, QuestionAnswer));
				}
				else if (QuestionType == "TF")
				{
					getline(file, Question);
					getline(file, QuestionAnswer);
					if (QuestionAnswer == "true")
					{
						TFAnswer = true;
					}
					else
						TFAnswer = false;
					if (Counter > 0)
					{
						for (size_t i = 0; i < Complete.size(); i++)
						{
							if (TF[i].getQuestion() == Question)
							{
								checkDuplicate = true;
								break;
							}

						}
						if (!checkDuplicate)
						{
							TF.push_back(TFQuestion(Question, TFAnswer));
						}
					}
					else
						TF.push_back(TFQuestion(Question, TFAnswer));
				}
			}
			file.close(); //  Closing file
			if (MCQ.size() > 0 && TF.size() > 0 && Complete.size() > 0)
			{
				Counter++;

			}
		}

	}
	void getQuestions()
	{
		int counter = 1;
		if (MCQ.size() > 0 || TF.size() > 0 || Complete.size() > 0)
		{
			int QuestionNamber = MCQ.size() + TF.size() + Complete.size();
			cout << "Number of Questions\n";
			cout << "-------------------------------------------------------------\n";
			cout << "MCQ Question=" << MCQ.size() << endl;
			cout << "-------------------------------------------------------------\n";
			for (auto it : MCQ)
			{
				cout << "[" << counter++ << "]" << it << endl;
			}
			cout << "-------------------------------------------------------------\n";
			cout << "TF Question=" << TF.size() << endl;
			cout << "-------------------------------------------------------------\n";
			for (auto it : TF)
			{
				cout << "[" << counter++ << "]" << it << endl;
			}
			cout << "-------------------------------------------------------------\n";
			cout << "Complete Question" << Complete.size() << endl;
			cout << "-------------------------------------------------------------\n";
			for (auto it : Complete)
			{
				cout << "[" << counter++ << "]" << it << endl;
			}
			cout << "-------------------------------------------------------------\n";
		er:
			char x;//to receive d or b 
			cout << "Press [d] and the question ID if you want to delete a question (Example: d 2)\nPress[b] if you want to go back to the main menu\n";
			//cin.ignore();
			cin >> x;
			if (x=='d'||x=='b')
			{
				if (x=='d')
				{
					if (x == 'd')
					{
						
						int y;//to receive Number of question the admin will delete
						mm:
						cin >> y;
						while (1)
						{
							if (cin.fail())
							{
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								cout <<"You have entered wrong input" << endl;
								cin >> y;
							}
							if (!cin.fail())
								break;
						}
						/*if (cin.fail()) { // if the user wrote a char
							cout << "invalid choice2\n";
							cin.ignore(9999, '\n');
							cin.clear();
							goto mm;
						}*/
						if (y <= MCQ.size())
						{
							y--;
							auto it = MCQ.begin();//it is a  MCQ iterator
							it = MCQ.begin() + y;
							MCQ.erase(it);
						}
						else if (y <= (MCQ.size() + TF.size()))
						{
							y = y - MCQ.size() - 1;
							auto it = TF.begin() + y;
							TF.erase(it);
						}
						else if (y <= (MCQ.size() + TF.size() + Complete.size()))
						{
							y = y - (MCQ.size() + TF.size()) - 1;
							auto it = Complete.begin() + y;
							Complete.erase(it);
						}
						else
						{
							cout << "this number of question does not exist\ntry again\n";
							goto er;
						}
					}
				}

			}
			else
			{
				cin.ignore(9999, '\n');// in case of if the user wrote a word.
				cout << "invalid choice1\n";
				goto er;
			}

		}
		else
			cerr << "no questions to view\n";
	}
	void addNewQuestion()
	{
	e:
		bool checkDuplicate = false;
		cout << "which type of questions you want to add\n";
		string QuestionType, Question, Answer;
		string MCQAnswers[4];
		cin.ignore();
		cin >> QuestionType;
		if (QuestionType == "MCQ")
		{

			cout << "question you want to add\n";
			cin.ignore();
			string abcd = "abcd";
			getline(cin, Question);
			for (size_t i = 0; i < 4; i++)
			{
				cout << "Enter question answer : " << abcd[i] << endl;
				cin.ignore();
				getline(cin, MCQAnswers[i]);
			}
			if (Counter > 0)
			{
				if (!checkDuplicate)
				{
					for (size_t i = 0; i < MCQ.size(); i++)
					{
						if (MCQ[i].getQuestion() == Question)
						{
							checkDuplicate = true;
							break;
						}
						if (!checkDuplicate)
						{
							MCQ.push_back(MCQQuestion(Question, MCQAnswers));
							Counter++;
						}

					}
				}
			}
			else
			{
				MCQ.push_back(MCQQuestion(Question, MCQAnswers));
				Counter++;
			}
		}
		else if (QuestionType == "COMPLETE")
		{
			cout << "question you want to add\n";
			cin.ignore();
			getline(cin, Question);
			cout << "Enter question answer : \n";
			cin.ignore();
			getline(cin, Answer);
			if (Counter > 0)
			{
				for (size_t i = 0; i < Complete.size(); i++)
				{
					if (Complete[i].getQuestion() == Question)
					{
						checkDuplicate = true;
						break;
					}

				}
				if (!checkDuplicate)
				{
					Complete.push_back(CompleteQuestion(Question, Answer));
					Counter++;
				}
			}
			else
			{
				Complete.push_back(CompleteQuestion(Question, Answer));
				Counter++;
			}
		}
		else if (QuestionType == "TF")
		{
			bool TFAnswer;
			cout << "question you want to add\n";
			cin.ignore();
			getline(cin, Question);
			cout << "Enter question answer : \n";
			cin.ignore();
			getline(cin, Answer);
			if (Answer == "true")
			{
				TFAnswer = true;
			}
			else
				TFAnswer = false;
			if (Counter > 0)
			{
				for (size_t i = 0; i < Complete.size(); i++)
				{
					if (Complete[i].getQuestion() == Question)
					{
						checkDuplicate = true;
						break;
					}

				}
				if (!checkDuplicate)
				{
					TF.push_back(TFQuestion(Question, TFAnswer));
					Counter++;
				}
			}
			else
			{
				TF.push_back(TFQuestion(Question, TFAnswer));
				Counter++;

			}
		}
		else
		{
			cerr << "try again \n";
			goto e;
		}
	}

	void startQuiz()
	{
		//bool TFQ[1000000] = { false }, MCQQ[1000000] = { false }, CQ[1000000] = { false };
		// this arrays is used to know if the question was printed or was not
		bool* TFQ, * MCQQ, * CQ;
		int size1 = TF.size(), size2 = MCQ.size(), size3 = Complete.size();
		TFQ = new bool[size1];
		MCQQ = new bool[size2];
		CQ = new bool[size3];
		for (size_t i = 0; i < size2; i++)
		{
			MCQQ[i] = false;
		}
		for (size_t i = 0; i < size1; i++)
		{
			TFQ[i] = false;
		}
		for (size_t i = 0; i < size3; i++)
		{
			CQ[i] = false;
		}
		if (MCQ.size() > 2 && TF.size() > 1 && Complete.size() > 0)
		{
			int counter = 0, counter2 = 0;
			if ((mcq + 3) <= MCQ.size() && (tf + 2) <= TF.size() && (complete + 1) <= Complete.size())
			{
				while ((tf + mcq + complete) < 6)
				{
				er0:
					int random = rand() % 3;
					if (random == 0)
					{
						if (mcq < 3)
						{
						er1:
							int random2 = rand() % MCQ.size();
							if (!MCQQ[random2])
							{
								cout << "   MCQ\n";
								MCQ[random2].printQuestion();
								string choice;
								int cheeker;

							qq:
								cin >> choice;
								if (choice == "a") cheeker = 0;
								else if (choice == "b")cheeker = 1;
								else if (choice == "c")cheeker = 2;
								else if (choice == "d")cheeker = 3;
								else {
									cout << "wrong option try again\n";
									goto qq;
								}
								if (MCQRightAnswer = cheeker)
									MCQRightAnswers++;
								else
									MCQFalseANswer++;
								MCQQ[random2] = true;
								counter++;
								mcq += 1;
							}
							else
							{
								goto er1;
							}
						}
						else
							goto er0;
					}
					if (random == 1)
					{
					er2:
						if (tf < 2)
						{
							int random2 = rand() % TF.size();
							if (!TFQ[random2])
							{
								cout << "True or False\n";
								TF[random2].printQuestion();
								string choice;
								bool cheecker = false;
							er3:
								cin >> choice;
								if (choice == "true") cheecker = true;
								else if (choice == "false")cheecker = false;
								else
								{
									cout << "please write false or true\n";
									goto er3;
								}
								if (TF[random2].getAnswer() == cheecker)
								{
									TFRightAnswer++;
								}
								else
									TFFalseANswer++;

								TFQ[random2] = true;
								counter2++;
								tf += 1;

							}
							else
							{
								goto er2;
							}
						}
						else
							goto er0;
					}
					if (random == 2)
					{
						if (complete < 1)
						{
						err3:
							int random2 = rand() % Complete.size();
							if (!CQ[random2])
							{
								cout << "Complete\n";
								Complete[random2].printQuestion();
								string checker;
								cin >> checker;
								//string checker2 = Complete[random2].getAnswer();
								if (checker == Complete[random2].getAnswer())
									CompleteAnswer = 1;
								CQ[random2] = true;


								complete += 1;
							}
							else
							{
								goto err3;
							}
						}
						else
							goto er0;
					}

				}
				cout << "you get: " << ((1 * MCQRightAnswer) + (2 * TFRightAnswer) + (3 * CompleteAnswer)) << endl;
				takeQuiz = true;
			}
			else
			{
				cout << "no questions please ask your admin to add questions\n";
			}

			/*while ((tf + mcq + complete) < 6)
			{
				er0:
				int random = rand() % 3;
				if (random == 0)
				{
					if (mcq < 3)
					{
					er1:
						int random2 = rand() % MCQ.size();
						if (!MCQQ[random2])
						{
							cout << "   MCQ\n";
							MCQ[random2].printQuestion();
							string choice;
							int cheeker;

						qq:
							cin >> choice;
							if (choice == "a") cheeker = 0;
							else if (choice == "b")cheeker = 1;
							else if (choice == "c")cheeker = 2;
							else if (choice == "d")cheeker = 3;
							else {
								cout << "wrong option try again\n";
								goto qq;
							}
							if (MCQRightAnswer = cheeker)
								MCQRightAnswers++;
							else
								MCQFalseANswer++;
							MCQQ[random2] = true;
							counter++;
							mcq += 1;
						}
						else
						{
							goto er1;
						}
					}
					else
						goto er0;
				}
				if (random == 1)
				{
				er2:
					if (tf < 2)
					{
						int random2 = rand() % TF.size();
						if (!TFQ[random2])
						{
							cout << "True or False\n";
							TF[random2].printQuestion();
							string choice;
							bool cheecker = false;
						er3:
							cin >> choice;
							if (choice == "true") cheecker = true;
							else if (choice == "false")cheecker = false;
							else
							{
								cout << "please write false or true\n";
								goto er3;
							}
							if (TF[random2].getAnswer() == cheecker)
							{
								TFRightAnswer++;
							}
							else
								TFFalseANswer++;

							TFQ[random2] = true;
							counter2++;
							tf += 1;

						}
						else
						{
							goto er2;
						}
					}
					else
						goto er0;
				}
				if (random == 2)
				{
					if (complete < 1)
					{
					err3:
						int random2 = rand() % Complete.size();
						if (!CQ[random2])
						{
							cout << "Complete\n";
							Complete[random2].printQuestion();
							string checker;
							cin >> checker;
							//string checker2 = Complete[random2].getAnswer();
							if (checker == Complete[random2].getAnswer())
								CompleteAnswer = 1;
							CQ[random2] = true;


							complete += 1;
						}
						else
						{
							goto err3;
						}
					}
					else
						goto er0;
				}

			}
			cout << "you get: " << ((1 * MCQRightAnswer) + (2 * TFRightAnswer )+ (3 * CompleteAnswer)) << endl;
			takeQuiz = true;*/
		}
		else
		{
			cout << "no questions please ask your admin to add questions\n";
		}

	}

};
int main()
{
	char y;
	bool checkuser = false;
	string userType, FileName;
	vector<Admin>admins;
	vector<Player>players;
	pair<string, string>userdata;
	int userNumber;
	Quiz quiz;
	string username = "user", password = "00000000", firstname = "user", secondname = "user";
	admins.push_back(Admin(username, password, firstname, secondname));
start:
	cout << "\n*******************************************************************\n";
	cout << "             Welcome to the Quiz game program V2.0!                \n";
	cout << "*******************************************************************\n";

	cout << "user name\n";
	cin >> userdata.first;
	cout << "password\n";
	cin >> userdata.second;
	char choice;
	for (size_t i = 0; i < admins.size(); i++)
	{
		if (admins[i].checkAdmin(userdata))
		{
		start2:
			admins[i].adminMenu();
			cin >> choice;
			switch (choice)
			{
			case '1':
				goto start;
				break;
			case'2':
				cout << "first name\n";
				cin >> userdata.first;
				cout << "second name\n";
				cin >> userdata.second;
				admins[i].updateName(userdata.first, userdata.second);
				goto start2;
				break;
			case'3':
			start4:
			userError1:
				cout << "user name \tfirst name \tsecond name\trole\n";
				copy(admins.begin(), admins.end(), ostream_iterator<Admin>(cout, "\n"));
				copy(players.begin(), players.end(), ostream_iterator<Player>(cout, "\n"));
			error1:
				cout << "Press [n] if you want to add a new user or [b] to go back to the main menu.\n";

				cin >> y;
				if (y == 'b')
				{
					goto start2;
				}
				else if (y == 'n')
				{
					cout << "Which type of user you want to add\n";

					cin >> userType;
					if (userType == "admin" || userType == "Admin")
					{

						cout << "enter user name\n";
						cin >> userdata.first;
						cout << "enter password\n";
						cin >> userdata.second;
						cout << "enter first name \n";
						cin >> firstname;
						cout << "enter second name\n";
						cin >> secondname;
						for (size_t z = 0; z < admins.size(); z++)
						{
							if (userdata == admins[z])
								checkuser = true;
						}
						for (size_t z = 0; z < players.size(); z++)
						{
							if (userdata == players[z])
								checkuser = true;
						}
						if (checkuser)
						{
							cout << "this user already exist\ntry again\n";
							checkuser = false;
							goto start4;
						}
						else
						{
							admins.push_back(Admin(userdata.first, userdata.second, firstname, secondname));
							cout << "this user is created\n";
							checkuser = false;
							goto start4;
						}

					}
					else if (userType == "player" || userType == "Player")
					{

						cout << "enter user name\n";
						cin >> userdata.first;
						cout << "enter password\n";
						cin >> userdata.second;
						cout << "enter first name \n";
						cin >> firstname;
						cout << "enter second name\n";
						cin >> secondname;
						for (size_t z = 0; z < admins.size(); z++)
						{
							if (userdata == admins[z])
								checkuser = true;
						}
						for (size_t z = 0; z < players.size(); z++)
						{
							if (userdata == players[z])
								checkuser = true;
						}
						if (checkuser)
						{
							cout << "this user already exist\ntry again\n";
							checkuser = false;
							goto start4;
						}
						else
						{
							players.push_back(Player(userdata.first, userdata.second, firstname, secondname));
							cout << "Done\n";
							checkuser = false;
							goto start4;
						}
						checkuser = false;
					}
					else
					{
						cout << "please enter player oe admin\n";
						goto userError1;
					}
				}
				else
				{
					cout << "try again\n";
					cin.ignore(9999, '\n');
					goto error1;
				}
				break;
			case'4':
			userError:
				cout << "Which type of user you want to add\n";

				cin >> userType;
				if (userType == "admin" || userType == "Admin")
				{

					cout << "enter user name\n";
					cin >> userdata.first;
					cout << "enter password\n";
					cin >> userdata.second;
					cout << "enter first name \n";
					cin >> firstname;
					cout << "enter second name\n";
					cin >> secondname;
					for (size_t z = 0; z < admins.size(); z++)
					{
						if (userdata == admins[z])
							checkuser = true;
					}
					for (size_t z = 0; z < players.size(); z++)
					{
						if (userdata == players[z])
							checkuser = true;
					}
					if (checkuser)
					{
						cout << "this user already exist\ntry again\n";
						checkuser = false;
						goto start2;
					}
					else
					{
						admins.push_back(Admin(userdata.first, userdata.second, firstname, secondname));
						cout << "this user is created\n";
						checkuser = false;
						goto start2;
					}
					checkuser = false;
				}
				else if (userType == "player" || userType == "Player")
				{

					cout << "enter user name\n";
					cin >> userdata.first;
					cout << "enter password\n";
					cin >> userdata.second;
					cout << "enter first name \n";
					cin >> firstname;
					cout << "enter second name\n";
					cin >> secondname;
					for (size_t z = 0; z < admins.size(); z++)
					{
						if (userdata == admins[z])
							checkuser = true;
					}
					for (size_t z = 0; z < players.size(); z++)
					{
						if (userdata == players[z])
							checkuser = true;
					}
					if (checkuser)
					{
						cout << "this user already exist\ntry again\n";
						checkuser = false;
						goto start2;
					}
					else
					{
						players.push_back(Player(userdata.first, userdata.second, firstname, secondname));
						cout << "Done\n";
						checkuser = false;
						goto start2;
					}
					checkuser = false;
				}
				else
				{
					cout << "please enter player oe admin\n";
					cin.ignore(9999, '\n');
					goto userError;
				}
				//cout << "press[b] to back or[e] to exit\n";

				goto start2;
				break;
			case '5':
				quiz.getQuestions();
				goto start2;
				break;
			case'6':
				quiz.addNewQuestion();
				goto start2;
				break;
			case'7':
				cout << "enter File Name\n";
				cin.ignore();
				getline(cin, FileName);
				quiz.setQuestions(FileName);
				goto start2;
				break;
			case'8':
				goto end;
				break;
			default:
				cout << "please enter one of this numbers{1,2,3,4,5,6,7,8}\n ";
				cin.ignore(9999, '\n');
				goto start2;
				break;
			}

		}
	}
	for (size_t i = 0; i < players.size(); i++)
	{
		if (players[i].checkPlayer(userdata))
		{
		start3:
			players[i].playerMenu();
			cin >> choice;
			switch (choice)
			{
			case'1':
				goto start;
				break;
			case'2':
				cout << "enter first name\n";
				cin >> firstname;
				cout << "enter second name\n";
				cin >> secondname;
				players[i].updateName(firstname, secondname);
				goto start3;
				break;
			case'3':
				quiz.startQuiz();
				if (takeQuiz)
				{
					players[i].calculateGrade(MCQRightAnswers, TFRightAnswer, CompleteAnswer);
					players[i].setMCQAnswer(MCQRightAnswers, MCQFalseANswer);
					players[i].setTFAnswer(TFRightAnswer, TFFalseANswer);
					players[i].setCompleteANswer(CompleteAnswer);
					CompleteAnswer = 0;
					MCQRightAnswers = 0;
					MCQFalseANswer = 0;
					TFRightAnswer = 0;
					TFFalseANswer = 0;
					takeQuiz = false;
					tf = 0;
					complete = 0;
					mcq = 0;

				}
				goto start3;
			case'4':
				players[i].scoreStatistics();
			error7:
				cout << "Press [b] if you want to go back to the main menu or [e] to exit\n";
				cin >> y;
				if (y == 'b')
				{
					goto start3;
				}
				else if (y == 'e')
					goto end;
				else
				{
					cout << "try again\n";
					cin.ignore(9999, '\n');
					goto error7;
				}
				break;
			case'5':
				players[i].allScore();
			error8:
				cout << "Press [b] if you want to go back to the main menu or [e] to exit\n";
				cin >> y;
				if (y == 'b')
				{
					goto start3;
				}
				else if (y == 'e')
					goto end;
				else
				{
					cout << "try again\n";
					cin.ignore(9999, '\n');

					goto error8;
				}
				break;
			case'6':
				goto end;
				break;
			default:
				cout << "wrong option try again\n";
				cin.ignore(9999, '\n');
				goto start3;
				break;
			}

		}

	}
	cout << "error in user name or pasword\n";
	goto start;
end:
	return 0;
}