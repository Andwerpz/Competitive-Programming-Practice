/*
ID: andwerp1
LANG: JAVA
TASK: haybales
*/

package haybales;

import java.io.*;
import java.util.*;

class haybalesver1 {
	public static void main (String [] args) throws IOException {
		
	//for each query, we need to return the amount of haybales within a specific interval of the road
	//since the haybales are stored as their locations on the road, we can binary search to find the start and end points
	//and then subtract the end with the start - 1 to get the amount of haybales between them
		
	//this implementation finds the greatest value that is less than the start point.
    
    BufferedReader fin = new BufferedReader(new FileReader("haybales.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("haybales.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int q = Integer.parseInt(st.nextToken());
    
    int[] haybales = new int[n];
    
    st = new StringTokenizer(fin.readLine());
    
    for(int i = 0; i < n; i++) {
    	
    	haybales[i] = Integer.parseInt(st.nextToken());
    	
    }
    
    Arrays.sort(haybales);
    
    for(int i : haybales) {
    	System.out.print(i + " ");
    }
    System.out.println();
    
    for(int i = 0; i < q; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int ansLow = -1;
    	int ansHigh = -1;
    	
    	int a = Integer.parseInt(st.nextToken());
    	int b = Integer.parseInt(st.nextToken());
    	
    	int low = 0;
    	int high = n - 1;
    	
    	int mid = 0;
    	
    	while(low <= high) {
    		
    		mid = low + (high - low) / 2;
    		
    		if(haybales[mid] < a) {
    			low = mid + 1;
    			ansLow = mid;
    		}
    		
    		else {
    			high = mid - 1;
    		}
    		
    	}
    	
    	low = 0;
    	high = n - 1;
    	
    	while(low <= high) {
    		
    		mid = low + (high - low) / 2;
    		
    		if(haybales[mid] <= b) {
    			low = mid + 1;
    			ansHigh = mid;
    		}
    		
    		else {
    			high  = mid - 1;
    		}
    		
    	}
    	
    	System.out.println(ansLow + " " + ansHigh);
    	
    	fout.println(ansHigh - ansLow);
    	
    }
    
    fin.close();
    fout.close();
    
	}
}