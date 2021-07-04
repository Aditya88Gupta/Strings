#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;


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

string InverseBWT(const string& bwt) {
  string text = "";
  int n = bwt.length();
  vector<vector<int> > Count(5,vector<int>(n+1,0));
  for(size_t i=1;i<=n;i++){
    for(size_t j=0;j<5;j++){
      Count[j][i]=Count[j][i-1];
    }
    Count[letterToIndex(bwt[i-1])][i]+=1;
  }
  // for(int i=0;i<5;i++){
  //   for(int j=0;j<=n;j++){
  //     std::cout<<Count[i][j]<<" ";
  //   }
  //   std::cout<<"\n";
  // }
  vector<int> firstOccurence(5,0);
  int prevStart=0;
  int prevCount=1;
  for(size_t i=1;i<5;i++){
    if(Count[i][n]==0){
      firstOccurence[i]=-1;
      continue;
    }
    firstOccurence[i]=prevStart+prevCount;
    prevStart=firstOccurence[i];
    prevCount=Count[i][n];
  }
  int k=0;
  for(size_t i=0;i<n-1;i++){
    text=bwt[k]+text;
    k = firstOccurence[letterToIndex(bwt[k])] + Count[letterToIndex(bwt[k])][k];
  }
  text+= '$';
  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
