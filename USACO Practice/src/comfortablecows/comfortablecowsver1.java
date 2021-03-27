/*
ID: andwerp1
LANG: JAVA
TASK: comfortablecows
*/

package comfortablecows;

import java.io.*;
import java.util.*;

public class comfortablecowsver1 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    
    int[][] cows = new int[2000][2000];
    
    int numTemp = 0;
    
    StringBuilder fout = new StringBuilder();
    
    for(int i = 0; i < n; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int x = Integer.parseInt(st.nextToken()) + 1000;
    	int y = Integer.parseInt(st.nextToken()) + 1000;
    	
    	if(cows[x][y] == 1) {
    		numTemp--;
    	}
    	
    	cows[x][y] = 2;
    	
    	Stack<int[]> toProcess = new Stack<int[]>();
    	toProcess.add(new int[] {x, y});
    	
    	while(toProcess.size() != 0) {
    		
    		int[] cur = toProcess.pop();
    		
    		int adj = 0;
    		
    		int xCur = cur[0];
    		int yCur = cur[1];
    		
    		int xAdd = 0;
    		int yAdd = 0;
    		
    		xCur -= 1;
    		
    		if(xCur >= 0 && cows[xCur][yCur] > 0) {
    			adj++;
    			//toProcess.add(new int[] {xCur, yCur});
    		}
    		
    		xCur += 2;
    		
    		if(xCur < cows.length && cows[xCur][yCur] > 0) {
    			adj++;
    			//toProcess.add(new int[] {xCur, yCur});
    		}
    		
    		xCur -= 1;
    		yCur -= 1;
    		
    		if(yCur >= 0 && cows[xCur][yCur] > 0) {
    			adj++;
    			//toProcess.add(new int[] {xCur, yCur});
    		}
    		
    		yCur += 2;
    		
    		if(yCur < cows.length && cows[xCur][yCur] > 0) {
    			adj++;
    			//toProcess.add(new int[] {xCur, yCur});
    		}
    		
    		yCur -= 1;
    		
    		if(adj == 3) {
    			
    			numTemp ++;
    			
    			xCur -= 1;
        		
        		if(xCur >= 0 && cows[xCur][yCur] == 0) {
        			cows[xCur][yCur] = 1;
        			toProcess.add(new int[] {xCur, yCur});
        			xAdd = xCur;
        			yAdd = yCur;
        		}
        		
        		xCur += 2;
        		
        		if(xCur < cows.length && cows[xCur][yCur] == 0) {
        			cows[xCur][yCur] = 1;
        			toProcess.add(new int[] {xCur, yCur});
        			xAdd = xCur;
        			yAdd = yCur;
        		}
        		
        		xCur -= 1;
        		yCur -= 1;
        		
        		if(yCur >= 0 && cows[xCur][yCur] == 0) {
        			cows[xCur][yCur] = 1;
        			toProcess.add(new int[] {xCur, yCur});
        			xAdd = xCur;
        			yAdd = yCur;
        		}
        		
        		yCur += 2;
        		
        		if(yCur < cows.length && cows[xCur][yCur] == 0) {
        			cows[xCur][yCur] = 1;
        			toProcess.add(new int[] {xCur, yCur});
        			xAdd = xCur;
        			yAdd = yCur;
        		}
        		
        		yCur -= 1;
        		
        		xAdd -= 1;
        		
        		if(xAdd >= 0 && cows[xAdd][yAdd] != 0) {
        			toProcess.add(new int[] {xAdd, yAdd});
        		}
        		
        		xAdd += 2;
        		
        		if(xAdd < cows.length && cows[xAdd][yAdd] != 0) {
        			toProcess.add(new int[] {xAdd, yAdd});
        		}
        		
        		xAdd -= 1;
        		yAdd -= 1;
        		
        		if(yAdd >= 0 && cows[xAdd][yAdd] != 0) {
        			toProcess.add(new int[] {xAdd, yAdd});
        		}
        		
        		yAdd += 2;
        		
        		if(yAdd < cows.length && cows[xAdd][yAdd] != 0) {
        			toProcess.add(new int[] {xAdd, yAdd});
        		}
    			
    		}
    		
    	}
    	
    	fout.append(numTemp).append("\n");
    	
    }
    
    //StringBuilder fout = new StringBuilder();
    
    System.out.print(fout);
    fin.close();
    
	}
}

