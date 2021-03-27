/*
ID: andwerp1
LANG: JAVA
TASK: rectangularpasturever1
*/

//package rectangularpasture;

import java.io.*;
import java.util.*;

public class rectangularpasture {
	public static void main (String [] args) throws IOException {
		
	//we can do this in O(n^2)
		
	//we have to iterate once from left to right all the cows. 
		
	//for each cow, we try to make rectangles with all other cows that are right of the pointer cow. Rectangles with the ith cow at the left side and the jth cow at the right side.
	//since all x and y coordinates are unique, we won't ever run into a situation where there are two cows on one x-axis.
	
	//for every jth cow, the amount of rectangles goes up for every cow that is within the x constraint, but above the top constraining cow or below the bottom constraining cow.
	//1 (for the jth cow) + number of extra cows.
		
	//to count the number of extra cows, we can just take the prefix sums of the two ranges.
	//we will have to do two prefix sums for each cow, summing up the amount of cows that are above and below the target cow. Each index position will be for one cow.
	//since all y coordinates are unique, we won't have to worry about cows being on the same y as the target cow.
		
	//the answer is the sum of all the rectangles we count. + 1 for the empty subset
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    
    int[][] cows = new int[n][2];
    int[][] pfx = new int [n][n + 1];	//the pfx sum array will save the amount of cows that are above the target cow (greater y value);
    int[][] pfxLess = new int[n][n + 1];
    
    //we can retrieve the amount of cows below the target cow by getting the size of the range and subtracting the amount of cows that are above the target cow
    //this is possible because cows are either above or below, never on the same y
    
    for(int i = 0; i < n; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int x = Integer.parseInt(st.nextToken());
    	int y = Integer.parseInt(st.nextToken());
    	
    	cows[i][0] = x;
    	cows[i][1] = y;
    
    }
    
    Arrays.sort(cows, (a, b) -> a[0] - b[0]);
    
    for(int i = 0; i < n; i++) {
    	for(int j = 1; j < n + 1; j++) {
    		
    		if(cows[i][1] < cows[j - 1][1]) {
    			pfx[i][j] += 1;
    		}
    		
    		if(cows[i][1] > cows[j - 1][1]) {
    			pfxLess[i][j] += 1;
    		}
    		
    		pfx[i][j] += pfx[i][j - 1];
    		pfxLess[i][j] += pfxLess[i][j - 1];
    	}
    }
    //System.out.println();
    for(int[] i : cows) {
    	for(int j : i) {
    		//System.out.print(j + " ");
    	}
    	//System.out.println();
    }
    
    //System.out.println();
    
    for(int[] i : pfx) {
    	//System.out.print("cow " + i + ":");
    	for(int j : i) {
    		//System.out.print(j + " ");
    	}
    	//System.out.println();
    }
    
    //System.out.println();
    
    for(int[] i : pfxLess) {
    	//System.out.print("cow " + i + ":");
    	for(int j : i) {
    		//System.out.print(j + " ");
    	}
    	//System.out.println();
    }
    
    long count = 1 + n;	//starting with 1 to account for the empty one
    
    for(int i = 0; i < n; i++) {
    	
    	for(int j = i + 1; j < n; j++) {
    		
    		count++;	//one for each set of cow
    		
    		int above = pfx[i][j] - pfx[i][i];
    		int below = (j - i) - (pfx[j][j + 1] - pfx[j][i + 1]);
    		
    		int greater = 0;
    		int less = 0;
    		
    		if(cows[i][1] > cows[j][1]) {
    			
    			greater = pfx[i][j + 1] - pfx[i][i + 1];
    			less = pfxLess[j][j + 1] - pfxLess[j][i + 1];
    			//greater += 1;
    			//System.out.println("anchor cow greater " + pfxLess[j][j + 1] + " " + pfxLess[j][i + 1] + " " + less);
    			
    		}
    		
    		else {
    			
    			greater = pfx[j][j + 1] - pfx[j][i + 1];
    			less = pfxLess[i][j + 1] - pfxLess[i][i + 1];
    			//less += 1;
    			//System.out.println("target cow greater");
    			
    		}
    		
    		//System.out.println("cows: " + i + " " + j + " greater: " + greater + " less: " + less);
    		
    		count += greater + less + (greater * less);
    		
    	}
    	
    }
    
    StringBuilder fout = new StringBuilder();
    fout.append(count).append("\n");
    System.out.print(fout);
    fin.close();
    
	}
}