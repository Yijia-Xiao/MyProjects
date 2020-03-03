#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstdlib>
struct Node {
	char c;
	Node* nex, * pre;
	Node(char _c = '\0', Node* _n = nullptr, Node* _p = nullptr) { c = _c; nex = _n; pre = _p; }
}head, tail;
struct Cursor {
	Node* left;
	Node* right;
	Cursor(Node* _l = nullptr, Node* _r = nullptr) { left = _l; right = _r; }
}l, r;
Node* tmp;
Node* storer;
// Here, we pack the commands into functions to make the program more readable
// ll means left cursor move left, lr means left crusor move right
inline void ll();
inline void lr();
inline void rl();
inline void rr();
// dl mean delete using left cursor
// dr mean delete using right cursor
inline void dl();
inline void dr();
// insl means insert using left cursor
inline void insl(char);
inline void insr(char);
// revr means reverse
inline void revr();
inline void show();
// exp means 'explanation', this is used for showing the nodes and cursors (in dubugging)
inline void exp();
int order;
// The use of 'order' is to indicate the relative position of left and right cursor
inline void swap(Node& a, Node& b) { Node temp = a;  a = b; b = temp; }
int main() {
	// Initializing the data, and and list
	int lines;
	char* ori = new char[3200010]();
	char* cmd = new char[10]();
	// read in data
	scanf("%s", ori);
	scanf("%d", &lines);
	// connect the head and tail
	head.nex = &tail;
	tail.pre = &head;
	Node* cur = &head;
	int index = 0;
	// begin converting chars to nodes and fully connect them
	while (ori[index]) {
		Node* node = new Node;
		(*node).c = ori[index];
		(*node).pre = cur;
		(*cur).nex = node;
		cur = node;
		index++;
	}
	order = index;
//	printf("%d", order);
	tail.pre = cur; (*cur).nex = &tail;
	// Until here, the chain is fully connected!
	// Initialing the cursors below
	l.left = &head; l.right = head.nex;
	r.left = tail.pre; r.right = &tail;
	// read in the '\n'
	gets(cmd);
	while (lines--)
	{
		// read in the command
		gets(cmd);
		switch (cmd[0])
		{
			// for this part, we just need to find the meaning of the command, and then call the corresponding function 
		case '<':
			if (cmd[2] == 'L')
				ll();
			else
				rl();
			break;
		case '>':
			if (cmd[2] == 'L')
				lr();
			else
				rr();
			break;
		case 'I':
			if (cmd[2] == 'L')
				insl(cmd[4]);
			else
				insr(cmd[4]);
			break;
		case 'D':
			if (cmd[2] == 'L')
				dl();
			else
				dr();
			break;
		case 'R':
			revr();
			break;
		case 'S':
			show();
			break;
		default:
			break;
		}
//		exp();
	}
	return 0;
}

inline void ll() {
	// if the move is not valid
	if (l.left == &head) {
		printf("F\n");
		return;
	}
	else
		printf("T\n");
	order++;
	tmp = l.left;
	// here the if - else below is used for judging 
	// judging whether the node on the opposite side of right is left.nex or left.pre
	// the other 3 move function are similar
	if (l.left->nex == l.right)
		l.left = l.left->pre;
	else
		l.left = l.left->nex;

	l.right = tmp;
}
inline void lr() {
	// if the move is not valid
	if (l.right == &tail) {
		printf("F\n");
		return;
	}
	else
		printf("T\n");
	
	order--;
	tmp = l.right;
	
	if (l.right->pre == l.left)
		l.right = l.right->nex;
	else
		l.right = l.right->pre;

	l.left = tmp;
}
inline void rl() {
	// if the move is not valid
	if (r.left == &head) {
		printf("F\n");
		return;
	}
	else
		printf("T\n");

	order--;
	tmp = r.left;

	// here the if - else below is used for judging 
	// judging whether the node on the opposite side of left is right.nex or right.pre
	// the other 3 move function are similar
	if (r.left->nex == r.right)
		r.left = r.left->pre;
	else
		r.left = r.left->nex;

	r.right = tmp;
}
inline void rr() {
	// if the move is not valid
	if (r.right == &tail) {
		printf("F\n");
		return;
	}
	else
		printf("T\n");

	order++;
	tmp = r.right;

	if (r.right->pre == r.left)
		r.right = r.right->nex;
	else
		r.right = r.right->pre;

	r.left = tmp;
}

