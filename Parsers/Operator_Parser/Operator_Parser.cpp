/*
Name Jiten Sidhpura
UID 2018130051
Roll No 57
Batch D
TE COMPS

Aim : To Implement the Bottom-Up Operator Precedence Parser for the given grammar 

Non Terminals --> {E}
Terminals --> {|,&,i}
Start Symbol --> E
Productions --> {
        E -> E & E
        E -> E | E
        E -> i
    }

*/

// $ is assumed to be empty symbol of the stack
#include <bits/stdc++.h>
#define debug(x) cout << #x << " " << x << endl;
using namespace std;

// Class to parse a string
class OperatorParser
{

    // private data structures to help while parsing the input string
private:
    map<string, int> f_function_values, g_function_values;
    string buffer;
    map<string, string> mapping_productions;
    set<pair<string, string>> non_comparables;
    set<string> terminals, non_terminals, identifers;

    // public functions of the class
public:
    // Constructor to initialize all the variables and the data structure of the object
    OperatorParser()
    {
        initialize();
    }

    // To parse the input string
    void parse(string &input)
    {

        this->buffer = input;

        int i = 0;
        stack<string> mystack;
        mystack.push("$");
        // $ is pushed at the start of the stack

        cout << "Stack \t\tBuffer \t\tRule\n";

        int cnt = 0;

        // Loop until string is traversed completely
        while (i < this->buffer.size())
        {
            // cnt++;
            // if(cnt == 50) break;

            print_stack(mystack);

            string substring = (this->buffer).substr(i);
            cout << substring << "\t\t";

            string f_value, g_value;

            // find the valid stack element and the buffer element
            f_value = get_valid_element_from_stack(mystack);
            g_value = string{this->buffer[i]};

            // Condition for accepting the input string
            if (f_value == "$" and g_value == "$")
            {
                cout << "String is Accepted";
                break;
            }

            // If pairs are incomparable then break
            else if (this->non_comparables.count(make_pair(f_value, g_value)) > 0)
            {
                cout << "Cannot be Compared";
                break;
            }

            // If f and g values are absent then break
            else if (this->f_function_values.count(f_value) == 0 or this->g_function_values.count(g_value) == 0)
            {
                cout << "Not Found";
                break;
            }

            // Shift Operation Condition
            else if (this->f_function_values[f_value] <= this->g_function_values[g_value])
            {
                cout << "Shift";
                i++;
                mystack.push(g_value);
            }

            // Reduce Operation Condition
            else if (this->f_function_values[f_value] >= this->g_function_values[g_value])
            {
                // Identifier Case
                if (this->identifers.count(mystack.top()) > 0)
                {

                    // Found Production to Substitute
                    if (this->mapping_productions.count(mystack.top()) > 0)
                    {
                        string temp = mystack.top();
                        mystack.pop();
                        mystack.push(this->mapping_productions[temp]);
                        cout << "Reduced " << temp << " with " << this->mapping_productions[temp] << " -> " << temp;
                    }

                    // Unable to find substitution
                    else
                    {
                        cout << "Unable to find Production";
                        break;
                    }
                }

                // Non Terminal Case
                else if (this->non_terminals.count(mystack.top()) > 0)
                {
                    string substitute = "";

                    substitute += mystack.top();
                    mystack.pop();
                    substitute += mystack.top();
                    mystack.pop();
                    substitute += mystack.top();
                    mystack.pop();

                    // Found Production to Substitute
                    if (this->mapping_productions.count(substitute) > 0)
                    {
                        mystack.push(this->mapping_productions[substitute]);
                        cout << "Reduced " << substitute << " with " << this->mapping_productions[substitute] << " -> " << substitute;
                    }

                    // Unable to find substitution
                    else
                    {
                        cout << "Unable to find Production";
                        break;
                    }
                }

                // when string is completely traversed but stack is not empty yet
                else if (g_value == "$" and this->non_terminals.count(mystack.top()) > 0)
                {
                    string substitute = "";

                    substitute += mystack.top();
                    mystack.pop();
                    substitute += mystack.top();
                    mystack.pop();
                    substitute += mystack.top();
                    mystack.pop();

                    // Found Production to Substitute
                    if (this->mapping_productions.count(substitute) > 0)
                    {
                        mystack.push(this->mapping_productions[substitute]);
                        cout << "Reduced " << substitute << " with " << this->mapping_productions[substitute] << " -> " << substitute;
                    }

                    // Unable to find substitution
                    else
                    {
                        cout << "Unable to find Production";
                        break;
                    }
                }

                // Error while parsing the string
                else
                {
                    cout << "Error";
                    break;
                }
            }

            cout << endl;
        }

        cout << endl;
    }

private:
    // Initializes the object variables to help in parsing the input string
    void initialize()
    {
        initialize_functions();
        initalize_mapping_productions();
        initialize_non_comparables();
        initialize_terminals();
        initialize_non_terminals();
        initialize_identifiers();
    }

    // Initializes the map that stores f and g function values
    void initialize_functions()
    {

        // f function values
        this->f_function_values["&"] = 4;
        this->f_function_values["|"] = 2;
        this->f_function_values["i"] = 4;
        this->f_function_values["$"] = 0;

        // g function values
        this->g_function_values["&"] = 3;
        this->g_function_values["|"] = 1;
        this->g_function_values["i"] = 5;
        this->g_function_values["$"] = 0;
    }

    // Initializes the map that maps the RHS of the productions with it's LHS
    void initalize_mapping_productions()
    {
        this->mapping_productions["E&E"] = "E";
        this->mapping_productions["E|E"] = "E";
        this->mapping_productions["i"] = "E";
    }

    // Initializes the set that holds all non comparable pairs
    void initialize_non_comparables()
    {
        this->non_comparables.insert(make_pair("i", "i"));
    }

    // Prints the stack
    void print_stack(stack<string> mystack)
    {
        vector<string> reverse_stack;

        while (!mystack.empty())
        {
            reverse_stack.emplace_back(mystack.top());
            mystack.pop();
        }

        reverse(reverse_stack.begin(), reverse_stack.end());

        for (auto x : reverse_stack)
        {
            cout << x;
        }

        cout << "\t\t";
    }

    // Stores all terminals
    void initialize_terminals()
    {
        this->terminals.insert("&");
        this->terminals.insert("|");
        this->terminals.insert("i");
    }

    // Stores all non terminals
    void initialize_non_terminals()
    {
        this->non_terminals.insert("E");
    }

    // Stores all identifiers
    void initialize_identifiers()
    {
        this->identifers.insert("i");
    }

    // Get valid entry from the stack
    string get_valid_element_from_stack(stack<string> mystack)
    {

        while (!mystack.empty())
        {
            if (this->non_terminals.count(mystack.top()) > 0)
            {
                mystack.pop();
            }
            else
            {
                return mystack.top();
            }
        }

        return "$";
    }
};

// Driver Function
int main(int argc, char **argv)
{

    // Reading input
    string input;

    cout << "Enter the input string : ";
    getline(cin, input);
    // input = "i|i&i";

    //Remove spaces from the input and append $ at the end of the input
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    input += '$';

    //Creating Operator Parser Object
    OperatorParser *operatorparser = new OperatorParser();
    operatorparser->parse(input);
    delete operatorparser;

    return 0;
}