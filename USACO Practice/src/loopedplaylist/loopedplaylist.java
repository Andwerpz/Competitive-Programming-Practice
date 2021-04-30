//package loopedplaylist;

import java.util.*;
import java.io.*;

public class loopedplaylist {
	public static void main(String[] args) throws IOException {
		
		//first get the sum of positivity of all the songs in the playlist. If p is greater than this number, then we need to find the shortest subarray that is greater than or equal to the
		//p mod the sum of all positivity.
		
		//when outputting the index, make sure it's 1 indexed
		
		//also when figuring out how many songs to play when doing the remainder, make sure to loop through the playlist more than once to get the subarrays on the edges of the playlist
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		long p = Long.parseLong(st.nextToken());
		long numSongs = 0;
		long total = 0;
		int[] songs = new int[n];
		long sum = 0;
		int low = 0;
		int min = Integer.MAX_VALUE;
		int minIndex = 0;
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			songs[i] = Integer.parseInt(st.nextToken());
			total += songs[i];
		}
		numSongs += (p / total) * n;
		p %= total;
		//System.out.println(p + " " + total);
		for(int i = 0; i <= n * 3 + 1; i++) {
			sum += songs[i % n];
			while(sum - songs[low % n] >= p) {
				sum -= songs[low % n];
				low++;
			}
			if(min > i - low + 1 && sum >= p) {
				min = i - low + 1;
				minIndex = low % n;
			}
		}
		System.out.println((minIndex + 1) + " " + (numSongs + (min == Integer.MAX_VALUE? 0 : min)));
	}
}
