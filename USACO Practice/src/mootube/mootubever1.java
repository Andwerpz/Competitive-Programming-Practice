/*
ID: andwerp2
LANG: JAVA
TASK: mootube
*/

package mootube;

import java.io.*;
import java.util.*;

class mootubever1 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("example.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("example.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int q = Integer.parseInt(st.nextToken());
    
    int[][] connections = new int[n - 1][3];
    int[][] questions = new int[q][2];
    
    for(int i = 0; i < n - 1; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	connections[i][0] = Integer.parseInt(st.nextToken());
    	connections[i][1] = Integer.parseInt(st.nextToken());
    	connections[i][2] = Integer.parseInt(st.nextToken());
    	
    }
    
    for(int i = 0; i < q; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	questions[i][0] = Integer.parseInt(st.nextToken());
    	questions[i][1] = Integer.parseInt(st.nextToken());
    	
    }
    
    fin.close();
    fout.close();
    
	}
}