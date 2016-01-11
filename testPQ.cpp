/*
	Compile this test against your .h files to make sure they compile. Note how the eecs281 priority queues can be constructed with the different types.  We suggest adding to this file or creating your own test cases to test your priority queue implementations. 
*/

#include "Eecs281PQ.h"
#include "SortedPQ.h"
#include "BinaryPQ.h"
#include "PairingPQ.h"
#include <vector>
#include <assert.h>
#include <iostream>
using std::vector;

//void testSorted(vector<int>&);
void testBinary(vector<int>&);
//void testPairing(vector<int>&);
using namespace std;
int main()
{
	vector<int> vec;
	//vec.push_back(0);
	//vec.push_back(1);
	vec.push_back(2);
	vec.push_back(1);
	vec.push_back(4);
	vec.push_back(23);
	vec.push_back(15);
	vec.push_back(9);
	vec.push_back(24);
	vec.push_back(8);
	vec.push_back(17);
	vec.push_back(15);
	/*
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(17);
	vec.push_back(8);
	vec.push_back(9);
	*/

	//testSorted(vec);
	//testBinary(vec);
	
	Eecs281PQ<int> * pq1 = new PairingPQ<int>(vec.begin(), vec.end());
	Eecs281PQ<int> * pq2 = new PairingPQ<int>(*((PairingPQ<int> *)pq1));
	//This line is different just to show two different ways to declare a pairing heap:
	//	as an Eecs281PQ and as a PairingPQ. Yay for inheritance!
	//PairingPQ<int> * pq2 = new PairingPQ<int>();
	// *pq2 = *((PairingPQ<int> *)pq1);

	
	//pq1->push(3);
	//assert(pq1->top() == 16);
	//pq2->pop();
	//pq1->pop();

	/*
	pq1->size();
	pq1->empty();
	assert(pq1->top() == 14);
	pq1->pop();
	assert(pq1->top() == 5);
	//pq1->pop();
	//assert(pq1->top() == 4);
	pq1->push(13); 
	pq1->push(6); 
	assert(pq1->top() == 13);
	pq1->push(20);
	assert(pq1->top() == 20); 
	cout << pq2->top() << endl;
	*/

	//cout << "fdgsdfg" << endl;
	
	assert(pq2->top() == 24);
	assert(pq2->size() == 10);
	//pq2->pop();
	pq2->pop();
	assert(pq2->size() == 9);
	assert(pq2->empty() == false);
	//cout << pq2->top() << endl;
	assert(pq2->top() == 23);
	pq2->pop();
	assert(pq2->size() == 8);
	assert(pq2->top() == 17);
	//pq1->pop();
	//assert(pq1->top() == 4);
	pq2->pop();
	assert(pq2->size() == 7);
	//pq2->push(13); 
	//pq2->push(6); 
	assert(pq2->top() == 15);
	pq2->pop();
	assert(pq2->size() == 6);
	//pq2->push(20);
	assert(pq2->top() == 15); 
	pq2->pop();
	assert(pq2->size() == 5);
	//pq2->push(20);
	assert(pq2->top() == 9); 
	pq2->pop();
	assert(pq2->size() == 4);
	//pq2->push(20);
	assert(pq2->top() == 8);
	pq2->pop();
	assert(pq2->size() == 3);
	//pq2->push(20);
	assert(pq2->top() == 4);
	pq2->pop();
	assert(pq2->size() == 2);
	//pq2->push(20);
	assert(pq2->top() == 2);
	pq2->pop();
	assert(pq2->size() == 1);
	//pq2->push(20);
	assert(pq2->top() == 1);
	pq2->pop();
	assert(pq2->size() == 0);
	cout << "wwwww" << endl;
	assert(pq2->empty() == true);
	cout << "wwwww" << endl;
	


	delete pq1;
	delete pq2;
	
	
}

/*
void testSorted(vector<int> & vec)
{
	Eecs281PQ<int> * pq1 = new SortedPQ<int>(vec.begin(), vec.end());
	pq1->push(3);
	pq1->pop();
	pq1->size();
	pq1->empty();
	assert(pq1->top() == 1);
	cout << "here" << endl;
	delete pq1;
}
*/

