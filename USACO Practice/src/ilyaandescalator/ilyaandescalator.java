//package ilyaandescalator;

import java.util.*;
import java.io.*;

public class ilyaandescalator {
	public static void main(String[] args) throws IOException {
		
		//518D
		
		//represent the situation in 2 state dp, for the ith time step, what is the probability of there being j people on the elevator.
		//to get the next state, all you have to do is multiply the current probablity by the base probability. For example, if there is a 0.5 chance that 1 person is on the escalator
		//and the base is 0.2, then in the next step from this state, there will be a 0.1 chance that 2 people are on the escalator and 0.4 that there is still just 1 person. 
		//to get the expected number of people, just go to the time step that you want, multiply the probability by the number of people, and add them all up.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		double p = Double.parseDouble(st.nextToken());
		int t = Integer.parseInt(st.nextToken());
		double[][] dp = new double[t + 1][n + 1];
		dp[0][0] = 1;	//before the first timestep, it is guaranteed that there are 0 people on the elevator.
		for(int i = 0; i < t; i++) {
			for(int j = 0; j <= n; j++) {
				if(dp[i][j] != 0) {
					if(j != n) {
						dp[i + 1][j] += dp[i][j] * (1 - p);
						dp[i + 1][j + 1] += dp[i][j] * p;
						//System.out.println(dp[i + 1][j + 1] + " " + dp[i + 1][j]);
					}
					else {
						dp[i + 1][n] += dp[i][n];
					}
				}
				
			}
		}
//		System.out.println(p);
//		for(double[] i : dp) {
//			for(double j : i) {
//				System.out.print(j + " ");
//			}
//			System.out.println();
//		}
		double ans = 0;
		for(int i = 0; i <= n; i++) {
			ans += dp[t][i] * i;
		}
		System.out.println(ans);
	}
}
