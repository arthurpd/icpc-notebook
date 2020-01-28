/*
	Suffix Tree:
        A compressed trie is a trie where all reduntant nodes are 
        eliminated by allowing edges to hold substrings.
        A Suffix Tree is a Trie containig all the suffixes of a 
        certain string S.
        Using a dummy character in the end of S gurantees that all 
        suffixes end in leafs, and vice-vers.
        This code builds the Suffix Tree in O(|S|*lg|Alph|) time and 
        O(|S|) memory (where |Alph| is the size of the alphabet).

	Example:
		A dfs through the Suffix Tree of "banana$" looks like:
        Begin in root
        Enter through "$"
        Leave through "$"
        Enter through "na"
        Enter through "$"
        Leave through "$"
        Enter through "na$"
        Leave through "na$"
        Enter through "banana$"
        Leave through "banana$"
        Enter through "a"
        Enter through "$"
        Leave through "$"
        Enter through "na"
        Enter through "$"
        Leave through "$
        Enter through "na$"
        Leave through "na$"
        Leave through "na"
        Leave through "a"

	Usage:
		Create an object Suffix Tree st passing the string as 
        argument, and optionally the dummy character as second 
        argument.
        "verify_substring(P)" checks in O(|P|) if P is a substring of 
        S.
        

	Author: Augusto Damschi Bernardi
    Based on: https://bcc.ime.usp.br/tccs/2016/yancouto/tcc.pdf
*/
#include "../../contest/header.hpp"

struct node{
    // Each node keeps information about the edge arriving into it.

    // Keeps left and right index of edge's substring in S. 
    // (may not be the same occurrence one, see "aba$"); 
    int left, right;

    // *parent points to parent node
    // *suffix points to node corresponding to [left+1...right] 
    // (by the end of the process exists for every node other than 
    // the root)
    node *parent, *suffix;

    //next_node[c] points to the kid of current node whose edge
    // begins with character c (only one by character).
    map<char, node*> next_node;

    node(int _left, int _right, node *_parent):
    left(_left), right(_right), parent(_parent){}

    ~node(){
        for(auto child : next_node)
            delete child.second;   
    }

    //Lenght of current edge
    int len(){
        return right - left + 1;
    }

    //Convinient way to find kid
    node* next(char c){
        if(next_node.count(c))
            return next_node[c];
        return NULL;
    }

};

struct suffix_tree{
    node *root;
    char dummy;
    string s;

    suffix_tree(string _s, char _dummy = '$')
    {
		s = _s;
		dummy = _dummy;
        s += dummy;
        root = new node(0, -1, NULL);
        // In the beginning of iteration i,j, node cur_node in 
        // [left...cur_dist] represents [i...j-1]
        // need_suffix points to node that doesn't have a suffix yet 
        // (at most one at a time, for at most one iteration of i)
        node *cur_node = root;
        int cur_dist = -1, i = 0;

        //Invariants:        
        //  *At the beginning of step i,j, s[i...j-1] and all of it's 
        // suffixes are inserted in the suffix trie
        //  *At the beggining of step i,j, cur_node[cur_dist] is the 
        // end point representing s[i...j-1]
        //  *At any increment of i, at most one node doesn't have 
        // "suffix" field defined, and it's stored in "need_suffix"
        for(int j = 0; j < (int)s.size(); j++){
            char c = s[j];
            node *need_suffix = NULL;
            while(i <= j){
                // Inserts s[i...j]

                // Case 1: s[i...j] already exists in the suffix tree
                // If it's in the next node, move to it
                if(cur_dist == cur_node->len() - 1 and cur_node->next(c) != NULL){
                    cur_node = cur_node->next(c);
                    cur_dist = -1;
                }
                // If now we have to take one more char from the
                // edge, take it
                if(cur_dist < cur_node->len() - 1 and get_char(cur_node, cur_dist + 1) == c){
                    cur_dist += 1;
                    break;
                }
				
                // Case 2: s[i...j-1] ends in a node
                if(cur_dist == cur_node->len() - 1){
                    cur_node->next_node[c] = new node(j, s.size() - 1, cur_node);
                    // Puts cur_node in s[i_1...j-1]
                    if(cur_node != root){
                        cur_node = cur_node->suffix;
                        cur_dist = cur_node->len() - 1;
                    }
                }

                // Caso 3: s[i...j-1] ends in an edge
                else{
                    // Creates a new node and splits the edge
                    node *mid = new node(cur_node->left, cur_node->left + cur_dist, cur_node->parent);
                    cur_node->parent->next_node[get_char(mid, 0)] = mid;
                    mid->next_node[get_char(cur_node, cur_dist + 1)] = cur_node;
                    cur_node->parent = mid;
                    cur_node->left += cur_dist + 1;
                    mid->next_node[s[j]] = new node(j, s.size() - 1, mid);
                    // Sets any missing suffix link
                    if(need_suffix != NULL)
                        need_suffix->suffix = mid;
                    // Tries to find the suffix link for "mid"
                    cur_node = mid->parent;
                    int g;
                    if(cur_node != root){
                        cur_node = cur_node->suffix;
                        g = j - cur_dist - 1;
                    }
                    else
                        g = i + 1;
                    // Initially cur_node points to node 
                    // [i+1 ... g-1]
                    while(g < j and g + cur_node->next(s[g])->len() <= j){
                        cur_node= cur_node->next(s[g]);
                        g += cur_node->len();
                    }
                    // Case where suffix link was found
                    if(g == j){
                        need_suffix = NULL;
                        mid->suffix = cur_node;
                        cur_dist = cur_node->len() - 1;
                    }
                    // Case where suffix link doesnt exists yet
                    else{
                        need_suffix = mid;
                        cur_node = cur_node->next(s[g]);
                        cur_dist = j - g - 1;
                    }
                }
                i += 1;
            }
        }
    }

    ~suffix_tree(){
        delete root;
    }

    char get_char(node *cur, int ind){
        return s[cur->left + ind];
    }

    //Optional
    bool verify_substring(string sub){
        node *cur_node = root;
        int cur_dist = -1;

        for(char c : sub){
            if(cur_dist < cur_node->len() - 1){
                if(get_char(cur_node, cur_dist + 1) != c)
                    return false;
                cur_dist++;
            }
            else{
                if(cur_node->next(c) == NULL)
                    return false;
                cur_node = cur_node->next(c);
                cur_dist = 0;
            }
        }

        return true;
    }
    
    //Onlu for debbuging
    void print(node* cur_node = NULL){
		if(cur_node == NULL)
			cur_node = root;
		printf("node %d %d [", cur_node->left, cur_node->right);
		for(int i = cur_node->left; i <= cur_node->right; i++)
			printf("%c", s[i]);
		printf("] entra\n");

        for(auto el : cur_node->next_node){
            print(el.second);
        }
        
        printf("node %d %d [", cur_node->left, cur_node->right);
		for(int i = cur_node->left; i <= cur_node->right; i++)
			printf("%c", s[i]);
		printf("] sai\n");
	}
};
