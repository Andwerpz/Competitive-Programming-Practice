/*
ID: andwerp1
LANG: JAVA
TASK: mooyomooyo
*/

//package mooyomooyo;

import java.io.*;
import java.util.*;

public class mooyomooyo {
	public static void main (String [] args) throws IOException {
		
	//for this solution, all we need to do is floodfill the board, and then once floodfill is done, we can update the board by dropping everything to the bottom. 
		
	//when we do floodfill, we first need to check if there are more than 3 connected components before we start removing them.
	//we do this by first floodfilling and counting components, putting visited components into a hashmap. 
	//once we count to the threshold, we start a second floodfill on one of the components, this time removing them by overwriting their values with 0
		
	//once all floodfill is done, we can drop all the pieces down by removing the leading 0s in the arrays.
	
	//to check for the final state, we just need to check if we don't remove any pieces
    
    BufferedReader fin = new BufferedReader(new FileReader("mooyomooyo.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("mooyomooyo.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    
    ArrayList<ArrayList<Integer>> board = new ArrayList<ArrayList<Integer>>();
    int[][] temp = new int[n][10];
    
    for(int i = 0; i < n; i++) {
    	
    	String input = fin.readLine();
    	
    	for(int j = 0; j < 10; j++) {
    		
    		temp[i][j] = Integer.parseInt(input.substring(j, j + 1));
    		
    	}
    	
    }
    
    for(int i = 0; i < 10; i++) {
    	board.add(new ArrayList<Integer>());
    }
    
    for(int i = temp.length - 1; i >= 0; i--) {
    	
    	for(int j = 0; j < temp[i].length; j++) {
    		
    		if(temp[i][j] != 0) {
    			board.get(j).add(temp[i][j]);
    		}
    		
    	}
    	
    }
    
    
    
    
    boolean noChanges = false;
    
    while(!noChanges) {
    	
    	//System.out.println("there are changes");
    	
    	noChanges = true;
    	
    	for(int i = 0; i < board.size(); i++) {
    		
    		for(int j = 0; j < board.get(i).size(); j++) {
    			
    			if(board.get(i).get(j) != 0) {
    				
    				//first floodfill: determining whether or not to remove
    				
    				boolean remove = false;
    				
    				int curColor = board.get(i).get(j);
    				
    				Stack<int[]> toProcess = new Stack<int[]>();
    				toProcess.add(new int[] {i, j});
    				
    				HashSet<ArrayList<Integer>> visited = new HashSet<ArrayList<Integer>>();
    				ArrayList<Integer> first = new ArrayList<Integer>();
    				first.add(i);
    				first.add(j);
    				visited.add(first);
    				
    				while(toProcess.size() != 0) {
    					
    					//System.out.println("first floodfill, num remaining: " + toProcess.size());
    					
    					int[] cur = toProcess.pop();
    					
    					int x = cur[0];
    					int y = cur[1];
    					
    					ArrayList<Integer> negX = new ArrayList<Integer>();
    					ArrayList<Integer> posX = new ArrayList<Integer>();
    					ArrayList<Integer> negY = new ArrayList<Integer>();
    					ArrayList<Integer> posY = new ArrayList<Integer>();
    					
    					negX.add(x - 1);
    					negX.add(y);
    					
    					posX.add(x + 1);
    					posX.add(y);
    					
    					negY.add(x);
    					negY.add(y - 1);
    					
    					posY.add(x);
    					posY.add(y + 1);
    					
    					if(x - 1 >= 0 && board.get(x - 1).size() > y && board.get(x - 1).get(y) == curColor && !visited.contains(negX)) {	//-x
    						
    						toProcess.add(new int[] {x - 1, y});
    						visited.add(negX);
    						
    					}
    					
    					if(x + 1 < 10 && board.get(x + 1).size() > y && board.get(x + 1).get(y) == curColor && !visited.contains(posX)) {	//+x
    						
    						toProcess.add(new int[] {x + 1, y});
    						visited.add(posX);
    						
    					}
    					
    					if(y - 1 >= 0 && board.get(x).get(y - 1) == curColor && !visited.contains(negY)) {	//-y
    						
    						toProcess.add(new int[] {x, y - 1});
    						visited.add(negY);
    						
    					}
    					
    					if(y + 1 < board.get(x).size() && board.get(x).get(y + 1) == curColor && !visited.contains(posY)) {	//+y
    						
    						toProcess.add(new int[] {x, y + 1});
    						visited.add(posY);
    						
    					}
    					
    					if(visited.size() >= k) {
    						
    						//System.out.println(visited.size());
    						
    						remove = true;
    						break;
    						
    					}
    					
    				}
    				
    				//second floodfill: removal if it is determined that removal is valid
    				
    				if(remove) {
    					
    					//System.out.println("removing color " + curColor);
    					
    					noChanges = false;
    					
    					toProcess = new Stack<int[]>();
        				toProcess.add(new int[] {i, j});
        				
        				while(toProcess.size() != 0) {
        					
        					int[] cur = toProcess.pop();
        					
        					int x = cur[0];
        					int y = cur[1];
        					
        					board.get(x).set(y, 0);
        					
        					if(x - 1 >= 0 && board.get(x - 1).size() > y && board.get(x - 1).get(y) == curColor) {	//-x
        						
        						int[] next = new int[] {x - 1, y};
        						toProcess.add(next);
        						
        					}
        					
        					if(x + 1 < 10 && board.get(x + 1).size() > y && board.get(x + 1).get(y) == curColor) {	//+x
        						
        						int[] next = new int[] {x + 1, y};
        						toProcess.add(next);
        						
        					}
        					
        					if(y - 1 >= 0 && board.get(x).get(y - 1) == curColor) {	//-y
        						
        						int[] next = new int[] {x, y - 1};
        						toProcess.add(next);
        						
        					}
        					
        					if(y + 1 < board.get(x).size() && board.get(x).get(y + 1) == curColor) {	//+y
        						
        						int[] next = new int[] {x, y + 1};
        						toProcess.add(next);
        						
        					}
        					
        				}
    					
    				}
    				
    			}
    			
    		}
    		
    	}
    	
    	//third phase: once everything is done, check to see if there were any changes; if yes then get rid of all the zeroes, moving everything down.
    	
    	if(!noChanges) {
    		
    		for(int i = 0; i < board.size(); i++) {
    			
    			for(int j = 0; j < board.get(i).size(); j++) {
    				
    				if(board.get(i).get(j) == 0) {
    					
    					board.get(i).remove(j);
    					j--;
    					
    				}
    				
    			}
    			
    		}
    		
    	}
    	
    	
    	
    	
    }
    
    
    temp = new int[n][10];
    
    for(int i = 0; i < board.size(); i++) {
    	
    	for(int j = 0; j < board.get(i).size(); j++) {
    		
    		temp[j][i] = board.get(i).get(j);
    		
    	}
    	
    }
    
    for(int i = temp.length - 1; i >= 0; i--) {
    	
    	for(int j = 0; j < temp[i].length; j++) {
    		
    		fout.print(temp[i][j]);
    		
    	}
    	
    	fout.println();
    	
    }
    
    fin.close();
    fout.close();
    
	}
}