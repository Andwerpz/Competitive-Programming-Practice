package cereal2;

import java.util.*;
import java.io.*;

public class cereal2 {
	public static void main(String[] args) throws IOException {
		
		//USACO Silver 2022 Feb
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		boolean[] v = new boolean[m];
		boolean[] eaten = new boolean[n];
		int[][] cows = new int[n][2];
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			//next box, cow id, first or second
			cows[i][0] = a;
			cows[i][1] = b;
		}
		StringBuilder fout = new StringBuilder();
		ArrayList<Integer> ans = new ArrayList<Integer>();
		for(int i = 0; i < n; i++) {
			if(!v[cows[i][0]]) {
				eaten[i] = true;
				ans.add(i + 1);
				v[cows[i][0]] = true;
			}
		}
		for(int i = 0; i < n; i++) {
			if(v[cows[i][0]] && !v[cows[i][1]] && !eaten[i]) {
				eaten[i] = true;
				ans.add(i + 1);
				v[cows[i][1]] = true;
			}
		}
		fout.append(ans.size()).append("\n");
		for(int i : ans) {
			fout.append(i).append("\n");
		}
		for(int i = 0; i < n; i++) {
			if(!eaten[i]) {
				fout.append(i + 1).append("\n");
			}
		}
		System.out.print(fout);
	}
}
