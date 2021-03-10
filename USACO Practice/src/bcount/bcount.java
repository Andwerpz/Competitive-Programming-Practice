/*
ID: andwerp1
LANG: JAVA
TASK: bcount
*/

//package bcount;

import java.io.*;
import java.util.*;

class bcount {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("bcount.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("bcount.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int q = Integer.parseInt(st.nextToken());
    
    int[] h = new int[n];
    int[] g = new int[n];
    int[] j = new int[n];
    
    for(int i = 0; i < n; i++) {
    	
    	int nextBreed = Integer.parseInt(fin.readLine());
    	
    	if(i == 0) {
    		
    		if(nextBreed == 1) {
    			h[0] = 1;
    		}
    		
    		else if(nextBreed == 2) {
    			g[0] = 1;
    		}
    		
    		else if(nextBreed == 3) {
    			j[0] = 1;
    		}
    		
    	}
    	
    	else {
    		
    		if(nextBreed == 1) {
    			h[i] += 1;
    		}
    		
    		else if(nextBreed == 2) {
    			g[i] += 1;
    		}
    		
    		else if(nextBreed == 3) {
    			j[i] += 1;
    		}
    		
    		h[i] += h[i - 1];
    		g[i] += g[i - 1];
    		j[i] += j[i - 1];
    		
    	}
    	
    }
    
    
    for(int i = 0; i < q; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int start = Integer.parseInt(st.nextToken()) - 2;
    	int end = Integer.parseInt(st.nextToken()) - 1;
    	
    	String output = "";
    	
    	if(start < 0) {
    		
    		output = (h[end]) + " " + (g[end]) + " " + (j[end]);
    		
    	}
    	
    	else {
    		
    		output = (h[end] - h[start]) + " " + (g[end] - g[start]) + " " + (j[end] - j[start]);
    		
    	}
    	
    	
    	
    	fout.println(output);
    	
    }
    
    fin.close();
    fout.close();
    
	}
}