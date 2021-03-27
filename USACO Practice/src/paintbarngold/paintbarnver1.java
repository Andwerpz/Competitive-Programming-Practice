/*
ID: andwerp1
LANG: JAVA
TASK: paintbarn
*/

package paintbarngold;

import java.io.*;	
import java.util.*;

class paintbarnver1 {
	public static void main (String [] args) throws IOException {
		
	//for this one, we need to first construct the base barn wall, and then from there, we need to figure out
	//which two subrectangles to paint to get the most cells with k layers of paint.
		
	//Since the two rectangles that are selected have to be disjoint, we don't have to update the pfx sum array in between rectangles.
		
	//First we construct a prefix sum array with the +1s being the cells 1 away from k layers of paint, and the -1s being the ones at k layers of paint. 0 will occupy every other cell. 
	//next, we search for the maximum subarray sum using kandanes algorithm modified for 2d arrays - being researched
		
	//or we could just scan through all possible rectangles in the array, leading to O(n^3) efficiency
    
    BufferedReader fin = new BufferedReader(new FileReader("paintbarn.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("paintbarn.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    
    int[][] pfx = new int[201][201];
    int[][] pfx2 = new int[201][201];
    
    for(int i = 0; i < n; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int startX = Integer.parseInt(st.nextToken());
    	int startY = Integer.parseInt(st.nextToken());
    	int endX = Integer.parseInt(st.nextToken());
    	int endY = Integer.parseInt(st.nextToken());
    	
    	pfx[startX][startY] = 1;
    	pfx[endX][endY] = 1;
    	pfx[startX][endY] = -1;
    	pfx[endX][startY] = -1;
    	
    }
    
    for(int i = 1; i < pfx.length; i++) {
    	for(int j = 1; j < pfx.length; j++) {
    		pfx[i][j] += pfx[i - 1][j] + pfx[i][j - 1] - pfx[i - 1][j - 1];
    		pfx2[i][j] += pfx2[i - 1][j] + pfx2[i][j - 1] - pfx2[i - 1][j - 1];
    		
    		if(pfx[i][j] == k - 1) {
    			pfx2[i][j] += 1;
    		}
    		
    		else if(pfx[i][j] == k) {
    			pfx2[i][j] -= 1;
    		}
    		
    	}
    }
    
    for(int i = 0; i < pfx.length; i++) {
    	for(int j = 0; j < pfx.length; j++) {
    		System.out.print(pfx[i][j]);
    	}
    	System.out.println();
    }
    
    System.out.println();
    
    for(int i = 0; i < pfx.length; i++) {
    	for(int j = 0; j < pfx.length; j++) {
    		System.out.print(pfx2[i][j]);
    	}
    	System.out.println();
    }
    
    int maxSum = Integer.MIN_VALUE;
    
    for(int w = 200; w >= 1; w--) {
    	
    	for(int h = 200; h >= 1; h--) {
    		
    		
    		
    	}
    	
    }
    
    fin.close();
    fout.close();
    
	}
}