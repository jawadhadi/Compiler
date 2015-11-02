//
//  parser.cpp
//  Compiler
//
//  Created by Hadi on 01/11/2015.
//  Copyright © 2015 Hadi. All rights reserved.
//

#include "lex.h"

string lookahead;
string lexeme;

int initialPointer = 0;
int nextPointer = 0;

int space = 0;


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



//////////////////////////    Declaration      ////////////////////////////


//void T(){
//
//    if (strcmp(lookahead, "integer") == 0) {
//        match("integer");
//    }else if (strcmp(lookahead, "character") == 0){
//
//        match("character");
//
//    }
//
//}

void D(){
    
    //setLookAhead();
    //T();
    
    space += 2;
    
    printSpace();
    
    printf("D\n");
    
    match("ID");match(";");
    
    space -= 2;
}


////////////////////// Assignment /////////////////////////////////

void R(){
    
    if (lookahead.compare("NUM") == 0) {
        match("NUM");
    }else if (lookahead.compare("ID") == 0){
        
        match("ID");
        
    }
    
}


void A(){
    
    //setLookAhead();
    
    space += 2;
    printSpace();
    printf("A\n");
    match("ID");match("<-");R();match(";");
    
    space -=2;
    
}

/////////////////////////////// if  ////////////////////////////

void Br(){
    
    space += 2;
    printSpace();
    printf("Br\n");
    if (lookahead.compare("[") == 0) {
        match("[");match("ID");match("]");
    }
    space -= 2;
    
}


void C(){
    
    space += 2;
    printSpace();
    printf("C\n");
    match("ID");Br();match("RO");match("ID");Br();
    space -= 2;
}

void iBody(){
    
    space += 2;
    printSpace();
    printf("iBody\n");
    if (lookahead.compare("ID")== 0) {
        A();iBody();
    }else if(lookahead.compare("integer") == 0){
        
        match("integer");D();iBody();
    }else if (lookahead.compare("character") == 0){
        
        match("character");D();iBody();
        
    }else if (lookahead.compare("COMMENT") == 0){
        match("COMMENT");iBody();
    }
    space -= 2;
}


void I(){
    
    //setLookAhead();
    
    space += 2;
    printSpace();
    printf("I\n");
    match("if");C();match("begin");iBody();match("end");
    space -= 2;
    
}


///////////////////////////////////    while          ///////////


void wBody(){
    
    space += 2;
    printSpace();
    printf("wBody\n");
    if (lookahead.compare("if") == 0) {
        I();wBody();
    }else if(lookahead.compare("integer") == 0){
        
        match("integer");D();wBody();
    }else if (lookahead.compare("character") == 0){
        
        match("character");D();wBody();
        
    }else if (lookahead.compare("ID") == 0){
        
        A();wBody();
    }else if (lookahead.compare("COMMENT") == 0){
        match("COMMENT");wBody();
    }
    space -= 2;
    
}


void W(){
    
    //setLookAhead();
    
    space += 2;
    printSpace();
    printf("W\n");
    match("while");C();match("begin");wBody();match("end");
    space -= 2;
    
}


/////////////////////////////     Function     //////////////////////////////

void f_T(){
    
    space += 2;
    printSpace();
    printf("f_T\n");
    
    if (lookahead.compare("integer") == 0) {
        
        match("integer");
        
    }else if(lookahead.compare("character") == 0){
        
        match("character");
        
    }else if (lookahead.compare("void") == 0){
        
        match("void");
        
    }
    space -= 2;
    
}

void P();

void m_P(){
    
    space += 2;
    printSpace();
    printf("m_P\n");
    if (lookahead.compare(",") == 0) {
        
        match(",");P();
        
    }
    space -= 2;
    
}

void B(){
    
    space += 2;
    printSpace();
    printf("B\n");
    if (lookahead.compare("[") == 0) {
        
        match("[");match("]");
        
    }
    space -= 2;
    
}

void P(){
    
    space += 2;
    printSpace();
    
    if ((lookahead.compare("integer") == 0) || (lookahead.compare("character") == 0)) {
        printf("P\n");
        f_T();B();match("ID");m_P();
    }
    
    space -= 2;
}

void fBody(){
    
    space += 2;
    printSpace();
    printf("fBody\n");
    if (lookahead.compare("if") == 0) {
        I();fBody();
    }else if(lookahead.compare("integer") == 0){
        
        match("integer");D();fBody();
    }else if (lookahead.compare("character") == 0){
        
        match("character");D();fBody();
        
    }else if (lookahead.compare("ID") == 0){
        
        A();fBody();
    }else if (lookahead.compare("while") == 0){
        
        W();fBody();
    }else if(lookahead.compare("return") == 0){
        
        match("return");match("ID");match(";");
        
    }else if (lookahead.compare("COMMENT") == 0){
        match("COMMENT");fBody();
    }
    space -= 2;
    
}


void F(){
    
    space += 2;
    printSpace();
    cout<<"F\n";
    match("function");match("ID");match("(");P();match(")");match("returns");f_T();match("begin");fBody();match("end");
    space -=2;
    
}






/////////////////////////////////////////////////////////////////////


void runCFGs(){
    
    getNextToken(lookahead, lexeme);
    
     do{
        
        if (lookahead.compare("function") == 0) {
            F();
        }else if (lookahead.compare("integer") == 0){
            match("integer");D();
            
        }else if (lookahead.compare("character") == 0){
            match("character");D();
        }else if (lookahead.compare("ID") == 0){
            
            match("ID");
            A();
            
        }else if (lookahead.compare("if") == 0){
            
            I();
            
        }else if (lookahead.compare("while") == 0){
            W();
        }else if (lookahead.compare("COMMENT") == 0){
            match("COMMENT");
        }
         
//         if (lookahead.compare("COMMENT") == 0) {
//             getNextToken(lookahead, lexeme);
//         }
        
     }while (getNextToken(lookahead, lexeme));
}



int main(int argc, const char * argv[]) {
    
    runCFGs();
    
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
