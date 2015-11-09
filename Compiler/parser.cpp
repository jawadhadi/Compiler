//
//  parser.cpp
//  Compiler
//
//  Created by Hadi on 01/11/2015.
//  Copyright © 2015 Hadi. All rights reserved.
//

#include "lex.h"
using namespace std;


string taCode[20];
int lineNumber = 1;

int fCount = 0;

int emitFalse = 0;

int onTrue;
int onFalse[30];
//int otherGoto;

string lookahead;
string lexeme;

int space = 0;  //to print blank spaces for tree

void printSpace(){
    
    for (int i = 0; i < space; i++) {
        printf(" ");
    }
}


void match(string terminal){
    
    if (lookahead.compare(terminal) == 0) {
        
        getNextToken(lookahead, lexeme);
        
    }else{
        
        printf("Syntax error!\n");
        
    }
    
}

void declaration();
void assignment();

void assignmentDeclarationBody(){
    
    if (lookahead.compare("ID") == 0) {
        
        assignment();assignmentDeclarationBody();
    }else if (lookahead.compare("integer") == 0){
        
        match("integer");declaration();
        
    }else if (lookahead.compare("character") == 0){
        match("character");declaration();
    }

    
}

void declaration(){
    
    space += 2;
    
    printSpace();
    
    printf("declaration\n");
    
    match("ID");match(";");
    
    space -= 2;
}

////////////////////// Assignment /////////////////////////////////

void var(){
    
    if (lookahead.compare("NUM") == 0) {
        taCode[lineNumber].append(lexeme);match("NUM");
    }else if (lookahead.compare("ID") == 0){
        
        taCode[lineNumber].append(lexeme);match("ID");
        
    }
    
}


void assignment(){
    
    //setLookAheadeclaration();
    
    space += 2;
    printSpace();
    printf("assignment\n");
    taCode[lineNumber].append(lexeme);match("ID");taCode[lineNumber].append("=");match("<-");var();taCode[lineNumber].append(";");match(";");
    lineNumber++;
    
    
    space -=2;
    assignmentDeclarationBody();
    
}

/////////////////////////////// if  ////////////////////////////

void Br(){
    
    //space += 2;
    //printSpace();
    //printf("Br\n");
    if (lookahead.compare("[") == 0) {
        taCode[lineNumber].append(lookahead);match("[");taCode[lineNumber].append(lexeme);match("ID");taCode[lineNumber].append(lookahead);match("]");
    }
    //space -= 2;
    
}


void conditionCheck(){
    
    //space += 2;
    //printSpace();
    //printf("C\n");
    taCode[lineNumber].append(lexeme);match("ID");Br();taCode[lineNumber].append(lexeme);match("RO");taCode[lineNumber].append(lexeme);match("ID");Br();taCode[lineNumber].append("goto ");taCode[lineNumber].append(to_string(lineNumber+2));lineNumber++;taCode[lineNumber].append("goto ");onFalse[fCount] = lineNumber;fCount++;
    lineNumber++;
    //space -= 2;
}

void ifBody(){
    
    space += 2;
    printSpace();
    printf("ifBody\n");
    if (lookahead.compare("ID")== 0) {
        assignment();lineNumber++;ifBody();
    }else if(lookahead.compare("integer") == 0){
        
        match("integer");declaration();ifBody();
    }else if (lookahead.compare("character") == 0){
        
        match("character");declaration();ifBody();
        
    }else if (lookahead.compare("COMMENT") == 0){
        match("COMMENT");ifBody();
    }
    space -= 2;
}


void ifcondition(){
    
    space += 2;
    printSpace();
    printf("ifcondition\n");
    taCode[lineNumber].append(lookahead);match("if");conditionCheck();match("begin");ifBody();taCode[lineNumber].append(lookahead);match("end");
    space -= 2;
    lineNumber++;
    taCode[lineNumber].append("goto ");taCode[onFalse[emitFalse]].append(to_string(lineNumber));emitFalse++;
    
}

///////////////////////////////////    while          ///////////

void whileBody(){
    
    space += 2;
    printSpace();
    printf("whileBody\n");
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
    space -= 2;
    
}

void whileLoop(){
    
    //setLookAheadeclaration();
    
    space += 2;
    printSpace();
    printf("whileLoop\n");
    taCode[lineNumber].append(lookahead);match("while");conditionCheck();match("begin");lineNumber++;whileBody();match("end");
    space -= 2;
    
    taCode[onFalse[emitFalse]].append(to_string(lineNumber));emitFalse++;
    lineNumber++;
    taCode[lineNumber].append("goto ");taCode[lineNumber].append(to_string(lineNumber));
    
}

/////////////////////////////     Function     //////////////////////////////

void funcReturnType(){
    
    space += 2;
    printSpace();
    printf("funcReturnType\n");
    
    if (lookahead.compare("integer") == 0) {
        
        match("integer");
        
    }else if(lookahead.compare("character") == 0){
        
        match("character");
        
    }else if (lookahead.compare("void") == 0){
        
        match("void");
        
    }
    space -= 2;
    
}

void OP();

void multipleParameters(){
    
    //space += 2;
    //printSpace();
    //printf("m_P\n");
    if (lookahead.compare(",") == 0) {
        
        match(",");OP();
        
    }
    //space -= 2;
    
}

void arrayBracket(){
    
    //space += 2;
    //printSpace();
    //printf("B\n");
    if (lookahead.compare("[") == 0) {
        
        match("[");match("]");
        
    }
    //space -= 2;
    
}

void OP(){
    
    space += 2;
    if (lookahead.compare("integer") == 0) {
        match("integer");arrayBracket();match("ID");multipleParameters();
         printSpace();
        printf("OP\n");
    }else if (lookahead.compare("character") == 0){
        match("character");arrayBracket();match("ID");multipleParameters();
         printSpace();
        printf("OP\n");
    }
    
    space -= 2;
}

void funcBody(){
    
    space += 2;
    printSpace();
    printf("func_Body\n");
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
    
    
    
    space -= 2;
    
}


void func(){
    
    space += 2;
    printSpace();
    cout<<"func\n";
    match("function");match("ID");match("(");OP();match(")");match("returns");funcReturnType();match("begin");funcBody();match("end");
    space -=2;
    
}
/////////////////////////////////////////////////////////////////////

void runCFGs(){
    
    getNextToken(lookahead, lexeme);
    
    do{
        
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
            whileLoop();
        }else if (lookahead.compare("COMMENT") == 0){
            match("COMMENT");
        }
        
     }while (getNextToken(lookahead, lexeme));
}



int main(int argc, const char * argv[]) {
    
    runCFGs();
    
    for (int i = 0; i <= lineNumber; i++) {
        cout<<taCode[i]<<endl;
    }
    
    return 0;
}



//int main(int argc, const char * argv[]) {
//    
//    string token;
//    string lexeme;
//    
//    
//    while (getNextToken(token, lexeme)) {
//        cout<<token<<" "<<lexeme<<endl;
//    }
//    
//    if (!endOfFile) {
//        cout<<"Unrecoginzed token"<<endl;
//    }
//    cout<<"End of file."<<endl;
//
//
//    
//}
