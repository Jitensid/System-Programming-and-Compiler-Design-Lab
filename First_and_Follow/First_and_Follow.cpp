/*
Name Jiten Sidhpura
UID 2018130051
Roll No 57
Batch D
TE COMPS

Aim : Program to find first and follow sets for the given grammar {V,T,P,S}.

Non Terminals --> {A,B,C,S}
Terminals --> {a,b,c,d,e,f}
Start Symbol --> S
Productions --> {
        S ->ABC,
        A ->a|b|#,
        B ->c|d|#,
        C ->e|f|#,
    }

It is assumed that # denotes empty symbol / epsilon
*/

#include <bits/stdc++.h>
#define debug(x) cout << #x << endl;
#define print_array(data)  \
    cout << #data << endl; \
    for (auto x : data)    \
    {                      \
        cout << x << " ";  \
    }                      \
    cout << endl;
#define print_map(data)                             \
    cout << #data << endl;                          \
    for (auto x : data)                             \
    {                                               \
        cout << x.first << " " << x.second << endl; \
    }                                               \
    cout << endl;
using namespace std;

// class to find find and follow of the given grammar
class FirstFollowFinder
{

private:
    // private data structures to store the grammar
    unordered_set<string> terminals, non_terminals;
    map<string, string> productions;
    string start_symbol;
    map<string, vector<string>> first, follow;

    // Method which finds first of productions where all are terminals
    void find_first_of_productions_directly()
    {

        // Iterate all productions and find the first if possible
        for (auto prods : productions)
        {

            // Stores the first values in the vector
            vector<string> first_values;

            // Get lhs of the production
            auto lhs = prods.first;

            // Get rhs of the production
            auto rhs = prods.second;

            int first_flag = 0;

            // flag which denotes whether we can store the first of the production
            // 0 means valid so store
            // -1 means invalid so don't store
            int validity = 0;

            // Iterate the rhs of the production
            for (auto x : rhs)
            {
                // We need to find first of this character
                if (first_flag == 0)
                {

                    // This is a terminal so simply add it into the vector
                    if (this->terminals.count(string{x}) > 0 or x == '#')
                    {
                        first_values.push_back(string{x});
                    }

                    // if non terminal
                    else if (this->non_terminals.count(string{x}) > 0)
                    {
                        validity = -1;
                        break;
                    }

                    // Change the flag value
                    first_flag = 1;
                }

                else
                {
                    // If found pipe character again then state first_flag to 0
                    if (x == '|')
                    {
                        first_flag = 0;
                    }
                }
            }

            // Storing in the map
            if (validity == 0)
            {
                this->first[lhs] = first_values;
            }
        }
    }

    // returns only unique elements in vector
    void unique_elements_vector(vector<string> &vec)
    {
        set<string> myset(vec.begin(), vec.end());

        vec.clear();

        for (auto x : myset)
        {
            vec.push_back(x);
        }
    }

    // Method to find first of remaining productions
    void find_first_of_remaining_productions()
    {
        for (auto x : this->productions)
        {

            // if found then skip
            if (this->first.count(x.first) > 0)
            {
                continue;
            }

            this->first[x.first] = this->handle_first_recursively(x.first);
        }
    }

    // recursively find remaining productions
    vector<string> handle_first_recursively(string lhs)
    {

        // Store the result
        vector<string> result;

        // If present then return from the data structure
        if (this->first.count(lhs) > 0)
        {
            result.insert(result.end(), this->first[lhs].begin(), this->first[lhs].end());
            return result;
        }

        string rhs = this->productions[lhs];

        // first_flag to whether read charcater or not
        // index to parse the string
        int first_flag = 0, index = 0;

        for (auto y : rhs)
        {

            if (first_flag == 0)
            {

                if (this->terminals.count(string{y}) > 0 or y == '#')
                {
                    result.push_back(string{y});
                    first_flag = 1;
                }

                else
                {
                    vector<string> temp = this->handle_first_recursively(string{y});
                    result.insert(result.end(), temp.begin(), temp.end());

                    // if epsilon then check for next character as well
                    if (find(result.begin(), result.end(), "#") != result.end())
                    {
                        if (index < rhs.size() - 1)
                        {
                            result.erase(remove(result.begin(), result.end(), "#"), result.end());
                        }
                    }

                    else
                    {
                        first_flag = 1;
                    }
                }
            }

            else
            {

                if (y == '|')
                {
                    first_flag = 0;
                }
            }

            index++;
        }

        // remove duplicates if present
        this->unique_elements_vector(result);

        return result;
    }

