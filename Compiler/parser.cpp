//
//  parser.cpp
//  Compiler
//
//  Created by Hadi on 01/11/2015.
//  Copyright © 2015 Hadi. All rights reserved.
//

#include "lex.h"

int main(int argc, const char * argv[]) {
    
    string token;
    string lexeme;
    
    
    while (getNextToken(token, lexeme)) {
        cout<<token<<" "<<lexeme<<endl;
    }
    
    //cout<<"Token not found."<<endl;


    
}
