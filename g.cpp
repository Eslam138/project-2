#include <iostream>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

//Ahmed Mohamed Abd El Rashied  20180028;
//Moamen Eid Mahmoud   20180299;
//Eslam Nasser Abd El Kader 20180047;
int ar[4];
static int adq = 0;
static int counter1 = 0, counter2 = 0;
void hhh()
{
	bool arr[100] = { 0 };
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
void cheek(std::ifstream& file)
{
	string line = " ";
	while (getline(file, line)) //(file.is_open())
	{
		counter1++;
		int i = 0;
		while (i < 4)
		{
			if (getline(file, line))
			{
				counter2 += 1;
			}
			i++;
		}
	}
}
void mainMenu(string asd, char &y)
{
	cout << "welcome " << asd << " , please choose from the following options\n";
	cout << "[1] Go to administration menu\n[2] Update your name\n";
	cout << "[3] Start a new quiz\n[4] Display your scores statistics\n[5] Display all your scores\n[6] Exit" << endl;
	cout << "your choice: ";
	cin >> y;
}
string ask[100], q[400];
void loud(std::ifstream& file)
{
	int z = adq*4;
	for (size_t i = adq; i < counter1; i++)
	{
		getline(file, ask[i]);
		for (size_t j = 0; j < 4; j++)
		{
			getline(file, q[z]);
			z++;
		}
	}
	adq += counter1;
}
void Amenu(char &x)
{
	cout << "Welcome to the administration menu, please choose from the following options:\n";
	cout << "[1] View all questions\n[2] Add new question\n[3] Load questions from file\n[4] Go back to main menu" << endl;
	cout << "your choice:";
	cin >> x;
}
void Uname(string& asd)
{
	cout << "your name:_ ";
	cin >> asd;
}
static int y = 0;
static int count1 = 0;
void start_quaz(int answers[][3])
{
	
	int count2 = 0, f = 0, t = 0,id2;
	static int r = 0;
	string d;
	string ch = "abcd";
	string cho[4];
	bool aee[100] = {0};
	if (counter1 > 0)
	{	
		for (size_t cou = 1; cou < 6; cou++)
		{
			int show = rand() % counter1;
			if (!aee[show])
			{
				hhh();
				cout << cou << ": " << ask[show] << endl;
				cout << "\n";
				y = show * 4;
				int id = ar[0];
				for (size_t k = 0; k < 4; k++)
				{
					cho[ar[k]] = q[y];
					y++;
				}
				for (size_t s = 0; s < 4; s++)
				{
					cout << "[" << ch[s] << "]" << cho[s] << "\t";
				}
				cout << "\n";
			er1:
				cout << "your answer_:";
				cin >> d;
				cout << "\n";
				if (d == "a" || d == "b" || d == "c" || d == "d")
				{
					if (d == "a") { id2 = 0; }
					else if (d == "b") { id2 = 1; }
					else if (d == "c") { id2 = 2; }
					else
					{
						id2 = 3;
					}
					if (id2 == id) { t += 1; }
					else
					{
						f += 1;
					}
				}
				else
				{
					cout << "invalid answer try again\n";
					goto er1;
				}
			}
			else
				cou--;
			aee[show] = true;
		}
		r += 1;
		answers[count1][0] = r;
		answers[count1][1] = t;
		answers[count1][2] = f;
		cout << "your correct answers: " << answers[count1][1] << endl;
		cout << "your incorrect answers: " << answers[count1][2] << endl;
		count1++;
	}
	else
		cerr << "you should enter questions \n";
}
void Display_your_scores_statistics(string& n, int answers[][3])
{
	int x = 0, l = 1, y = 10;
	if (answers[0][0] >= 1)
	{
		for (size_t i = 0; i < 10; i++)
		{
			if (answers[i][0] >= 1)
			{
				if (answers[i][0] > l) { l = answers[i][0]; }
				if (answers[i][1] > x) { x = answers[i][1]; }
				if (answers[i][1] < y) { y = answers[i][1]; }
			}
		}
		cout << "Number of Quizzes taken: " << l << endl;
		cout << "Highest score: " << (x * 2) << "/" << "10" << endl;
		cout << "lawiest score: " << (y * 2) << "/" << "10" << endl;
	e:
		cout << "Press [b] if you want to go back to the main menu or [e] to exit\n";
		cin >> n;
		if (n == "b" || n == "e")
			cout << "\n";
		else {
			cout << "invalid option try again:_";
			goto e;
		}
	}
	else
	{
		cerr << "you should take a quiz\n";
		n = "b";
	}
}
void Display_your_scores(string &n, int answers[][3])
{
	if (answers[0][0] > 0)
	{
		for (size_t i = 0; i < 100; i++)
		{
			if (answers[i][0] == 0)
			{
				break;
			}
			else
			{
				cout << "quiz number:" << answers[i][0] << endl;
				cout << "correct answers:" << answers[i][1] << endl;
				cout << "incorrect:" << answers[i][2] << endl;
			}
		}
	e:
		cout << "Press [b] if you want to go back to the main menu or [e] to exit\n";
		cin >> n;
		if (n == "b" || n == "e")
			cout << "\n";
		else {
			cout << "invalid option try again:_";
			goto e;
		}
	}
	else
	{
		cerr << "you shoud take a quiz\n";
		n = "b";
	}
}
void view(string &w, int& x)
{
	char a;
	y = 0;
	int o = 1;
	if (counter1 > 0)
	{ 
		cout << "number of questions:" << counter1 << endl;
		for (size_t i = 0; i < counter1; i++)
		{
			cout << "[" << o << "]" << ask[i] << endl;
			cout << "\n";
			o++;
			for (size_t s = 0; s < 4; s++)
			{
				cout << q[y] << "\t";
				y++;
			}
			cout << "\n";
		}
	er:
		cout << "----------------------------------------\n";
		cout << "Press[d] and the question ID if you want to delete a question(Example: d 2)\n";
		cout << "Press[b] if you want to go back to the main menu\n";
		cin >> w;
		if (w == "d" || w == "b")
		{
			if (w == "d")
			{
				cin >> x;
				if (x > counter1)
				{
					cerr << "no question in this number try again\n";
					goto er;
				}
			}
		}
		else
		{
			cerr << "invalid option try again\n";
			goto er;
		}
	}
	else
	{
		cerr << "you shoud add a question \n";
		w = "b";
	}
}
void add()
{
	int i = 1;
	cout << "enter new question"<<endl;
	cin.ignore();
	getline(cin, ask[counter1]);
	for (size_t j = 0; j < 4; j++)
	{
		cout << "enter Choice number " << i << endl;
		getline(cin, q[counter2]);
		counter2++;
		i++;
	}
	adq++;
	counter1++;
}
void remove(int n)
{
	n--;
	int tem = n + 1, i1 = n * 4, i2=(n*4) + 4;
	for (size_t i = n; i < 99; i++)
	{
		swap(ask[i], ask[tem]);
		tem++;
		swap(q[i1], q[i2]);
		i1++; i2++;
		swap(q[i1], q[i2]);
		i1++; i2++;
		swap(q[i1], q[i2]);
		i1++; i2++;
		swap(q[i1], q[i2]);
		i1++; i2++;
	}
	counter1--;
	counter2 -= 4;
	adq--;
}
int main()
{
	string name = { "user" };
	string n,w;
	int answers[10][3] = { 0,0,0 };
	char choose1, choose2;
	int u;
	ifstream file1, file2;
	e2:
	mainMenu(name,choose1);
	switch (choose1)
	{
	case '1':
	e3:
		Amenu(choose2);
		switch (choose2)
		{
		case '1':
			view(w,u);
			if (w == "b")
			{
				goto e2;
			}
			else
			{
				remove(u);
				goto e3;
			}
			break;
		case '2':
			add();
			goto e3;
			break;
		case '3':
		e4:
			cout << "enter file name \n";
			cin >> n;
			file1.open(n.c_str());
			file2.open(n.c_str());
			cheek(file1);
			if ((counter1 * 4) == counter2)
			{
				loud(file2);
			}
			else
			{
				cerr << "this file not include asks \n";
				cout << "try again please\n";
				goto e3;
			}
			goto e3;
			break;
		case '4':
			goto e2;
			break;
		default:
			cout << "invalid option \n";
			choose1=0;
			goto e2;
			break;
		}
		break;
	case '2':
		Uname(name);
		goto e2;
		break;
	case '3':
		start_quaz(answers);
		goto e2;
		break;
	case '4':
		Display_your_scores_statistics(n, answers);
		if (n == "b") { goto e2; }
		break;
	case '5':
		Display_your_scores(n, answers);
		if (n == "b") 
		{
			goto e2;
		}
		break;
	case '6':
		break;
	default:
		cout << "invalid option\n";
		goto e2;
		break;
	}
	return 0;
}
