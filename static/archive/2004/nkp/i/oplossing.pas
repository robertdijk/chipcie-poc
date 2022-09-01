program backtobasic(input, ouput);

const
   maxn	  = 200;
   maxlen = 60;
   
var
   run,nruns : integer;
   n		 : integer;
   lines	 : array[1..maxn] of string[maxlen];
   vars		 : array['a'..'z'] of longint;
   line, pos : integer;
   
procedure error;
begin
   writeln('Error in testcase ',run);
   halt(1);
end; { error }

procedure readinput;
var
   i : integer;
begin
   readln(n);
   for i := 1 to n do readln(lines[i]);
end; { readinput }

function readword: string;
begin
   readword := '';
   while ( (pos<=length(lines[line])) and (lines[line][pos]= ' ') ) do inc(pos);
   while ( (pos<=length(lines[line])) and (lines[line][pos]<>' ') ) do
   begin
	  readword := readword + lines[line][pos];
	  inc(pos);
   end;
end; { readword }

function value: longint;
var
   str	: string[10];
   V	: longint;
   code	: word;
begin 
   str := readword();
   case ( str[1] ) of
	 'a'..'z': value := vars[str[1]];
   else
   begin
	  val(str,V,code);
	  value	:= V;
   end;
   end; { case }
end; { value }

function expr: longint;
var
   op		   : string[10];
   left, right : longint;
begin
   left := value();
   op := readword();
   if ( op<>'' ) then
   begin
	  right := value();
	  case ( op[1] ) of
		'+'	: expr := left + right;
		'-'	: expr := left - right;
		'*'	: expr := left * right;
		'/'	: expr := left div right;
	  end;
   end else
	  expr := left;
end; { expr }

function test: boolean;
var
   cmp		   : string[10];
   left, right : longint;
begin 
   left := value();
   cmp := readword();
   right := value();
   case ( cmp[1] ) of
	 '<' : test := (left < right);
	 '=' : test := (left = right);
	 '>' : test := (left > right);
   end;
end; { test }

procedure simulate;
var
   cmd, arg	: string[10];
   V		: longint;
   code		: word;
begin
   line := 1;
   pos := 1;
   repeat
	  cmd := readword();
	  case ( cmd[1] ) of
		'a'..'z': begin
		   readword();
		   vars[cmd[1]] := expr();
		   inc(line);
		   pos := 1;
		end;	 
		'E'		 : exit;
		'G'		 : begin
		   arg := readword();
		   val(arg,V,code);
		   line := V;
		   pos := 1;
		end;
		'I'		 : begin
		   if ( test() ) then
			  readword()
		   else
		   begin
			  inc(line);
			  pos := 1;
		   end;
		end;
		'P'		 : begin
		   V := value();
		   writeln(V);
		   inc(line);
		   pos := 1;
		end;
	  end; { case }
   until false;
end; { solve }

begin
   readln(nruns);

   for run := 1 to nruns do
   begin
	  readinput();
	  simulate();
   end;
   
end.
