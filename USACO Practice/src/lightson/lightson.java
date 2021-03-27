/*
ID: andwerp1
LANG: JAVA
TASK: lightson
*/

//package lightson;

import java.io.*;
import java.util.*;

public class lightson {
	public static void main (String [] args) throws IOException {
		
	//this solution will ignore all the fancy time saving techniques. Whenever we reach a point where we can't activate more rooms, we
	//are just going to restart the floodfill. If we can get more rooms, then good, but if we can't then we count the amount of rooms that we already have
	//and we return that 
		
	//im dumb lol, we need to return the amount of rooms illuminated, not the amount of rooms that bessie can walk in
    
    BufferedReader fin = new BufferedReader(new FileReader("lightson.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("lightson.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    
    boolean[][] rooms = new boolean[n][n];
    boolean[][] switchFlipped = new boolean[n][n];
    ArrayList<ArrayList<ArrayList<int[]>>> switches = new ArrayList<ArrayList<ArrayList<int[]>>>();
    
    rooms[0][0] = true;
    
    for(int i = 0; i < n; i++) {
    	switches.add(new ArrayList<ArrayList<int[]>>());
    	for(int j = 0; j < n; j++) {
    		switches.get(i).add(new ArrayList<int[]>());
    	}
    }
    
    for(int i = 0; i < m; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int x = Integer.parseInt(st.nextToken()) - 1;
    	int y = Integer.parseInt(st.nextToken()) - 1;
    	
    	int[] coords = new int[] {Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()) - 1};
    	
    	switches.get(x).get(y).add(coords);
    	
    }
    
    
    boolean done = false;
    
    while(!done) {
    	
    	done = true;
    	
    	Stack<int[]> toProcess = new Stack<int[]>();
    	toProcess.add(new int[] {0, 0});
    	
    	HashSet<ArrayList<Integer>> visited = new HashSet<ArrayList<Integer>>();
    	visited.add(new ArrayList<Integer>(Arrays.asList(0, 0)));
    	
    	while(toProcess.size() != 0) {
    		
    		int[] cur = toProcess.pop();
    		
    		int x = cur[0];
    		int y = cur[1];
    		
    		if(!switchFlipped[x][y]) {
    			
    			for(int i = 0; i < switches.get(x).get(y).size(); i++) {
    				
    				int[] s = switches.get(x).get(y).get(i);
    				rooms[s[0]][s[1]] = true;
    				
    			}
    			
    			switchFlipped[x][y] = true;
    			done = false;
    			
    		}
    		
    		x -= 1;
    		
    		if(x >= 0 && !visited.contains(new ArrayList<Integer>(Arrays.asList(x, y))) && rooms[x][y] == true) {
    			
    			toProcess.add(new int[] {x, y});
    			visited.add(new ArrayList<Integer>(Arrays.asList(x, y)));
    			
    		}
    		
    		x += 2;
    		
    		if(x < rooms.length && !visited.contains(new ArrayList<Integer>(Arrays.asList(x, y))) && rooms[x][y] == true) {
    			
    			toProcess.add(new int[] {x, y});
    			visited.add(new ArrayList<Integer>(Arrays.asList(x, y)));
    			
    		}
    		
    		x -= 1;
    		y -= 1;

			if(y >= 0 && !visited.contains(new ArrayList<Integer>(Arrays.asList(x, y))) && rooms[x][y] == true) {
				
				toProcess.add(new int[] {x, y});
				visited.add(new ArrayList<Integer>(Arrays.asList(x, y)));
				
			}
			
			y += 2;
			
			if(y < rooms.length && !visited.contains(new ArrayList<Integer>(Arrays.asList(x, y))) && rooms[x][y] == true) {
				
				toProcess.add(new int[] {x, y});
				visited.add(new ArrayList<Integer>(Arrays.asList(x, y)));
				
			}
    		
    	}
    	
    	//System.out.println(visited.size());
    	
    }
    
    int numIlluminated = 0;
    
    for(boolean[] i : rooms) {
    	for(boolean j : i) {
    		if(j) {
    			numIlluminated++;
    		}
    	}
    }
    
    fout.println(numIlluminated);
    fin.close();
    fout.close();
    
	}
}