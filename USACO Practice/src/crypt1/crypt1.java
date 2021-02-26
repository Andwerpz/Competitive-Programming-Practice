/*
ID: andwerp1
LANG: JAVA
TASK: crypt1
*/

//package crypt1;

import java.io.*;
import java.util.*;

class crypt1 {
	
	static int[] nums;
	static int numSolutions;
	
	public static void sort(int[] values) {
		
		quicksort(0, values.length - 1, values);
		
	}
	
	public static void quicksort(int low, int high, int[] values) {
		
		int initialLow = low;
		int initialHigh = high;
		
		int pivot = values[low + (high - low) / 2];
		
		while(low <= high) {
			
			while(pivot > values[low]) {
				low++;
			}
			
			while(pivot < values[high]) {
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
	
	public static void permute(int[] scramble, int k) {
		
		if(k == 1) {
			
			isPossible(scramble, nums);
			
		}
		
		else {
			
			permute(scramble, k - 1);
			
			for(int i = 0; i < k - 1; i++) {
				
				if(k % 2 == 0) {
					int temp = scramble[i];
					scramble[i] = scramble[k - 1];						//swapping elements i and k - 1
					scramble[k - 1] = temp;
				}
				
				else {
					int temp = scramble[0];
					scramble[0] = scramble[k - 1];						//swapping elements 0 and k - 1
					scramble[k - 1] = temp;
				}
				
				permute(scramble, k - 1);
			}
		}
		
	}
	
	static void printAllKLength(int[] set, int k) { 
		int n = set.length; 
		int[] prefix = new int[0];
		printAllKLengthRec(set, prefix, n, k); 
	} 
	
	static void printAllKLengthRec(int[] set, int[] prefix, int n, int k) { 
		
		if (k == 0) { 

			for(int i : prefix) {
				//System.out.print(i + " ");
			}
			//System.out.println();
			
			isPossible(prefix, nums);
			
			return; 
		} 
	
		// One by one add all characters 
		// from set and recursively 
		// call for k equals to k-1 
		for (int i = 0; i < n; i++) { 
	
			// Next character of input added
			
			int[] newPrefix = new int[prefix.length + 1];
			
			for(int j = 0; j < prefix.length; j++) {
				newPrefix[j] = prefix[j];
			}
			
			newPrefix[newPrefix.length - 1] = set[i];
			
			// k is decreased, because 
			// we have added a new character 
			printAllKLengthRec(set, newPrefix, n, k - 1); 
		} 
	} 
	
	public static void isPossible(int[] firstRow, int[] nums) {
		
		int num1 = firstRow[0] + firstRow[1] * 10 + firstRow[2] * 100;
		
		String add1 = (num1 * firstRow[3]) + "";
		String add2 = (num1 * firstRow[4]) + "";
		
		if(add1.length() != 3 || add2.length() != 3) {
			return;
		}
		
		for(int i = 0; i < 3; i++) {
			
			boolean is1Valid = false;
			boolean is2Valid = false;
			
			for(int j = 0; j < nums.length; j++) {
				
				if((Integer.parseInt(add1.substring(i, i + 1)) == nums[j])) {
					is1Valid = true;
				}
				
				if((Integer.parseInt(add2.substring(i, i + 1)) == nums[j])) {
					is2Valid = true;
				}
				//System.out.println(add1.substring(i, i+1) + " " + nums[j]);
				
			}
			
			if(!is1Valid || !is2Valid) {
				return;
			}
			
		}
		
		String addFinal = (Integer.parseInt(add1) + Integer.parseInt(add2) * 10) + "";
		
		for(int i = 0; i < 3; i++) {
			
			boolean isValid = false;
			
			for(int j = 0; j < nums.length; j++) {
				if(Integer.parseInt(addFinal.substring(i, i + 1)) == nums[j]){
					isValid = true;
				}
			}
			
			if(!isValid) {
				return;
			}
			
		}
		
		numSolutions++;
		
		//System.out.println(add1 + " " + add2);
		//System.out.println(addFinal);
		
	}
	
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("crypt1.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("crypt1.out")));
    
    int n = Integer.parseInt(fin.readLine());
    nums = new int[n];
    
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    for(int i = 0; i < n; i++) {
    	nums[i] = Integer.parseInt(st.nextToken());
    }
    
    sort(nums);
    
    for(int i : nums) {
    	System.out.println(i + " ");
    }
    
    //permute(nums, nums.length);
    printAllKLength(nums, 5);
    
    System.out.println(numSolutions);
    
    fout.println(numSolutions);
    
    fin.close();
    fout.close();
    
	}
}