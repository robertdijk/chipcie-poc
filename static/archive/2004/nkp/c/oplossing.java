/* avondvierdaagse.java
 *
 * Pieter Eendebak
 * eendebak at math uu nl
 *
 */
 
import java.util.StringTokenizer;
import java.io.*;
import java.util.Arrays;
import java.util.Comparator;
import java.lang.Math;

class Mud {
	public long x, y; 
}

class MudCompare implements Comparator{
	public int compare(Object a, Object b) {
		Mud A = (Mud)a;
		Mud B = (Mud)b;
		
		return (A.x-B.x)<0?-1:1;
	}
}


class Main {
	public static StringTokenizer tok;
	public static String line;
	public static BufferedReader in;

	public static void write(String s) {
		System.out.print(s);
	}
	public static void writen(String s) {
		System.out.print(s+"\n");
	}

	public static int readInt() throws Exception {
  		tok();
	  	return nextInt();
 	}

 	public static void tok() throws Exception {
  		tok = new StringTokenizer(in.readLine());
	}

	public static String nextString() throws Exception {
  		return (String)tok.nextToken();
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
	
	public static void doit() throws Exception
	{
		int n; long l;
		// read in data
		tok();
		n = nextInt();
		l = nextInt();
		
		//writen("Doing run with "+n+" mudpools");

		Mud [] mudpool = new Mud[n];
		
		int i = 0, j;
		for(i=0;i<n;i++) {
			tok();
			mudpool[i] = new Mud();
			mudpool[i].x = nextInt();
			mudpool[i].y = nextInt();
			//writen("read " + mudpool[i].x + " " + mudpool[i].y);
		}
		
		// find optimal number of planks
		Arrays.sort( mudpool, new MudCompare());
		
		long end=0;
		long pl=0;
		
		i=0;
		while(i<n) {
			//writen("i: " + i + " pl: " + pl + " end: " + end);
			if(mudpool[i].y>end) {
				// add new plank
				end = l + Math.max(end, mudpool[i].x);
				pl++;
			}
			else i++;
		}
		
		// print the results
		writen(""+pl);
	}
}
