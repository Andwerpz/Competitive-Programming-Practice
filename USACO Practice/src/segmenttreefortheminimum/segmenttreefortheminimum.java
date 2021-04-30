//package segmenttreefortheminimum;

import java.util.*;
import java.io.*;

public class segmenttreefortheminimum {
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
			int next = Integer.MAX_VALUE;	//we do this so that we don't interfere with minimum
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
					tree.get(layer).add(Math.min(tree.get(layer - 1).get(size - 1), tree.get(layer - 1).get(size - 2)));
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
				//long diff = v - tree.get(0).get(i);
				for(int l = 0; l < tree.size(); l++) {
					if(l == 0) {	//special case for first layer, since we actually need to change the value
						tree.get(l).set(i, (long) v);
					}
					else {	//all subsequent layers depend on the value of the value, so we can just compare
						tree.get(l).set(i, Math.min(tree.get(l - 1).get(i * 2), tree.get(l - 1).get(i * 2 + 1))); 
					}
					
					i /= 2;
				}
			}
			else {
				int l = Integer.parseInt(st.nextToken());
				int r = Integer.parseInt(st.nextToken());
				long ans = Integer.MAX_VALUE;
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
							ans = Math.min(tree.get(layer).get(index), ans);
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