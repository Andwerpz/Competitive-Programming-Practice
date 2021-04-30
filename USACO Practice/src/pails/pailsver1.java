/*
ID: andwerp1
LANG: JAVA
TASK: pails
*/

package pails;

import java.io.*;
import java.util.*;

class pailsver1 {
	public static void main (String [] args) throws IOException {
		
	//we can represent the possible moves as an 2d grid, which we can floodfill through. i think...	no!
	//use dp 0-1 knapsack
    
    BufferedReader fin = new BufferedReader(new FileReader("pails.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("pails.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int x = Integer.parseInt(st.nextToken());
    int y = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    boolean[][] dp = new boolean[x + 1][y + 1];	//whether or not you can achieve x bucket with i gallons and y bucket with j gallons
    dp[0][0] = true;	//empty configuration
    while(k -- > 0) {	//going through the moves
    	boolean[][] cur = new boolean[x + 1][y + 1];
    	for(int i = 0; i <= x; i++) {
    		for(int j = 0; j <= y; j++) {
    			cur[i][j] = dp[i][j];
    		}
    	}
    	for(int i = 0; i <= x; i++) {
    		for(int j = 0; j <= y; j++) {
    			if(cur[i][j]) {	//if achievable
    				dp[x][j] = true;	//fill bucket x
    				dp[i][y] = true;	//fill bucket y
    				dp[0][j] = true;	//empty bucket x
    				dp[i][0] = true;	//empty bucket y
    				int nextX = Math.max(0, i - (y - j));
    				int nextY = Math.min(j + i, y);//pour bucket x into bucket y
    				//System.out.println(nextX + " " + nextY);
    				dp[nextX][nextY] = true;
    				nextX = Math.min(j + i, x);
    				nextY = Math.max(0, j - (x - i));
    				dp[nextX][nextY] = true;	//pour bucket y into x
    				//System.out.println(nextX + " " + nextY + " " + dp[nextX][nextY]);
    			}
    		}
    	}
    }
    int ans = Integer.MAX_VALUE;
    int[] ansArr = new int[2];
    for(int i = 0; i <= x; i++) {
    	for(int j = 0; j <= y; j++) {
    		if(dp[i][j]) {
    			ans = Math.min(ans, Math.abs(m - (i + j)));
    			ansArr[0] = i;
    			ansArr[1] = j;
    			//System.out.println(i + " " + j);
    		}
    		//System.out.print(dp[i][j]? "#" : ".");
    	}
    	//System.out.println();
    }
    //System.out.println(ans + " " + ansArr[0] + " " + ansArr[1]);
    fout.println(ans);
    
    fin.close();
    fout.close();
    
	}
}