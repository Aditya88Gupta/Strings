#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <set>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;
using std::set;

// For unique values 
set<int> occurrences;


int letterToIndex (char letter){
	switch (letter){
		case '$': return 0; break;
		case 'A': return 1; break;
		case 'C': return 2; break;
		case 'G': return 3; break;
    case 'T': return 4; break;
		default : return -1;
	}
}

// Initial Phase, sorting suffix of length 1

vector<int> SortChar(const string& text){
  vector<int> Count(5,0);
  vector<int> Order(text.length(),0);
  for(size_t i=0;i<text.length();i++){
    Count[letterToIndex(text[i])]+=1;
  }
  for(size_t i=1;i<5;i++){
    Count[i]+= Count[i-1];
  }
  //std::cout<<"\n";
  int i=text.length()-1;
  while(i>=0){
    //cout<<i<<" ";
    Count[letterToIndex(text[i])]--;
    Order[Count[letterToIndex(text[i])]] = i;
    i--;
  }
  return Order;
}

// Initial Phase, computing classes
// These classes play an important role while sortDoubled

vector<int> ComputeCharClass(const string& text,vector<int> order){
  vector<int> eqClass(text.length(),0);
  for(size_t i=1;i<text.length();i++){
    if(text[order[i]]==text[order[i-1]])
      eqClass[order[i]] = eqClass[order[i-1]];
    else
      eqClass[order[i]] = eqClass[order[i-1]]+1;
  }
  return eqClass;
}


vector<int> SortDoubled(int L, vector<int> eqClass,vector<int> result,const string& text){
  // Count of eqClasses, max number of eqClasses = text.length()
  vector<int> Count(text.length(),0);
  vector<int> Order(text.length(),0);
  for(size_t i=0;i<text.length();i++){
    Count[eqClass[i]]+=1;
  }
  for(size_t i=1;i<text.length();i++){
    Count[i]+= Count[i-1];
  }
  int i=text.length()-1;
  while(i>=0){
    // Going back by L in cyclic manner
    int start = (result[i]-L+text.length())%text.length();
    Count[eqClass[start]]--;
    Order[Count[eqClass[start]]] = start;
    i--;
  }
  return Order;
}

vector<int> UpdateClass(int L, vector<int> eqClass, vector<int> result){
  int n = result.size();
  vector<int> newClass(n,0);
  for(size_t i=1;i<n;i++){
    int cur = result[i];
    int prev = result[i-1];
    int midCur = (cur+L)%n;
    int midPrev = (prev+L)%n;
    if(eqClass[cur]!=eqClass[prev] || eqClass[midCur]!=eqClass[midPrev])
      newClass[cur] = newClass[prev]+1;
    else
      newClass[cur] = newClass[prev];
  }
  return newClass;
}

vector<int> BuildSuffixArray(const string& text) {
  vector<int> result;
  result = SortChar(text);
  vector<int> eqClass = ComputeCharClass(text,result);
  long L=1;
  while(L<text.length()){
    result = SortDoubled(L,eqClass,result,text);
    eqClass = UpdateClass(L,eqClass,result);
    L = L*2;
  //   for (int i = 0; i < result.size(); ++i) {
  //   cout << result[i] << ' ';
  // }
  // cout << endl;
  }

  return result;
}

// Modified Binary Searching

void FindOccurrences(char *text, char *pattern, int pSize, int tSize, const vector<int> suffix_array) {

  int start(-1),end(-1);
  int minIndex(0),maxIndex(tSize);
  
  // First Occurence 
  while(minIndex<maxIndex){
    int midIndex = (minIndex+maxIndex)/2;
    int tmp = strncmp(pattern,text+suffix_array[midIndex],pSize);
    if(tmp>0)
      minIndex=midIndex+1;
    else 
      maxIndex=midIndex; 
  }

  start=minIndex;

  minIndex=0;
  maxIndex=tSize;
  // Last Occurence
  while(minIndex<maxIndex){
    int midIndex = (minIndex+maxIndex)/2;
    int tmp = strncmp(pattern,text+suffix_array[midIndex],pSize);
    if(tmp<0)
      maxIndex=midIndex;
    else 
      minIndex=midIndex+1;  
  }

  end=maxIndex;

  if(start<=end){
    for(int i=start;i<end;i++){
      occurrences.insert(suffix_array[i]);
    }
  }
}

int main() {

  int m;
  string text, pattern;
  cin >> text >> m;
  text += '$';
  vector<int> suffix_array = BuildSuffixArray(text);

  for (int i = 0; i < m; i++) {
    cin >> pattern;
    FindOccurrences(&text[0],&pattern[0],pattern.length(),text.length(),suffix_array);
  }

  for (auto x: occurrences)
    cout << x << ' ';

  return 0;
}
