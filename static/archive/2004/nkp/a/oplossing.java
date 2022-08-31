/* bustijden.java
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

class BusTime {
	public int time = 0;
	public int delta = 0;
	public int hi = 0;
	public int low = 0;

}

class BusCompareLow implements Comparator{
	public int compare(Object a, Object b) {
		BusTime A = (BusTime)a;
		BusTime B = (BusTime)b;
		
		return (A.low-B.low);
	}
}
class BusCompareHi implements Comparator{
	public int compare(Object a, Object b) {
		BusTime A = (BusTime)a;
		BusTime B = (BusTime)b;
		
		return (A.hi-B.hi);
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
	
	public static int n, k;
	public static int[] x;

	public static void doit() throws Exception
	{
		// read in data
		tok();
		n = nextInt();

		//writen("Doing run with "+n+" busses");

		int best = 0;
		int worst = 0;

		BusTime [][] busses = new BusTime[n][];
		int line[] = new int[n];
		int dis[] = new int[n];
		
		int i = 0, j;
		while(i<n) {
			tok();
			int b = nextInt();
			int t = nextInt();

			busses[i] = new BusTime[b];
			line[i]=b;
			dis[i]=t;
			for(j=0; j<b; j++) {
				busses[i][j] = scanBusTime();
				//writen(" line "+i+", bustimes "+busses[i][j].time+", "+busses[i][j].delta);
			}
			i++;
		}
		
		// find optimal bus time	
		// best arrival
		int ltime = 9*60, htime=9*60;
		
		for(i=0;i<n;i++) {
			Arrays.sort( busses[i], new BusCompareLow());
			j=0;
			while(j<line[i] && busses[i][j].hi<ltime) j++;
			if(j==line[i]) { writen("Wrong input"); return; }
			ltime = Math.max(busses[i][j].low, ltime) + dis[i];			
			
			Arrays.sort( busses[i], new BusCompareHi());
			j=0;
			while(j<line[i] && busses[i][j].low<htime) j++;
			if(j==line[i]) { writen("Wrong input"); return; }
			htime = busses[i][j].hi + dis[i];
		}
		
		// print the results
		int lhi = ltime/60;
		int lmi = ltime%60;
		int hhi = htime/60;
		int hmi = htime%60;
		String lm = (lmi<10)?("0"+lmi):(""+lmi);
		String hm = (hmi<10)?("0"+hmi):(""+hmi);
		String lh = (lhi<10)?("0"+lhi):(""+lhi);
		String hh = (hhi<10)?("0"+hhi):(""+hhi);
		writen(lh+":"+lm+" "+hh+":"+hm);
	}
	
	public static BusTime scanBusTime() throws Exception
	{
		BusTime b = new BusTime();

		tok();
		
		String str = nextString();
		int c = str.indexOf(':');
		int h = Integer.parseInt(str.substring(0,c));
		int m = Integer.parseInt(str.substring(c+1));
		b.time = 60*h+m;
		
		str = nextString();
		b.delta= Integer.parseInt(str.substring(1, str.length()-1));

		b.hi = b.time+b.delta;
		b.low = b.time-b.delta;
		return b;
	}

}
