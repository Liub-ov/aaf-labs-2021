#include <iostream>
#include <string>
#include <regex>

using namespace std;

string ParseIdentificators(string inputString, string ID)
{
    const regex CREATE(R"(([cC][rR][eE][aA][tT][eE]))");
    const regex CREATE_FULL(R"(([cC][rR][eE][aA][tT][eE])((\n)+|( +))(\n)*([a-zA-Z0-9_]+)(\n)* *(\n)*\(+(\n)* *(\n)*(([a-zA-Z0-9_])+ *((\n)* *)([iI][nN][dD][eE][xX][eE][dD])* *((\n)* *),+ *(\n)* *){0,}([a-zA-Z0-9_]+)(( *\n+ *| +)([iI][nN][dD][eE][xX][eE][dD]))*(\n)* *(\n)*\)+(\n)* *(\n)*;+)");
    const regex INSERT(R"(([iI][nN][sS][eE][rR][tT]))");
    const regex INSERT_FULL(R"(([iI][nN][sS][eE][rR][tT]) *((\n)+|( +))([iI][nN][tT][oO])*(\n)*( *)([a-zA-Z0-9_]+) *(\n)* *\(+(\n)* *(\n)*("+ *(\n)*( *)([a-zA-Z0-9_]+) *(\n)*( *)\"+ *(\n)*( *),+ *(\n)*( *)){0,}("+ *(\n)*( *)([a-zA-Z0-9_]+) *(\n)*( *)\"+ *(\n)*( *)\)+) *\n* *;)");
    const regex SELECT(R"(([sS][eE][lL][eE][cC][tT]))");
    const regex SELECT_FULL(R"(([sS][eE][lL][eE][cC][tT]) *(((\n)+ *)|( +))(\*|([a-zA-Z0-9]+ *(((\n)+ *)|( *)), *(((\n)+ *)|( *))){0,}([a-zA-Z0-9]+)) *(((\n)+ *)|( *))(([fF][rR][oO][mM])) *(((\n)+ *)|( +))([a-zA-Z0-9]+) *(((\n)+ *)|( *))(;|([wW][hH][eE][rR][eE])(((\n)+ *)|( +))([a-zA-Z0-9]+)(((\n)+ *)|( *))((=+|!=+|>+|<+|>=+|<=+)(((\n)+ *)|( *)))\"+ *(((\n)+ *)|( *))[a-zA-Z0-9]+ *(((\n)+ *)|( *))\"+ *(((\n)+ *)|( *));|([lL][eE][fF][tT]_[jJ][oO][iI][nN]) *(((\n)+ *)|( +))([a-zA-Z0-9]+ *(((\n)+ *)|( +))([oO][nN])(((\n)+ *)|( +))([a-zA-Z0-9])+ *(((\n)+ *)|( +))(=+|!=+|>+|<+|>=+|<=+)(((\n)+ *)|( +))+ *\n*([a-zA-Z0-9])+ *((\n)* *))+ *\n*;+))");
    const regex DELETE(R"(([dD][eE][lL][eE][tT][eE]))");
    const regex DELETE_FULL(R"(([dD][eE][lL][eE][tT][eE]) *(((\n)+ *)|( +))(((([fF][rR][oO][mM])* *(((\n)+ *)|( +))[a-zA-Z0-9]+ *(((\n)+ *)|( *))))|[a-zA-Z0-9]+ *(((\n)+ *)|( *))(([wW][hH][eE][rR][eE]) *(((\n)+ *)|( +))[a-zA-Z0-9]+ *(((\n)+ *)|( *))(=|!=|>|<|>=|<=) *(((\n)+ *)|( *))\" *(((\n)+ *)|( *))[a-zA-Z0-9]+ *(((\n)+ *)|( *))\" *(((\n)+ *)|( *))){0,1});)");
    smatch tested, return_value;
    if (regex_search(ID, tested, CREATE))
    {
        cout << "create" << endl;
        if (regex_search(inputString, return_value, CREATE_FULL)) {
            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
        }
    }
    if (regex_search(ID, tested, INSERT))
    {

        cout << "insert" << endl;

        if (regex_search(inputString, return_value, INSERT_FULL)) {
            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
        }
    }
    if (regex_search(ID, tested, SELECT))
    {

        cout << "select" << endl;

        if (regex_search(inputString, return_value, SELECT_FULL)) {
            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
        }
    }
    if (regex_search(ID, tested, DELETE))
    {
        cout << "delete" << endl;

        if (regex_search(inputString, return_value, DELETE_FULL)) {
            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
        }
    }


    throw std::invalid_argument("_");
}


int main()
{
    string s;
    while (s != "exit") {
        s.clear();
        cout << "Enter command: " << flush;
        getline(cin, s, ';');
        if (s.find(';')) s += ';';
        char temp[1024]{};
        string line;
        strcpy(temp, s.c_str());
        line = strtok(temp, " ,.");

        try
        {
            s = ParseIdentificators(s, line);
        }
        catch (const exception&)
        {
            cout << "Identificator '" + s + "' is not correct" << endl;
            continue;
        }
        cout << "Succesfully completed" << endl;
    }
}
