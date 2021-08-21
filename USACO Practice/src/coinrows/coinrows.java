//package coinrows;

import java.util.*;
import java.io.*;

public class coinrows {
	public static void main(String[] args) throws IOException {
		
		//1555C
		
		//there are m possible games. Pick the game with the lowest maximum score for bob.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int m = Integer.parseInt(fin.readLine());
			int[] pfxTop = new int[m];
			int[] pfxBottom = new int[m];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < m; i++) {
				pfxTop[i] = Integer.parseInt(st.nextToken());
				if(i != 0) {
					pfxTop[i] += pfxTop[i - 1];
				}
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < m; i++) {
				pfxBottom[i] = Integer.parseInt(st.nextToken());
				if(i != 0) {
					pfxBottom[i] += pfxBottom[i - 1];
				}
			}
			int ans = Integer.MAX_VALUE;
			for(int i = 0; i < m; i++) {
				int nextAns = Math.max(pfxTop[m - 1] - pfxTop[i], i == 0? 0 : pfxBottom[i - 1]);
				ans = Math.min(ans, nextAns);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
