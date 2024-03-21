#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <iostream>
#include <cctype>
#include <stack>
#include <cmath>

enum class Operator { ADD, SUB, MUL, DIV, OPEN_PAREN, CLOSE_PAREN};
enum class TokenType { OPERATOR, OPERAND };

struct Token 
{
  TokenType type;
  float value;
  Operator op;
};

std::vector<std::string>split_string(std::string const& s)
{
    std::istringstream in(s);
    return std::vector<std::string>(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>()); 
}

bool is_floating(std::string const& s)
{
   for (int i = 0; i < s.size() ; i++)
   {
        if (!(std::isdigit(s[i]) || s[i] == '.'))
            return false;
   }
    return true;
}

float calculate_result (float leftOperand, std::string NPI_operator, float rightOperand)
{
    if (NPI_operator == "+")
    {
        return leftOperand + rightOperand;
    }
    else if (NPI_operator == "-")
    {
        return leftOperand - rightOperand;
    }
    else if (NPI_operator == "*")
    {
        return leftOperand * rightOperand;
    }
    else if (NPI_operator == "/")
    {
        return leftOperand / rightOperand;
    }
    else 
    {
        return pow(leftOperand, rightOperand);
    }
}

float npi_evaluate(std::vector<std::string> const& tokens)
{
    std::stack<float> stack;
    for (int i = 0; i < tokens.size(); i++)
    {
        if (is_floating(tokens[i]))
        {
            stack.push(std::stof(tokens[i]));
        }
        else
        {
            std::string NPI_operator = tokens[i];

            float rightOperand { stack.top() };
            stack.pop();
            float leftOperand { stack.top() };
            stack.pop();

            float result = {calculate_result(leftOperand, NPI_operator, rightOperand)};
            stack.push(result);
        }
    }
    return stack.top(); 
}

Token make_token(float value)
{
    // S'il y a un couac au lancement c'est peut-être dû à ça...
    return {TokenType::OPERAND, value, Operator::ADD};
}

Token make_token(Operator op)
{
    // ... ou ça
    return {TokenType::OPERATOR, 0, op};
}

std::vector<Token> tokenize(std::vector<std::string> const& words)
{
    for (int i = 0; i < words.size(); i++)
    {
        if (is_floating(words[i]))
        {
            make_token(std::stof(words[i]));
        }
        else
        {
            // ! PB ICI
            make_token(words[i]);
        }
    }
}

int main()
{
    std::string user_input;
    std::cout << "Please enter NPI expression :";
    std::getline(std::cin, user_input);
    
    std::vector<std::string> splitted_user_input = split_string(user_input);
    std::cout << npi_evaluate(splitted_user_input);

    return 0;
}