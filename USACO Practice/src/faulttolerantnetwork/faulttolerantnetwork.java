//package faulttolerantnetwork;

import java.util.*;
import java.io.*;

public class faulttolerantnetwork {
	public static void main(String[] args) throws IOException {
		
		//1651C
		
		//notice that in order for the network to be fault tolerant, you need to only connect the ends of the
		//two sides to the other side. 
		
		//since each end has 3 possiblities as to where to connect: first / last of other side or number
		//with min dist on other side, you can just brute force through the 4^3 combinations
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] a = new int[n];
			int[] b = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				a[i] = Integer.parseInt(st.nextToken());
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				b[i] = Integer.parseInt(st.nextToken());
			}
			int[][] cost = new int[4][3];
			cost[0][0] = Math.abs(a[0] - b[0]);	cost[0][2] = Math.abs(a[0] - b[n - 1]);
			cost[1][0] = Math.abs(a[n - 1] - b[0]);	cost[1][2] = Math.abs(a[n - 1] - b[n - 1]);
			cost[2][0] = Math.abs(a[0] - b[0]);	cost[2][2] = Math.abs(a[n - 1] - b[0]);
			cost[3][0] = Math.abs(a[0] - b[n - 1]); cost[3][2] = Math.abs(a[n - 1] - b[n - 1]);
			cost[0][1] = Integer.MAX_VALUE;
			cost[1][1] = Integer.MAX_VALUE;
			cost[2][1] = Integer.MAX_VALUE;
			cost[3][1] = Integer.MAX_VALUE;
			for(int i = 1; i < n - 1; i++) {
				cost[0][1] = Math.min(cost[0][1], Math.abs(a[0] - b[i]));
				cost[1][1] = Math.min(cost[1][1], Math.abs(a[n - 1] - b[i]));
				cost[2][1] = Math.min(cost[2][1], Math.abs(b[0] - a[i]));
				cost[3][1] = Math.min(cost[3][1], Math.abs(b[n - 1] - a[i]));
			}
			long ans = Long.MAX_VALUE;
			for(int a0 = 0; a0 < 3; a0++){
				for(int an = 0; an < 3; an++) {
					for(int b0 = 0; b0 < 3; b0++) {
						for(int bn = 0; bn < 3; bn++) {
							long curAns = cost[0][a0] + cost[1][an];
							if(!((a0 == 0 && b0 == 0) || (an == 0 && b0 == 2))){
								curAns += cost[2][b0];
							}
							if(!((a0 == 2 && bn == 0) || (an == 2 && bn == 2))) {
								curAns += cost[3][bn];
							}
							ans = Math.min(ans, curAns);
						}
					}
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
