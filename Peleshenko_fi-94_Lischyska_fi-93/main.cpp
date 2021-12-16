#include <iostream>
#include <string>
#include <regex>
#include <iomanip>
#include <sstream>



bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}


bool operator==(const std::string str, int number) {

    std::stringstream ss(str);
    int strAsInt;
    ss >> strAsInt;
    return (strAsInt = number);

}



bool operator!=(const std::string str, int number) {

    std::stringstream ss(str);
    int strAsInt;
    ss >> strAsInt;
    return (strAsInt != number);

}


using namespace std;

void show_all_table(string*** tables)
{
    for (int table_id = 0; table_id < 5; table_id++) {
        if (!tables[table_id][0][0].empty()) {
            cout << "table name = " << tables[table_id][0][0] << endl;
            for (int i = 1; i < 5 && !tables[table_id][i][0].empty(); i++)
            {
                for (int j = 0; j < 21; j++) {
                    if (j == 20) {
                        cout << "+";
                        continue;
                    }
                    else
                        cout << "-";
                }

            }
            cout << endl;
            for (int j = 1; j < 6 && !tables[table_id][j][0].empty(); j++) cout << setw(20) << tables[table_id][j][0] << "|";
            cout << endl;
            for (int i = 1; i < 5 && !tables[table_id][i][0].empty(); i++)
            {
                for (int j = 0; j < 21; j++) {
                    if (j == 20) {
                        cout << "+";
                        continue;
                    }
                    else
                        cout << "-";
                }
            }
            cout << endl;
            for (int j = 1; j < 6; j++)
            {

                for (int k = 1; k < 6; k++) {
                    if (!tables[table_id][k][j].empty()) {
                        cout << setw(20) << tables[table_id][k][j] << "|";

                    }
                    else {
                        bool flag = 0;
                        for (int kk = k; kk < 6; kk++)
                        {
                            if (!tables[table_id][kk][j].empty()) flag = 1;
                        }
                        if (flag) { cout << setw(20) << tables[table_id][k][j] << "|"; }
                        else continue;
                    }

                }
                cout << endl;
                //if(!tables[table_id][0][j].empty()){cout<<endl;}


            }

            for (int i = 1; i < 5 && !tables[table_id][i][0].empty(); i++)
            {
                for (int j = 0; j < 21; j++) {
                    if (j == 20) {
                        cout << "+";
                        continue;
                    }
                    else
                        cout << "-";
                }

            }
            cout << endl;

        }
    }
}

void show_table(string*** tables, int table_id)
{
    cout << "table name = " << tables[table_id][0][0] << endl;

    for (int j = 1; j < 6 && !tables[table_id][j][0].empty(); j++) cout << setw(20) << tables[table_id][j][0] << "|";
    cout << endl;
    for (int i = 1; i < 5 && !tables[table_id][i][0].empty(); i++)
    {
        for (int j = 0; j < 21; j++)
            cout << "-";
    }
    cout << endl;
    for (int j = 1; j < 6; j++)
    {

        for (int k = 1; k < 6; k++) {
            if (!tables[table_id][k][j].empty()) {
                cout << setw(20) << tables[table_id][k][j] << "|";
            }

        }
    }
}







