//package correctingmistakes;

import java.util.*;
import java.io.*;

public class correctingmistakesver1 {
	public static void main(String[] args) throws IOException {
		
		//when you take the letter out of the string from different locations, all of the letters in between those locations are shifted one.
		//before and after the shift are fine. If an entire string is shifted, it is ok.
		//when comparing two strings, we don't know what direction the shift is going to be. Just one direction has to be consistent throughout.
		//to detect when the shift ends, if when trying the shift direction, it returns false, on a valid string, the normal direction is going to be true.
		//if a shift is only 1 character long, then there are two possible answers.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		char[] s = fin.readLine().toCharArray();
		char[] t = fin.readLine().toCharArray();
		boolean left = false;
		boolean right = false;
		boolean shift = false;
		if(false) {
			System.out.println("0");
		}
		else {
			//System.out.println(n);
			boolean isValid = true;
			boolean alreadyShifted = false;
			int shiftLength = 0;
			for(int i = 0; i < n; i++) {
				//System.out.println(s[i] + " " + t[i]);
				if(s[i] == t[i]) {
					if(shift) {
						alreadyShifted = true;
						if(!(left || right)) {	//if left or right werent' consistent
							isValid = false;
							break;
						}
					}
				}
				else {
					shiftLength ++;
					if(alreadyShifted) {
						isValid = false;
						break;
					}
					if(!shift) {
						right = true;
					}
					if(left) {
						if(i - 1 != -1 && s[i] != t[i - 1] && s[i - 1] != t[i - 1]) {
							left = false;
						}
					}
					if(right) {
						if(i + 1 != n && s[i] != t[i + 1] && s[i + 1] != t[i + 1]) {
							right = false;
						}
					}
					if(!shift) {
						left = true;
					}
					shift = true;
					//System.out.println(left + " " + right + " " + s[i] + " " + t[i + 1]);
				}
			}
			
			if(!(left || right)) {
				isValid = false;
			}
			//System.out.println(isValid + " " + left + " " + right);
			if(isValid) {
				System.out.println(shiftLength == 1? "2" : "1");
			}
			else {
				System.out.println("0");
			}
		}
	}
}
