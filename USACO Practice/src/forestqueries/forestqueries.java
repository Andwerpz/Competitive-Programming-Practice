
//package forestqueries;

import java.io.*;
import java.util.*;

public class forestqueries {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int q = Integer.parseInt(st.nextToken());
    
    int[][] pfx = new int[n + 1][n + 1];
    
    for(int i = 0; i < n; i++) {
    	
    	String line = fin.readLine();
    	
    	for(int j = 0; j < n; j++) {
    		
    		if(line.substring(j, j + 1).equals("*")) {
    			
    			pfx[i + 1][j + 1] += 1;
    		
    		}
    		
    		pfx[i + 1][j + 1] += pfx[i][j + 1] + pfx[i + 1][j] - pfx[i][j];	//gotta remember how to properly construct 2d prefix sums
    		
    	}
    	
    }
    
    StringBuilder fout = new StringBuilder();
    
    for(int i = 0; i < q; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int x1 = Integer.parseInt(st.nextToken());
    	int y1 = Integer.parseInt(st.nextToken());
    	int x2 = Integer.parseInt(st.nextToken());
    	int y2 = Integer.parseInt(st.nextToken());
    	
    	fout.append(pfx[x2][y2] - pfx[x1 - 1][y2] - pfx[x2][y1 - 1] + pfx[x1 - 1][y1 - 1]).append("\n");
    	
    }
    
    System.out.print(fout);
    fin.close();
    
	}
}