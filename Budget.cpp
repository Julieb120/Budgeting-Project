#include <iostream>
#include <fstream>
#include <string>
#include <fstream>
#include <iomanip>



using namespace std;

class Expenses
{
public: 
	int amount;
	string location;

};

class Categories
{
public:
	int spent=0;
	string category;
	int budget =0;
};


enum resume { yes = 1, no = 2 };

void Header();
void CreateBudget(int &budgCount, Categories category[]);
void CreateExpense(int &expCount, int &totalSpent, Expenses expense[], Categories category[], int budgCount);
void CreateIncome(int &totalIncome);
//void SaveFile(Categories category[], int budgCount, int totalIncome, int totalSpent);
//void LoadFile(Categories category[], int budgCount, int totalIncome, int totalSpent);
void DisplaySummary(Categories category[], int totalIncome, int budgCount);
void SpendingHistory(int expCount, Expenses expense[]);



int main()
{
	//Classes
	Expenses expense[1000];
	Categories category[1000];
	

	
	//variables
	int expCount = 0;
	int budgCount = 0;

	int choice;

	int totalIncome = 0;
	int totalSpent = 0; // sum spent amount
	
	//LoadFile(category, budgCount, totalIncome, totalSpent);

	while (true)
	{
		Header();
		cin >> choice;


		if (choice == 1)
		{
			CreateBudget(budgCount, category);
		}
		else if (choice == 2)
		{
			CreateExpense(expCount, totalSpent, expense, category, budgCount);
		}
		else if (choice == 3)
		{
			CreateIncome(totalIncome);
		}

		else if (choice == 4)
		{
			DisplaySummary(category, totalIncome, budgCount);
			//SaveFile(category, budgCount, totalIncome, totalSpent);
		}

		else if (choice == 5)
		{
			SpendingHistory(expCount, expense);
		}

		else if (choice == 6)
		{
			break;
		}
	}

	system("PAUSE");
	return 0;

}

void Header()
{
	cout << "Budgeting System" << endl;
	cout << "1:Create Budget" << endl;
	cout << "2:Input expense" << endl;
	cout << "3:Input income" << endl;
	cout << "4:Budget Summary " << endl;
	cout << "5:Spending History" << endl;
	cout << "6:Exit" << endl;
	cout << "=========================" << endl;
}
void CreateBudget (int &budgCount, Categories category[])
{

	int resume = yes;

	cout << "Type the categories you'd like in your budget" << endl;
	//set to zero
	category[budgCount].budget = 0;
	category[budgCount].spent = 0;

	while (resume == yes) //TRUE
	{
		cout << "Category: ";
		cin.ignore();
		getline(cin, category[budgCount].category);

		cout << "Budget for " << category[budgCount].category << ": ";
		cin >> category[budgCount].budget;

		budgCount++;

		cout << "Another category?" <<endl;
		cout << "   1-Yes" << endl;
		cout << "   2-No" << endl;
		cin >> resume;
		cout << endl;

		if (resume == no)
		{
			 // BREAK
		}
	
	}
		
}

void CreateExpense(int &expCount, int &totalSpent, Expenses expense[], Categories category[], int budgCount)
{
	int resume = yes;
	int amountSpent = 0;
	int catNum = 0;
	
	while (resume == yes) 
	{
		cout << "Where did you spend?" << endl;
		cin.ignore();
		getline(cin, expense[expCount].location); 


		cout << "How much did you spend?" << endl;
		
		cin >> amountSpent;
		expense[expCount].amount = amountSpent;
		

		cout << "What category did you spend in?" << endl;
		
		for (int i = 0; i < budgCount; i++)
		{
			cout << i << ": " << category[i].category << endl;
		}
		cin >> catNum;

		int sum =0;
		

		
		sum = category[catNum].spent + amountSpent;
		category[catNum].spent = amountSpent;


		totalSpent += expense[expCount].amount;

		expCount++;

		cout << "Another category?" << endl;
		cout << "   1-Yes" << endl;
		cout << "   2-No" << endl;
		cin >> resume;
		cout << endl;
	

		if (resume == no)
		{
			//BREAK
		}
	}	
}

void CreateIncome(int &totalIncome)
{
	int income = 0;

	cout << "How much income have received?" << endl;
	cin >> income;

	totalIncome += income;
}

void DisplaySummary(Categories category[],  int totalIncome, int budgCount) 
{
	
	
	cout << setw(10)<< "Over/Under" <<setw(12)<< "Category" << setw(12) << "Budgeted" << setw(12) << "Spent" << setw(12) << "Difference" << endl;
	for (int i = 0; i < budgCount; i++)
	{
		if (category[i].spent > category[i].budget) // check if over budget
		{
			cout << setw(12)<< "Over" << setw(12) << category[i].category << setw(12) << category[i].budget << setw(12) << category[i].spent << setw(12) << category[i].budget - category[i].spent << endl;
		}
		
		if (category[i].spent < category[i].budget) // check if under budget
		{
			cout << setw(12)<<  "Under" << setw(12) <<category[i].category << setw(12) << category[i].budget << setw(12) << category[i].spent << setw(12) << category[i].budget - category[i].spent << endl;
		}
	}

}

void SpendingHistory(int expCount, Expenses expense[])
{
	cout << "Spending History" << endl;
	//TEST
	cout << expCount << endl;
	//END
	
	for (int i = 0;i < expCount; i++)
	{
		cout << expense[i].location << setw(12) << expense[i].amount << endl;
	}
}

void SaveFile(Categories category[], int budgCount, int totalIncome, int totalSpent)
{
	ofstream file("budget.txt");

	file << budgCount;
	file << totalIncome;
	file << totalSpent;
	// file << "Category" << " " <<  "Budgeted" <<" " << "Spent" << endl;

	for (int i = 0; i < budgCount; i++)
	{
		file << category[i].category << " " << category[i].budget << " " << category[i].spent;

		if (i < budgCount - 1) 
		{
			file << endl;
		}
	}

	file.close();
}

void LoadFile(Categories category[], int budgCount, int totalIncome, int totalSpent)
{
	ifstream file("budget.txt");
	if (!file.good()) { return; }

	file >> budgCount;
	file >> totalIncome;
	file >> totalSpent;
	//file >> "Category" << " " << "Budgeted" << " " << "Spent" << endl;
	for (int i = 0; i < budgCount; i++) {
		file >> category[i].category;
		file >> category[i].budget;
		file >> category[i].spent;
	}

	file.close();
}

