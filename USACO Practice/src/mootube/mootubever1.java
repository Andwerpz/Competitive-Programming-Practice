/*
ID: andwerp2
LANG: JAVA
TASK: mootube
*/

package mootube;

import java.io.*;
import java.util.*;

class mootubever1 {
	public static void main (String [] args) throws IOException {
		
	//searching in a tree
    
    BufferedReader fin = new BufferedReader(new FileReader("mootube.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("mootube.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int q = Integer.parseInt(st.nextToken());
    
    ArrayList<ArrayList<int[]>> connections = new ArrayList<ArrayList<int[]>>();
    int[][] questions = new int[q][2];
    
    for(int i = 0; i < n; i++) {
    	
    	connections.add(new ArrayList<int[]>());
    	
    }
    
    for(int i = 0; i < n - 1; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int a = Integer.parseInt(st.nextToken()) - 1;
    	int b = Integer.parseInt(st.nextToken()) - 1;
    	int str = Integer.parseInt(st.nextToken());
    	
    	connections.get(a).add(new int[] {b, str});
    	connections.get(b).add(new int[] {a, str});
    	
    }
    
    StringBuilder str = new StringBuilder();
    
    for(int i = 0; i < q; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int k = Integer.parseInt(st.nextToken());
    	int cur = Integer.parseInt(st.nextToken()) - 1;
    	
    	System.out.println("searching node " + cur + " with strength " + k);
    	
    	Stack<Integer> toProcess = new Stack<Integer>();
    	toProcess.add(cur);
    	
    	HashSet<Integer> visited = new HashSet<Integer>();
    	visited.add(cur);
    	
    	while(toProcess.size() != 0) {
    		
    		int c = toProcess.pop();
    		
    		ArrayList<int[]> curCon = connections.get(c);
    		
    		for(int j = 0; j < curCon.size(); j ++) {
    			System.out.println(curCon.get(j)[0] + " " + curCon.get(j)[1]);
    			if(curCon.get(j)[1] >= k && !visited.contains(curCon.get(j)[0])) {
    				
    				toProcess.add(curCon.get(j)[0]);
    				visited.add(curCon.get(j)[0]);
    				
    			}
    		}
    		
    	}
    	
    	str.append(visited.size() - 1 + "\n");
    	
    }
    
    fout.print(str);    
    fin.close();
    fout.close();
    
	}
}