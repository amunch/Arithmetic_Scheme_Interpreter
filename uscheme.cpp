// uscheme.cpp
//By Mark Pruitt and Andrew Munch

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unistd.h>

using namespace std;

// Globals ---------------------------------------------------------------------

bool BATCH = false;
bool DEBUG = false;

// Structures ------------------------------------------------------------------

struct Node {
    Node() { // constructor
	value=""; //empty string
	left=nullptr; right=nullptr; //null children
    }
    Node(string v, Node *l, Node *r) { //constructor with values
	value=v; //set value
	//set children
	left=l;
	right=r;
    } 
    ~Node() { //deconstructor
	if(left) //is left not null
	    delete left; //DELETE IT!!!
	if(right) //is right not null
	    delete right; //BURN IT WITH FIRE
    }
    string value; //value of the node
    //children
    Node * left;
    Node * right;
    //override << operator
    friend ostream &operator<<(ostream &os, const Node &n);
};

//overide <<
ostream &operator<<(ostream &os, const Node &n) {
    cout << "(Node: value=";
    cout << n.value; //print value of node n
    if(n.left) { //is left not null which means right is also not null
	cout << " left=";
	os << *n.left; //print left recursively
	cout << " right=";
    	os << *n.right; //print right recursively
    }
    cout << ")";

    return os;
}

// Parser ----------------------------------------------------------------------
//get the next operator or number
string parse_token(istream &s) {
    string token;
    char next;
    char temp;
    next = s.peek(); //get the next without popping it off
    if(isspace(next)) { //if a space then move on
        temp = s.get(); //just get in a temp variable to throw away
    }
    
    next = s.peek(); //peak again to see next item
    //is a operator aka non number
    if((next == '(') || (next == ')') || (next == '+') || (next == '-') || (next == '*') || (next == '/')) {
        token = s.get(); //get it
    }
    else { //a number then
        char next_num = s.peek();
        while(isdigit(next_num)) { //while we have digits to get
	    token = token + to_string(s.get()-'0'); //add on the next digit and convert to int
	    next_num = s.peek();
        }
    }
    return token;
}
//put together the tree
Node *parse_expression(istream &s) {
    string token = parse_token(s); //get the operator or number
    Node *left=nullptr; Node *right=nullptr; 
    if((token == "") || (token == ")")) { //we are done here so return null
	return nullptr;
    }
    else if(token == "(") { //got a operator to follow (
  	token = parse_token(s); //get the operator
        left = parse_expression(s); //do same on next number or operator
        if(left) { //does it exist?
            right = parse_expression(s); //do it on right too
        }
        if(right) { //right exist?
            parse_token(s);
        }
    }
    return new Node(token,left,right);
}

// Interpreter -----------------------------------------------------------------
//recursive helper function to eveluate
void evaluate_r(const Node *n, stack<int> &s) {
    if(n->left) { //does left exist so right also does
        evaluate_r(n->left, s); //do same on left
        evaluate_r(n->right, s); //and right
    }
    if(isdigit(n->value[0])) { //is a digit
        s.push(atoi(n->value.c_str())); //add the value to the stack
    }
    else { //not a digit so operator
        int first = s.top(); //first digit
        s.pop();
        int second = s.top(); //second
        s.pop();
        if(n->value == "+") { //add
            s.push(second + first);
        }
        if(n->value == "-") { //subtract
            s.push(second - first);
        }
        if(n->value == "/") { //divide
            s.push(second / first);
        }
        if(n->value == "*") { //multiply
            s.push(second * first);
        }
    }
}
//evaluate by going through the tree
int evaluate(const Node *n) {
    stack<int> s;
    evaluate_r(n, s);
    return s.top();
}

// Main execution --------------------------------------------------------------

int main(int argc, char *argv[]) {
    string line;
    int c;

    while ((c = getopt(argc, argv, "bdh")) != -1) {
        switch (c) {
            case 'b': BATCH = true; break;
            case 'd': DEBUG = true; break;
            default:
                cerr << "usage: " << argv[0] << endl;
                cerr << "    -b Batch mode (disable prompt)"   << endl;
                cerr << "    -d Debug mode (display messages)" << endl;
                return 1;
        }
    }

    while (!cin.eof()) {
        if (!BATCH) {
            cout << ">>> ";
            cout.flush();
        }

        if (!getline(cin, line)) {
            break;
        }

        if (DEBUG) { cout << "LINE: " << line << endl; }

        stringstream s(line);
        Node *n = parse_expression(s);
        if (DEBUG) { cout << "TREE: " << *n << endl; }

        cout << evaluate(n) << endl;

        delete n;
    }

    return 0;
}

