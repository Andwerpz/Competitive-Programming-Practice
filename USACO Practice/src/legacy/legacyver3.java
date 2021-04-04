
package legacy;

import java.io.*;
import java.util.*;

public class legacyver3 {
	public static void main (String [] args) throws IOException {
		
	//using dijkstra's algorithm
	//fixed the algorithm from previous iterations, just too slow
    
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
    Arrays.fill(dist, -1);
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
    
    
    boolean[] v = new boolean[n];
    boolean done = false;
    
    
    while(true) {
    	long curDist = Long.MAX_VALUE;
    	int cur = -1;
    	for(int i = 0; i < dist.length; i++) {
    		if((dist[i] != -1 && curDist > dist[i]) && !v[i]) {
    			curDist = dist[i];
    			cur = i;
    		}
    	}
    	if(cur == -1) {
    		break;
    	}
    	v[cur] = true;
    	HashMap<Integer, Integer> con = connections.get(cur);
    	Set<Integer> keys = con.keySet();
    	for(int k : keys) {
    		long cost = curDist + con.get(k);
    		if(dist[k] > cost || dist[k] == -1) {
    			dist[k] = cost;
    		}
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