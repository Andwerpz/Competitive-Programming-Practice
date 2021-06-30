//package fountains;

import java.util.*;
import java.io.*;

public class fountains {
	
	static int[][] pfxC;
	static int[][] pfxD;
	static ArrayList<int[]> coins;
	static ArrayList<int[]> diamonds;
	
	public static int searchC(int val, int low) {	//returns the highest possible beauty only using val amount of currency
		int high = pfxC.length - 1;
		int mid = low + (high - low) / 2;
		int ans = 0;
		while(low <= high) {
			if(pfxC[mid][1] <= val) {
				if(pfxC[mid][0] > ans) {
					ans = pfxC[mid][0];
				}
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		return ans;
	}
	
	public static int searchD(int val, int low) {
		int high = pfxD.length - 1;
		int mid = low + (high - low) / 2;
		int ans = 0;
		while(low <= high) {
			if(pfxD[mid][1] <= val) {
				if(pfxD[mid][0] > ans) {
					ans = pfxD[mid][0];
				}
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//799C
		
		//notice that we can have three different combinations of fountain. We can have two coin, two diamond, or one coin and one diamond. 
		//getting the maximum beauty of one coin and one diamond fountain is simple, just go through the array and search for the maximum possible beauty of each
		//and add them together. Finding the max possible beauty of either two coin or diamond fountains is more difficult, but you can process them separately
		//since at this point they don't affect each other. To find the max, first buy one fountain, and then figure out what is the maximum beauty fountain
		//that you can buy with the remaining money. Doing this naively results in an O(n^2) algorithm, but you can turn this into an O(n * log(n)) by implementing binary search. 
		//Construct a sfx array (i labelled it pfx in the code, my bad) that tells you for each fountain, what is the price you must pay in order to get the current fountains beauty or better.
		//then, since it is strictly non-decreasing, you can just binary search through it every time you do another fountain.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int c = Integer.parseInt(st.nextToken());
		int d = Integer.parseInt(st.nextToken());
		coins = new ArrayList<int[]>();
		diamonds = new ArrayList<int[]>();
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			int b = Integer.parseInt(st.nextToken());
			int p = Integer.parseInt(st.nextToken());
			if(st.nextToken().equals("C")) {
				coins.add(new int[] {b, p});
			}
			else {
				diamonds.add(new int[] {b, p});
			}
		}
		coins.sort((a, b) -> a[0] - b[0]);
		diamonds.sort((a, b) -> a[0] - b[0]);
		pfxC = new int[coins.size()][2];
		pfxD = new int[diamonds.size()][2];
		if(coins.size() != 0) {
			pfxC[pfxC.length - 1][0] = coins.get(coins.size() - 1)[0];
			pfxC[pfxC.length - 1][1] = coins.get(coins.size() - 1)[1];
			for(int i = pfxC.length - 2; i >= 0; i--) {
				pfxC[i][0] = coins.get(i)[0];
				pfxC[i][1] = Math.min(coins.get(i)[1], pfxC[i + 1][1]);
			}
		}
		if(diamonds.size() != 0) {
			
			pfxD[pfxD.length - 1][0] = diamonds.get(diamonds.size() - 1)[0];
			pfxD[pfxD.length - 1][1] = diamonds.get(diamonds.size() - 1)[1];
			
			for(int i = pfxD.length - 2; i >= 0; i--) {
				pfxD[i][0] = diamonds.get(i)[0];
				pfxD[i][1] = Math.min(diamonds.get(i)[1], pfxD[i + 1][1]);
			}
		}
		
		
		int ans = 0;
		if(coins.size() != 0 && diamonds.size() != 0 && searchC(c, 0) != 0 && searchD(d, 0) != 0) {
			ans = searchC(c, 0) + searchD(d, 0);
			
			
		}
		//System.out.println("INITIAL ANS: " + ans);
		for(int i = 0; i < pfxC.length - 1; i++) {
			if(c >= coins.get(i)[1]) {
				int next = searchC(c - coins.get(i)[1], i + 1);
				if(next != 0) {	//can't have it being 0 since we have to have 2 fountains
					ans = Math.max(ans, coins.get(i)[0] + next);
				}
			}
		}
		for(int i = 0; i < pfxD.length; i++) {
			if(d >= diamonds.get(i)[1]) {
				int next = searchD(d - diamonds.get(i)[1], i + 1);
				if(next != 0) {
					ans = Math.max(ans, diamonds.get(i)[0] + next);
				}
			}
		}
		
		System.out.println(ans);
	}
}
