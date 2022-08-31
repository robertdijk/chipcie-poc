/*
 *  NKP 2004: Back to Basic
 *  door Jan Kuipers
 */

using namespace std;

#include <ctype.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

int N,now;
vector<string> line;
map<string,int> variable;

void read () {
  cin >> N; cin.ignore();
  line=vector<string>(N);
  
  for (int i=0; i<N; i++) {
    char tmp[1000];
    cin.getline (tmp, 1000);
    line[i]=string(tmp);
  }
}

int value (string s) {
  if (isdigit(s[0])) return atoi(s.c_str());
  return variable[s];
}

void solve () {

  now=0;
  
  while (1) {
    string tmp;
    vector<string> token;
    istringstream iss(line[now]);
    while (iss >> tmp) token.push_back(tmp);

  again:
    if (token[0]=="END") break;
    
    if (token[0]=="GOTO") now = value(token[1])-1;
    
    if (token[0]=="PRINT") {
      cout << value(token[1]) << endl;
      now++;
    }

    if (token[0]=="IF") {
      if ( (token[2]=="<" && value(token[1]) < value(token[3])) ||
	   (token[2]==">" && value(token[1]) > value(token[3])) ||
	   (token[2]=="=" && value(token[1]) == value(token[3]))) {
	token.erase(token.begin(), token.begin()+5);
	goto again;
      }      
      now++;
    }

    if (islower(token[0][0])) {
      if (token.size()==3)
	variable[token[0]] = value(token[2]);
      else {
	if (token[3]=="+") variable[token[0]] = value(token[2]) + value(token[4]);
	if (token[3]=="-") variable[token[0]] = value(token[2]) - value(token[4]);
	if (token[3]=="*") variable[token[0]] = value(token[2]) * value(token[4]);
	if (token[3]=="/") variable[token[0]] = value(token[2]) / value(token[4]);
      }
      now++;
    }    
  }
}

int main () {

  int run,runs;
  cin >> runs;
  for (run=0; run<runs; run++) {
    read ();
    solve ();
  }
  return 0;
}
