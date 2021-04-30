//package cellularnetwork;

import java.util.*;
import java.io.*;

public class cellularnetwork {
	
	static int[] cities;
	static int[] towers;
	
	public static boolean isPossible(long r) {
		int t = 0;
		for(int i = 0; i < cities.length; i++) {
			int next = cities[i];
			while(t < towers.length && !(towers[t] - r <= next && towers[t] + r >= next)) {
				//System.out.println(t);
				t ++;
			}
			if(t == towers.length) {
				return false;
			}
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		cities = new int[n];
		towers = new int[m];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			cities[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < m; i++) {
			towers[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(cities);
		Arrays.sort(towers);
		long high = (long) (2 * Math.pow(10, 9));	//gotta remember math.pow
		long low = 0;
		long mid = low + (high - low) / 2;
		long ans = high;
		while(low <= high) {
			//System.out.println(low + " " + high + " " + mid);
			if(isPossible(mid)) {
				if(ans > mid) {
					ans = mid;
				}
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
