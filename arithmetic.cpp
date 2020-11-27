#include <iostream>
#include <string>
#include <stack>
#include <regex>

#include "lib/Parser.hpp"
#include "lib/ShuntingYard.hpp"
#include "lib/PostfixEvaluation.hpp"

using namespace std;

void expressionToQuadruple(std::stack<std::string> rpnStack);
std::string removeSpaces(std::string expression);
bool isOperator(std::string operato);

int main(int argc, char *argv[])
{
    std::cout << "\nBienvenido a mi generador de cuadruplos!\n" << std::endl;
    std::cout << "\nLe recordamos que en su ecuación debe reemplazar sus icognitas por valores. \n Ej: A = 30, B = 40, C = 50... \n ((A+B) * C) = ((30 + 40) * 50)\n" << std::endl;

    std::cout << "Ingrese su expresion con valores: " << std::endl;
    std::string line; // Linea de ingreso
    std::stack<std::string> output;  // Salida para el algoritmo de ShuntingYard.

    getline(std::cin, line);  // Lee la cadena

    // Inicializamos el algoritmo
    ShuntingYard sy(line);

    try
    {
        sy.parsing(); // Proceso de parseo 
    }
    catch (const std::invalid_argument &e) // Retornamos algun error
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;
    }

    std::stack<std::string> rpnStack = sy.get_rpn(); //Obtenemos la cadena para generar cuadruplos

    expressionToQuadruple(rpnStack); // Generamos los cuadruplos basado en la cadena

    

    return 0;
}

void expressionToQuadruple(std::stack<std::string> rpnStack){
    std::string tab = "\t";
    std::string newline = "\n";
    std::stack<std::string> quadStack;
    std::string quadExpression = newline + "OP" + tab + "Arg1" + tab + "Arg2" + tab + "RESULTADO" + newline;
    int stepCounter = 0;

// (22+90)*((82+45)/(30+5))
    while(!rpnStack.empty()){

        std::string currentValue = rpnStack.top();
        rpnStack.pop();

        if(isOperator(currentValue)){

            std::string argument2 = quadStack.top();
            quadStack.pop();
            std::string argument1 = quadStack.top();
            quadStack.pop();

            // if(!quadStack.empty()) {
            //     argument1 = quadStack.top();
            //     quadStack.pop();
            // }

            std::string oper = currentValue;
            
            stepCounter++;

            std::string tStepCounter = "T" + std::to_string(stepCounter);
            std::string quadruple = "\n" + oper + "\t" + argument1 + "\t" + argument2 + "\t" + tStepCounter;

            quadExpression.append(quadruple);
            quadStack.push(tStepCounter);

        } else {

            quadStack.push(currentValue);
        }
    }
    std::cout << "Expresion: " << quadExpression << std::endl;
}

bool isOperator(std::string operato)
{
    if(operato == "+" || operato == "-" || operato == "*" || operato == "/" || operato == "^")
    {
        return true;
    }
    else
    {
        return false;
    }
}