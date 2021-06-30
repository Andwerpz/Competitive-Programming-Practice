//package messy;

import java.util.*;
import java.io.*;

public class messy {
	
	static char[] s;
	
	public static void reverse(int l, int r) {	//l and r inclusive
		Stack<Character> replace = new Stack<Character>();
		for(int i = l; i <= r; i++) {
			replace.push(s[i]);
		}
		for(int i = l; i <= r; i++) {
			s[i] = replace.pop();
		}
	}
	
	public static String goFor(int l, char a) {
		for(int i = l + 1; i < s.length; i++) {
			if(s[i] == a) {
				reverse(l, i);
				return (l + 1) + " " + (i + 1) + "\n";
			}
		}
		return null;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1227C
		
		//just go down the line, and reverse whenever you need to replace a bracket. Since you get n reversals, you will always have enough to replace all brackets.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			s = fin.readLine().toCharArray();
			int pointer = 0;
			StringBuilder cur = new StringBuilder();
			int ans = 0;
			for(int i = 0; i < k - 1; i++) {
				if(s[pointer] != '(') {
					ans ++;
					cur.append(goFor(pointer, '('));
				}
				pointer ++;
				if(s[pointer] != ')') {
					ans ++;
					cur.append(goFor(pointer, ')'));
				}
				pointer ++;
			}
			int numLeft = (n - pointer) / 2;
			//System.out.println(numLeft + " " + pointer);
			for(int i = 0; i < numLeft; i++) {
				if(s[pointer] != '(') {
					ans ++;
					cur.append(goFor(pointer, '('));
				}
				pointer ++;
			}
			for(int i = 0; i < numLeft; i++) {
				if(s[pointer] != ')') {
					ans ++;
					cur.append(goFor(pointer, ')'));
				}
				pointer ++;
			}
			fout.append(ans).append("\n");
			fout.append(cur);
			//System.out.println(String.valueOf(s));
		}
		System.out.print(fout);
	}
}
