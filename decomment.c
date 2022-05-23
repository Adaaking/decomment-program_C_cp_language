
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdbool.h>

typedef enum decomment{
    Normal,
    forwardSlash, 
    comment,
    endOfComment,
    doubleQuote, 
    StringScape, 
    singleQuote,
    characterScape,
} deCommentState;


void handleNormalState(deCommentState *state, char Char) {
    
    if (Char == '\"') {
        *state = doubleQuote;
    } 
    else if (Char == '\'') {
        *state = singleQuote;
    } 
    else if (Char== '/') {
        *state = forwardSlash;
    }

    if (*state != forwardSlash) {
        putchar(Char);
    }
    
};


void handleStringScape(deCommentState *state, char Char) {

    *state = doubleQuote;
    putchar(Char);

};
void handleDoubleQuote(deCommentState *state, char Char) {

    if (Char == '\\') {
        *state = StringScape;
    } 
    else if (Char== '\"') {
        *state = Normal;
    }
    putchar(Char);

};
void handlesingleQuote(deCommentState *state, char Char) {

    if (Char == '\\') {
        *state = characterScape;
    } 
    else if (Char== '\'') {
        *state = Normal;
    }
    putchar(Char);

};
void handlecharaterScape(deCommentState *state, char Char) {

    *state = singleQuote;
    putchar(Char);
};


void handleForwardSlash(deCommentState *state, char Char,int *commentStartLine,int *curruntLine) {

    if (Char == '*') {
        *state = comment;
        *commentStartLine = *curruntLine;
    } 
    else if ((Char == '/') && *state == forwardSlash) {
        putchar(Char);
        *state = forwardSlash;
    }  
    else if (Char == '/') {
        *state = forwardSlash;
    } 
    else {
        *state = Normal;
    }

    if (*state == Normal) {
        putchar('/');
        putchar(Char);
    }

};
void handleCommentState(deCommentState *state, char Char) {

    if (Char == '*') {
        *state = endOfComment;
    }

    if (Char == '\n') {
        putchar(Char);
    }

};

void handleEndOfComment(deCommentState *state, char Char) {

    if (Char == '/') {
        *state = Normal;
    } else if (Char == '*') {
        *state = endOfComment;
    } else {
        *state = comment;
    }

    if (*state == Normal) {
        putchar(' ');
    }

};

void proveFileEnd(deCommentState *state, int lastCommentline) {

    if (*state == comment || *state == forwardSlash) {
        fprintf(stderr, "Error: Comment started on line  %d  is unterminated comment.\n", lastCommentline);
    }

}

void countLine(int *line, char Char) {

    if (Char== '\n') {
        *line += 1;
    }

}

void main(){
   deCommentState state = Normal;

    int line = 1; 
    int startComment= 1;  
    while(true){

      char inputChar = getchar();
      countLine(&line, inputChar);
      if (inputChar== EOF) {
         proveFileEnd(&state,  startComment);
         break;
      }

      if(state == Normal){
         handleNormalState(&state, inputChar);
         }
      else if(state == forwardSlash){
         handleForwardSlash(&state, inputChar,&startComment,&line);
         }
      else if(state == comment){
         handleCommentState(&state, inputChar);
         }

      else if(state == doubleQuote){
         handleDoubleQuote(&state, inputChar);
         }
      else if(state == singleQuote){
         handlesingleQuote(&state, inputChar);
        }
      else if(state == endOfComment){
         handleEndOfComment(&state,inputChar);
       }
       else if(state == StringScape){
          handleStringScape(&state,inputChar);
       }else if(state == characterScape){
          handlecharaterScape(&state,inputChar);
       }
   }
}


