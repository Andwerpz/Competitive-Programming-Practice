/*
ID: your_id_here
LANG: JAVA
TASK: test
*/

package transform;

import java.io.*;
import java.util.*;

class transformver1 {
	
	public static boolean is90Degree(int[][] start, int[][] end) {
		
		boolean output = true;
		
		for(int i = 0; i < start.length; i++) {
			for(int j = 0; j < start.length; j++) {
				if(start[i][j] != end[j][end.length - 1 - i]) {
					output = false;
				}
			}
		}

		return output;
	}
	
	public static boolean is180Degree(int[][] start, int[][] end) {
		
		boolean output = true;
		
		for(int i = 0; i < start.length; i++) {
			for(int j = 0; j < start.length; j++) {
				if(start[i][j] != end[end.length - 1 - i][end.length - 1 - j]) {
					output = false;
				}
			}
		}

		return output;
		
	}
	
	public static boolean is270Degree(int[][] start, int[][] end) {
		
		boolean output = true;
		
		for(int i = 0; i < start.length; i++) {
			for(int j = 0; j < start.length; j++) {
				if(start[i][j] != end[end.length - 1 - j][i]) {
					output = false;
				}
			}
		}

		return output;
		
	}
	
	public static boolean isReflection(int[][] start, int[][] end) {
		
		boolean output = true;
		
		for(int i = 0; i < start.length; i++) {
			for(int j = 0; j < start.length; j++) {
				if(start[i][j] != end[i][end.length - 1 - j]) {
					output = false;
				}
			}
		}
		
		return output;
		
	}
	
	public static boolean isCombination(int[][] start, int[][] end) {
		
		boolean output = false;
		
		int[][] reflected = new int[start.length][start.length];
		
		for(int i = 0; i < start.length; i++) {
			for(int j = 0; j < start.length; j++) {
				reflected[i][j] = start[i][start.length - 1 - j];
			}
		}
		
		if(is90Degree(reflected, end) || is180Degree(reflected, end) || is270Degree(reflected, end)) {
			output = true;
		}
		
		return output;
		
	}
	
	public static boolean isNoChange(int[][] start, int[][] end) {
		
		boolean output = true;
		
		for(int i = 0; i < start.length; i++) {
			for(int j = 0; j < start.length; j++) {
				if(start[i][j] != end[i][j]) {
					output = false;
				}
			}
		}
		
		return output;
		
	}
	
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("transform.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("transform.out")));
    
    int gridDimensions = Integer.parseInt(fin.readLine());
    int[][] gridStart = new int[gridDimensions][gridDimensions];
    int[][] gridFinal = new int[gridDimensions][gridDimensions];
    
    for(int i = 0; i < gridDimensions; i++) {
    	
    	String row = fin.readLine();
    	char[] chars = new char[row.length()];
    	row.getChars(0, row.length(), chars, 0);
    	
    	for(int j = 0; j < gridDimensions; j++) {
    		
    		if(chars[j] == '-') {
    			gridStart[i][j] = 0;
    		}
    		else {
    			gridStart[i][j] = 1;
    		}
    		
    	}
    	
    }
    
    for(int i = 0; i < gridDimensions; i++) {
    	
    	String row = fin.readLine();
    	char[] chars = new char[row.length()];
    	row.getChars(0, row.length(), chars, 0);
    	
    	for(int j = 0; j < gridDimensions; j++) {
    		
    		if(chars[j] == '-') {
    			gridFinal[i][j] = 0;
    		}
    		else {
    			gridFinal[i][j] = 1;
    		}
    		
    	}
    	
    }
    
    for(int[] i : gridStart) {
    	for(int j : i) {
    		System.out.print(j + " ");
    	}
    	System.out.println();
    }
    
    for(int[] i : gridFinal) {
    	for(int j : i) {
    		System.out.print(j + " ");
    	}
    	System.out.println();
    }
    
    if(is90Degree(gridStart, gridFinal)) {
    	fout.println("1");
    }
    else if(is180Degree(gridStart, gridFinal)) {
    	fout.println("2");
    }
    else if(is270Degree(gridStart, gridFinal)) {
    	fout.println("3");
    }
    else if(isReflection(gridStart, gridFinal)) {
    	fout.println("4");
    }
    else if(isCombination(gridStart, gridFinal)) {
    	fout.println("5");
    }
    else if(isNoChange(gridStart, gridFinal)) {
    	fout.println("6");
    }
    else {
    	fout.println("7");
    }
    
    fin.close();
    fout.close();
	
	}
}