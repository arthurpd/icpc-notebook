#include "../../contest/header.hpp"

/*
	Prefix Function and KMP:
		Computes prefix function for a given string in O(n).
		String matching in O(n + m).
		No need to be strings, you can use vector<int> since the
		algorithms don't depend on the alphabet size, they only perform equality comparisons.
		Usage is explained in each function.

	Author: Arthur Pratti Dadalto
*/

// Returns the prefix function for the given string.
// pi[i] for 0 <= i <= s.size() (s.size() + 1 elements).
// pi[i] considers the prefix of string s having size i.
// pi[i] is the size of its (the prefix's) largest proper prefix which is also a suffix.
// For "aabaaab", pi is is {0,0,1,0,1,2,2,3}
template <class T>
vector<int> prefix_function(T s)
{
	vector<int> pi(s.size() + 1, 0);
	for (int i = 2; i <= s.size(); i++)
	{
		int j = pi[i - 1];				  // j is the size of the candidate prefix to expand.
		while (j > 0 && s[j] != s[i - 1]) // While we still have a candidate prefix and it can't be expanded.
			j = pi[j];					  // Go to the next candidate prefix.

		// If candidate prefix can be expanded, do it. Otherwise, there is no prefix that is also a suffix.
		pi[i] = s[j] == s[i - 1] ? j + 1 : 0;
	}

	return pi;
}

// Returns a sorted list of all positions in the text string where begins an ocurrence of the key string.
// e.g. kmp("aabaaab", "aab") returns {0, 4}.
template <class T>
vector<int> kmp(T text, T key)
{
	vector<int> retv;
	vector<int> pi = prefix_function(key);
	for (int i = 0, match = 0; i < text.size(); i++) // There is no need to have the entire text in memory, you could do this char by char.
	{
		// match stores the size of the prefix of the key which is a suffix of the current processed text.
		while (match > 0 && text[i] != key[match])
			match = pi[match];
		if (text[i] == key[match])
			match++;

		if (match == key.size())
		{
			retv.push_back(i - match + 1);
			match = pi[match]; // To avoid access to key[key.size()] in next iteration.
		}
	}

	return retv;
}
