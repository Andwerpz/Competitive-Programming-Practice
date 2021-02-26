/*
ID: andwerp1
LANG: JAVA
TASK: convention
*/

package convention;

import java.io.*;
import java.util.*;

class conventionver1 {
	
	static int[] numbers;

	static int[] cowTimes;
	static int n;
	static int m;
	static int c;
	
	
	public static void sort(int[] values) {
		
		numbers = values;
		int number = values.length;
		quicksort(0, number - 1);
		
	}
	
	public static void quicksort(int low, int high) {
		
		int initialLow = low;
		int initialHigh = high;
		int pointer = numbers[low + (high - low) / 2];
		
		while(low <= high) {
			
			while(numbers[low] < pointer) {
				low++;
			}
			
			while(numbers[high] > pointer) {
				high--;
			}
			
			if(low <= high) {
				int temp = numbers[low];
				numbers[low] = numbers[high];
				numbers[high] = temp;
				low++;
				high--;
			}
			
		}
		
		if(initialLow < high) {
			quicksort(initialLow, high);
		}
		
		if(initialHigh > low) {
			quicksort(low, initialHigh);
		}
		
	}
	
	public static int binarySearch(int low, int high) {
		
		System.out.println(low + " " + high);
		
		if(high == low) {
			return low;
		}
		
		if(high == low + 1) {
			if(isPossible(low)) {
				return low;
			}
			return high;
		}
		
		int mid = (high + low) / 2;
		
		if(isPossible(mid)) {
			return binarySearch(low, mid);
		}
		
		else {
			return binarySearch(mid + 1, high);
		}
		
		
		
	}
	
	public static boolean isPossible(int wait) {
		
		int numBusses = 1;
		int firstTime = cowTimes[0];
		int firstIndex = 0;
		
		for(int i = 1; i < n; i++) {
			
			if(cowTimes[i] - firstTime > wait || i + 1 - firstIndex > c) {
				numBusses ++;
				firstTime = cowTimes[i];
				firstIndex = i;
			}
			
		} 
		
		return (numBusses <= wait);
		
	}
	
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("convention.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("convention.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    n = Integer.parseInt(st.nextToken());	//num cows
    m = Integer.parseInt(st.nextToken());	//num busses
    c = Integer.parseInt(st.nextToken());	//num cows per bus
    
    System.out.println(n + " " + m + " " + c);
    cowTimes = new int[n];
    
    st = new StringTokenizer(fin.readLine());
    
    for(int i = 0; i < n; i++) {
    	cowTimes[i] = Integer.parseInt(st.nextToken());
    }
    
    sort(cowTimes);
    
    for(int i : cowTimes) {
    	//System.out.println(i);
    }
    
    for(int i = 0; i < cowTimes.length; i++) {
    	
    	
    }
    
    fout.println(binarySearch(0, 1000000000));
    
    fin.close();
    fout.close();
    
	}
}