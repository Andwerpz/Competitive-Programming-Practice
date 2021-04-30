//package dreamoonandwifi;

import java.util.*;
import java.io.*;

public class dreamoonandwifi {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] draz = fin.readLine().toCharArray();
		char[] dream = fin.readLine().toCharArray();
		int n = dream.length;
		double[][] dp = new double[n + 1][100];	//dp[i][j] the probability of ending at position j at move i
		dp[0][50] = 1;
		for(int i = 0; i < n; i++) {
			char cur = dream[i];
			for(int j = 1; j < 100 - 1; j++) {
				if(cur == '-') {
					dp[i + 1][j - 1] += dp[i][j];
				}
				else if(cur == '+') {
					dp[i + 1][j + 1] += dp[i][j];
				}
				else {
					double next = dp[i][j] / 2;
					dp[i + 1][j - 1] += next;
					dp[i + 1][j + 1] += next;
					//System.out.println((j + 1) + " " + (j - 1));
					//System.out.println(dp[i + 1][j - 1] + " " + dp[i + 1][j + 1]);
				}
			}
		}
		for(double[] i : dp) {
			for(double j : i) {
				//System.out.print(j + " ");
			}
			//System.out.println();
		}
		int actualPos = 50;
		for(int i = 0; i < n; i++) {
			actualPos += (draz[i] == '+'? 1 : -1);
			//System.out.println(actualPos);
		}
		//System.out.println(actualPos);
		System.out.println(dp[n][actualPos]);
		
	}
}
