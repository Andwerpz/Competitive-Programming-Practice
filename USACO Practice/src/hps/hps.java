/*
ID: andwerp1
LANG: JAVA
TASK: hps
*/



import java.io.*;
import java.util.*;

class hps {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("hps.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("hps.out")));
    
    
    int n = Integer.parseInt(fin.readLine());
    
    int[] h = new int[n];
    int[] p = new int[n];
    int[] s = new int[n];
    
    
    for(int i = 0; i < n; i++) {
    	
    	String nextMove = fin.readLine();
    	
    	if(i == 0) {
    		
    		if(nextMove.equals("H")) {
    			h[0] = 1;
    		}
    		
    		else if(nextMove.equals("P")) {
    			p[0] = 1;
    		}
    		
    		else if(nextMove.equals("S")) {
    			s[0] = 1;
    		}
    		
    	}
    	
    	else {
    		
    		if(nextMove.equals("H")) {
    			h[i] += 1;
    		}
    		
    		else if(nextMove.equals("P")) {
    			p[i] += 1;
    		}
    		
    		else if(nextMove.equals("S")) {
    			s[i] += 1;
    		}
    		
    		h[i] += h[i - 1];
    		p[i] += p[i - 1];
    		s[i] += s[i - 1];
    		
    	}
    	
    }
    
    int bestSwitch = 0;
    int max = 0;
    
    for(int i = 0; i < n; i++) {
    	
    	int beforeSwitch = Math.max(Math.max(h[i], p[i]), s[i]);
    	
    	int afterSwitch = Math.max(Math.max(h[n - 1] - h[i], p[n - 1] - p[i]), s[n - 1] - s[i]);
    	
    	if(beforeSwitch + afterSwitch > max) {
    		
    		bestSwitch = i;
    		max = beforeSwitch + afterSwitch;
    		
    	}
    	
    	
    }
    
    fout.println(max);
    
    fin.close();
    fout.close();
    
	}
}