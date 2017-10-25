// File: Parser.cpp
// Created by: Eric Lewantowicz
// Course: CSE 6341

#include <cstdlib>
#include <iostream>
#include "Parser.h"
using namespace std;

// initialize class static member values
const std::string StartNode::reservedList [] =
		{"T", "NIL", "CAR", "CDR", "CONS", "ATOM", "EQ", "NULL", "INT", "PLUS", "MINUS", 
		"TIMES", "LESS", "GREATER", "COND", "QUOTE", "DEFUN"};
Node* StartNode::dList = new Node(true, AtomType::LITERAL, -999999, "NIL");

// constructor definitions
StartNode::StartNode() {
  expr = new Node();
  prodAlt = 1;
  aList = new Node(true, AtomType::LITERAL, -999999, "NIL");	// initialize A-List to empty list
}

Node::Node() {
  isAtom = false;									// new node is List node by default; may be changed to Atom node in parsing
  atomType = AtomType::LIST;
  name = " ";
  value = -999999;
}

Node::Node(bool _isAtom, AtomType _atomType, int _value, std::string _name) {
  isAtom = _isAtom;
  atomType = _atomType;
  value = _value;
  name = _name;
}

// Per context free grammar, program must contain at least one <expr> and eof token
// params: t: object containing vector list of tokens
void StartNode::parseStart(TokenMaker *t) {
  if (t->getNextName() == "DEFUN") {				// parse DEFUN high level expression and update D-List
	string funName = expr->parseDefun(t);
    cout << funName << endl;
  } else {											// parse and eval regular high level expression
    expr->parseExpr(t);
    sExpr = expr;
    Node *result = sExpr->eval(StartNode::aList);	// A-List is empty at this call
    result->printListNotation(true);
    cout << endl;
  }
  if (t->getCurrentType() != TokenType::EOF_T) {
    start = new StartNode();						// more tokens exist; recursively parse next high level <expr>
    start->parseStart(t);
  } else {
    prodAlt = 2;									// end of program EOF token reached
  }
}

