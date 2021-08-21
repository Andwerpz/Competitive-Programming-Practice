//package boboniuchatswithdu;

import java.util.*;
import java.io.*;

public class boboniuchatswithdu {
	public static void main(String[] args) throws IOException {
		
		//1394A
		
		//this one took 11 attempts... why didnt' the dp solution work :((
		
		//For each amount of small numbers that you choose: 0 -> n, find out how many big numbers you can choose.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int d = Integer.parseInt(st.nextToken());
		long m = Integer.parseInt(st.nextToken());
		ArrayList<Long> small = new ArrayList<Long>();
		ArrayList<Long> large = new ArrayList<Long>();
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			long next = Integer.parseInt(st.nextToken());
			if(next <= m) {
				small.add(next);
			}
			else {
				large.add(next);
			}
		}
		small.sort((a, b) -> -Long.compare(a, b));
		large.sort((a, b) -> -Long.compare(a, b));
		//System.out.println(small + "\n" + large);
		for(int i = 1; i < small.size(); i++) {
			small.set(i, small.get(i) + small.get(i - 1));
		}
		for(int i = 1; i < large.size(); i++) {
			large.set(i, large.get(i) + large.get(i - 1));
		}
		long ans = 0;
		
		if(small.size() == 0) {
			ans = large.get((int) (n / (d + 1)) + ((n) % (d + 1) == 0? -1 : 0));
		}
		else {
			for(int i = -1; i < small.size(); i++) {
				if(n - i - 1 >= large.size()) {
					long smallSum = i == -1? 0 : small.get(i);
					long largeSum = 0;
					if(large.size() != 0) {
						largeSum = large.get(Math.min((n - i - 1) / (d + 1) + ((n - i - 1) % (d + 1) == 0? -1 : 0), large.size() - 1));
					}
					//System.out.println(smallSum + " " + largeSum);
					ans = Math.max(ans, largeSum + smallSum);
				}
			}
		}
		System.out.println(ans);
	}
}
