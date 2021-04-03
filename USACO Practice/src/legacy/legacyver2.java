
package legacy;

import java.io.*;
import java.util.*;

public class legacyver2 {
	public static void main (String [] args) throws IOException {
		
	//using dijkstra's algorithm
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int q = Integer.parseInt(st.nextToken());
    int s = Integer.parseInt(st.nextToken()) - 1;
    
    ArrayList<HashMap<Integer, Integer>> connections = new ArrayList<HashMap<Integer, Integer>>();	//try to circumvent the mem issue with arraylist
    for(int i = 0; i < n; i++) {
    	connections.add(new HashMap<Integer, Integer>());
    }
    long[] dist = new long[n];
    for(int i = 0; i < n; i++) {
    	dist[i] = -1;
    }
    dist[s] = 0;
    
    
    
    for(int i = 0; i < q; i++) {
    	st = new StringTokenizer(fin.readLine());
    	int t = Integer.parseInt(st.nextToken());
    	if(t == 1) {
    		int v = Integer.parseInt(st.nextToken()) - 1;
    		int u = Integer.parseInt(st.nextToken()) - 1;
    		int w = Integer.parseInt(st.nextToken());
    		if(connections.get(v).containsKey(u) && connections.get(v).get(u) < w) {
    			continue;
    		}
    		else {
    			connections.get(v).put(u, w);
    		}
    	}
    	else if(t == 2) {
    		int v = Integer.parseInt(st.nextToken()) - 1;
    		int l = Integer.parseInt(st.nextToken()) - 1;
    		int r = Integer.parseInt(st.nextToken()) - 1;
    		int w = Integer.parseInt(st.nextToken());
    		for(int j = l; j <= r; j++) {
    			if(connections.get(v).containsKey(j) && connections.get(v).get(j) < w) {
        			continue;
        		}
        		else {
        			connections.get(v).put(j, w);
        		}
    		}
    	}
    	else {
    		int v = Integer.parseInt(st.nextToken()) - 1;
    		int l = Integer.parseInt(st.nextToken()) - 1;
    		int r = Integer.parseInt(st.nextToken()) - 1;
    		int w = Integer.parseInt(st.nextToken());
    		for(int j = l; j <= r; j++) {
    			if(connections.get(j).containsKey(v) && connections.get(j).get(v) < w) {
        			continue;
        		}
        		else {
        			connections.get(j).put(v, w);
        		}
    		}
    	}
    }
    
    
    
    ArrayList<long[]> qu = new ArrayList<long[]>();
    qu.add(new long[] {0, s});
    
    boolean[] v = new boolean[n];
    v[s] = true;
    boolean done = false;
    
    
    while(qu.size() != 0) {	//dijkstra's algo bfs
    	boolean valueChanged = false;
    	long[] next = qu.remove(qu.size() - 1);
    	int cur = (int)next[1];
    	//System.out.println("now processing " + cur);
    	HashMap<Integer, Integer> con = connections.get(cur);
    	Set<Integer> keys = connections.get(cur).keySet();
    	for(int i : keys) {
    		long cost = con.get(i) + dist[cur];
    		if(cost < dist[i] || dist[i] == -1) {
    			valueChanged = true;
				dist[i] = cost;
			}
			if(!v[i]) {
				qu.add(new long[] {(long)dist[i], (long)i});
				v[i] = true;
			}
			
			//System.out.println("to planet " + i + " cost " + cost);
			
    		
    	}
    	if(valueChanged) {
	    	for(int i = 0; i < qu.size(); i++) {
	    		qu.get(i)[0] = dist[i];
	    	}
	    	qu.sort((a, b) -> Long.compare(a[0], b[0]));
    	}
    	
    }
    
    
    
    
    StringBuilder fout = new StringBuilder();
    for(int i = 0; i < dist.length; i++) {
    	fout.append(dist[i] + " ");
    }
    
    System.out.print(fout);
    fin.close();
    
	}
}