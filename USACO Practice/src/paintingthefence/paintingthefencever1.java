package paintingthefence;

import java.util.*;
import java.io.*;

public class paintingthefencever1 {
	public static void main(String[] args) throws IOException {
		
		//this algorithm is too greedy.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(fin.readLine());
		int q = Integer.parseInt(fin.readLine());
		int[] alone = new int[q];
		int[][] times = new int[q * 2][2];
		for(int i = 0; i < q; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			times[i][0] = a;
			times[i + q][0] = b;
			times[i][1] = i;
			times[i + q][1] = i;
		}
		Arrays.sort(times, (a, b) -> a[0] - b[0]);
		HashSet<Integer> active = new HashSet<Integer>();
		int totalActive = 0;
		int prev = times[0][0];
		for(int i = 0; i < times.length; i++) {
			int timeElapsed = times[i][0] - prev;
			prev = times[i][0];
			if(active.size() != 0) {
				totalActive += timeElapsed;
			}
			if(active.size() == 1) {
				for(int id : active) {
					alone[id] += timeElapsed;
				}
			}
			int id = times[i][1];
			if(active.contains(id)) {
				active.remove(id);
			}
			else {
				active.add(id);
			}
			while(times[i + 1][0] == prev) {
				i ++;
				id = times[i][1];
				if(active.contains(id)) {
					active.remove(id);
				}
				else {
					active.add(id);
				}
			}
		}
		Arrays.sort(alone);
		int subtract = alone[0];
		Arrays.fill(alone, 0);
		
	}
}
