/*
ID: andwerp2
LANG: JAVA
TASK: maxcross
*/

package maxcross;

import java.io.*;
import java.util.*;

class maxcrossver1 {
	
	static boolean doesWork(int[] brokenLights, int numFixed, int goal, int numCrosswalks) {
		
		System.out.println(numFixed + " " + goal + " " + numCrosswalks + " " + brokenLights.length);
		
		if(brokenLights.length == numFixed + 1) {
			
			return true;
		}
		
		if(brokenLights[numFixed] - 1 > goal) {
			return true;
		}
		
		if(numCrosswalks - brokenLights[brokenLights.length - (numFixed + 1)] - 1 > goal) {
			return true;
		}
		for(int i = 1; i < brokenLights.length - numFixed - 2; i++) {
			
			if(brokenLights[i + numFixed + 1] - brokenLights[i] - 1 > goal) {
				
				return true;
				
			}
			
		}
		
		return false;
		
	}
	
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("maxcross.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("maxcross.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    int b = Integer.parseInt(st.nextToken());
    
    int[] brokenLights = new int[b];
    
    for(int i = 0; i < b; i++) {
    	
    	brokenLights[i] = Integer.parseInt(fin.readLine());
    	
    }
    
    Arrays.sort(brokenLights);	//sorted into ascending order
    
    int pointer = b / 2;
    
    int low = 0;
    int high = b;
    
    boolean solved = false;
    
    while(!solved) {
    	
    	//System.out.println(low + " " + high + " " + pointer);
    
    	
    	if(doesWork(brokenLights, pointer, k, n)) {
    		
    		//System.out.println(pointer + " does work");
    		
    		high = pointer;
    		pointer = (high + low) / 2;
    		
    		if(!doesWork(brokenLights, pointer + 1, k, n)) {
    			break;
    		}
    		
    	}
    	
    	else {
    		low = pointer;
    		pointer = (high + low) / 2;
    	}
    	
    	if(low + 1 == high) {
    		break;
    	}
    	
    }
    
    fout.println(low);
    
    fin.close();
    fout.close();
    
	}
}