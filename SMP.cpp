#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;
struct Expense {
    string date;
    float amount;
};

void addExpense() // -------- ADD EXPENSE --------
{
    Expense e;
    ofstream file("expenses.txt", ios::app);
    if (!file) 
	{
        cout << "Error opening file!\n";
        return;
    }
    cout << "Enter date (DD-MM-YYYY): ";
    cin >> e.date;
    cout << "Enter amount: ";
    cin >> e.amount;
    file << e.date << " " << e.amount << endl;
    file.close();
    cout << "Expense added successfully!\n";
}
void showAll() // -------- SHOW ALL --------
{
    ifstream file("expenses.txt");
    if (!file) 
	{
        cout << "No data available.\n";
        return;
    }
    string date;
    float amount;
    int i = 1;
    cout << "\n--- Expense List ---\n";
    while (file >> date >> amount) 
	{
        cout << i++ << ". " << date << " - " << amount << endl;
    }
    file.close();
}
void viewByDate() // -------- VIEW BY DATE --------
{
    string searchDate, date;
    float amount;
    bool found = false;
    ifstream file("expenses.txt");
    if (!file) {
        cout << "No data available.\n";
        return;
    }
    cout << "Enter date to search: ";
    cin >> searchDate;
    cout << "\nExpenses on " << searchDate << ":\n";
    while (file >> date >> amount) 
	{
        if (date == searchDate) 
		{
            cout << "Amount: " << amount << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No expenses found for this date.\n";
    }
    file.close();
}
void monthlyReport() // -------- MONTHLY REPORT --------
{
    ifstream file("expenses.txt");
    ofstream report("report.txt");
    if (!file) 
	{
        cout << "No data available.\n";
        return;
    }
    string date;
    float amount, total = 0;
    report << "----- Monthly Expense Report -----\n\n";
    while (file >> date >> amount) 
	{
        report << date << " - " << amount << endl;
        total += amount;
    }
    report << "\nTotal Expense: " << total << endl;
    file.close();
    report.close();
    cout << "Report saved in report.txt\n";
}
void deleteSingle() // -------- DELETE SINGLE --------
{
    ifstream file("expenses.txt");
    if (!file) {
        cout << "No data available.\n";
        return;
    }
    showAll();
    cout << "Enter record number to delete: ";
    int delIndex;
    cin >> delIndex;
    ofstream temp("temp.txt");
    string date;
    float amount;
    int i = 1;
    while (file >> date >> amount) 
	{
        if (i != delIndex) {
            temp << date << " " << amount << endl;
        }
        i++;
    }
    file.close();
    temp.close();
    remove("expenses.txt");
    rename("temp.txt", "expenses.txt");
    cout << "Record deleted successfully.\n";
}

void deleteMenu() // -------- DELETE MENU --------
{
    int choice;
    cout << "\n1. Delete All Data\n";
    cout << "2. Delete Single Record\n";
    cout << "Enter choice: ";
    cin >> choice;
    if (choice == 1)
	 {
        char confirm;
        cout << "Are you sure? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') 
		{
            if (remove("expenses.txt") == 0) 
			{
                cout << "All data deleted.\n";
            }
			else
			{
                cout << "No file found.\n";
            }
        } 
		else 
		{
            cout << "Cancelled.\n";
        }
    }
    else if (choice == 2) 
	{
        deleteSingle();
    }
    else 
	{
        cout << "Invalid choice.\n";
    }
}

void editRecord() // -------- EDIT RECORD --------
{
    ifstream file("expenses.txt");
    if (!file) 
	{
        cout << "No data available.\n";
        return;
    }
    showAll();
    cout << "Enter record number to edit: ";
    int editIndex;
    cin >> editIndex;
    ofstream temp("temp.txt");
    string date;
    float amount;
    int i = 1;
    while (file >> date >> amount) 
	{
        if (i == editIndex) 
		{
            cout << "Enter new date: ";
            cin >> date;
            cout << "Enter new amount: ";
            cin >> amount;
        }
        temp << date << " " << amount << endl;
        i++;
    }
    file.close();
    temp.close();
    remove("expenses.txt");
    rename("temp.txt", "expenses.txt");
    cout << "Record updated successfully.\n";
}

int main()
{
    int choice;
    do {
        cout << "\n===== Expense Manager =====\n";
        cout << "1. Add Expense\n";
        cout << "2. View by Date\n";
        cout << "3. Monthly Report\n";
        cout << "4. Delete Options\n";
        cout << "5. Edit Record\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
		{
            case 1: addExpense(); break;
            case 2: viewByDate(); break;
            case 3: monthlyReport(); break;
            case 4: deleteMenu(); break;
            case 5: editRecord(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } 
	while (choice != 6);
    return 0;
}
