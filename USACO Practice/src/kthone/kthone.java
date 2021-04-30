//package kthone;

import java.util.*;
import java.io.*;

public class kthone {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		ArrayList<ArrayList<Integer>> tree = new ArrayList<ArrayList<Integer>>();
		st = new StringTokenizer(fin.readLine());
		int treeSize = (int) (Math.pow(2, Math.ceil(Math.log10(n) / Math.log10(2))));
		for(int i = 0; i < treeSize; i++) {
			int next = 0;
			if(i < n) {
				next = Integer.parseInt(st.nextToken());
			}
			int layer = 0;
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
				int index = Integer.parseInt(st.nextToken());
				if(tree.get(0).get(index) == 0) {
					tree.get(0).set(index, 1);
				}
				else {
					tree.get(0).set(index, 0);
				}
				index /= 2;
				for(int l = 1; l < tree.size(); l++) {
					int a = tree.get(l - 1).get(index * 2);
					int b = tree.get(l - 1).get(index * 2 + 1);
					tree.get(l).set(index, a + b);
					index /= 2;
				}
			}
			else {
				int which = Integer.parseInt(st.nextToken()) + 1;
				int layer = tree.size() - 1;
				int index = 0;
				while(layer != 0) {
					if(tree.get(layer - 1).get(index * 2) >= which) {
						index = index * 2;
					}
					else {
						which -= tree.get(layer - 1).get(index * 2);
						index = index * 2 + 1;
					}
					layer --;
				}
				fout.append(index).append("\n");
			}
		}
		System.out.print(fout);
	}
}
