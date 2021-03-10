/*
ID: andwerp1
LANG: JAVA
TASK: paintbarn
*/

package paintbarn;

import java.io.*;
import java.util.*;

class paintbarnver1 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("paintbarn.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("paintbarn.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    
    int[][] barn = new int[1001][1001];
    int[][] pfx = new int[1001][1001]; 
    
    for(int i = 0; i < n; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int startX = Integer.parseInt(st.nextToken());
    	int startY = Integer.parseInt(st.nextToken());
    	int endX = Integer.parseInt(st.nextToken());
    	int endY = Integer.parseInt(st.nextToken());
    	
    	for(int j = startX; j < endX; j++) {
    		for(int l = startY; l < endY; l++) {
    			barn[j][l] ++;
    		}
    	}
    	
    }
    
    for(int[] i : barn) {
    	for(int j : i) {
    		System.out.print(j + " ");
    	}
    	System.out.println();
    }
    
    for(int i = 1; i < barn.length; i++) {
    	for(int j = 1; j < barn.length; j++) {
    		
    		if(barn[i][j] == k) {
    			pfx[i][j] = 1 + pfx[i - 1][j] + pfx[i][j - 1] - pfx[i - 1][j - 1];
    			
    		}
    		
    		else {
    			pfx[i][j] = pfx[i - 1][j] + pfx[i][j - 1] - pfx[i - 1][j - 1];
    		}
    		
    		
    		
    	}
    }
    
    System.out.println();
    
    for(int[] i : pfx) {
    	for(int j : i) {
    		System.out.print(j + " ");
    	}
    	System.out.println();
    }
    
    fout.println(pfx[pfx.length - 1][barn.length - 1]);
    
    fin.close();
    fout.close();
    
	}
}