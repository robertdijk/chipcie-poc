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
	
	public static int n, k;
	public static int[] x;

	public static void doit() throws Exception
	{
		tok();
		n = nextInt();
		k = nextInt();
		x = new int[n];
		tok();
		for( int i=0; i<n; i++ )
			x[i] = nextInt();
			
		int maxdist = bsearch( 1, (x[n-1]-x[0])/(k-1) );
		write( maxdist + "\n" );
	}
	
	public static boolean possible( int dist )
	{	
		int p = k;
		int i = 0;
		int x0;
		while( p>0 && i<n ) {
			x0 = x[i];
			while( i<n && x[i] - x0 < dist ) i++;
			p--;
		}
		return p==0;			}
	
	public static int bsearch( int min, int max )
	{
		while( min < max ) {
			int mid = (min+max+1)/2;
			if( possible(mid) )
				min = mid;
			else
				max = mid - 1;
		}
		return min;
	}
}
