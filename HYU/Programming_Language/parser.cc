// PL homework: calculator
// parser.cc

#include <iostream>
#include "parser.h"
#include <cstdlib>
#include <sstream>
#include <stack>  //stack을 사용하자!
#include <cmath>  //수학적인 계산을 위해서 ㅇㅇ...
#include <stdlib.h>  //exit()함수를 위해서

using namespace std;

/*
//column :  0-EOS, 1-id, 2-num, 3-cmd, 4-"=", 5-"+", 6-"-", 7-"*", 
          //8-"/", 9-"^", 10-"(", 11-")", 12-"S", 13-"E", 14-"T", 15-"F", 16-"B"
const string LRtable[33][17]={
  {"**","S03","S10","S02","N","S08","S09","N","N","N","S11","N","01","04","05","06","07"},//0
  {"**","N","N","N","N","N","N","N","N","N","N","N","N","N","N","N","N"},//1
  {"R01","N","N","N","N","N","N","N","N","N","N","N","N","N","N","N","N"},//2
  {"R16","N","N","N","S12","R16","R16","R16","R16","R16","N","R16","N","N","N","N","N"},//3
  {"R03","N","N","N","N","S13","S14","N","N","N","N","N","N","N","N","N","N"},//4
  {"R06","N","N","N","N","R06","R06","S15","S16","N","N","R06","N","N","N","N","N"},//5
  {"R09","N","N","N","N","R09","R09","R09","R09","N","N","R09","N","N","N","N","N"},//6
  {"R10","N","N","N","N","R10","R10","R10","R10","S17","N","R10","N","N","N","N","N"},//7
  {"N","S20","S10","N","N","N","N","N","N","N","S11","N","N","N","N","N","18"},//8
  {"N","S20","S10","N","N","N","N","N","N","N","S11","N","N","N","N","N","19"},//9
  {"R17","N","N","N","N","R17","R17","R17","R17","R17","N","R17","N","N","N","N","N"},//10
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","21","05","06","07"},//11
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","22","05","06","07"},//12
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","N","23","06","07"},//13
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","N","24","06","07"},//14
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","N","N","25","07"},//15
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","N","N","26","07"},//16
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","N","N","27","07"},//17
  {"R12","N","N","N","N","R12","R12","R12","R12","S28","N","R12","N","N","N","N","N"},//18
  {"R14","N","N","N","N","R14","R14","R14","R14","S29","N","R14","N","N","N","N","N"},//19
  {"R16","N","N","N","N","R16","R16","R16","R16","R16","N","R16","N","N","N","N","N"},//20
  {"N","N","N","N","N","S13","S14","N","N","N","N","S30","N","N","N","N","N"},//21
  {"R02","N","N","N","N","S13","S14","N","N","N","N","N","N","N","N","N","N"},//22
  {"R04","N","N","N","N","R04","R04","S15","S16","N","N","R04","N","N","N","N","N"},//23
  {"R05","N","N","N","N","R05","R05","S15","S16","N","N","R05","N","N","N","N","N"},//24
  {"R07","N","N","N","N","R07","R07","R07","R07","N","N","R07","N","N","N","N","N"},//25
  {"R08","N","N","N","N","R08","R08","R08","R08","N","N","R08","N","N","N","N","N"},//26
  {"R11","N","N","N","N","R11","R11","R11","R11","N","N","R11","N","N","N","N","N"},//27
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","N","N","31","07"},//28
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","N","N","32","07"},//29
  {"R18","N","N","N","N","R18","R18","R18","R18","R18","N","R18","N","N","N","N","N"},//30
  {"R13","N","N","N","N","R13","R13","R13","R13","N","N","R13","N","N","N","N","N"},//31
  {"R15","N","N","N","N","R15","R15","R15","R15","N","N","R15","N","N","N","N","N"}//32
};  //LRTABLE 노가다...
const string MG[19][2] = { {".","."},
  {"S","CMD"},{"S","ID"},{"S","E"},{"E","E"},{"E","E"},{"E","T"},{"T","T"},{"T","T"},{"T","F"},
  {"F","B"},{"F","B"},{"F","+"},{"F","+"},{"F","-"},{"F","-"},{"B","ID"},{"B","NUMBER"},{"B","("}
};  //그래머를 Lvalue와 follow로 나눠서 간단하게 저장하였다.
-------------------------------------------------------------------------위의 테이블은 일반과제
-----------------------------------------아래는 추가과제 1번을 추가한 테이블---------------------*/
//grammar 19. B -> id ( E )를 LRtable 과 gototable에 추가하였다. 추가는 그냥 생각으로... 로우몇개더 추가했습니다.
//column :  0-EOS, 1-id, 2-num, 3-cmd, 4-"=", 5-"+", 6-"-", 7-"*", 
          //8-"/", 9-"^", 10-"(", 11-")", 12-"S", 13-"E", 14-"T", 15-"F", 16-"B"
