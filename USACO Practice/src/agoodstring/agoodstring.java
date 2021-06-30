///package agoodstring;

import java.util.*;
import java.io.*;

public class agoodstring {
	
	static char[] s;
	
	public static int minCost(char x, int low, int high) {
		if(high - low == 1) {
			//System.out.println("RETURN " + (x == s[low]? 0 : 1));
			return x == s[low]? 0 : 1;
		}
		int left = 0;
		int right = 0;
		int mid = low + (high - low) / 2;
		for(int i = low; i < mid; i++) {
			if(s[i] != x) {
				left ++;
			}
		}
		for(int i = mid; i < high; i++) {
			if(s[i] != x) {
				right ++;
			}
		}
		
		left += minCost((char) (x + 1), mid, high);
		right += minCost((char) (x + 1), low, mid);
		//System.out.println("LEFT: " + left + " RIGHT: " + right + " " + low + " " + high + " " + x);
		return Math.min(left, right);
	}
	
	public static void main(String[] args) throws IOException {
		
		//1385D
		
		//since n is limited to 2^17, we can do an easy recursive solution. Given a string, find for each the left and right side the cost of changing them to the desired letter.
		//then recursively call the function on the other side; left calls right, and right calls left. If the segment is length 1, then just return the cost of changing 
		//the letter. Complexity is O(n * log(n))
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			s = fin.readLine().toCharArray();
			fout.append(minCost('a', 0, n)).append("\n");
			//System.out.println();
		}
		System.out.print(fout);
	}
}
