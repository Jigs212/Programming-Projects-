
#include <iostream>
#include <string>
#include <stack>
using namespace std;
// node for grades
struct grade_node {
	float data;
	grade_node* nextg; // next grade
};
// node for subject name
struct subj_node {
	string subj;
	subj_node* nexts; // next subject
};
// for displaying
void line_dash() {
	cout << "-------";
}
class ListStack {
private:
	float grades[5] = { 89.25,95.10,84.45,78.90,75.35 };
	string subjects[5] = { "Data Structures", "Automata", "Discrete Structures",
	"Calculus", "Artificial Intelligence" };
	int SIZE = sizeof(grades) / sizeof(grades[0]);
	grade_node* head1; // 1 for the grades linked list
	grade_node* tail1;
	subj_node* head2; // 2 for the subject name linked list
	subj_node* tail2;
	string password;
	stack <char> reverse; // stack that reverses the string/other stack
	stack <char> processor; // stack that processes the encryption
	stack <char> last_3; // stack containing the last 3 characters
public:
	ListStack() {
		head1 = NULL;
		tail1 = NULL;
		head2 = NULL;
		tail2 = NULL;
	}
	~ListStack() {
		system("cls");
		cout << "Thank you" << endl;
	}
	//input validation
	void input_val(bool& check) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			system("cls");
		}
		else {
			check = false;
		}
	}
	// will create the initial linked lists of the subjects and their respective grades
		void set() {
		for (int i = 0; i < SIZE; i++) {
			grade_node* temp1 = new grade_node;
			subj_node* temp2 = new subj_node;
			temp1->data = grades[i];
			temp1->nextg = NULL;
			// checks if list is empty (for grades)
			if (head1 == NULL) {
				head1 = temp1;
				tail1 = temp1;
			}
			else {
				tail1->nextg = temp1;
				tail1 = tail1->nextg;
			}
			temp2->subj = subjects[i];
			temp2->nexts = NULL;
			// checks if list is empty (for subject name)
			if (head2 == NULL) {
				head2 = temp2;
				tail2 = temp2;
			}
			else {
				tail2->nexts = temp2;
				tail2 = tail2->nexts;
			}
		}
	}
	void printing() {
		system("cls");
		cout << " List of subjects and grades" << endl << endl;
		grade_node* temp1 = head1;
		subj_node* temp2 = head2;
		while (temp1 != NULL && temp2 != NULL) {
			cout << temp2->subj << ": " << temp1->data << endl;
			temp1 = temp1->nextg;
			temp2 = temp2->nexts;
		}
	}
	void highest_grade() {
		system("cls");
		grade_node* temp1 = head1;
		subj_node* temp2 = head2;
		float high_grade = 0.0;
		string high_subj;
		high_grade = temp1->data;
		high_subj = temp2->subj;
		// will find the highest grade
		while (temp1 != NULL && temp2 != NULL) {
			if (temp1->data > high_grade) {
				high_grade = temp1->data;
				high_subj = temp2->subj;
			}
			temp1 = temp1->nextg;
			temp2 = temp2->nexts;
		}
		cout << "The highest grade is: " << endl;
		cout << high_subj << ": " << high_grade << endl;
	}
	void lowest_grade() {
		system("cls");
		grade_node* temp1 = head1;
		subj_node* temp2 = head2;
		float low_grade = 0.0;
		string low_subj;
		low_grade = temp1->data;
		low_subj = temp2->subj;
		// will find the lowest grade
		while (temp1 != NULL && temp2 != NULL) {
			if (temp1->data < low_grade) {
				low_grade = temp1->data;
				low_subj = temp2->subj;
			}
			temp1 = temp1->nextg;
			temp2 = temp2->nexts;
		}
		cout << "The lowest grade is: " << endl;
		cout << low_subj << ": " << low_grade << endl;
	}
	void average_grade() {
		system("cls");
		float average = 0.0;
		float temp_grade = 0.0;
		int counter = 0;
		cout << " List of subjects and grades" << endl << endl;
		grade_node* temp1 = head1;
		subj_node* temp2 = head2;
		while (temp1 != NULL && temp2 != NULL) {
			temp_grade = temp1->data;
			average = average + temp_grade;
			cout << temp2->subj << ": " << temp1->data << endl;
			temp1 = temp1->nextg;
			temp2 = temp2->nexts;
			counter++;
		}
		average = average / counter;
		cout << endl << endl;
		cout << "Average grade is: " << average << endl;
	}
	void add_grade() {
		system("cls");
		float new_grade = 0.0;
		string new_subject;
		bool grade_check = true;
		do {
			cout << "Please enter a valid grade: ";
			cin >> new_grade;
			// grade validation
			if (new_grade >= 0.0 && new_grade <= 100.0) {
				grade_check = false;
			}
			else {
				system("cls");
				cout << "Invalid Grade" << endl << endl;
			}
		} while (grade_check == true);
		system("cls");
		cin.clear();
		cin.ignore();
		cout << "Please enter the subject name: ";
		getline(cin, new_subject);
		system("cls");
		grade_node* temp1 = new grade_node;
		subj_node* temp2 = new subj_node;
		temp1->data = new_grade;
		temp2->subj = new_subject;
		temp1->nextg = NULL;
		temp2->nexts = NULL;
		tail1->nextg = temp1;
		tail1 = tail1->nextg;
		tail2->nexts = temp2;
		tail2 = tail2->nexts;
		cout << "The new subject is: " << endl;
		cout << temp2->subj << ": " << temp1->data << endl;
	}
	void user_password() {
		system("cls");
		cin.clear();
		cin.ignore();
		bool password_check = true;
		do {
			line_dash();
			cout << "PASSWORD ENCRYPTION";
			line_dash();
			cout << endl << endl << endl;
			cout << "Please enter the desired password to encrypt (alphanumeric characters, 5 - 20 characters only)" << endl;
				getline(cin, password);
			int counter = 0;
			if (password.length() >= 5 && password.length() <= 20) {
				//checks if password is valid
				for (int i = 0; i < password.length(); i++) {
					if (!isalnum(password[i])) {
						counter++;
					}
				}
				if (counter == 0) {
					password_check = false;
				}
				else {
					system("cls");
					cout << "Invalid Password" << endl << endl;
				}
			}
			else {
				system("cls");
				cout << "Invalid Password" << endl << endl;
			}
		} while (password_check == true);
	}
	// the numbers represent the steps
	// reverses the password
	void encrypt_1() {
		system("cls");
		for (int i = 0; i < password.length(); i++) {
			reverse.push(password[i]);
		}
		cout << "Password: " << password << endl;
		cout << "Step 1: ";
		while (!reverse.empty()) {
			cout << reverse.top();
			processor.push(reverse.top());
			reverse.pop();
		}
		cout << endl;
	}
	// changes vowels into digits and digits into 'V'
	void encrypt_2() {
		while (!processor.empty()) {
			if (isalpha(processor.top())) {
				processor.top() = tolower(processor.top());
				switch (processor.top()) {
				case 'a': {
					processor.top() = '1';
					break;
				}
				case 'e': {
					processor.top() = '2';
					break;
				}
				case 'i': {
					processor.top() = '3';
					break;
				}
				case 'o': {
					processor.top() = '4';
					break;
				}
				case 'u': {
					processor.top() = '5';
					break;
				}
				default: {
					break;
				}
				}
			}
			else if (isdigit(processor.top())) {
				processor.top() = 'V';
			}
			reverse.push(processor.top());
			processor.pop();
		}
		cout << "Step 2: ";
		while (!reverse.empty()) {
			cout << reverse.top();
			processor.push(reverse.top());
			reverse.pop();
		}
		cout << endl;
	}
	// gets the last 3 characters and places a copy to the front
	void encrypt_3() {
		int counter = 3;
		while (!processor.empty()) {
			reverse.push(processor.top());
			if (counter > 0) {
				last_3.push(processor.top());
			}
			processor.pop();
			counter--;
		}
		cout << "Step 3: ";
		password.clear();
		while (!last_3.empty()) {
			cout << last_3.top();
			password.push_back(last_3.top());
			last_3.pop();
		}
		while (!reverse.empty()) {
			cout << reverse.top();
			password.push_back(reverse.top());
			reverse.pop();
		}
		cout << endl << endl;
		cout << "\t Encrypted Password: " << password << endl;
	}
	void repeat(bool& val) {
		bool validation = true;
		do {
			system("cls");
			char choice;
			cout << "Try Again [Y/N]" << endl;
			cin >> choice;
			choice = toupper(choice);
			switch (choice) {
			case 'N': {
				validation = false;
				val = false;
				break;
			}
			case 'Y': {
				validation = false;
				break;
			}
			default: {
				system("cls");
				cout << "Invalid Input" << endl << endl;
				break;
			}
			}
		} while (validation == true);
		{
		}
	}
};
int main()
{
	ListStack ls; //ls meaning linnked list and stack
	ls.set();
	bool try_again = true;
	do {
		char choice1;
		bool validation1 = true;
		do {
			cout << "Would you like to: " << endl;
			cout << "[A] Monitor your grades" << endl;
			cout << "[B] Encrypt a password" << endl << endl;
			cin >> choice1;
			choice1 = toupper(choice1);
			ls.input_val(validation1);
		} while (validation1 == true);
		switch (choice1) {
		case 'A': {
			bool check = true;
			do {
				bool validation2 = true;
				int choice2;
				do {
					system("cls");
					line_dash();
					cout << "GRADES";
					line_dash();
					cout << endl << endl << endl;
					cout << "[1]\t Display Grades " << endl;
					cout << "[2]\t Highest Grade " << endl;
					cout << "[3]\t Lowest Grade " << endl;
					cout << "[4]\t Average Grade " << endl;
					cout << "[5]\t Add Grades " << endl;
					cout << "[6]\t Exit " << endl << endl;
					cin >> choice2;
					ls.input_val(validation2);
				} while (validation2 == true);
				switch (choice2) {
				case 1: {
					ls.printing();
					system("pause");
					break;
				}
				case 2: {
					ls.highest_grade();
					system("pause");
					break;
				}
				case 3: {
					ls.lowest_grade();
					system("pause");
					break;
				}
				case 4: {
					ls.average_grade();
					system("pause");
					break;
				}
				case 5: {
					ls.add_grade();
					system("pause");
					break;
				}
				case 6: {
					check = false;
					break;
				}
				default: {
					system("cls");
					cout << "Invalid Input" << endl << endl;
					break;
				}
				}
			} while (check == true);
			break;
		}
		case 'B': {
			ls.user_password();
			ls.encrypt_1();
			ls.encrypt_2();
			ls.encrypt_3();
			break;
		}
		default: {
			system("cls");
			cout << "Invalid Input" << endl << endl;
			break;
		}
		}
		system("pause");
		ls.repeat(try_again);
		system("cls");
	} while (try_again == true);
}