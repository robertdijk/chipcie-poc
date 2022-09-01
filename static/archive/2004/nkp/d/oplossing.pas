program drugsbende(input,output);

const
   maxn			  = 100000;
   maxc	: longint = 1000000000;
   
var
   run, nruns : integer;
   n,k		  : longint;
   best		  : longint;
   cel		  : array[1..maxn] of longint;
   
procedure error;
begin
   writeln('Error in testcase ',run);
   halt(1);
end; { error }

procedure readinput;
var
   i : longint;
begin
   readln(n,k);
   if ( (k>n) or (n>maxn) ) then error();
   for i := 1 to n do
   begin
	  read(cel[i]);
	  if ( (i>1) and (cel[i]<=cel[i-1]) ) then error();
	  if ( (cel[i]<0) or (cel[i]>maxc) ) then error();
   end;
   readln();
end; { readinput }

procedure writeoutput;
begin
   writeln(best);
end; { writeoutput }

procedure solve;
var
   mindist, maxdist, dist : longint;
   i,j,last,fits		  : longint;
begin
   mindist := 1;
   maxdist := maxc;
   while ( mindist<maxdist ) do
   begin
	  dist := (mindist+maxdist+1) div 2;
	  last := 1;
	  fits := 1;
	  for i := 2 to k do
	  begin
		 j := last+1;
		 while ( (j<=n) and (cel[j]-cel[last]<dist) ) do inc(j);
		 if ( j>n ) then
		 begin
			fits := 0;
			break;
		 end;
		 last := j;
	  end;
	  if ( fits = 1 ) then
		 mindist := dist
	  else
		 maxdist := dist-1;
   end;
   best := mindist;
end; { solve }		

begin
   readln(nruns);
   
   for run := 1 to nruns do
   begin
	  readinput();
	  solve();
	  writeoutput();
   end;
end.
