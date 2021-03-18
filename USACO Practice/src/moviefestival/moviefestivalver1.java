/*
ID: andwerp1
LANG: JAVA
TASK: moviefestival
*/

package moviefestival;

import java.io.*;
import java.util.*;

public class moviefestivalver1 {
	public static void main (String [] args) throws IOException {
		
	//this solution runs out of time
    
    Scanner fin = new Scanner(System.in);
    
    
    int n = Integer.parseInt(fin.nextLine());
    
    int[][] movies = new int[n][2];
    
    for(int i = 0; i < n; i++) {
    	
    	StringTokenizer st = new StringTokenizer(fin.nextLine());
    	
    	movies[i] = new int[] {Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken())};
    	
    }
    
    Arrays.sort(movies, (a, b) -> a[1] - b[1]);
    
    int curTime = 0;
    int numMovies = 0;
    
    for(int i = 0; i < n; i++) {
    	
    	if(curTime <= movies[i][0]) {
    		numMovies++;
    		curTime = movies[i][1];
    	}
    	
    }
    
    System.out.println(numMovies);
    
    fin.close();
    
	}
}