//package tvshows;

import java.util.*;
import java.io.*;

public class tvshows {
	public static void main(String[] args) throws IOException {
		
		//1061D
		
		//first, sort the shows in ascending order by start time. Then iterate through the shows, keeping track of watched shows endtimes. If a shows start time is after some other shows end time,
		//pick the end time closest to the next shows start time, and see if it is less costly to just keep the tv through the break. If it is, remove that end time, and change the cost,
		//if it isn't just continue like normal.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		long x = Integer.parseInt(st.nextToken());
		long y = Integer.parseInt(st.nextToken());
		long mod = (long) (1e9 + 7);
		int[][] shows = new int[n][2];
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			shows[i][0] = Integer.parseInt(st.nextToken());
			shows[i][1] = Integer.parseInt(st.nextToken());
		}
		long ans = 0;
		TreeMap<Integer, Integer> ends = new TreeMap<Integer, Integer>();
		Arrays.sort(shows, (a, b) -> a[0] - b[0]);
		for(int i = 0; i < n; i++) {
			int start = shows[i][0];
			int end = shows[i][1];
			//System.out.println(start + " " + end);
			//System.out.println(ends);
			ans += x + ((long) (end - start) * y);
			ans %= mod;
			Integer prevEnd = ends.floorKey(start - 1);
			if(prevEnd != null && (start - prevEnd) * y < x) {
				//System.out.println("YES " + prevEnd + " " + start + " " + ((start - prevEnd) * y));
				ans -= x;
				if(ans < 0) {
					ans += mod;
				}
				ans += (start - prevEnd) * y;
				ans %= mod;
				ends.put(prevEnd, ends.get(prevEnd) - 1);
				if(ends.get(prevEnd) == 0) {
					ends.remove(prevEnd);
				}
			}
			ends.put(end, ends.getOrDefault(end, 0) + 1);
		}
		System.out.println(ans);
	}
}
