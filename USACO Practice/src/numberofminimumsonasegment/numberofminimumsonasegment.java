//package numberofminimumsonasegment;

import java.util.*;
import java.io.*;

public class numberofminimumsonasegment {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int treeSize = (int) Math.pow(2, Math.ceil(Math.log10(n) / Math.log10(2)));
		st = new StringTokenizer(fin.readLine());
		ArrayList<ArrayList<long[]>> tree = new ArrayList<ArrayList<long[]>>();	//use an arraylist to represent the tree, the lowest level is 0, and it goes up
		//to access the parent node from a child, just divide the index by 2, int division is pretty handy
		//long[] so we can count the number of occurrences of the minimum
		for(int i = 0; i < treeSize; i++) {
			int layer = 0;
			int next = Integer.MAX_VALUE;	//we do this so that we don't interfere with minimum
			if(!(i >= n)) {
				next = Integer.parseInt(st.nextToken());
			}
			boolean done = false;
			while(!done) {
				if(tree.size() == layer) {
					tree.add(new ArrayList<long[]>());
				}
				if(layer == 0) {
					tree.get(0).add(new long[] {next, 1});	//second number is the number of occurrences of the minimum within that segment
				}
				else {
					int size = tree.get(layer - 1).size();
					long[] a = tree.get(layer - 1).get(size - 1);
					long[] b = tree.get(layer - 1).get(size - 2);
					long num[] = new long[] {Math.min(a[0], b[0]), 0};
					if(a[0] == b[0]) {
						num[1] = a[1] + b[1];
					}
					else if(a[0] < b[0]) {
						num[1] = a[1];
					}
					else if(b[0] < a[0]) {
						num[1] = b[1];
					}
					tree.get(layer).add(num);	//TODO need to do insertion in question
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
						tree.get(l).set(i, new long[] {v, 1});
					}
					else {	//all subsequent layers depend on the value of the value, so we can just compare
						long[] a = tree.get(l - 1).get(i * 2);
						long[] b = tree.get(l - 1).get(i * 2 + 1);
						long[] num = new long[2];
						if(a[0] == b[0]) {
							num[0] = a[0];
							num[1] = a[1] + b[1];
						}
						else if(a[0] < b[0]) {
							num[0] = a[0];
							num[1] = a[1];
						}
						else if(b[0] < a[0]) {
							num[0] = b[0];
							num[1] = b[1];
						}
						tree.get(l).set(i, num); 
					}
					
					i /= 2;
				}
			}
			else {
				int l = Integer.parseInt(st.nextToken());
				int r = Integer.parseInt(st.nextToken());
				long ans = 0;
				long min = Integer.MAX_VALUE;
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
							if(min == tree.get(layer).get(index)[0]) {
								ans += tree.get(layer).get(index)[1];
							}
							else if(min > tree.get(layer).get(index)[0]) {
								min = tree.get(layer).get(index)[0];
								ans = tree.get(layer).get(index)[1];
							}
							i += increment / 2;
						}
						else {
							layer ++;
							index /= 2;
						}
					}
				}
				fout.append(min).append(" ").append(ans).append("\n");
			}
		}
		System.out.println(fout);
	}
}