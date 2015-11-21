//
//  parser.cpp
//  Compiler
//
//  Created by Hadi on 01/11/2015.
//  Copyright © 2015 Hadi. All rights reserved.
//

#include "lex.h"
using namespace std;


string taCode[100];
int lineNumber = 1;
string lookahead;
string lexeme;


void backpatch(int currentLine, int onFalse){
    
    taCode[onFalse].append(to_string(currentLine));
}

void match(string terminal){
    
    if (lookahead.compare(terminal) == 0) {
        
        getNextToken(lookahead, lexeme);
        
    }else{
        
        printf("Syntax error!\n");
        
    }
    
}

void declaration(){

    
    match("ID");match(";");

}

////////////////////// Assignment /////////////////////////////////


//void T2(){
//
//    if (lookahead.compare("*") == 0) {
//        taCode[lineNumber].append(lexeme);match("*");F();T2();
//    }else if (lookahead.compare("/") == 0){
//
//        taCode[lineNumber].append(lexeme);match("/");F();T2();
//    }
//
//}
//
//void T(){
//
//    F();T2();
//
//}
//
//void E2(){
//
//    if (lookahead.compare("+") == 0) {
//        taCode[lineNumber].append(lexeme);match("+");T();E2();
//    }else if (lookahead.compare("-") == 0){
//
//        taCode[lineNumber].append(lexeme);match("-");T();E2();
//    }
//
//}
//
//void expression(){
//
//
//    T();E2();
//
//}


int tmpCount = 0;
string mainTmp;
string getTmp(){
    mainTmp = "tmp";
    tmpCount++;
    return mainTmp.append(to_string(tmpCount));
}

bool simpleExpr = false;

string F(){
    
    string tmp;
    if (lookahead.compare("NUM") == 0) {
        tmp = lexeme;
        //taCode[lineNumber].append(lexeme);
        match("NUM");
        return tmp;
    }else if (lookahead.compare("ID") == 0){
        tmp = lexeme;
        //taCode[lineNumber].append(lexeme);
        match("ID");
        return tmp;
    }
    return nullptr;
}

bool T2(string op){

    bool flag = false;
    if (lookahead.compare("*") == 0) {
        string tmp = getTmp();match("*");string op2 = F();taCode[lineNumber].append(tmp+ " = "+ op+ " * "+op2+";");lineNumber++;T2(tmp);
        flag = true;
    }else if (lookahead.compare("/") == 0){

        string tmp = getTmp();match("/");string op2 = F();taCode[lineNumber].append(tmp+ " = "+ op+ " / "+op2+";");lineNumber++;T2(tmp);
        flag = true;
    }
    
    if (lookahead.compare(";") == 0) {
        
        simpleExpr = true;
    }
    
    return flag;
}

string T(){
    
    string someOp = F();if(T2(someOp)){
        return mainTmp;
    }else{
        return someOp;
    }

}

bool E2(string op){
    
    bool flag = false;

    if (lookahead.compare("+") == 0) {
        match("+");string op2 = T();string tmp = getTmp();taCode[lineNumber].append(tmp+ " = "+ op+ " + "+op2+";");lineNumber++;E2(mainTmp);
        flag = true;
    }else if (lookahead.compare("-") == 0){
        
        match("-");string op2 = T();string tmp = getTmp();taCode[lineNumber].append(tmp+ " = "+ op+ " - "+op2+";");lineNumber++;E2(mainTmp);
        flag = true;
    }
    return flag;

}


void expression(string mainOp){
    
    string op = T();if(E2(op)){
     
        taCode[lineNumber].append(mainOp + " = "+ mainTmp +";");match(";");
    }
    else{
         taCode[lineNumber].append(mainOp + " = "+ op +";");match(";");
    }
    
}


void assignment(){
    
    string mainOp = lexeme;
    //taCode[lineNumber].append(lexeme);
    match("ID");//taCode[lineNumber].append("=");
    match("<-");expression(mainOp);
    lineNumber++;
    
    
}

/////////////////////////////// if  ////////////////////////////

void Br(){
    
    if (lookahead.compare("[") == 0) {
        taCode[lineNumber].append(lookahead);match("[");taCode[lineNumber].append(lexeme);match("ID");taCode[lineNumber].append(lookahead);match("]");
    }
    
}


void conditionCheck(int &onFalse){
    
    taCode[lineNumber].append(lexeme);match("ID");Br();taCode[lineNumber].append(lexeme);match("RO");taCode[lineNumber].append(lexeme);match("ID");Br();taCode[lineNumber].append("goto ");taCode[lineNumber].append(to_string(lineNumber+2));lineNumber++;taCode[lineNumber].append("goto ");onFalse = lineNumber;
    lineNumber++;
}

