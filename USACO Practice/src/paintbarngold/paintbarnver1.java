/*
ID: andwerp1
LANG: JAVA
TASK: paintbarn
*/

package paintbarngold;

import java.io.*;
import java.util.*;

class paintbarngold {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("paintbarn.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("paintbarn.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    
    int[][] pfx = new int[1001][1001];
    
    for(int i = 0; i < n; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int startX = Integer.parseInt(st.nextToken()) + 1;
    	int startY = Integer.parseInt(st.nextToken()) + 1;
    	int endX = Integer.parseInt(st.nextToken()) + 1;
    	int endY = Integer.parseInt(st.nextToken()) + 1;
    	
    }
    
    for(int i = 1; i < pfx.length; i++) {
    	for(int j = 1; j < pfx.length; j++) {
    		pfx[i][j] += pfx[i - 1][j] + pfx[i][j - 1] - pfx[i - 1][j - 1];
    	}
    }
    
    fin.close();
    fout.close();
    
	}
}