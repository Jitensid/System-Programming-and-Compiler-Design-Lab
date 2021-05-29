/*
Name Jiten Sidhpura
UID 2018130051
Roll No 57
Batch D
TE COMPS

Aim : To Implement the Bottom-Up SLR Parser for the given grammar {V,T,P,S}.

Non Terminals --> {E,T,F}
Terminals --> {+,*,a,b}
Start Symbol --> E
Productions --> {
        E -> E + T | T
        T -> T F | F
        F -> F* | a | b
    }

*/

// $ is assumed to be empty symbol of the stack
#include <bits/stdc++.h>
#define debug(x) cout << #x << " " << x << endl;
using namespace std;

// class to represent SLR Parser
class SLRParser
{
	// private data structures to help while parsing the input string
private:
	unordered_map<string, pair<string, string>> slr_parsing_table;
	string buffer;
	string shift_action = "shift", reduce_action = "reduce", non_terminal_action = "non_terminal_action", accept_action = "accepted";
	unordered_map<string, string> productions_lhs, productions_rhs;

public:
	// Constructor to initialize all the variables and the data structure of the object
	SLRParser()
	{
		initalize();
	}

	// To parse the input string
	void parse(string &input)
	{
		// Initiliaze the stack for parsing
		stack<string> mystack;
		mystack.push("$");
		mystack.push("0");

		this->buffer = input;

		int index = 0;

		cout << "Stack \t\tBuffer \t\tAction\n";

		while (index < this->buffer.length())
		{
			string stack_top = mystack.top();

			string key = this->buffer[index] + stack_top;

			this->print_stack(mystack);
			this->print_buffer(index);

			// If key is present
			if (this->slr_parsing_table.count(key) > 0)
			{
				// first get the action type
				string action_type = this->get_action_type(this->slr_parsing_table[key]);

				// shift action state
				if (action_type == this->shift_action)
				{
					this->handle_shift_action(mystack, index, key);
				}

				// reduce action state
				else if (action_type == this->reduce_action)
				{
					this->handle_reduce_action(mystack, key);
				}

				// non_terminal action state
				else if (action_type == this->non_terminal_action)
				{
					this->handle_non_terminal_action(mystack);
				}

				// accept action state
				else if (action_type == this->accept_action)
				{
					this->handle_accept_action(mystack);
					return;
				}
			}

			// Return error since key is not present in the table
			else
			{
				cout << "Error while parsing the given string" << endl;
				return;
			}
		}
	};

private:
	// Initializes the object variables to help in parsing the input string
	void initalize()
	{
		initialize_slr_parsing_table();
		initialize_productions_lhs();
		initialize_productions_rhs();
	}

	// Intializes the slr parsing table
	void initialize_slr_parsing_table()
	{
		string shift_action = this->shift_action;
		string non_terminal_action = this->non_terminal_action;
		string accept_action = this->accept_action;
		string reduce_action = this->reduce_action;

		this->slr_parsing_table["a0"] = make_pair(shift_action, "5");
		this->slr_parsing_table["b0"] = make_pair(shift_action, "4");
		this->slr_parsing_table["E0"] = make_pair(non_terminal_action, "1");
		this->slr_parsing_table["T0"] = make_pair(non_terminal_action, "2");
		this->slr_parsing_table["F0"] = make_pair(non_terminal_action, "3");

		this->slr_parsing_table["+1"] = make_pair(shift_action, "6");
		this->slr_parsing_table["$1"] = make_pair(accept_action, "0");

		this->slr_parsing_table["a2"] = make_pair(shift_action, "5");
		this->slr_parsing_table["b2"] = make_pair(shift_action, "4");
		this->slr_parsing_table["+2"] = make_pair(reduce_action, "2");
		this->slr_parsing_table["$2"] = make_pair(reduce_action, "2");
		this->slr_parsing_table["F2"] = make_pair(non_terminal_action, "7");

		this->slr_parsing_table["a3"] = make_pair(reduce_action, "4");
		this->slr_parsing_table["b3"] = make_pair(reduce_action, "4");
		this->slr_parsing_table["+3"] = make_pair(reduce_action, "4");
		this->slr_parsing_table["*3"] = make_pair(shift_action, "8");
		this->slr_parsing_table["$3"] = make_pair(reduce_action, "4");

		this->slr_parsing_table["a4"] = make_pair(reduce_action, "7");
		this->slr_parsing_table["b4"] = make_pair(reduce_action, "7");
		this->slr_parsing_table["+4"] = make_pair(reduce_action, "7");
		this->slr_parsing_table["*4"] = make_pair(reduce_action, "7");
		this->slr_parsing_table["$4"] = make_pair(reduce_action, "7");

		this->slr_parsing_table["a5"] = make_pair(reduce_action, "6");
		this->slr_parsing_table["b5"] = make_pair(reduce_action, "6");
		this->slr_parsing_table["+5"] = make_pair(reduce_action, "6");
		this->slr_parsing_table["*5"] = make_pair(reduce_action, "6");
		this->slr_parsing_table["$5"] = make_pair(reduce_action, "6");

		this->slr_parsing_table["a6"] = make_pair(shift_action, "5");
		this->slr_parsing_table["b6"] = make_pair(shift_action, "4");
		this->slr_parsing_table["T6"] = make_pair(non_terminal_action, "9");
		this->slr_parsing_table["F6"] = make_pair(non_terminal_action, "3");

		this->slr_parsing_table["a7"] = make_pair(reduce_action, "3");
		this->slr_parsing_table["b7"] = make_pair(reduce_action, "3");
		this->slr_parsing_table["+7"] = make_pair(reduce_action, "3");
		this->slr_parsing_table["*7"] = make_pair(shift_action, "8");
		this->slr_parsing_table["$7"] = make_pair(reduce_action, "3");

		this->slr_parsing_table["a8"] = make_pair(reduce_action, "5");
		this->slr_parsing_table["b8"] = make_pair(reduce_action, "5");
		this->slr_parsing_table["+8"] = make_pair(reduce_action, "5");
		this->slr_parsing_table["*8"] = make_pair(reduce_action, "5");
		this->slr_parsing_table["$8"] = make_pair(reduce_action, "5");

		this->slr_parsing_table["a9"] = make_pair(shift_action, "5");
		this->slr_parsing_table["b9"] = make_pair(shift_action, "4");
		this->slr_parsing_table["F9"] = make_pair(non_terminal_action, "7");
		this->slr_parsing_table["+9"] = make_pair(reduce_action, "1");
		this->slr_parsing_table["$9"] = make_pair(reduce_action, "1");
	}

