#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::istringstream;
using std::map;
using std::string;
using std::vector;

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt, map<char, int>& firstOccurence, map<char, vector<int> >& Count) {
  int n = bwt.length();
  for(size_t i=0;i<n;i++){
    if(Count.find(bwt[i]) == Count.end()){
      Count.insert(std::make_pair(bwt[i],vector<int>(n+1,0)));
    }
  }
  for(size_t i=1;i<=n;i++){
    for(map<char,vector<int>>::iterator itr = Count.begin();itr!=Count.end();itr++){
      itr->second[i] = itr->second[i-1];
    }
    map<char, vector<int>>::iterator tmp = Count.find(bwt[i-1]);
    tmp->second[i] += 1;
  }
  // for(map<char,vector<int>>::iterator itr = Count.begin();itr!=Count.end();itr++){
  //   std::cout<<itr->first<<" ";
  //   vector<int> tmp = itr->second;
  //   for(int j=0;j<=n;j++){
  //     std::cout<<tmp[j]<<" ";
  //   }
  //   std::cout<<"\n";
  // }
  firstOccurence.insert(std::make_pair('$',0));
  int prevCount=1;
  int prevStart=0;
  for(map<char,vector<int>>::iterator itr = ++Count.begin();itr!=Count.end();itr++){
    int tmp = prevStart+prevCount;
    firstOccurence.insert(std::make_pair(itr->first,tmp));
    prevStart=tmp;
    prevCount=itr->second[n];
  }
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern, const string& bwt, const map<char, int>& firstOccurence, const map<char, vector<int> >& Count) {
  int n = pattern.length();
  int top(0),bottom(bwt.length()-1);
  while(top<=bottom){
    if(n==0){
      return bottom-top+1;
    }
    if(firstOccurence.find(pattern[n-1])!=firstOccurence.end()){
      top = firstOccurence.find(pattern[n-1])->second + Count.find(pattern[n-1])->second[top];
      bottom = firstOccurence.find(pattern[n-1])->second + Count.find(pattern[n-1])->second[bottom+1]-1;
      n--;
    }
    else
      return 0;
  }
  return 0;
}
     

int main() {
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;
  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, int> starts;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, vector<int> > occ_count_before;
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}
