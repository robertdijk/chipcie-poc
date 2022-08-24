import java.util.*;
import java.util.stream.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.InputStream;
import java.util.StringTokenizer;

public class solution {
  public static void main(String[] args) throws IOException {

    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());

    int n = Integer.parseInt(st.nextToken()); 
    int m = Integer.parseInt(st.nextToken()); 

    st = new StringTokenizer(br.readLine());
    int s = Integer.parseInt(st.nextToken()); s--; 
    int t = Integer.parseInt(st.nextToken()); t--;
    long C = Integer.parseInt(st.nextToken());


    ArrayList<ArrayList<Edge>> Adj = new ArrayList<ArrayList<Edge>>(n);
    for(int i=0; i <n; i++){
      Adj.add(new ArrayList<Edge>());
    }

    int u, v, p;
    for (int i = 0; i < m; i++) {
      st = new StringTokenizer(br.readLine());
      u = Integer.parseInt(st.nextToken()); u--;
      v = Integer.parseInt(st.nextToken()); v--;
      p = Integer.parseInt(st.nextToken());

      Adj.get(u).add(new Edge(v, p));
      Adj.get(v).add(new Edge(u, p));
    }

    ArrayList<Long> remaining = new ArrayList<Long>(Collections.nCopies(n, 0L));
    boolean[] visited = new boolean[n]; //initialized to false

    remaining.set(s, C);

    PriorityQueue<Pair> q = new PriorityQueue<Pair>();
    q.add(new Pair(C, s));
    while(q.peek() != null){
      Pair elt = q.poll();
      long ru = elt.value;
      u = elt.index;
      if(visited[u]) continue;
      visited[u] =  true;

      if(u == t) break;

      for(int i=0; i < Adj.get(u).size(); i++){
        v = Adj.get(u).get(i).v;
        if(!visited[v]){
          p = Adj.get(u).get(i).p;
          long rv = (ru * (100 - p))/100;
          if(rv > remaining.get(v)){
            remaining.set(v, rv);
            q.add(new Pair(rv, v));
          }
        }
      }
    }

    System.out.println(remaining.get(t));
  }
}

class Pair implements Comparable<Pair> {
    Long value;
    Integer index;

    public Pair(Long value, Integer index) {
        this.value = value;
        this.index = index;
    }

    @Override
    public int compareTo(Pair o) {
        return (int)(o.value - value);
    }
}

class Edge{
    Integer v;
    Integer p;

    public Edge(Integer v, Integer p) {
        this.v = v;
        this.p = p;
    }
}
