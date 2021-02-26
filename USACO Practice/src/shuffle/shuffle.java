/*
ID: andwerp2
LANG: JAVA
TASK: shuffle
*/



import java.io.*;
import java.util.*;

class shuffle {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("shuffle.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("shuffle.out")));
    
    
    int n = Integer.parseInt(fin.readLine());
    
    int[] moves = new int[n];
    HashSet<Integer> visited = new HashSet<Integer>();
    
    int numLooping = 0;
    
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    for(int i = 0; i < n; i++) {
    	
    	moves[i] = Integer.parseInt(st.nextToken()) - 1;
    	
    }
    
    
    
    for(int i = 0; i < n; i++) {
    	if(!visited.contains(i)) {
    		
    		HashSet<Integer> curVisited = new HashSet<Integer>();
    		ArrayList<Integer> visitOrder = new ArrayList<Integer>();
    		
    		int pointer = i;
    		
    		curVisited.add(pointer);
    		visitOrder.add(pointer);
    		
    		pointer = moves[pointer];
    		
    		while(!curVisited.contains(pointer) && !visited.contains(pointer)) {
    			
//    			System.out.println(!curVisited.contains(pointer));
//    			System.out.println(!visited.contains(pointer));
//    			
//    			System.out.println(i);
    			
    			curVisited.add(pointer);
    			visitOrder.add(pointer);
    			
    			pointer = moves[pointer];
    			
    		}
    		
    		if(curVisited.contains(pointer)) {
    			for(int j = 0; j < visitOrder.size(); j++) {
    				if(visitOrder.get(j) == pointer) {
    					
    					numLooping += visitOrder.size() - j;
    					
    				}
    			}
    		}
    		
    		visited.addAll(curVisited);
    		
    	}
    }
    
    
    fout.println(numLooping);
    
    fin.close();
    fout.close();
    
	}
}