	// initializes the map of rhs of all prodcutions with number
	void initialize_productions_rhs()
	{
		this->productions_rhs["1"] = "E+T";
		this->productions_rhs["2"] = "T";
		this->productions_rhs["3"] = "TF";
		this->productions_rhs["4"] = "F";
		this->productions_rhs["5"] = "F*";
		this->productions_rhs["6"] = "a";
		this->productions_rhs["7"] = "b";
	}

	// initializes the map of lhs of all prodcutions with number
	void initialize_productions_lhs()
	{
		this->productions_lhs["1"] = "E";
		this->productions_lhs["2"] = "E";
		this->productions_lhs["3"] = "T";
		this->productions_lhs["4"] = "T";
		this->productions_lhs["5"] = "F";
		this->productions_lhs["6"] = "F";
		this->productions_lhs["7"] = "F";
	}

	// Returns action type of the pair
	string get_action_type(pair<string, string> &slr_parsing_table_pair)
	{
		return slr_parsing_table_pair.first;
	}

	// handles shift action
	void handle_shift_action(stack<string> &mystack, int &index, string &key)
	{
		mystack.push(string(1, this->buffer[index]));
		mystack.push(this->slr_parsing_table[key].second);
		cout << "Shift " << this->buffer[index] << "  with state " << this->slr_parsing_table[key].second << endl;
		index++;
	}

	// handles reduce action
	void handle_reduce_action(stack<string> &mystack, string &key)
	{
		mystack.pop();

		string production_index = this->slr_parsing_table[key].second;

		string original_rhs_of_production = this->productions_rhs[production_index];
		string rhs_of_production = this->productions_rhs[production_index];
		string lhs_of_production = this->productions_lhs[production_index];

		reverse(rhs_of_production.begin(), rhs_of_production.end());

		string replace_stack_contents = "";

		while (!mystack.empty())
		{

			string stack_top_string = mystack.top();

			if (replace_stack_contents == rhs_of_production)
			{
				string previous_number = mystack.top();

				mystack.push(lhs_of_production);

				mystack.push(this->slr_parsing_table[lhs_of_production + previous_number].second);

				cout << "Reduce " << this->slr_parsing_table[key].first << this->slr_parsing_table[key].second
					 << " " << lhs_of_production << " -> " << original_rhs_of_production << endl;
				break;
			}

			else if (!isdigit(stack_top_string[0]))
			{
				replace_stack_contents += stack_top_string[0];
			}

			mystack.pop();
		}
	}

	// handles non_terminal action
	void handle_non_terminal_action(stack<string> &mystack)
	{
	}

	// handles accept action
	void handle_accept_action(stack<string> &mystack)
	{
		cout << "The Given String is Accepted \n";
	}

	// print contents of the stack
	void print_stack(stack<string> mystack)
	{
		string stack_to_string = "";
		while (!mystack.empty())
		{
			stack_to_string.append(mystack.top());
			mystack.pop();
		}

		reverse(stack_to_string.begin(), stack_to_string.end());

		cout << stack_to_string << "\t\t";
	}

	// print contents of the buffer
	void print_buffer(int &index)
	{
		int start = index;

		for (int i = start; i < this->buffer.length(); i++)
		{
			cout << this->buffer[i];
		}
		cout << "\t\t";
	}
};

// Driver Function
int main(int argc, char **argv)
{

	string input;

	cout << "Enter the input string : ";
	getline(cin, input);
	input += '$';
	// Test ab*a+b

	// Creating SLR Parser Object
	SLRParser *slrparser = new SLRParser();
	slrparser->parse(input);
	delete slrparser;

	cout << endl;
	return 0;
}