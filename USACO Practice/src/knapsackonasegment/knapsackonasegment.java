//package knapsackonasegment;

import java.util.*;
import java.io.*;

public class knapsackonasegment {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		long s = Long.parseLong(st.nextToken());
		int[] cost = new int[n];
		int[] weight = new int[n];
		long costSum = 0;
		long weightSum = 0;
		long max = 0;
		int low = 0;
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			weight[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			cost[i] = Integer.parseInt(st.nextToken());
		}
		for(int i = 0; i < n; i++) {
			costSum += cost[i];
			weightSum += weight[i];
			while(weightSum > s) {
				weightSum -= weight[low];
				costSum -= cost[low];
				low++;
			}
			if(costSum > max) {
				max = costSum;
			}
		}
		System.out.println(max);
	}
}
