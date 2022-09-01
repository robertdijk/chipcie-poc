/******************************************************************************
* Sample solution for the Word Encoding problem in NWERC'04
* Author: Andreas Björklund
* Solution: Dynamic programming counting the number of strings of a given
* length starting with a given pair of symbols.
******************************************************************************/
#include <stdio.h>
#include <string.h>

#define MAXN (1000)
int cnt;
char forb[27][27][27];
unsigned int Mx[21][27][27],CMx[4000][4];

void findString(int id,char *ans)
{
  int i=0,l,a,b,j,k,stop;
  unsigned int sum;
  while (id>CMx[i][0]) i++;  
  if (i) id-=CMx[i-1][0];
  a=CMx[i][2];
  b=CMx[i][3];
  for (l=CMx[i][1];l>0;l--)
  {
    sum=stop=0;
    for (j=0;j<27 && !stop;j++)
      if (!forb[a][b][j])
      {
        sum+=Mx[l-1][b][j];
        stop=sum>=id;
        if (stop)
        {
         id-=sum-Mx[l-1][b][j]; 
        }
      }
    ans[CMx[i][1]-l]=a+'a'-1;
    a=b;
    b=j-1;
  }
  ans[CMx[i][1]]=0;
}

int findId(char *query,unsigned int low,unsigned int high)
{
  char cmp[30];
  unsigned int middle=(low+high)/2; 
  if (low>high) return -1;
  findString(middle,cmp);
  if (strcmp(query,cmp)==0) return middle;
  if (strlen(query)<strlen(cmp) || (strlen(query)==strlen(cmp) && strcmp(query,cmp)<0)) return findId(query,low,middle-1);
  return findId(query,middle+1,high);
}

int main(void)
{
  int i,j,k,l,t,n,m,done;
  unsigned int csum;
  char tmp[30];
  scanf("%d",&t);
  while(t--)
  {
    scanf("%d %d",&n,&m);
    gets(tmp);
   
    // Clear forbidden table
    for (i=0;i<27;i++)
      for (j=0;j<27;j++)
        for (k=0;k<27;k++)
          forb[i][j][k]=i==0; // Strings may not start with termination symbol (here 0)
 
    // Build forbidden words
    for (i=0;i<n;i++)
    {
      gets(tmp);
      if (strlen(tmp)==3)
        forb[tmp[0]-'a'+1][tmp[1]-'a'+1][tmp[2]-'a'+1]=1;
      else if (strlen(tmp)==2)
        for (j=0;j<27;j++)
          forb[tmp[0]-'a'+1][tmp[1]-'a'+1][j]=1;
      else
        for (j=0;j<27;j++)
          for (k=0;k<27;k++)
            forb[tmp[0]-'a'+1][j][k]=1;       
    }
    
    // Build count table
    csum=cnt=done=0;
    for (i=0;i<27;i++)
        for (j=0;j<27;j++)
          Mx[0][i][j]=0;
    Mx[0][0][0]=1; // There is one word of length 0.
    for (l=1;l<=20 && !done;l++)
      for (i=0;i<27 && !done;i++)
        for (j=0;j<27 && !done;j++)
        {
          int sum=0;  
          for (k=0;k<27;k++)
            if (!forb[i][j][k])
              sum+=Mx[l-1][j][k];
          Mx[l][i][j]=sum;  
          csum+=sum;
          if (sum)
          {
            CMx[cnt][0]=csum;
            CMx[cnt][1]=l;
            CMx[cnt][2]=i;
            CMx[cnt++][3]=j;
          }
          done=(csum>2000000000);
        }
    
    for (i=0;i<m;i++)
    {
      char ans[22];
      int val;
      gets(tmp);
      if (sscanf(tmp,"%d",&val))
      {
        findString(val,ans);
        printf("%s\n",ans);  
      }
      else
      {
        val=findId(tmp,1,csum);  
        printf("%d\n",val);
      }  
    }
  }
  return 0;
}
