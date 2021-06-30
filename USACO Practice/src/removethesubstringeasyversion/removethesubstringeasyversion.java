//package removethesubstringeasyversion;

import java.util.*;
import java.io.*;

public class removethesubstringeasyversion {
	public static void main(String[] args) throws IOException {
		
		//1203D1
		
		//first notice that the substring that you remove from s has to be in between two of the letters from the subsequence made by t. 
		//since the string lengths are so small, you can just test each combination of prefix and suffix of t, and take the maximum gap
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = fin.readLine().toCharArray();
		String t = fin.readLine();
		int max = 0;
		for(int i = 0; i <= t.length(); i++) {
			char[] begin = t.substring(0, i).toCharArray();
			char[] end = t.substring(i).toCharArray();
			//System.out.println("BEGIN: " + String.valueOf(begin) + " END: " + String.valueOf(end));
			int b = 0;
			int e = s.length - 1;
			for(int j = 0; j < begin.length; j++) {
				while(s[b] != begin[j]) {
					b ++;
				}
				if(j != begin.length - 1) {
					b ++;
				}
			}
			for(int j = end.length - 1; j >= 0; j--) {
				while(s[e] != end[j]) {
					//System.out.println("less");
					e --;
				}
				if(j != 0) {
					e--;
				}
			}
			//System.out.println(b + " " + e);
			int cur = e - b - 1;
			if(i == 0 || i == t.length()) {
				cur ++;
			}
			//System.out.println(cur);
			max = Math.max(max, cur);
		}
		System.out.println(max);
	}
}