/*
void testBinary(vector<int> & vec)
{
	Eecs281PQ<int> * pq1 = new BinaryPQ<int>(vec.begin(), vec.end());
	//cout << pq1->top() << endl;
	assert(pq1->size() == 10);
	assert(pq1->top() == 24); 
	pq1->pop();
	cout << pq1->size() << endl;
	assert(pq1->top() == 23);
	pq1->pop();
	cout << pq1->size() << endl;
	assert(pq1->top() == 17);
	pq1->pop();
	cout << pq1->size() << endl;
	assert(pq1->top() == 15);
	pq1->pop();
	cout << pq1->size() << endl;
	assert(pq1->top() == 15);
	assert(pq1->size() == 6);
	pq1->pop();
	cout << pq1->size() << endl;
	pq1->pop();
	cout << pq1->size() << endl;
	pq1->pop();
	cout << pq1->size() << endl;
	pq1->pop();
	cout << pq1->size() << endl;
	pq1->pop();
	cout << pq1->size() << endl;
	pq1->pop();
	cout << pq1->size() << endl;
	if(!(pq1->empty())) {
		cout << "Holla" << endl;
	}

	//assert(pq1->top() == 14);
	//pq1->pop();
	//assert(pq1->top() == 13);
	delete pq1;
}
*/


/*
void testPairing(vector<int> & vec)
{
	Eecs281PQ<int> * pq1 = new PairingPQ<int>(vec.begin(), vec.end());
	Eecs281PQ<int> * pq2 = new PairingPQ<int>(*((PairingPQ<int> *)pq1));
	//This line is different just to show two different ways to declare a pairing heap:
	//	as an Eecs281PQ and as a PairingPQ. Yay for inheritance!
	//PairingPQ<int> * pq2 = new PairingPQ<int>();
	// *pq2 = *((PairingPQ<int> *)pq1);

	
	//pq1->push(3);
	//assert(pq1->top() == 16);
	//pq2->pop();
	//pq1->pop();


	pq1->size();
	pq1->empty();
	assert(pq1->top() == 14);
	pq1->pop();
	assert(pq1->top() == 5);
	//pq1->pop();
	//assert(pq1->top() == 4);
	pq1->push(13); 
	pq1->push(6); 
	assert(pq1->top() == 13);
	pq1->push(20);
	assert(pq1->top() == 20); 
	cout << pq2->top() << endl;
	


	//cout << "fdgsdfg" << endl;
	assert(pq2->top() == 24);
	assert(pq2->size() == 10);
	//pq2->pop();
	pq2->pop();
	assert(pq2->size() == 9);
	assert(pq2->empty() == false);
	//cout << pq2->top() << endl;
	assert(pq2->top() == 23);
	pq2->pop();
	assert(pq2->size() == 8);
	assert(pq2->top() == 17);
	//pq1->pop();
	//assert(pq1->top() == 4);
	pq2->pop();
	assert(pq2->size() == 7);
	//pq2->push(13); 
	//pq2->push(6); 
	assert(pq2->top() == 15);
	pq2->pop();
	assert(pq2->size() == 6);
	//pq2->push(20);
	assert(pq2->top() == 15); 
	pq2->pop();
	assert(pq2->size() == 5);
	//pq2->push(20);
	assert(pq2->top() == 9); 
	pq2->pop();
	assert(pq2->size() == 4);
	//pq2->push(20);
	assert(pq2->top() == 8);
	pq2->pop();
	assert(pq2->size() == 3);
	//pq2->push(20);
	assert(pq2->top() == 4);
	pq2->pop();
	assert(pq2->size() == 2);
	//pq2->push(20);
	assert(pq2->top() == 2);
	pq2->pop();
	assert(pq2->size() == 1);
	//pq2->push(20);
	assert(pq2->top() == 1);
	pq2->pop();
	assert(pq2->size() == 0);
	cout << "wwwww" << endl;
	assert(pq2->empty() == true);
	cout << "wwwww" << endl;



	delete pq1;
	delete pq2;
	//delete pq3;
}
*/



