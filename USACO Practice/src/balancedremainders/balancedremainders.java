//package balancedremainders;

import java.util.*;
import java.io.*;

public class balancedremainders {
	public static void main(String[] args) throws IOException {
		
		//1490B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] remainders = new int[3];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken()) % 3;
				remainders[next] ++;
			}
			int ans = 0;
			int goal = n / 3;
			for(int i = 0; i < 3; i++) {
				if(remainders[i] > goal) {
					int over = remainders[i] - goal;
					remainders[i] = goal;
					for(int j = 1; j <= 2; j++) {
						if(remainders[(i + j) % 3] < goal) {
							int add = Math.min(goal - remainders[(i + j) % 3], over);
							ans += add * j;
							over -= add;
							remainders[(i + j) % 3] += add;
						}
					}
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
