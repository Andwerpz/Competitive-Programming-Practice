//package inversions;

import java.util.*;
import java.io.*;

public class inversions {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int treeSize = (int) (Math.pow(2, Math.ceil(Math.log10(n) / Math.log10(2))));
		ArrayList<ArrayList<Integer>> tree = new ArrayList<ArrayList<Integer>>();
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
		StringTokenizer st = new StringTokenizer(fin.readLine());
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < n; i++) {
			
			
			int next = Integer.parseInt(st.nextToken());
			int sum = 0;
			for(int j = treeSize - 1; j >= next; j -= 0) {
				int layer = 0;
				int index = j;
				while(true) {
					int increment = (int) Math.pow(2, layer + 1);
					int low = (index / 2) * increment;
					int high = low + increment;
					if(low < next) {
						j -= increment / 2;
						sum += tree.get(layer).get(index);
						//System.out.println(low + " " + high);
						break;
					}
					else {
						index /= 2;
						layer ++;
					}
				}
				//System.out.println(j);
			}
			int index = next - 1;
			tree.get(0).set(index, 1);
			index /= 2;
			for(int l = 1; l < tree.size(); l++) {
				tree.get(l).set(index, tree.get(l).get(index) + 1);
				index /= 2;
			}
			fout.append(sum).append(" ");
			//System.out.println("the sum is " + sum);
		}
		System.out.print(fout.substring(0, fout.length() - 1));
	}
}