Node *Node::eval(Node *aList) {

  Node *result = this;
  // cases for list
  if (!isAtom) {
	// deprecated in project 4; may now have DEFUN calls with list length 1
    //if (length(0) < 2) {												
    //  cout << "ERROR: list eval() is undefined for lists less than length 2. This list: ";
    //  printListNotation(true);
    //  cout << " is only length " << length(0) << "." << endl;
    //  exit(1);
    //}
    // check for recognized car() literal
    if (leftChild->name == "PLUS") {
      if (length(0) != 3) {
        cout << "ERROR: eval() plus() is undefined for: ";
        printListNotation(true);
        cout << " of lists not length 3. This list is length " << length(0) << "." << endl;
        exit(1);
      }
      result = rightChild->plus(aList);
    }
     else if (leftChild->name == "MINUS") {
      if (length(0) != 3) {
        cout << "ERROR: eval() minus() is undefined for: ";
        printListNotation(true);
        cout << " of lists not length 3. This list is length " << length(0) << "." << endl;
        exit(1);
      }
      result = rightChild->minus(aList);
    }
    else if (leftChild->name == "TIMES") {
      if (length(0) != 3) {
        cout << "ERROR: eval() times() is undefined for: ";
        printListNotation(true);
        cout << " of lists not length 3. This list is length " << length(0) << "." << endl;
        exit(1);
      }
      result = rightChild->times(aList);
    }
    else if (leftChild->name == "LESS") {
      if (length(0) != 3) {
        cout << "ERROR: eval() less() is undefined for: ";
        printListNotation(true);
        cout << " of lists not length 3. This list is length " << length(0) << "." << endl;
        exit(1);
      }
      result = this->rightChild->less(aList);
    }    
    else if (leftChild->name == "GREATER") {
      if (length(0) != 3) {
        cout << "ERROR: eval() greater() is undefined for: ";
        printListNotation(true);
        cout << " of lists not length 3. This list is length " << length(0) << "." << endl;
        exit(1);
      }
      result = rightChild->greater(aList);
    }    
    else if (leftChild->name == "EQ") {
      if (length(0) != 3) {
        cout << "ERROR: eval() eq() is undefined for: ";
        printListNotation(true);
        cout << " of lists not length 3. This list is length " << length(0) << "." << endl;
        exit(1);
      }
      result = rightChild->eq(aList);
    }   
    else if (leftChild->name == "ATOM") {
      if (length(0) != 2) {
        cout << "ERROR: eval() atom() is undefined for: ";
        printListNotation(true);
        cout << " of lists not length 2. This list is length " << length(0) << "." << endl;
        exit(1);
      }
      result = this->rightChild->atom(aList);
    }   
    else if (leftChild->name == "INT") {
      if (length(0) != 2) {
        cout << "ERROR: eval() int() is undefined for: ";
        printListNotation(true);
        cout << " of lists not length 2. This list is length " << length(0) << "." << endl;
        exit(1);
      }
      result = this->rightChild->_int(aList);
    }   
    else if (leftChild->name == "NULL") {
      if (length(0) != 2) {
        cout << "ERROR: eval() null() is undefined for: ";
        printListNotation(true);
        cout << " of lists not length 2. This list is length " << length(0) << "." << endl;
        exit(1);
      }
      result = rightChild->_null(aList);
    }   
    else if (leftChild->name == "CAR") {
      if (this->length(0) != 2) {
        cout << "ERROR: eval() car() is undefined for: ";
        printListNotation(true);
        cout << " of lists not length 2. This list is length " << length(0) << "." << endl;
        exit(1);
      }
      result = rightChild->car(aList);
    }   
    else if (leftChild->name == "CDR") {
      if (length(0) != 2) {
        cout << "ERROR: eval() cdr() is undefined for: ";
        printListNotation(true);
        cout << " of lists not length 2. This list is length " << length(0) << "." << endl;
        exit(1);
      }
      result = rightChild->cdr(aList);
    } 
    else if (leftChild->name == "CONS") {
      if (length(0) != 3) {
        cout << "ERROR: eval() cons() is undefined for: ";
        printListNotation(true);
        cout << " of lists not length 3. This list is length " << length(0) << "." << endl;
        exit(1);
      }
      result = rightChild->cons(aList);
    } 
    else if (leftChild->name == "QUOTE") {
      if (length(0) != 2) {
        cout << "ERROR: eval() quote() is undefined for: ";
        printListNotation(true);
        cout << " of lists not length 2. This list is length " << length(0) << "." << endl;
        exit(1);
      }
      result = rightChild->quote(aList);
    } else if (leftChild->name == "COND"){
      if (rightChild->name == "NIL") {
        cout << "ERROR: eval() cond() is undefined with no lists for: ";
        printListNotation(true);
        cout << endl;
        exit(1);        
      }
      rightChild->goodCondBE(this, aList); 											// check that all (b e) expressions are lists and length 2
      result = rightChild->cond(this, aList);
	// check if user function name
    } else {
	    if (leftChild->bound(StartNode::dList)) {												// check if function name is bound in D-List
		  Node *actualList = this->rightChild->evList(aList);									// evaluate list of actual parameters
		  Node *functionPair = leftChild->getVal(StartNode::dList);								// get list of formal parameters
		  Node *formalList = functionPair->leftChild;
		  if (actualList->length(0) == formalList->length(0)) {									// must be same # formal params and actual params

		    aList = addPairs(aList, formalList, actualList);									// bind formals to actual params and add pairs to A-List
			result = functionPair->rightChild->eval(aList);
          } else {
		    cout << "ERROR: number of actual parameters must match formal parameters in call to user function: ";
  			cout << leftChild->name << endl;
			exit(1);
          }
        } else {
          cout << "ERROR: eval() unrecognized list or atom is undefined for: ";
          printListNotation(true);
          cout << endl;
          exit(1);
	    }
    }
  // cases for atom
  } else if (isAtom) {

    if (name == "T" || name == "NIL" || atomType == AtomType::NUMERIC) {    // case for T atom or NIL atom or Numeric atom; return pointer to same atom
      return result;
    } else if (this->bound(aList)) {									// check if atom is literal atom variable bound in A-List
      return this->getVal(aList);
    } else {
      cout << "ERROR: eval() is undefined for this atom: ";
      printListNotation(0);
      cout << " -- Expected T, NIL, numberic atom, or literal atom variable not found in A-List." << endl;
      exit(1);      
    }
  } else {																	// undefined case: error
    cout << "ERROR: Undefined case in eval() function." << endl;
    exit(1);
  }
  return result;
}

