// Smart Supermarket Billing & Inventory System

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

void clearScreen() {
	system("cls");
}

class Product {
	public:
		int id;
		string name;
		double price;
		int quantity;

		Product() {
			id = 0;
			name = "";
			price = 0;
			quantity = 0;
		}

		void input(int newId) {
			id = newId;
			cout << "Enter Product Name: ";
			cin.ignore();
			getline(cin, name);
			do {
				cout << "Enter Price: ";
				cin >> price;
				if (price < 0)
					cout << "Price cannot be negative. Try again.\n";
			} while (price < 0);

			do {
				cout << "Enter Quantity: ";
				cin >> quantity;
				if (quantity < 0)
					cout << "Quantity cannot be negative. Try again.\n";
			} while (quantity < 0);

		}

		void display() {
			cout << setw(5) << id << setw(15) << name << setw(10) << price << setw(10) << quantity << endl;
		}
};


class Inventory {
	public:
		Product products[100];
		int productCount;

		Inventory() {
			productCount = 0;
		}

		void loadFromFile() {
			ifstream fin("products.txt");
			productCount = 0;
			string line;

			while (getline(fin, line)) {
				int pos1 = line.find('|');
				int pos2 = line.find('|', pos1 + 1);
				int pos3 = line.find('|', pos2 + 1);

				if (pos1 == -1 || pos2 == -1 || pos3 == -1) continue;

				products[productCount].id = stoi(line.substr(0, pos1));
				products[productCount].name = line.substr(pos1 + 1, pos2 - pos1 - 1);
				products[productCount].price = stof(line.substr(pos2 + 1, pos3 - pos2 - 1));
				products[productCount].quantity = stoi(line.substr(pos3 + 1));

				productCount++;
			}
			fin.close();
		}


		void saveToFile() {
			ofstream fout("products.txt");
			for (int i = 0; i < productCount; i++) {
				fout << products[i].id << "|"
				     << products[i].name << "|"
				     << products[i].price << "|"
				     << products[i].quantity << endl;
			}
			fout.close();
		}


		void addProduct() {
			if (productCount >= 100) {
				cout << "Inventory full!\n";
				return;
			}
			int newId = (productCount == 0) ? 1 : products[productCount - 1].id + 1;
			products[productCount].input(newId);

			productCount++;

			saveToFile();
			cout << "Product added successfully.\n";
		}

		void viewProducts();
		void updateProduct();
		void deleteProduct();

		Product* findProductById(string idStr) {
			int id = stoi(idStr);
			for (int i = 0; i < productCount; ++i) {
				if (products[i].id == id) {
					return &products[i];
				}
			}
			return nullptr;
		}
};

void Inventory::viewProducts() {
	if (productCount == 0) {
		cout << "\nNo products available.\n";
		return;
	}

	cout << "\n--- Product List ---\n";
	cout << left << setw(10) << "ID"
	     << setw(20) << "Name"
	     << setw(10) << "Price"
	     << setw(10) << "Qty" << endl;
	cout << "----------------------------------------------\n";

	for (int i = 0; i < productCount; ++i) {
		cout << left << setw(10) << products[i].id
		     << setw(20) << products[i].name
		     << setw(10) << fixed << setprecision(2) << products[i].price
		     << setw(10) << products[i].quantity << endl;
	}
}
void Inventory::updateProduct() {
	if (productCount == 0) {
		cout << "\nNo products to update.\n";
		return;
	}

	int id;
	cout << "\nEnter Product ID to update: ";
	cin >> id;

	bool found = false;

	for (int i = 0; i < productCount; ++i) {
		if (products[i].id == id) {
			found = true;
			cout << "\nCurrent Details:\n";
			cout << "Name: " << products[i].name << endl;
			cout << "Price: " << products[i].price << endl;
			cout << "Quantity: " << products[i].quantity << endl;

			cout << "\nEnter new name: ";
			cin.ignore();
			getline(cin, products[i].name);

			cout << "Enter new price: ";
			cin >> products[i].price;
			if (products[i].price < 0) {
				cout << "Price can't be negative. Setting to 0.\n";
				products[i].price = 0;
			}

			cout << "Enter new quantity: ";
			cin >> products[i].quantity;
			if (products[i].quantity < 0) {
				cout << "Quantity can't be negative. Setting to 0.\n";
				products[i].quantity = 0;
			}

			saveToFile();
			cout << "\nProduct updated successfully.\n";
			break;
		}
	}

	if (!found) {
		cout << "\nProduct with ID " << id << " not found.\n";
	}
}
void Inventory::deleteProduct() {
	if (productCount == 0) {
		cout << "\nNo products to delete.\n";
		return;
	}

	int id;
	cout << "\nEnter Product ID to delete: ";
	cin >> id;

	bool found = false;

	for (int i = 0; i < productCount; ++i) {
		if (products[i].id == id) {
			found = true;

			for (int j = i; j < productCount - 1; ++j) {
				products[j] = products[j + 1];
			}

			productCount--;

			saveToFile();
			cout << "\nProduct deleted successfully.\n";
			break;
		}
	}

	if (!found) {
		cout << "\nProduct with ID " << id << " not found.\n";
	}
}


