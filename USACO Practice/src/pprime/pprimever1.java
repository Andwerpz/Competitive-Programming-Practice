/*
ID: andwerp1
LANG: JAVA
TASK: pprime
*/

package pprime;

import java.io.*;
import java.util.*;

class pprimever1 {
	
	static int a;
	static int b;
	
	static int topPowerLimitA;
	static int topPowerLimitB;
	
	static int aPower;
	
	static void generatePalindromes(ArrayList<Integer> palindromes, char[] startPalindrome, int limit) {
		
//		int number = 0;
//		
//		for(int i = 0; i < (startPalindrome.length + 1) / 2; i++) {
//			number += Integer.parseInt(startPalindrome[startPalindrome.length - 1 - i] + "") * Math.pow(10, (startPalindrome.length + 1) / 2 - i - 1);
//		}
		
		//System.out.println(number);
		
		ArrayList<Integer> curPal = new ArrayList<Integer>();
		
		for(int i = 0; i < (startPalindrome.length + 1) / 2; i++) {
			curPal.add(Integer.parseInt(startPalindrome[i] + ""));
		}
		
		System.out.println(curPal);
		
		int power = startPalindrome.length;
		int number = 0;
		
		for(int i = 0; i < curPal.size(); i++) {
			if(power % 2 == 1 && i == curPal.size() - 1) {
				number += curPal.get(i) * Math.pow(10, i);;
			}
			
			else {
				number += curPal.get(i) * Math.pow(10, i);
				number += curPal.get(i) * Math.pow(10, power - i - 1);
			}
		}
		
		System.out.println(number + " " + power);
		
		number = Integer.parseInt(String.valueOf(startPalindrome));
		
		while(number < limit) {
			
			//curPal.set(curPal.size() - 1, curPal.get(curPal.size() - 1) + 1);
			
			int temp = 0;
			
			for(int i = 0; i < curPal.size(); i++) {
				temp += curPal.get(i) * Math.pow(10, i);
			}
			
			temp += 1;
			curPal.clear();
			
			System.out.println(temp % 10);
			
			while(temp > 0) {
				curPal.add(0, temp % 10);
				temp /= 10;
			}
			
			System.out.println(curPal);
			
			number = 0;
			
			for(int i = 0; i < curPal.size(); i++) {
				if(power % 2 == 1 && i == curPal.size() - 1) {
					number += curPal.get(i) * Math.pow(10, i);;
				}
				
				else {
					number += curPal.get(i) * Math.pow(10, i);
					number += curPal.get(i) * Math.pow(10, power - i - 1);
				}
			}
			
			System.out.println(number);
			
		}
		
	}
	
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("pprime.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("pprime.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    a = Integer.parseInt(st.nextToken());
    b = Integer.parseInt(st.nextToken());
    
    topPowerLimitA = a;
    topPowerLimitB = b;
    
    while(topPowerLimitA > 10) {
    	topPowerLimitA = topPowerLimitA / 10;
    }
    
    while(topPowerLimitB > 10) {
    	topPowerLimitB = topPowerLimitB / 10;
    }
    
    int temp = a;
    
    while(temp > 10) {
    	temp /= 10;
    	aPower ++;
    }
    
    aPower ++;
    
    
    temp = a;
    
    char[] aChars = (temp + "").toCharArray();
    
    boolean isPalindrome = true;
    
    for(int i = 0; i < aPower / 2; i++) {
    	
    	if(aChars[i] != aChars[aPower - 1 - i]) {
    		isPalindrome = false;
    	}
    	
    }
    
    //System.out.println(isPalindrome);
    
    while(!isPalindrome) {
    	temp += 1;
    	isPalindrome = true;
    	
    	aChars = (temp + "").toCharArray();
    			
		for(int i = 0; i < aPower / 2; i++) {
	    	
	    	if(aChars[i] != aChars[aPower - 1 - i]) {
	    		isPalindrome = false;
	    		break;
	    	}
	    	
	    }
    }
    
    System.out.println(aPower + " " + temp);
    
    ArrayList<Integer> palindromes = new ArrayList<Integer>();
    
    generatePalindromes(palindromes, (temp + "").toCharArray(), b);
    
    fin.close();
    fout.close();
    
	}
}