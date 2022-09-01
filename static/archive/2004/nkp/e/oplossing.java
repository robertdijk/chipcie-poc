import java.util.*;
import java.io.*;
import java.text.*;

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
	
	static DecimalFormat format;

	public static void main(String[] args) throws Exception {
		in = new BufferedReader( new InputStreamReader(System.in) );
		format = new DecimalFormat( "##0.00" );
		int runs = readInt();
		for( int run=0; run<runs; run++ )
			doit();
	}

	
	public static void doit() throws Exception
	{
		tok();
		int p = nextInt();
		int q = nextInt();
		tok();
		int k = nextInt();
	//	Kruispunt[] kp = new Kruispunt[k+1];
	//	for( int i=1; i<=k; i++ )
	//		kp[i] = new Kruispunt(i);
		int w = nextInt();
		
		int[][] dist = new int[k+1][k+1];
		double[][] pr = new double[k+1][k+1];
		int[] nways = new int[k+1];
		int[][] ways = new int[k+1][k];
		
		for( int i=0; i<w; i++ ) {
			tok();
			int b = nextInt();
			int e = nextInt();
			dist[b][e] = nextInt();
			pr[b][e] = (100-nextInt())/100.0;
			ways[e][ nways[e] ] = b;
			nways[e]++;
		}
		
		double[][] prob = new double[k+1][q+1];
		for( int i=1; i<=k; i++ )
			for( int j=0; j<=q; j++ )
				prob[i][j] = 3; // not initialized yet
		prob[1][0] = 1; // we haven't seen a lion yet
				
		for( int t=1; t<=q; t++ ) {
			for( int u=1; u<=k; u++ ) {
				for( int v=0; v<nways[u]; v++ ) {
					if( dist[ways[u][v]][u] <= t && prob[ ways[u][v] ][ t-dist[ways[u][v]][u] ] < 2 ) {
						double newprob = prob[ ways[u][v] ][ t-dist[ways[u][v]][u] ] * pr[ ways[u][v] ][ u ];
						if( newprob < prob[u][t] ) 
							prob[u][t] = newprob;
					}
					
				}
			}
		}
			
		double min = 3;
		for( int i=p; i<=q; i++ )
			if( prob[1][i] < min )
				min = prob[1][i];
		
		if( min < 2 )
			write( format.format((1.0-min)*100.0) + "\n" );
		else
			write( "onmogelijk\n" );
		
	}
}
