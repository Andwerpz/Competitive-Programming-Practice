/*
ID: andwerp1
LANG: JAVA
TASK: ariprog
*/

package ariprog;

import java.util.*;
import java.io.*;

public class ariprogver2 {
	
	static int m;
	
	public static void sort3(int[] values) {
		quicksort3(0, values.length - 1, values);
	}
	
	public static void quicksort3(int low, int high, int[] values) {
		
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
			quicksort3(initialLow, high, values);
		}
		
		if(initialHigh > low) {
			quicksort3(low, initialHigh, values);
		}
		
	}

	public static void sort(ArrayList<int[]> values) {
		if(values.size() == 0) {
			return;
		}
		quicksort(0, values.size() - 1, values);
	}
	
	public static void quicksort(int low, int high, ArrayList<int[]> values) {
		
		int initialLow = low;
		int initialHigh = high;
		int pointer = values.get(low + (high - low) / 2)[1];
		
		while(low <= high) {
			while(pointer > values.get(low)[1]) {
				low++;
			}
			while(pointer < values.get(high)[1]) {
				high--;
			}
			if(low <= high) {
				int temp = values.get(low)[1];
				values.get(low)[1] = values.get(high)[1];
				values.get(high)[1] = temp;
				  
				temp = values.get(low)[0];
				values.get(low)[0] = values.get(high)[0];
				values.get(high)[0] = temp;
				  
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
	
	public static void sort2(ArrayList<int[]> values) {
		if(values.size() == 0) {
			return;
		}
		quicksort2(0, values.size() - 1, values);
	}
	
	public static void quicksort2(int low, int high, ArrayList<int[]> values) {
		
		int initialLow = low;
		int initialHigh = high;
		int pointer = values.get(low + (high - low) / 2)[0];
		
		while(low <= high) {
			while(pointer > values.get(low)[0]) {
				low++;
			}
			while(pointer < values.get(high)[0]) {
				high--;
			}
			if(low <= high) {
				int temp = values.get(low)[1];
				values.get(low)[1] = values.get(high)[1];
				values.get(high)[1] = temp;
				  
				temp = values.get(low)[0];
				values.get(low)[0] = values.get(high)[0];
				values.get(high)[0] = temp;
				  
				low++;
				high--;
			}
		}
		
		if(initialLow < high) {
			quicksort2(initialLow, high, values);
		}
		
		if(initialHigh > low) {
			quicksort2(low, initialHigh, values);
		}
		
	}
	
	public static boolean isSequenceValid(int[] squares, int start, int gap, int length) {
		
		int finalNum = start + (gap * (length - 1));
		
		if(finalNum > (m * m) * 2) {
			return false;
		}
		
		int pointer = start;
		int prevK = 0;
		
		for(int j = 0; j < length; j++) {
			
//			boolean isValid = false;
//			
//			for(int k = prevK; k < squares.length; k++) {
//				for(int i = k; i < squares.length; i++) {
//					if(squares[i] + squares[k] == pointer) {
//						isValid = true;
//						break;
//					}
//				}
//				
//				if(isValid) {
//					break;
//				}
//			}
//			
//			if(!isValid) {
//				return false;
//			}
			
			if(!binarySearch(squares, pointer, 0, squares.length - 1)) {
				return false;
			}
			
			pointer += gap;
			
		}
		
		return true;
		
	}
	
	public static boolean binarySearch(int[] values, int target, int low, int high) {
		
		//System.out.println(low + " " + high);
		
		if(high - low <= 2) {
			//System.out.println("found one");
			for(int i = low; i <= high; i++) {
				
				//System.out.println(target + " " + values[i]);
				
				if(target == values[i]) {
					//System.out.println("found one 2");
					return true;
				}
			}
			return false;
		}
		
		int mid = (high + low) / 2;
		
	
		
		if(values[mid] == target) {
			return true;
		}
		
		else if(values[mid] > target) {
			//System.out.println("lower");
			return binarySearch(values, target, low, mid);
		}
		
		else {
			//System.out.println("higher" + mid);
			return binarySearch(values, target, mid, high);
		}
		
	}
	
	public static void main(String[] args) throws IOException{
		
		BufferedReader fin = new BufferedReader(new FileReader("ariprog.in"));
		PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("ariprog.out")));
		
		int n = Integer.parseInt(fin.readLine());
		m = Integer.parseInt(fin.readLine());
		
		int[] squares = new int[(m + 1) * (m + 1) / 2 + (m / 2) + 1];
		int counter = 0;
		
		for(int i = 0; i <= m; i++) {
			for(int j = i; j <= m; j++) {
				squares[counter] = (i * i) + (j * j);
				//System.out.println(squares[counter] + " " + i + " " + j);
				counter++;
			}
		}
		
		//System.out.println(counter + " -------");
		
		sort3(squares);
		
		for(int i : squares) {
			System.out.println(i);
		}
		
		ArrayList<int[]> validSequences = new ArrayList<int[]>();
		
		
		for(int i = 0; i < m * m + 1; i++) {
			
			if(binarySearch(squares, i, 0, squares.length - 1)) {
				
				int maxGap = (squares[squares.length - 1] - i) / (n - 1);
				
				for(int j = 1; j < maxGap + 1; j++) {
					//System.out.println(i + " " + j+ " ------------");
					
					if(isSequenceValid(squares, i, j, n)) {
						
						int[] temp = new int[2];
						temp[0] = i;
						temp[1] = j;
						validSequences.add(temp);
						
						counter++;
						
					}
				}
			}
			
			
		}
		
		sort(validSequences);
		
		if(validSequences.size() == 0) {
			fout.println("NONE");
		}
		
		else {
			
			ArrayList<ArrayList<int[]>> output = new ArrayList<ArrayList<int[]>>();
			
			int prevUniqueNum = validSequences.get(0)[1];
			int pointer = 0;
			
			while(pointer < validSequences.size()) {
				
				ArrayList<int[]> temp = new ArrayList<int[]>();
				
				for(int i = pointer; i < validSequences.size(); i++) {
					
					if(validSequences.get(i)[1] == prevUniqueNum) {
						int[] temp1 = new int[2];
						temp1[0] = validSequences.get(i)[0];
						temp1[1] = validSequences.get(i)[1];
						temp.add(temp1);
						
						pointer++;
					}
					
					else {
						prevUniqueNum = validSequences.get(i)[1];
						break;
					}
					
				}
				
				output.add(temp);
				
			}
			
			for(int i = 0; i < output.size(); i++) {
				sort2(output.get(i));
				for(int j = 0; j < output.get(i).size(); j++) {
					fout.println(output.get(i).get(j)[0] + " " + output.get(i).get(j)[1]);
				}
			}
			
		}
		
		fin.close();
		fout.close();
		
	}
	
}
