//package segmenttreeforthesum;

import java.util.*;
import java.io.*;

public class segmenttreeforthesum {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int treeSize = (int) Math.pow(2, Math.ceil(Math.log10(n) / Math.log10(2)));
		st = new StringTokenizer(fin.readLine());
		ArrayList<ArrayList<Long>> tree = new ArrayList<ArrayList<Long>>();	//use an arraylist to represent the tree, the lowest level is 0, and it goes up
		//to access the parent node from a child, just divide the index by 2, int division is pretty handy
		for(int i = 0; i < treeSize; i++) {
			int layer = 0;
			int next = 0;
			if(!(i >= n)) {
				next = Integer.parseInt(st.nextToken());
			}
			boolean done = false;
			while(!done) {
				if(tree.size() == layer) {
					tree.add(new ArrayList<Long>());
				}
				if(layer == 0) {
					tree.get(0).add((long) next);
				}
				else {
					int size = tree.get(layer - 1).size();
					tree.get(layer).add(tree.get(layer - 1).get(size - 1) + tree.get(layer - 1).get(size - 2));
				}
				if(tree.get(layer).size() % 2 == 0) {
					layer ++;
				}
				else {
					done = true;
				}
			}
		}
		StringBuilder fout = new StringBuilder();
		while(m -- > 0) {
			st = new StringTokenizer(fin.readLine());
			if(st.nextToken().equals("1")) {
				int i = Integer.parseInt(st.nextToken());
				int v = Integer.parseInt(st.nextToken());
				long diff = v - tree.get(0).get(i);
				for(int l = 0; l < tree.size(); l++) {
					tree.get(l).set(i, tree.get(l).get(i) + diff);
					i /= 2;
				}
			}
			else {
				int l = Integer.parseInt(st.nextToken());
				int r = Integer.parseInt(st.nextToken());
				long ans = 0;
				for(int i = l; i < r; i += 0) {
					boolean done = false;
					int layer = 0;
					int index = i;
					while(!done) {
						int increment = (int) (Math.pow(2, layer + 1));
						int low = (index / 2) * increment;
						int high = low + increment;
						if(low < l || high >= r) {
							done = true;
							ans += tree.get(layer).get(index);
							i += increment / 2;
						}
						else {
							layer ++;
							index /= 2;
						}
					}
				}
				fout.append(ans).append("\n");
			}
		}
		System.out.println(fout);
	}
}