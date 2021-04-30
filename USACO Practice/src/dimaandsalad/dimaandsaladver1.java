package dimaandsalad;

import java.util.*;
import java.io.*;

public class dimaandsaladver1 {
	public static void main(String[] args) throws IOException {
		
		//too slow, since we have to save maxTaste * maxCal slots
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int[] taste = new int[n];
		int[] cal = new int[n];
		int tasteSum = 0;
		int calSum = 0;
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			taste[i] = Integer.parseInt(st.nextToken());
			tasteSum += taste[i];
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			cal[i] = Integer.parseInt(st.nextToken());
			calSum += cal[i];
		}
		boolean[][] dp = new boolean[tasteSum + 1][calSum + 1];	//dp[i][j] where i is taste and j is calories, and save whether or not we can get here
		dp[0][0] = true;
		for(int i = 0; i < n; i++) {	//loop through all fruits
			int curTaste = taste[i];
			int curCal = cal[i];
			for(int r = dp.length - 1 - curTaste; r >= 0; r--) {
				for(int c = dp[r].length - 1 - curCal; c >= 0; c--) {
					if(dp[r][c]) {
						dp[r + curTaste][c + curCal] = true;
					}
				}
			}
		}
		int ans = 0;
		for(int i = 0; i <= calSum; i++) {
			if(i * k > tasteSum) {
				break;
			}
			else {
				if(dp[i * k][i]) {
					ans = i;
				}
			}
		}
		System.out.println(ans == 0? "-1" : (ans * k));
	}
}