inline void dl() {
	// if is not valid
	if (l.right == &tail) {
		printf("F\n");
		return;
	}
	else {
		printf("T\n");
		// nn is used for storing a Node* type value temporarily
		Node* nn;
		// case 1 : left cursor's right node* 's next node is left cursor's left
		if (l.right->nex == l.left) {
			nn = l.right->pre;
			l.right->c = '\0';
			if (l.left->nex == l.right)
				l.left->nex = nn;
			else
				l.left->pre = nn;
			
			if (nn->pre == l.right)
				nn->pre = l.left;
			else
				nn->nex = l.left;
		}
		// case 2: the opposite case
		else {
			nn = l.right->nex;
			l.right->c = '\0';
			if (l.left->nex == l.right)
				l.left->nex = nn;
			else
				l.left->pre = nn;

			if (nn->pre == l.right)
				nn->pre = l.left;
			else
				nn->nex = l.left;
		}
		// assigning the temp value nn to l.right
		l.right = nn;
		
		// the 'order' is used for storing the relative position of two cursors
		// same position
		if (order == 0) {
			r.left = l.left;
			r.right = l.right;
		}
		// distance is 1, and left cursor is on the left of right
		else if (order == 1) {
			order--;
			r.left = l.left;
			r.right = l.right;
		}
		// dis >= 2
		else if (order > 1) {
			order--;
		}
		// the other cases will not influence order 
		else {
			
		}
	}
}
inline void dr() {
	// if is not valid
	if (r.right == &tail) {
		printf("F\n");
		return;
	}
	else {
		printf("T\n");
		Node* nn;
		if (r.right->nex == r.left) {
			nn = r.right->pre;
			r.right->c = '\0';
			if (r.left->nex == r.right)
				r.left->nex = nn;
			else
				r.left->pre = nn;

			if (nn->pre == r.right)
				nn->pre = r.left;
			else
				nn->nex = r.left;
		}
		else {
			nn = r.right->nex;
			r.right->c = '\0';
			if (r.left->nex == r.right)
				r.left->nex = nn;
			else
				r.left->pre = nn;

			if (nn->pre == r.right)
				nn->pre = r.left;
			else
				nn->nex = r.left;
		}
		r.right = nn;
		// the 'order' is used for storing the relative position of two cursors
		// same position
		if (order == 0) {
			l.left = r.left;
			l.right = r.right;
		}
		else if (order == -1) {
			order++;
			l.left = r.left;
			l.right = r.right;
		}
		else if (order < -1) {
			order++;
		}
		// the other cases will not influence order 
		else {

		}
	}
}
inline void insl(char c) {
	// pos is used for whether the 2 cursors are at the same position
	// at first we assume it is not 
	bool pos = false;
	if (l.left == r.left && l.right == r.right)
		pos = true;

	if (order < 0)
		order--;
	
	Node* ins = new Node;
	ins->c = c;
	ins->pre = l.left;
	ins->nex = l.right;
	if (l.left->nex == l.right)
		l.left->nex = ins;
	else
		l.left->pre = ins;

	if (l.right->pre == l.left)
		l.right->pre = ins;
	else
		l.right->nex = ins;
	l.left = ins;
	if (pos) {
		r.left = l.left;
		r.right = l.right;
	}
	printf("T\n");
}
inline void insr(char c) {
	// pos is used for whether the 2 cursors are at the same position
	// at first we assume it is not 
	bool pos = false;
	// the same position
	if (l.left == r.left && l.right == r.right)
		pos = true;

	if (order > 0)
		order++;
	
	Node* ins = new Node;
	ins->c = c;
	ins->pre = r.left;
	ins->nex = r.right;
	if (r.left->nex == r.right)
		r.left->nex = ins;
	else
		r.left->pre = ins;

	if (r.right->pre == r.left)
		r.right->pre = ins;
	else
		r.right->nex = ins;
	r.left = ins;
	if (pos) {
		l.left = r.left;
		l.right = r.right;
	}
	printf("T\n");
}

inline void revr() {
	Node* carry;
	// the same position or not in order
	if (order <= 0) {
	// if not valid
		printf("F\n");
		return;
	}
	else {
		// we need to connect 4 Node*
		if (l.left->nex == l.right)
			l.left->nex = r.left;
		else
			l.left->pre = r.left;

		if (l.right->nex == l.left)
			l.right->nex = r.right;
		else
			l.right->pre = r.right;

		if (r.left->nex == r.right)
			r.left->nex = l.left;
		else
			r.left->pre = l.left;

		if (r.right->nex == r.left)
			r.right->nex = l.right;
		else
			r.right->pre = l.right;
		carry = l.right;
		l.right = r.left;
		r.left = carry;
		printf("T\n");
	}
}
inline void show() {
	// just show one by one iteratively
	tmp = head.nex;
	storer = tmp;
	// Here storer is for storing tmp temporarily
	Node* pre = &head;
	while (tmp->c) {
		storer = tmp;
		printf("%c", tmp->c);
		if (tmp->nex == pre)
			tmp = tmp->pre;
		else
			tmp = tmp->nex;
		pre = storer;
	}
	printf("\n");
}
// show nodes and cursors, for debugging
/*
inline void exp() {
	tmp = head.nex;
	storer = tmp;
	// Here storer is for storing tmp temporarily
	Node* pre = &head;
	while (tmp->c) {
		storer = tmp;

		printf("%c", tmp->c);

		if (l.left == tmp)
			printf("[");
		if (r.left == tmp)
			printf("]");

		if (tmp->nex == pre)
			tmp = tmp->pre;
		else
			tmp = tmp->nex;
		pre = storer;
	}
	printf("\n");
}
*/