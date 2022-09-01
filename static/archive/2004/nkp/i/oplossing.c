#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define maxN 200
#define maxL 60
#define maxI 65535
#define maxS 10000

const int undef = -1;

/* exitcodes for statement function: */
const int endprog = 1;
const int gotoline = 2;

int run,nruns;

int nstatements;
int n;
char code[maxN+10][maxL+10];
int var[30];
int line;

void error(char *str)
{
  printf("Error in testcase %d, line %d: %s!\n",run+1,line+1,str);
  exit(1);
}

void read()
{
  int i;
  
  scanf("%d\n",&n);
  if ( n<1 || n>maxN ) error("read: nlines");
  
  for(i=0; i<n; i++) {
    fgets(code[i],maxL+5,stdin);
    if ( code[i][strlen(code[i])-1]=='\n' ) code[i][strlen(code[i])-1] = 0;
    if ( strlen(code[i])>maxL ) error("read: line length");
  }
  if ( strcmp(code[n-1],"END")!=0 ) error("read: last statement no END");
}

int integer(char *str)
{
  int i;
  if ( !isdigit(str[0]) ) error("integer: no digit");
  for(i=0; isdigit(str[i]); i++);
  if ( str[i]!=' ' && str[i]!=0 ) error("integer: no integer");
  if ( sscanf(str,"%d",&i)!=1 ) error("integer: read error");
  if ( i<0 || i>maxI ) error("integer: out of bounds");
  return i;
}

int variabele(char *str)
{
  int v;
  v = str[0]-'a';
  if ( str[1]!=' ' && str[1]!=0 ) error("variabele: multiple characters");
  if ( var[v]==undef ) error("variabele: undefined");
  return var[v];
}

int waarde(char *str)
{
  if ( islower(str[0]) )
    return variabele(str);
  else
    return integer(str);
}

int expressie(char *str)
{
  long long w1, w2, res;
  char op;
  int i;

  w1 = waarde(&str[0]);
  for(i=0; str[i]!=' ' && str[i]!=0; i++);
  if ( str[i]==0 ) return w1;
  op = str[++i];
  if ( str[++i]!=' ' ) error("expressie: space expected");
  w2 = waarde(&str[++i]);
  for(; str[i]!=' ' && str[i]!=0; i++);
  if ( str[i]!=0 ) error("expressie: newline expected");

  switch ( op ) {
  case '+': res = w1 + w2; break;
  case '-': res = w1 - w2; break;
  case '*': res = w1 * w2; break;
  case '/':
    if ( w2==0 ) error("div zero");
    res = w1 / w2;
    break;
  default: error("no operator");
  }
  if ( res<0 || res>maxI ) error("expressie: out of bounds");
  return res;
}

int test(char *str, int *size)
{
  int w1, w2;
  char cmp;
  int i;
  
  w1 = waarde(&str[0]);
  for(i=0; str[i]!=' ' && str[i]!=0; i++);
  if ( str[i]!=' ' ) error("test: space expected");
  cmp = str[++i];
  if ( str[++i]!=' ' ) error("test: space expected");
  w2 = waarde(&str[++i]);
  for(; str[i]!=' '&& str[i]!=0; i++);
  if ( str[i]!=' ' ) error("test: space expected");
  *size = i;
  
  switch ( cmp ) {
  case '<': return w1 <  w2;
  case '=': return w1 == w2;
  case '>': return w1 >  w2;
  default: error("no comparator");
  }
  return 0;
}

int statement(char *str)
{
  int v,w,t,pos;

  //printf("line %d: %s\n",line+1,str);
  
  nstatements++;
  if ( nstatements>maxS ) error("statement: max statements");
  
  if ( islower(str[0]) ) {
    v = str[0]-'a';
    if ( strncmp(&str[1]," = ",3)!=0 ) error("statement: =");
    w = expressie(&str[4]);
    var[v] = w;
    return 0;
  }
       
  switch ( str[0] ) {
  case 'I':
    if ( strncmp(str,"IF ",3)!=0 ) error("statement: IF");
    t = test(&str[3],&pos);
    pos += 3;
    if ( strncmp(&str[pos]," THEN ",6)!=0 ) error("statement: THEN");
    if ( t ) return statement(&str[pos+6]);
    return 0;

  case 'E':
    if ( strcmp(str,"END")!=0 ) error("statement: END");
    return endprog;
    
  case 'G':
    if ( strncmp(str,"GOTO ",5)!=0 ) error("statement: GOTO");
    w = integer(&str[5]);
    if ( w<1 || w>n ) error("statement: GOTO line");
    line = w - 1;
    return gotoline;
    
  case 'P':
    if ( strncmp(str,"PRINT ",6)!=0 ) error("statement: PRINT");
    w = waarde(&str[6]);
    printf("%d\n",w);
    return 0;

  default:
    error("no statement");
  }
  return 0;
}

void solve()
{
  int i;
  
  line = 0;
  nstatements = 0;
  for(i=0; i<26; i++) var[i] = undef;

  while ( 1 ) {
    if ( line<0 || line>=n ) error("line bounds");
    i = statement(code[line]);
    if ( i==endprog ) break;
    if ( i!=gotoline ) line++;
  }
  
}

int main()
{
  scanf("%d\n",&nruns);

  for(run=0; run<nruns; run++) {
    read();
    solve();
  }
  
  return 0;
}
