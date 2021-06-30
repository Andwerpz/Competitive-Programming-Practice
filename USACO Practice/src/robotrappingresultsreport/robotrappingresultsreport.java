//package robotrappingresultsreport;

import java.util.*;
import java.io.*;

public class robotrappingresultsreport {
	
	static ArrayList<ArrayList<int[]>> c;
	static int[][] order;
	
	public static int initialSearch(int[] dp, int node) {	//determining whether we can make a consistent order with the stuff we're given
		int ans = 0;
		if(dp[node] != -1) {
			return dp[node];
		}
		if(c.get(node).size() == 0) {
			dp[node] = 0;
			return 0;
		}
		for(int i = 0; i < c.get(node).size(); i++) {
			int nextNode = c.get(node).get(i)[0];
			if(dp[nextNode] != -1) {
				ans = Math.max(dp[nextNode], ans);
			}
			else {
				ans = Math.max(initialSearch(dp, nextNode), ans);
			}
		}
		dp[node] = ans + 1;
		return ans + 1;
	}
	
	public static int search(int[] dp, int node, int amount) {	//now trying to minimize the amount of battles required.
		int ans = 0;
		if(dp[node] != -1) {
			return dp[node];
		}
		int count = 0;
		for(int i = 0; i < c.get(node).size(); i++) {
			int nextNode = c.get(node).get(i)[0];
			if(dp[nextNode] != -1 && c.get(node).get(i)[1] <= amount) {
				count ++;
				ans = Math.max(dp[nextNode], ans);
			}
			else if(c.get(node).get(i)[1] <= amount){
				count ++;
				ans = Math.max(search(dp, nextNode, amount), ans);
			}
		}
		if(count == 0) {
			dp[node] = 0;
			return 0;
		}
		dp[node] = ans + 1;
		return ans + 1;
	}
	
	public static boolean isValid(int[] dp, int amount) {	//wrapper for the search function
		for(int i = 0; i < order.length; i++) {
			search(dp, order[i][1], amount);
		}
		Arrays.sort(dp);
		boolean isValid = true;
		for(int i = 0; i < order.length; i++) {
			if(dp[i] != i) {
				isValid = false;
			}
		}
		Arrays.fill(dp, -1);
		return isValid;
	}
	
	public static void main(String[] args) throws IOException {
		
		//first, make a directed graph with the players as nodes, and if a player wins against another player
		//you put an edge going from the winning player to the losing player. If the graph gives you one ordering, then starting from the worst player,
		//they should be able to traverse to 0 other people, the next best player traverses to 1, and so on, until the best player being able to traverse
		//to every other person in the graph. To check this, we start from the worst player, and save the number of possible nodes in a dp array. When we visit this node in the future,
		//we just add on that total to the running sum. If a node that we are trying to visit hasn't been visited, then we know that the number of battles
		//that we are trying is invalid. 
		
		//the situation is pretty much a big tree with just one branch with tons of forwards edges. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		c = new ArrayList<ArrayList<int[]>>();
		order = new int[n][2];	//saves the bots order from weakest to strongest.
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<int[]>());
		}
		for(int i = 0; i < m; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			c.get(a).add(new int[] {b, i + 1});
		}
		int[] dp = new int[n];
		Arrays.fill(dp, -1);
		for(int i = 0; i < n; i++) {
			if(dp[i] == -1) {
				initialSearch(dp, i);
			}
			order[i][0] = dp[i];
			order[i][1] = i;
		}
		Arrays.sort(order, (a, b) -> a[0] - b[0]);
		boolean isValid = true;
		for(int i = 0; i < n; i++) {
			if(order[i][0] != i) {
				isValid = false;
				break;
			}
		}
//		for(int[] i : order) {
//			System.out.print(i[0] + " ");
//		}
		//System.out.println();
		//System.out.println("isValid: " + isValid);
		StringBuilder fout = new StringBuilder();
		if(isValid) {
			int high = m;
			int low = 0;
			int mid = low + (high - low) / 2;
			int ans = high;
			Arrays.fill(dp, -1);
			while(low <= high) {
				if(isValid(dp, mid)) {
					if(mid < ans) {
						ans = mid;
					}
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}
				mid = low + (high - low) / 2;
			}
			fout.append(ans + "\n");
		}
		else {
			fout.append("-1\n");
		}
		System.out.print(fout);
	}
}