// add formal.actual_value parameter pairs to A-List
// precondition: length of formals and actuals must be equal
// return: pointer to updated A-List
Node* Node::addPairs(Node *aList, Node *formals, Node *actuals) {
  Node *newHead = aList;
  while (formals->name != "NIL") {
    Node *tempHead = new Node();
    Node *newPair = new Node();
    tempHead->leftChild = newPair;
    tempHead->rightChild = newHead;
    newHead = tempHead;
    newPair->leftChild = formals->leftChild;
    formals = formals->rightChild;
    newPair->rightChild = actuals->leftChild;
    actuals = actuals->rightChild;
  }
  return newHead;
}

// evaluate list of actual parameters for user function call
// params: this: list of actual parameters; may be NIL
// return list of evaluated actuals; list may be NIL
Node *Node::evList(Node *aList) {
  Node *head = new Node();					// create new list node
  Node *tail = head;
  Node *currentActual = this;
  while (currentActual->name != "NIL") {
    tail->leftChild = currentActual->leftChild->eval(aList);
    currentActual = currentActual->rightChild;
    tail->rightChild = new Node();
    tail = tail->rightChild;
  }
  tail->isAtom = true;
  tail->atomType = AtomType::LITERAL;
  tail->name = "NIL";
  return head;
}

// check if function or variable name is bound in A-List or D-list
bool Node::bound(Node *list) {
  bool isBound = false;
  Node *head = list;
  while (head->name != "NIL") {
    if (head->leftChild->leftChild->name == this->name) {
      isBound = true;
    }
    head = head->rightChild;
  }
  return isBound;
}

// precondition: variable name is bound in A-List or D-List
// return value bound to variable or function 
Node *Node::getVal(Node *list) {
  Node *result;
  bool found = false;
  Node *head = list;
  while (head->name != "NIL" && !found) {
    if (head->leftChild->leftChild->name == this->name) {
      result = head->leftChild->rightChild;
      found = true;
    }
    head = head->rightChild;
  }
  return result;
}

Node *Node::plus(Node *aList) {
  Node *s1 = leftChild->eval(aList);
  Node *s2 = rightChild->leftChild->eval(aList);
  if (s1->atomType != AtomType::NUMERIC || s2->atomType != AtomType::NUMERIC) {
    cout << "ERROR: plus() is undefined; an expression does not evaluate to a numeric atom." << endl;
    exit(1);  
  }
  int resultValue = s1->value + s2->value;
  Node *result = new Node(true, AtomType::NUMERIC, resultValue, " ");
  return result;
}

Node *Node::minus(Node *aList) {
  Node *s1 = leftChild->eval(aList);
  Node *s2 = rightChild->leftChild->eval(aList);
  if (s1->atomType != AtomType::NUMERIC || s2->atomType != AtomType::NUMERIC) {
    cout << "ERROR: minus() is undefined; an expression does not evaluate to a numeric atom." << endl;
    exit(1);  
  }
  int resultValue = s1->value - s2->value;
  Node *result = new Node(true, AtomType::NUMERIC, resultValue, " ");
  return result;
}

Node *Node::times(Node *aList) {
  Node *s1 = leftChild->eval(aList);
  Node *s2 = rightChild->leftChild->eval(aList);
  if (s1->atomType != AtomType::NUMERIC || s2->atomType != AtomType::NUMERIC) {
    cout << "ERROR: times() is undefined; an expression does not evaluate to a numeric atom." << endl;
    exit(1);  
  }
  int resultValue = s1->value * s2->value;
  Node *result = new Node(true, AtomType::NUMERIC, resultValue, " ");
  return result;
}

Node *Node::less(Node *aList) {
  Node *s1 = leftChild->eval(aList);
  Node *s2 = rightChild->leftChild->eval(aList);
  if (s1->atomType != AtomType::NUMERIC || s2->atomType != AtomType::NUMERIC) {
    cout << "ERROR: less() is undefined; an expression does not evaluate to a numeric atom." << endl;
    exit(1);  
  }
  string resultName = "NIL";
  if (s1->value < s2->value) {
    resultName = "T";
  }
  Node *result = new Node(true, AtomType::LITERAL, -999999, resultName);
  return result;
}

Node *Node::greater(Node *aList) {
  Node *s1 = leftChild->eval(aList);
  Node *s2 = rightChild->leftChild->eval(aList);
  if (s1->atomType != AtomType::NUMERIC || s2->atomType != AtomType::NUMERIC) {
    cout << "ERROR: greater() is undefined; an expression does not evaluate to a numeric atom." << endl;
    exit(1);  
  }
  string resultName = "NIL";
  if (s1->value > s2->value) {
    resultName = "T";
  }
  Node *result = new Node(true, AtomType::LITERAL, -999999, resultName);
  return result;
}

