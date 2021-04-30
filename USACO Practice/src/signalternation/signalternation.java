//package signalternation;

import java.util.*;
import java.io.*;

public class signalternation {
	
	static ArrayList<ArrayList<Integer>> tree;
	
	public static void changeValue(int index, int value) {
		tree.get(0).set(index, value);
		for(int i = 1; i < tree.size(); i++) {
			index /= 2;
			int a = tree.get(i - 1).get(index * 2);
			int b = tree.get(i - 1).get(index * 2 + 1);
			tree.get(i).set(index, a + b);
		}
	}
	
	public static int getSumInRange(int high, int low) {	//high and low inclusive
		int sum = 0;
		for(int i = low; i <= high; i += 0) {
			int index = i;
			int layer = 0;
			int increment = 1;
			while(true) {
				int temp = index;
				index /= 2;
				increment *= 2;
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
			sum += tree.get(layer).get(index);
		}
		return sum;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int treeSize = (int) Math.pow(2, Math.ceil(Math.log(n) / Math.log(2)));
		tree = new ArrayList<ArrayList<Integer>>();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < treeSize; i++) {
			int layer = 0;
			int next = 0;
			if(i < n) {
				next = Integer.parseInt(st.nextToken());
			}
			if(i % 2 == 1) {
				next *= -1;
			}
			while(true) {
				if(layer == tree.size()) {
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
					layer++;
				}
				else {
					break;
				}
			}
		}
		int m = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(m -- > 0) {
			st = new StringTokenizer(fin.readLine());
			if(st.nextToken().equals("0")) {
				int index = Integer.parseInt(st.nextToken()) - 1;
				int value = Integer.parseInt(st.nextToken());
				if(index % 2 == 1) {
					value *= -1;
				}
				changeValue(index, value);
			}
			else {
				int low = Integer.parseInt(st.nextToken()) - 1;
				int high = Integer.parseInt(st.nextToken()) - 1;
				int ans = getSumInRange(high, low);
				if(low % 2 == 1) {
					ans *= -1;
				}
				fout.append(ans).append("\n");
			}
		}
		System.out.print(fout);
	}
}
