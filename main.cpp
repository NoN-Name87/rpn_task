#include <iostream>
#include <cstring>
#include <regex>
#include <stack>

constexpr char PLUS = '+';
constexpr char MINUS = '-';
constexpr char MULT = '*';

void operation(std::stack<int> & nums, char operand)
{
    if(nums.size() < 2)
        throw std::logic_error("Stack size for operations less than 2");

    int first_val = nums.top();
    nums.pop();
    int &result = nums.top();
    switch (operand)
    {
    case PLUS:
        result += first_val;
        break;
    case MINUS:
        result -= first_val;
        break;
    case MULT:
        result *= first_val;
        break; 
    default:
        throw std::logic_error("Incorrect operand (must be +, -, *)");
        break;
    }
}

int tokenize_n_calculate(const std::string & num_expr)
{
    std::stack<int> nums;
    std::regex reg("(-?[0-9]+|\\W{1}|\\w+)");
    std::sregex_token_iterator token(num_expr.cbegin(), num_expr.cend(), reg, 0);
    std::sregex_token_iterator end;
    while(token != end)
    {
        if(std::regex_match(token->str(), std::regex("(-?[0-9]+)|\\w+")))
        {
            nums.push(std::stoi(*token));
        }
        else if(*token != " ")
        {
            char operand = token->str()[0];
            operation(nums, operand);
        }
        token++;
    }
    if(nums.size() > 1)
        throw std::logic_error("Stack size more than 1 or empty");
    return nums.top();
}

int main(int argc, char **argv) //cmd: ./rpn_task 8 9 + 1 7 - '*' or ./rpn_task '8 9 + 1 7 - *' 
{
    std::string expr;
    try
    {
        if(argc > 1)
        {
            for(size_t i = 1; i < argc; i++)
            {
                expr += std::string(argv[i]) + " ";
            }
            std::cout << tokenize_n_calculate(expr) << "\n";
        }
    }
    catch(const std::exception & except)
    {
        std::cout << "ERROR: " << except.what() << "\n";
    }
    return 0;
}