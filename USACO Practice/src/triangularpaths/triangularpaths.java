//package triangularpaths;

import java.util.*;
import java.io.*;

public class triangularpaths {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[][] nodes = new int[n + 1][2];
			for(int i = 0; i < 2; i++) {
				StringTokenizer st = new StringTokenizer(fin.readLine());
				for(int j = 0; j < n; j++) {
					nodes[j][i] = Integer.parseInt(st.nextToken());
				}
			}
			nodes[n][0] = 1;
			nodes[n][1] = 1;
			Arrays.sort(nodes, (a, b) -> a[0] - b[0]);
			int ans = 0;
			for(int i = 0; i < n; i++) {
				int leftDist = 0;
				int[] cur = nodes[i];
				int[] next = nodes[i + 1];
				if(cur[0] - cur[1] == next[0] - next[1]) {	//checking if they are on the same rightwards path. Otherwise, rightwards travel is cost free
					//if they are on the same right path, then left cost is free
					if((cur[0] + cur[1]) % 2 == 0) {
						ans += next[0] - cur[0];
					}
					
				}
				
				else {
					leftDist = (next[0] - next[1]) - (cur[0] - cur[1]);
					if((cur[0] + cur[1]) % 2 == 1) {
						ans += 1;
						leftDist --;
					}
					ans += leftDist / 2;
				}
				
				//System.out.println("cur: " + cur[0] + " " + cur[1] + " next: " + next[0] + " " + next[1]);
				//System.out.println(leftDist / 2 + " " + ((cur[0] + cur[1]) % 2 == 1? 1 : 0));
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
