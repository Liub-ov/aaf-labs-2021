#include <iostream>
#include <string>
#include <regex>

using namespace std;

string ParseIdentificators(string inputString, string ID)
{
    const regex CREATE(R"(([cC][rR][eE][aA][tT][eE]))");
    const regex CREATE_FULL(R"(([cC][rR][eE][aA][tT][eE])((\n)+|( +))(\n)*([a-zA-Z0-9_]+)(\n)* *(\n)*\(+(\n)* *(\n)*(([a-zA-Z0-9_])+ *((\n)* *)([iI][nN][dD][eE][xX][eE][dD])* *((\n)* *),+ *(\n)* *){0,}([a-zA-Z0-9_]+)(( *\n+ *| +)([iI][nN][dD][eE][xX][eE][dD]))*(\n)* *(\n)*\)+(\n)* *(\n)*;+)");
    const regex INSERT(R"(([iI][nN][sS][eE][rR][tT]))");
    const regex INSERT_FULL(R"(([iI][nN][sS][eE][rR][tT]) *((\n)+|( +))(\n)*( *)([a-zA-Z0-9_]+) *(\n)* *\(+(\n)* *(\n)*(\"+([^\"]+) *(\n)*( *)\"+ *(\n)*( *),+ *(\n)*( *)){0,}\"+([^\"]+) *(\n)*( *"+ *(\n)*( *)\)+) *\n* *;)");
    const regex INSERT_INTO(R"(([iI][nN][sS][eE][rR][tT]) *((\n)+|( +))([iI][nN][tT][oO]) *(\n)*( *)([a-zA-Z0-9_]+) *(\n)* *\(+(\n)* *(\n)*(\"+([^\"]+) *(\n)*( *)\"+ *(\n)*( *),+ *(\n)*( *)){0,}\"+([^\"]+) *(\n)*( *"+ *(\n)*( *)\)+) *\n* *;)");
    const regex SELECT(R"(([sS][eE][lL][eE][cC][tT]))");
    const regex SELECT_ALL(R"/(([sS][eE][lL][eE][cC][tT]) *(((\n)* *)|( *))(\*) *(\n)*(([fF][rR][oO][mM])) *(((\n)+ *)|( +))(\n)*([a-zA-Z0-9]+) *(((\n)+ *)|( *));)/");
    const regex SELECT_WHERE(R"(([sS][eE][lL][eE][cC][tT]) *(((\n)+ *)|( +))(\n)*(([a-zA-Z0-9]+ *(((\n)+ *)|( *)), *(((\n)+ *)|( *))){0,}([a-zA-Z0-9]+)) *(((\n)+ *)|( *))(([fF][rR][oO][mM])) *(((\n)+ *)|( +))([a-zA-Z0-9]+) *(((\n)+ *)|( *))([wW][hH][eE][rR][eE])(((\n)+ *)|( +))([a-zA-Z0-9]+)(((\n)+ *)|( *))((=+)(((\n)+ *)|( *)))(\n)*((\"+[^\"]+\"*)(((\n)+ *)|( *)) *(((\n)+ *)|( *))\"+) *(((\n)+ *)|( *));+)");
    const regex SELECT_ON(R"(([sS][eE][lL][eE][cC][tT]) *(((\n)+ *)|( +))(([a-zA-Z0-9]+ *(((\n)+ *)|( *)), *(((\n)+ *)|( *))){0,}([a-zA-Z0-9]+)) *(((\n)+ *)|( *))(([fF][rR][oO][mM])) *(((\n)+ *)|( +))([a-zA-Z0-9]+) *(((\n)+ *)|( +))+ *([lL][eE][fF][tT]_[jJ][oO][iI][nN]) *(((\n)+ *)|( +))([a-zA-Z0-9]+ *(((\n)+ *)|( +))(\n)*([oO][nN])(((\n)+ *)|( +))(\n)*([a-zA-Z0-9])+ *(((\n)+ *)|( +))(=+)(((\n)+ *)|( +))+ *(\n)*([a-zA-Z0-9])+ *((\n)* *))+ *(\n)*;+)");
    const regex DELETE(R"(([dD][eE][lL][eE][tT][eE]))");
    const regex DELETE_ALL(R"(([dD][eE][lL][eE][tT][eE]) *(((\n)+ *)|( +))(\n)*(( *[a-zA-Z0-9]+ *(((\n)+ *)|( *)))) *(\n)*;+)");
    const regex DELETE_NAME(R"(([dD][eE][lL][eE][tT][eE]) *(((\n)+ *)|( +))([a-zA-Z0-9]+)(((\n)+ *)|( *))(\n)*([wW][hH][eE][rR][eE]) *(((\n)+ *)|( +))[a-zA-Z0-9]+ *(((\n)+ *)|( *))(=+) *(((\n)+ *)|( *))\"+[^\"]+\"*(((\n)+ *)|( *));+)");
    const regex DELETE_ID(R"(([dD][eE][lL][eE][tT][eE]) *(((\n)+ *)|( +))([a-zA-Z0-9]+ *(((\n)+ *)|( *)))([wW][hH][eE][rR][eE]) *(((\n)+ *)|( +))[a-zA-Z0-9]+ *(((\n)+ *)|( *))(=|!=|>|<|>=|<=) *(((\n)+ *)|( *))\" *(((\n)+ *)|( *))[0-9]+ *(((\n)+ *)|( *))\" *(((\n)+ *)|( *));+)");
    const regex WHERE(R"(([wW][hH][eE][rR][eE]))");
    const regex FROM(R"(([fF][rR][oO][mM]))");
    const regex LEFT_JOIN(R"(([lL][eE][fF][tT]_[jJ][oO][iI][nN]))");
    const regex ON(R"(([oO][nN]))");
    char temp[1024]{};
    char* line;
    char* table, * all, * el, * res, * table1, * table2;
    string temps;
    smatch tested, return_value, test;



    if (regex_search(ID, tested, CREATE))
    {
        if (regex_search(inputString, return_value, CREATE_FULL)) {
            strcpy(temp, inputString.c_str());
            for (int i = 0; line != nullptr; i++) {
                line = strtok(nullptr, " ,.(");
                if (i == 0) cout << "table " << line << " has been created\n";
            }
            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
            line = nullptr;
        }
    }


    if (regex_search(ID, tested, INSERT))
    {

        if (regex_search(inputString, return_value, INSERT_FULL)) {

            strcpy(temp, inputString.c_str());
            for (int i = 0; line != nullptr; i++) {
                line = strtok(nullptr, "();");
                if (i == 0) table = line;
                if (i > 0 && line != nullptr) cout << line << " ";
            }
            cout << "has been inserted into table " << table << "\n";
            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
            line = nullptr;
        }

        if (regex_search(inputString, return_value, INSERT_INTO)) {

            strcpy(temp, inputString.c_str());
            for (int i = 0; line != nullptr; i++) {
                line = strtok(nullptr, " ,.();");
                if (i == 1) table = line;
                if (i > 1 && line != nullptr) cout << line << " ";
            }
            cout << "has been inserted into table " << table << "\n";
            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
            line = nullptr;
        }
    }

    int t = 1000, flag = 0, k = 1000, h = 1000;

    if (regex_search(ID, tested, SELECT))
    {

        if (regex_search(inputString, return_value, SELECT_ALL)) {

            strcpy(temp, inputString.c_str());
            for (int i = 0; line != nullptr; i++) {
                line = strtok(nullptr, " ,.();");
                if (i == 2) table = line;
            }
            cout << "all elements has been selected from table " << table << "\n";

            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
            line = nullptr;
        }

        if (regex_search(inputString, return_value, SELECT_WHERE)) {

            strcpy(temp, inputString.c_str());
            for (int i = 0; line != NULL; i++) {
                line = strtok(NULL, " ,.();=");
                if (line == NULL) break;
                temps = line;
                if (regex_search(temps, test, WHERE)) {
                    t = i;
                }
                if (regex_search(temps, test, FROM)) {
                    flag = 1;
                    k = i;
                }
                else if (flag == 0) {
                    cout << line << " ";
                }
                if (i == k + 1 && line != nullptr) table = line;
                if (i == t + 1 && line != nullptr) {
                    el = line;
                    cout << "has been selected from table " << table << " where " << el << " = ";
                }
                if (i >= t + 2 && line != nullptr) {
                    cout << line << " ";
                }
            }

            cout << "\n";
            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
            line = nullptr;
        }
        if (regex_search(inputString, return_value, SELECT_ON)) {

            strcpy(temp, inputString.c_str());
            for (int i = 0; line != NULL; i++) {
                line = strtok(NULL, " ,.();=");
                if (line == NULL) break;
                temps = line;
                if (regex_search(temps, test, ON)) {
                    h = i;
                }
                if (regex_search(temps, test, LEFT_JOIN)) {
                    t = i;
                }
                if (regex_search(temps, test, FROM)) {
                    flag = 1;
                    k = i;
                }
                else if (flag == 0) {
                    cout << line << " ";
                }
                if (i == k + 1 && line != nullptr) table1 = line;
                if (i == t + 1 && line != nullptr) table2 = line;
                if (i == h + 1 && line != nullptr) {
                    el = line;
                    cout << "has been selected from table " << table1 << " left join with " << table2 << " where " << el << " = ";
                }
                if (i >= h + 2 && line != nullptr) {
                    cout << line << " ";
                }
            }
            cout << "\n";

            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
            line = nullptr;
        }
    }



    if (regex_search(ID, tested, DELETE))
    {

        if (regex_search(inputString, return_value, DELETE_ALL)) {

            strcpy(temp, inputString.c_str());

            for (int i = 0; line != nullptr; i++) {
                line = strtok(nullptr, " ,.(;");
                if (i == 0 && line != nullptr) cout << "table " << line << " has been deleted\n";
            }
            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
        }
        if (regex_search(inputString, return_value, DELETE_NAME)) {

            strcpy(temp, inputString.c_str());
            for (int i = 0; line != NULL; i++) {
                line = strtok(NULL, " ,.();=");
                if (line == NULL) break;
                temps = line;
                if (i == 0) table = line;
                if (regex_search(temps, test, WHERE)) {
                    t = i;
                }

                if (i == t + 1 && line != nullptr) {
                    el = line;
                    cout << "elements has been deleted from table " << table << " where " << el << " = ";
                }
                if (i >= t + 2 && line != nullptr) cout << line << " ";
            }

            cout << "\n";
            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
        }
    }

    delete table;
    delete table1;
    delete table2;
    delete el;
    delete res;
    delete line;
    line = nullptr;

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