Node *Node::eq(Node *aList) {
  Node *s1 = leftChild->eval(aList);
  Node *s2 = rightChild->leftChild->eval(aList);
  if (!s1->isAtom || !s2->isAtom) {
    cout << "ERROR: eq() is undefined; s1 and s2 must evaluate to atoms." << endl;
    exit(1);  
  }
  string resultName = "NIL";
  if (s1->atomType == AtomType::NUMERIC && s2->atomType == AtomType::NUMERIC) {
    if (s1->value == s2->value) {
      resultName = "T";
    }
  } else if (s1->atomType == AtomType::LITERAL && s2->atomType == AtomType::LITERAL) {
    if (s1->name == s2->name) {
      resultName = "T";
    }
  } else {								
    cout << "ERROR: eq() is undefined; s1 and s2 don't match--they must both evaluate to Numeric atoms or both Literal atoms." << endl;
    exit(1);  
  }
  Node *result = new Node(true, AtomType::LITERAL, -999999, resultName);
  return result;
}

// requires: list length 1 (length 2 before the call including ATOM literal)
Node *Node::atom(Node *aList) {
  Node *s1 = leftChild->eval(aList);
  string resultName = "NIL";
  if (s1->isAtom) {  
    resultName = "T";
  }
  Node *result = new Node(true, AtomType::LITERAL, -999999, resultName);
  return result;
}

// requires: list length 1 (length 2 before the call including INT literal)
Node *Node::_int(Node *aList) {
  Node *s1 = leftChild->eval(aList);
  string resultName = "NIL";
  if (s1->atomType == AtomType::NUMERIC) {  
    resultName = "T";
  }
  Node *result = new Node(true, AtomType::LITERAL, -999999, resultName);
  return result;
}

// requires: list length 1 (length 2 before the call including NULL literal)
Node *Node::_null(Node *aList) {
  Node *s1 = leftChild->eval(aList);
  string resultName = "NIL";
  if (s1->atomType == AtomType::LITERAL && s1->name == "NIL") {  
    resultName = "T";
  }
  Node *result = new Node(true, AtomType::LITERAL, -999999, resultName);
  return result;
}

Node *Node::car(Node *aList) {
  Node *s1 = leftChild->eval(aList);
  if (s1->isAtom) {
    cout << "ERROR: car() is undefined for s1 binary tree with one node, i.e. atom.  Atom was: ";
    s1->printListNotation(0);
    cout << endl;
    exit(1);
  } else {
    return s1->leftChild;
  }
}

Node *Node::cdr(Node *aList) {
  Node *s1 = leftChild->eval(aList);
  if (s1->isAtom) {
    cout << "ERROR: cdr() is undefined for binary tree with one node, i.e. atom.  Atom was: ";
    s1->printListNotation(0);
    cout << endl;
    exit(1);
  } else {
    return s1->rightChild;
  }
}

Node *Node::cons(Node *aList) {
  Node *head = new Node(false, AtomType::LIST, -999999, " ");
  Node *s1 = leftChild->eval(aList);
  Node *s2 = rightChild->leftChild->eval(aList);
  head->leftChild = s1;
  head->rightChild = s2;
  return head;
}

Node *Node::quote(Node *aList) {
  Node *s1 = leftChild;
  return s1;
}

// function evaluates COND expression
// params: head: pointer to root of COND expression to maintain ability to print expression from root in case of error
Node *Node::cond(Node* head, Node *aList) {
  Node *result = this;
  if (leftChild->length(0) != 2) {										// undefined if s is not length 2; needs to be (b,e)
    cout << "ERROR: cond() is undefined for: ";
    head->printListNotation(true);
    cout << " with any lists not length 2." << endl;
    cout << " The list: ";
    leftChild->printListNotation(true);
    cout << " is length " << leftChild->length(0) << "." << endl;
    exit(1);
  }
  Node *b = leftChild->leftChild->eval(aList);
  if (b->name != "NIL") {												// b evaluates to non-NIL
    result = leftChild->rightChild->leftChild->eval(aList);
  } else if (length(0) > 1) {											// if b is NIL, evaluate next b
    result = rightChild->cond(head, aList);
  } else {
    cout << "ERROR: cond() is undefined for: ";
    head->printListNotation(true);
    cout << ". No expression evaluates to non-NIL. ";
    exit(1);
  }
  return result;
}

