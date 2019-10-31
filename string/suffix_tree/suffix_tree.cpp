/*TODO: Comment code
*/
#include <bits/stdc++.h>

using namespace std;

struct node{
    int left, right;
    node *parent, *suffix;
    map<char, node*> next_node;

    node(int _left, int _right, node *_parent):
    left(_left), right(_right), parent(_parent){}

    ~node(){
        for(auto child : next_node)
            delete child.second;   
    }

    int len(){
        return right - left + 1;
    }

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

        node *cur_node = root, *need_suffix = NULL;
        int cur_dist = -1, i = 0;

        for(int j = 0; j < (int)s.size(); j++){
			//~ if(j == 11)
            char c = s[j];
            while(i <= j){
                //Caso 1:
                if(cur_dist == cur_node->len() - 1 and cur_node->next(c) != NULL){
                    cur_node = cur_node->next(c);
                    cur_dist = -1;
                }

                if(cur_dist < cur_node->len() - 1 and get_char(cur_node, cur_dist + 1) == c){
                    cur_dist += 1;
                    break;
                }
				
			//	printf("ok1\n");
			//	printf("ok1.5 %d\n", cur_dist == cur_node->len() - 1);
				
                //Caso 2:
                if(cur_dist == cur_node->len() - 1){
                    cur_node->next_node[c] = new node(j, s.size() - 1, cur_node);
                    if(cur_node != root){
                        cur_node = cur_node->suffix;
                        cur_dist = cur_node->len() - 1;
                    }
                }

                //Caso 3:
                else{
                    //Cria um novo node e divide a aresta
                    node *mid = new node(cur_node->left, cur_node->left + cur_dist, cur_node->parent);
                    cur_node->parent->next_node[get_char(mid, 0)] = mid;
                    mid->next_node[get_char(cur_node, cur_dist + 1)] = cur_node;
                    cur_node->parent = mid;
                    cur_node->left += cur_dist + 1;
                    mid->next_node[s[j]] = new node(j, s.size() - 1, mid);
                    //Preenche o suffix_link que estiver faltando
                    if(need_suffix != NULL)
                        need_suffix->suffix = mid;
                    //Tenta encontrar o suffix link para mid
                    cur_node = mid->parent;
                    int g;
                    if(cur_node != root){
                        cur_node = cur_node->suffix;
                        g = j - cur_dist;
                    }
                    else
                        g = i + 1;
                    //Inicialmente cur_node esta no node que vai de [i+1 ... g-1]
                    while(g < j and g + cur_node->next(s[g])->len() <= j){
                        cur_node= cur_node->next(s[g]);
                        g += cur_node->len();
                    }
                    //Caso em que encontramos o suffix link
                    if(g == j){
                        need_suffix = NULL;
                        mid->suffix = cur_node;
                        cur_dist = cur_node->len() - 1;
                    }
                    //Caso em que não encontramos
                    else{
                        need_suffix = mid;
                        cur_node = cur_node->next(s[g]);
                        cur_dist = j - g;
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

int main(){
    int t;
    scanf("%d", &t);

    while(t--){
		string s;
		cin >> s;
		
		suffix_tree st = suffix_tree(s);
		
		//st.print();
		
		int q;
		scanf("%d", &q);
		
		for(int i = 0; i < q; i++){
			string s;
			cin >> s;
			
			if(st.verify_substring(s))
				printf("y\n");
			else
				printf("n\n");
		}
        
    }

    return 0;
}
