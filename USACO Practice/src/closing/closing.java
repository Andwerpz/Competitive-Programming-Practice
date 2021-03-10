/*
ID: andwerp1
LANG: JAVA
TASK: closing
*/

//package closing;

import java.io.*;
import java.util.*;

class closing {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("closing.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("closing.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    
    ArrayList<ArrayList<Integer>> connections = new ArrayList<ArrayList<Integer>>();
    
    for(int i = 0; i < n + 1; i++) {
    	
    	connections.add(new ArrayList<Integer>());
    	
    }
    
    boolean[] isClosed = new boolean[n];
    
    for(int i = 0; i < m; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int a = Integer.parseInt(st.nextToken()) - 1;
    	int b = Integer.parseInt(st.nextToken()) - 1;
    	
    	connections.get(a).add(b);
    	connections.get(b).add(a);
    	
    }
    
    for(int i = 0; i < connections.size(); i++) {
    	//System.out.print(i + ": ");
    	for(int j = 0; j < connections.get(i).size(); j++) {
    		//System.out.print(connections.get(i).get(j) + " ");
    	}
    	//System.out.println();
    }
    
    
    int numOpen = n;
    
    boolean[] closed = new boolean[n];
    
    
    for(int i = 0; i < n; i++) {
    	
    	
    	
    	Stack<Integer> toProcess = new Stack<Integer>();
    	HashSet<Integer> visited = new HashSet<Integer>();
    	
    	if(i == 0) {
    		
    		
    		
    	}
    	
    	else {
    		
    		////System.out.println("numopen --");
    		
    		numOpen --;
    	
    		int closeNext = Integer.parseInt(fin.readLine()) - 1;
    		
    		//System.out.println("close next: " + closeNext);
    	
    		closed[closeNext] = true;
    		
    	}
    	//System.out.println("num remaining: " + numOpen);
    	
    	for(int j = 0; j < n; j++) {
    		if(!closed[j]) {
    			
    			toProcess.add(j);
    			visited.add(j);
    			//System.out.print(j + " ");
    			break;
    		}
    	}
    	
    	while(toProcess.size() != 0) {
    		
    		int curBarn = toProcess.pop();
    		
    		ArrayList<Integer> curConn = connections.get(curBarn);
    		
    		for(int j = 0; j < curConn.size(); j++) {
    			
    			
    			
    			if(!visited.contains(curConn.get(j)) && !closed[curConn.get(j)]) {
    				
    				toProcess.add(curConn.get(j));
    				visited.add(curConn.get(j));
    				
    				//System.out.print(curConn.get(j) + " ");
    				
    			}
    			
    		}
    		
    	}
    	
    	//System.out.println("");
    	
    	//System.out.println("visited size: " + visited.size());
    	
    	//System.out.println("\n");
    	
    	if(numOpen == visited.size()) {
    		fout.println("YES");
    	}
    	
    	else {
    		fout.println("NO");
    	}
    	
    }
    
    
    fin.close();
    fout.close();
    
	}
}