#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
using namespace std;
void decoration();
int initialize(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[], string cartID[], int cartP[], int cartQ[]);
int showRepository(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[]);
int addTOcart(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[], string cartID[], int cartP[], int cartQ[]);
int updateRepository(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[]);
int clearCart(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[], string cartID[], int cartP[], int cartQ[],bool confirm);
int showCart(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[], string cartID[], int cartP[], int cartQ[]);
int searchitem(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[], string cartID[], int cartP[], int cartQ[], bool print);
int editCart(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[], string cartID[], int cartP[], int cartQ[]);
void getUserDetails(string& customerName, string& customerAddress, string& customerContact);
void generateBill(string& customerName, string& customerAddress, string& customerContact, string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[], string cartID[], int cartP[], int cartQ[]);
int deleteItem(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[], string cartID[], int cartP[], int cartQ[]);
int inform(int quantity[],string name[]);
const int N = 50;
int main()
{
	bool confirm = true, print=true;
	int price[N], quantity[N], cartP[N], cartQ[N], op,i;
	string id[N], name[N], weight[N], mfg[N], exp[N], cartID[N], customerAddress, customerName , customerContact;
	initialize(id, price, quantity, name, weight, mfg, exp, cartID, cartP, cartQ);
	for (int x = 0;x < 100;x++)
		cout << "#";
	cout << endl << setw(20) << right << "Welcome to \"Shop Mart\"" << endl;
	for (int x = 0;x < 100;x++)
		cout << "#";
	do {
		decoration();
		cout << "Enter '1' to show repository:\n"
			<< "Enter '2' to serach an item:\n"
			<< "Enter '3' to add something in your cart:\n"
			<< "Enter '4' to show your cart:\n"
			<< "Enter '5' to edit your cart:\n"
			<< "Enter '6' to delete an item in your cart:\n"
			<< "Enter '7' to clear your cart:\n"
			<< "Enter '8' to generate bill and checkout:\n";
		cout << "Select an operator(or '-1' to exit):";
		cin >> op;
		switch (op)
		{
		case 1:
			showRepository(id, price, quantity, name, weight, mfg, exp);
			break;
		case 2:
			searchitem(id, price, quantity, name, weight, mfg, exp, cartID, cartP, cartQ, print);
			
			break;
		case 3:
			addTOcart(id, price, quantity, name, weight, mfg, exp, cartID, cartP, cartQ);
			break;
		case 4:
			showCart(id, price, quantity, name, weight, mfg, exp, cartID, cartP, cartQ);
			break;
		case 5:
			editCart(id, price, quantity, name, weight, mfg, exp, cartID, cartP, cartQ);
			break;
		case 6:
			deleteItem(id, price, quantity, name, weight, mfg, exp, cartID, cartP, cartQ);
			break;
		case 7:
			clearCart(id, price, quantity, name, weight, mfg, exp, cartID, cartP, cartQ, confirm);
			break;
		case 8:
			generateBill(customerName, customerAddress, customerContact, id, price, quantity, name, weight, mfg, exp, cartID, cartP, cartQ);
			op = -1;
			break;
		case -1:
			break;
		default:
			cout << "Invalid operator!\n";
		}

	} while (op != -1);
	for (int x = 0;x < 100;x++)
		cout << "#";
	cout << endl << setw(20) << right << "Thanks for Shopping" << endl;
	for (int x = 0;x < 100;x++)
		cout << "#";
	cout << endl << endl;
	inform(quantity,name);
	return 0;
}