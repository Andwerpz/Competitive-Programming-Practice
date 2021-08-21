//package integershavefriends;

import java.util.*;
import java.io.*;

public class integershavefriends {
	
	static ArrayList<ArrayList<Long>> tree;
	
	public static long gcd(long a, long b) {
		long temp = 0;
		while(b != 0) {
			temp = b;
			b = a % b;
			a = temp;
		}
		return a;
	}
	
	public static long getGcd(int l, int r) {
		long ans = -1;
		for(int i = l; i <= r; i += 0) {
			int index = i;
			int increment = 1;
			int layer = 0;
			while(true) {
				int temp = index;
				index /= 2;
				increment *= 2;
				layer ++;
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
			int treeSize = (int) (Math.pow(2, Math.ceil(Math.log(n - 1) / Math.log(2))));
			tree = new ArrayList<ArrayList<Long>>();
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long prev = Long.parseLong(st.nextToken());
			for(int i = 0; i < treeSize; i++) {
				long next = 0;
				if(i < n - 1) {
					next = Long.parseLong(st.nextToken());
					long temp = next;
					next = Math.abs(next - prev);
					prev = temp;
				}
				int layer = 0;
				while(true) {
					if(layer == tree.size()) {
						tree.add(new ArrayList<Long>());
					}
					if(layer == 0) {
						tree.get(layer).add(next);
					}
					else {
						int size = tree.get(layer - 1).size();
						long a = tree.get(layer - 1).get(size - 1);
						long b = tree.get(layer - 1).get(size - 2);
						tree.get(layer).add(gcd(a, b));
					}
					if(tree.get(layer).size() % 2 == 0) {
						layer ++;
					}
					else {
						break;
					}
				}
			}
			//System.out.println(tree);
			int ans = 0;
			for(int i = 0; i < n - 1; i++) {
				int low = i;
				int high = n - 2;
				int mid = low + (high - low) / 2;
				int curAns = -1;
				while(low <= high) {
					if(getGcd(i, mid) != 1) {
						if(curAns == -1) {
							curAns = mid;
						}
						else {
							curAns = Math.max(curAns, mid);
						}
						low = mid + 1;
					}
					else {
						high = mid - 1;
					}
					mid = low + (high - low) / 2;
				}
				if(curAns == -1) {
					ans = Math.max(ans, 1);
				}
				else {
					ans = Math.max(ans, curAns - i + 2);
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
