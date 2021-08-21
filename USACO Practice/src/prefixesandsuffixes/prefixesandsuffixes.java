//package prefixesandsuffixes;

import java.util.*;
import java.io.*;

public class prefixesandsuffixes {
	public static void main(String[] args) throws IOException {
		
		//1092C
		
		//my implementation is horrendous, bandaids on top of bandaids
		
		//all you have to do is assume that one substring is the prefix, and then check for consistency with all the other substrings. Since it is guaranteed that all the strings come from one, then
		//there must be one substring that when assumed to be a prefix, that is consistent with all other strings.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int len = Integer.parseInt(fin.readLine());
		int n = len * 2 - 2;
		int[][][] s = new int[n][][];
		for(int i = 0; i < n; i++) {
			s[i] = new int[2][];
			char[] next = fin.readLine().toCharArray();
			s[i][0] = new int[next.length];
			for(int j = 0; j < next.length; j++) {
				s[i][0][j] = next[j];
			}
			s[i][1] = new int[] {i};
		}
		Arrays.sort(s, (a, b) -> a[0].length - b[0].length);
		for(int i = 0; i < n; i++) {
			int[] cur = new int[len];
			int[] test = s[i][0];
			char[] ans = new char[n];
			for(int j = 0; j < test.length; j++) {
				cur[j] = test[j];
			}
			HashSet<Integer> invalid = new HashSet<Integer>();
			for(int j = 0; j < n; j += 2) {
				boolean isValid = true;
				for(int k = 0; k < Math.min(cur.length, s[j][0].length); k++) {
					if(cur[k] != 0 && cur[k] != s[j][0][k]) {
						isValid = false;
						break;
					}
				}
				ans[s[j][1][0]] = (isValid? 'P' : 'S');
				ans[s[j + 1][1][0]] = (isValid? 'S' : 'P');
				//System.out.println(String.valueOf(test));
				if(isValid) {
					invalid.add(j + 1);
					for(int k = 0; k < s[j][0].length; k++) {
						cur[k] = s[j][0][k];
					}
				}
				else {
					invalid.add(j);
					for(int k = 0; k < s[j + 1][0].length; k++) {
						cur[k] = s[j + 1][0][k];
					}
				}
			}
			boolean isValid = true;
			outer:
			for(int j : invalid) {
				for(int k = 0; k < s[j][0].length; k++) {
					if(cur[len - 1 - k] != 0 && cur[len - 1 - k] != s[j][0][s[j][0].length - 1 - k]) {
						isValid = false;
						break outer;
					}
					cur[len - 1 - k] = s[j][0][s[j][0].length - 1 - k]; 
				}
			}
			//System.out.println(ans);
			if(isValid) {
				System.out.println(String.valueOf(ans));
				break;
			}
		}
	}
}