string ParseIdentificators(string inputString, string ID, string*** tables)
{
    const regex CREATE(R"(([cC][rR][eE][aA][tT][eE]))");
    const regex CREATE_FULL(R"(([cC][rR][eE][aA][tT][eE])((\n)+|( +))(\n)*([a-zA-Z0-9_]+)(\n)* *(\n)*\(+(\n)* *(\n)*(([a-zA-Z0-9_])+ *((\n)* *)([iI][nN][dD][eE][xX][eE][dD])* *((\n)* *),+ *(\n)* *){0,}([a-zA-Z0-9_]+)(( *\n+ *| +)([iI][nN][dD][eE][xX][eE][dD]))*(\n)* *(\n)*\)+(\n)* *(\n)*;+)");
    const regex INSERT(R"(([iI][nN][sS][eE][rR][tT]))");
    const regex INSERT_FULL(R"(([iI][nN][sS][eE][rR][tT]) *((\n)+|( +))(\n)*( *)([a-zA-Z0-9_]+) *(\n)* *\(+(\n)* *(\n)*(\"+([^\"]+) *(\n)*( *)\"+ *(\n)*( *),+ *(\n)*( *)){0,}\"+([^\"]+) *(\n)*( *"+ *(\n)*( *)\)+) *\n* *;)");
    const regex INSERT_INTO(R"(([iI][nN][sS][eE][rR][tT]) *((\n)+|( +))([iI][nN][tT][oO]) *(\n)*( *)([a-zA-Z0-9_]+) *(\n)* *\(+(\n)* *(\n)*(\"+([^\"]+) *(\n)*( *)\"+ *(\n)*( *),+ *(\n)*( *)){0,}\"+([^\"]+) *(\n)*( *"+ *(\n)*( *)\)+) *\n* *;)");
    const regex SELECT(R"(([sS][eE][lL][eE][cC][tT]))");
    const regex SELECT_ALL(R"(([sS][eE][lL][eE][cC][tT]) *(((\n)+ *)|( +))((\*)|(\*|([a-zA-Z0-9]+|(\*)) *(((\n)+ *)|( *)), *(((\n)+ *)|( *))){0,}([a-zA-Z0-9]+)) *(\n)*(([fF][rR][oO][mM])) *(((\n)+ *)|( +))(\n)*([a-zA-Z0-9]+) *(((\n)+ *)|( *));)");
    const regex SELECT_WHERE(R"(([sS][eE][lL][eE][cC][tT]) *(((\n)+ *)|( +))(\n)*(((\*|[a-zA-Z0-9]+|(\*)) *(((\n)+ *)|( *)), *(((\n)+ *)|( *))){0,}(\*|[a-zA-Z0-9]+)) *(((\n)+ *)|( *))(([fF][rR][oO][mM])) *(((\n)+ *)|( +))([a-zA-Z0-9]+) *(((\n)+ *)|( *))([wW][hH][eE][rR][eE])(((\n)+ *)|( +))([a-zA-Z0-9]+)(((\n)+ *)|( *))((=+)(((\n)+ *)|( *)))(\n)*((\"+[^\"]+\"*)(((\n)+ *)|( *)) *(((\n)+ *)|( *))\"+) *(((\n)+ *)|( *));+)");
    const regex SELECT_ON(R"(([sS][eE][lL][eE][cC][tT]) *(((\n)+ *)|( +))(((\*|[a-zA-Z0-9]+|(\*)) *(((\n)+ *)|( *)), *(((\n)+ *)|( *))){0,}(\*|[a-zA-Z0-9]+)) *(((\n)+ *)|( *))(([fF][rR][oO][mM])) *(((\n)+ *)|( +))([a-zA-Z0-9]+) *(((\n)+ *)|( +))+ *([lL][eE][fF][tT]_[jJ][oO][iI][nN]) *(((\n)+ *)|( +))([a-zA-Z0-9]+ *(((\n)+ *)|( +))(\n)*([oO][nN])(((\n)+ *)|( +))(\n)*([a-zA-Z0-9])+ *(((\n)+ *)|( +))(=+)(((\n)+ *)|( +))+ *(\n)*([a-zA-Z0-9])+ *((\n)* *))+ *(\n)*;+)");
    const regex DELETE(R"(([dD][eE][lL][eE][tT][eE]))");
    const regex DELETE_ALL(R"(([dD][eE][lL][eE][tT][eE]) *(((\n)+ *)|( +))(\n)*([fF][rR][oO][mM])(( *[a-zA-Z0-9]+ *(((\n)+ *)|( *)))) *(\n)*;+)");
    const regex DELETE_NAME(R"(([dD][eE][lL][eE][tT][eE]) *(((\n)+ *)|( +))([a-zA-Z0-9_]+)(((\n)+ *)|( *))(\n)*([wW][hH][eE][rR][eE]) *(((\n)+ *)|( +))[a-zA-Z0-9_]+ *(((\n)+ *)|( *))(=+) *(((\n)+ *)|( *))\"+[^\"]+\"*(((\n)+ *)|( *));+)");
    const regex DELETE_ID(R"(([dD][eE][lL][eE][tT][eE]) *(((\n)+ *)|( +))([a-zA-Z0-9_]+ *(((\n)+ *)|( *)))([wW][hH][eE][rR][eE]) *(((\n)+ *)|( +))[a-zA-Z0-9_]+ *(((\n)+ *)|( *))(=|!=|>|<|>=|<=) *(((\n)+ *)|( *))\" *(((\n)+ *)|( *))[a-zA-Z0-9_]+ *(((\n)+ *)|( *))\" *(((\n)+ *)|( *));+)");
    const regex WHERE(R"(([wW][hH][eE][rR][eE]))");
    const regex FROM(R"(([fF][rR][oO][mM]))");
    const regex LEFT_JOIN(R"(([lL][eE][fF][tT]_[jJ][oO][iI][nN]))");
    const regex ON(R"(([oO][nN]))");
    const regex ZNAK(R"((=|!=|>|<|>=|<=))");
    char temp[1024]{}, find_znak[1024]{};
    char* line;
    char* table, * all, * el, * res, * table1, * table2;
    string temps;
    smatch tested, return_value, test;
    int t = 1000, flag = 0, k = 1000, h = 1000;
    // string ***tables = new string**[5];





    string* values;

    cout << "avaluable tables= ";

    for (int i = 0; i < 5; i++) cout << tables[i][0][0];
    //       tables[i]="dsad";
    cout << endl;





    if (regex_search(ID, tested, CREATE))
    {
        if (regex_search(inputString, return_value, CREATE_FULL)) {
            strcpy(temp, inputString.c_str());

            line = strtok(temp, " ,.(");
            line = strtok(NULL, " ,.(");
            //-------------------------------------------------------------------------- створення таблиці

            for (int i = 0; i < 5; i++) {
                if (line == tables[i][0][0]) {
                    cout << "A table with that name have been created (" << i << ")\n";
                    throw std::invalid_argument("_");
                    break;
                }
            }
            for (int i = 0; i <= 5; i++)
            {

                if (i == 5) {
                    cout << "tables more than 5!\n";
                    throw std::invalid_argument("_");
                    break;
                }

                if (tables[i][0][0].empty())
                {

                    tables[i][0][0] = line;
                    cout << "table " << tables[i][0][0] << " has been created\n";

                    line = strtok(NULL, " ,.();");
                    int column_size = 0;
                    for (int j = 1; line != nullptr && j < 6; j++)
                    {
                        tables[i][j][0] = line;

                        line = strtok(NULL, " ,.();");

                        column_size++;
                    }

                    for (int j = 0; j < 6; j++)
                        cout << tables[i][j][0] << "\t";

                    tables[i][0][1] = column_size + 48;
                    break;
                }
            }

            cout << endl;
            //--------------------------------------------------------------------------

            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
            line = nullptr;
        }
    }


    if (regex_search(ID, tested, INSERT))
    {

        if (regex_search(inputString, return_value, INSERT_FULL)) {

            bool flag_correct_table_name = 0;
            strcpy(temp, inputString.c_str());

            line = strtok(temp, " ,\".();");
            line = strtok(NULL, " ,\".();");
            table = line;
            cout << "table=" << line << endl;
            for (int i = 0; i < 6 && line != nullptr; i++)
            {
                if (i == 5)
                {
                    cout << "cant find table with that name" << line << "\n";
                    throw std::invalid_argument("_");
                    break;

                }
                if (line == tables[i][0][0])
                {


                    //--------------------------------------------------------------------------
                    //обрахунок кількості елементів та перевірка аргументів
                    int count_arguments = 0;
                    for (int i = 0; temp[i] != ';'; i++)
                    {
                        if (temp[i] == '"') count_arguments++;
                    }
                    count_arguments /= 2;
                    cout << "\ncount_arguments=" << count_arguments << endl;;

                    if (tables[i][0][1] != count_arguments)
                    {
                        cout << "arguments " << count_arguments << "but should be(" << tables[i][0][1] << ")" << endl;
                        throw std::invalid_argument("_");
                        break;

                    }
                    //обрахунок кількості елементів та перевірка аргументів
                    //--------------------------------------------------------------------------



                    for (int m = 1; m < 7; m++)
                    {


                        //cout<<tables[i][m][0];
                        if (tables[i][1][m].empty())
                        {



                            cout << "m=" << m << endl;
                            for (int j = 1; line != nullptr;)
                            {

                                line = strtok(NULL, ",\".();");

                                if (line != nullptr && line[0] != ' ') {

                                    tables[i][j][m] = line;
                                    j++;

                                }
                                else continue;
                            }

                            break;
                        }
                    }
                }
            }


            cout << "has been inserted table " << table << "\n";
            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
            line = nullptr;
        }








        if (regex_search(inputString, return_value, INSERT_INTO)) {

            bool flag_correct_table_name = 0;
            strcpy(temp, inputString.c_str());

            line = strtok(temp, " ,\".();");
            line = strtok(NULL, " ,\".();");
            line = strtok(NULL, " ,\".();");
            table = line;
            cout << "table=" << line << endl;
            for (int i = 0; i < 6 && line != nullptr; i++)
            {
                if (i == 5)
                {
                    cout << "cant find table with that name" << line << "\n";
                    throw std::invalid_argument("_");
                    break;

                }
                if (line == tables[i][0][0])
                {


                    //--------------------------------------------------------------------------
                    //обрахунок кількості елементів та перевірка аргументів
                    int count_arguments = 0;
                    for (int i = 0; temp[i] != ';'; i++)
                    {
                        if (temp[i] == '"') count_arguments++;
                    }
                    count_arguments /= 2;
                    cout << "\ncount_arguments=" << count_arguments << endl;;

                    if (tables[i][0][1] != count_arguments)
                    {
                        cout << "arguments " << count_arguments << "but should be(" << tables[i][0][1] << ")" << endl;
                        throw std::invalid_argument("_");
                        break;

                    }
                    //обрахунок кількості елементів та перевірка аргументів
                    //--------------------------------------------------------------------------



                    for (int m = 1; m < 7; m++)
                    {


                        //cout<<tables[i][m][0];
                        if (tables[i][1][m].empty())
                        {



                            cout << "m=" << m << endl;
                            for (int j = 1; line != nullptr;)
                            {
                                //                                if(){
                                //                                    line = strtok(NULL, ",\".();");
                                //                                    continue;
                                //                                }
                                line = strtok(NULL, ",\".();");

                                if (line != nullptr && line[0] != ' ') {

                                    tables[i][j][m] = line;
                                    j++;

                                }
                                else continue;
                            }

                            break;


                        }


                    }
                }
            }

            cout << "has been inserted INTO table " << table << "\n";
            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
            line = nullptr;

        }

    }

    if (regex_search(ID, tested, SELECT))
    {

        if (regex_search(inputString, return_value, SELECT_ALL)) {

            strcpy(temp, inputString.c_str());
            line = strtok(temp, " ,.();");
            for (int i = 0; line != nullptr; i++) {
                line = strtok(NULL, " ,.();=");
                if (line == NULL) break;
                temps = line;
                if (regex_search(temps, test, FROM)) {
                    t = i;
                    flag = 1;
                }
                if (flag == 0) cout << line << " ";
                if (t + 1 == i && line != nullptr) table = line;
            }
            cout << "elements has been selected from table " << table << "\n";

            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
            line = nullptr;
        }

        if (regex_search(inputString, return_value, SELECT_WHERE)) {

            strcpy(temp, inputString.c_str());
            line = strtok(temp, " ,.();=");
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
            line = strtok(temp, " ,.();=");
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

            line = strtok(temp, " ,.(;");
            line = strtok(NULL, " ,.(;");

            //if(regex_search(line, tested,inputString.c_str()))
            line = strtok(NULL, " ,.(;");
            for (int i = 0; i < 5; i++)
            {
                if (tables[i][0][0] == line)
                {

                    for (int j = 0; j < 6; j++)
                    {
                        for (int m = 0; m < 6; m++)
                        {
                            tables[i][j][m].clear();
                        }
                    }

                }
            }

            cout << "table " << line << " has been deleted\n";

            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
        }
        if (regex_search(inputString, return_value, DELETE_ID)) {

            strcpy(temp, inputString.c_str());
            strcpy(find_znak, inputString.c_str());
            line = strtok(temp, " ,.();=");
            for (int i = 0; line != NULL; i++) {
                line = strtok(NULL, " ,.();=><!");
                if (line == NULL) break;
                temps = line;
                if (i == 0) table = line;
                if (regex_search(temps, test, WHERE)) {
                    t = i;
                }

                if (i == t + 1 && line != nullptr) {
                    el = line;

                    //--------------------------------------------------------------------------------------------------------------
                    //видалення таблиці

                    for (int ii = 0; ii < 5; ii++) //пошук таблиці
                    {
                        cout << "delete tables " << tables[i][0][0] << "\t";
                        if (tables[ii][0][0] == table)
                        {
                            for (int j = 1; j < 6; j++)
                            {
                                cout << tables[ii][j][0]/*<<"\t"<<el*/ << endl;
                                if (tables[ii][j][0] == el)//пошук колонки
                                {
                                    cout << "column with name " << el << " found" << endl;
                                    // strcpy(temp, inputString.c_str());

                                    //                                    do{
                                    //                                        line = strtok(NULL, " \",.();");
                                    //                                        if (line != nullptr)
                                    //                                            cout<<line<<endl;
                                    //                                        else break;
                                    //                                    }
                                    //                                    while(line!=nullptr||regex_search(line, temp, ZNAK)!=0);
                                    int variant = 0;
                                    string test_line = strtok(NULL, " ,.();=\"");
                                    for (int i = 0; i < 1024 && temp[i] != ';'; i++)//пошук знаку
                                    {
                                        if (find_znak[i] == '=' && find_znak[i - 1] == '>')
                                        {
                                            variant = 4;
                                            break;
                                        }
                                        if (find_znak[i] == '=' && find_znak[i - 1] == '<')
                                        {
                                            variant = 3;
                                            break;
                                        }
                                        if (find_znak[i] == '=' && find_znak[i - 1] == '!')
                                        {
                                            variant = 2;
                                            break;
                                        }

                                        if (find_znak[i] == '=' && find_znak[i - 1] != '>' && find_znak[i - 1] != '<' && find_znak[i - 1] != '!')
                                        {
                                            variant = 1;
                                            break;
                                        }
                                        if (find_znak[i] == '>' && find_znak[i + 1] != '=')
                                        {
                                            variant = 5;
                                            break;
                                        }
                                        if (find_znak[i] == '<' && find_znak[i + 1] != '=')
                                        {
                                            variant = 6;
                                            break;
                                        }

                                    }
                                    test_line = strtok(NULL, " ,.();=\"");
                                    if (variant > 2) //перевірка чи є рядки таблиці і аргумент цифрами
                                    {
                                        if (!is_number(test_line))
                                        {
                                            cout << "argument " << test_line << " is not a number!\n";
                                            throw std::invalid_argument("_");

                                        }
                                        for (int m = 1; m < 6; m++)
                                        {
                                            if (!tables[ii][j][m].empty())
                                            {
                                                if (!is_number(tables[ii][j][m]))
                                                {
                                                    cout << "line of table  " << tables[ii][j][m] << " is not a number!\n";
                                                    throw std::invalid_argument("_");
                                                    break;
                                                }
                                            }
                                        }

                                    }
                                    // cout<<" znak = has been found\n";
                                    switch (variant)
                                    {
                                    case 1: //=
                                        for (int m = 1; m < 6; m++)
                                        {
                                            if (!tables[ii][j][m].empty())cout << tables[ii][j][m] << "\t" << test_line;
                                            if (tables[ii][j][m] == test_line) {
                                                cout << "line has been deleted\n";
                                                tables[ii][j][m].clear();
                                            }
                                        }
                                        break;
                                    case 4: //>=
                                        for (int m = 1; m < 6; m++)
                                        {

                                            if (is_number(tables[ii][j][m]))
                                            {
                                                cout << tables[ii][j][m] << endl;
                                                if (tables[ii][j][m] >= test_line)
                                                {
                                                    cout << tables[ii][j][m] << " more or equal " << test_line << endl;
                                                    tables[ii][j][m].clear();
                                                }

                                            }


                                        }
                                        break;
                                    case 3: //<=
                                        for (int m = 1; m < 6; m++)
                                        {

                                            if (is_number(tables[ii][j][m]))
                                            {
                                                cout << tables[ii][j][m] << endl;
                                                if (tables[ii][j][m] <= test_line)
                                                {
                                                    cout << tables[ii][j][m] << " less or equal " << test_line << endl;
                                                    tables[ii][j][m].clear();
                                                }

                                            }


                                        }
                                        break;
                                    case 2: //!=
                                        for (int m = 1; m < 6; m++)
                                        {
                                            if (tables[ii][j][m] != line)
                                            {
                                                if (!tables[ii][j][m].empty())cout << tables[ii][j][m] << "\t" << test_line;
                                                if (tables[ii][j][m] != test_line) {
                                                    cout << "line has been deleted\n";
                                                    tables[ii][j][m].clear();
                                                }
                                            }
                                        }
                                        break;
                                    case 5: //>
                                        for (int m = 1; m < 6; m++)
                                        {

                                            if (is_number(tables[ii][j][m]))
                                            {
                                                cout << tables[ii][j][m] << endl;
                                                if (tables[ii][j][m] > test_line)
                                                {
                                                    cout << tables[ii][j][m] << " more than " << test_line << endl;
                                                    tables[ii][j][m].clear();
                                                }

                                            }


                                        }
                                        break;
                                    case 6: //<
                                        for (int m = 1; m < 6; m++)
                                        {

                                            if (is_number(tables[ii][j][m]))
                                            {
                                                cout << tables[ii][j][m] << endl;
                                                if (tables[ii][j][m] < test_line)
                                                {
                                                    cout << tables[ii][j][m] << " less than " << test_line << endl;
                                                    tables[ii][j][m].clear();
                                                }

                                            }


                                        }
                                        break;
                                    default:
                                    {
                                        cout << "no any zkak\n";
                                        cout << "can`t find column with name " << el << endl;
                                        throw std::invalid_argument("_");

                                    }
                                    }






                                    break;
                                }
                                if (j == 5)//колонку не знайшло
                                {
                                    cout << "can`t find column with name " << el << endl;
                                    throw std::invalid_argument("_");
                                    break;
                                }
                            }
                            break;
                        }
                        if (i == 4)//не знайшло таблицю
                        {
                            cout << "can`t find table " << table << endl;
                            throw std::invalid_argument("_");
                            break;

                        }
                    }


                    //видалення таблиці
                    //--------------------------------------------------------------------------------------------------------------

                    cout << "elements has been deleted from table " << table << " where " << el << " = ";
                }
                if (i >= t + 2 && line != nullptr) cout << line << " ";
            }
            cout << endl;
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 6; j++)
                {
                    for (int m = 0; m < 6; m++)
                    {
                        cout << tables[i][j][m] << "\t";
                    }
                    cout << endl;
                }
            }


            cout << "\n";
            for (int i = 0; i < 3; i++) {
                return return_value[i].str();
            }
        }
    }
    throw std::invalid_argument("_");

    delete table;
    delete table1;
    delete table2;
    delete el;
    delete res;
    delete line;
    line = nullptr;



}


int main()
{
    string s;
    string*** tables = new string * *[5];
    for (int i = 0; i < 5; i++)
    {
        tables[i] = new string * [6];
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            tables[i][j] = new string[6];
        }
    }
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
            s = ParseIdentificators(s, line, tables);
        }
        catch (const exception&)
        {
            cout << "Identificator '" + s + "' is not correct" << endl;
            continue;
        }
        cout << "Succesfully completed" << endl;
        show_all_table(tables);
    }
}
