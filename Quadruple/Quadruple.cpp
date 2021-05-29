/*
Name: Jiten Sidhpura
Class: TE COMPS
Batch: D
UID: 2018140051
Roll No. 57
Experiment No. 8  - Program to generate Quadruple table for the given postfix String.
*/

#include <bits/stdc++.h>
using namespace std;

// Class to generate the quadruple table for every string provided by the user
class QuadrupleTableGenerator
{
    string input_postfix;

public:
    // Generate the Table for given postfix expression
    void generate_table(string &postfix_expression)
    {
        // stack datastructure for evalaution
        stack<string> mystack;

        // To store the data in the quadruple table format
        vector<pair<pair<string, string>, pair<string, string>>> quadruple_table_array;

        // To store quadruple mapping
        map<string, string> quadruple_mapping;

        // to count the number of entries in the map (unique values)
        int counter = 0;

        // represents the element in the table
        pair<pair<string, string>, pair<string, string>> quadruple_table_element;

        // traverse the string from left to right
        for (auto x : postfix_expression)
        {

            // if the character is an alphabet
            if (isalpha(x))
            {
                mystack.push(string{x});
            }

            // if the character is not an alphabet
            else
            {
                string operand1, operand2;

                // get the stack top element if stack not empty
                if (!mystack.empty())
                {
                    operand1 = mystack.top();
                    mystack.pop();
                }

                // get the stack top element if stack not empty
                if (!mystack.empty())
                {
                    operand2 = mystack.top();
                    mystack.pop();
                }

                // create the expression from 2 operands and then push it into the stack
                string result;
                result.append(operand1);
                result += x;
                result.append(operand2);

                // if string not found in the map then store it
                if (!quadruple_mapping.count(result) > 0)
                {
                    // store in the map to preserve the quadruple and increment the counter
                    counter++;
                    quadruple_mapping[result] = "T" + to_string(counter);
                }

                quadruple_table_element = {{string{x}, operand2}, {operand1, quadruple_mapping[result]}};

                // pushing it to the vector
                quadruple_table_array.emplace_back(quadruple_table_element);

                // push the quadruple into the stack
                mystack.push(quadruple_mapping[result]);
            }
        }

        quadruple_table_element = {{"=", mystack.top()}, {"LHS", ""}};
        quadruple_table_array.emplace_back(quadruple_table_element);

        print_quadruple_table(quadruple_table_array);
    }

    // Method prints the quadruple table from the vector in the desired format
    void print_quadruple_table(vector<pair<pair<string, string>, pair<string, string>>> &quadruple_table_array)
    {
        cout << "Op \t arg1 \t arg2 \t result \n";

        // Traverse the quadruple array and print the elements in the desired format
        for (auto x : quadruple_table_array)
        {
            cout << x.first.first << "\t" << x.first.second << "\t" << x.second.first << "\t" << x.second.second << "\n";
        }
    }
};

// Driver Function
int main()
{
    // to store the input postfix expression
    string postfix_expression;
    // abc+d/*

    // Creating QuadrupleTableGenerator object for the input strings
    QuadrupleTableGenerator *quadrupletablegenerator = new QuadrupleTableGenerator;

    while (true)
    {
        cout << "Enter <exit> to terminate the program\n";
        cout << "Enter the postfix expression : ";
        cin >> postfix_expression;

        // execute loop till exit is entered by the user
        if (postfix_expression == "exit")
        {
            break;
        }

        // calling generatetable method for the given input
        quadrupletablegenerator->generate_table(postfix_expression);
    }

    // deleting the object after executing all the inputs
    delete quadrupletablegenerator;

    return 0;
}