/*
ID: andwerp1
LANG: JAVA
TASK: highcard
*/

//package highcard;

import java.io.*;
import java.util.*;

public class highcard {
	public static void main (String [] args) throws IOException {
		
	//for this solution, we will generate both cows hands, and sort them. For each card in elsie's hand, we will take the lowest card in Bessie's hand to beat it
	//and if we can't beat it, we will match it with the lowest card in bessie's hand.
    
    BufferedReader fin = new BufferedReader(new FileReader("highcard.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("highcard.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    
    int[] e = new int[n];
    ArrayList<Integer> b = new ArrayList<Integer>();
    
    for(int i = 0; i < n; i++) {
    	
    	e[i] = Integer.parseInt(fin.readLine()) - 1;
    	
    }
    
    Arrays.sort(e);
    
    int ePointer = 0;
    int bPointer = 0;
    
    for(int i = 0; i < n * 2; i++) {
    	
    	//System.out.println("i: " + i);
    	
    	if(ePointer < n && e[ePointer] != i) {
    		b.add(i);
    		//System.out.println("added to bessie");
    	}
    	
    	else if(ePointer < n && e[ePointer] == i) {
    		ePointer ++;
    	}
    	
    	else if(ePointer == n) {
    		b.add(i);
    	}
    	
    }
    
    
    for(int i = 0; i < n; i++) {
    	//System.out.print(e[i] + " ");
    	//System.out.println(b.get(i));
    }
    
    
    int wins = 0;
    
    for(int i = 0; i < n; i++) {
    	
    	int low = 0;
    	int high = b.size() - 1;
    	
    	int mid = low + (high - low) / 2;
    	
    	int ans = n + 1;
    	
    	while(low <= high) {
    		
    		if(b.get(mid) > e[i]) {
    			if(ans > mid) {
    				ans = mid;
    			}
    			
    			high = mid - 1;
    		}
    		
    		else {
    			low = mid + 1;
    		}
    		
    		mid = low + (high - low) / 2;
    		
    	}
    	
    	if(ans != n + 1) {
    		
    		b.remove(ans);
    		wins++;
    		
    	}
    	
    	else {
    		b.remove(0);
    	}
    	
    }
    
    fout.println(wins);
    
    fin.close();
    fout.close();
    
	}
}