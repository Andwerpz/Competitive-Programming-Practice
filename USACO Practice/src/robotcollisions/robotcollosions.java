//package robotcollisions;

import java.util.*;
import java.io.*;

public class robotcollosions {
	
	static int[] ans;
	static boolean[] v;
	static int m;
	
	public static void solve(int[][] robots) {
		//System.out.println("FUNCTION CALL");
		TreeSet<int[]> left = new TreeSet<int[]>((a, b) -> a[0] - b[0]);
		TreeSet<int[]> right = new TreeSet<int[]>((a, b) -> a[0] - b[0]);
		for(int i = 0; i < robots.length; i++) {
			if(robots[i][1] == 0) {
				left.add(new int[] {robots[i][0], robots[i][2]});
			}
			else {
				right.add(new int[] {robots[i][0], robots[i][2]});
			}
		}
		//System.out.print("LEFT: ");
//		for(int[] i : left) {
//			//System.out.print("[" + i[0] + ", " + i[1] + "] ");
//		}
		//System.out.println();
		//System.out.print("RIGHT: ");
//		for(int[] i : right) {
//			//System.out.print("[" + i[0] + ", " + i[1] + "] ");
//		}
		//System.out.println();
		int[] pointer = new int[] {0, 0};
		while(left.ceiling(pointer) != null) {
			pointer = left.ceiling(pointer);
			////System.out.println(pointer[0] + " " + pointer[1]);
			if(right.floor(pointer) != null) {
				int[] next = right.floor(pointer);
				left.remove(pointer);
				right.remove(next);
				ans[pointer[1]] = (pointer[0] - next[0]) / 2;
				ans[next[1]] = (pointer[0] - next[0]) / 2;
			}
			else {
				pointer = new int[] {pointer[0] + 1, pointer[1]};
			}
		}
		//System.out.println("REMAINING LEFT: " + left.size() + " REMAINING RIGHT: " + right.size());
		while(left.size() > 1) {
			int[] a = left.pollFirst();
			int[] b = left.pollFirst();
			ans[a[1]] = (a[0] + b[0]) / 2;
			ans[b[1]] = (a[0] + b[0]) / 2;
			//System.out.println("LEFTWARDS: " + a[0] + " " + b[0] + " " + v.length);
		}
		while(right.size() > 1) {
			int[] a = right.pollLast();
			int[] b = right.pollLast();
			ans[a[1]] = ((m - a[0]) + (m - b[0])) / 2;
			ans[b[1]] = ((m - a[0]) + (m - b[0])) / 2;
		}
		if(left.size() == 1 && right.size() == 1) {
			
			int[] a = right.pollLast();
			int[] b = left.pollFirst();
			//System.out.println("FINAL CLAUSE: " + (m + (m - a[0])) + " " + b[0] + " " + a[0] + " " + b[0]);
			ans[a[1]] = (m + (m - a[0]) + b[0]) / 2;
			ans[b[1]] = (m + (m - a[0]) + b[0]) / 2;
		}
		//System.out.println();
	}
	
	public static void main(String[] args) throws IOException {
		
		//1525C
		
		//first notice that only robots on even starting coordinates can collide with even robots, and vice versa. So you can split the original set of robots into 
		//evens and odds. For each group, first check if there are any direct collisions; collisions between two robots where neither of them bounce off of the wall. Once all
		//the direct collision robots are removed, this leaves you with all rightwards robots on the right side, and leftwards robots on the left side. Next, you account for the wall,
		//remove robots two by two starting from the wall side. If there is a leftover robot from both the right and left sides, they collide with eachother after bouncing off the wall
		//but if there is only one left, or none left, then you're done.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			m = Integer.parseInt(st.nextToken());
			int[] nums = new int[n];
			char[] directions = new char[n];
			st = new StringTokenizer(fin.readLine());
			StringTokenizer st2 = new StringTokenizer(fin.readLine());
			int numEven = 0;
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				directions[i] = st2.nextToken().charAt(0);
				if(nums[i] % 2 == 0) {
					numEven ++;
				}
			}
			ans = new int[n];
			v = new boolean[n];
			Arrays.fill(ans, -1);
			int[][] next = new int[numEven][3];	//initial position, direction, id
			int pointer = 0;
			//System.out.print("INPUT EVEN: ");
			for(int i = 0; i < n; i++) {
				if(nums[i] % 2 == 0) {
					//System.out.print("{" + nums[i] + ", " + directions[i] + "} ");
					next[pointer][0] = nums[i];
					next[pointer][1] = directions[i] == 'R'? 1 : 0;	//1 for right, 0 for left
					next[pointer][2] = i;
					pointer ++;
				}
			}
			//System.out.println();
			Arrays.sort(next, (a, b) -> a[0] - b[0]);
			solve(next);
			next = new int[n - numEven][3];
			pointer = 0;
			//System.out.print("INPUT ODD: ");
			for(int i = 0; i < n; i++) {
				if(nums[i] % 2 == 1) {
					//System.out.print("{" + nums[i] + ", " + directions[i] + "} ");
					next[pointer][0] = nums[i];
					next[pointer][1] = directions[i] == 'R'? 1 : 0;	//1 for right, 0 for left
					next[pointer][2] = i;
					pointer ++;
				}
			}
			//System.out.println();
			Arrays.sort(next, (a, b) -> a[0] - b[0]);
			solve(next);
			for(int i : ans) {
				fout.append(i).append(" ");
			}
			fout.append("\n");
			////System.out.print(fout);;
		}
		System.out.print(fout);
	}
}
