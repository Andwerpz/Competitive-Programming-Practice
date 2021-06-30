//package cleaningthephone;

import java.util.*;
import java.io.*;

public class cleaningthephone {
	public static void main(String[] args) throws IOException {
		
		//1475D
		
		//this problem is like the swords and warhammer problem in RPG Protagonist. You basically are given two groups of objects with varying benefits, but uniform costs
		//and you have to try all combinations in linear time. The important thing is that you don't have to try all combinations, you can just greedily pick the ones
		//with the best benefits from one group. Slowly remove the ones you picked from the first group from the least benefit to the most, and add benefits from the second group when
		//necessary.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			long[][] apps = new long[n][2];	//0 : mem units freed, 1 : convenience points lost
			ArrayList<Long> ones = new ArrayList<Long>();
			ArrayList<Long> twos = new ArrayList<Long>();
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				apps[i][0] = Integer.parseInt(st.nextToken());
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				apps[i][1] = Integer.parseInt(st.nextToken());
				if(apps[i][1] == 1) {
					ones.add(apps[i][0]);
				}
				else {
					twos.add(apps[i][0]);
				}
			}
			ones.sort((a, b) -> -Long.compare(a, b));
			twos.sort((a, b) -> -Long.compare(a, b));
			for(int i = 1; i < ones.size(); i++) {
				ones.set(i, ones.get(i) + ones.get(i - 1));
			}
			for(int i = 1; i < twos.size(); i++) {
				twos.set(i, twos.get(i) + twos.get(i - 1));
			}
			int pointer = -1;
			long ans = -1;
			for(int i = ones.size() - 1; i >= -1; i--) {
				long cur = i != -1? ones.get(i) : 0;
				long cost = i + 1;
				while(pointer + 1 < twos.size() && cur + (pointer == -1? 0 : twos.get(pointer)) < m) {
					pointer ++;
				}
				if(cur + (pointer == -1? 0 : twos.get(pointer)) >= m) {
					cost += (pointer + 1) * 2;
					ans = Math.min(cost, ans == -1? Integer.MAX_VALUE : ans);
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
