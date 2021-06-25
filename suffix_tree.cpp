#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;

typedef pair<int, pair<int, int> > edges;
typedef vector<vector<edges> > Tree;
typedef vector<int> start;
int count=1;

int letterToIndex (char letter){
	switch (letter){
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
    case '$': return 4; break;
		default : return -1;
	}
}

vector<string> ComputeSuffixTreeEdges(const string& text) {
  vector<string> result;
  Tree suffixTree(2*text.length(),vector<edges>(5,std::make_pair(-1,std::make_pair(-1,-1))));
  //start tmp(2*text.length(),-1);
  for(size_t i=0;i<text.length();i++){
    int curNode = 0;                 // Root
    int k  = letterToIndex(text[i]);
    int x = i;
    while(true){
      if(suffixTree[curNode][k].second.first == -1){
        suffixTree[curNode][k].first = count++;
        suffixTree[curNode][k].second.first = x;
        suffixTree[curNode][k].second.second = text.length()-x;
        //tmp[count] = i;
        break;
      }else{
        int y=0;
        while(x<text.length() && y<suffixTree[curNode][k].second.second){
          if(text[x]==text[suffixTree[curNode][k].second.first+y]){
            x++;
            y++;
            continue;
          }
          break;
        }
        int newLen = suffixTree[curNode][k].second.second - y;
        int s = suffixTree[curNode][k].second.first;
        if(text[suffixTree[curNode][k].second.first+suffixTree[curNode][k].second.second-1]=='$'){
          suffixTree[curNode][k].second.second = y;
          curNode = suffixTree[curNode][k].first;
          suffixTree[curNode][letterToIndex(text[s+y])].first = count++;
          suffixTree[curNode][letterToIndex(text[s+y])].second.first = s+y;
          suffixTree[curNode][letterToIndex(text[s+y])].second.second = newLen;
          suffixTree[curNode][letterToIndex(text[x])].first = count++;
          suffixTree[curNode][letterToIndex(text[x])].second.first = x;
          suffixTree[curNode][letterToIndex(text[x])].second.second = text.length()-x;
          break;
        }else if(newLen!=0){
           suffixTree[curNode][k].second.second = y;
           curNode = suffixTree[curNode][k].first;
           k = letterToIndex(text[s+y]);
           int new_Node = count++;
           for(int index=0;index<5;index++){
             suffixTree[new_Node][index].first = suffixTree[curNode][index].first;
             suffixTree[new_Node][index].second.first = suffixTree[curNode][index].second.first;
             suffixTree[new_Node][index].second.second = suffixTree[curNode][index].second.second;
             suffixTree[curNode][index].first = -1;
             suffixTree[curNode][index].second.first = -1;
             suffixTree[curNode][index].second.second = -1;
           }
           suffixTree[curNode][k].first = new_Node;
           suffixTree[curNode][k].second.first = s+y;
           suffixTree[curNode][k].second.second = newLen;
           suffixTree[curNode][letterToIndex(text[x])].first = count++;
           suffixTree[curNode][letterToIndex(text[x])].second.first = x;
           suffixTree[curNode][letterToIndex(text[x])].second.second = text.length()-x;
           break;
        }else{
          curNode = suffixTree[curNode][k].first;
          k = letterToIndex(text[x]);
        }
      }
    }
  }

  for(int i=0;i<count;i++){
    for(int j=0;j<5;j++){
      int s = suffixTree[i][j].second.first;
      int len = suffixTree[i][j].second.second;
      if(s==-1)
        continue;
      string Str="";
      for(int k=0;k<len;k++){
        Str+=text[s+k];
      }
      result.push_back(Str);
    }
  }
  return result;
}

int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
