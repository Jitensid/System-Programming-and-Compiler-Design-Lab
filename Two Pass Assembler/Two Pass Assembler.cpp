/*
Name: Jiten Sidhpura
Class: TE COMPS
Batch: D
UID: 2018140051
Roll No. 57
Experiment No. 1  -To implement two pass assembler.
*/

#include <bits/stdc++.h>
using namespace std;

// class to implement 2 pass assembler
class TwoPassAssembler
{

    // private variables and datastructure for 2 pass assembler
private:
    string input_filename, intermediate_filename;
    map<string, string> op_table;
    map<string, int> symbol_table;
    int location_counter = 0;
    int starting_address = 0;
    string headerrecord, endrecord, textrecord;

    // initializes the optable because it is static
    void initialize_op_table()
    {
        // values are taken from ppt
        this->op_table["START"] = "START";
        this->op_table["LDA"] = "00";
        this->op_table["STA"] = "0C";
        this->op_table["LDCH"] = "50";
        this->op_table["STCH"] = "54";
        this->op_table["LDX"] = "04";
        this->op_table["TIX"] = "2C";
        this->op_table["JLT"] = "38";
        this->op_table["END"] = "END";
    }

public:
    // constructor accepts the input filename and sets it and intermediate filename
    TwoPassAssembler(string &input_filename)
    {
        this->input_filename = input_filename;
        this->intermediate_filename = "intermediate.txt";
        initialize_op_table();
    }

    // method prints the symbol table
    void print_symbol_table()
    {
        cout << endl;
        cout << "Contents of the Symbol Table are as follows" << endl;

        // iterate through map data structure and print key value pair
        for (auto &x : this->symbol_table)
        {
            cout << x.first << " " << x.second << endl;
        }

        cout << endl
             << endl;
    }

    // method prints the op table
    void print_op_table()
    {
        cout << endl;
        cout << "Contents of the Operation Table are as follows" << endl;

        // iterate through map data structure and print key value pair
        for (auto &x : this->op_table)
        {
            cout << x.first << " " << x.second << endl;
        }

        cout << endl
             << endl;
    }

    // converts the input number as string to size 6 hexadecimal number
    string string_to_hexa(string &input)
    {
        int size = input.size();

        string result = "";

        // iterate and append 0 to result
        for (int i = 0; i < 6 - size; i++)
        {
            result += '0';
        }

        // append input to result
        result.append(input);

        return result;
    }

    // method to print the final object code
    void print_object_code()
    {
        cout << endl
             << endl;

        cout << "The Object Code is as follow " << endl;

        // print the headerrecord in the desired format
        cout << this->headerrecord << endl;

        // print the textrecord in the desired format
        cout << this->textrecord << endl;

        // print the endrecord in the desired format
        cout << this->endrecord << endl;

        cout << endl
             << endl;
    }

    // Method to implement pass 1
    void pass1()
    {
        // ifstream object to read the given file
        ifstream filereader;

        // ofstream object to read the given file
        ofstream filewriter;

        string label, opcode, operand, mneumonic;

        // open the input file for reading and intermediate file in the write mode
        filereader.open(this->input_filename);
        filewriter.open(this->intermediate_filename);

        cout << "Intermediate Code Generated after Pass 1" << endl
             << endl;

        // cols of the input file
        cout << "LOCCTR\t"
             << "Label\t"
             << "Mnemonic "
             << "Operand" << endl
             << endl;

        // read until input file ends
        while (filereader >> label >> mneumonic >> operand)
        {
            // stringstream object is used to convert the given integer to hexadecimal value
            stringstream ss;

            string res;

            // for mneumonic "START"
            if (mneumonic == "START")
            {
                // convert int to hexadecimal
                ss << hex << operand;
                ss >> this->starting_address;

                // print if label is present or execute the else condition
                if (label == "**")
                {
                    this->location_counter = this->starting_address;
                    cout << hex << this->location_counter << "\t"
                         << "\t" << mneumonic << "\t" << operand << endl;
                }

                else
                {
                    this->location_counter = this->starting_address;

                    cout << hex << this->location_counter << "\t" << label
                         << "\t" << mneumonic << "\t" << operand << endl;
                }

                // write to the intermediate file
                filewriter << hex << location_counter << " " << label << " " << mneumonic << " " << operand << "\n";
            }

            // for mneumonic "END"
            else if (mneumonic == "END")
            {
                // print if label is present or execute the else condition
                if (label == "**")
                {
                    cout << (this->location_counter - this->starting_address) << "\t\t"
                         << "END\n";
                }

                else
                {
                    cout << (this->location_counter - this->starting_address) << "\t" << label
                         << "END\n";
                }

                // write to the intermediate file
                filewriter << (this->location_counter - this->starting_address) << " " << label << " " << mneumonic << " " << operand;
            }

            else
            {
                filewriter << hex << this->location_counter << " " << label << " " << mneumonic << " " << operand << "\n";

                // print if label is present or execute the else condition
                if (label != "**")
                {
                    cout << hex << this->location_counter << "\t" << label << "\t" << mneumonic << "\t" << operand << endl;
                }

                else
                {
                    cout << hex << this->location_counter << "\t"
                         << "\t" << mneumonic << "\t" << operand << endl;
                }

                if (label != "**")
                {
                    // label already exists in the symbol table then throw runtime error
                    if (this->symbol_table.count(label) > 0)
                    {
                        throw std::runtime_error("Symbol Already exists in the symbol table");
                    }

                    // else store the location_counter value into the symbol table
                    else
                    {
                        this->symbol_table[label] = (this->location_counter);
                    }
                }

                // if mneumonic present in the table
                if (this->op_table.count(mneumonic) > 0)
                {
                    this->location_counter += 3;
                }

                // if mneumonic is WORD incerement by 3
                else if (mneumonic == "WORD")
                {
                    this->location_counter += 3;
                }

                // if mneumonic is RESW then 3 times value of the operand
                else if (mneumonic == "RESW")
                {
                    this->location_counter += 3 * stoi(operand);
                }

                // if mneumonic is RESB incerement by the length of the operand
                else if (mneumonic == "RESB")
                {
                    this->location_counter += stoi(operand);
                }

                // if mneumonic is BYTE then incerement by size of the data
                else if (mneumonic == "BYTE")
                {
                    this->location_counter += operand.length() - 3;
                }

                // throw runtime error in other case
                else
                {
                    throw std::runtime_error("Invalid mneumonic found in the program");
                }
            }
        }

        // print both the tables
        // print symbol table
        this->print_symbol_table();

        // print operator table
        this->print_op_table();
    }

