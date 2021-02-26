/*
ID: andwerp1
LANG: JAVA
TASK: combo
*/

//package combo;

import java.io.*;
import java.util.*;

class combo {
	
	static int[] fCombo;
	static int[] mCombo;
	static int n;
	
	public static boolean isValidCombo(ArrayList<Integer> combo, int[] key) {
		
		  
		
		for(int i = 0; i < key.length; i++) {
			
			boolean isValid = false;
			//System.out.println(combo.get(i) + " " + key[i]);

			if((Math.abs(combo.get(i) - key[i]) <= 2)) {
				//System.out.println("case 1");
				isValid = true;
			}
			
						
			else if(key[i] <= 2 || Math.abs(key[i] - n) <= 2) {
    			
    			if((Math.abs(key[i] + n - combo.get(i)) <= 2) || Math.abs(key[i] - (n + combo.get(i))) <= 2) {
    				//System.out.println("case 23423432");
        			isValid = true;
        		}
    			
    		}
			
			if(!isValid) {
				return false;
			}
			
		}
		
		return true;
		
	}
	
	public static void main (String [] args) throws IOException {
    
	    BufferedReader fin = new BufferedReader(new FileReader("combo.in"));
	    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("combo.out")));
	    
	    n = Integer.parseInt(fin.readLine());
	    fCombo = new int[3];
	    mCombo = new int[3];
	    
	    StringTokenizer st = new StringTokenizer(fin.readLine());
	    
	    fCombo[0] = Integer.parseInt(st.nextToken());
	    fCombo[1] = Integer.parseInt(st.nextToken());
	    fCombo[2] = Integer.parseInt(st.nextToken());
	    
	    st = new StringTokenizer(fin.readLine());
	    
	    mCombo[0] = Integer.parseInt(st.nextToken());
	    mCombo[1] = Integer.parseInt(st.nextToken());
	    mCombo[2] = Integer.parseInt(st.nextToken());
	    
	    ArrayList<ArrayList<Integer>> possibleDigits = new ArrayList<ArrayList<Integer>>();
	    
	    for(int i = 0; i < fCombo.length; i++) {
	    	
	    	ArrayList<Integer> temp = new ArrayList<Integer>();
	    	
	    	for(int j = 1; j <= n; j++) {
	    		
	    		if(Math.abs(fCombo[i] - j) <= 2 || Math.abs(mCombo[i] - j) <= 2) {
	    			
	    			if(j == 0) {
	    				temp.add(n);
	    			}
	    			
	    			else {
	    				temp.add(j);
	    			}
	    		}
	    		
	    		else if(j <= 2 || Math.abs(n - j) <= 2) {
	    			
	    			if(Math.abs(fCombo[i] + n - j) <= 2 || Math.abs(mCombo[i] + n - j) <= 2) {
	        			temp.add(j);
	        		}
	    			
	    			else if(Math.abs(fCombo[i] - (n + j)) <= 2 || Math.abs(mCombo[i] - (n + j)) <= 2) {
	        			temp.add(j);
	        		}
	    			
	    			
	    			
	    		}
	    		
	    	}
	    	
	    	possibleDigits.add(temp);
	    	
	    }
	    
	    ArrayList<ArrayList<Integer>> possibleCombos = new ArrayList<ArrayList<Integer>>();
	    
	    
	    	
	    	
	    	
	    for(int i = 0; i < possibleDigits.get(0).size(); i++) { 		
	    	for(int j = 0; j < possibleDigits.get(1).size(); j++) {
	       		for(int k = 0; k < possibleDigits.get(2).size(); k++) {
	       			
	       			ArrayList<Integer> temp = new ArrayList<Integer>();
	       			
	       			temp.add(possibleDigits.get(0).get(i));
	       			temp.add(possibleDigits.get(1).get(j));
	           		temp.add(possibleDigits.get(2).get(k));
	           		
	           		System.out.println(temp);
	            		
	           		if(isValidCombo(temp, fCombo)) {
	           			System.out.println("is valid combo");
	           			possibleCombos.add(temp);
	           		}
	           		
	           		else if(isValidCombo(temp, mCombo)) {
	           			possibleCombos.add(temp);
	           			System.out.println("isValidCombo");
	           		}
	           		
	           	}   	
	       	}
	    }
	    	
	
	    	
	    
	    
	    System.out.println(possibleDigits);
	    System.out.println(possibleCombos.size());
	    
	    fout.println(possibleCombos.size());
	    
	    fin.close();
	    fout.close();
	    
	}
}