/*
Experiment 5: Program to remove left recursion for the given grammar. 

Name: Jiten Sidhpura
Roll No: 57
UID: 2018130051
Batch: D

e ==> denotes epsilon
Starting Production is at the end =>

Input Format:

S
3
B>Sc/a
A>SB/b
S>A/B
*/

#include<bits/stdc++.h>
using namespace std;

// global variables to store data about variables,productions and start symbols
int no_of_productions;
string start_symbol;
unordered_map<string, string> production_rules;
unordered_set<string> terminals;
vector<string> order_of_non_terminals;
vector<string> order_of_productions;

// Prints the Grammar in the Desired Format
void print_grammar(string type){

    cout<<endl;
    cout<<endl;
    cout<<"\t\t"<<type<<" Grammar (V,T,P,S)\n\n";
    cout<<"V ==> {";

    for(auto x : production_rules){
        cout<<x.first<<", ";
    }
    cout<<"}";
    cout<<endl;

    cout<<"T ==> {";
    for(auto x : terminals){
        cout<<x<<" ,";
    }
    cout<<"}";
    cout<<endl;

    cout<<"P: \n";
    for(auto x : production_rules){
        cout<<x.first<<"\t==>\t"<<x.second<<endl;
    }

    cout<<"Start Symbol  ==> {"<<start_symbol<<"}\n";
    cout<<endl;
    cout<<endl;
}

// Function which stores all the terminals from the input grammar
void store_terminals(){
    for(auto x : production_rules){
        auto rhs_side = x.second;

        for(auto y : rhs_side){
            if(islower(y)){
                terminals.insert(string{y});
            }
        }
    }
}

// Function which solves direct recursion
void solve_direct_recursion(string key){
    int prev_separator_position = -1,beta_flag = 0;

    string rhs_side = production_rules[key];
    vector<string> beta;

    int size = rhs_side.size();

    string new_production_key = string{key} + "'";
    string temp = "";

    string modified_production = "",new_production = "";

    for(int i=0;i<rhs_side.size();i++){

        if(i == 1 + prev_separator_position){
            if(key != string{rhs_side[i]}){
                temp += rhs_side[i];
                beta_flag = 1;
            }
            else{
                beta_flag = 2;
            }
        }

        else if(rhs_side[i] == '/'){
            prev_separator_position = i;
            if(beta_flag == 1){
                temp.append(new_production_key);
                modified_production.append(temp);
                modified_production.append("/");
                temp.clear();
            }

            else if(beta_flag == 2){
                new_production.append(new_production_key);
                new_production.append("/");
            }

            beta_flag = 0;
        }

        else if(beta_flag == 1){
            temp += rhs_side[i];
        }

        else if(beta_flag == 2){
            new_production += rhs_side[i];
        }

    }

    if(beta_flag == 1){
        temp.append(new_production_key);
        modified_production.append(temp);
        modified_production.append("/");
        temp.clear();
    }

    else if(beta_flag == 2){
        new_production.append("/");
    }

    production_rules[key] = modified_production;
    production_rules[new_production_key] = new_production.append("e");

}

// Function which checks for direct recursion in a rule
void check_for_direct_recursion(string key){
    int prev = -1;
    int flag = 0;

    string rhs_side = production_rules[key];

    for(int i=0;i<rhs_side.size();i++){
        if(prev == -1 and key == string{rhs_side[i]}){
            // cout<<"Direct Recursion is detected\n";
            prev = 0;
            flag = 1;
        }

        else if(rhs_side[i] == '/'){
            prev = -1;
        }

        else{
            prev = 0;
        }
    }

    // if present then solve it 
    if(flag){
        solve_direct_recursion(key);
    }

}

// Returns index of the non terminal from the ordered vector
int getIndex(string non_terminal){
    for(int i=0;i<order_of_non_terminals.size();i++){
        if(order_of_non_terminals[i] == non_terminal) return i; 
    }

    return -1;
}

// Function to merge one rule with another rule
string merge(string buffer, string rule){
    string result = "";
    
    string temp = "";

    for(auto x : rule){
        
        if(x == '/'){
            result.append(buffer);
            result.append(temp);
            result.append("/");
            temp.clear();
        }

        else{
            temp += x;
        }
    }

    result.append(buffer);
    result.append(temp);
    temp.clear();

    return result;
}

// Function which converts indirect to direct recursion
void solve(){
    if(order_of_productions.size() == 1){
        check_for_direct_recursion(production_rules.begin()->first);
    }
    else{
        for(int i=1;i<no_of_productions;i++){
            auto rhs_rule = order_of_productions[i];
            rhs_rule += "/";

            string modified_rule = "",buffer = "";

            int flag = 0;

            for(auto y : rhs_rule){

                if(y == '/'){
                    if(flag == 0){
                        modified_rule += buffer;
                    }

                    flag = 0;
                    buffer.clear();
                }

                if(isupper(y) and getIndex(string{y}) < i){
                    flag = 1;
                    modified_rule += merge(buffer,production_rules[string{y}]);
                    continue;
                }

                buffer += y;
            }

            production_rules[order_of_non_terminals[i]] = modified_rule;
        }
    }

    check_for_direct_recursion(start_symbol); 
}


// Driver Function which reads the data from file or via terminal
int main(int argc, char** argv){

    //When filename is passed in the commandline input
    if(argc > 1){

        ifstream input_file;

        string line,key;

        input_file.open(argv[1]);

        getline(input_file,line);
        start_symbol = line;

        getline(input_file,line);
        no_of_productions = stoi(line);

        for(int i=0;i<no_of_productions;i++){
            
            getline(input_file,line);
            key = line[0];
            order_of_non_terminals.emplace_back(string{key});
            order_of_productions.emplace_back(line.substr(2));
            production_rules[key] = line.substr(2);

        }

        input_file.close();
    }


    //When filename is not passed as a commandline Input so input is received from the input
    else{   
        string line,key;

        cout<<"Enter the number of productions\n";
        cin>>no_of_productions;

        cout<<"Enter the Start Symbol\n";
        cin>>start_symbol;

        cout<<"Enter the Production Rules\n";

        for(int i=0;i<no_of_productions;i++){
     
            cin>>line;
            key = line[0];
            order_of_non_terminals.emplace_back(string{key});
            order_of_productions.emplace_back(line.substr(2));
            production_rules[key] = line.substr(2);

        }

    }

    store_terminals();
    print_grammar("Input");
    solve();
    print_grammar("Final");

    return 0;   
}