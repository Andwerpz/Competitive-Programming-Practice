package nezzarandbinarystring;

import java.util.*;
import java.io.*;

public class nezzarandbinarystring {
	
	public static ArrayList<ArrayList<Integer>> tree, lazy;
	public static int curP = 0;
	
	public static void assignToSegment(int l, int r, int val, int layer, int index, int increment) {
		System.out.println(layer + " " + index + " " + l + " " + r);
		int low = index * increment;
		int mid = low + increment / 2;
		int high = low + increment - 1;
		int curVal = lazy.get(layer).get(index);
		if(l == low && r == high) {
			lazy.get(layer).set(index, val);
			return;
		}
		lazy.get(layer).set(index, -1);
		int nextSum = val * (r - l + 1);
		if(curVal != -1) {
			nextSum += increment * curVal;
			tree.get(layer).set(index, nextSum);
		}
		if(l < mid) {
			assignToSegment(l, Math.min(r, mid - 1), val, layer - 1, index * 2, increment / 2);
			if(curVal != 0 && l != low) {
				assignToSegment(low, l - 1, curVal, layer - 1, index * 2, increment / 2);
			}
			if(curVal != 0 && r < mid - 1) {
				assignToSegment(r + 1, mid - 1, curVal, layer - 1, index * 2, increment / 2);
			}
		}
		else if(curVal != 0){
			assignToSegment(low, mid - 1, curVal, layer - 1, index * 2, increment / 2);
		}
		if(r >= mid) {
			assignToSegment(Math.max(l, mid), r, val, layer - 1, index * 2 + 1, increment / 2);
			if(curVal != 0 && r != high) {
				assignToSegment(r + 1, high, curVal, layer - 1, index * 2 + 1, increment / 2);
			}
			if(curVal != 0 && l > mid) {
				assignToSegment(mid, l - 1, curVal, layer - 1, index * 2 + 1, increment / 2);
			}
		}
		else if(curVal != 0) {
			assignToSegment(mid, high, curVal, layer - 1, index * 2 + 1, increment / 2);
		}
	}
	
	public static int getSum(int l, int r) {
		int ans = 0;
		for(int i = l; i <= r; i += 0) {
			int layer = 0;
			int index = i;
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
					layer --;
					increment /= 2;
					break;
				}
			}
			i += increment;
			int curVal = tree.get(layer).get(index);
			for(int j = layer; j < tree.size(); j++) {
				if(lazy.get(j).get(index) != -1) {
					curVal = lazy.get(j).get(index) * increment;
				}
				index /= 2;
			}
			ans += curVal;
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1477B
		
		//try to figure out how to make a lazy propagation segment tree that supports range assignment and range query sum.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			curP = 0;
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int q = Integer.parseInt(st.nextToken());
			char[] s = fin.readLine().toCharArray();
			char[] f = fin.readLine().toCharArray();
			tree = new ArrayList<ArrayList<Integer>>();
			lazy = new ArrayList<ArrayList<Integer>>();
			int treeSize = (int) (Math.pow(2, Math.ceil(Math.log(n) / Math.log(2))));
			for(int i = 0; i < treeSize; i++) {
				int next = 0;
				if(i < n) {
					next = f[i] == '1'? 1 : 0;
				}
				int layer = 0;
				while(true) {
					if(tree.size() == layer) {
						tree.add(new ArrayList<Integer>());
					}
					if(layer == 0) {
						tree.get(layer).add(next);
					}
					else {
						int size = tree.get(layer - 1).size();
						int a = tree.get(layer - 1).get(size - 1);
						int b = tree.get(layer - 1).get(size - 2);
						tree.get(layer).add(a + b);
					}
					if(tree.get(layer).size() % 2 == 0) {
						layer ++;
					}
					else {
						break;
					}
				}
			}
			int pointer = treeSize;
			while(pointer != 0) {
				lazy.add(new ArrayList<Integer>());
				for(int i = 0; i < pointer; i++) {
					lazy.get(lazy.size() - 1).add(-1);
				}
				pointer /= 2;
			}
			boolean isValid = true;
			int[][] queries = new int[q][2];
			for(int i = 0; i < q; i++) {
				st = new StringTokenizer(fin.readLine());
				int l = Integer.parseInt(st.nextToken()) - 1;
				int r = Integer.parseInt(st.nextToken()) - 1;
				queries[i][0] = l;
				queries[i][1] = r;
			}
			for(int i = q - 1; i >= 0; i--) {
				System.out.println(tree + "\n" + lazy);
				int l = queries[i][0];
				int r = queries[i][1];
				int diff = r - l + 1;
				int sum = getSum(l, r);
				if(sum * 2 > diff) {
					assignToSegment(l, r, 1, tree.size() - 1, 0, treeSize);
				}
				else if(sum * 2 < diff) {
					assignToSegment(l, r, 0, tree.size() - 1, 0, treeSize);
				}
				else {
					isValid = false;
					break;
				}
			}
			for(int i = 0; i < n; i++) {
				int val = getSum(i, i);
				if(val == 1 && s[i] != '1' || val == 0 && s[i] != '0') {
					isValid = false;
					break;
				}
			}
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}