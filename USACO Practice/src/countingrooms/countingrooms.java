
//package countingrooms;

import java.io.*;
import java.util.*;

public class countingrooms {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int w = Integer.parseInt(st.nextToken());
    int h = Integer.parseInt(st.nextToken());
    
    int[][] rooms = new int[w][h];
    
    for(int i = 0; i < w; i++) {
    	String in = fin.readLine();
    	//System.out.println(in);
    	for(int j = 0; j < h; j++) {
    		rooms[i][j] = in.charAt(j) == '#'? 1 : 0;
    	}
    }
    
    boolean[][] v = new boolean[w][h];
    
    int[] dx = new int[] {1, -1, 0, 0};
    int[] dy = new int[] {0, 0, 1, -1};
    
    int numRooms = 0;
    
    for(int i = 0; i < rooms.length; i++) {
    	for(int j = 0; j < rooms[i].length; j++) {
    		
    		if(rooms[i][j] == 0 && !v[i][j]) {
    			
    			
    			Stack<int[]> s = new Stack<int[]>();
    			s.add(new int[] {i, j});
    			
    			v[i][j] = true;
    			numRooms ++;
    			while(s.size() != 0) {
    				
    				//System.out.println("infinite loop");
    				
    				
    				int[] cur = s.pop();
    				
    				
    				
    				for(int k = 0; k < 4; k++) {
    					int x = cur[0] + dx[k];
    					int y = cur[1] + dy[k];
    					if(x >= 0 && x < w && y >= 0 && y < h && rooms[x][y] == 0 && !v[x][y]) {
    						
    						s.add(new int[] {x, y});
    						v[x][y] = true;
    						//numRooms++;
    						
    					}
    				}
    				
    			}
    			
    			
    			
    		}
    		
    	}
    }
    
    
    
   
    
    System.out.println(numRooms);
    fin.close();
    
	}
}