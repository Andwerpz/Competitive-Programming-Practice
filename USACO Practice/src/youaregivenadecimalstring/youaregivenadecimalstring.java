//package youaregivenadecimalstring;

import java.util.*;
import java.io.*;

public class youaregivenadecimalstring {
	
	public static int gcd(int a, int b) {
		if(b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}
	
	public static int[] getCost(int a, int b) {
		int gcd = gcd(a, b);
		int lcm = (a == 0 || b == 0)? (a + b) * (a + b) : (a / gcd) * b;
		lcm *= 100;
		int[] dp = new int[lcm + 1];
		Arrays.fill(dp, -1);
		dp[a] = 1;
		dp[b] = 1;
		for(int i = 0; i <= lcm; i++) {
			if(dp[i] != -1) {
				if(i + a <= lcm) {
					dp[i + a] = dp[i + a] == -1? dp[i] + 1 : Math.min(dp[i + a], dp[i] + 1);
				}
				if(i + b <= lcm) {
					dp[i + b] = dp[i + b] == -1? dp[i] + 1 : Math.min(dp[i + b], dp[i] + 1);
				}
			}
		}
		int[] cost = new int[10];
		Arrays.fill(cost, -1);
		for(int i = 0; i <= lcm; i++) {
			if(dp[i] != -1) {
				int which = i % 10;
				int curCost = dp[i];
				cost[which] = cost[which] == -1? curCost : Math.min(cost[which], curCost);
			}
		}
		return cost;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1202B
		
		//first calculate for each combination of x and y, the minimum cost to increase the output from 0 - n, 0 <= n <= 9. Then count how many times you have to do each increment
		//in the string, and then for each x and y, calculate the total cost.
		
		//use dp for the preprocessing, and remember that to go from 0 -> 0 is not free, if a != 0 && b != 0.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int[][][] cost = new int[10][10][10];	//for each combination of number, the cost for getting to the next with offset 0 - 9
		for(int i = 0; i < 10; i++) {
			for(int j = 0; j < 10; j++) {
				//System.out.print(i + " " + j + ": ");
				cost[i][j] = getCost(i, j);
//				for(int k : cost[i][j]) {
//					System.out.print(k + " ");
//				}
//				System.out.println();
			}
		}
		int[] inputCosts = new int[10];
		char[] s = fin.readLine().toCharArray();
		for(int i = 0; i < s.length - 1; i++) {
			int cur = Integer.parseInt(s[i] + "");
			int next = Integer.parseInt(s[i + 1] + "");
			if(next < cur) {
				next += 10;
			}
			//System.out.println(next - cur);
			inputCosts[next - cur] ++;
		}
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < 10; i++) {
			for(int j = 0; j < 10; j++) {
				long sum = 0;
				for(int k = 0; k < 10; k++) {
					if(cost[i][j][k] == -1 && inputCosts[k] != 0) {
						sum = -1;
						break;
					}
					else {
						if(!(cost[i][j][k] <= 1)) {
							sum += ((long) cost[i][j][k] - 1) * ((long) inputCosts[k]);
						}
					}
				}
				fout.append(sum).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
