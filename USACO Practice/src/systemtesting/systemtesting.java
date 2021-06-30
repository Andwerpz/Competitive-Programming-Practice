//package systemtesting;

import java.util.*;
import java.io.*;

public class systemtesting {
	
	public static int getPercent(double n, double m) {
		return (int) (Math.floor(100d * ((double)m / (double)n) + 0.5d));
	}
	
	public static void main(String[] args) throws IOException {
		
		//1121C
		
		//just implementation of the problem statement
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int[][] testing = new int[k][3];	//0: time elapsed, 1: total time, 2: is judged to be interesting
		int[] solutions = new int[n];
		int numFinished = 0;
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			solutions[i] = Integer.parseInt(st.nextToken());
		}
		int pointer = 0;
		int ans = 0;
		while(numFinished != n) {
			for(int i = 0; i < k; i++) {
				if(testing[i][0] == testing[i][1]) {
					testing[i][2] = 0;
					if(testing[i][1] != 0) {
						numFinished ++;
					}
					if(pointer == n) {
						testing[i][1] = -1;
						testing[i][0] = -2;
					}
					else {
						testing[i][0] = 1;
						testing[i][1] = solutions[pointer];
						pointer ++;
					}
				}
				else {
					if(testing[i][1] != -1) {
						testing[i][0] ++;
					}
				}
			}
			int percent = getPercent(n, numFinished);
			for(int i = 0; i < k; i++) {
				//System.out.print(testing[i][0] + "/" + testing[i][1] + ", ");
				if(testing[i][0] == percent && testing[i][2] == 0) {
					testing[i][2] = 1;
					ans ++;
					//System.out.print(" Interesting");
				}
			}
			//System.out.println("%" + percent);
		}
		System.out.println(ans);
	}
}
