// File: Parser.h
// Created by: Eric Lewantowicz
// Course: CSE 6341

#ifndef _PARSER_H
#define _PARSER_H

#include "Scanner.h"

enum class AtomType {NUMERIC, LITERAL, LIST};

// forward class declarations
class StartNode;
class Node;

class StartNode {
  private:
    Node *expr;	
    StartNode *start;							// prodAlt 1  <Expr><Start>
    int prodAlt;								// rule production alternative; prodAlt 2 means EOF token reached

    Node *sExpr;

  public:
	static Node *dList;							// dList contains DEFUN definitions
	Node *aList;								// aList contains stack of bound variables used in DEFUN applications
	static const std::string reservedList [];	// list of reserved literal atoms

    StartNode();								// constructor

    void parseStart(TokenMaker *t);
    static bool isReserved(TokenMaker *t);
	static bool isDuplicate(Node *root, std::string name, int numFormals);
};

class Node {
  private:

  public:
	// constructors
    Node();							
    Node(bool _isAtom, AtomType _atomType, int _value, std::string _name);

    Node *leftChild;
    Node *rightChild;
    bool isAtom;					// TRUE if leaf numeric, literal, or nil atom; FALSE if list node with chilren
    AtomType atomType;				// atomTypes numeric, literal, or NIL
    int value;						// integer value for numeric atom
    std::string name;				// name can be NIL or named Literal atom

    void parseExpr(TokenMaker *t);
    std::string parseDefun(TokenMaker *t);
    void printDotNotation();
    void parseList(TokenMaker *t);

    bool bound(Node *list);
    Node *getVal(Node *list);
    Node *evList(Node *aList);
    static Node* addPairs(Node *aList, Node *formals, Node *actuals);

    // project 3 interpreter functions
    Node *eval(Node *aList);
    int length(int accum);
    Node *car(Node *aList);
    Node *cdr(Node *aList);
    Node *cons(Node *aList);
    Node *quote(Node *aList);
    Node *plus(Node *aList);
    Node *minus(Node *aList);
    Node *times(Node *aList);
    Node *less(Node *aList);
    Node *greater(Node *aList);
    Node *eq(Node *aList);
    Node *atom(Node *aList);
    Node *_int(Node *aList);
    Node *_null(Node *aList);
    Node *cond(Node *head, Node *aList);
    void goodCondBE(Node *head, Node *aList);
    void printListNotation(bool isRoot);
};


#endif

