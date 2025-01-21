#include<iostream>	
#include<iomanip>
#include<fstream>
#include<string>
const int N = 50;
using namespace std;
void decoration()
{
	cout << endl << endl;
	for (int i = 0; i <= 100; i++)
		cout << "*";
	cout << endl << endl;
}
int clearCart(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[], string cartID[], int cartP[], int cartQ[], bool confirm)
{
	if (confirm)
	{
		string ask;
		decoration();
		cout << "Are you sure to clear your cart?(y/n):";
		cin >> ask;
		if (ask == "n")
			return 1;
	}
	for (int i = 0; i < N; i++)
	{
		cartID[i] = id[i];
		cartP[i] = price[i];
		if(confirm)
			quantity[i] += cartQ[i];
		cartQ[i] = 0;
	}
	if (confirm)
		cout << "Cart cleared successfully\n\n";
	return 0;
}
int initialize(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[], string cartID[], int cartP[], int cartQ[])
{
	bool confirm = false;
	ifstream fin("storage.txt");
	if (!fin.is_open())
	{
		cout << "**ERROR OPENING FILE**";
		return -2;
	}
	for (int i = 0;i < N;i++)
	{
		fin >> id[i];
		fin >> name[i];
		fin >> weight[i];
		fin >> mfg[i];
		fin >> exp[i];
		fin >> price[i];
		fin >> quantity[i];
	}
	fin.close();
	clearCart(id, price, quantity, name, weight, mfg, exp, cartID,cartP,cartQ, confirm);
	return 0;
}
int showRepository(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[])
{
	decoration();
	cout << setw(15) << left << "Product ID" << setw(20) << left << "Name" << setw(15) << left << "Weight"<<setw(15) << left<<"MFG" << setw(15) << left << "EXP"<< setw(15) << left <<"Price" << setw(15) << left << "Quantity"<<endl;
	for (int i = 0;i < N;i++)
	{
		cout <<setw(15)<<left<< id[i] ;
		cout <<setw(20)<<left<< name[i] ;
		cout <<setw(15)<<left<< weight[i] ;
		cout <<setw(15)<<left<< mfg[i] ;
		cout <<setw(15)<<left<< exp[i] ;
		cout <<setw(15)<<left<< price[i] ;
		cout <<setw(15)<<left<< quantity[i] ;
		cout << endl;
	}
	return 0;
}
int searchitem(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[], string cartID[], int cartP[], int cartQ[], bool print)
{
	int  i, j;
	string uname;
	bool validName = false;
A:
	i = 0;
	if (print)
	{
		decoration();
	}
	cout << "Enter the product name or ID (or '-1' to exit):";
	cin >> uname;
	if (uname == "-1")
		return -1;
	for (j = 0; !(validName) && j < N; j++)
	{
		if (name[j] == uname)
		{
			i = j;
			validName = true;
		}
		else if (id[j] == uname)
		{
			i = j;
			validName = true;
		}
	}
	if (!validName)
	{
		cout << "Product not found in the repository, try AGAIN!!\n\n";
		goto A;
	}
	if (print)
	{
		cout << setw(15) << left << id[i];
		cout << setw(20) << left << name[i];
		cout << setw(15) << left << weight[i];
		cout << setw(15) << left << mfg[i];
		cout << setw(15) << left << exp[i];
		cout << setw(15) << left << price[i];
		cout << setw(15) << left << quantity[i];
		cout << endl;
	}
	return i;
}
int addTOcart(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[], string cartID[], int cartP[], int cartQ[])
{
	decoration();
	int  num, i;
	bool valid ;
	bool print=false;
		A:
		i = searchitem(id, price, quantity, name, weight, mfg, exp, cartID, cartP, cartQ, print);
		if (i == -1)
			return -1;
		if (quantity[i] == 0)
		{
			cout << "Sorry we have no more pieces of " << name[i] << " left\n\n";
			goto A;
		}
		do {
		valid=true;
		cout << "Input Quantity for "<<name[i]<<":";
		cin >> num;
		if (num < 0)
		{
			cout << "Input a real quantity\n\n";
			valid = false;
		}
		else if (num > quantity[i])
		{
			cout << "Don't have enough stock, we have only " << quantity[i] << " left, SORRY!!\n\n";
			valid = false;
		}
		}while(!valid);
		cartQ[i] += num;
		quantity[i] -= num;
		cout << endl << name[i] << " price of one piece=" << price[i] << ". price for " << cartQ[i] << " pieces=" << num * price[i] << endl;
	
	return 0;
}
int updateRepository(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[])
{
	ofstream fout("storage.txt");
	for (int i = 0;i < N;i++)
	{
		fout << setw(15) << left << id[i];
		fout << setw(20) << left << name[i];
		fout << setw(15) << left << weight[i];
		fout << setw(15) << left << mfg[i];
		fout << setw(15) << left << exp[i];
		fout << setw(15) << left << price[i];
		fout << setw(15) << left << quantity[i];
		fout << endl;
	}
	fout.close();
	return 0;
}
int showCart(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[], string cartID[], int cartP[], int cartQ[])
{
	decoration();
	cout << setw(15) << left << "Product ID" << setw(20) << left << "Name" << setw(15) << left << "Weight" << setw(15) << left
		<< "MFG" << setw(15) << left << "EXP" << setw(15) << left << "Price" << setw(15) << left << "Quantity" << endl;
	for (int i = 0; i < N; i++)
	{
		if (cartQ[i] != 0)
		{
			cout << setw(15) << left << id[i];
			cout << setw(20) << left << name[i];
			cout << setw(15) << left << weight[i];
			cout << setw(15) << left << mfg[i];
			cout << setw(15) << left << exp[i];
			cout << setw(15) << left << price[i];
			cout << setw(15) << left << cartQ[i];
			cout << endl;
		}
	}
	return 0;
}
int editCart(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[], string cartID[], int cartP[], int cartQ[])
{
	int i,op,num;
	string uname;
	bool  valid, print = false;
	showCart(id, price, quantity, name, weight, mfg, exp, cartID, cartP, cartQ);
	A:
	i = searchitem(id, price, quantity, name, weight, mfg, exp, cartID, cartP, cartQ, print);
	if (i == -1)
		return -1;
	if (cartQ[i]==0)
	{
		cout << "Nothing is in your cart, try AGAIN!!\n\n";
		goto A;
	}
	do 
	{
		cout << "Enter '1' for adding and enter '2' for substracting the quantity of " << name[i] << ":";
		cin >> op;
	} while (op != 1 && op != 2);
	if (op == 1)
	{
		if (quantity[i] == 0)
		{
			cout << "Sorry we have no more pieces of " << name[i] << " left\n\n";
			goto A;
		}
		do {
			valid = true;
			cout << "Input Quantity you want to add in " << name[i] << " (or '-1' to exit):";
			cin >> num;
			if (num == -1)
				return -1;
			if (num < 0)
			{
				cout << "Input a real quantity\n\n";
				valid = false;
			}
			else if (num > quantity[i])
			{
				cout << "Don't have enough stock, we have only " << quantity[i] << " left, SORRY!!\n\n";
				valid = false;
			}
		} while (!valid);
		cartQ[i] += num;
		quantity[i] -= num;
		cout << name[i] << " price of one piece=" << price[i] << ". price for " << cartQ[i] << " pieces=" << num * price[i] << endl;
	}
	else
	{
		do {
			valid = true;
			cout << "Input Quantity you want to substract from " << name[i] << " (or '-1' to exit):";
			cin >> num;
			if (num == -1)
				return -1;
			if (num < 0)
			{
				cout << "Input a real quantity\n\n";
				valid = false;
			}
			else if (num > cartQ[i])
			{
				cout << "You have not enough quantity in cart, you only have "<<cartQ[i]<<" left!!\n\n";
				valid = false;
			}
		} while (!valid);
		cartQ[i] -= num;
		quantity[i] += num;
		cout << endl << "You have " << cartQ[i] << " pieces of " << name[i] << " left in your cart\n";
	}	
	return 0;
}
void getUserDetails(string& customerName, string& customerAddress, string& customerContact)
{
	decoration();
	cout << "";
	getline(cin, customerName);
	cout << " Enter your name: ";
	getline(cin, customerName);
	cout << " Enter your address: ";
	getline(cin, customerAddress);
	cout << "Enter your contact number: ";
	getline(cin, customerContact);
	ofstream detailsFile("customer_details.txt", ios::app);
	detailsFile << customerName << ", " << customerAddress << endl;
	detailsFile.close();
}
void generateBill(string& customerName, string& customerAddress, string& customerContact, string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[], string cartID[], int cartP[], int cartQ[])
{
	getUserDetails(customerName, customerAddress, customerContact);
	decoration();
	ifstream detailsFile("customer_details.txt");
	string line;
	bool loyaltyCheck = false;
	int orderCount = 0;
	while (getline(detailsFile, line))
	{
		if (line == customerName + ", " + customerAddress)
		{
			orderCount++;
		}
	}
	detailsFile.close();
	if (orderCount >= 5)
	{
		loyaltyCheck = true;
	}
	ofstream billFile("bills/" + customerName + ".txt", ios::app);
	billFile << "Customer Name: " << customerName << endl;
	billFile << "Customer Address: " << customerAddress << endl;
	billFile << "==================================================================================" << endl;
	billFile << setw(30) << left << "Product Name" << "\t";
	billFile << setw(10) << left << "Quantity" << "\t";
	billFile << setw(10) << left << "Price/Qty" << "\t";
	billFile << setw(15) << left << "Total Price" << endl;
	billFile << "==================================================================================" << endl;
	cout << "Customer Name: " << customerName << endl;
	cout << "Customer Address: " << customerAddress << endl;
	cout << "==================================================================================" << endl;
	cout << setw(30) << left << "Product Name" << "\t";
	cout << setw(10) << left << "Quantity" << "\t";
	cout << setw(10) << left <<"Price/Qty" << "\t";
	cout << setw(15) << left << "Total Price" << endl;
	cout << "==================================================================================" << endl;
	float subTotal = 0;
	for (int i = 0; i < N; i++)
	{
		if (cartQ[i] != 0)
		{
			float itemPrice = cartQ[i] * price[i];
			subTotal = subTotal + itemPrice;
			billFile << setw(30) << left << name[i] << "\t";
			billFile << setw(10) << left << cartQ[i] << "\t";
			billFile << setw(10) << left << price[i] << "\t";
			billFile << setw(15) << left << itemPrice << endl;
			cout << setw(30) << left << name[i] << "\t";
			cout << setw(10) << left << cartQ[i] << "\t";
			cout << setw(10) << left << price[i] << "\t";
			cout << setw(15) << left << itemPrice << endl;
		}
	}
	billFile << "----------------------------------------------------------------------------------" << endl;
	cout << "----------------------------------------------------------------------------------" << endl;
	float tax = 0.1; 
	float deliveryCharge = 100; 
	float taxAmount = subTotal * tax;
	if (subTotal >= 10000.0)
	{
		deliveryCharge = 0.0; 
		cout << "Your order exceeds 10,000 PKR. Your delivery charges have been waived off. Enjoy! " << endl;
	}
	else if(subTotal<=0)
		deliveryCharge = 0.0;
	float total = subTotal + taxAmount + deliveryCharge;
	if (loyaltyCheck)
	{
		total = total - (total * 0.2);
	}
	billFile << setw(25) << left << "Subtotal:" << "\t" << setw(15) << subTotal << " PKR" << endl;
	billFile << setw(25) << left << "Tax (10%):" << "\t" << setw(15) << taxAmount << " PKR" << endl;
	billFile << setw(25) << left << "Delivery Charge:" << "\t" << setw(15) << deliveryCharge << " PKR" << endl;
	cout << setw(25) << left << "Subtotal:" << "\t" << setw(15) << subTotal << " PKR" << endl;
	cout << setw(25) << left << "Tax (10%):" << "\t" << setw(15) << taxAmount << " PKR" << endl;
	cout << setw(25) << left << "Delivery Charge:" << "\t" << setw(15) << deliveryCharge << " PKR" << endl;
	if (loyaltyCheck)
	{
		billFile << setw(25) << left << "Loyalty Discount:" << "\t" << setw(15) << (subTotal * 0.2) << " PKR" << endl;
		cout << setw(25) << left << "Loyalty Discount:" << "\t" << setw(15) << (subTotal * 0.2) << " PKR" << endl;
	}
	billFile << "----------------------------------------------------------------------------------" << endl;
	billFile << setw(25) << left << "Total Bill:" << "\t" << setw(15) << total << " PKR" << endl;
	cout << "----------------------------------------------------------------------------------" << endl;
	cout << setw(25) << left << "Total Bill:" << "\t" << setw(15) << total << " PKR" << endl;
	billFile.close();
	updateRepository(id, price, quantity, name, weight, mfg, exp);
}
int deleteItem(string id[], int price[], int quantity[], string name[], string weight[], string mfg[], string exp[], string cartID[], int cartP[], int cartQ[])
{
	bool  print = false;
	string  ask;
	showCart(id, price, quantity, name, weight, mfg, exp, cartID, cartP, cartQ);
	A:
	int i = searchitem(id, price, quantity, name, weight, mfg, exp, cartID, cartP, cartQ, print);
	if (i == -1)
		return 0;
	if (cartQ[i] == 0)
	{
		cout << "Product not found in the cart, try AGAIN!!\n\n";
		goto A;
	}
	else
	{
		cout << "Are you sure to delete " << name[i] << " from your cart?(y/n):";
		cin >> ask;
		if (ask == "y")
		{
			quantity[i] += cartQ[i];
			cartQ[i] = 0;
		}
		else
		{
			return 1;
		}
	}
	return 0;
}
int inform(int quantity[], string name[])
{
	for (int j = 0;j < N;j++)
	{
		if (quantity[j] <= 2)
		{
			for (int i = 1;i < 100;i++)
				cout << "!";
			cout << endl << "We are running short of " << name[j] << " $$Message for staff$$\n";
		}
	}
	cout << endl << endl;
	return 0;
}