    // Print First of the given grammar
    void print_first_map()
    {
        cout << "First for the given grammar is as follows" << endl;

        for (auto x : this->first)
        {
            cout << x.first << endl;

            for (auto y : x.second)
            {
                cout << y << " ";
            }

            cout << endl;
            cout << endl;
        }
    }

    // Print Follow of the given grammar
    void print_follow_map()
    {
        cout << "Follow for the given grammar is as follows" << endl;

        for (auto x : this->follow)
        {
            cout << x.first << endl;

            for (auto y : x.second)
            {
                cout << y << " ";
            }

            cout << endl;
            cout << endl;
        }
    }

    // Method to find follow of the productions
    void find_follow_of_productions()
    {
        // Iterate through all the non terminals
        for (auto &prods : this->productions)
        {
            // if found then skip
            if (this->follow.count(prods.first) > 0)
            {
                continue;
            }

            // store it in the map
            this->follow[prods.first] = this->handle_follow_recursively(prods.first);
        }
    }

    // Method to find follow recursively 
    vector<string> handle_follow_recursively(string non_terminal)
    {

        // if found then just return
        if (this->follow.count(non_terminal) > 0)
        {
            return this->follow[non_terminal];
        }

        vector<string> result;

        // follow for start symbol is $
        if (non_terminal == this->start_symbol)
        {
            result.push_back("$");
        }

        // Iterate through all the productions
        for (auto &prod : this->productions)
        {

            // fetch lhs and rhs of the production
            auto lhs_of_production = prod.first;
            auto rhs_of_production = prod.second;

            // Iterate through rhs of the production
            for (int i = 0; i < rhs_of_production.size(); i++)
            {
                // if non terminal is present in the production
                if (string{rhs_of_production[i]} == non_terminal)
                {
                    // if next elements exists
                    if (i + 1 < rhs_of_production.size())
                    {
                        // if terminal then simply add it to the vector
                        if (this->terminals.count(string{rhs_of_production[i + 1]}) > 0)
                        {
                            result.push_back(string{rhs_of_production[i + 1]});
                        }

                        // if non terminal then find it's first and then add it to the vector
                        else if (this->non_terminals.count(string{rhs_of_production[i + 1]}))
                        {
                            vector<string> temp = this->first[string{rhs_of_production[i + 1]}];
                            result.insert(result.end(), temp.begin(), temp.end());

                            // if epsilon in first of the non terminal
                            if (find(result.begin(), result.end(), "#") != result.end())
                            {
                                // make this character same as non terminal so that next character can be computed as well
                                rhs_of_production[i + 1] = non_terminal[0];
                            }
                        }

                        // then find follow of the lhs of the production and add it to the vector
                        else if (rhs_of_production[i] == '|')
                        {
                            vector<string> temp;

                            // then find follow of the lhs of the production
                            temp = this->handle_follow_recursively(lhs_of_production);

                            // insert the follow of the lhs into the vector
                            result.insert(result.end(), temp.begin(), temp.end());
                        }
                    }

                    else
                    {

                        vector<string> temp;

                        // then find follow of the lhs of the production
                        temp = this->handle_follow_recursively(lhs_of_production);

                        // insert the follow of the lhs into the vector
                        result.insert(result.end(), temp.begin(), temp.end());
                    }
                }
            }
        }

        // remove duplicates if present
        this->unique_elements_vector(result);

        // follow does not have epsilon so remove it
        result.erase(remove(result.begin(), result.end(), "#"), result.end());

        return result;
    }

public:
    // constructor which sets all the private data structures
    FirstFollowFinder(unordered_set<string> &terminals, unordered_set<string> &non_terminals, map<string, string> &productions, string &start_symbol)
    {
        this->terminals = terminals;
        this->non_terminals = non_terminals;
        this->productions = productions;
        this->start_symbol = start_symbol;
    }

