//package permutationgame;

import java.util.*;
import java.io.*;

public class permutationgame {
	
	static int[] dp;
	static int[] nums;
	
	public static void solve(int index) {
		//go through each of the possible moves for the current tile. If there is one move that you can force a win, then you can win on this tile, otherwise
		//the player who moves loses on this tile. To force wins, you look for dp entries of 0, that means that the person who moves on that tile loses.
		//a tile can also be assigned 0 if there are no valid moves for this tile.
		int value = nums[index];
		int pointer = index;
		boolean isValid = false;
		while(pointer - value >= 0) {
			pointer -= value;
			if(nums[pointer] > value && dp[pointer] == 0) {
				dp[index] = 1;
				return;
			}
		}
		pointer = index;
		while(pointer + value < nums.length) {
			pointer += value;
			if(nums[pointer] > value && dp[pointer] == 0) {
				dp[index] = 1;
				return;
			}
		}
		dp[index] = 0;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		nums = new int[n];
		int[][] order = new int[n][2];	//the order in which we process the numbers.
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			order[i] = new int[] {nums[i], i};
		}
		dp = new int[n];//saves who will win if the game was started on this position. 1 for the person who moves wins, 0 if the person who doesn't move wins
		Arrays.fill(dp, -1);	
		Arrays.sort(order, (a, b) -> -(a[0] - b[0]));
		for(int i = 0; i < order.length; i++) {
			solve(order[i][1]);
		}
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < n; i++) {
			fout.append(dp[i] == 1? "A" : "B");
		}
		System.out.println(fout);
	}
}