class User {
	protected:
		string username, password;
	public:
		User(string u = "", string p = "") : username(u), password(p) {}
		virtual void dashboard() = 0;
};


class AdminUser : public User {
	public:
		AdminUser() : User("", "") {}
		AdminUser(string u, string p) : User(u, p) {}

		void dashboard() override {
			Inventory inv;
			inv.loadFromFile();
			int choice;
			do {
				clearScreen();
				cout << "=====================================\n";
				cout << "           ADMIN DASHBOARD\n";
				cout << "=====================================\n";
				cout << "  [1] Add Product\n";
				cout << "  [2] View Products\n";
				cout << "  [3] Update Product\n";
				cout << "  [4] Delete Product\n";
				cout << "  [0] Logout\n";
				cout << "-------------------------------------\n";
				cout << "Enter your choice: ";
				cin >> choice;

				switch (choice) {
					case 1:
						inv.addProduct();
						system("pause");
						break;
					case 2:
						inv.viewProducts();
						system("pause");
						break;
					case 3:
						inv.updateProduct();
						system("pause");
						break;
					case 4:
						inv.deleteProduct();
						system("pause");
						break;
					case 0:
						cout << "Logging out...\n";
						break;
					default:
						cout << "Invalid choice.\n";
						break;
				}

			} while (choice != 0);
		}
};


class Billing {
	public:
		void generateBill(Inventory& inv) {
			const int MAX_ITEMS = 50;
			Product cart[MAX_ITEMS];
			int quantities[MAX_ITEMS];
			int count = 0;
			string id;
			char choice;
            
            clearScreen();
			inv.viewProducts();

			do {
				cout << "\nEnter Product ID to add to cart: ";
				cin >> id;

				Product* p = inv.findProductById(id);
				if (p != nullptr) {
					cout << "Enter quantity: ";
					int qty;
					cin >> qty;

					if (qty <= 0) {
						cout << "Quantity must be greater than 0.\n";
					} else if (qty > p->quantity) {
						cout << "Not enough stock available.\n";
					} else {
						cart[count] = *p;
						quantities[count] = qty;
						count++;
						p->quantity -= qty;
						cout << "Product added to cart.\n";
					}

				} else {
					cout << "Product not found.\n";
				}

				cout << "Add more products? (y/n): ";
				cin >> choice;

			} while (choice == 'y' || choice == 'Y');

			if (count == 0) {
				cout << "Cart is empty. No bill generated.\n";
				return;
			}
			clearScreen();
			double total = 0;
			system("mkdir bills >nul 2>&1");

			time_t now = time(0);
			tm* ltm = localtime(&now);
			char filename[100];
			sprintf(filename, "bills/bill_%04d%02d%02d_%02d%02d%02d.txt",
			        1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,
			        ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

			ofstream billFile(filename);

			char timeStr[100];
			strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", ltm);

			cout << "=============================================\n";
			cout << "              SuperMarket Bill\n";
			cout << "             " << timeStr << "\n";
			cout << "=============================================\n";
			cout << left << setw(8) << "ID"
			     << setw(15) << "Name"
			     << setw(6) << "Qty"
			     << setw(8) << "Unit"
			     << setw(10) << "Subtotal" << "\n";
			cout << "---------------------------------------------\n";

			billFile << "=============================================\n";
			billFile << "              SuperMarket Bill\n";
			billFile << "             " << timeStr << "\n";
			billFile << "=============================================\n";
			billFile << left << setw(8) << "ID"
			         << setw(15) << "Name"
			         << setw(6) << "Qty"
			         << setw(8) << "Unit"
			         << setw(10) << "Subtotal" << "\n";
			billFile << "---------------------------------------------\n";

			for (int i = 0; i < count; i++) {
				double subtotal = cart[i].price * quantities[i];
				cout << left << setw(8) << cart[i].id
				     << setw(15) << cart[i].name
				     << setw(6) << quantities[i]
				     << setw(8) << fixed << setprecision(2) << cart[i].price
				     << setw(10) << subtotal << "\n";

				billFile << left << setw(8) << cart[i].id
				         << setw(15) << cart[i].name
				         << setw(6) << quantities[i]
				         << setw(8) << fixed << setprecision(2) << cart[i].price
				         << setw(10) << subtotal << "\n";

				total += subtotal;
			}

			cout << "---------------------------------------------\n";
			cout << right << setw(37) << "TOTAL: " << total << "\n";
			cout << "=============================================\n";
			cout << setw(30) << "       Thank you for shopping with us!\n";
			cout << "=============================================\n";

			billFile << "---------------------------------------------\n";
			billFile << right << setw(37) << "TOTAL: " << total << "\n";
			billFile << "=============================================\n";
			billFile << setw(30) << "       Thank you for shopping with us!\n";
			billFile << "=============================================\n";


			billFile.close();
			inv.saveToFile();
		}
};


class CashierUser : public User {
	public:
		CashierUser() : User("", "") {}
		CashierUser(string u, string p) : User(u, p) {}

