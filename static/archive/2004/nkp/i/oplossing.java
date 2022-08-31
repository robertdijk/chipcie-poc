import java.util.StringTokenizer;
import java.io.*;

class Main {
	public static StringTokenizer tok;
	public static String line;
	public static BufferedReader in;

	public static void write(String s) {
		System.out.print(s);
	}

	public static int readInt() throws Exception {
  		tok();
	  	return nextInt();
 	}

 	public static void tok() throws Exception {
  		tok = new StringTokenizer(in.readLine());
	}

	public static int nextInt() throws Exception {
  		return Integer.parseInt((String)tok.nextToken());
	}

	public static void main(String[] args) throws Exception {
		in = new BufferedReader( new InputStreamReader(System.in) );
		int runs = readInt();
		for( int run=0; run<runs; run++ )
			doit();
	}
	
	static int[] vars;
	static String[] statements;
	static int linenum;
	static boolean finished;
	
	public static void doit() throws Exception
	{
		int ns = readInt();
		statements = new String[ ns + 1 ];
		for( int i=1; i<=ns; i++ )
			 statements[i] = in.readLine();
	
		vars = new int[26];
		
		// interpretation loop
		linenum = 1;
		finished = false;
		while( !finished )
			execute( statements[linenum] );	
	
	}
	
	
	public static int parseExpr() throws Exception
	{
		int a = parseWaarde();
		if( !tok.hasMoreTokens() ) return a;
		char op = ((String)tok.nextToken()).charAt(0);
		int b = parseWaarde();
		switch(op) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			return a / b;
		}
		return -1;
	}
	
	public static int parseWaarde() throws Exception
	{
		String s = (String)tok.nextToken();
		if( s.charAt(0) >= 'a' && s.charAt(0) <= 'z' )
			return vars[ s.charAt(0) - 'a' ];
		return Integer.parseInt(s);
	}
	
	public static boolean parseTest() throws Exception
	{
		int a = parseWaarde();
		char op = ((String)tok.nextToken()).charAt(0);
		int b = parseWaarde();
		switch(op) {
		case '>':
			return a > b;
		case '<':
			return a < b;
		case '=':
			return a == b;
		}
		return false;
	}
		public static void execute( String statement ) throws Exception
	{
		//write( statement + "\n" );
		tok = new StringTokenizer( statement );
		String type = (String)tok.nextToken();
		if( type.equals( "PRINT" ) ) {
			write( parseWaarde() + "\n" );
			linenum++;	return;
		}
		
		if( type.equals( "GOTO" ) ) {
			linenum = nextInt();
			return;
		}
		
		if( type.equals( "END" ) ) {
			finished = true;
			linenum++; return;
		}
		
		if( type.equals( "IF" ) ) {
			boolean condition = parseTest();
			if( !condition ) {
				linenum++; return;
			}
			tok.nextToken(); // 'THEN'
			execute( statement.substring( statement.indexOf( 'N' ) + 2 )  );
			return;
		}
		
		// var '=' expr
		int var = type.charAt(0) - 'a';
		//write( "DEBUG: " + var + "\n" );
		tok.nextToken(); // '='
		int value = parseExpr();
		vars[var] = value;
		linenum++;
	}
	
}
