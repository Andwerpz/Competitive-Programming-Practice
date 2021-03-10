/*
ID: andwerp1
LANG: JAVA
TASK: paintbarn
*/

package paintbarn;

import java.io.*;
import java.util.*;

class paintbarnver2 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("paintbarn.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("paintbarn.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    
    int[][] pfx = new int[10][10]; 
    
    for(int i = 0; i < n; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int startX = Integer.parseInt(st.nextToken()) + 1;
    	int startY = Integer.parseInt(st.nextToken()) + 1;
    	int endX = Integer.parseInt(st.nextToken()) + 1;
    	int endY = Integer.parseInt(st.nextToken()) + 1;
    	
    	pfx[startX][startY]++;
    	pfx[endX][endY]++;
    	pfx[startX][endY]--;
    	pfx[endX][startY]--;
    	
    }
    
    for(int[] i : pfx) {
    	for(int j : i) {
    		System.out.print(j + " ");
    	}
    	System.out.println();
    }
    System.out.println();
    
    int sum = 0;
    
    for(int i = 1; i < pfx.length; i++) {
    	for(int j = 1; j < pfx.length; j++) {
    		
    		pfx[i][j] += pfx[i][j - 1] + pfx[i - 1][j] - pfx[i - 1][j - 1];
    		if(pfx[i][j] == k) {
    			sum++;
    		}
    		
    	}
    }
    
    
    
    
    for(int[] i : pfx) {
    	for(int j : i) {
    		System.out.print(j + " ");
    	}
    	System.out.println();
    }
    
    fout.println(sum);
    
    fin.close();
    fout.close();
    
	}
}