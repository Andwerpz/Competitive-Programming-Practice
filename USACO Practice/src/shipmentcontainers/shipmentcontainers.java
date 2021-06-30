package shipmentcontainers;

import java.util.*;
import java.io.*;

public class shipmentcontainers {
	public static void main(String[] args) throws IOException {
		
		//2021 Keep Austin Hacking
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int x = Integer.parseInt(st.nextToken());
		int[][] boxes = new int[n][3];
		int[][] dp = new int[n][x + 1];
		for(int i = 0; i < n; i++) {
			Arrays.fill(dp[i], -1);
			st = new StringTokenizer(fin.readLine());
			boxes[i] = new int[] {Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken())};
		}
		Arrays.sort(boxes, (a, b) -> Integer.compare(Math.max(a[0], a[1]), Math.max(b[0], b[1])));
		for(int i = 0; i < n; i++) {
			int h = boxes[i][2];
			dp[i][h] = 1;
		}
		int ans = 1;
		for(int i = 0; i < n; i++) {
			int[] a = boxes[i];
			for(int j = 0; j < i; j++) {	//a go below b
				int[] b = boxes[j];
				if(a[0] > b[0] && a[1] > b[1]) {
					for(int k = 0; k < dp[j].length; k++) {
						if(dp[j][k] != -1 && k + a[2] <= x) {
							dp[i][k + a[2]] = Math.max(dp[i][k + a[2]], dp[j][k] + 1);
							ans = Math.max(ans, dp[i][k + a[2]]);
						}
					}
				}
			}
		}
		System.out.println(ans);
	}
}
