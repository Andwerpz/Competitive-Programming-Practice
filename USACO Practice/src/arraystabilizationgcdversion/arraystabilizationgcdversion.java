//package arraystabilizationgcdversion;

import java.util.*;
import java.io.*;

public class arraystabilizationgcdversion {
	
	static ArrayList<ArrayList<Integer>> tree;
	
	public static int gcd(int a, int b) {
		if(b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}
	
	public static int getGcd(int l, int r) {
		int ans = -1;
		for(int i = l; i <= r; i += 0) {
			int index = i;
			int layer = 0;
			int increment = 1;
			while(true) {
				int temp = index;
				index /= 2;
				layer ++;
				increment *= 2;
				int low = index * increment;
				int high = low + increment;
				if(low < l || high > r) {
					index = temp;
					increment /= 2;
					layer --;
					break;
				}
			}
			if(ans == -1) {
				ans = tree.get(layer).get(index);
			}
			else {
				ans = gcd(ans, tree.get(layer).get(index));
			}
			i += increment;
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int treeSize = (int) (Math.pow(2, Math.ceil(Math.log(n) / Math.log(2))));
			tree = new ArrayList<ArrayList<Integer>>();
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < treeSize; i++) {
				int layer = 0;
				int next = 1;
				if(i < n) {
					next = Integer.parseInt(st.nextToken());
				}
				while(true) {
					if(layer == tree.size()) {
						tree.add(new ArrayList<Integer>());
					}
					if(layer == 0) {
						tree.get(0).add(next);
					}
					else {
						int size = tree.get(layer - 1).size();
						int a = tree.get(layer - 1).get(size - 1);
						int b = tree.get(layer - 1).get(size - 2);
						tree.get(layer).add(gcd(a, b));
					}
					if(tree.get(layer).size() % 2 == 0) {
						tree.add(new ArrayList<Integer>());
						layer ++;
					}
					else {
						break;
					}
				}
			}
			int low = 0;
			int high = n;
			int mid = low + (high - low) / 2;
			int ans = high;
			while(low <= high) {
				boolean isValid = true;
				int prev = 0;
				for(int i = 0; i < n; i++) {
					int end = i + mid;
					int gcd = 0;
					if(end >= n) {
						gcd = gcd(getGcd(i, n - 1), getGcd(0, end - n));
						//System.out.println("YES");
					}
					else {
						gcd = getGcd(i, end);
					}//System.out.println(gcd);
					if(i == 0) {
						prev = gcd;
					}
					
					else if(prev != gcd) {
						isValid = false;
						break;
					}
				}
				if(isValid) {
					high = mid - 1;
					ans = Math.min(ans, mid);
				}
				else {
					low = mid + 1;
				}
				//System.out.println(mid + " " + isValid);
				mid = low + (high - low) / 2;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
