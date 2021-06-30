//package decorateappletree;

import java.util.*;
import java.io.*;

public class decorateappletree {
	
	static ArrayList<ArrayList<Integer>> c;
	static int[] dp;
	
	public static int search(int node) {	//finding how many leaf nodes this node can traverse to.
		if(dp[node] != -1) {
			return dp[node];
		}
		if(c.get(node).size() == 0) {
			dp[node] = 1;
			return 1;
		}
		int ans = 0;
		for(int i = 0; i < c.get(node).size(); i++) {
			int nextNode = c.get(node).get(i);
			if(dp[nextNode] != -1) {
				ans += dp[nextNode];
			}
			else {
				ans += search(nextNode);
			}
		}
		dp[node] = ans;
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1056D
		
		//the problem statement is kind of confusing, so i'll explain it here. You are given a tree. You can color the leaves of the tree,
		//(the nodes that have no other connections). A given subtree is considered 'good' if all of its leaves are of a different color. The task is to
		//output for each number of good subtrees from 1 - n, how many colors different colors are required.
		//First we have to conduct a search through the tree to find for each subtree, how many leaves does it have. the number of leaves in a subtree
		//is equal to the number of unique colors it requires to be 'good'. We can basically just construct a pfx array with the cumulative amount of
		//good trees as a function of number of colors. Just iterate through the array once using a two pointer technique, and problem solved.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		c = new ArrayList<ArrayList<Integer>>();
		dp = new int[n];
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<Integer>());
			dp[i] = -1;
		}
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n - 1; i++) {
			int a = Integer.parseInt(st.nextToken()) - 1;
			c.get(a).add(i + 1); 
		}
		search(0);
		int[] pfx = new int[n + 1];
//		for(int i : dp) {
//			System.out.print(i + " ");
//		}
		for(int i = 0; i < n; i++) {
			int next = dp[i];
			pfx[next] ++;
		}
		for(int i = 1; i < n + 1; i++) {
			pfx[i] += pfx[i - 1];
		}
		int index = 0;
		StringBuilder fout = new StringBuilder();
		for(int i = 1; i <= n; i++) {
			while(index + 1 < n + 1 && pfx[index] < i) {
				index ++;
			}
			fout.append(index).append(" ");
		}
		System.out.println(fout);
	}
}
