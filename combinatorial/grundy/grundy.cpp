
#include "../../contest/header.hpp"

/*
	Mex for Grundy Number O(N):
		To calculate the Grundy Number for a set of states, first 
		set terminal states' Grundy Number (zero if no move is a 
		loss condition).
		Then, for each state, find the MEX for the Grundy Numbers of 
		reacheable states (i.e. the lowest Grundy Number not 
		present). 
		This will be the current state's Grundy Number.
		If you have many parallel games, you can find the equivalent 
		Grundy number by doing XOR of individual Grundy Numbers. 
		0 equals losing position, any other value is a winning 
		position.

	Constraints:
		The game must be symmetrical (same moves are available for 
		both players); have perfect information (no hidden or 
		random stuff); 
		be finite (no loops).

	Usage:
		For each state, save the Grundy Number of all reacheble 
		states in a vector v, and pass as argument to mex().


	Source: my head
*/
 
int mex(vector<int> v){
	//Place every value in the position with same index (if possible 
	//and it's not already there)
	for(int i = 0; i < v.size(); i++){
		while(v[i] < v.size() && v[v[i]] != v[i])
			swap(v[v[i]], v[i]);
	}
	//Verify the first missing number 
	for(int i = 0; i < v.size(); i++)
		if(v[i] != i)
			return i;
	
	return v.size();
}
