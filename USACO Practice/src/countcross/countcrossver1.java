/*
ID: andwerp1
LANG: JAVA
TASK: countcross
*/

package countcross;

import java.io.*;
import java.util.*;

public class countcrossver1 {
	public static void main (String [] args) throws IOException {
		
	//for this problem, we need to return how many pairs of cows are isolated from each other, meaning that they have to cross a road to get to the other cow. 
		
	//we can solve this problem by first seeing which groups of cows aren't isolated from each other. 
	//we floodfill one section of the map, seeing which cows we can get to, and put those into a group. Repeat until all the map has been checked.
		
	//then from there, calculating the amount of isolated pairs is just combinatorics. 
	//if you have two groups of 10 cows, then the amount of pairs is 100, since each cow from one group is in a pair with each cow from the other group.
	//with more than two groups, it's a little tricky but what you do is first consider one group. Given three groups with each 5 cows, we can consider 1 group of 5
	//each cow from that group of 5 will be in a pair with all the other 10 cows, so we have 50 pairs so far. Now we can consider one of the other groups.
	//but when we consider one of the other groups, we need to keep in mind that we already factored in the pairs with the group we are looking at and the group
	//that we just did. So we subtract the amount of cows from the first group and then we multiply the amount of cows in the selected group with the remaining cows.
	//this comes out to 75 pairs. 
    
    BufferedReader fin = new BufferedReader(new FileReader("countcross.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("countcross.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    int r = Integer.parseInt(st.nextToken());
    
    int[][] pasture = new int[n * 2][n * 2];
    ArrayList<Integer> groups = new ArrayList<Integer>();
    
    //making the roads
    
    for(int i = 0; i < r; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int ax = (Integer.parseInt(st.nextToken()) - 1) * 2;
    	int ay = (Integer.parseInt(st.nextToken()) - 1) * 2;
    	int bx = (Integer.parseInt(st.nextToken()) - 1) * 2;
    	int by = (Integer.parseInt(st.nextToken()) - 1) * 2;
    	
    	if(bx < ax) {	//-x
    		
    		pasture[ax - 1][ay] = -1;
    		
    		if(ay - 1 >= 0) {
    			pasture[ax - 1][ay - 1] = -1;
    		}
    		
    		if(ay + 1 < pasture.length) {
    			pasture[ax - 1][ay + 1] = -1;
    		}
    		
    	}
    	
    	else if(bx > ax) {	//+x
    		
    		pasture[ax + 1][ay] = -1;
    		
    		if(ay - 1 >= 0) {
    			pasture[ax + 1][ay - 1] = -1;
    		}
    		
    		if(ay + 1 < pasture.length) {
    			pasture[ax + 1][ay + 1] = -1;
    		}
    		
    	}
    	
    	else if(by < ay) {	//-y
    		
    		pasture[ax][ay - 1] = -1;
    		
    		if(ax - 1 >= 0) {
    			pasture[ax - 1][ay - 1] = -1;
    		}
    		
    		if(ax + 1 < pasture.length) {
    			pasture[ax + 1][ay - 1] = -1;
    		}
    		
    	}
    	
    	else if(by > ay) {	//+y
    		
    		pasture[ax][ay + 1] = -1;
    		
    		if(ax - 1 >= 0) {
    			pasture[ax - 1][ay + 1] = -1;
    		}
    		
    		if(ax + 1 < pasture.length) {
    			pasture[ax + 1][ay + 1] = -1;
    		}
    		
    	}
    	
    }
    
    //placing the cows
    
    for(int i = 0; i < k; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int x = (Integer.parseInt(st.nextToken()) - 1) * 2;
    	int y = (Integer.parseInt(st.nextToken()) - 1) * 2;
    	
    	pasture[x][y] = 1;
    	
    }
    
    
    for(int i = 0; i < pasture.length; i++) {
    	for(int j = 0; j < pasture.length; j++) {
    		if(pasture[i][j] == -1) {
    			System.out.print("#");
    		}
    		else if(pasture[i][j] == 0) {
    			System.out.print(".");
    		}
    		else {
    			System.out.print(pasture[i][j]);
    		}
    	}
    	
    	System.out.println();
    }
    
    System.out.println();
    
    //floodfilling the pasture to find the cow groups
    
    for(int i = 0; i < pasture.length; i++) {
    	
    	for(int j = 0; j < pasture.length; j++) {
    		
    		if(pasture[i][j] != -1) {
    			
    			Stack<int[]> toProcess = new Stack<int[]>();
    			toProcess.add(new int[] {i, j});
    			
    			int numCows = 0;
    			
    			if(pasture[i][j] == 1) {
    				numCows++;
    			}
    			
    			pasture[i][j] = -1;
    			
    			while(toProcess.size() != 0) {
    				
    				int[] cur = toProcess.pop();
    				
    				int x = cur[0];
    				int y = cur[1];
    				
    				if(x - 1 >= 0 && pasture[x - 1][y] != -1) {	//-x
    					
    					toProcess.add(new int[] {x - 1, y});
    					
    					if(pasture[x - 1][y] == 1) {
    						numCows++;
    					}
    					
    					pasture[x - 1][y] = -1;
    					
    				}
    				
    				if(x + 1 < pasture.length && pasture[x + 1][y] != -1) {	//+x
    					
    					toProcess.add(new int[] {x + 1, y});
    					
    					if(pasture[x + 1][y] == 1) {
    						numCows++;
    					}
    					
    					pasture[x + 1][y] = -1;
    					
    				}
    				
    				if(y - 1 >= 0 && pasture[x][y - 1] != -1) {	//-y
    					
    					toProcess.add(new int[] {x, y - 1});
    					
    					if(pasture[x][y - 1] == 1) {
    						numCows++;
    					}
    					
    					pasture[x][y - 1] = -1;
    					
    				}
    				
    				if(y + 1 < pasture.length && pasture[x][y + 1] != -1) {	//+y
    					
    					toProcess.add(new int[] {x, y + 1});
    					
    					if(pasture[x][y + 1] == 1) {
    						numCows++;
    					}
    					
    					pasture[x][y + 1] = -1;
    					
    				}
    				
    			}
    			
    			groups.add(numCows);
    			
    			for(int i2 = 0; i2 < pasture.length; i2++) {
    		    	for(int j2 = 0; j2 < pasture.length; j2++) {
    		    		if(pasture[i2][j2] == -1) {
    		    			System.out.print("#");
    		    		}
    		    		else if(pasture[i2][j2] == 0) {
    		    			System.out.print(".");
    		    		}
    		    		else {
    		    			System.out.print(pasture[i2][j2]);
    		    		}
    		    	}
    		    	
    		    	System.out.println();
    		    	
    		    }
    			
    			System.out.println("cows detected: " + numCows);
    			
    		}
    		
    	}
    	
    }
    
    System.out.println(groups);
    
    //calculating the number of pairs based on the groups
    
    int sum = 0;
    int output = 0;
    
    for(int i = 0; i < groups.size(); i++) {
    	
    	output += sum * groups.get(i);
    	sum += groups.get(i);
    	
    }
    
    System.out.println(output);
    
    fout.println(output);
    
    fin.close();
    fout.close();
    
	}
}