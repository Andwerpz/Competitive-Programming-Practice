//package circleofmonsters;

import java.util.*;
import java.io.*;

public class circleofmonsters {
	public static void main(String[] args) throws IOException {
		
		//1334C
		
		//notice that since a monsters health and chain explosion damage is always greater than or equal to 1, you can always kill every monster by lowering all their
		//healths to be able to be killed by the previous one in the line, and then killing one of them. So the optimal solution is to lower all their healths down,
		//and then kill one of them. You can just iterate through all the monsters to find out which one is best to kill.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			long[][] monsters = new long[n][2];	//health and damage dealt on explosion
			for(int i = 0; i < n; i++) {
				StringTokenizer st = new StringTokenizer(fin.readLine());
				monsters[i][0] = Long.parseLong(st.nextToken());
				monsters[i][1] = Long.parseLong(st.nextToken());
			}
			long base = 0;
			for(int i = n; i < n * 2; i++) {
				if(monsters[i % n][0] > monsters[(i - 1) % n][1]) {
					base += monsters[i % n][0] - monsters[(i - 1) % n][1];
					monsters[i % n][0] = monsters[(i - 1) % n][1];
				}
			}
			long ans = base + monsters[0][0];
			for(int i = 0; i < n; i++) {
				ans = Math.min(ans, base + monsters[i][0]);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
