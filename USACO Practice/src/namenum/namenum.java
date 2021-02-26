/*
ID: andwerp1
LANG: JAVA
TASK: namenum
*/

//ver1

//package namenum;

import java.io.*;
import java.util.*;

class namenum {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("dict.txt"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("namenum.out")));
    
    ArrayList<ArrayList<String>> dict = new ArrayList<ArrayList<String>>();
    
    for(int i = 0; i < 12; i++) {
    	dict.add(new ArrayList<String>());
    }
    
    for(int i = 0; i < 4617; i++) {
    	
    	String name = fin.readLine();
    			
    	dict.get(name.length() - 1).add(name);
    	
    }
    
    for(String i : dict.get(0)) {
    	System.out.println(i);
    }
    
    fin.close();
    
    fin = new BufferedReader(new FileReader("namenum.in"));
    
    String temp = fin.readLine();
    
    int idLength = temp.length();
    int[] cowId = new int[idLength];
    
    for(int i = 0; i < idLength; i++) {
    	cowId[i] = Integer.parseInt(temp.substring(i, i + 1));
    }
    
    String[][] code = new String[10][3];
    
    code[2][0] = "A";
    code[2][1] = "B";
    code[2][2] = "C";
    code[3][0] = "D";
    code[3][1] = "E";
    code[3][2] = "F";
    code[4][0] = "G";
    code[4][1] = "H";
    code[4][2] = "I";
    code[5][0] = "J";
    code[5][1] = "K";
    code[5][2] = "L";
    code[6][0] = "M";
    code[6][1] = "N";
    code[6][2] = "O";
    code[7][0] = "P";
    code[7][1] = "R";
    code[7][2] = "S";
    code[8][0] = "T";
    code[8][1] = "U";
    code[8][2] = "V";
    code[9][0] = "W";
    code[9][1] = "X";
    code[9][2] = "Y";
    
    ArrayList<String> validNames = new ArrayList<String>();
    
    for(int i = 0; i < dict.get(idLength - 1).size(); i++) {
    	
    	boolean isValidName = false;
    	String testName = dict.get(idLength - 1).get(i);
    	
    	for(int j = 0; j < idLength; j++) {
    		
    		isValidName = false;
    		
    		int testNum = Integer.parseInt(temp.substring(j, j + 1));
    		
    		for(int k = 0; k < code[testNum].length; k++) {
    			
    			if(code[testNum][k].equals(testName.substring(j, j + 1))) {
    				isValidName = true;
    			}
    			
    		}
    		
    		if(!isValidName) {
    			break;
    		}
    		
    	}
    	
    	if(isValidName) {
    		validNames.add(testName);
    	}
    	
    }
    
    for(String i : validNames) {
    	fout.println(i);
    }
    
    if(validNames.size() == 0) {
    	fout.println("NONE");
    }
    
    
    fin.close();
    fout.close();
    
	}
}