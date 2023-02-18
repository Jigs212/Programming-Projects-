
#include <iostream>
#include <Windows.h>
using namespace std;
class Pqueue {
private:
	struct {
		int process_no = 0;
		int arrival_time = 0;
		int burst_time = 0;
		int priority = 0;
		double waiting_time = 0;
		int service_time = 0;
	}process[10]; // struct containing variables for priority queue array
	int front;
	int rear;
	int at; // arrival time input
	int bt; // burst time input
	int pr; // priority input
	int process_quantity; // the number of processes
	double average_wt; // average waiting time
public:
	Pqueue() {
		front = rear = -1;
		at = 0;
		bt = 0;
		pr = 0;
		process_quantity = 0;
		average_wt = 0;
	}
	~Pqueue() {
		cout << endl << endl << "\tProcessing" << endl;
		Sleep(3000);
		system("cls");
	}
	void inputval(bool& val) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			system("cls");
		}
		else {
			val = false;
		}
	}
	void numproc() {
		do {
			bool validation = true;
			do {
				system("cls");
				cout << "Enter the number of processes to handle (from 3 to 10 only): " << endl;
					cin >> process_quantity;
				inputval(validation);
			} while (validation == true);
		} while (process_quantity < 3 || process_quantity > 10); // this will repeat as long as there is an invalid number
	}
	void inserting() {
		for (int i = 0; i < process_quantity; i++) {
			bool num_check = true;
			bool priority_check = true;
			do {
				cout << "Process " << i + 1 << ": " << endl;
				process[i].process_no = i + 1;
				if (i == 0) {
					front = i;
					process[i].arrival_time = 0;
					cout << "Arrival Time: " << process[i].arrival_time << endl;
					priority_check = false;
				}
				else {
					bool at_check = true;
					do {
						cout << "Arrival Time: ";
						cin >> at;
						process[i].arrival_time = at;
						// will make sure that arrival time is valid for the succeeding processes
							if (process[i].arrival_time > process[i - 1].arrival_time)
							{
								at_check = false;
							}
					} while (at_check == true);
				}
				cout << "CPU Burst: ";
				cin >> bt;
				process[i].burst_time = bt;
				// checks if the process is the first one in the queue
				if (priority_check == false) {
					cout << "Priority: ";
					process[i].priority = 1;
					cout << process[i].priority << endl;
				}
				else {
					cout << "Priority: ";
					cin >> pr;
					process[i].priority = pr;
				}
				if (bt > 0 || pr > 0) {
					num_check = false; // checks if data is valid
				}
			} while (num_check == true);
			rear++;
			cout << endl;
		}
	}
	void sorting() {
		int temp = 0;
		for (int i = front; i <= rear; i++) {
			for (int j = front; j < rear; j++) {
				if (process[j].priority > process[j + 1].priority) {
					// sorting according to priority
					temp = process[j].priority;
					process[j].priority = process[j + 1].priority;
					process[j + 1].priority = temp;
					temp = process[j].process_no;
					process[j].process_no = process[j + 1].process_no;
					process[j + 1].process_no = temp;
					temp = process[j].arrival_time;
					process[j].arrival_time = process[j + 1].arrival_time;
					process[j + 1].arrival_time = temp;
					temp = process[j].burst_time;
					process[j].burst_time = process[j + 1].burst_time;
					process[j + 1].burst_time = temp;
				}
			}
		}
		cout << "\tGantt Chart" << endl << endl;
		for (int i = front; i <= rear; i++) {
			cout << process[i].process_no << "-";
		}
	}
	// computes the waiting time
	void compute() {
		process[front].service_time = process[front].burst_time - process[front].arrival_time;
		process[front].waiting_time = process[front].burst_time; // since the first process' arrival time is 0
		average_wt += process[front].waiting_time;

		for (int i = front + 1; i <= rear; i++) {
			process[i].service_time = process[i - 1].service_time +process[i].burst_time;
			process[i].waiting_time = (double)process[i].service_time - (double)process[i].arrival_time;

			if (process[i].waiting_time < 0) {
				process[i].waiting_time = 0;
			}
			average_wt += process[i].waiting_time; // storing fr the average waiting time
		}
		average_wt = average_wt / process_quantity;
	}
	void print() {
		cout << "\tWaiting Time:" << endl << endl;
		int temp = 0;
		for (int i = front; i <= rear; i++) {
			for (int j = front; j < rear; j++) {
				if (process[j].process_no > process[j + 1].process_no) {
					// sorting according to process number
					temp = process[j].priority;
					process[j].priority = process[j + 1].priority;
					process[j + 1].priority = temp;

					temp = process[j].process_no;
					process[j].process_no = process[j + 1].process_no;
					process[j + 1].process_no = temp;

					temp = process[j].arrival_time;
					process[j].arrival_time = process[j + 1].arrival_time;
					process[j + 1].arrival_time = temp;

					temp = process[j].burst_time;
					process[j].burst_time = process[j + 1].burst_time;
					process[j + 1].burst_time = temp;

					temp = process[j].service_time;
					process[j].service_time = process[j + 1].service_time;
					process[j + 1].service_time = temp;

					temp = process[j].waiting_time;
					process[j].waiting_time = process[j + 1].waiting_time;
					process[j + 1].waiting_time = temp;
				}
			}
		}
		for (int i = front; i <= rear; i++) {
			// printing according to process number
			cout << "Process " << process[i].process_no << ": " <<
				process[i].waiting_time << endl;
		}
		cout << endl << "Average Waiting time: " << average_wt << endl << endl;
	}
	void repeat(bool& repeat) {
		bool check = true;
		do {
			char choice;
			cout << "\n\nTry again [Y/N]: ";
			cin >> choice;
			choice = toupper(choice);
			switch (choice) {
			case 'Y': {
				system("cls");
				check = false;
				break;
			}
			case 'N': {
				check = false;
				repeat = false;
				break;
			}
			default: {
				cout << "Invalid Input\n\n";
				break;
			}
			}
		} while (check == true);
	}
};
int main()
{
	bool repeat = true;
	do {
		Pqueue pq;
		pq.numproc();
		cout << endl << endl;
		pq.inserting();
		cout << endl << endl;
		pq.sorting();
		pq.compute();
		cout << endl << endl;
		pq.print();
		pq.repeat(repeat);
	} while (repeat == true);
}