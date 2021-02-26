/*
ID: andwerp1
LANG: JAVA
TASK: ariprog
*/

package ariprog;

import java.io.*;
import java.util.*;

public class ariprogver1{
	
	
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
	
  public static boolean isSequenceValid(int[] squares, int start, int gap, int length){

    int pointer = start;

    for(int j = 0; j < length; j++){

      boolean isValid = false;

      // if(pointer > squares[squares.length - 1] + squares[squares.length - 2]){
      //   //isValid = true;
      // }

      for(int k = 0; k < squares.length; k++){
        for(int i = 0; i < squares.length; i++){

          //System.out.println(squares[i] + " " + squares[k] + " " + pointer + " " + (squares[i] + squares[k]));

          if(squares[i] + squares[k] == pointer){
            isValid = true;
            //System.out.println("is valid");
            break;
          }
        }
          
        if(isValid){
          break;
        }

      }

      if(!isValid){
        return false;
      }

      pointer += gap;

    }

    return true;

  }

  public static void main(String[] args) throws IOException{

    BufferedReader fin = new BufferedReader(new FileReader("ariprog.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("ariprog.out")));

    int n = Integer.parseInt(fin.readLine());
    int m = Integer.parseInt(fin.readLine());

    //int n = 5;
    //int m = 250;

    int[] squares = new int[m + 1];

    for(int i = 0; i < m + 1; i++){
      squares[i] = (int) Math.pow(i, 2);
      System.out.println(squares[i]);
    }

    //int[][] validSequences = new int[10000][2];
    ArrayList<int[]> validSequences = new ArrayList<int[]>();
    //int counter = 0;

    for(int i = 0; i < squares[squares.length - 1] * 2; i++){

      for(int j = 1; j < squares[squares.length - 1] * 2; j++){

        //System.out.println("new sequence" + i + " " + j);

        if(isSequenceValid(squares, i, j, n)){
          //validSequences[counter][0] = i;
          //validSequences[counter][1] = j;
          
          int[] temp = new int[2];
          temp[0] = i;
          temp[1] = j;
          validSequences.add(temp);

          //System.out.println("valid sequence");

          //counter++;
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
	    		
	    		//System.out.println(i);
	    		boolean duplicate = false;
	    		
	    		if(validSequences.get(i)[1] == prevUniqueNum) {
	    			
	    			if(!duplicate) {
	    				int[] temp1 = new int[2];
	    				temp1[0] = validSequences.get(i)[0];
	    				temp1[1] = validSequences.get(i)[1];
	    				temp.add(temp1);
	    			}
	    			//duplicate = !duplicate;
	    			
	    			pointer++;
	    		}
	    		
	    		else {
	    			prevUniqueNum = validSequences.get(i)[1];
	    			
	    			break;
	    		}
	    		
	    	}
	    	//pointer++;
	    	output.add(temp);
	    }
	    
	    for(int i = 0; i < output.size(); i++) {
	    	
	    	sort2(output.get(i));
	    	//System.out.println(output.size());
	    	for(int j = 0; j < output.get(i).size(); j++) {
	    		//System.out.println(output.get(i).size());
	    		
	   
	    		fout.println(output.get(i).get(j)[0] + " " + output.get(i).get(j)[1]);
	    		
	    	}
	    }
   }
    
    

    //isSequenceValid(squares, 5, 20, n);

//    for(int i = 0; i < validSequences.size(); i++){
//
//      
//        fout.println(validSequences.get(i)[0] + " " + validSequences.get(i)[1]);
//      
//      
//    }

    fin.close();
    fout.close();

  }

}