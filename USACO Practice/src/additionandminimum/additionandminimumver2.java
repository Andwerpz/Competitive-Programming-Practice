package additionandminimum;

import java.util.*;
import java.io.*;

public class additionandminimumver2 {
	
	public static ArrayList<ArrayList<Node>> tree;
	
	public static void addInRange(int low, int high, int value) {
		System.out.println("constraints: low: " + low + " high: " + high);
		for(int i = low; i < high; i += 0) {
			System.out.println("starting at index : " + i);
			int index = i;
			int increment = 1;
			int layer = 0;
			while(true) {
				int temp = index;
				increment *= 2;
				index /= 2;
				layer ++;
				int l = index * increment;
				int h = l + increment;
				if(l < low || h > high) {
					System.out.println("low: " + l + " high: " + h);
					index = temp;
					i += increment / 2;
					layer --;
					break;
				}
			}
			System.out.println("layer: " + layer + " index: " + index);
			tree.get(layer).get(index).minimum += value;
			tree.get(layer).get(index).add += value;
			index /= 2;
			layer ++;
			for(int j = layer; j < tree.size(); j++) {
				int a = tree.get(j - 1).get(index * 2).minimum;
				int b = tree.get(j - 1).get(index * 2 + 1).minimum;
				tree.get(j).get(index).minimum = Math.min(a, b);
				index /= 2;
			}
		}
	}
	
	public static int getMinimumInRange(int low, int high) {
		int ans = -1;
		for(int i = low; i < high; i += 0) {
			int index = i;
			int increment = 1;
			int layer = 0;
			while(true) {
				int temp = index;
				increment *= 2;
				index /= 2;
				layer ++;
				int l = index * increment;
				int h = l + increment;
				if(l < low || h > high) {
					index = temp;
					i += increment / 2;
					layer --;
					break;
				}
			}
			int next = tree.get(layer).get(index).minimum;
			index /= 2;
			for(int j = layer + 1; j < tree.size(); j++) {
				next += tree.get(j).get(index).add;
				index /= 2;
			}
			ans = Math.min(ans == -1? Integer.MAX_VALUE : ans, next);
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int treeSize = (int) Math.pow(2, Math.ceil(Math.log(n) / Math.log(2)));
		tree = new ArrayList<ArrayList<Node>>();
		for(int i = 0; i < treeSize; i++) {
			int next = Integer.MAX_VALUE;
			int layer = 0;
			if(i < n) {
				next = 0;
			}
			while(true) {
				if(layer == tree.size()) {
					tree.add(new ArrayList<Node>());
				}
				if(layer == 0) {
					tree.get(layer).add(new Node(0, next, 0, 0));
				}
				else {
					int size = tree.get(layer - 1).size();
					int a = tree.get(layer - 1).get(size - 2).minimum;
					int b = tree.get(layer - 1).get(size - 1).minimum;
					tree.get(layer).add(new Node(0, Math.min(a, b), a, b));
				}
				if(tree.get(layer).size() % 2 == 0) {
					layer ++;
				}
				else {
					break;
				}
			}
		}
		while(m-- > 0) {
			st = new StringTokenizer(fin.readLine());
			if(st.nextToken().equals("1")) {
				int low = Integer.parseInt(st.nextToken());
				int high = Integer.parseInt(st.nextToken());
				int value = Integer.parseInt(st.nextToken());
				addInRange(low, high, value);
				for(ArrayList<Node> i : tree) {
					for(Node j : i) {
						System.out.print(j.minimum + " ");
					}
					System.out.println();
				}
			}
			else {
				int low = Integer.parseInt(st.nextToken());
				int high = Integer.parseInt(st.nextToken());
				fout.append(getMinimumInRange(low, high)).append("\n");
			}
		}
		System.out.print(fout);
	}
}

class Node {
	
	public int add;
	public int minimum;
	
	public Node(int add, int minimum, int a, int b) {
		this.add = add;
		this.minimum = minimum;
	}
	
}
