/*
ID: andwerp1
LANG: JAVA
TASK: barn1
*/

package barn1;

import java.io.*;
import java.util.*;

class barn1ver1 {
	
	static ArrayList<Integer> numbers;
	
	public static void sort(ArrayList<Integer> values) {
		
		if(values.size() == 0) {
			return;
		}
		
		numbers = values;
		int number = values.size();
		
		quicksort(0, number - 1);
		
	}
	
	public static void quicksort(int low, int high) {
		
		int initialLow = low;
		int initialHigh = high;
		
		int pivot = numbers.get(low + (high - low) / 2);
		
		while(low <= high) {
			
			while(numbers.get(low) < pivot) {
				low++;
			}
			
			while(numbers.get(high) > pivot) {
				high--;
			}
			
			if(low <= high) {
				int temp = numbers.get(low);
				numbers.set(low, numbers.get(high));
				numbers.set(high, temp);
				
				low++;
				high--;
			}
			
		}
		
		if(initialLow < high) {
			quicksort(initialLow, high);
		}
		
		if(initialHigh > low) {
			quicksort(initialHigh, low);
		}
		
	}
	
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("barn1.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("barn1.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int numBoards = Integer.parseInt(st.nextToken());
    int numStalls = Integer.parseInt(st.nextToken());
    int numCows = Integer.parseInt(st.nextToken());
    
    int[] cowLocations = new int[numStalls];
    int[] boardLocations = new int[numStalls];
    
    ArrayList<Integer> gapLocations = new ArrayList<Integer>();
    
    int firstCow = -1;
    int lastCow = -1;
    
    for(int i = 0; i < numCows; i++) {
    	int cowLocation = Integer.parseInt(fin.readLine());
    	cowLocations[cowLocation - 1] = 1;
    }
    
    for(int i : cowLocations) {
    	System.out.print(i);
    }
    
    System.out.println();
    
    for(int i = 0; i < cowLocations.length; i++) {
    	if(cowLocations[i] == 1 && firstCow == -1) {
    		firstCow = i;
    	}
    	
    	if(cowLocations[i] == 1) {
    		lastCow = i;
    	}
    }
    
    int gapStart = -1;
    boolean isInGap = false;
    
    for(int i = firstCow; i <= lastCow; i++) {
    	
    	if(cowLocations[i] == 0 && !isInGap) {
    		gapStart = i;
    		isInGap = true;
    	}
    	
    	if(cowLocations[i] == 1 && isInGap) {
    		gapLocations.add(i - gapStart);
    		System.out.println(i - gapStart);
    		isInGap = false;
    	}
    	
    }
    
    sort(gapLocations);
    
    System.out.println(gapLocations);
    
    int totalGaps = 0;
    
    for(int i = 0; i < numBoards - 1; i++) {
    	totalGaps += gapLocations.get(gapLocations.size() - (i + 1));
    }
    
    System.out.println(firstCow + " " + lastCow);
    
    System.out.println((lastCow - firstCow)  + " " + (totalGaps - 1));
    
    System.out.println((lastCow - firstCow + 1) - (totalGaps));
    
    fout.print((lastCow - firstCow) - (totalGaps - 1));
    
    fin.close();
    fout.close();
    
	}
}