/*
ID: andwerp1
LANG: JAVA
TASK: lightson
*/

//package lightson;

import java.io.*;
import java.util.*;

class lightson {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("lightson.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("lightson.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    
    ArrayList<ArrayList<ArrayList<int[]>>> connections = new ArrayList<ArrayList<ArrayList<int[]>>>();
    
    for(int i = 0; i < n; i++) {
    	connections.add(new ArrayList<ArrayList<int[]>>());
    	for(int j = 0; j < n; j++) {
    		
    		connections.get(i).add(new ArrayList<int[]>());
    		
    	}
    }
    
    for(int i = 0; i < m; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int[] start = new int[] {Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()) - 1};
    	int[] end = new int[] {Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()) - 1};
    	
    	connections.get(start[0]).get(start[1]).add(end);
    	
    	//System.out.print(start[0] + " " + start[1] + " ");
    	//System.out.println(end[0] + " " + end[1]);
    	
    }
    
    
    boolean[][] isLight = new boolean[n][n];
    isLight[0][0] = true;
    
    boolean[][] visited = new boolean[n][n];
    visited[0][0] = true;
    
    Stack<int[]> toProcess = new Stack<int[]>();
    toProcess.add(new int[] {0, 0});
    
    int numVisited = 1;
    
    int counter = 0;
    
    while(toProcess.size() != 0) {
    	
    	counter++;
    	
    	//System.out.println(counter);
    	
//    	for(int i = 0; i < n; i++) {
//        	
//        	for(int j = 0; j < n; j++) {
//        		
//        		if(isLight[i][j]) {
//        			//System.out.print("# ");
//        		}
//        		
//        		else {
//        			//System.out.print(". ");
//        		}
//        		
//        	}
//        	
//        	//System.out.println();
//        	
//        }
    	
    	int[] curLoc = toProcess.pop();
    	
    	//System.out.println("processing: " + curLoc[0] + " " + curLoc[1]);
    	
    	ArrayList<int[]> conn = connections.get(curLoc[0]).get(curLoc[1]);
    	
    	for(int i = 0; i < conn.size(); i++) {
    		
    		int[] temp = conn.get(i);
    		isLight[temp[0]][temp[1]] = true;
    		
    		//System.out.println(temp[0] + " " + temp[1]);
    		
    		//checking if the newly turned on room is connected to any visited rooms
    		
    		//System.out.println("Visited Room to left? " + (temp[1] - 1 > 0 && visited[temp[0]][temp[1] - 1]));
    		//System.out.println("Visited Room to the right? " + (temp[1] + 1 < n && visited[temp[0]][temp[1] + 1]));
    		
    		if(
    				((temp[0] - 1 > -1 && visited[temp[0] - 1][temp[1]]) || 
    				(temp[0] + 1 < n && visited[temp[0] + 1][temp[1]]) ||
    				(temp[1] - 1 > -1 && visited[temp[0]][temp[1] - 1]) ||
    				(temp[1] + 1 < n && visited[temp[0]][temp[1] + 1])) &&
    				!visited[temp[0]][temp[1]]){	
    			
    			//System.out.println("is connected to light: " + temp[0] + " " + temp[1]);
    			
    			toProcess.add(temp);
    			visited[temp[0]][temp[1]] = true;
    			
    			numVisited++;
    			
    		}
    		
    	}
    	
    	if(curLoc[0] - 1 > -1 && isLight[curLoc[0] - 1][curLoc[1]] && !visited[curLoc[0] - 1][curLoc[1]]) {	//-x
    		
    		toProcess.add(new int[] {curLoc[0] - 1, curLoc[1]});
    		visited[curLoc[0] - 1][curLoc[1]] = true;
    		
    		numVisited++;
    		
    	}
    	
    	if(curLoc[0] + 1 < n && isLight[curLoc[0] + 1][curLoc[1]] && !visited[curLoc[0] + 1][curLoc[1]]) {	//+x
    		
    		toProcess.add(new int[] {curLoc[0] + 1, curLoc[1]});
    		visited[curLoc[0] + 1][curLoc[1]] = true;
    		
    		numVisited++;
    		
    	}
    	
    	if(curLoc[1] - 1 > -1 && isLight[curLoc[0]][curLoc[1] - 1] && !visited[curLoc[0]][curLoc[1] - 1]) {	//-y
    		
    		toProcess.add(new int[] {curLoc[0], curLoc[1] - 1});
    		visited[curLoc[0]][curLoc[1] - 1] = true;
    		
    		numVisited++;
    		
    	}
    	
    	if(curLoc[1] + 1 < n && isLight[curLoc[0]][curLoc[1] + 1] && !visited[curLoc[0]][curLoc[1] + 1]) {	//+y
    		
    		toProcess.add(new int[] {curLoc[0], curLoc[1] + 1});
    		visited[curLoc[0]][curLoc[1] + 1] = true;
    		
    		numVisited++;
    		
    	}
    	
    	//System.out.println("size of stack: " + toProcess.size());
    	//System.out.println("numVisited: " + numVisited);
    	
    }
    
    fout.println(numVisited);
    
    fin.close();
    fout.close();
    
	}
}