    void pass2()
    {
        // ifstream object to read the given file
        ifstream filereader;

        // cols of the interemediate file
        string label, mneumonic, operand, address, opcode;

        // read the intermediate file
        filereader.open(this->intermediate_filename);

        cout << "LOCCTR\t"
             << "Label\t"
             << "Mnemonic "
             << "Operand "
             << "Object Code"
             << endl
             << endl;

        // read the intermediate file until it ends
        while (filereader >> address >> label >> mneumonic >> operand)
        {
            string res;

            // stringstream object is used to convert the given integer to hexadecimal value
            stringstream hexstr;

            // for mneumonic "START"
            if (mneumonic == "START")
            {

                // print if label is present or execute the else condition
                if (label == "**")
                {
                    cout << hex << this->starting_address << "\t"
                         << "\t" << mneumonic << "\t" << operand << endl;
                }

                else
                {

                    cout << hex << this->starting_address << "\t" << label
                         << "\t" << mneumonic << "\t" << operand << endl;
                }

                //append to the header record
                this->headerrecord += 'H';
                this->headerrecord += ' ';
                this->headerrecord.append(label);
                this->headerrecord += ' ';
                this->headerrecord.append(this->string_to_hexa(address));
                this->headerrecord += ' ';

                //append to the text record
                this->textrecord += 'T';
                this->textrecord += ' ';

                // append to the end record
                this->endrecord += 'E';
                this->endrecord += ' ';
                this->endrecord.append(this->string_to_hexa(address));
            }

            // for mneumonic "START"
            else if (mneumonic == "END")
            {

                // if label not there print in th given format
                if (label == "**")
                {
                    cout << address << "\t\t"
                         << mneumonic << endl;
                }

                // print in different format if label is there
                else
                {
                    cout << address << "\t" << label
                         << "END\n";
                }

                // append to the header record
                this->headerrecord.append(this->string_to_hexa(address));
            }

            else
            {
                // print if label is present or execute the else condition
                if (label != "**")
                {
                    cout << address << "\t" << label << "\t" << mneumonic << "\t" << operand << "\t";
                }

                else
                {
                    cout << address << "\t"
                         << "\t" << mneumonic << "\t" << operand << "\t";
                }

                string hexa;

                // for mneumonic "BYTE"
                if (mneumonic == "BYTE")
                {
                    string constant = "";
                    int flag = 0;

                    // get the constant part of the operand
                    for (auto &x : operand)
                    {
                        // append if flag == 1
                        if (flag == 1)
                        {
                            constant += x;
                        }

                        else
                        {
                            // change flag if the below character is found
                            if (x == '\'')
                            {
                                flag ^= 1;
                            }
                        }
                    }

                    // pop the unnecessary character
                    constant.pop_back();

                    // iterate over the string and then convert every character to hexadecimal
                    for (auto &x : constant)
                    {
                        cout << hex << (int)x;
                        hexstr << hex << (int)x;
                    }

                    // append to the text record
                    this->textrecord.append(hexstr.str());
                    this->textrecord += ' ';
                }

                // for "word" opocode just convert the string to hexadecimal
                else if (mneumonic == "WORD")
                {
                    int size = operand.length();

                    // gets the hexavalue
                    string hexavalue = this->string_to_hexa(operand);

                    cout << hexavalue;

                    // append to the text record
                    this->textrecord.append(hexavalue);
                    this->textrecord += ' ';
                }

                else
                {
                    // If in symbol table then print hexaddress and in the text record
                    if (this->symbol_table.count(operand) > 0)
                    {
                        cout << this->op_table[mneumonic] << this->symbol_table[operand];

                        hexstr << hex << this->symbol_table[operand];

                        // append to the textrecord
                        this->textrecord.append(this->op_table[mneumonic].append(hexstr.str()));
                        this->textrecord += ' ';
                    }
                }

                cout << endl;
            }
        }

        // finally print the object code in the desired format
        this->print_object_code();
    }
};

// Driver Function
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        throw std::invalid_argument("Enter filename");
    }
    // input filename
    string input_filename = argv[1];

    // twopassassembler object to perform both the pass1 and pass2
    TwoPassAssembler *twopassassembler = new TwoPassAssembler(input_filename);

    // call pass1 method
    twopassassembler->pass1();

    // call pass2 method
    twopassassembler->pass2();

    // delete the object from the heap
    delete twopassassembler;

    return 0;
}