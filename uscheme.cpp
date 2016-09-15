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
    Node() {
	value="";
	left=nullptr; right=nullptr;
    }
    Node(string v, Node *l, Node *r) {
	value=v;
	left=l;
	right=r;
    } 
    string value;
    Node * left;
    Node * right;

    friend ostream &operator<<(ostream &os, const Node &n);
};


ostream &operator<<(ostream &os, const Node &n) {
    stack<Node> nums;
    stack<bool> side;
    int num_right = 2;
    nums.push(n);

    while(!nums.empty()) {
        Node temp = nums.top();
        nums.pop();
	if(!side.empty()) {
            if(side.top()) {
                cout << "left=";
		cout << "(Node: value=";
                cout << temp.value;
		if(isdigit(temp.value[0])) {cout << ")";}
            }
            else {
                cout << "right=";
		cout << "(Node: value=";
                cout << temp.value;
                if(isdigit(temp.value[0])) {
		    for(int j = 0; j < num_right; j++) {   
			cout << ")";
		    }
		    num_right++;
		}
            }
	    side.pop();
	    if(!nums.empty() && side.empty()) {cout << ", ";}
        }
	else {
            cout << "(Node: value=";
            cout << temp.value;      
            cout << ", ";
	}
	if(temp.right) {
            nums.push(*temp.right);
            side.push(0);
        }
        if(temp.left) { 
	    nums.push(*temp.left);
            side.push(1);
        }
    }
    return os;
}

// Parser ----------------------------------------------------------------------

string parse_token(istream &s) {
    string token;
    char next;
    char temp;
    next = s.peek();
    if(isspace(next)) {
        temp = s.get();
    }
    
    next = s.peek();
    if((next == '(') || (next == ')') || (next == '+') || (next == '-') || (next == '*') || (next == '/')) {
        token = s.get();
    }
    else {
        char next_num = s.peek();
        while(isdigit(next_num)) {
	    token = token + to_string(s.get()-'0');
	    next_num = s.peek();
        }
    }
    return token;
}

Node *parse_expression(istream &s) {
    string token = parse_token(s);
    Node *left=nullptr; Node *right=nullptr; 
    if((token == "") || (token == ")")) {
	cout << NULL;
	return nullptr;
    }
    else if(token == "(") { 
  	token = parse_token(s);
        left = parse_expression(s);
        if(left) {
            right = parse_expression(s);
        }
        if(right) {
            parse_token(s);
        }
    }
    return new Node(token,left,right);
}

// Interpreter -----------------------------------------------------------------

void evaluate_r(const Node *n, stack<int> &s) {
    cout<<"yo"<<endl;
    if(n->left) {
        evaluate_r(n->left, s);
        evaluate_r(n->right, s);
    }
    if(isdigit(n->value[0])) {
        s.push(atoi(n->value.c_str()));
    }
    else {
        int first = s.top();
        s.pop();
        int second = s.top();
        s.pop();
        if(n->value == "+") {
            s.push(first + second);
        }
        if(n->value == "-") {
            s.push(first - second);
        }
        if(n->value == "/") {
            s.push(first / second);
        }
        if(n->value == "*") {
            s.push(first * second);
        }
    }
}

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

        //cout << evaluate(n) << endl;

        delete n;
    }

    return 0;
}

