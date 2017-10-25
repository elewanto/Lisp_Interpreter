// File: Scanner.h
// Created by: Eric Lewantowicz
// Course: CSE 6341

#ifndef _SCANNER_H
#define _SCANNER_H

#include <vector>
#include <string>

enum class TokenType {ATOM_LITERAL, ATOM_NUMERIC, PAREN_OPEN, PAREN_CLOSE, ERROR_T, EOF_T};

// Token object
class Token {

  public:

	// member variables
    std::string name;
    int value;
    TokenType type;

	// constructor
    Token(std::string _name, int _value, TokenType _type) {
      name = _name;
      value = _value;
      type = _type;
    }
};


class TokenMaker {

  private:

	// member variables
    std::vector<Token> tokenList;	// list of tokens scanned from input file

  public:

	// constructor
    TokenMaker() { }

	// member functions
    void addToken(std::string name, int value, TokenType _type);
    TokenType getNextToken();
    void moveToNext();
    TokenType getCurrentType();
    int getCurrentValue();
    std::string getCurrentName();
	std::string getNextName();
    TokenType processNumericAtomOrError(char inputChar);
    int getLastTokenValue();
    std::string getLastTokenName();
    void processLiteralAtom(char inputChar);
    void printLastToken();
    void printLiteralAtoms();
};


#endif

