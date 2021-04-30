package bookshop;

import java.util.*;
import java.io.*;

public class bookshopver1 {
	
	static Node[] dp = new Node[100001];	//for each amount of money remaining, store the amount of pages that you can get
	static int[] pages;
	static int[] costs;
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int x = Integer.parseInt(st.nextToken());
		pages = new int[n];
		costs = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			costs[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			pages[i] = Integer.parseInt(st.nextToken());
		}
		for(int i = 0; i < dp.length; i++) {
			dp[i] = new Node();
			int ans = dp[i == 0? 0 : (i - 1)].pages;
			int book = -1;
			int index = i == 0? 0 : (i - 1);
			for(int j = 0; j < n; j++) {
				if(i - costs[j] >= 0 && !dp[i - costs[j]].booksBought.contains(j)) {
					System.out.println("adding book " + j);
					if(ans < dp[i - costs[j]].pages + pages[j]) {
						book = j;
						index = i - costs[j];
					}
					ans = Math.max(ans, dp[i - costs[j]].pages + pages[j]);
				}
			}
			dp[i].pages = ans;
			for(int j : dp[index].booksBought) {
				dp[i].booksBought.add(j);
			}
			dp[i].booksBought.add(book);
			if(i <= 100) {
				System.out.println(dp[i].pages);
			}
		}
		System.out.println(dp[x].pages);
	}
}

class Node {
	
	public HashSet<Integer> booksBought;
	public int pages;
	
	public Node() {
		pages = 0;
		booksBought = new HashSet<Integer>();
	}
	
}