    // Prints the data structures
    void print_datastructures()
    {
        // print terminals
        print_array(this->terminals);

        // print non terminals
        print_array(this->non_terminals);

        // print productions
        print_map(this->productions);

        // print start symbol
        cout << this->start_symbol << endl;
    }

    // Main method to find first and follow
    void find_first_and_follow()
    {
        // Compute first of direct productions
        this->find_first_of_productions_directly();

        // Compute first of remaning productions
        this->find_first_of_remaining_productions();

        // Display first of all the productions
        this->print_first_map();

        // Compute folloe of all the productions
        this->find_follow_of_productions();

        // Display follow of all the productions
        this->print_follow_map();
    }
};

// helper function to read Grammar from a file
void read_grammar_from_file(unordered_set<string> &terminals, unordered_set<string> &non_terminals, map<string, string> &productions, string &start_symbol, string &filename)
{
    string line;

    int count = 0, total_lines = 0;

    // ifstream of the file
    ifstream myfile, file;
    myfile.open(filename);

    // handle error while opening the file
    if (!myfile.is_open())
    {
        cout << "Error while reading file\n";
        return;
    }

    // Getting number of lines in the file
    while (getline(myfile, line))
    {
        total_lines += 1;
    }

    file.open(filename);

    // handle error while opening the file
    if (!file.is_open())
    {
        cout << "Error while reading file\n";
        return;
    }

    // Reading the file line by line
    while (getline(file, line))
    {
        // Reading and storing non terminals in the set
        if (count == 0)
        {
            auto temp = line.substr(4);

            // Remove { and } from the string
            temp.erase(remove(temp.begin(), temp.end(), '{'), temp.end());
            temp.erase(remove(temp.begin(), temp.end(), '}'), temp.end());

            for (auto x : temp)
            {
                if (x != ',')
                {
                    non_terminals.insert(string{x});
                }
            }
        }

        // Reading and storing terminals in the set
        else if (count == 1)
        {
            auto temp = line.substr(4);

            // Removing { and } from the string
            temp.erase(remove(temp.begin(), temp.end(), '{'), temp.end());
            temp.erase(remove(temp.begin(), temp.end(), '}'), temp.end());

            for (auto x : temp)
            {
                if (x != ',')
                {
                    terminals.insert(string{x});
                }
            }
        }

        // Reading and storing productions in the map
        else if (count >= 4 and count < total_lines - 1)
        {
            int i = 0;
            string lhs = "";

            for (i = 0; i < line.size(); i++)
            {
                // store the lhs of the production
                if (line[i] != '>')
                {
                    lhs += line[i];
                    break;
                }
            }

            // store the start symbol
            if (count == 4)
            {
                start_symbol = lhs;
            }

            productions[lhs] = line.substr(i + 2);
        }

        count += 1;
    }
}

int main(int argc, char **argv)
{
    // Variables and Data Structures to read the grammar from the text file
    unordered_set<string> terminals, non_terminals;
    map<string, string> productions;
    string start_symbol;

    // if filename not specified via command line then inform and return
    if (argc <= 1)
    {
        cout << "Enter filename\n";
        return 0;
    }

    // fetch the filename from the command line
    string filename = argv[1];

    // Read the grammar from the text file and store all terminals, non_terminals and productions from the grammar
    read_grammar_from_file(terminals, non_terminals, productions, start_symbol, filename);

    // create the firstfollowfinder object and pass the data stored into the data structures
    FirstFollowFinder *firstfollowfinder = new FirstFollowFinder(terminals, non_terminals, productions, start_symbol);

    // find first and follow
    firstfollowfinder->find_first_and_follow();

    return 0;
}