//package cheapdinner;

import java.util.*;
import java.io.*;

public class cheapdinner {
	public static void main(String[] args) throws IOException {
		
		//1487E
		
		//use dp and work backwards. Kind of like box stacking problem. For each meal, find out the minimum cost required to eat that meal in a combo.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		Integer[][] nums = new Integer[4][];
		for(int i = 0; i < 4; i++) {
			nums[i] = new Integer[Integer.parseInt(st.nextToken())];
		}
		for(int i = 0; i < 4; i++) {
			st = new StringTokenizer(fin.readLine());
			for(int j = 0; j < nums[i].length; j++) {
				nums[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		ArrayList<ArrayList<HashSet<Integer>>> badCombinations = new ArrayList<ArrayList<HashSet<Integer>>>();
		for(int i = 0; i < 3; i++) {
			badCombinations.add(new ArrayList<HashSet<Integer>>());
			int size = Integer.parseInt(fin.readLine());
			for(int j = 0; j < nums[i].length; j++) {
				badCombinations.get(i).add(new HashSet<Integer>());
			}
			for(int j = 0; j < size; j++) {
				st = new StringTokenizer(fin.readLine());
				int a = Integer.parseInt(st.nextToken()) - 1;
				int b = Integer.parseInt(st.nextToken()) - 1;
				badCombinations.get(i).get(a).add(b);
			}
		}
		//System.out.println(badCombinations);
		boolean isValid = false;
		long ans = Long.MAX_VALUE;
		long[][][] dp = new long[4][][];
		for(int i = 3; i >= 0; i--) {
			dp[i] = new long[nums[i].length][2];
			if(i == 3) {
				for(int j = 0; j < nums[i].length; j++) {
					dp[i][j][0] = nums[i][j];
					dp[i][j][1] = j;
					//System.out.println(dp[i][j][1]);
				}
				Arrays.sort(dp[i], (a, b) -> Long.compare(a[0], b[0]));
			}
			
			else {
				int pointer = 0;
				while(pointer < dp[i + 1].length && dp[i + 1][pointer][0] == -1) {
					pointer ++;
				}
				for(int j = 0; j < nums[i].length; j++) {
					boolean foundAns = false;
					long curAns = Integer.MAX_VALUE;
					for(int k = pointer; k < nums[i + 1].length; k++) {
						if(!badCombinations.get(i).get(j).contains((int) dp[i + 1][k][1]) && dp[i + 1][k][0] != -1) {
							//System.out.println(dp[i + 1][k][1]);
							foundAns = true;
							curAns = nums[i][j] + dp[i + 1][k][0];
							break;
						}
					}
					if(foundAns) {
						//System.out.println(i + " " + j);
						dp[i][j][0] = curAns;
						if(i == 0) {
							ans = Math.min(ans, curAns);
							isValid = true;
						}
					}
					else {
						dp[i][j][0] = -1;
					}
					dp[i][j][1] = j;
				}
				Arrays.sort(dp[i], (a, b) -> Long.compare(a[0], b[0]));
			}
		}
		System.out.println(isValid? ans : -1);
	}
}
