//package bigbrush;

import java.util.*;
import java.io.*;

public class bigbrush {
	
	public static void check(int[][] nums, Stack<int[]> s, Stack<int[]> ans, int i, int j) {
		//System.out.println(i + " " + j);
		if(i < 0 || j < 0 || i + 1 >= nums.length || j + 1 >= nums[0].length) {
			return;
		}
		//System.out.println();
		//System.out.println(nums[i][j] + " " + nums[i][j + 1]);
		//System.out.println(nums[i + 1][j] + " " + nums[i + 1][j + 1]);
		int n = -1;
		if(nums[i][j] != -1) {
			n = nums[i][j];
		}
		if(nums[i + 1][j] != -1) {
			if(nums[i + 1][j] != n && n != -1) {
				return;
			}
			n = nums[i + 1][j];
		}
		if(nums[i][j + 1] != -1) {
			if(nums[i][j + 1] != n && n != -1) {
				return;
			}
			n = nums[i][j + 1];
		}
		if(nums[i + 1][j + 1] != -1) {
			if(nums[i + 1][j + 1] != n && n != -1) {
				return;
			}
			n = nums[i + 1][j + 1];
		}
		//System.out.println(n);
		if(n != -1) {
			//System.out.println("YES");
			ans.add(new int[] {i + 1, j + 1, n});
			nums[i][j] = -1;
			nums[i + 1][j] = -1;
			nums[i][j + 1] = -1;
			nums[i + 1][j + 1] = -1;
			s.add(new int[] {i, j});
			s.add(new int[] {i + 1, j});
			s.add(new int[] {i, j + 1});
			s.add(new int[] {i + 1, j + 1});
		}
	}
	
	public static void main(String[] args) throws IOException {
		
		//1638D
		
		//honestly, i didn't think this solution would work
		
		//to solve, you can just work backwards to an empty board.
		
		//first, you have to find a 2x2 square of the same color. Any valid board has to have one, since there
		//always has to be a last brush. 
		
		//Once found, remove the paint from that 2x2 square, and query the newly empty cells. 
		
		//when querying, check if any of the surrounding 2x2 squares could be made into a single color by changing
		//the queried cell's color. When checking, you can also use adjacent blank cells. 
		
		//if you can, then remove the paint, and query each of the new blank cells. Save the move in a stack
		
		//when constructing the answer, you can just reverse the order of your saved moves
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[][] nums = new int[n][m];	//-1 means available color
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			for(int j = 0; j < m; j++) {
				nums[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		Stack<int[]> ans = new Stack<int[]>();
		Stack<int[]> s = new Stack<int[]>();
		//check for squares, and remove them
		for(int i = 0; i < n - 1; i++) {
			for(int j = 0; j < m - 1; j++) {
				if(nums[i][j] == nums[i][j + 1] && nums[i][j] == nums[i + 1][j] && nums[i][j] == nums[i + 1][j + 1] && nums[i][j] != -1) {
					ans.add(new int[] {i + 1, j + 1, nums[i][j]});
					nums[i][j] = -1;
					nums[i + 1][j] = -1;
					nums[i][j + 1] = -1;
					nums[i + 1][j + 1] = -1;
					s.add(new int[] {i, j});
					s.add(new int[] {i + 1, j});
					s.add(new int[] {i, j + 1});
					s.add(new int[] {i + 1, j + 1});
				}
			}
		}
		while(s.size() != 0) {
			int[] next = s.pop();
			int i = next[0];
			int j = next[1];
			check(nums, s, ans, i, j);
			check(nums, s, ans, i - 1, j);
			check(nums, s, ans, i, j - 1);
			check(nums, s, ans, i - 1, j - 1);
		}
		boolean isValid = true;
		outer:
		for(int[] i : nums) {
			for(int j : i) {
				if(j != -1) {
					isValid = false;
					//break outer;
				}
				//System.out.print(j + " ");
			}
			//System.out.println();
		}
		if(!isValid) {
			System.out.println(-1);
			return;
		}
		StringBuilder fout = new StringBuilder();
		fout.append(ans.size()).append("\n");
		while(ans.size() != 0) {
			int[] next = ans.pop();
			fout.append(next[0]).append(" ").append(next[1]).append(" ").append(next[2]).append("\n");
		}
		System.out.print(fout);
	}
}
