/*
ID: andwerp1
LANG: JAVA
TASK: milk3
*/

//package milk3;

import java.io.*;
import java.util.*;

class milk3 {
	static ArrayList<int[]> checkedStates = new ArrayList<int[]>();
	  static ArrayList<Integer> validEnds = new ArrayList<Integer>();
	  static int maxA;
	  static int maxB;
	  static int maxC;

	  static int stateCounter;

	  public static boolean isValidEndState(int a, int b, int c){
	    if(a == 0){
	      return true;
	    }
	    return false;
	  }

	  public static void generateNextStates(int a, int b, int c){

	    int[] currentState = {a, b, c};

	    for(int[] i : checkedStates){
	      if(Arrays.equals(i, currentState)){
	        return;
	      }
	    }

	    checkedStates.add(currentState);

	    if(isValidEndState(a, b, c)){
	      //System.out.println(a + " " + b + " " + c);
	      validEnds.add(c);
	    }

	    if(a != 0){
	      int[] temp = pour(b, a, maxB);
	      generateNextStates(temp[1], temp[0], c);
	      temp = pour(c, a, maxC);
	      generateNextStates(temp[1], b, temp[0]);
	    }

	    if(b != 0){
	      int[] temp = pour(a, b, maxA);
	      generateNextStates(temp[0], temp[1], c);
	      temp = pour(c, b, maxC);
	      generateNextStates(a, temp[1], temp[0]);
	    }

	    if(c != 0){
	      int[] temp = pour(a, c, maxA);
	      generateNextStates(temp[0], b, temp[1]);
	      temp = pour(b, c, maxB);
	      generateNextStates(a, temp[0], temp[1]);
	    }
	    

	  }

	  public static int[] pour(int bucket1, int bucket2, int max1){
	    
	    bucket1 += bucket2;
	    bucket2 = 0;
	    if(bucket1 > max1){
	      bucket2 += bucket1 - max1;
	      bucket1 = max1;
	    }

	    int[] temp = {bucket1, bucket2};

	    return temp;

	  }

	  public static void sort(ArrayList<Integer> values){

	    quicksort(0, values.size() - 1, values);
	        
	  }

	  public static void quicksort(int low, int high, ArrayList<Integer> values){

	    int initialLow = low;
	    int initialHigh = high;
	    int pivot = values.get(low + (high - low) / 2);

	    while(low <= high){

	      while(pivot > values.get(low)){
	        low++;
	      }

	      while(pivot < values.get(high)){
	        high--;
	      }

	      if(low <= high){
	        int temp = values.get(low);
	        values.set(low, values.get(high));
	        values.set(high, temp);
	        low++;
	        high--;
	      }

	    }

	    if(initialLow < high){
	      quicksort(initialLow, high, values);
	    }
	    if(initialHigh > low){
	      quicksort(low, initialHigh, values);
	    }

	  }

	  public static void main(String[] args) throws IOException {
	    
	    BufferedReader fin = new BufferedReader(new FileReader("milk3.in"));
	    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("milk3.out")));

	    StringTokenizer st = new StringTokenizer(fin.readLine());

	    maxA = Integer.parseInt(st.nextToken());
	    maxB = Integer.parseInt(st.nextToken());
	    maxC = Integer.parseInt(st.nextToken());

	    //maxA = 8;
	    //maxB = 9;
	    //maxC = 10;

	    generateNextStates(0, 0, maxC);
	    
	    sort(validEnds);

	    System.out.println(validEnds);

	    for(int i = 0; i < validEnds.size(); i++) {
	    	if(i < validEnds.size() - 1) {
	    		fout.print(validEnds.get(i) + " ");
	    	}
	    	
	    	else {
	    		fout.print(validEnds.get(i));
	    	}
	    }
	    fout.println();
	    fout.close();
	    fin.close();

	  }
}