//package toytrainsimplified;

import java.util.*;
import java.io.*;

public class toytrainsimplified {
	
	static int n, m;
	
	public static int getAns(int val, ArrayList<PriorityQueue<Integer>> q) {
		int pointer = val;
		int amt = m;
		int ans = 0;
		int[] cargo = new int[n];
		while(amt != 0) {
			if(q.get(pointer).size() != 0) {
				int next = q.get(pointer).poll() % n;
				cargo[next] ++;
			}
			
			amt -= cargo[pointer];
			cargo[pointer] = 0;
			if(amt != 0) {
				ans ++;
			}
			pointer ++;
			pointer %= n;
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1129A1
		
		//just simulate the problem statement. 
		
		//when picking up candies, always take the candy that will take the longest to drop off. This is because it always takes a maximum of 1 revolution to deliver a candy, so in order to 
		//save on time, you want to save the candies that take the least effort for last.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		ArrayList<PriorityQueue<Integer>> q = new ArrayList<PriorityQueue<Integer>>();
		for(int i = 0; i < n; i++) {
			q.add(new PriorityQueue<Integer>((a, b) -> -(a - b)));
		}
		for(int i = 0; i < m; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			if(b < a) {
				b += n;
			}
			q.get(a).add(b);
		}
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < n; i++) {
			ArrayList<PriorityQueue<Integer>> next = new ArrayList<PriorityQueue<Integer>>();
			for(int j = 0; j < n; j++) {
				next.add(new PriorityQueue<Integer>(q.get(j)));
			}
			fout.append(getAns(i, next)).append(" ");
		}
		System.out.print(fout);
	}
}
