//package wifi;

import java.util.*;
import java.io.*;

public class wifi {
	
	public static long query(long[][] tree, int index) {
		long ans = tree[0][index];
		for(int i = 1; i < tree.length; i++) {
			index /= 2;
			ans = Math.min(ans, tree[i][index]);
		}
		return ans;
	}
	
	public static void set(long[][] tree, int l, int r, long val) {
		for(int i = l; i <= r; i += 0) {
			int increment = 1;
			int index = i;
			int layer = 0;
			while(true) {
				int temp = index / 2;
				layer ++;
				increment *= 2;
				if(temp * increment < l || temp * increment + increment > r) {
					layer --;
					increment /= 2;
					break;
				}
				index = temp;
			}
			tree[layer][index] = Math.min(tree[layer][index], val);
			i += increment;
		}
	}
	
	public static void main(String[] args) throws IOException {
		
		//1216F
		
		//interesting solution, never used seg trees as dp array
		
		//notice that we can approach this problem like a dp problem. 1D dp.
		//dp[i] = minimum cost to connect wifi to rooms 1 - i. 
		
		//dp[i] = d[i - 1] + i. General case
		//if router: dp[j] = min(dp[j], dp[i - k - 1] + i); i - k <= j <= i + k. 
		
		//since we need to do a range update, and query it later to update future dp states, the seg tree
		//fits perfectly into this role. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		char[] ac = fin.readLine().toCharArray();
		int treeSize = (int) Math.pow(2, Integer.toBinaryString(n + 1).length() + 1);
		long[][] tree = new long[Integer.toBinaryString(n + 1).length() + 2][];	//range min seg tree
		for(int i = 0; i < tree.length; i++) {
			tree[i] = new long[treeSize];
			treeSize /= 2;
			Arrays.fill(tree[i], Long.MAX_VALUE);
		}
		tree[0][0] = 0;
		for(int i = 1; i <= n; i++) {
			tree[0][i] = Math.min(tree[0][i], tree[0][i - 1] + i);
			if(ac[i - 1] == '1') {
				int l = Math.max(1, i - k);
				int r = Math.min(n, i + k);
				set(tree, l, r, query(tree, l - 1) + i);
			}
		}
		System.out.println(query(tree, n));
	}
}
