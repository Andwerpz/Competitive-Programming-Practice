/*
ID: andwerp1
LANG: JAVA
TASK: numtri
*/

//package numtri;

import java.io.*;
import java.util.*;

class numtri {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("numtri.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("numtri.out")));
    
    int n = Integer.parseInt(fin.readLine());
    
    ArrayList<ArrayList<Integer>> nums = new ArrayList<ArrayList<Integer>>();
    
    for(int i = 0; i < n; i++) {
    	
    	StringTokenizer st = new StringTokenizer(fin.readLine());
    	
    	nums.add(new ArrayList<Integer>());
    	
    	for(int j = 0; j < i + 1; j++) {
    		
    		if(i == 0) {
    			nums.get(i).add(Integer.parseInt(st.nextToken()));
    		}
    		
    		else if(j == 0) {
    			nums.get(i).add(nums.get(i - 1).get(0) + Integer.parseInt(st.nextToken()));
    		}
    		
    		else if(j == i) {
    			nums.get(i).add(nums.get(i - 1).get(j - 1) + Integer.parseInt(st.nextToken()));
    		}
    		
    		else {
    			if(nums.get(i - 1).get(j) > nums.get(i - 1).get(j - 1)) {
    				nums.get(i).add(nums.get(i - 1).get(j) + Integer.parseInt(st.nextToken()));
    			}
    			
    			else {
    				nums.get(i).add(nums.get(i - 1).get(j - 1) + Integer.parseInt(st.nextToken()));
    			}
    		}
    		
    		
    		
    		//System.out.print(nums.get(i).get(j) + " ");
    		
    	}
    	
    	//System.out.println();
    	
    }
    
    int max = 0;
    
    for(int i = 0; i < n; i++) {
    	if(max < nums.get(n - 1).get(i)) {
    		max = nums.get(n - 1).get(i);
    	}
    }
    
    fout.println(max);
    
    fin.close();
    fout.close();
    
	}
}