const string LRtable[36][17]={
  {"**","S03","S10","S02","N","S08","S09","N","N","N","S11","N","01","04","05","06","07"},//0
  {"**","N","N","N","N","N","N","N","N","N","N","N","N","N","N","N","N"},//1
  {"R01","N","N","N","N","N","N","N","N","N","N","N","N","N","N","N","N"},//2
  {"R16","N","N","N","S12","R16","R16","R16","R16","R16","S33","R16","N","N","N","N","N"},//3
  {"R03","N","N","N","N","S13","S14","N","N","N","N","N","N","N","N","N","N"},//4
  {"R06","N","N","N","N","R06","R06","S15","S16","N","N","R06","N","N","N","N","N"},//5
  {"R09","N","N","N","N","R09","R09","R09","R09","N","N","R09","N","N","N","N","N"},//6
  {"R10","N","N","N","N","R10","R10","R10","R10","S17","N","R10","N","N","N","N","N"},//7
  {"N","S20","S10","N","N","N","N","N","N","N","S11","N","N","N","N","N","18"},//8
  {"N","S20","S10","N","N","N","N","N","N","N","S11","N","N","N","N","N","19"},//9
  {"R17","N","N","N","N","R17","R17","R17","R17","R17","N","R17","N","N","N","N","N"},//10
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","21","05","06","07"},//11
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","22","05","06","07"},//12
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","N","23","06","07"},//13
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","N","24","06","07"},//14
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","N","N","25","07"},//15
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","N","N","26","07"},//16
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","N","N","27","07"},//17
  {"R12","N","N","N","N","R12","R12","R12","R12","S28","N","R12","N","N","N","N","N"},//18
  {"R14","N","N","N","N","R14","R14","R14","R14","S29","N","R14","N","N","N","N","N"},//19
  {"R16","N","N","N","N","R16","R16","R16","R16","R16","S33","R16","N","N","N","N","N"},//20
  {"N","N","N","N","N","S13","S14","N","N","N","N","S30","N","N","N","N","N"},//21
  {"R02","N","N","N","N","S13","S14","N","N","N","N","N","N","N","N","N","N"},//22
  {"R04","N","N","N","N","R04","R04","S15","S16","N","N","R04","N","N","N","N","N"},//23
  {"R05","N","N","N","N","R05","R05","S15","S16","N","N","R05","N","N","N","N","N"},//24
  {"R07","N","N","N","N","R07","R07","R07","R07","N","N","R07","N","N","N","N","N"},//25
  {"R08","N","N","N","N","R08","R08","R08","R08","N","N","R08","N","N","N","N","N"},//26
  {"R11","N","N","N","N","R11","R11","R11","R11","N","N","R11","N","N","N","N","N"},//27
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","N","N","31","07"},//28
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","N","N","32","07"},//29
  {"R18","N","N","N","N","R18","R18","R18","R18","R18","N","R18","N","N","N","N","N"},//30
  {"R13","N","N","N","N","R13","R13","R13","R13","N","N","R13","N","N","N","N","N"},//31
  {"R15","N","N","N","N","R15","R15","R15","R15","N","N","R15","N","N","N","N","N"},//32
  {"N","S20","S10","N","N","S08","S09","N","N","N","S11","N","N","34","05","06","07"},//33
  {"N","N","N","N","N","S13","S14","N","N","N","N","S35","N","N","N","N","N"},//34
  {"R19","N","N","N","N","R19","R19","R19","R19","R19","N","R19","N","N","N","N","N"}//35
};  //LRTABLE 노가다...
const string MG[20][2] = { {".","."},
  {"S","CMD"},{"S","ID"},{"S","E"},{"E","E"},{"E","E"},{"E","T"},{"T","T"},{"T","T"},{"T","F"},
  {"F","B"},{"F","B"},{"F","+"},{"F","+"},{"F","-"},{"F","-"},{"B","ID"},{"B","NUMBER"},{"B","("},
  {"B","ID"}
};  //그래머를 Lvalue와 follow로 나눠서 간단하게 저장하였다.
int row_num;  //stack.top을 이용
int column_num;  //칼럼값 (token을 이용)
stack<std::string> S_real;  //실제 계산할 값들의 스택이다. 
std::map<std::string,double> var_map;  
//해당하는 변수에 해당하는 값을 연결하는 것을 map이라는 API로 해결했다.
std::map<std::string,double>::iterator it;
//map을 가르키는 것.? 포인터라고 생각하면 될 것같다.

