import java.util.*;
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

	public static String readLine() throws Exception {
		return in.readLine();
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

	static int[] s, b;
	static int n;
	static int[][][] N;
	
	public static void doit() throws Exception
	{
		n = readInt();
		s = new int[n]; b = new int[n];
		int ss = 0, bb = 0;
		for( int i=0; i<n; i++ ) {
			tok();
			s[i] = nextInt();
			b[i] = nextInt();
			ss += s[i];
			bb += b[i];
		}

		N = new int[2][ss+1][bb+1];

		N[0][0][0] = 1;
		for( int i=1; i<n; i++ )
			for( int j=0; j<=ss; j++ )
				for( int k=0; k<=bb; k++ ) {
					N[i%2][j][k] = N[(i-1)%2][j][k];
					if( j>=s[i] && k>= b[i] ) N[i%2][j][k] += N[(i-1)%2][j-s[i]][k-b[i]];
				}
			
		int meer = 0, crit = 0;
		for( int j=0; j<=ss; j++ )
			for( int k=0; k<=bb; k++ ) {
				if( j+s[0] >= Math.ceil(0.5*ss) && k+b[0] >= Math.ceil(0.6*bb) ) {
					meer += N[(n-1)%2][j][k];
					if( j>=Math.ceil(0.5*ss) && k>=Math.ceil(0.6*bb) )
						meer += N[(n-1)%2][j][k];
					else
						crit += N[(n-1)%2][j][k];
				}

			}
				
		write( meer + " " + crit + "\n" );
	}

}
