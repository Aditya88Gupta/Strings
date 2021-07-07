#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.

vector<int> prefixFunction(string S){
  vector<int> prefix(S.length(),0);
  int border=0;
  for(size_t i=1;i<S.length();i++){
    while(border>0 && S[i]!=S[border]){
      border = prefix[border-1];
    }
    if(S[border]==S[i])
      border+=1;
    else
      border=0;
    prefix[i]=border;  
  }
  return prefix;
}

vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  string S = pattern+"-"+text;
  vector<int> prefix = prefixFunction(S);
  int p_len = pattern.length();
  for(size_t i=p_len+1;i<S.length();i++){
    if(prefix[i]==p_len)
       result.push_back(i-2*p_len);
  }
  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