Parser::Parser() {
  // TODO(optional): Load the parsing table in the constructor. 옵션이라 다행.. 이거보고식겁했습니다.. 
}

Parser::~Parser() {
}

bool Parser::ParseInputString(const std::string& input_string) {
  lexer_.SetInputString(input_string);
  // TODO: Make this function do the parsing.
  // The placeholder below just calls OnShift for all tokens then OnAccept.
  Token token = ERROR;
  int gotonum;  //이동할때 다음 스테이트를 숫자로 저장할 변수.
  int gram_num;  //해당하는 그래머를 숫자로 저장할 변수.
  int R_row_num;  //그래머의 오른쪽 값들에 따라 팝하고 남은 스테이트를 저장할 변수. (그래머제거후어딜갈지정할때사용)
  bool parse_er = 0;  //파싱에러가 일어났는 지 확인하는 플래그 변수.
  bool var_er = 1;    //맵핑에러가 떳는지 확인하는 플래그변수.
  //해당하는 변수가 있으면 0, 없어서 에러가 뜨면 1이다.
  std::string LRstr_;  //테이블의 값을 저장
  std::string S_top;  //스택탑의 값을 저장
  std::string goto_str;  //다음 스테이지의 값을 스트링으로 저장한다 (스택에 넣기위해)
  std::string push_str;  //스택에 넣을 토큰을 저장한다.
  std::string follow_str;  //그래머에서 알밸류 맨처음 값을 저장한다. 이 값이 나올 때까지 팝한다.
  std::string L_value_str;  //follow_str까지 팝한후 스택탑과 그래머의 엘밸류를 비교해서 다음 스테이트를 정한다.
  int L_value_num;  //그래머의 L밸류에 따라서 해당하는 테이블의 칼럼값을 저장하는 변수
  std::string LR_togo;  //그래머를 없앤 후 다음 스테이트를 저장하는 변수.
  stack<string> S;  //stack. name is S.
  

  S.push("0");  //스택초기화. 0을 집어넣는다.

  token = lexer_.Lex();  //맨 처음에 일단 토큰이 먼지 가져온다.

  do {

    S_top = S.top();
    row_num = atoi(&S_top.at(0));  //스택의 탑의 값을 (현재스테이트)를 테이블의 로우값으로 이용한다.

    if (token == ERROR) {  //토큰이 에러면 바로 렉시컬_에러를 출력한다.
      OnLexerError();
    } else {  //에러가 아니고 정상적인 토큰이면  
      //테이블의 칼럼때문에 여러단계로 나눠져 있다. 해당하는 토큰을 해당하는 칼럼에 맞게 일대일 대응시켰다.
      if (token == ID || token == NUMBER || token == EOS) {  
        column_num = token;
        if (column_num == 1) push_str = "ID";  //각 토큰에 따라서 S00가 나올 경우 스택에 집어넣을 문자
        else push_str = "NUMBER";               //를 push_str에 저장한다.
      } else if (token == CMD_EXIT || token == CMD_LIST || token == CMD_CLEAR) {
        column_num = 3;
        push_str = "CMD";
      } else if (token >= 10 && token <=17) {
        column_num = token - 5;
        switch (token) {
          case 10 : push_str = "+"; break;
          case 11 : push_str = "-"; break;
          case 12 : push_str = "*"; break;
          case 13 : push_str = "/"; break;
          case 14 : push_str = "^"; break;
          case 15 : {
            push_str = "=";
            column_num = 4;
          } break;
          case 16 : {
            push_str = "(";
            column_num = 10;
          } break;
          case 17 : {
            push_str = ")";
            column_num = 11;
          } break;
        }
      }  //여기까지가 각 토큰에 따른 테이블 칼럼값과 스택에 넣을 문자를 일대일 대응으로 골라주는 코드이다.
      //이제 대응된 칼럼값과 push_str를 이용하여 S_operation과 R_operation을 실행하는 부분이다.
      LRstr_ = LRtable[row_num][column_num];  //테이블에 해당하는 값을 읽어온다.
      //S-operation일 경우  
      if (LRstr_.at(0) == 'S') {
        gotonum = atoi(&LRstr_.at(1)); //S다음에 오는 문자(다음스테이트)를 숫자로 바꾼다.
        ostringstream gs;
        gs << gotonum;
        goto_str = gs.str();  //숫자로 바꾼것을 다시 문자로... (왜? 스택에 넣을라고요 ㅎㅎ..)
        //cout << goto_str << "\n";
        OnShift(token, lexer_.GetTokenString(), gotonum);  //해당하는 스테이트로 이동한다는 메세지
        S.push(push_str);
        S.push(goto_str);   //해당하는 push_str와 이동하려는 스테이트 값을 스택에 차례로 푸쉬푸쉬!
        token = lexer_.Lex();  //S를 실행한 경우에는 다음 토큰을 읽어야하니 교수님이 짜주신 렉스렉스!

      //R-operation의 경우
      } else if (LRstr_.at(0) == 'R') {
        gram_num = atoi(&LRstr_.at(1));  //R다음의 숫자. 해당하는 그래머를 숫자로 바꾼다.
        L_value_str = MG[gram_num][0];  //해당하는 그래머의 처음문자 (L_value)를 저장
        //cout << L_value_str;
        if (L_value_str.at(0) == 'S') L_value_num = 12;
        else if (L_value_str.at(0) == 'E') L_value_num = 13;
        else if (L_value_str.at(0) == 'T') L_value_num = 14;
        else if (L_value_str.at(0) == 'F') L_value_num = 15;
        else if (L_value_str.at(0) == 'B') L_value_num = 16;  //해당하는 값에 따른 칼럼을 일대일대응!
        follow_str = MG[gram_num][1];  //해당하는 그래머의 두번째 문자 follow_str!
        //cout << follow_str;
        S_top = S.top();  //S.top()이걸로 바로 메소드를 못써서요.. 번거러운 방법을 택했습니다.
        while(S_top.compare(follow_str)!=0){  //팔로우값이 나올 떄 까지 팝팝!!!
          S.pop();
          S_top = S.top();
        }
        /*-------------------------------------------
        추가설명
        왜! E -> E + E와 같은 그래머에서는 위와같은 방법이 통하지 않음에도 불구하고!
        위와 같은 방법을 택했나!
        제 생각에 하나의 오른쪽 익스프레션에 두개의 같은 넌터미널이 있으면 앰비규어스 해져서
        그러한 그래마는 엘알파서에서 안 쓸거 같아서 그리했습니다!.. 아니면 죄송합니다... 머리가 딸려서..
        */
        S.pop();  //아직 남아있는 팔로우 값마저 팝!
        S_top = S.top();  //이제 남아있는 것은 스테이트값이다! 그것을 읽어와서!
        //cout << S_top;
        R_row_num = atoi(&S_top.at(0));  //고투테이블의 로우값으로 지정!
        LR_togo = LRtable[R_row_num][L_value_num];  //고투테이블에 로우값과 해당하는 엘밸류 칼럼값으로 접근!
        S.push(L_value_str);  //해당하는 엘밸류값을 푸쉬!
        S.push(LR_togo);  //해당하는 고투테이블의 값을 다음 스테이트로 푸쉬!
        S_top = S.top();  //이제 탑이된 (다음 스테이트)를
        var_er = OnReduce(gram_num, atoi(&S_top.at(0)));  //onReuduce함수의 파라미터로 투척!
        if(var_er==true) break;     //리듀스 도중에 에러가 발생하면 와일문을 탈출.
      //N이라면 == NULL, 값이 없다면!
      } else if (LRstr_.at(0) == 'N') {
        OnParseError(); 
        parse_er = 1;  //파싱에러플래그를 1로 바꾸고
        break;  //파싱에러다. 바로 브레이크로 탈출!
      } else if (LRstr_.at(0) == '*') break;  //어셉트! 브레이크!
    }
  } while (token != ERROR);  //에러여도 탈출!
  if (token != ERROR && parse_er != 1 && var_er==false) {  //에러거나 파싱에러면 어셉트를 출력 ㄴㄴ한다.
    //OnAccept();
  }
  return (token == EOS);  
}

