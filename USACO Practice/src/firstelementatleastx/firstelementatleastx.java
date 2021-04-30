//package firstelementatleastx;

import java.util.*;
import java.io.*;

public class firstelementatleastx {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int treeSize = (int) (Math.pow(2, Math.ceil(Math.log10(n) / Math.log10(2))));
		ArrayList<ArrayList<Integer>> tree = new ArrayList<ArrayList<Integer>>();
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < treeSize; i++) {
			int next = Integer.MIN_VALUE;
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
					tree.get(layer).add(Math.max(a, b));
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
				int v = Integer.parseInt(st.nextToken());
				tree.get(0).set(index, v);
				index /= 2;
				for(int l = 1; l < tree.size(); l++) {
					int a = tree.get(l - 1).get(index * 2);
					int b = tree.get(l - 1).get(index * 2 + 1);
					tree.get(l).set(index, Math.max(a, b));
					index /= 2;
				}
			}
			else {
				int which = Integer.parseInt(st.nextToken());
				int index = 0;
				for(int l = tree.size() - 1; l > 0; l--) {
					if(tree.get(l - 1).get(index * 2) >= which) {
						index = index * 2;
					}
					else {
						index = index * 2 + 1;
					}
				}
				if(tree.get(0).get(index) < which) {
					fout.append("-1\n");
				}
				else {
					fout.append(index).append("\n");
				}
			}
		}
		System.out.println(fout);
	}
}
