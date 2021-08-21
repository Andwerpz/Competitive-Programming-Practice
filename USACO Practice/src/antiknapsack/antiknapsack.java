//package antiknapsack;

import java.util.*;
import java.io.*;

public class antiknapsack {
	public static void main(String[] args) throws IOException {
		
		//1493A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int ans = 0;
			StringBuilder curAns = new StringBuilder();
			for(int i = k + 1; i <= n; i++) {
				curAns.append(i).append(" ");
				ans ++;
			}
			if(k == 2) {
				curAns.append(1).append(" ");
				ans ++;
			}
			else if(k == 1) {
				
			}
			else {
				for(int i = k / 2 + (k % 2 == 1? 1 : 0); i < k; i++) {
					curAns.append(i).append(" ");
					ans ++;
				}
			}
			//System.out.println(ans);
			fout.append(ans).append("\n").append(curAns).append("\n");
		}
		System.out.print(fout);
	}
}
