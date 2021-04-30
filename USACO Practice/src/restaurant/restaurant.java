//package restaurant;

import java.util.*;
import java.io.*;

public class restaurant {
	public static void main(String[] args) throws IOException {
		
		//prioritize orders with the earliest end time
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[][] orders = new int[n][2];	//start time, end time
		for(int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			orders[i] = new int[] {Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken())};
		}
		Arrays.sort(orders, (a, b) -> a[1] - b[1]);
		int curTime = -1;
		int ans = 0;
		for(int i = 0; i < n; i += 0) {
			while(i < n && orders[i][0] <= curTime) {
				i ++;
			}
			if(i == n) {
				break;
			}
			ans ++ ;
			curTime = orders[i][1];
		}
		System.out.println(ans);
	}
}
