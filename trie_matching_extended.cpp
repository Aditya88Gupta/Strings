#include <string>
#include <iostream>
#include <vector>

using std::pair;
using std::vector;
using std::string;

typedef pair<bool, pair<char, int> > edges;
typedef vector< vector<edges> > trie;
int count=1;
trie t;

int letterToIndex (char letter){
	switch (letter){
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default : return -1;
	}
}

trie build_trie(long long tmp, vector<string> & patterns) {
  trie t(tmp+1,vector<edges>(4,std::make_pair(false, std::make_pair('-',-1))));
  for(int i=0;i<patterns.size();i++){
    int curNode=0;
    string Str=patterns[i];
    int index(0);
    while(index!=Str.length()){
		int k = letterToIndex(Str[index]);
		if(index==Str.length()-1)
		  t[curNode][k].first = true;
		if(t[curNode][k].second.first == Str[index]){
			curNode=t[curNode][k].second.second;
            index++;
        } else{
			t[curNode][k].second= std::make_pair(Str[index],count);
            curNode=count;
            index++;
            count++;
		}
	}
  }
  return t;
}

bool prefixTrie_Matching(int s, string text){
	int curNode = 0;
	int index = s;
	while(index<=text.length()){ 
		int k = letterToIndex(text[index]);
		if(t[curNode][k].second.first == text[index]){
			if(t[curNode][k].first == true)
			  return true;
			curNode=t[curNode][k].second.second;
			index++;
		}else
		  return false;  
	}
	return false;
} 

vector<int> Trie_Matching(string text, long long tmp, vector<string>& patterns){
	
	t = build_trie(tmp,patterns);
	int i=0;
	vector <int> result;
	while(i!=text.length()){
		if(prefixTrie_Matching(i,text))
		  result.push_back(i);
		i++;  
	}
	return result;
}

int main(){
	string text;
	std::cin >> text;

	int n;
	std::cin >> n;

	long long tmp;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++){
		std::cin >> patterns[i];
		tmp+=patterns[i].length();
	}

	vector <int> ans;
	ans = Trie_Matching (text, tmp, patterns);

	for (int i = 0; i < (int) ans.size (); i++){
		std::cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			std::cout << " ";
		}
		else
		{
			std::cout << "\n";
		}
	}

	return 0;
}
