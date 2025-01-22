#include<iostream>
#include<string>
#include <sstream>
#include <stdlib.h>
#include <iomanip>
using namespace std;
#define MAX 100
struct Stack{
	int top;
  string value[MAX];
};
int Push(Stack &s, string x){
  s.top++;
	s.value[s.top] = x;
  return 0;
}
//retrive the last char and pop it
string Pop(Stack &s){
	string x;
  x = s.value[s.top];
	s.top--;
  return x;
}
//judge whether this char is an operator
bool In(string s){
  if(s =="*" || s=="/" || s=="-" ||s=="+" || s=="("||s==")") return true;
  else return false;
}
//define the priority of each operator
int Prior(string x){
  if(x=="+"|| x=="-") return 0;
  else if(x=="*" || x=="/") return 1;
  else if(x=="(") return -1;
}

double calculate(string A, string B, string c){
  double a = atof(A.c_str());
  double b = atof(B.c_str());
  double result;
  if(c == "+") result = a + b;
  else if(c == "-") result = a - b;
  else if(c == "*") result = a * b;
  else if(c == "/") result = a / b;
  return result;
}

string double_to_string(double result){
  ostringstream outcome;
	outcome.precision(18);
  outcome<<result;
  return outcome.str();
}

//transfer infix to postfix
string Infix(string s){
  int i,j,k;
  string pop_item, keep,a ,b, outcome, merge, next, find, index;
	double result;
  Stack Data, Operator, Calculator;
	Data.top = -1;
	Operator.top = -1;
	Calculator.top = -1;
  // read all of the infix string
  for(i=0; i<s.size(); i++){
    char p = s[i];
    keep = p;
		if(In(keep) == false){
			for(j=i; j < s.size(); j++){
				char u = s[j];
				find = u;
				if(In(find)){
					break;
				}
			}
		}
		if (In(keep)==true){
		//if the index is an operator
			if(Operator.top == -1 || keep =="("){
				//if the Operator Stack is IsEmpty or the (
				Push(Operator,keep);
			}else if(keep==")"){
				//if encounter )
	      //need to pop all of the char in Operator
	      //until encounter '('
        while(Operator.top!= -1 && Operator.value[Operator.top]!="("){
					pop_item = Pop(Operator);
					Push(Data, pop_item);
				}
				//pop the '('
				Pop(Operator);
      }else{
      //compare the prior of the s[i] and oper.Top
      //if bigger or equal just Push
      //if smaller then pop until bigger than and add to data
        if(Prior(keep) <= Prior(Operator.value[Operator.top])){
					pop_item = Pop(Operator);
					Push(Data, pop_item);;
					while(Operator.top!=-1 && (Prior(keep)<=Prior(Operator.value[Operator.top]))){
						pop_item = Pop(Operator);
						Push(Data, pop_item);
					}
					Push(Operator, keep);
				}else{
					Push(Operator,keep);
				}
      }
    }else{
			//encounter a data or .
      if(i < j){
				merge = keep;
				for(k=i+1; k < j; k++){
					char d = s[k];
					index = d;
					merge = merge + index;
				}
        Push(Data, merge);
      }else{
        Push(Data, keep);
      }
			i = j-1;
    }
  }
  //if the Operator is not empty pop all of the operator and add to data
	while(Operator.top !=-1){
		pop_item = Pop(Operator);
		Push(Data, pop_item);
	}
	// for(i=0; i< s.size(); i++){
	// 	cout << Data.value[i]<< " ";
	// }
	// cout << endl;
  for(i=0; i<s.size(); i++){
    //if encounter operator
    if(In(Data.value[i])){
      b = Pop(Calculator);
      a = Pop(Calculator);
      result = calculate(a,b,Data.value[i]);
			outcome = double_to_string(result);
      Push(Calculator, outcome);;
    }else{
      Push(Calculator, Data.value[i]);
    }
  }
  return Calculator.value[0];
}

int main() {
	string final_result;
	string s;
	const char* str;
	str = "";
	// s = "1/3";
	getline(cin,s);
	// cout << s << endl;
	while(s.find(" ")!=-1){
    s = s.replace(s.find(" "), 1, str);
  }
	while(s.find("\t")!=-1){
		s = s.replace(s.find("\t"), 1, str);
	}
  final_result = Infix(s);
	double F = atof(final_result.c_str());
	cout << setprecision(18)<< F << endl;
  return 0;
}
