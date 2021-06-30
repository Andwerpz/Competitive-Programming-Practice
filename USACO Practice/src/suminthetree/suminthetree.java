//package suminthetree;

import java.util.*;
import java.io.*;

public class suminthetree {
	public static void main(String[] args) throws IOException {
		
		//1098A
		
		//You can't change odd depth nodes. 
		//When encountering an even depth node, set the sum of the node to be equal to the minimum of all of it's connections, and the previous sum if it doesn't have any connections.
		//this will minimize the value since now the load is being put onto one node, instead of being spread out and multiplied across multiple nodes.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<Integer>());
		}
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 1; i < n; i++) {
			int next = Integer.parseInt(st.nextToken()) - 1;
			c.get(next).add(i);
		}
		int[] nums = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		boolean isValid = true;
		long ans = 0;
		Queue<Integer> q = new ArrayDeque<Integer>();
		Queue<Integer> s = new ArrayDeque<Integer>();
		q.add(0);
		s.add(0);
		while(q.size() != 0) {
			int cur = q.poll();
			int prevSum = s.poll();
			int curSum = nums[cur];
			if(curSum == -1 && c.get(cur).size() != 0) {
				curSum = Integer.MAX_VALUE;
				for(int i = 0; i < c.get(cur).size(); i++) {
					curSum = Math.min(curSum, nums[c.get(cur).get(i)]);
				}
			}
			else if(curSum == -1){
				curSum = prevSum;
			}
			if(curSum < prevSum) {
				isValid = false;
				break;
			}
			ans += (long) (curSum - prevSum);
			for(int i = 0; i < c.get(cur).size(); i++) {
				q.add(c.get(cur).get(i));
				s.add(curSum);
			}
			//System.out.println(cur + " " + curSum);
		}
		if(isValid) {
			System.out.println(ans);
		}
		else {
			System.out.println("-1");
		}
	}
}