// function validates (b e) expressions within a COND expression are valid; used prior to evaluating a COND expression
// params: head: pointer to root of COND expression to maintain ability to print expression from root in case of error
void Node::goodCondBE(Node *head, Node *aList) {
  if (leftChild->isAtom || leftChild->length(0) != 2) {
    cout << "ERROR: in COND evalutaion.  (b e) expression is malformed for: ";
    leftChild->printListNotation(true);
    cout << endl << "eval() cond() is undefined for: ";
    head->printListNotation(true);
    cout << endl;
    exit(1); 
  } 
  if (rightChild->name != "NIL") {
    rightChild->goodCondBE(head, aList);
  }
}

// function returns length of a tree/list, where empty list is length 0
// requires: calling object is a list
// params: accum: increments length of list through recursive calls
int Node::length(int accum) {
  Node *next = this;
  if (isAtom && name == "NIL") {									// empty list case; atom is NIL; return list length 0
    // no action; return
  } else if (isAtom) {												// single atom or atom at end of list: return length 0 (should be error case?)
	// no action
  } else {															// list is not empty case
    accum = 1 + next->rightChild->length(accum);					// recursive call to length() on right child
  }
  return accum;
}

/////////////////////////////////////////////////////////////////////////////////////////
// parse and print functions

// add new DEFUN to top of D-List binary tree stack
string Node::parseDefun(TokenMaker *t) {
  Node *root = new Node();
  root->rightChild = StartNode::dList;
  StartNode::dList = root;
  StartNode::dList->leftChild = new Node();
  Node *defun = StartNode::dList->leftChild;
  if (t->getCurrentType() != TokenType::PAREN_OPEN) {
    cout << "ERROR: Invalid token type found before DEFUN token in parseDefun()." << endl;
	exit(1);
  }
  t->moveToNext();														// consume "(" token
  if (t->getCurrentName() != "DEFUN") {
    cout << "ERROR: Expected DEFUN token in parseDefun()." << endl;
    exit(1);
  }
  t->moveToNext();														// consume DEFUN token
  if (t->getCurrentType() != TokenType::ATOM_LITERAL) {
    cout << "ERROR: Expected literal atom after DEFUN token in parseDefun()." << endl;
    exit(1);
  }
  if (StartNode::isReserved(t)) {
    cout << "ERROR: Literal atom token DEFUN name in parseDefun() is reserved word: " << t->getCurrentName() << endl;
    exit(1);  
  }
  defun->leftChild = new Node(true, AtomType::LITERAL, -999999, t->getCurrentName());
  t->moveToNext();														// consume function name token

  defun->rightChild = new Node();										// process formal parameters list
  Node *pair = defun->rightChild;
  pair->leftChild = new Node();
  Node *formals = pair->leftChild;
  int numFormals = 0;
  if (t->getCurrentType() == TokenType::ATOM_LITERAL && t->getCurrentName() == "NIL") {		// case with NIL formals (DEFUN F NIL (BODY))
    t->moveToNext();													// consume formals NIL token
  } else {
    if (t->getCurrentType() != TokenType::PAREN_OPEN) {
      cout << "ERROR: Expected ( after DEFUN function name token in parseDefun()." << endl;
	  exit(1);
    }
    t->moveToNext();														// consume formals "(" token
    while (t->getCurrentType() != TokenType::PAREN_CLOSE) {
      if (t->getCurrentType() != TokenType::ATOM_LITERAL && t->getCurrentType() != TokenType::PAREN_CLOSE) {
        cout << "ERROR: Expected literal atom or ) in DEFUN formals list in parseDefun()." << endl;
	    exit(1);
      }
      if (StartNode::isReserved(t)) {
        cout << "ERROR: Literal atom token DEFUN formal parameter in parseDefun() is reserved word: " << t->getCurrentName() << endl;
        exit(1);  
      }
	  if (StartNode::isDuplicate(pair->leftChild, t->getCurrentName(), numFormals)) {
        cout << "ERROR: Literal atom token DEFUN formal parameter in parseDefun() is duplicate: " << t->getCurrentName() << endl;
	    cout << "in DEFUN: " << defun->leftChild->name << endl;
        exit(1); 
      }
      numFormals++;
      formals->leftChild = new Node(true, AtomType::LITERAL, -999999, t->getCurrentName());
      formals->rightChild = new Node();
      formals = formals->rightChild;
  	  t->moveToNext();													// consume formal param token
    }
    t->moveToNext();													// consume formals ")" token
  }
  formals->isAtom = true;												// set end of formals list to NIL atom
  formals->atomType = AtomType::LITERAL;
  formals->name = "NIL";
  pair->rightChild = new Node();
  pair->rightChild->parseExpr(t);										// parse DEFUN body as an expression
  if (t->getCurrentType() != TokenType::PAREN_CLOSE) {
    cout << "ERROR: Expected ) token at end of DEFUN." << endl;
	exit(1);
  }
  t->moveToNext();														// consume DEFUN ")" token  
  return defun->leftChild->name;  										// return DEFUN function name
}

