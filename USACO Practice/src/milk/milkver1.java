/*
ID: andwerp1
LANG: JAVA
TASK: milk
*/

package milk;

import java.io.*;
import java.util.*;

public class milkver1{
	
	static int[][] numbers;
	
	public static void sort(int[][] values) {
        // check for empty or null array
        if (values ==null || values.length==0){
            return;
        }
        numbers = values;
        int number = values.length;
        quicksort2(0, number - 1);
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
    
//    private static void quicksort2(int low, int high) {
//    	
//    	System.out.println("recursion");
//    	
//    	int initialLow = low;
//    	int initialHigh = high;
//    	
//    	int pivot = numbers[low + (high - low) / 2][0];	//pivot element is from the middle of the list
//    	
//    	while(low <= high) {
//    		
//    		System.out.println("new while");
//    		
//    		while(numbers[low][0] < pivot) {
//    			low++;
//    		}
//    		
//    		while(numbers[high][0] > pivot) {
//    			high--;
//    		}
//    		
//    		if(low <= high) {
//    			
//    			for(int i = 0; i < numbers.length; i++) {
//    				System.out.print(numbers[i][0] + " ");
//    			}
//    			System.out.println();
//    			
//    			exchange(low, high);
//    			low++;
//    			high--;
//    		}
//    		
//    	}
//    	
//    	if(initialLow < high) {
//    		quicksort2(initialLow, high);
//    	}
//    	
//    	if(initialHigh > low) {
//    		quicksort2(low, initialHigh);
//    	}
//    	System.out.println("exit");
//    }
    
    public static void quicksort2(int low, int high) {
    	
    	int initialLow = low;
    	int initialHigh = high;
    	
    	int pivot = numbers[low + (high - low) / 2][0];
    	
    	while(low <= high) {
    		
    		while(numbers[low][0] < pivot) {
    			low ++;
    		}
    		
    		while(numbers[high][0] > pivot) {
    			high--;
    		}
    		
    		if(low <= high) {
    			exchange(low, high);
    			low++;
    			high--;
    		}
    		
    	}
    	
    	if(initialLow < high) {
    		quicksort2(initialLow, high);
    	}
    	
    	if(initialHigh > low) {
    		quicksort2(low, initialHigh);
    	}
    	
    }

    private static void exchange(int i, int j) {
        int[] temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }
	
	public static void main (String [] args) throws IOException {
    
	    BufferedReader fin = new BufferedReader(new FileReader("milk.in"));
	    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("milk.out")));
	    StringTokenizer st = new StringTokenizer(fin.readLine());
	    
	    int targetMilk = Integer.parseInt(st.nextToken());
	    int numFarmers = Integer.parseInt(st.nextToken());
	    
	    boolean isDone = false;
	    
	    int[][] farmers = new int[numFarmers][2];
	    
	    for(int i = 0; i < numFarmers; i++) {
	    	
	    	st = new StringTokenizer(fin.readLine());
	    	farmers[i][0] = Integer.parseInt(st.nextToken());
	    	farmers[i][1] = Integer.parseInt(st.nextToken());
	    	
	    }
	    
	    sort(farmers);
	    
	    int finalCost = 0;
	    
	    while(!isDone) {
	    	
	    	int currentMilk = 0;
	    	int currentCost = 0;
	    	
	    	for(int i = 0; i < numFarmers; i++) {
	    		
	    		currentMilk += farmers[i][1];
	    		currentCost += farmers[i][0] * farmers[i][1];	//multiplying the price of milk by how many units we purchase
	    		
	    		if(currentMilk > targetMilk) {
	    			currentCost -= farmers[i][0] * (currentMilk - targetMilk);
	    			currentMilk = targetMilk;
	    		}
	    		
	    	}
	    	
	    	if(currentMilk == targetMilk) {
	    		finalCost = currentCost;
	    		isDone = true;
	    	}
	    	
	    }
	    
	    fout.print(finalCost);
	    
	    fin.close();
	    fout.close();
    
	}
}