/*
ID: andwerp2
LANG: JAVA
TASK: perimeter
*/

package perimeter;

import java.io.*;
import java.util.*;

class perimeterver1 {
	public static void main (String [] args) throws IOException {
		
	
    
    BufferedReader fin = new BufferedReader(new FileReader("perimeter.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("perimeter.out")));
   
    int n = Integer.parseInt(fin.readLine());
    
    String[][] iceCream = new String[n][n];
    int[][] visited = new int[n][n];
    
    for(int i = 0; i < n; i++) {
    	
    	String input = fin.readLine();
    	
    	for(int j = 0; j < n; j++) {
    		
    		iceCream[i][j] = input.charAt(j) + "";
    		
    		System.out.print(iceCream[i][j]);
    		
    	}
    	
    	System.out.println();
    	
    }
    
    int maxArea = 0;
    int maxPerimeter = 0;
    
    for(int i = 0; i < n; i++) {
    	
    	for(int j = 0; j < n; j++) {
    		
    		if(iceCream[i][j].equals("#") && visited[i][j] != 1) {
    			
    			int curArea = 0;
    			int curPerimeter = 0;
    			
    			ArrayList<int[]> toProcess = new ArrayList<int[]>();
    			
    			toProcess.add(new int[] {i, j});
    			visited[i][j] = 1;
    			
    			while(toProcess.size() != 0) {
    				
    				ArrayList<int[]> nextToProcess = new ArrayList<int[]>();
    				
    				for(int k = 0; k < toProcess.size(); k++) {
    					
    					int curI = toProcess.get(k)[0];
    					int curJ = toProcess.get(k)[1];
    					
    					curArea ++;
    					
    					if(curI + 1 == n || iceCream[curI + 1][curJ].equals(".")) {	//down
    						
    						curPerimeter ++;
    						
    					}
    					
    					else if(visited[curI + 1][curJ] != 1){
    						nextToProcess.add(new int[] {curI + 1, curJ});
    						visited[curI + 1][curJ] = 1;
    					}
    					
    					
    					if(curI == 0 || iceCream[curI - 1][curJ].equals(".")) {	//up
    						
    						curPerimeter ++;
    						
    					}
    					
    					else if(visited[curI - 1][curJ] != 1){
    						nextToProcess.add(new int[] {curI - 1, curJ});
    						visited[curI - 1][curJ] = 1;
    					}
    					
    					if(curJ + 1 == n || iceCream[curI][curJ + 1].equals(".")) {	//right
    						
    						curPerimeter ++;
    						
    					}
    					
    					else if(visited[curI][curJ + 1] != 1){
    						nextToProcess.add(new int[] {curI, curJ + 1});
    						visited[curI][curJ + 1] = 1;
    					}
    					
    					if(curJ == 0 || iceCream[curI][curJ - 1].equals(".")) {	//left
    						
    						curPerimeter ++;
    						
    					}
    					
    					else if(visited[curI][curJ - 1] != 1){
    						nextToProcess.add(new int[] {curI, curJ - 1});
    						visited[curI][curJ - 1] = 1;
    					}
    					
    					
    					
    					
    				}
    				
    				toProcess = nextToProcess;
    				
    			}
    			
    			
    			if(maxArea < curArea) {
    				maxArea = curArea;
    				maxPerimeter = curPerimeter;
    			}
    			
    			else if(curArea == maxArea && maxPerimeter > curPerimeter) {
    				maxArea = curArea;
    				maxPerimeter = curPerimeter;
    			}
    			
    		}
    		
    	}
    	
    }
    
    fout.println(maxArea + " " + maxPerimeter);
    
    
    fin.close();
    fout.close();
    
	}
}