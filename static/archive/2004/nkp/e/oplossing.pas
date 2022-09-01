program safari(input,output);

const
   maxn	  = 110;
   maxlen = 610;
   
var
   run, nruns		: integer;
   mint, maxt, n, w	: integer;
   tijd				: array[1..maxn,1..maxn] of integer;
   kans				: array[1..maxn,1..maxn] of single;
   len				: integer;
   res				: single;
   
procedure readinput;
var
   i, j, k, t, p : integer;
begin
   readln(mint,maxt);
   readln(n,w);
   
   for j := 1 to n do
	  for k := 1 to n do
	  begin
		 tijd[j][k] := maxlen;
		 kans[j][k] := 0;
	  end;

   for i := 1 to w do
   begin
	  readln(j,k,t,p);
	  tijd[j][k] := t;
	  kans[j][k] := p / 100;
   end;
   
end; { readinput }

procedure writeoutput;
var
   rounddiff : double;
begin
   if ( res<-0.5 ) then
	  writeln('onmogelijk')
   else
   begin
	  res := res * 100;
	  rounddiff := 100*res - trunc(100*res);
	  if ( abs(rounddiff-0.5)<0.05 ) then writeln('rounding imprecision: ',res:1:5);
	  writeln(res:1:2);
   end;
end; { writeoutput }

procedure solve;
var
   i, j, k : integer;
   pneg	   : array[1..maxn,0..maxlen] of single;
   p	   : single;
begin
   for i := 1 to n do
	  for j := 0 to maxt do
		 pneg[i][j] := 2;

   pneg[1][0] := 1;

   for i := 0 to maxt-1 do
	  for j := 1 to n do
		 for k := 1 to n do
			if ( (i+tijd[j,k]<=maxt) and (pneg[j,i]<1.5) ) then
			begin
			   p := pneg[j,i]*(1-kans[j,k]);
			   if ( p<pneg[k,i+tijd[j,k]] ) then
			   begin
				  pneg[k,i+tijd[j,k]] := p;
{				  writeln('update ',j,' -> ',k,': ',p:1:5); }
			   end;
			end;

   res := 2;
   len := maxlen;
   
   for i := mint to maxt do
	  if ( pneg[1,i]<res ) then
	  begin
		 res := pneg[1,i];
		 len := i;
	  end;
		
   res := 1-res;
   
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