// Do not change the handlers for this homework.

bool Parser::OnShift(Token token, const string& token_string, int next_state) {
  S_real.push(token_string);
  // 각 토큰을 리얼 스택에 넣는다. 
  //  리얼 스택은 각 과정에서의 실제값들을 다룬다.
  //  각 룰을 처리할 때 빼내어 연산을 처리하고 그 값을 다시 넣어주는 식으로 계산한다.
  //cout << "  S" << next_state << "[" << token << ":" << token_string << "]";
  return true;
}

bool Parser::OnReduce(int rule, int next_state) {
  //cout << "  R" << rule << "," << next_state;
  std::string CMD;
  std::string ID;
  std::string NUM;
  std::string E;
  std::string T;
  std::string F;
  std::string B;    //임시저장 변수들이다. 


  //아래부터는 각 룰을 처리하는 부분이다.
  //어떻게 해야할지 모르겠어서 그냥 1번 룰부터 처리가 필요한 룰들을 이프문으로 나열했다.

  if(rule == 1){  //S->cmd
    CMD = S_real.top();  
    S_real.pop();
    //탑의 토큰 == 명령어를 꺼내어서 각 경우에 따라 이프문을 돌린다.
    if(CMD=="exit"||CMD=="quit"){
      //cout << '\n' ;
      exit(0);  //종료
    } 
    else if(CMD=="clear") var_map.clear();  //변수맵을 초기화한다.
    else if(CMD=="list"){
      for(it = var_map.begin(); it != var_map.end(); ++it)
        std::cout << "  " << it->first << " => " << it->second << '\n' ;
    }  //변수맵의 시작부터 끝가지 해당하는 모든 값을 출력한다.

  }else if(rule == 2){  //S->id=E
    std::pair<std::map<std::string,double>::iterator,bool> reset;
    E = S_real.top();   S_real.pop();   S_real.pop();
    ID = S_real.top();  S_real.pop();
    //해당하는 변수이름과 값을 꺼내서 맵핑을 시킨다.
    reset = var_map.insert(std::pair<std::string,double>(ID,string_to_double(E)));
    //값을 인설트한다.
    if(reset.second == false){  //만약에 실패하면 == 이미 해당변수가 맵핑되어있으면
      var_map.erase(ID);  //지워버리고
      var_map.insert(std::pair<std::string,double>(ID,string_to_double(E)));  //다시맵핑.
    }
    cout << "  UPDATE THE VALUE \'" << ID << "\' TO \'" << string_to_double(E) << "\'\n" ;
  
  }else if(rule == 3){  //S->E
    E = S_real.top();
    S_real.pop();
    cout << "  RESULT : " << string_to_double(E) << '\n' ;  //해당하는 연산의 값을 출력한다.

  }else if(rule == 4){ //E->E+T
    double tmp;
    ostringstream gs; 
    T = S_real.top();   S_real.pop();   S_real.pop();
    E = S_real.top();   S_real.pop();
    tmp = string_to_double(E) + string_to_double(T);  //꺼내서 더한다. 
    gs << tmp;
    E = gs.str();  //다시 스트링으로 바꿔서 
    S_real.push(E);  //스택에 해당 결과를 넣는다.
  }else if(rule == 5){  //E->E-T
    double tmp;
    ostringstream gs; 
    T = S_real.top();   S_real.pop();   S_real.pop();
    E = S_real.top();   S_real.pop();
    tmp = string_to_double(E) - string_to_double(T);
    gs << tmp;
    E = gs.str();
    S_real.push(E);
  }else if(rule == 7){   //T->T*F
    double tmp;
    ostringstream gs; 
    F = S_real.top();   S_real.pop();   S_real.pop();
    T = S_real.top();   S_real.pop();
    tmp = string_to_double(T) * string_to_double(F);
    gs << tmp;
    T = gs.str();
    S_real.push(T);
  }else if(rule == 8){   //T->T/F
    double tmp;
    ostringstream gs; 
    F = S_real.top();   S_real.pop();   S_real.pop();
    T = S_real.top();   S_real.pop();
    tmp = string_to_double(T) / string_to_double(F);
    gs << tmp;
    T = gs.str();
    S_real.push(T);
  }else if(rule == 11){   //F->B^F
    double tmp;
    ostringstream gs; 
    F = S_real.top();   S_real.pop();   S_real.pop();
    B = S_real.top();   S_real.pop();
    tmp = pow(string_to_double(B), string_to_double(F));
    gs << tmp;
    F = gs.str();
    S_real.push(F);
  }else if(rule == 12){   //F->+B
    double tmp;
    ostringstream gs; 
    B = S_real.top();   S_real.pop();   S_real.pop();
    tmp = 0 + string_to_double(B);
    gs << tmp;
    F = gs.str();
    S_real.push(F);
  }else if(rule == 13){   //F->+B^F
    double tmp;
    ostringstream gs; 
    F = S_real.top();   S_real.pop();   S_real.pop();
    B = S_real.top();   S_real.pop();   S_real.pop();
    tmp = 0 + pow(string_to_double(B), string_to_double(F));
    gs << tmp;
    F = gs.str();
    S_real.push(F);
  }else if(rule == 14){   //F->-B
    double tmp;
    ostringstream gs; 
    B = S_real.top();   S_real.pop();   S_real.pop();
    tmp = 0 - string_to_double(B);
    gs << tmp;
    F = gs.str();
    S_real.push(F);
  }else if(rule == 15){   //F->-B^F
    double tmp;
    ostringstream gs; 
    F = S_real.top();   S_real.pop();   S_real.pop();
    B = S_real.top();   S_real.pop();   S_real.pop();
    tmp = 0 - pow(string_to_double(B), string_to_double(F));
    gs << tmp;
    F = gs.str();
    S_real.push(F);
    //여기까지는 모두 같다.

  }else if(rule == 16){  //B->ID
    double tmp;
    ostringstream gs; 
    ID = S_real.top();  S_real.pop();
    it = var_map.find(ID);  //찾는다. 만약에 찾는 데 실패하면 it는 맵의 맨끝을 가르키게 된다.
    if(it == var_map.end()){  //못찾으면.
      cout << "  ParseError (var not found)" << endl;  
      return true;  //에러를 출력하고 트루를 리턴한다. 이값은 위에서 Var_er라는 에러플래그를 1로 만든다.
    }else{  //찾으면
      tmp = it->second;
      gs << tmp;
      B = gs.str();
      S_real.push(B);  //해당하는 변수에 맞는 값을 꺼내서 스트링으로 바꾼 뒤 푸쉬한다.
    }
  }else if(rule == 18){ //B -> (E) 
    double tmp;
    S_real.pop();       E = S_real.top();   S_real.pop();   S_real.pop();
    S_real.push(E);  //괄호는 다 버리고 값만 푸쉬한다.
  }else if(rule == 19){  //B -> ID(E)
    double tmp;
    double temp;
    ostringstream gs; 
    S_real.pop();       E = S_real.top();   S_real.pop();   S_real.pop();
    tmp = string_to_double(E);  //값을 꺼내고
    ID = S_real.top();  S_real.pop();  //아이디 (함수명)을 꺼내서 함수명에 따라 이프문.
    if(ID=="sin"){
      temp = sin(tmp);
    }else if(ID=="cos"){
      temp = cos(tmp);
    }else if(ID=="tan"){
      temp = tan(tmp);
    }else if(ID=="exp"){
      temp = exp(tmp);
    }else if(ID=="ln"){
      temp = log(tmp);
    }else if(ID=="log"){
      temp = log10(tmp);
    }else{
      cout << "  ParserError (undefinded function)" << endl;
      return true;  //만약에 이상한 함수명이면 에러를 출력하고 트루를 리턴한다. 에러플래그를 1로만든다.
    }
    gs << temp;
    B = gs.str();
    S_real.push(B);  //그리고나서 계산한 값을 스택에 넣는다.
  }
  return false;
}

void Parser::OnAccept() {
  cout << "  **" << endl;
}

void Parser::OnParseError() {
  cout << "  ParseError (action not found)" << endl;
}

void Parser::OnLexerError() {
  cout << "  LexerError" << endl;
}

double Parser::string_to_double(const std::string& double_string){
  double x;
  x = ::atof(double_string.c_str());
  return x;
}  //계산은 더블로 해야하고 스택에는 아이디와 여러 토큰을 넣어야 하기때문에 스트링으로 선언했다. 그래서 두 
// 데이터 타입이 충돌하기 때문에 스트링을 더블로 바꾸는 함수가 필요했다. 
// 더블을 스트링으로 바꾸는 것은 별로 없어서 각 이프문에 집어 넣었따. 

