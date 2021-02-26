/*
ID: andwerp2
LANG: JAVA
TASK: cbarn
*/

package cbarn;

import java.io.*;
import java.util.*;

class cbarnver1 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("cbarn.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("cbarn.out")));
    
    
    int n = Integer.parseInt(fin.readLine());
    
    int[] barns = new int[n];
    
    for(int i = 0; i < n; i++) {
    	
    	barns[i] = Integer.parseInt(fin.readLine());
    	
    }
    
    int min = Integer.MAX_VALUE;
    
    for(int i = 1; i < n; i++) {
    	
    	if(barns[i] == 0 && barns[i - 1] != 0) {
    		
    		int[] temp = Arrays.copyOf(barns, barns.length);
    		int[] moved = new int[n];
    		
    		int curZero = i;
    		
    		boolean finished = false;
    		
    	}
    	
    }
    
    fin.close();
    fout.close();
    
	}
}