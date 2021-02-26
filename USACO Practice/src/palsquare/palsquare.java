/*
ID: andwerp1
LANG: JAVA
TASK: palsquare
*/

//package palsquare;

import java.io.*;
import java.util.*;

class palsquare {
	
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
	
	public static String printNum(int num) {
		
		switch(num) {
		
		case 0:
			return "0";
			
		case 1:
			return "1";
			
		case 2:
			return "2";
			
		case 3:
			return "3";
			
		case 4:
			return "4";
			
		case 5:
			return "5";
			
		case 6:
			return "6";
			
		case 7:
			return "7";
			
		case 8:
			return "8";
			
		case 9:
			return "9";
			
		case 10:
			return "A";
			
		case 11:
			return "B";
			
		case 12:
			return "C";
			
		case 13:
			return "D";
			
		case 14:
			return "E";
			
		case 15:
			return "F";
			
		case 16:
			return "G";
			
		case 17:
			return "H";
			
		case 18:
			return "I";
			
		case 19:
			return "J";
		
		}
		
		return "";
		
	}
	
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("palsquare.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("palsquare.out")));
    
    int base = Integer.parseInt(fin.readLine());
    
    for(int i = 1; i < 301; i++) {
    	
    	int num = i * i;
    	
    	ArrayList<Integer> convertedNum2 = convertBase(base, num);
    	boolean isPalindrome = true;
    	
    	for(int j = 0; j < convertedNum2.size() / 2; j++) {
    		
    		if(convertedNum2.get(j) != convertedNum2.get(convertedNum2.size() - (j + 1))) {
    			isPalindrome = false;
    		}
    		
    	}
    	
    	if(isPalindrome) {
    		
    		ArrayList<Integer> convertedNum = convertBase(base, i);
    		
    		for(int j = 0; j < convertedNum.size(); j++) {
    			fout.print(printNum(convertedNum.get(j)));
    		}
    		
    		fout.print(" ");
    		
    		for(int j = 0; j < convertedNum2.size(); j++) {
    			fout.print(printNum(convertedNum2.get(j)));
    		}
    		
    		fout.println();
    		
    	}
    	
    }
    
    fin.close();
    fout.close();
    
	}
}