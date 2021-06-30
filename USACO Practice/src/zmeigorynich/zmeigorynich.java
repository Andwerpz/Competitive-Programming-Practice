//package zmeigorynich;

import java.util.*;
import java.io.*;

public class zmeigorynich {
	public static void main(String[] args) throws IOException {
		
		//1217B
		
		//first, we need to get two values, the maximum damage that we can do, and the maximum amount of difference between damage and amount of heads regrown. 
		//If the maximum difference in damage is negative, this means that after we do the damage, we always are left with more heads than we started with. In this case, if
		//we can't do enough damage to reduce the health to 0 on the first round, then we can't kill the dragon. Else, just calculate the number of moves required
		//by just doing the maximum difference in damage move, until you can do the maximum damage move and kill the dragon.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			int[] d = new int[n];
			int[] h = new int[n];
			int[] diff = new int[n];
			int maxD = Integer.MIN_VALUE;
			int maxDiff = Integer.MIN_VALUE;
			for(int i = 0; i < n; i++) {
				st = new StringTokenizer(fin.readLine());
				d[i] = Integer.parseInt(st.nextToken());
				h[i] = Integer.parseInt(st.nextToken());
				diff[i] = d[i] - h[i];
				maxDiff = Math.max(diff[i], maxDiff);
				maxD = Math.max(d[i], maxD);
			}
			if(maxDiff <= 0 && x > maxD) {
				fout.append("-1\n");
			}
			else {
				x -= maxD;
				int ans = 1 + (x > 0? (x / maxDiff) + (x % maxDiff == 0? 0 : 1): 0);
				fout.append(ans).append("\n");
			}
		}
		System.out.print(fout);
	}
}
