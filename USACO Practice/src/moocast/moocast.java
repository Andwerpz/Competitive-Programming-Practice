/*
ID: andwerp2
LANG: JAVA
TASK: moocast
*/

//package moocast;

import java.io.*;
import java.util.*;

class moocast {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("moocast.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("moocast.out")));
    
    int n = Integer.parseInt(fin.readLine());
    
    ArrayList<int[]> cows = new ArrayList<int[]>();
    
    for(int i = 0; i < n; i++) {
    	
    	StringTokenizer st = new StringTokenizer(fin.readLine());
    	
    	int[] cow = new int[] {Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken())};
    	
    	cows.add(cow);
    	
    }
    
    int max = 0;
    
    for(int i = 0; i < cows.size(); i++) {
    	
    	ArrayList<int[]> toProcess = new ArrayList<int[]>();
    	HashSet<Integer> visited = new HashSet<Integer>();
    	
    	toProcess.add(cows.get(i));
    	visited.add(i);
    	
    	while(toProcess.size() != 0) {
    		
    		ArrayList<int[]> nextToProcess = new ArrayList<int[]>();
    		
    		for(int j = 0; j < toProcess.size(); j++) {
    			
    			for(int k = 0; k < cows.size(); k++) {
    				
    				if(!visited.contains(k)) {
    					
    					int p = toProcess.get(j)[2];
    					
    					double dist = Math.sqrt(Math.pow(cows.get(k)[0] - toProcess.get(j)[0], 2) + Math.pow(cows.get(k)[1] - toProcess.get(j)[1], 2));
    					
    					if(p >= dist) {
    						
    						nextToProcess.add(cows.get(k));
    						visited.add(k);
    						
    					}
    					
    				}
    				
    			}
    			
    		}
    		
    		toProcess = nextToProcess;
    		
    	}
    	
    	if(visited.size() > max) {
    		max = visited.size();
    	}
    	
    }
    
    
    fout.println(max);
    
    fin.close();
    fout.close();
    
	}
}