#include <iostream>
#include "ArrayList.h"
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>

using namespace std;

string data = "";                      // input
string number = "";                    // tmp
bool before_is_number = false;         //tmp
bool not_op = false;                   //tmp
int array_index = 0;                   //index of main_array
int par_order = 0;                     // used for handle nested parentheses
vector<tuple<int, int>> par_locations; // used to save location of parentheses
string array_main[200];                // array for store characters

bool is_number(string x) // find is number or not
{
    if (((int)x[0] >= 48 && (int)x[0] <= 57))
    {
        return true;
    }
    if (x[0] == '-' && x.length() > 1)
    {
        return true;
    }
    if (x[0] == '.')
    {
        return true;
    }
    return false;
}

float myfind(int i, bool forward) // find two operands for a operator in main_array
{
    if (!forward)
    {
        while (true)
        {
            i--;
            if (is_number(array_main[i]))
            {
                float n1 = stof(array_main[i]);
                array_main[i] = "";
                return n1;
            }
        }
    }
    else
    {
        while (true)
        {
            i++;
            if (is_number(array_main[i]))
            {
                float n1 = stof(array_main[i]);
                array_main[i] = "";
                return n1;
            }
        }
    }
}

float inside_parentheses(int first) // calculate inside parentheses
{
    float result_pow = 0;
    float result_mult = 0;
    float result_sum = 0;
    int par_index = 0;
    bool is_mult = false;
    bool is_pow = false;
    bool is_sum = false;
    array_main[first] = "";
    for (int i = first + 1;; i++)
    {
        if (array_main[i] == ")")
        {
            par_index = i;
            break;
        }
        else if (array_main[i] == "^")
        {
            is_pow = true;
            result_pow = 0;
            float n1 = myfind(i, false);
            float n2 = myfind(i, true);
            float x = pow(n1, n2);
            // cout << n1 << " : " << n2 << " : " << x <<endl;
            array_main[i] = to_string(x);
            result_pow += x;
        }
    }
    for (int i = first + 1;; i++)
    {
        if (array_main[i] == ")")
        {
            break;
        }
        else if (array_main[i] == "*")
        {
            is_mult = true;
            result_mult = 0;
            float n1 = myfind(i, false);
            float n2 = myfind(i, true);
            float x = n1 * n2;
            // cout << n1 << " : " << n2 << " : " << x <<endl;
            array_main[i] = to_string(x);
            result_mult += x;
        }
        else if (array_main[i] == "/")
        {
            is_mult = true;
            result_mult = 0;
            float n1 = myfind(i, false);
            float n2 = myfind(i, true);
            float x = n1 / n2;
            // cout << n1 << " : " << n2 << " : " << x <<endl;
            array_main[i] = to_string(x);
            result_mult += x;
        }
    }
    for (int i = first + 1;; i++)
    {
        if (array_main[i] == ")")
        {
            break;
        }
        else if (array_main[i] == "+")
        {
            is_sum = true;
            result_sum = 0;
            float n1 = myfind(i, false);
            float n2 = myfind(i, true);
            float x = n1 + n2;
            // cout << n1 << " : " << n2 << " : " << x <<endl;
            array_main[i] = to_string(x);
            result_sum += x;
        }
        else if (array_main[i] == "-")
        {
            is_sum = true;
            result_sum = 0;
            float n1 = myfind(i, false);
            float n2 = myfind(i, true);
            float x = n1 - n2;
            // cout << n1 << " : " << n2 << " : " << x <<endl;
            array_main[i] = to_string(x);
            result_sum += x;
        }
    }
    array_main[par_index] = "";
    if (is_sum)
        return result_sum;
    if (is_mult)
        return result_mult;
    if (is_pow)
        return result_pow;
    else
    {
        not_op = true;
        return stof(array_main[first + 1]);
    }
}

float final_result() // calculate result
{
    float result_pow = 0;
    float result_mult = 0;
    float result_sum = 0;
    bool is_mult = false;
    bool is_sum = false;
    bool is_pow = false;
    for (int i = 0; i < 200; i++)
    {
        if (array_main[i] == "=")
        {
            break;
        }
        else if (array_main[i] == "^")
        {
            is_pow = true;
            result_pow = 0;
            // cout << "^ finded\n";
            float n1 = myfind(i, false);
            float n2 = myfind(i, true);
            float x = pow(n1, n2);
            // cout << n1 << " : " << n2 << " : " << x <<endl;
            array_main[i] = to_string(x);
            result_pow += x;
        }
    }
    for (int i = 0; i < 200; i++)
    {
        if (array_main[i] == "=")
        {
            break;
        }
        else if (array_main[i] == "*")
        {
            is_mult = true;
            result_mult = 0;
            // cout << "* finded\n";
            float n1 = myfind(i, false);
            float n2 = myfind(i, true);
            float x = n1 * n2;
            // cout << n1 << " : " << n2 << " : " << x <<endl;
            array_main[i] = to_string(x);
            result_mult += x;
        }
        else if (array_main[i] == "/")
        {
            is_mult = true;
            result_mult = 0;
            // cout << "/ finded\n";
            float n1 = myfind(i, false);
            float n2 = myfind(i, true);
            float x = n1 / n2;
            // cout << n1 << " : " << n2 << " : " << x <<endl;
            array_main[i] = to_string(x);
            result_mult += x;
        }
    }
    for (int i = 0; i < 200; i++)
    {
        if (array_main[i] == "=")
        {
            break;
        }
        else if (array_main[i] == "+")
        {
            is_sum = true;
            result_sum = 0;
            // cout << "+ finded\n";
            float n1 = myfind(i, false);
            float n2 = myfind(i, true);
            float x = n1 + n2;
            // cout << n1 << " : " << n2 << " : " << x <<endl;
            array_main[i] = to_string(x);
            result_sum += x;
        }
        else if (array_main[i] == "-")
        {
            is_sum = true;
            result_sum = 0;
            // cout << "- finded\n";
            float n1 = myfind(i, false);
            float n2 = myfind(i, true);
            float x = n1 - n2;
            // cout << n1 << " : " << n2 << " : " << x <<endl;
            array_main[i] = to_string(x);
            result_sum += x;
        }
    }
    if (is_sum)
        return result_sum;
    if (is_mult)
        return result_mult;
    if (is_pow)
        return result_pow;
    else
    {
        for (int j = 0; j < 200; j++)
        {
            if (is_number(array_main[j]))
                return stof(array_main[j]);
        }
    }
}

