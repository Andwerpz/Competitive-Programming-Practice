
package buildingroads;

import java.io.*;
import java.util.*;

public class buildingroadsver1 {
	public static void main (String [] args) throws IOException {
		
	//we just have to do a floodfill on the graph and figure out how many connected components there are.
	//then from there, we just have to connect all the components into a chain to get the least amount of components. 
		
	//too slow since array based approaches take too much time, try making a node object to call upon with connections.
    
	BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    
    ArrayList<ArrayList<Integer>> connections = new ArrayList<ArrayList<Integer>>();
    ArrayList<ArrayList<Integer>> groups = new ArrayList<ArrayList<Integer>>();
    boolean[] visited = new boolean[n];
    
    for(int i = 0; i < n; i++) {
    	
    	connections.add(new ArrayList<Integer>());
    	
    }
    
    for(int i = 0; i < m; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int a = Integer.parseInt(st.nextToken()) - 1;
    	int b = Integer.parseInt(st.nextToken()) - 1;
    	
    	connections.get(a).add(b);
    	connections.get(b).add(a);
    	
    }
    
    for(int i = 0; i < connections.size(); i++) {
    	
    	if(!visited[i]) {
    		
    		System.out.println(i);
    		
    		Stack<Integer> toProcess = new Stack<Integer>();
    		toProcess.add(i);
    		
    		visited[i] = true;
    		
    		ArrayList<Integer> curGroup = new ArrayList<Integer>();
    		curGroup.add(i);
    		
    		while(toProcess.size() != 0) {
    			
    			
    			
    			int cur = toProcess.pop();
    			System.out.println(cur);
    			ArrayList<Integer> curCon = connections.get(cur);
    			
    			for(int j = 0; j < curCon.size(); j++) {
    				
    				if(!visited[curCon.get(j)]) {
    					
    					toProcess.add(curCon.get(j));
    					visited[curCon.get(j)] = true;
    					curGroup.add(curCon.get(j));
    					
    				}
    				
    			}
    			
    		}
    		
    		groups.add(curGroup);
    		
    	}
    	
    }
    
    StringBuilder fout = new StringBuilder();
    
    fout.append(groups.size() - 1).append("\n");
    
    //System.out.println(groups.size() - 1);
    
    for(int i = 1; i < groups.size(); i++) {
    	
    	fout.append((groups.get(i - 1).get(0) + 1) + " " + (groups.get(i).get(0) + 1)).append("\n");
    	
    	//System.out.println((groups.get(i - 1).get(0) + 1) + " " + (groups.get(i).get(0) + 1));
    	
    }
    
    System.out.print(fout);
        
    fin.close();
    
	}
}