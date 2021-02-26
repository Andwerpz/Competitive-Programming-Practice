/*
ID: andwerp1
LANG: JAVA
TASK: milk2
*/

//ver3

//package milk2;

import java.io.*;
import java.util.*;


public class milk2 {
	
	private static int[][] numbers;
	private static int number;
	
	public static void sort(int[][] values) {
        // check for empty or null array
        if (values ==null || values.length==0){
            return;
        }
        numbers = values;
        number = values.length;
        quicksort(0, number - 1);
    }

    private static void quicksort(int low, int high) {
        int i = low, j = high;
        // Get the pivot element from the middle of the list
        int pivot = numbers[low + (high-low)/2][0];

        // Divide into two lists
        while (i <= j) {
            // If the current value from the left list is smaller than the pivot
            // element then get the next element from the left list
            while (numbers[i][0] < pivot) {
                i++;
            }
            // If the current value from the right list is larger than the pivot
            // element then get the next element from the right list
            while (numbers[j][0] > pivot) {
                j--;
            }

            // If we have found a value in the left list which is larger than
            // the pivot element and if we have found a value in the right list
            // which is smaller than the pivot element then we exchange the
            // values.
            // As we are done we can increase i and j
            if (i <= j) {
                exchange(i, j);
                i++;
                j--;
            }
        }
        // Recursion
        if (low < j)
            quicksort(low, j);
        if (i < high)
            quicksort(i, high);
    }

    private static void exchange(int i, int j) {
        int[] temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }
	
	public static void main (String [] args) throws IOException {
		
    BufferedReader fin = new BufferedReader(new FileReader("milk2.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("milk2.out")));
    int numFarmers = Integer.parseInt(fin.readLine());
    
    int[][] milkTimes = new int[numFarmers][2];
    
    for(int i = 0; i < numFarmers; i++) {
    	
    	StringTokenizer st = new StringTokenizer(fin.readLine());
    	
    	milkTimes[i][0] = Integer.parseInt(st.nextToken());
    	milkTimes[i][1] = Integer.parseInt(st.nextToken());
    	
    }
    
    
    
    
    sort(milkTimes);
    
    /*for(int[] i : temp) {
    	System.out.println(i[0] + " " + i[1]);
    }*/
    
    
    boolean isSimplified = false;
    
    while(!isSimplified) {
    	
    	isSimplified = true;
    	
	    for(int i = 0; i < numFarmers; i++) {
	    	for(int j = 0; j < numFarmers; j++) {
	    		
	    		if(milkTimes[i][0] < milkTimes[j][0] && milkTimes[i][1] >= milkTimes[j][0]) {
	    			milkTimes[j][0] = milkTimes[i][0];
	    			isSimplified = false;
	    		}
	    		
	    		if(milkTimes[i][1] > milkTimes[j][1] && milkTimes[i][0] < milkTimes[j][1]) {
	    			milkTimes[j][1] = milkTimes[i][1];
	    			isSimplified = false;
	    		}
	    		
	    	}
	    }
    }
    
    //Arrays.sort(milkTimes);
    //Arrays.sort(milkTimes);
    
    /*for(int i = 0; i < numFarmers; i++) {
    	System.out.println(milkTimes[i][0] + " " + milkTimes[i][1]);
    }*/
    
    int longestMilk = 0;
    int longestIdle = 0;
    
    for(int i = 0; i < numFarmers; i++) {
    	if(milkTimes[i][1] - milkTimes[i][0] > longestMilk) {
    		longestMilk = milkTimes[i][1] - milkTimes[i][0];
    	}
    }
    
    for(int i = 0; i < numFarmers - 1; i++) {
    	if(milkTimes[i + 1][0] - milkTimes[i][1] > longestIdle) {
    		longestIdle = milkTimes[i + 1][0] - milkTimes[i][1];
    	}
    }
    
    fout.println(longestMilk + " " + longestIdle);
    
    fout.close();
    fin.close();
    
	}
}