void Node::parseExpr(TokenMaker *t) {
  if (t->getCurrentType() == TokenType::ATOM_LITERAL || t->getCurrentType() == TokenType::ATOM_NUMERIC) {
    isAtom = true;														// update node type to Atom
    if (t->getCurrentType() == TokenType::ATOM_LITERAL) {
      atomType = AtomType::LITERAL;
      name = t->getCurrentName();
    } else if (t->getCurrentType() == TokenType::ATOM_NUMERIC) {
      atomType = AtomType::NUMERIC;
      value = t->getCurrentValue();
    } else {															// case should not occur
      cout << "ERROR: Invalid token type found in AtomNode." << endl;
    }
    t->moveToNext();													// consume atom token
  } else if (t->getCurrentType() == TokenType::PAREN_OPEN) {
    t->moveToNext();													// consume "(" token
    this->parseList(t);
    if (t->getCurrentType() == TokenType::PAREN_CLOSE) {
      t->moveToNext();													// consume ")" token
    } else {
      cout << "ERROR: Expecting \")\" token at end of <List>." << endl;
      exit(1);
    }
  } else {
    cout << "ERROR: Invalid token found in parseExpr().  Expecting atom or \"(\" token. " << t->getCurrentName() << endl;
    exit(1);
  }
}

void Node::parseList(TokenMaker *t) {
  if (t->getCurrentType() == TokenType::PAREN_OPEN || t->getCurrentType() == TokenType::ATOM_LITERAL ||
      t->getCurrentType() == TokenType::ATOM_NUMERIC) {					// <Expr><List> alternative
    leftChild = new Node();
    leftChild->parseExpr(t);
    rightChild = new Node();
    rightChild->parseList(t);
  } else if (t->getCurrentType() == TokenType::PAREN_CLOSE) {			// empty or end of <List>; node becomes NIL atom
    isAtom = true;
    atomType = AtomType::LITERAL;
    name = "NIL";
  } else {
    cout << "ERROR: Invalid token found in parseList().  Expecting \")\" or atom or \"(\" token." << endl;
    exit(1);
  }
}

bool StartNode::isReserved(TokenMaker *t) {
  bool result = false;
  for (int i = 0; i < 17; i++) {
    if (t->getCurrentName() == StartNode::reservedList[i]) {
      result = true;
    }
  }
  return result;
}

bool StartNode::isDuplicate(Node *root, string name, int numFormals) {
  bool result = false;
  for (int i = 0; i < numFormals; i++) {
    if (root->leftChild->name == name) {
      result = true;
    }
    root = root->rightChild;
  }
  return result;
}

// new print format used in project 3
void Node::printListNotation(bool isRoot) {
  if (isAtom) {															// root node is atom
    if (atomType == AtomType::NUMERIC) {
      cout << value;
    } else {
      cout << name;
    }    
  } else {																// root node is list
    if (isRoot) {
      cout << "(";
    }
    leftChild->printListNotation(true);									// recursively print left subtree
    if (!rightChild->isAtom) {
      cout << " ";
    }
    if (rightChild->isAtom) {											// check if last inner node in list before right atom leaf
      if (rightChild->name == "NIL") {									// right child is atom, not list
        cout << ")";
      } else {
        cout << " . ";
        if (rightChild->atomType == AtomType::NUMERIC) {				// right child is numeric atom
	  cout << rightChild->value;
        } else {														// right child is literal atom
          cout << rightChild->name;
        }
        cout << ")";
      }
    } else {															// right child is list; continue printing right tree
      rightChild->printListNotation(false);
    }
  }
}

// deprecated print format used in project 2
void Node::printDotNotation() {
  if (isAtom) {															// node is atom
    if (atomType == AtomType::NUMERIC) {
      cout << value;
    } else {
      cout << name;
    }    
  } else {																// node is list
    cout << "(";
    leftChild->printDotNotation();
    cout << " . ";
    rightChild->printDotNotation();
    cout << ")";
  }
}


