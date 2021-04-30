//package applyingmaxtosegment;

import java.util.*;
import java.io.*;

public class applyingmaxtosegment {
	
	static ArrayList<ArrayList<Integer>> tree;
	
	public static void maxToRange(int low, int high, int value) {	//low inclusive, high exclusive
		for(int i = low; i < high; i += 0) {
			int index = i;
			int layer = 0;
			int increment = 1;
			while(true) {
				int temp = index;
				index /= 2;
				layer ++;
				increment *= 2;
				int l = index * increment;
				int h = l + increment;
				if(l < low || h >= high) {
					index = temp;
					layer --;
					i += increment / 2;
					break;
				}
			}
			tree.get(layer).set(index, Math.max(tree.get(layer).get(index), value));
		}
	}
	
	public static int getValue(int index) {
		int ans = 0;
		for(int i = 0; i < tree.size(); i++) {
			ans = Math.max(tree.get(i).get(index), ans);
			index /= 2;
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int treeSize = (int) Math.pow(2, Math.ceil(Math.log(n) / Math.log(2)));
		tree = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < treeSize; i++) {
			int layer = 0;
			while(true) {
				if(layer == tree.size()) {
					tree.add(new ArrayList<Integer>());
				}
				tree.get(layer).add(0);
				if(tree.get(layer).size() % 2 == 0) {
					layer ++;
				}
				else {
					break;
				}
			}
		}
		StringBuilder fout = new StringBuilder();
		while(m -- > 0) {
			st = new StringTokenizer(fin.readLine());
			if(st.nextToken().equals("1")) {
				int low = Integer.parseInt(st.nextToken());
				int high = Integer.parseInt(st.nextToken());
				int value = Integer.parseInt(st.nextToken());
				maxToRange(low, high, value);
			}
			else {
				fout.append(getValue(Integer.parseInt(st.nextToken()))).append("\n");
			}
		}
		System.out.print(fout);
	}
}
