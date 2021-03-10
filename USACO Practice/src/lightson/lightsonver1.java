/*
ID: andwerp1
LANG: JAVA
TASK: lightson
*/

package lightson;

import java.io.*;
import java.util.*;

class lightsonver1 {
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
    	
    	System.out.print(start[0] + " " + start[1] + " ");
    	System.out.println(end[0] + " " + end[1]);
    	
    }
    
    
    Stack<int[]> toProcess = new Stack<int[]>();
    boolean[][] visited = new boolean[n][n];
    boolean[][] isVisitable = new boolean[n][n];
    
    int amountVisited = 1;
    int numVisitable = 0;
    
    boolean noNewVisitable = false;
    
    toProcess.add(new int[] {0, 0});
    visited[0][0] = true;
    isVisitable[0][0] = true;
    
    while(toProcess.size() != 0 || !noNewVisitable) {
    	
    	noNewVisitable = true;
    	
    	int[] curRoom = toProcess.pop();
    	
    	ArrayList<int[]> conn = connections.get(curRoom[0]).get(curRoom[1]);
    	
    	System.out.println("\n");
    	
    	System.out.println("processing room: " + curRoom[0] + " " + curRoom[1]);
    	
    	System.out.println(conn.size() + " switches in room " + curRoom[0] + " " + curRoom[1]);
    	
    	for(int i = 0; i < conn.size(); i++) {
    		
    		int[] pointer = conn.get(i);
    		
    		System.out.println("looking at room: " + pointer[0] + " " + pointer[1]);
    		
    		if(!visited[pointer[0]][pointer[1]]) {
    			
    			System.out.println("haven't visited this room");
    			
    			toProcess.add(pointer);
    			visited[pointer[0]][pointer[1]] = true;
    			amountVisited++;
    			
    		}
    		
    	}
    	
    	if(toProcess.size() == 0) {
    		
    		System.out.println();
    		
    		System.out.println("starting floodfill");
    		
    		numVisitable = 1;
    		
    		Stack<int[]> stack = new Stack<int[]>();
    		boolean[][] stackVisited = new boolean[n][n];
    		
    		stack.add(new int[] {0, 0});
    		stackVisited[0][0] = true;
    		
    		while(stack.size() != 0) {
    			
    			int[] curLoc = stack.pop();
    			
    			System.out.println("curloc: " + curLoc[0] + " " + curLoc[1]);
    			
    			if(curLoc[0] != 0 && visited[curLoc[0] - 1][curLoc[1]] == true && !stackVisited[curLoc[0] - 1][curLoc[1]] && !isVisitable[curLoc[0] - 1][curLoc[1]]) {	//-x
    				
    				isVisitable[curLoc[0] - 1][curLoc[1]] = true;
    				stack.add(new int[] {curLoc[0] - 1, curLoc[1]});
    				stackVisited[curLoc[0] - 1][curLoc[1]] = true;
    				toProcess.add(new int[] {curLoc[0] - 1, curLoc[1]});
    				numVisitable++;
    				noNewVisitable = false;
    				
    			}
    			
				if(curLoc[0] != n - 1 && visited[curLoc[0] + 1][curLoc[1]] == true && !stackVisited[curLoc[0] + 1][curLoc[1]] && !isVisitable[curLoc[0] + 1][curLoc[1]]) {	//+x
				    				
					isVisitable[curLoc[0] + 1][curLoc[1]] = true;
					stack.add(new int[] {curLoc[0] + 1, curLoc[1]});
					stackVisited[curLoc[0] + 1][curLoc[1]] = true;
					toProcess.add(new int[] {curLoc[0] + 1, curLoc[1]});
					numVisitable++;
					noNewVisitable = false;
					
				}

				if(curLoc[1] != 0 && visited[curLoc[0]][curLoc[1] - 1] == true && !stackVisited[curLoc[0]][curLoc[1] - 1] && !isVisitable[curLoc[0]][curLoc[1] - 1]) {	//-y
					
					isVisitable[curLoc[0]][curLoc[1] - 1] = true;
					stack.add(new int[] {curLoc[0], curLoc[1] - 1});
					stackVisited[curLoc[0]][curLoc[1] - 1] = true;
					toProcess.add(new int[] {curLoc[0], curLoc[1] - 1});
					numVisitable++;
					noNewVisitable = false;
					
				}
				
				System.out.println(curLoc[1] != n - 1 && visited[curLoc[0]][curLoc[1] + 1] == true && !stackVisited[curLoc[0]][curLoc[1] + 1]);
				
				if(curLoc[1] != n - 1 && visited[curLoc[0]][curLoc[1] + 1] == true && !stackVisited[curLoc[0]][curLoc[1] + 1] && !isVisitable[curLoc[0]][curLoc[1] + 1]) {	//+y
					
					isVisitable[curLoc[0]][curLoc[1] + 1] = true;
					stack.add(new int[] {curLoc[0], curLoc[1] + 1});
					stackVisited[curLoc[0]][curLoc[1] + 1] = true;
					toProcess.add(new int[] {curLoc[0], curLoc[1] + 1});
					numVisitable++;
					noNewVisitable = false;
					System.out.println("visitable now");
					
				}
    			
    		}
    		
    		System.out.println("num Visitable: " + numVisitable);
    		
    		
    	}
    	
    }
    
    fout.println(amountVisited);
    
    fin.close();
    fout.close();
    
	}
}