package afraidofthedark;

import java.util.*;
import java.io.*;

public class afraidofthedark {
	
	static long[][] lamps;
	static long x1, y1, x2, y2;
	static int n;
	static ArrayList<ArrayList<long[]>> c;
	
	public static boolean isValid(long s) {
		int mikeId = -1;
		int campId = -1;
		for(int i = 0; i < n; i++) {
			if(Math.abs(x1 - lamps[i][0]) <= s && Math.abs(y1 - lamps[i][1]) <= s) {
				mikeId = i;
				break;
			}
		}
		for(int i = 0; i < n; i++) {
			if(Math.abs(x2 - lamps[i][0]) <= s && Math.abs(y2 - lamps[i][1]) <= s) {
				campId = i;
				break;
			}
		}
		if(mikeId == -1 || campId == -1) {
			return false;
		}
		Stack<Integer> stack = new Stack<Integer>();
		stack.add(mikeId);
		boolean[] v = new boolean[n];
		v[mikeId] = true;
		while(stack.size() != 0) {
			int cur = stack.pop();
			if(cur == campId) {
				return true;
			}
			for(int i = 0; i < c.get(cur).size(); i++) {
				if(i != cur && !v[i] && Math.abs(lamps[cur][0] - lamps[i][0]) <= s * 2 + 1 && Math.abs(lamps[cur][1] - lamps[i][1]) <= s * 2 + 1 &&
						!(Math.abs(lamps[cur][0] - lamps[i][0]) == s * 2 + 1 && Math.abs(lamps[cur][1] - lamps[i][1]) == s * 2 + 1)) {
					v[i] = true;
					stack.push(i);
				}
			}
		}
		return false;
	}
	
	public static void main(String[] args) throws IOException {
		
		//2021 Keep Austin Hacking
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		x1 = Integer.parseInt(st.nextToken());
		y1 = Integer.parseInt(st.nextToken());
		x2 = Integer.parseInt(st.nextToken());
		y2 = Integer.parseInt(st.nextToken());
		n = Integer.parseInt(st.nextToken());
		lamps = new long[n][2];
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			lamps[i] = new long[] {Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken())};
		}
		c = new ArrayList<ArrayList<long[]>>();
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<long[]>());
			for(int j = 0; j < n; j++) {
				c.get(i).add(new long[] {Math.abs(lamps[i][0] - lamps[j][0]), Math.abs(lamps[i][1] - lamps[j][1])});
			}
		}
		long high = (long) (Integer.MAX_VALUE) * 2;
		long low = 0;
		long mid = low + (high - low) / 2;
		long ans = high;
		while(low <= high) {
			if(isValid(mid)) {
				ans = Math.min(ans, mid);
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
			mid = low + (high - low) / 2;
		}
		System.out.println(ans);
	}
}
