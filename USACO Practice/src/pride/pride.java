//package pride;

import java.util.*;
import java.io.*;

public class pride {
	
	public static int gcd(int a, int b) {
		int ans = 1;
		if(a == b) {
			return a;
		}
		for(int i = 2; i <= Math.min(a, b); i++) {
			while(a % i == 0 && b % i == 0) {
				//System.out.println(a + " " + b);
				ans *= i;
				a /= i;
				b /= i;
			}
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//if you are able to make a 1, the number of moves remaining is just the remaining amount of numbers that aren't 1's
		//make a dp[l][r] where you consider the segment starting at l and ending at r. For each entry, save the gcd of the segment. 
		//if there is an entry with a gcd of 1, then the answer is the size of segment + size of the array - 1
		//else, print -1
		//dp[l][r] = gcd(dp[l + 1][r], dp[l][r - 1])
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[][] dp = new int[n][n];
		int ans = 0;
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			dp[i][i] = Integer.parseInt(st.nextToken());
			if(dp[i][i] == 1) {
				ans --;
			}
		}
		if(ans < 0) {
			System.out.println(ans + n);
		}
		else {
			boolean ansFound = false;
			for(int i = 1; i < n; i++) {
				for(int j = i; j < n; j++) {
					//System.out.println(j - i + " " + j);
					dp[j - i][j] = gcd(dp[(j - i) + 1][j], dp[j - i][j - 1]);
					if(dp[j - i][j] == 1) {
						//System.out.println(dp[j - i][j]);
						ans = i;
						ansFound = true;
						break;
					}
				}
				if(ansFound) {
					break;
				}
			}
//			for(int[] i : dp) {
//				for(int j : i) {
//					System.out.print(j + " " );
//				}
//				System.out.println();
//			}
			if(ansFound) {
				System.out.println(ans + (n - 1));
			}
			else {
				System.out.println(-1);
			}
			
		}
		
	}
}
