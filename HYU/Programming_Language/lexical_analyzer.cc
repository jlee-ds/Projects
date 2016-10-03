// PL homework: calculator
// lexical_ananlyzer.cc

#include "lexical_analyzer.h"
#include <stdio.h>

const char ALPHA = 'A';  // A-Z,a-z,_
const char DIGIT = '0';  // 0-9

//DFA 배열. 행값은 현재 STATE를 열값은 현재 검사하는 문자를 그리고 그 표의 해당하는 값은 다음 STATE를 상징한다.
const int DFA[19][13] = {{2,1,2,5,8,9,11,3,10,4,7,6,-1},
						{12,1,13,14,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						{2,2,2,12,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						{-1,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						{-1,16,-1,-1,17,17,-1,-1,-1,-1,-1,-1,-1},
						{-1,14,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						{-1,15,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						{-1,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						{-1,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
						{-1,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};

struct TableElement {
  int state;
  char input_char;
  int next_state;
};

// Define the finite state machine table here.

LexicalAnalyzer::LexicalAnalyzer() {
}

LexicalAnalyzer::~LexicalAnalyzer() {
}

void LexicalAnalyzer::SetInputString(const std::string& input_string) {
  str_ = input_string;
  index_ = 0;
}

Token LexicalAnalyzer::Lex() {
  // Implement Lex() function body here.
	char input_char;
	int input_int;
	int now_state = 0;
	int start_index_;
    int next_state = 0;

  //토큰 스트링 초기화.
    token_string_.clear();

  //스트링을 다 검사했으면 EOS를 리턴한다.
    if(index_>=str_.length()) return EOS;
    while(str_.at(index_)==' '){
    	index_++;
    	if(index_==str_.length()) return EOS;
    }

  //입력 스트링에서 각 인덱스에 해당하는 문자를 받아서 어떤 문자에 해당하는 지 검사하여 배열번호에 맞게 숫자를 매치한다.
  
    do{
        now_state = next_state;
	    input_char = str_.at(index_);
	    if((input_char>='A'&&input_char<='Z')||(input_char>='a'&&input_char<='z')||input_char=='_'){
	    	if(input_char=='E'||input_char=='e') input_int = 2;
	    	else input_int = 0;
	    }else if(input_char>='0'&&input_char<='9') input_int = 1;
	    else if(input_char=='.') input_int = 3; 
	    else if(input_char=='+') input_int = 4;
	    else if(input_char=='-') input_int = 5;
	    else if(input_char=='*') input_int = 6;
	    else if(input_char=='/') input_int = 7;
	    else if(input_char=='^') input_int = 8;
	    else if(input_char=='=') input_int = 9;
	    else if(input_char=='(') input_int = 10;
	    else if(input_char==')') input_int = 11;
        else if(input_char==' '){
        	input_int = 12;
        	index_++;
        }
	    else{
            index_++;
            token_string_.append(str_, index_, 1);
            return ERROR;
        }

  		//검사한 문자로 매치된 열의 숫자로 다음 스테이트를 검사한다.
      	if(DFA[now_state][input_int]!=-1){	//만약에 해당 문자에 해당하는 다음 스테이트가 있다면
		    next_state = DFA[now_state][input_int];  //다음 스테이트로 이동하고
		    token_string_.append(str_, index_, 1);	//해당 문자를 토큰스트링에 붙이고
		   	
            index_=index_+1;
		}								//index_를 한 칸 증가시킨다.
	}while((DFA[now_state][input_int]!=-1) && index_<str_.length());

    now_state = next_state;
	//if(DFA[now_state][input_int]==-1){
	    if(now_state==0||now_state==5||now_state==12||now_state==13||now_state==17) //NON-final_state
			return ERROR;
	   	else if(now_state==1||now_state==14||now_state==15||now_state==16||now_state==18) //NUMBER
			return NUMBER;
	 	else if(now_state==2){ //ID
	  		if(token_string_.compare("list")==0) return CMD_LIST;
	        else if(token_string_.compare("exit")==0) return CMD_EXIT;
	        else if(token_string_.compare("clear")==0) return CMD_CLEAR;
	        else return ID;
	    }
	    else if(now_state==8) //OP_PLUS
	    	return OP_PLUS;
	    else if(now_state==9) //OP_MINUS
	    	return OP_MINUS;
	    else if(now_state==11) //OP_MUL
	    	return OP_MUL; 
	    else if(now_state==3) //OP_DIV
	    	return OP_DIV; 
	    else if(now_state==10) //OP_POW
	    	return OP_POW; 
	    else if(now_state==4) //OP_ASSIGN
	    	return OP_ASSIGN; 
	    else if(now_state==7) //OP_LPAREN
	    	return OP_LPAREN; 
	    else if(now_state==6) //OP_RPAREN
	    	return OP_RPAREN;   
	//}
    /*else{
        index_++;
        return ERROR;
    }*/
}

