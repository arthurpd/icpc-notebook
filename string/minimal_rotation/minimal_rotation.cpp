#include<bits/stdc++.h>
using namespace std;

/*
	Minimal Rotation:
		A rotation of a string s[0...n-1] is s[i...n-1] 
        concatenated with s[0...i-1] for some i, 0<i<n.
        This finds the lexicographical minimal rotation
        in O(n).

	Usage:
		Pass the string as argument. 
        Returns index of lexicographical minimal rotation.
        You can use vector<T>, just change the first line
        to concatenate the vector with itself. 
*/

int minimal_rotation(string s){
    s = s + s;
    vector<int> f(s.size(), -1);
    int k = 0;

    for(int j = 1; j < (int)s.size(); j++){
        int i = f[j - k - 1];
        while(i != -1 && s[j] != s[i + k + 1]){
            if(s[j] < s[i + k + 1])
                k = j - i - 1;
            i = f[i];
        }

        if(s[j] != s[i + k + 1]){
            if(s[j] < s[i + k + 1])
                k = j;
            f[j - k] = -1;
        }
        else
            f[j - k] = i+1;
    }

    return k;
}
