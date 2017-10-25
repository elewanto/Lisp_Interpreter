// File: Main.cpp
// Created by: Eric Lewantowicz
// Date: 10/11/2017
// Course: CSE 6341
// Assignment: Project 4 -- Lisp User Defined Functions
// Dependences: Parser.cpp, Parser.h, Scanner.cpp, Scanner.h

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <ctype.h>

#include "Scanner.h"
#include "Parser.h"
using namespace std;

int main(int argc, char *argv[]) {

  TokenMaker *programTokens = new TokenMaker(); // instantiate TokenMaker object; contains token list and helper functions

  int numLiteralAtoms = 0;			// number literal atoms
  int numNumericAtoms = 0;			// number numeric atoms
  int numericAtomSum = 0;
  int numOpenParen = 0;				// number open parentheses
  int numCloseParen = 0;			// number closing parentheses
  TokenType checkToken = TokenType::ATOM_LITERAL;

  while (checkToken != TokenType::ERROR_T && checkToken != TokenType::EOF_T) {
    checkToken = programTokens->getNextToken();						// call getNextToken helper function
    if (checkToken == TokenType::PAREN_OPEN) {
      numOpenParen++;
    } else if (checkToken == TokenType::PAREN_CLOSE) {
      numCloseParen++;
    } else if (checkToken == TokenType::ATOM_LITERAL) {
      numLiteralAtoms++;
    } else if (checkToken == TokenType::ATOM_NUMERIC) {
      numNumericAtoms++;
      numericAtomSum += programTokens->getLastTokenValue();
    } else if (checkToken == TokenType::ERROR_T) {
      cout << "ERROR: Invalid token " << programTokens->getLastTokenName() << endl;	// output to file
      cerr << "ERROR: Invalid token " << programTokens->getLastTokenName() << endl;	// output to console
      exit(2);										// ERROR token exits to OS
    } else if (checkToken == TokenType::EOF_T) {
      // no action; will exit loop
    } else {
      cerr << "whoops; case should not occur";
    }
  }
  cerr << "Scanner complete." << endl;
  StartNode *startNode = new StartNode();
  startNode->parseStart(programTokens);
  cerr << "Parser complete." << endl; 
  return 0;
}
