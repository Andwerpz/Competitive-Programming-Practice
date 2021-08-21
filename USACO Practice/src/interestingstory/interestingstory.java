//package interestingstory;

import java.util.*;
import java.io.*;

public class interestingstory {
	
	public static int getAns(int val, int[][] words) {
		Arrays.sort(words, (a, b) -> Integer.compare(a[5] - a[val] * 2, b[5] - b[val] * 2));
		int ans = 0;
		int chosenSum = 0;
		int otherSum = 0;
//		for(int[] i : words) {
//			for(int j : i) {
//				System.out.print(j + " ");
//			}
//			System.out.println();
//		}
//		System.out.println();
		for(int i = 0; i < words.length; i++) {
			chosenSum += words[i][val];
			otherSum += words[i][5] - words[i][val];
			if(chosenSum <= otherSum) {
				break;
			}
			else {
				ans ++;
			}
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1551C
		
		//maximize each letter: 'a' 'b' ... ect. sort words by: chosen letter - rest of letters.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[][] words = new int[n][6];
			for(int i = 0; i < n; i++) {
				char[] s = fin.readLine().toCharArray();
				for(int j = 0; j < s.length; j++) {
					int next = s[j] - 'a';
					words[i][next] ++;
				}
				for(int j = 0; j < words[i].length - 1; j++) {
					words[i][5] += words[i][j];
				}
			}
			int ans = 0;
			for(int i = 0; i < 5; i++) {
				ans = Math.max(ans, getAns(i, words));
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
