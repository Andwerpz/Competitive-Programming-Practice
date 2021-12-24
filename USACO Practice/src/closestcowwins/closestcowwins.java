//package closestcowwins;

import java.util.*;
import java.io.*;

public class closestcowwins {
	public static void main(String[] args) throws IOException {
		
		//USACO 2021 December Contest Silver
		
		//i have no idea how to do this one - bruh
		
		//compute the intervals made by nhoj's cows independently. 
		
		//note that the first cow to be placed in an interval will always net more tastieness than the second cow. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int k, m, n;
		StringTokenizer st = new StringTokenizer(fin.readLine());
		k = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		n = Integer.parseInt(st.nextToken());
		int[][] patches = new int[k][2];
		int[] cows = new int[m];
		for(int i = 0; i < k; i++) {
			st = new StringTokenizer(fin.readLine());
			patches[i][0] = Integer.parseInt(st.nextToken());
			patches[i][1] = Integer.parseInt(st.nextToken());
		}
		for(int i = 0; i < m; i++) {
			cows[i] = Integer.parseInt(fin.readLine());
		}
		Arrays.sort(patches, (a, b) -> Integer.compare(a[0], b[0]));
		Arrays.sort(cows);
		ArrayList<I> intervals = new ArrayList<I>();
		int pointer = 0;
		for(int i = 0; i < cows.length; i++) {
			int curPos = cows[i];
			I next = new I(i == 0? 0 : cows[i - 1], curPos);
			long totalT = 0;
			while(pointer < k && patches[pointer][0] < curPos) {
				next.p.add(patches[pointer]);
				totalT += patches[pointer][1];
				pointer ++;
			}
			next.totalT = totalT;
			intervals.add(next);
		}
		//System.out.println("DOINE");
		ArrayList<Long> nums = new ArrayList<Long>();
		for(I i : intervals) {
			int window = (i.end - i.start) / 2;
			int p1 = 0;
			int p2 = 0;
			long firstT = 0;
			long sum = 0;
			while(p1 < i.p.size()) {
				sum += i.p.get(p1)[1];
				while(i.p.get(p1)[0] - window >= i.p.get(p2)[0]) {
					sum -= i.p.get(p2)[1];
					p2 ++;
				}
				firstT = Math.max(sum, firstT);
				p1 ++;
			}
			i.firstT = firstT;
			i.secondT = i.totalT - firstT;
		}
		nums.add(intervals.get(0).totalT);
		if(pointer != patches.length) {
			long sum = 0;
			for(int i = pointer; i < patches.length; i++) {
				sum += patches[i][1];
				//System.out.println("ADD : " + patches[pointer][1]);
			}
			nums.add(sum);
		}
		for(int i = 1; i < intervals.size(); i++) {
			nums.add(intervals.get(i).firstT);
			nums.add(intervals.get(i).secondT);
		}
		nums.sort((a, b) -> -Long.compare(a, b));
		long ans = 0;
		for(int i = 0; i < Math.min(n, nums.size()); i++) {
			ans += nums.get(i);
		}
		System.out.println(ans);
	}
}

class I {
	int start, end;
	long firstT, secondT, totalT;
	ArrayList<int[]> p;
	
	public I(int start, int end) {
		this.start = start;
		this.end = end;
		this.p = new ArrayList<int[]>();
	}
	
	public String toString() {
		return start + " " + end + " " + totalT + " " + firstT + " " + secondT;
	}
}