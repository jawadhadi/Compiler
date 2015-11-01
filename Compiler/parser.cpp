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
    
    for (int i = 0; i < 3; i++) {
        if(getNextToken(token, lexeme)){
            cout<<token<<" "<<lexeme<<endl;
        }else{
            cout<<"Token not found."<<endl;
        }
    }

    
}
