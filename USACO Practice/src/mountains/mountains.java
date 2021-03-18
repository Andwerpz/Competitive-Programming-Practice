/*
ID: andwerp1
LANG: JAVA
TASK: mountains
*/

//package mountains;

import java.io.*;
import java.util.*;

class mountains {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("mountains.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("mountains.out")));
    
    
    int n = Integer.parseInt(fin.readLine());
    
    int[][] temp = new int[n][2];
    
    for(int i = 0; i < n; i++) {
    	
    	StringTokenizer st = new StringTokenizer(fin.readLine());
    	
    	temp[i][0] = Integer.parseInt(st.nextToken());
    	temp[i][1] = Integer.parseInt(st.nextToken());
    	
    }
    
    Arrays.sort(temp, (a, b) -> a[0] - b[0]);
    
    ArrayList<int[]> mountains = new ArrayList<int[]>();
    
    for(int i = 0; i < n; i++) {
    	
    	mountains.add(temp[i]);
    	
    	//System.out.println(temp[i][0] + " " + temp[i][1]);
    	
    }
    
    for(int i = 0; i < mountains.size(); i++) {
    	
    	//System.out.println("Iteration " + i + ":");
    	
    	int pointer = i;
    	
    	int mountainHeight = mountains.get(i)[1];
    	
    	//System.out.println("mountain height: " + mountainHeight);
    	
    	while(pointer - 1 >= 0 && mountainHeight - Math.abs(mountains.get(i)[0] - mountains.get(pointer - 1)[0]) >= 0) {
    		
    		//System.out.println("looking to remove at position " + (pointer - 1));
    		
    		pointer--;
    		
    		if(Math.abs(mountains.get(i)[0] - mountains.get(pointer)[0]) + mountains.get(pointer)[1] <= mountainHeight) {
    			
    			//System.out.println("removed from position " + pointer);
    			
    			mountains.remove(pointer);
    			i--;
    			
    		}
    		
    	}
    	
    	pointer = i;
    	
    	while(pointer + 1 < mountains.size() && mountainHeight - Math.abs(mountains.get(i)[0] - mountains.get(pointer + 1)[0]) >= 0) {
    		
    		//System.out.println("looking to remove at position " + (pointer + 1));
    		
    		pointer++;
    		
    		if(Math.abs(mountains.get(i)[0] - mountains.get(pointer)[0]) + mountains.get(pointer)[1] <= mountainHeight) {
    			
    			//System.out.println("removed from position " + pointer);
    			
    			mountains.remove(pointer);
    			pointer--;
    			
    		}
    		
    	}
    	
    }
    
    fout.println(mountains.size());
    
    fin.close();
    fout.close();
    
	}
}