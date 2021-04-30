package concerttickets;

import java.util.*;
import java.io.*;

public class concertticketsver2 {
	public static void main(String[] args) throws IOException {
		
		//have to find a way to deal with the situation that you find a ticket, but it's already been taken in binary search
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[] tickets = new int[n];
		boolean[] v = new boolean[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			tickets[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(tickets);
		StringBuilder fout = new StringBuilder();
		st = new StringTokenizer(fin.readLine());
		while(m-- > 0) {
			int target = Integer.parseInt(st.nextToken());
			int low = 0;
			int high = n - 1;
			int mid = low + (high - low) / 2;
			int ans = -1;
			while(low <= high) {
				if(tickets[mid] <= target && !v[mid]) {
					low = mid + 1;
					if(ans == -1 || ans < mid) {
						ans = mid;
					}
				}
				else {
					high = mid - 1;
				}
				mid = low + (high - low) / 2;
			}
			fout.append(ans == -1? "-1" : tickets[ans]).append("\n");
			if(ans != -1) {
				v[ans] = true;
			}
		}
		System.out.print(fout);
	}
}
