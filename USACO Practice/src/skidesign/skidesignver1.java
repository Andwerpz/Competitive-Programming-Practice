/*
ID: andwerp1
LANG: JAVA
TASK: skidesign
*/

package skidesign;

import java.io.*;
import java.util.*;

class skidesignver1 {
	
	public static void sort(int[] values) {
		quicksort(0, values.length - 1, values);
	}
	
	public static void quicksort(int low, int high, int[] values) {
		
		int initialLow = low;
		int initialHigh = high;
		int pointer = values[low + (high - low) / 2];
		
		while(low <= high) {
			
			while(pointer > values[low]) {
				low++;
			}
			
			while(pointer < values[high]) {
				high--;
			}
			
			if(low <= high) {
				int temp = values[low];
				values[low] = values[high];
				values[high] = temp;
				low++;
				high--;
			}
			
		}
		
		if(initialLow < high) {
			quicksort(initialLow, high, values);
		}
		
		if(initialHigh > low) {
			quicksort(low, initialHigh, values);
		}
		
	}
	
	public static int calculatePrice(int startHill, int[] hills) {
		
		int range = 17;
		int totalCost = 0;
		
		for(int i = 0; i < hills.length; i++) {
			
			if(hills[i] < startHill) {
				totalCost += Math.pow(startHill - hills[i], 2);
			}
			
			else if(hills[i] > startHill + range) {
				totalCost += Math.pow(hills[i] - (startHill + range), 2);
			}			
		}
		
		return totalCost;
		
	}
	
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("skidesign.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("skidesign.out")));
    //StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(fin.readLine());
    int[] hills = new int[n];
    
    for(int i = 0; i < n; i++) {
    	hills[i] = Integer.parseInt(fin.readLine());
    }
    
    sort(hills);
    
    for(int i : hills) {
    	System.out.print(i + " ");
    }
    
    System.out.println();
    
    
    
    int[] below = new int[n];
    int[] above = new int[n];
    
    int minCost = -1;
    
    for(int i = 1; i <= 100; i++) {
    	int currentCost = calculatePrice(i, hills);
    	
    	if(currentCost < minCost || minCost == -1) {
    		minCost = currentCost;
    	}
    }
    
    System.out.println(minCost);
    
    fout.println(minCost);
    
    fin.close();
    fout.close();
    
	}
}