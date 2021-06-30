//package playlist;

import java.util.*;
import java.io.*;

public class playlist {
	public static void main(String[] args) throws IOException {
		
		//1140C
		
		//since the beauty assigned to the whole group is equal to the minimum beauty, we can just pick an assigned minimum, and try to prioritize getting the most
		//length for all other songs. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int[][] songs = new int[n][2];
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			songs[i][0] = Integer.parseInt(st.nextToken());
			songs[i][1] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(songs, (a, b) -> a[1] - b[1]);
		PriorityQueue<Integer> set = new PriorityQueue<Integer>((a, b) -> Integer.compare(a, b));
		long ans = 0;
		long sum = 0;
		for(int i = n - 1; i >= 0; i--) {
			sum += songs[i][0];
			set.add(songs[i][0]);
			while(set.size() > k) {
				sum -= set.poll();
			}
			ans = Math.max(ans, sum * (long)songs[i][1]);
		}
		System.out.println(ans);
	}
}	
