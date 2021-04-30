package additionandminimum;

import java.util.*;
import java.io.*;

public class additionandminimumver1 {
	
	static ArrayList<ArrayList<Node>> tree;
	
	public static void addInRange(int low, int high, int value) {	//low inclusive, high exclusive
		for(int i = low; i < high; i += 0) {
			int index = i;
			int layer = 0;
			int increment = 1;
			while(true) {
				int temp = index;
				layer ++;
				increment *= 2;
				index /= 2;
				int l = index * increment;
				int h = l + increment;
				if(l < low || h >= high) {
					index = temp;
					layer --;
					i += increment / 2;
					break;
				}
			}
			tree.get(layer).get(index).add += value;
			int newMin = tree.get(layer).get(index).minimum + value;
			for(int j = layer; j < tree.size() - 1; j++) {
				if(index % 2 == 0) {
					tree.get(j).get(index / 2).a = newMin;
				}
				else {
					tree.get(j).get(index / 2).b = newMin;
				}
				tree.get(j).get(index / 2).recalculate();
				newMin = tree.get(j).get(index / 2).minimum + tree.get(j).get(index / 2).add;
				index /= 2;
			}
		}
	}
	
	public static int getMinimumInRange(int low, int high) {	//low inclusive, high exclusive
		int ans = Integer.MAX_VALUE;
		for(int i = low; i < high; i += 0) {
			int index = i;
			int layer = 0;
			int increment = 1;
			while(true) {
				int temp = index;
				layer ++;
				increment *= 2;
				index /= 2;
				int l = index * increment;
				int h = l + increment;
				if(l < low || h >= high) {
					index = temp;
					layer --;
					i += increment / 2;
					break;
				}
			}
			int min = tree.get(layer).get(index).minimum;
			for(int j = layer; j < tree.size(); j++) {
				min += tree.get(j).get(index).add;
				index /= 2;
			}
			ans = Math.min(ans, min);
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
			int layer = 0;
			int next = Integer.MAX_VALUE;
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
					int a = tree.get(layer - 1).get(size - 1).minimum;
					int b = tree.get(layer - 1).get(size - 2).minimum;
					tree.get(layer).add(new Node(0, Math.min(a, b), b, a));
				}
				if(tree.get(layer).size() % 2 == 0) {
					layer ++;
				}
				else {
					break;
				}
			}
		}
		while(m -- > 0) {
			st = new StringTokenizer(fin.readLine());
			if(st.nextToken().equals("1")) {
				int low = Integer.parseInt(st.nextToken());
				int high = Integer.parseInt(st.nextToken());
				int value = Integer.parseInt(st.nextToken());
				addInRange(low, high, value);
				for(ArrayList<Node> i : tree) {
					for(Node j : i) {
						System.out.print(j.b + " ");
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

