package campschedule;

import java.util.*;
import java.io.*;

public class campschedulever1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = fin.readLine().toCharArray();
		char[] t = fin.readLine().toCharArray();
		ArrayList<Character> repeat = new ArrayList<Character>();
		repeat.add(t[0]);
		int pointer = 1;	//points where the initial segment ends
		for(int i = 1; i < t.length; i++) {
			if(t[i] != repeat.get((i - pointer) % repeat.size())) {
				for(int j = pointer; j <= i; j++) {
					repeat.add(t[j]);
				}
				pointer = i + 1;
			}
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
		char[] ans = new char[s.length];
		for(int i = 0; i < s.length; i++) {
			if(repeat.get(i % repeat.size()) == '1') {
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
		int ratio = t.length / repeat.size();
		int count = 0;
		for(int i = 0; i < ans.length; i++) {
			if(ans[i] == repeat.get(i % repeat.size())) {
				if(i % repeat.size() == repeat.size() - 1) {
					count ++;
				}
			}
			else {
				break;
			}
		}
		System.out.println(String.valueOf(ans));
	}
}
