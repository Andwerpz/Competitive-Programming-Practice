///package mysteriouspresent;

import java.util.*;
import java.io.*;

public class mysteriouspresent {
	public static void main(String[] args) throws IOException {
		
		//too slow...
		//just use pointers baka
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int w = Integer.parseInt(st.nextToken());
		int h = Integer.parseInt(st.nextToken());
		int[][] e = new int[n][2];	//storing the width and height of all the cards
		int[][] order = new int[n][2];	//order of cards to be processed. cards are sorted in a way that any given card won't be contained by a card before it.
		int[][] dp = new int[n][2];	//for each card, stores the previous card in the maximum chain ending on this card. Also stores the length of given chain
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			order[i] = new int[] {i, Math.max(a, b)};
			e[i] = new int[] {a, b};
			dp[i][0] = -1;
		}
		Arrays.sort(order, (a, b) -> a[1] - b[1]);
		for(int i = 0; i < n; i++) {
			//System.out.println("card number " + i);
			int id = order[i][0];
			if(e[id][0] <= w || e[id][1] <= h) {	//the card doesn't fit inside this envelope.
				continue;
			}
			int max = 0;
			int maxId = -1;
			for(int j = 0; j < i; j++) {
				int nextId = order[j][0];
				//System.out.println("next id " + nextId);
				if(dp[j][1] > max && e[nextId][0] < e[id][0] && e[nextId][1] < e[id][1]) {
					maxId = j;
					max = dp[j][1];
				}
			}
			//System.out.println(maxId);
			if(maxId != -1) {
				dp[i][1] = dp[maxId][1] + 1;
			}
			else {
				dp[i][1] = 1;
			}
			
			dp[i][0] = maxId;
			//System.out.println(dp[i][0] + " " + dp[i][1]);
		}
	
		int max = 0;
		int id = -1;
		for(int i = 0; i < n; i++) {
			if(dp[i][1] > max) {
				max = dp[i][1];
				id = i;
			}
		}
		if(id == -1) {
			System.out.println(0);
		}
		else {
			StringBuilder fout = new StringBuilder();
			int pointer = dp[id][0];
			fout.append(order[id][0] + 1);
			while(pointer != -1) {
				fout.insert(0, (order[pointer][0] + 1) + " ");
				pointer = dp[pointer][0];
			}
			System.out.println(dp[id][1]);
			System.out.println(fout);
		}
		
	}
}