		void dashboard() override {
			Inventory inv;
			Billing bill;
			inv.loadFromFile();

			int choice;
			do {
				clearScreen();
				cout << "\n=====================================\n";
				cout << "         CASHIER DASHBOARD\n";
				cout << "=====================================\n";
				cout << "  [1] Generate Bill\n";
				cout << "  [2] View Products\n";
				cout << "  [0] Logout\n";
				cout << "-------------------------------------\n";
				cout << "Enter your choice: ";

				cin >> choice;
				switch (choice) {
					case 1:
						bill.generateBill(inv);
						system("pause");
						break;
					case 2:
						inv.viewProducts();
						system("pause");
						break;
					case 0:
						cout << "Logging out...\n";
						break;
					default:
						cout << "Invalid choice. Try again.\n";
				}
			} while (choice != 0);
		}

};


bool login(User*& loggedInUser) {
	string user, pass, role;
	cout << "===================\n";
	cout << "      Login \n";
	cout << "===================\n";
	cout << "Username: ";
	cin >> user;
	cout << "Password: ";
	cin >> pass;

	ifstream fin("users.txt");
	string line;
	while (getline(fin, line)) {
		size_t pos1 = line.find(',');
		size_t pos2 = line.rfind(',');

		if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2)
			continue;

		string fileUser = line.substr(0, pos1);
		string filePass = line.substr(pos1 + 1, pos2 - pos1 - 1);
		string fileRole = line.substr(pos2 + 1);

		if (user == fileUser && pass == filePass) {
			if (fileRole == "Admin") {
				loggedInUser = new AdminUser(user, pass);
			} else if (fileRole == "Cashier") {
				loggedInUser = new CashierUser(user, pass);
			} else {
				cout << "Unknown role type in file.\n";
				return false;
			}
			fin.close();
			return true;
		}
	}

	fin.close();
	cout << "Invalid credentials!\n";
	return false;
}


int main() {
	clearScreen();

	int choice;
	do {
		system("cls");
		cout << "=====================================\n";
		cout << "       SMART SUPERMARKET SYSTEM      \n";
		cout << "=====================================\n";
		cout << "  1. Login\n";
		cout << "  0. Exit\n";
		cout << "-------------------------------------\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
			case 1: {
				clearScreen();
				User* user = nullptr;
				if (login(user)) {
					system("pause");
					user->dashboard();
					delete user;
				} else {
					cout << "Login failed.\n";
					system("pause");
				}
				break;
			}
			case 0:
				cout << "\nExiting program...";
				break;
			default:
				cout << "Invalid choice. Try again.\n";
				system("pause");
		}
	} while (choice != 0);
	return 0;
}