float calculate() // main function of calculation
{
    for (int i = par_locations.size() - 1; i >= 0; i--)
    { // iterate over parentheses
        int first = get<1>(par_locations.at(i));
        // cout << get<0>(par_locations.at(i)) << " : " << get<1>(par_locations.at(i)) << " " << par_locations.size() << endl;
        float x = inside_parentheses(first);
        if (not_op)
        {
            array_main[first] = to_string(x);
            not_op = false;
        }
    }
    float res = final_result();
    return res;
}

void show_message(string location) // return error messages
{
    printf("Wrong equalition\n");
    printf(location.c_str(), "\n");
    printf("Please again!\n");
}

void parser() // parser for input data
{
    for (int i = 0; i < data.length(); i++)
    {
        if (data[i] == ' ')
            continue;
        if (is_number(string(1, data[i])))
        {
            number += data[i];
            before_is_number = true;
        }
        else if (before_is_number == true)
        { //number is detected
            before_is_number = false;
            if (array_index == 0)
            {
                array_main[array_index] = number;
                array_index++;
                number = "";
                i -= 1;
            }
            else if (array_main[array_index - 1] == "+" || array_main[array_index - 1] == "-" || array_main[array_index - 1] == "*" || array_main[array_index - 1] == "/" || array_main[array_index - 1] == "^" || array_main[array_index - 1] == "(")
            {
                array_main[array_index] = number;
                array_index++;
                number = "";
                i -= 1;
            }
            else
            {
                show_message("number detection error");
                return;
            }
        }
        else if (data[i] == '+' || data[i] == '-')
        { // + or - detected
            if (array_index == 0)
            {
                show_message("before <+> <-> number not found");
                return;
            }
            if (is_number(array_main[array_index - 1]) || array_main[array_index - 1] == ")")
            {
                array_main[array_index] = string(1, data[i]);
                array_index++;
            }
            else
            {
                show_message("before <+> <-> number not found");
                return;
            }
        }

        else if (data[i] == '*' || data[i] == '/')
        { // "*" or "/" detected
            if (array_index == 0)
            {
                show_message("before <*> </> number not found");
                return;
            }
            if (is_number(array_main[array_index - 1]) || array_main[array_index - 1] == ")")
            {
                array_main[array_index] = string(1, data[i]);
                array_index++;
            }
            else
            {
                show_message("before <*> </> number not found");
                return;
            }
        }
        else if (data[i] == '^')
        { // "^"" detected
            if (array_index == 0)
            {
                show_message("before <^> number or <)> not found");
                return;
            }
            if (is_number(array_main[array_index - 1]) || array_main[array_index - 1] == ")")
            {
                array_main[array_index] = string(1, data[i]);
                array_index++;
            }
            else
            {
                show_message("before <^> number or <)> not found");
                return;
            }
        }

        else if (data[i] == '(')
        { // "(" detected
            par_order++;
            if (array_index == 0)
            {
                array_main[array_index] = string(1, data[i]);
                par_locations.emplace_back(par_order, array_index);
                array_index++;
            }
            else if (array_main[array_index - 1] == "+" || array_main[array_index - 1] == "-" || array_main[array_index - 1] == "*" || array_main[array_index - 1] == "/" || array_main[array_index - 1] == "^" || array_main[array_index - 1] == "(")
            {
                array_main[array_index] = string(1, data[i]);
                par_locations.emplace_back(par_order, array_index);
                array_index++;
            }
            else
            {
                show_message("wrong pattern before )");
                return;
            }
        }

        else if (data[i] == ')')
        { // ")" detected
            par_order--;
            if (is_number(array_main[array_index - 1]) || array_main[array_index - 1] == ")")
            {
                array_main[array_index] = string(1, data[i]);
                array_index++;
            }
            else
            {
                show_message("wrong pattern before )");
                return;
            }
        }

        else if (data[i] == '=')
        { // "=" detected
            if (is_number(array_main[array_index - 1]) || array_main[array_index - 1] == ")")
            {
                array_main[array_index] = string(1, data[i]);
                sort(par_locations.begin(), par_locations.end());
                float res = calculate();
                cout << endl
                     << "Result is: " << res << endl << endl;
                return;
            }
            else
            {
                printf("number not found before \"=\" \n");
                return;
            }
        }

        else
        {
            printf("Wrong characters!\n");
            return;
        }
    }
}

int main() // main
{
    cout << "Basic calculator\nIt supports four main operators and power(^) and parentheses. Please write english and end of equation write '='\n";
    int order=0;
    
    while (true)
    { // get input
        cout << "1.start 2.exit\n";
        cin >> order;
        if (order == 1)
        {
        cout << "Equation: ";
        cin.ignore();
        getline(cin, data);
        cout << data<< endl;
        before_is_number = false;
        array_index = 0;
        not_op = false;
        parser();
        while (!par_locations.empty())
            par_locations.pop_back();
        }
        else if (order == 2)
            break;
        else
        {
            cout << "Wrong order. Please again\n";
            continue;
        }
    }
    return 0;
}