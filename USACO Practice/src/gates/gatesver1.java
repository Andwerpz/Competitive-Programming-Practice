/*
ID: andwerp1
LANG: JAVA
TASK: gates
*/

package gates;

import java.io.*;
import java.util.*;

class gatesver1 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("gates.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("gates.out")));
    
    //first we simulate fj's movements to find out where the fences will be laid
    //then we do a floodfill to figure out how many isolated sections there are.
    //the number of gates will always be the number of isolated sections - 1 since each section needs to have a gate, and each gate can only connect 2 sections together.
    
    //we start the floodfill from 0, 0 in the array
    //the first floodfill is to see which parts of the pasture are part of the outside
    //then we iterate through all cells in the pasture, and when we hit a section that wasn't visited, we floodfill it, and increment our cell counter
    
    
    int n = Integer.parseInt(fin.readLine());
    int[][] pasture = new int[n * 2 + 1][n * 2 + 1];
    
    String temp = fin.readLine();
    
    int pointerX = pasture.length / 2;
    int pointerY = pasture.length / 2;
    
    pasture[pointerX][pointerY] = -1;
    
    for(int i = 0; i < n; i++) {
    	
    	String nextMove = temp.charAt(i) + "";
    	
    	if(nextMove.equals("N")) {	//+y
    		
    		pasture[pointerX][pointerY + 1] = -1;
    		pasture[pointerX][pointerY + 2] = -1;
    		
    		pointerY += 2;
    		
    	}
    	
    	else if(nextMove.equals("S")) {	//-y
    		
    		pasture[pointerX][pointerY - 1] = -1;
    		pasture[pointerX][pointerY - 2] = -1;
    		
    		pointerY -= 2;
    		
    	}

    	else if(nextMove.equals("E")) {	//+x
			
			pasture[pointerX + 1][pointerY] = -1;
			pasture[pointerX + 2][pointerY] = -1;
			
			pointerX += 2;
			
		}
		
    	else if(nextMove.equals("W")) {	//-x
			
			pasture[pointerX - 1][pointerY] = -1;
			pasture[pointerX - 2][pointerY] = -1;
			
			pointerX -= 2;
			
		}
    	
    }
    
    Stack<int[]> toProcess = new Stack<int[]>();
    
    toProcess.add(new int[] {0, 0});
    
    while(toProcess.size() > 0) {
    	
    	int[] curCoords = toProcess.pop();
    	
    	int x = curCoords[0];
    	int y = curCoords[1];
    	
    	pasture[x][y] = 1;
    	
    	if(x + 1 < pasture.length && pasture[x + 1][y] == 0) {	//+x
    		
    		toProcess.add(new int[] {x + 1, y});
    		
    	}
    	
    	if(x - 1 >= 0 && pasture[x - 1][y] == 0) {	//-x
    		
    		toProcess.add(new int[] {x - 1, y});
    		
    	}
    	
    	if(y + 1 < pasture.length && pasture[x][y + 1] == 0) {	//+y
    		
    		toProcess.add(new int[] {x, y + 1});
    		
    	}
    	
    	if(y - 1 >= 0 && pasture[x][y - 1] == 0) {	//-y
    		
    		toProcess.add(new int[] {x, y - 1});
    		
    	}
    	
    }
    
    int numCells = 1;
    
    for(int i = 0; i < pasture.length; i++) {
    	
    	for(int j = 0; j < pasture.length; j++) {
    		
    		if(pasture[i][j] == 0) {
    			
    			numCells ++;
    			
    			Stack<int[]> toProcess2 = new Stack<int[]>();
    		    
    		    toProcess2.add(new int[] {i, j});
    		    
    		    while(toProcess2.size() > 0) {
    		    	
    		    	int[] curCoords = toProcess2.pop();
    		    	
    		    	int x = curCoords[0];
    		    	int y = curCoords[1];
    		    	
    		    	pasture[x][y] = numCells;
    		    	
    		    	if(x + 1 < pasture.length && pasture[x + 1][y] == 0) {	//+x
    		    		
    		    		toProcess2.add(new int[] {x + 1, y});
    		    		
    		    	}
    		    	
    		    	if(x - 1 >= 0 && pasture[x - 1][y] == 0) {	//-x
    		    		
    		    		toProcess2.add(new int[] {x - 1, y});
    		    		
    		    	}
    		    	
    		    	if(y + 1 < pasture.length && pasture[x][y + 1] == 0) {	//+y
    		    		
    		    		toProcess2.add(new int[] {x, y + 1});
    		    		
    		    	}
    		    	
    		    	if(y - 1 >= 0 && pasture[x][y - 1] == 0) {	//-y
    		    		
    		    		toProcess2.add(new int[] {x, y - 1});
    		    		
    		    	}
    		    	
    		    }
    			
    		}
    		
    	}
    	
    }
    
//    for(int i = 0; i < pasture.length; i++) {
//    	
//    	for(int j = 0; j < pasture.length; j++) {
//    		
//    		if(pasture[i][j] != 0 && pasture[i][j] != -1) {
//    			System.out.print(pasture[i][j]);
//    		}
//    		
//    		else if(pasture[i][j] != -1) {
//    			
//    			System.out.print(".");
//    			
//    		}
//    		
//    		else {
//    			System.out.print("#");
//    		}
//    		
//    	}
//    	
//    	System.out.println();
//    	
//    }
    
    fout.println(numCells - 1);
    
    fin.close();
    fout.close();
    
	}
}