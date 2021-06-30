//package potionshardversion;

import java.util.*;
import java.io.*;

public class potionshardversion {
	
	static ArrayList<ArrayList<Node>> tree;
	
	public static long getMin(int layer, int index) {
		long min = tree.get(layer).get(index).min;
		for(int i = layer + 1; i < tree.size(); i++) {
			index /= 2;
			min += tree.get(i).get(index).add;
		}
		return min;
	}
	
	public static void addToMin(int layer, int index, long val) {
		tree.get(layer).get(index).min += val;
		tree.get(layer).get(index).add += val;
		for(int i = layer + 1; i < tree.size(); i++) {
			index /= 2;
			int a = index * 2;
			int b = a + 1;
			tree.get(i).get(index).min = Math.min(tree.get(i - 1).get(a).min, tree.get(i - 1).get(b).min) + tree.get(i).get(index).add;
		}
	}
	
	public static long getMinInRange(int low, int high) {
		long min = Long.MAX_VALUE;
		for(int i = low; i <= high; i += 0) {
			int layer = 0;
			int index = i;
			int increment = 1;
			while(true) {
				layer ++;
				increment *= 2;
				int temp = index;
				index /= 2;
				int l = index * increment;
				int h = l + increment - 1;
				if(l < low || h > high) {
					index = temp;
					layer --;
					increment /= 2;
					break;
				}
			}
			i += increment;
			min = Math.min(min, getMin(layer, index));
		}
		return min;
	}
	
	public static void setMinInRange(int low, int high, long val) {
		for(int i = low; i <= high; i += 0) {
			int layer = 0;
			int index = i;
			int increment = 1;
			while(true) {
				layer ++;
				increment *= 2;
				int temp = index;
				index /= 2;
				int l = index * increment;
				int h = l + increment - 1;
				if(l < low || h > high) {
					//System.out.println("RANGE: " + l + " " + h);
					index = temp;
					layer --;
					increment /= 2;
					break;
				}
				
			}//System.out.println(increment);
			i += increment;
			addToMin(layer, index, val);
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		long[] health = new long[n];
		ArrayList<long[]> negatives = new ArrayList<long[]>();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int ans = 0;
		for(int i = 0; i < n; i++) {
			long next = Integer.parseInt(st.nextToken());
			if(next >= 0) {
				ans ++;
				health[i] += next;
			}
			else {
				negatives.add(new long[] {next, i});
			}
			if(i != 0) {
				health[i] += health[i - 1];
			}
		}
		negatives.sort((a, b) -> -Long.compare(a[0], b[0]));
		int treeSize = (int) (Math.pow(2, Math.ceil(Math.log(n) / Math.log(2))));
		tree = new ArrayList<ArrayList<Node>>();
		for(int i = 0; i < treeSize; i++) {
			int layer = 0;
			long min = Long.MAX_VALUE / 2;
			if(i < n) {
				min = health[i];
			}
			while(true) {
				if(layer == tree.size()) {
					tree.add(new ArrayList<Node>());
				}
				if(layer == 0) {
					Node node = new Node();
					node.min = min;
					tree.get(0).add(node);
				}
				else {
					Node node = new Node();
					int size = tree.get(layer - 1).size();
					node.min = Math.min(tree.get(layer - 1).get(size - 1).min, tree.get(layer - 1).get(size - 2).min);
					tree.get(layer).add(node);
				}
				if(tree.get(layer).size() % 2 == 0) {
					layer ++;
				}
				else {
					break;
				}
			}
		}
//		for(ArrayList<Node> t : tree) {
//			System.out.println(t);
//		}
//		System.out.println();
		for(long[] next : negatives) {
			int index = (int)next[1];
			//System.out.println(next[0]);
			if(getMinInRange(index, n - 1) >= Math.abs(next[0])) {
				setMinInRange(index, n - 1, next[0]);
				ans ++;
				//System.out.println("SUCCESS");
//				for(ArrayList<Node> t : tree) {
//					System.out.println(t);
//				}
//				System.out.println();
			}
//			else {
//				System.out.println("FAILED");
//			}
//			
		}
		System.out.println(ans);
	}
}

class Node {
	public long add, min;
	public Node() {
		add = 0;
		min = 0;
	}
	public String toString() {
		return "MIN: " + min + " ADD: " + add + ", ";
	}
}
