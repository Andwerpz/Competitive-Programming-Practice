/*
ID: andwerp1
LANG: JAVA
TASK: stacking
*/

//package stacking;

import java.io.*;
import java.util.*;

class stacking {
	public static void main (String [] args) throws IOException {
		
	Scanner fin = new Scanner(System.in);
	
    
    //BufferedReader fin = new BufferedReader(new FileReader("stacking.in"));
    //PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("stacking.out")));
    StringTokenizer st = new StringTokenizer(fin.nextLine());
    
    
    int n = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    
    int[] pfx = new int[n + 1];
    
    for(int i = 0; i < k; i++) {
    	
    	st = new StringTokenizer(fin.nextLine());
    	
    	int begin = Integer.parseInt(st.nextToken()) - 1;
    	int end = Integer.parseInt(st.nextToken()) - 1;
    	
    	pfx[begin] ++;
    	pfx[end + 1] --;
    	
    }
    
    //System.out.println();
    
    for(int i = 1; i < pfx.length; i++) {
    	
    	pfx[i] += pfx[i - 1];
    	
    	
    }
    
    int[] haybales = new int[n];
    
    for(int i = 0; i < haybales.length; i++) {
    	
    	haybales[i] = pfx[i];
    	
    }
    
    Arrays.sort(haybales);
    
    
    //fout.println(pfx[(n / 2)]);
    
    System.out.println(haybales[(n / 2)]);
    
    fin.close();
    
    
	}
}