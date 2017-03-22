/*
* @Gülþen Eryiðit
* Student Name: Melis Gülenay
* Student ID : 150120304
* Date:  25.12.2016
*/


#include "Queue.h"
#include "Stack.h"

using namespace std;

string operatorList[] = {"abs", "sqrt", "sub", "div", "exp", "log", "mod", "sum", "product", "min", "max"};

Stack stackPostFix;
Stack stackOperants;
Queue queuePostFix;
Queue answerQueue;

string answer;


bool IsOperator(string operandPerformmed);
bool prefixToPostfix(string line);
bool makeOperation(string operatorExecuted, int index);

string dondur(long a) {
	char * t;
        sprintf(t,"%ld",a);
        string g (t);
	return g;
};


int main(int argc,char * argv[]) {
    string line, temp;
    string exit = "exit";
    answer = "0";

    if (argv[1] && strcmp(argv[1],"input.txt") == 0) {
        ifstream input(argv[1]);
        while (getline(input, line)){
            prefixToPostfix(line);
            input.clear();
        }
    }
    //else{
        cout<<"Initializing the interpreter..."<<endl<<endl;
        cout<<">> ";
        
        while (getline(cin, line)){
            if (line == exit) {
                cout<<"Terminating the interpreter..."<<endl;
                break;
            }
            if (prefixToPostfix(line)) {
                cout<<endl<<"Postfix string: ";
                while (!queuePostFix.empty()) {
                    cout<<queuePostFix.pop()<<" ";
                }
                cout<<endl;
                cout<<"Answer: "<<answer<<endl<<endl;
            }
            cout<<">> ";
            cin.clear();
        }
        
   // }

    cout<<"Answer queue: ";
    while (!answerQueue.empty()) {
        cout<<answerQueue.pop()<<" ";
    }
    return 0;
}


//Checking if the token is an operant or not.
bool IsOperator(string operandPerformmed){
    for (int i = 0; i < 11; i++) {
        if (operandPerformmed == operatorList[i]) {
            return true;
        }
    }
    return false;
}

//Converting the prefix to postfix
bool prefixToPostfix(string line){
    int i = 0;
    string token, popped, operant, temp;
    istringstream stringLine(line);
    while (true) {
        if(!stackPostFix.empty()){stackPostFix.pop();}
        else if(!stackOperants.empty()){stackOperants.pop();}
        else if(!queuePostFix.empty()){queuePostFix.pop();}
        else{ break;}
    }
    
    while (stringLine>>token) {
        if (token == ")") {
            if (stackPostFix.empty()) {
                cout<<"Syntax error. "<<endl<<endl;
                return false;
            }
            popped = stackPostFix.pop();
            
            i = 0;
            while(popped != "("){
                if (stackPostFix.empty()) {
                    cout<<"Syntax error. "<< endl<<endl;
                    return false;
                }
                else{
                    if(!IsOperator(popped)){
                        if (popped != "ans") {
                            stackOperants.push(popped);
                            i++;
                            queuePostFix.push(popped);
                            //cout<<popped<<" ";
                        }
                        else{
                            stackOperants.push(answer);
                            i++;
                            queuePostFix.push("ans");
                        }
                        
                    }
                    else{
                        //cout<<popped<<" ";
                        if(!makeOperation(popped, i)){
                            cout<<"Syntax error. "<<endl<<endl;
                            return false;
                        }
                        queuePostFix.push(popped);
                    }
                }
                //cout<<"popped"<<endl;
                popped = stackPostFix.pop();
            }
        }
        else{
            //cout<<"pushed"<<endl;
            stackPostFix.push(token);
        }
    }
    i = 0;
    while (!stackPostFix.empty()) {
        //cout<<"Last popped"<<endl;
        popped = stackPostFix.pop();
        if(!IsOperator(popped)){
            if (popped != "ans") {
                stackOperants.push(popped);
                i++;
                //cout<<popped<<" ";
                queuePostFix.push(popped);
            }
            else{
                stackOperants.push(answer);
            }
        }
        else{
            //cout<<popped<<" ";
            if(!makeOperation(popped, i)){
                cout<<"Syntax error. "<<endl<<endl;
                return false;
            }
            queuePostFix.push(popped);
        }
    }
    temp = stackOperants.pop();
    if(!stackOperants.empty()){
        cout<<"Syntax error. "<<endl<<endl;
        return false;
    }
    else{
        answer = temp;
        answerQueue.push(answer);
    }
    return true;
};