void ifBody(){
    
    if (lookahead.compare("ID")== 0) {
        assignment();ifBody();
    }else if(lookahead.compare("integer") == 0){
        
        match("integer");declaration();ifBody();
    }else if (lookahead.compare("character") == 0){
        
        match("character");declaration();ifBody();
        
    }else if (lookahead.compare("COMMENT") == 0){
        match("COMMENT");ifBody();
    }
}


void ifcondition(){
    
    int onFalse;
    int otherGoto;
    taCode[lineNumber].append(lookahead);match("if");conditionCheck(onFalse);match("begin");ifBody();match("end");
    
    if (lookahead.compare("else") == 0) {
        taCode[lineNumber].append("goto ");otherGoto = lineNumber;
        lineNumber++;
        match("else");match("begin");backpatch(lineNumber, onFalse);ifBody();match("end");backpatch(lineNumber, otherGoto);
    }else{
        backpatch(lineNumber, onFalse);
    }
}

///////////////////////////////////    while          ///////////

void whileBody(){
    
    if (lookahead.compare("if") == 0) {
        ifcondition();whileBody();
    }else if(lookahead.compare("integer") == 0){
        
        match("integer");declaration();whileBody();
    }else if (lookahead.compare("character") == 0){
        
       match("character");declaration();whileBody();
        
    }else if (lookahead.compare("ID") == 0){
        
        assignment();whileBody();
    }else if (lookahead.compare("COMMENT") == 0){
        match("COMMENT");whileBody();
    }
    
}

void whileLoop(){
    
    int whileStart;
    int onFalse;
    taCode[lineNumber].append(lookahead);match("while");whileStart = lineNumber;conditionCheck(onFalse);match("begin");whileBody();match("end");
    
    taCode[lineNumber].append("goto ");taCode[lineNumber].append(to_string(whileStart));
    lineNumber++;
    backpatch(lineNumber, onFalse);

    taCode[lineNumber].append("goto ");taCode[lineNumber].append(to_string(lineNumber+1));
    lineNumber++;
}

/////////////////////////////     Function     //////////////////////////////

void funcReturnType(){
    
    if (lookahead.compare("integer") == 0) {
        
        match("integer");
        
    }else if(lookahead.compare("character") == 0){
        
        match("character");
        
    }else if (lookahead.compare("void") == 0){
        
        match("void");
        
    }
    
}

void OP();

void multipleParameters(){
    
    if (lookahead.compare(",") == 0) {
        
        match(",");OP();
        
    }
    
}

void arrayBracket(){
    
    if (lookahead.compare("[") == 0) {
        
        match("[");match("]");
        
    }
}

void OP(){
    
     
    if (lookahead.compare("integer") == 0) {
        
        match("integer");arrayBracket();match("ID");multipleParameters();
    }else if (lookahead.compare("character") == 0){
        
        match("character");arrayBracket();match("ID");multipleParameters();
    }
    
     
}

void funcBody(){
    
    if (lookahead.compare("if") == 0) {
        ifcondition();funcBody();
    }else if(lookahead.compare("integer") == 0){
        
        match("integer");declaration();funcBody();
    }else if (lookahead.compare("character") == 0){
        
        match("character");declaration();funcBody();
        
    }else if (lookahead.compare("ID") == 0){
        
        assignment();funcBody();
    }else if (lookahead.compare("while") == 0){
        
        whileLoop();funcBody();
    }else if(lookahead.compare("return") == 0){
        
        match("return");match("ID");match(";");
        
    }else if (lookahead.compare("COMMENT") == 0){
        match("COMMENT");funcBody();
    }
    
}


void func(){
    
    match("function");match("ID");match("(");OP();match(")");match("returns");funcReturnType();match("begin");funcBody();match("end");
    
}
/////////////////////////////////////////////////////////////////////

void runCFGs(){
        
        if (lookahead.compare("function") == 0) {
            func();
        }else if (lookahead.compare("integer") == 0){
            match("integer");declaration();
            
        }else if (lookahead.compare("character") == 0){
            match("character");declaration();
        }else if (lookahead.compare("ID") == 0){
            
            assignment();
            
        }else if (lookahead.compare("if") == 0){
            
            ifcondition();
            
        }else if (lookahead.compare("while") == 0){
            whileLoop();runCFGs();
        }else if (lookahead.compare("COMMENT") == 0){
            match("COMMENT");
        }
}



int main(int argc, const char * argv[]) {
    
    getNextToken(lookahead, lexeme);
    runCFGs();
    
    for (int i = 1; i <= lineNumber; i++) {
        cout<<i<<" "<<taCode[i]<<endl;
    }
    
    return 0;
}
