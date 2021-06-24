#include <string>
#include <iostream>
#include <vector>

using std::pair;
using std::vector;
using std::string;

typedef pair<char, int> edges;
typedef vector<vector<edges> > trie;
int count=1;

trie build_trie(long long tmp, vector<string> & patterns) {
  trie t(tmp+1,vector<edges>());
  for(int i=0;i<patterns.size();i++){
    int curNode=0;
    string Str=patterns[i];
    int index(0),k(0);
    while(index!=Str.length()){
      if(t[curNode].size()!=0 && k<t[curNode].size() && t[curNode][k].first == Str[index]){
        curNode=t[curNode][k].second;
        index++;
        k=0;
      } else if(k==t[curNode].size()){
        t[curNode].push_back(std::make_pair(Str[index],count));
        curNode=count;
        k=0;
        index++;
        count++;
      }else
        k++;
    }
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  long long tmp(0);
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    tmp+= s.length();
    patterns.push_back(s);
  }

  trie t = build_trie(tmp,patterns);
  for (size_t i = 0; i < count; ++i) {
    for (size_t j = 0; j< t[i].size(); j++) {
      std::cout << i << "->" << t[i][j].second << ":" << t[i][j].first << "\n";
    }
  }

  return 0;
}