//Making Operation
bool makeOperation(string oper, int index){
    string *operants = new string[20];
    int i = 0;
    long result = 0, operant = 0;
    string stringOperand;
    
    //sum operation
    if (oper == "sum") {
        result = 0;
        operant = 0;
        i = 0;
        while (!stackOperants.empty()) {
            stringOperand = stackOperants.pop();
            if (stringOperand == "inf" || stringOperand == "-inf") {
                string inf = stringOperand;
                while (!stackOperants.empty()) {
                    stackOperants.pop();
                }

                stackOperants.push(inf);
                return true;
            }
            
   
            operant = atol(stringOperand.c_str());
            result += operant;
        }
        if (result == operant) {
            return false;
        }
        //cout<<endl<<"sum = "<< result<<endl;
        char * t;
        sprintf(t,"%ld",result);
        string g (t);
        stackOperants.push(g);
        delete [] operants;
        return true;
    }
    
    //exponent operation
    if (oper == "exp") {
        result = 0;
        operant = 0;
        i = 0;
        while (!stackOperants.empty()) {
            stringOperand = stackOperants.pop();
            if (stringOperand == "-inf") {
                return false;
            }
            else{
                operants[i] = stringOperand;
            }
            queuePostFix.pop();
            i++;
            if (i == 2) {
                break;
            }
        }
        
        if(i == 1){
            if (operants[0] == "inf") {
                stackOperants.push("inf");
                queuePostFix.push("inf");
            }
            else{
                result = exp(atoi(operants[0].c_str()));
                queuePostFix.push(operants[0]);
                stackOperants.push(dondur(result));
            }
        }
        if (i == 2) {
            if (operants[0] != "inf" || operants[0] != "inf") {
                stackOperants.push("inf");
            }
            else{
                result = pow(atoi(operants[0].c_str()), atoi(operants[1].c_str()));
                stackOperants.push(dondur(result));
            }
            queuePostFix.push(operants[0]);
            queuePostFix.push(operants[1]);
        }
        if (i == 0) {
            return false;
        }
        //cout<<endl<<"exp = "<< result<<endl;

        delete [] operants;
        return true;
    }
    
    //sqrt operation
    if (oper == "sqrt") {
        result = 0;
        operant = 0;
        if (stackOperants.empty()) {
            return false;
        }
        else{
            stringOperand = stackOperants.pop();
            if (stringOperand == "-inf" || stringOperand == "inf") {
                if (stringOperand == "-inf") {
                    return false;
                }
                stackOperants.push(stringOperand);
                return true;
            }
            operant = atol(stringOperand.c_str());
            result = sqrt(operant);
            //cout<<endl<<"sqrt = "<< result<<endl;
            stackOperants.push(dondur(result));
            return true;
        }
    }
    
    //abs operation
    if (oper == "abs") {
        result = 0;
        operant = 0;
        if (stackOperants.empty()) {
            return false;
        }
        else{
            stringOperand = stackOperants.pop();
            if (stringOperand == "-inf" || stringOperand == "inf") {
                if (stringOperand == "-inf") {
                    stringOperand = "inf";
                }
                stackOperants.push(stringOperand);
                return true;
            }
            operant = atoi(stringOperand.c_str());
            result = abs(operant);
            stackOperants.push(dondur(result));
            delete [] operants;
            return true;
        }
    }
    
    //product operation
    if (oper == "product") {
        result = 1;
        operant = 1;
        while (!stackOperants.empty()) {
            stringOperand = stackOperants.pop();
            if (stringOperand == "inf" || stringOperand == "-inf") {
                string inf = stringOperand;
                while (!stackOperants.empty()) {
                    stackOperants.pop();
                }
                stackOperants.push(inf);
                return true;
            }
            operant = atol(stringOperand.c_str());
            result *= operant;
        }
        if (result == operant) {
            return false;
        }
        delete [] operants;
        //cout <<"Product: "<<result<<endl;
        stackOperants.push(dondur(result));
        return true;
    }
    
    //min opearation
    if (oper == "min") {
        result = LONG_MAX;
        operant = 0;
        while (!stackOperants.empty()) {
            stringOperand = stackOperants.pop();
            if (stringOperand == "inf" || stringOperand == "-inf") {
                if (stringOperand == "inf") {
                    continue;
                }
                string inf = stringOperand;
                while (!stackOperants.empty()) {
                    stackOperants.pop();
                }
                stackOperants.push(inf);
                return true;
            }
            operant = atol(stringOperand.c_str());
            if (operant < result) {
                result = operant;
            }
        }
        if (result == LONG_MAX) {
            return false;
        }
        delete [] operants;
        stackOperants.push(dondur(result));
        return true;
    }
    
    //max opearation
    if (oper == "max") {
        result = LONG_MIN;
        operant = 0;
        while (!stackOperants.empty()) {
            stringOperand = stackOperants.pop();
            if (stringOperand == "inf" || stringOperand == "-inf") {
                if (stringOperand == "-inf") {
                    continue;
                }
                string inf = stringOperand;
                while (!stackOperants.empty()) {
                    stackOperants.pop();
                }
                stackOperants.push(inf);
                return true;
            }
            operant = atol(stringOperand.c_str());
            if (operant > result) {
                result = operant;
            }
        }
        if (result == LONG_MIN) {
            return false;
        }
        delete [] operants;
        stackOperants.push(dondur(result));
        return true;
    }
    
    //log operation
    if (oper == "log") {
        result = 0;
        i = 0;
        operant = 0;
        while (!stackOperants.empty()) {
            stringOperand = stackOperants.pop();
            if (stringOperand == "-inf") {
                return false;
            }
            operant = atol(stringOperand.c_str());
            
            operants[i] = stringOperand;
            if (operant <= 0) {
                return false;
            }
            i++;
            if (i == 2) {
                break;
            }
        }
        if(i == 1){
            if (operants[0] == "inf") {
                stackOperants.push(operants[0]);
            }
            else{
                result = log(atoi(operants[0].c_str()));
                stackOperants.push(dondur(result));
            }
        }
        if (i == 2) {
            if (operants[0] == "inf" || operants[1] == "inf") {
                stackOperants.push("inf");
            }
            else{
                if (index == 2) {
                    result = log(atoi(operants[0].c_str())) / log(atoi(operants[1].c_str()));
                    stackOperants.push(dondur(result));
                }
                else if (index == 1) {
                    result = log(atoi(operants[1].c_str())) / log(atoi(operants[0].c_str()));
                    stackOperants.push(dondur(result));
                }
                else{
                    return false;
                }
            }
        }
        if (i == 0) {
            return false;
        }
        delete [] operants;
        return true;
    }
    
    //mod operation
    if (oper == "mod") {
        result = 0;
        i = 0;
        while (!stackOperants.empty()) {
            stringOperand = stackOperants.pop();
            if (stringOperand == "inf" || stringOperand == "-inf") {
                return false;
            }
            operants[i] = stringOperand;
            if (atoi(operants[i].c_str()) <= 0) {
                return false;
            }
            i++;
            if (i == 2) {
                break;
            }
        }
        if(i == 1){
            result = atoi(operants[0].c_str()) % 10;
        }
        if (i == 2) {
            if (index == 2 && atoi(operants[0].c_str()) != 0) {
                cout<<"index : "<<index<<endl;
                result = atoi(operants[0].c_str()) % atoi(operants[1].c_str());
            }
            else if (index == 1 && atoi(operants[1].c_str()) != 0) {
                cout<<"index : "<<index<<endl;
                result = atoi(operants[1].c_str()) % atoi(operants[0].c_str());
            }
            else{
                return false;
            }
        }
        if (i == 0) {
            return false;
        }
        //cout<<endl<<"mod = "<< result<<endl;
        stackOperants.push(dondur(result));
        return true;
    }
    
    //sub operation
    if (oper == "sub") {
        result = 0;
        i = 0;
        while (!stackOperants.empty()) {
            stringOperand = stackOperants.pop();
            operants[i] = stringOperand;
            i++;
            if (i == 2) {
                break;
            }
        }
        if (i == 2) {
            if (operants[0] == "inf" || operants[0] == "-inf") {
                stackOperants.push(operants[0]);
            }
            else if(operants[1] == "inf" || operants[1] == "-inf"){
                if (operants[1] == "inf") {
                    stackOperants.push("-inf");
                }
                else{
                    stackOperants.push("inf");
                }
            }
            else{
                if (index == 2) {
                    result = atoi(operants[0].c_str()) - atoi(operants[1].c_str());
                    stackOperants.push(dondur(result));
                }
                else if (index == 1) {
                    result = atoi(operants[1].c_str()) - atoi(operants[0].c_str());
                }
                else{
                    return false;
                }
            }
        }
        else{
            return false;
        }
        delete [] operants;
        return true;
    }
    
    //div operation
    if (oper == "div") {
        result = 0;
        i = 0;
        while (!stackOperants.empty()) {
            stringOperand = stackOperants.pop();
            operants[i] = stringOperand;
 
            i++;
            if (i == 2) {
                break;
            }
        }
        if (i == 2) {
            if (operants[0] == "inf" || operants[0] == "-inf") {
                stackOperants.push(operants[0]);
            }
            else if(operants[1] == "inf" || operants[1] == "-inf"){
                stackOperants.push("0");
            }
            else{
                if (index == 2 && atoi(operants[1].c_str()) != 0) {
                    result = atoi(operants[0].c_str()) / atoi(operants[1].c_str());
                }
                else if (index == 1 && atoi(operants[0].c_str()) != 0) {
                    result = atoi(operants[1].c_str()) / atoi(operants[0].c_str());
                }
                else{
                    return false;
                }
                stackOperants.push(dondur(result));
            }
            
        }
        else{
            return false;
        }
        //cout<<endl<<"div = "<< result<<endl;
        delete [] operants;
        return true;
    }

    return true;
};


