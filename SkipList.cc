#include <bits/stdc++.h>
using namespace std;

// Class to implement node
class Node
{
	public:
		int key;

		// Array to hold pointers to node of different level 
		Node **forward;
		Node(int, int);
};

Node::Node(int key, int level)
{
	this->key = key;

	// Allocate memory to forward 
	forward = new Node*[level+1];

	// Fill forward array with 0(NULL)
	memset(forward, 0, sizeof(Node*)*(level+1));
};

// Class for Skip list
class SkipList
{
	// Maximum level for this skip list
	int MAXLVL;

	// P is the fraction of the nodes with level 
	// i pointers also having level i+1 pointers
	float P;

	// current level of skip list
	int level;

	// pointer to header node
	Node *header;
	public:
	SkipList(int, float);
	int randomLevel();
	Node* createNode(int, int);
	void insertElement(int);
	void deleteElement(int);
	void searchElement(int);
	void displayList();
	
	//get number of lists and count data's additional copy average 
	int getlevel();
	float count;
};

SkipList::SkipList(int MAXLVL, float P)
{
	this->MAXLVL = MAXLVL;
	this->P = P;
	level = 0;
	count = 0;
	// create header node and initialize key to -1
	header = new Node(-1, MAXLVL);
};

// create random level for node
int SkipList::randomLevel()
{
	float r = (float)rand()/RAND_MAX;
	int lvl = 0;
	while(r < P && lvl < MAXLVL)
	{
		lvl++;
		r = (float)rand()/RAND_MAX;
	}
	
	//count data's additional copy
	count += lvl;
	return lvl;
};

// create new node
Node* SkipList::createNode(int key, int level)
{
	Node *n = new Node(key, level);
	return n;
};

//get number of lists
int SkipList::getlevel()
{
	return level;
}

// Insert given key in skip list
void SkipList::insertElement(int key)
{
	Node *current = header;

	// create update array and initialize it
	Node *update[MAXLVL+1];
	memset(update, 0, sizeof(Node*)*(MAXLVL+1));

	/*    start from highest level of skip list
		  move the current pointer forward while key 
		  is greater than key of node next to current
		  Otherwise inserted current in update and 
		  move one level down and continue search
	 */
	for(int i = level; i >= 0; i--)
	{
		while(current->forward[i] != NULL &&
				current->forward[i]->key < key)
			current = current->forward[i];
		update[i] = current;
	}

	/* reached level 0 and forward pointer to 
	   right, which is desired position to 
	   insert key. 
	 */
	current = current->forward[0];

	/* if current is NULL that means we have reached
	   to end of the level or current's key is not equal
	   to key to insert that means we have to insert
	   node between update[0] and current node */
	if (current == NULL || current->key != key)
	{
		// Generate a random level for node
		int rlevel = randomLevel();
		/* If random level is greater than list's current
		   level (node with highest level inserted in 
		   list so far), initialize update value with pointer
		   to header for further use */
		if(rlevel > level)
		{
			for(int i=level+1;i<rlevel+1;i++)
				update[i] = header;

			// Update the list current level
			level = rlevel;
		}
		
		// create new node with random level generated
		Node* n = createNode(key, rlevel);

		// insert node by rearranging pointers 
		for(int i=0;i<=rlevel;i++)
		{
			n->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = n;
		}		
	}
};

// Search for element in skip list
void SkipList::searchElement(int key)
{
	Node *current = header;

	/*    start from highest level of skip list
		  move the current pointer forward while key 
		  is greater than key of node next to current
		  Otherwise inserted current in update and 
		  move one level down and continue search
	 */
	for(int i = level; i >= 0; i--)
	{
		while(current->forward[i] &&
				current->forward[i]->key < key)
			current = current->forward[i];

	}

	/* reached level 0 and advance pointer to 
	   right, which is possibly our desired node*/
	current = current->forward[0];

	// If current node have key equal to
	// search key, we have found our target node
	
	/*if(current and current->key == key) 
		cout<<"Found key: "<<key<<"\n";
	*/
};

int main(){
	
	//0.9 is head's probability, can change to 0.1 or 0.5
	SkipList sk(400,0.9);

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<unsigned long long> dis(1, pow(2,30));

	for(int pow=10;pow <= 30;++pow){
		int num = 1 << pow;
		int *arr = new int[num];
		clock_t start,end;
		for(int j=0;j<num;++j){
			*(arr+j) =  dis(gen);
		}
		start = clock();

		for(int i = 0; i < num; ++i)
			sk.insertElement(arr[i]);

		end = clock();
		
		double ans1;
		ans1 = ((double) (end - start)) / CLOCKS_PER_SEC;

		start = clock();

		for(int i = 0; i < 100000; ++i){
			sk.searchElement(dis(gen));
		}

		end = clock();
		
		double ans2;
		ans2 = ((double) (end-start)) / CLOCKS_PER_SEC;
		
		cout << pow << ", " << ans1 << ", " << ans2 << ", " << sk.getlevel() << ", " << sk.count/(float)num << endl;
		delete [] arr;
	}

	return 0;
}

