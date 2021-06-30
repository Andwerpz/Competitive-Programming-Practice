//package minimizetheinteger;

import java.util.*;
import java.io.*;

public class minimizetheinteger {
	public static void main(String[] args) throws IOException {
		
		//1251C
		
		//since you can only switch odds with evens, the subsequence of odds and even numbers can't change, but they can be placed around each other
		//in any order. So the solution is to greedily add the least number from the two sets of odd and even to the front of the number. Continue
		//until you have exhausted both sets.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			ArrayDeque<Integer> evens = new ArrayDeque<Integer>();
			ArrayDeque<Integer> odds = new ArrayDeque<Integer>();
			for(int i = 0; i < s.length; i++) {
				int next = Integer.parseInt(s[i] + "");
				if(next % 2 == 0) {
					evens.push(next);
				}
				else {
					odds.push(next);
				}
			}
			for(int i = 0; i < s.length; i++) {
				if(evens.size() != 0 && odds.size() != 0) {
					if(evens.peekLast() < odds.peekLast()) {
						fout.append(evens.pollLast());
					}
					else {
						fout.append(odds.pollLast());
					}
				}
				else if(evens.size() != 0) {
					fout.append(evens.pollLast());
				}
				else {
					fout.append(odds.pollLast());
				}
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
