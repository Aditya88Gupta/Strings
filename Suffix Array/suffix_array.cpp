#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
  int n = text.length();
  vector<int> result(n,0);
  vector<pair<string,int> > Mat;
  for(size_t i=0;i<n;i++){
    int k = i;
    string tmp="";
    for(size_t j=0;j<n;j++){
      tmp += text[k++];
      if(k == n)
        k=0;
    }
    Mat.push_back(std::make_pair(tmp,i));
  }
  sort(Mat.begin(),Mat.end());
  for(size_t i=0;i<n;i++){
    result[i] = Mat[i].second;
  }
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
