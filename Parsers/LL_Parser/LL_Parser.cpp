/*
Name Jiten Sidhpura
UID 2018130051
Roll No 57
Batch D
TE COMPS

Program for LL(1) Parser
*/

// $ is assumed to be empty symbol of the stack and follow of the start symbol

class Parser{
    
    // Object Variables
    map< pair<string,string>, string > parsing_table;
    unordered_set<string> terminals,non_terminals;
    string start_symbol,buffer;

    public:

        Parser(){
            cout<<"Default Constructor\n";
        }

        // Constructor which sets all the data structure and the variables
        Parser(string &start_symbol,string &input_string, map< pair<string,string>, 
        string > &input_parsing_table, unordered_set<string> &terminals,unordered_set<string> &non_terminals){
            this->parsing_table = input_parsing_table;
            this->start_symbol = start_symbol;
            this->buffer = input_string;
            this->terminals = terminals;
            this->non_terminals = non_terminals;
        }

        // Method which finds whether given string is part of grammar or not
        bool parse_string(){
            // Initializing the given stack
            stack<string> mystack;
            mystack.push("$");
            mystack.push(this->start_symbol);

            // index for the given buffer
            int index = 0;

            string temp = "",stack_top;

            // Iterate until buffer ends
            while(index < this->buffer.size()){
                
                print_stack_and_buffer(mystack, temp);
                
                if(mystack.top() == temp){
                    mystack.pop();
                    index++;
                    print_stack_and_buffer(mystack, temp);
                    temp.clear();
                }

                temp += buffer[index];

                if(this->terminals.count(temp) > 0){
                    
                    if(this->non_terminals.count(mystack.top()) > 0){
                        
                        if(this->parsing_table.count(make_pair(mystack.top(),temp)) > 0){
                            modify_the_stack(mystack,this->parsing_table[make_pair(mystack.top(),temp)]);
                            mystack.pop();
                            print_stack_and_buffer(mystack, temp);
                            temp.clear();
                            index++;
                        }

                        else{
                            return false;
                        }
                    
                    }

                    else{
                        if(mystack.top() == temp){
                            mystack.pop();
                            print_stack_and_buffer(mystack, temp);
                            temp.clear();
                            index++;
                        }

                        else{
                            return false;
                        }
                    }
                }

                else{
                    index++;
                }

            }

            if(mystack.top() == temp){
                mystack.pop();
            }

            // debug(index);
            // debug(mystack.top());

            if(mystack.top() != "$" or index < this->buffer.size()) return false;

            return true;
        }

        // Function to print the parsing table
        void print_parsing_table(){
            for(auto x : this->parsing_table){
                cout<<x.first.first<<"\t"<<x.first.second<<"\t"<<x.second<<endl;
            }
        }

        // Function to add the rhs of the production into the stack
        void modify_the_stack(stack<string> &mystack, string rhs){
           
            string temp = "";
            vector<string> elements;

            mystack.pop();

            for(auto x : rhs){
                temp += x;

                if(this->terminals.count(temp) > 0){
                    elements.emplace_back(temp);
                    temp.clear();
                }

                else if(this->non_terminals.count(temp) > 0){
                    elements.emplace_back(temp);
                    temp.clear();
                }

            }

            if(this->terminals.count(temp) > 0){
                elements.emplace_back(temp);
                temp.clear();
            }

            if(this->non_terminals.count(temp) > 0){
                elements.emplace_back(temp);
                temp.clear();
            }

            reverse(elements.begin(),elements.end());
            // print_array(elements);

            // Pushing all elements of production in the reverse order
            for(auto x : elements){
                mystack.push(x);
            }

        }   

        // Prints the current status of the stack and the buffer
        void print_stack_and_buffer(stack<string> mystack, string temp){
            cout<<"Stack is \t : ";

            while(!mystack.empty()){
                cout<<mystack.top();
                cout<<" ";
                mystack.pop();
            }

            cout<<"Buffer is \t : ";
            cout<<temp<<endl;

        }

};

int main(){

    // Variable to read the input 
    string input_string,temp;

    int number_of_terminals,number_of_non_terminals, number_of_productions,entries;
    unordered_set<string> terminals,non_terminals;
    map<string,string> productions;
    map< pair<string,string>, string > parsing_table;

    string start_symbol;

    cout<<"Enter the Number of Terminals \n";
    cin>>number_of_terminals;

    for(int i=0;i<number_of_terminals;i++){
        cout<<"Enter terminal symbol "<<i<<" : ";
        cin>>temp;
        terminals.insert(temp);
    }

    cout<<"Enter the Number of Non-Terminals \n";
    cin>>number_of_non_terminals;

    for(int i=0;i<number_of_non_terminals;i++){
        cout<<"Enter non terminal symbol "<<i<<" : ";
        cin>>temp;
        non_terminals.insert(temp);
    }

    cout<<"Enter start symbol\n";
    cin>>start_symbol;

    cout<<"Enter Number of Productions \n";
    cin>>number_of_productions;

    for(int i=0;i<number_of_productions;i++){
        cout<<"Enter Production "<<i<<" : ";
        cin>>temp;
        productions[string{temp[0]}] = temp.substr(2);
    }
    
    cout<<"Enter no of entries of Parsing Table\n";
    cin>>entries;
    
    for(int i=0;i<entries;i++){
        string a,b,c;
        cout<<"Enter Production, Terminal, Production : ";
        cin>>a>>b>>c;
        parsing_table[{a,b}] = c;
    }

    cout<<"Enter a string to parse\n";
    cin>>input_string;

    // Creating object of the parser to parse the string
    Parser *myparser = new Parser(start_symbol,input_string,parsing_table,terminals,non_terminals);
    if(myparser->parse_string()){
        cout<<"Accepted\n";
    }

    else{
        cout<<"Error while parsing the given string\n";
    }

    myparser->print_parsing_table();

    delete myparser;

    return 0;
}