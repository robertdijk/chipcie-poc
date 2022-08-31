program bustijden(input, ouput);

const
   maxn	 = 100;
   maxb	 = 100;
   infty = 9999;
   
var
   run,nruns : integer;
   n		 : integer;
   duur,nbus : array[1..maxn] of integer;
   tijd,afw	 : array[1..maxn,1..maxb] of integer;
   trav		 : array[0..maxn,1..2] of integer;

function min(a,b : integer): integer;
begin
   if ( a<b ) then min := a else min := b;
end; { min }

function max(a,b : integer): integer;
begin
   if ( a>b ) then max := a else max := b;
end; { max }

procedure error;
begin
   writeln('Error in testcase ',run);
   halt(1);
end; { error }

function readtime: integer;
var
   h1,h2,colon,m1,m2 : char;
   h,m				 : integer;
begin
   read(h1,h2,colon,m1,m2);
   h := 10*(ord(h1)-ord('0')) + (ord(h2)-ord('0'));
   m := 10*(ord(m1)-ord('0')) + (ord(m2)-ord('0'));
   readtime := 60*h + m;
end; { readtime }

procedure writetime(t : integer);
var
   h,m : integer;
begin
   h := t div 60;
   m := t mod 60;
   write(chr(ord('0')+(h div 10)),chr(ord('0')+(h mod 10)),':');
   write(chr(ord('0')+(m div 10)),chr(ord('0')+(m mod 10)));
end; { writetime }

procedure readinput;
var
   i,j	: integer;
   c	: char;
   str	: string[10];
   V	: longint;
   code	: word;
begin
   readln(n);
   for i := 1 to n do
   begin
	  readln(nbus[i],duur[i]);
	  for j := 1 to nbus[i] do
	  begin
		 tijd[i,j] := readtime();
		 readln(str);
		 delete(str,1,2);
		 delete(str,length(str),1);
		 val(str,V,code);
		 afw[i,j] := V;
	  end;
   end;
end; { readinput }

procedure writeoutput;
begin
   writetime(trav[n,1]);
   write(' ');
   writetime(trav[n,2]);
   writeln();
end; { writeoutput }

procedure solve;
var
   i,j : integer;
begin
   trav[0,1] := 60*9;
   trav[0,2] := 60*9;
   for i := 1 to n do
   begin
	  trav[i,1] := infty;
	  trav[i,2] := infty;
	  for j := 1 to nbus[i] do
	  begin
		 if ( tijd[i,j]+afw[i,j]>=trav[i-1,1] ) then
			trav[i,1] := min(trav[i,1],max(trav[i-1,1],tijd[i,j]-afw[i,j])+duur[i]);
							 
		 if ( tijd[i,j]-afw[i,j]>=trav[i-1,2] ) then
			trav[i,2] := min(trav[i,2],tijd[i,j]+afw[i,j]+duur[i]);
	  end;
   end;
   
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
