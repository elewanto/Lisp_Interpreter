// File: Scanner.cpp
// Created by: Eric Lewantowicz
// Course: CSE 6341

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctype.h>

#include "Scanner.h"
using namespace std;

// consumes current token and moves to next token
void TokenMaker::moveToNext() {
  if (tokenList.size() == 0) {
    cout << "ERROR: No tokens remaining in moveToNext()." << endl;		// case should never occur; always eof token minimum
  } else {
    tokenList.erase(tokenList.begin());
  }
}

// returns current token tuple without consuming it
TokenType TokenMaker::getCurrentType() {
  TokenType type = TokenType::ERROR_T;
  if (tokenList.size() > 0) {
    type = tokenList.front().type;
  } else {
    cout << "ERROR: No tokens remaining in getCurrent()." << endl;		// case should never occur; always eof token minimum
  }
  return type;
}

// returns current Numeric token value without consuming it
int TokenMaker::getCurrentValue() {
  return tokenList.front().value;
}

// returns current Literal token name/id without consuming it
string TokenMaker::getCurrentName() {
  return tokenList.front().name;
}

// returns name of next (second) token without consuming it
string TokenMaker::getNextName() {
  string result = "";
  if (tokenList.size() > 1) {
    result = tokenList[1].name;
	//cerr << tokenList.front().name << " : " << tokenList[1].name << endl;

  }
  return result;
}

// builds token from input stream and returns token tuple
TokenType TokenMaker::getNextToken() {
  TokenType type = TokenType::EOF_T;									// next token type 
  char inputChar;														// next character from input string

  cin.get(inputChar);
  while (!cin.eof() && isspace(inputChar)) {							// consume white space chars with no action
    cin.get(inputChar);
  }
  if (cin.eof()) {														// add EOF token
    type = TokenType::EOF_T;
    addToken("", -1, TokenType::EOF_T); 
  } else if (inputChar == '(') {										// add open parenthesis token
    type = TokenType::PAREN_OPEN;
    addToken("", -1, TokenType::PAREN_OPEN);    
  } else if (inputChar == ')') {										// add close parenthesis token
    type = TokenType::PAREN_CLOSE;
    addToken("", -1, TokenType::PAREN_CLOSE);        
  } else if (isdigit(inputChar)) {										// add numeric atom or error token
    type = processNumericAtomOrError(inputChar);
  } else if (isupper(inputChar)) {										// add literal atomic token
    type = TokenType::ATOM_LITERAL;
    processLiteralAtom(inputChar);
  } else {																// this error case should not occur
    cerr << "whoops: unexpected character found" << endl;
  }
  return type;
}

// builds numeric atom token
TokenType TokenMaker::processNumericAtomOrError(char inputChar) {
  TokenType type = TokenType::ATOM_NUMERIC;								// return token type will be numeric or error
  char nextChar = ' ';
  string tokName (1, inputChar);										// construct string using input character param

  nextChar = cin.peek();												// peek at char in iostream without consuming
  while(!isspace(nextChar) && nextChar != '(' && nextChar != ')') {
    if (isdigit(nextChar)) {
      cin.get(nextChar);												// consume digit
      tokName += nextChar;
    } else {															// ERROR: uppercase letter encountered in numeric atom; finish constructing bad token below
      cin.get(nextChar);												// consume uppercase letter or digit
      tokName += nextChar;
      cin.get(nextChar);
      while(!isspace(nextChar) && nextChar != '(' && nextChar != ')') { // finish constructing erroneous numeric atom
        tokName += nextChar;
        cin.get(nextChar);
      }
      addToken(tokName, -1, TokenType::ERROR_T);						// add ERROR token to token list
      return TokenType::ERROR_T;
    }
    nextChar = cin.peek();
  }
  addToken("", stoi(tokName), TokenType::ATOM_NUMERIC);
  return type;
}

// builds literal atom token
void TokenMaker::processLiteralAtom(char inputChar) {
  char nextChar = ' ';
  string tokName(1, inputChar);											// construct string using input character param
  
  nextChar = cin.peek();												// peek at char in iostream without consuming
  while(!isspace(nextChar) && nextChar != '(' && nextChar != ')') {
    cin.get(nextChar);													// consume digit or uppercase letter
    tokName += nextChar;
    nextChar = cin.peek();
  }
  addToken(tokName, -1, TokenType::ATOM_LITERAL);
}

// adds new token to end of token queue
void TokenMaker::addToken(std::string name, int value, TokenType _type) {
  Token token(name, value, _type);
  tokenList.push_back(token);
}

int TokenMaker::getLastTokenValue() {
  return tokenList.back().value;
}

string TokenMaker::getLastTokenName() {
  return tokenList.back().name;
}

void TokenMaker::printLiteralAtoms() {
  for (size_t i = 0; i < tokenList.size(); ++i) {
    if (tokenList[i].type == TokenType::ATOM_LITERAL) {
      cout << ", " << tokenList[i].name;
    }
  }
}

void TokenMaker::printLastToken() {
  if (tokenList.size() != 0) {
    Token token = tokenList.back();										// point to last token in list
    cout << static_cast<int>(token.type) << "  " << token.value << " " << token.name << endl;
  }
}

