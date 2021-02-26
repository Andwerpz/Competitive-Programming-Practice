/*
ID: andwerp1
LANG: JAVA
TASK: dualpal
*/

//package dualpal;

import java.io.*;
import java.util.*;

class dualpal {
	
	public static ArrayList<Integer> convertBase(int base, int num) {
		
		int convertNum = num;
		ArrayList<Integer> convertedNum = new ArrayList<Integer>();
		
		while(convertNum != 0) {
			
			//System.out.println(convertNum + " " + convertedNum);
			convertedNum.add(0, convertNum % base);
			convertNum /= base;
		}
		
		return convertedNum;
		
	}
	
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("dualpal.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("dualpal.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int num = Integer.parseInt(st.nextToken());
    int lowerBound = Integer.parseInt(st.nextToken());
    
    int[] palindromes = new int[num];
    int pointer = lowerBound + 1;
    
    while(num != 0) {
    	
    	System.out.println(num + " " + pointer);
    	
    	int numPalindromes = 0;
    	
    	for(int i = 2; i <= 10; i++) {
    		
    		boolean isPalindrome = true;
    		ArrayList<Integer> convertedNum = convertBase(i, pointer);
    		
    		//System.out.println(convertedNum);
    		
    		for(int j = 0; j < convertedNum.size() / 2; j++) {
    			if(convertedNum.get(j) != convertedNum.get(convertedNum.size() - (j + 1))){
    				isPalindrome = false;
    				break;
    			}
    		}
    		
    		if(isPalindrome) {
    			numPalindromes++;
    			//System.out.println("is palindrome");
    		}
    		
    		if(numPalindromes == 2) {
    			break;
    		}
    		
    	}
    	
    	if(numPalindromes >= 2) {
    		num -= 1;
    		palindromes[palindromes.length - (num + 1)] = pointer;
    	}
    	
    	pointer++;
    	
    }
    
    for(int i : palindromes) {
    	fout.println(i);
    }
    
    fin.close();
    fout.close();
    
	}
}