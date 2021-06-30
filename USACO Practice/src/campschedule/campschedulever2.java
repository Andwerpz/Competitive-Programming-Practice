package campschedule;

import java.util.*;
import java.io.*;

public class campschedulever2 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = fin.readLine().toCharArray();
		char[] t = fin.readLine().toCharArray();
		HashSet<String> dict = new HashSet<String>();
		String pointer = t[0] + "";
		dict.add(pointer);
		for(int i = 1; i < t.length; i++) {
			pointer += t[i];
			dict.add(pointer);
		}
		int maxSuffix = 0;
		pointer = "";
		for(int i = t.length - 1; i > 0; i--) {	//not >= 0, since that suffix is the entire string
			pointer = t[i] + pointer;
			if(dict.contains(pointer)) {
				//System.out.println(pointer);
				maxSuffix = t.length - i;
			}
		}
		char[] repeat = String.valueOf(t).substring(t.length - (t.length - maxSuffix), t.length).toCharArray();
		if(maxSuffix == 0) {
			repeat = t;
		}
		int numOnes = 0;
		int numZero = 0;
		for(int i = 0; i < s.length; i++) {
			if(s[i] == '1') {
				numOnes ++;
			}
			else {
				numZero ++;
			}
		}
		//System.out.println(String.valueOf(repeat) + " " + maxSuffix);
		char[] ans = new char[s.length];
		for(int i = 0; i < s.length; i++) {
			if(i < t.length) {
				if(t[i % t.length] == '1') {
					if(numOnes != 0) {
						numOnes --;
						ans[i] = '1';
					}
					else {
						numZero --;
						ans[i] = '0';
					}
				}
				else {
					if(numZero != 0) {
						numZero --;
						ans[i] = '0';
					}
					else {
						numOnes --;
						ans[i] = '1';
					}
				}

			}
			else {
				if(repeat[(i - t.length) % repeat.length] == '1') {
					if(numOnes != 0) {
						numOnes --;
						ans[i] = '1';
					}
					else {
						numZero --;
						ans[i] = '0';
					}
				}
				else {
					if(numZero != 0) {
						numZero --;
						ans[i] = '0';
					}
					else {
						numOnes --;
						ans[i] = '1';
					}
				}
			}
		}
		System.out.println(String.valueOf(ans));
	}
}
