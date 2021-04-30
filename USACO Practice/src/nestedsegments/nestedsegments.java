//package nestedsegments;

import java.util.*;
import java.io.*;

public class nestedsegments {
	
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
	
	public static int getSumInRange(int low, int high) {	//high and low inclusive
		//System.out.println(low + " " + high);
		int sum = 0;
		for(int i = low; i <= high; i += 0) {
			int layer = 0;
			int index = i;
			int increment = 1;
			while(true) {
				layer ++;
				int temp = index;
				index /= 2;
				increment *= 2;
				int l = index * increment;
				int h = low + increment;
				if(l < low || h > high) {
					layer--;
					index = temp;
					i += increment / 2;
					break;
				}
			}
			sum += tree.get(layer).get(index);
		}
		return sum;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine()) * 2;
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
					layer++;
				}
				else {
					break;
				}
			}
		}
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int[] leftIndex = new int[n / 2];
		int[] ans = new int[n / 2];
		Arrays.fill(leftIndex, -1);
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken()) - 1;
			if(leftIndex[next] == -1) {
				leftIndex[next] = i;
			}
			else {
				//System.out.println("Searching for nestings under " + next);
				ans[next] = getSumInRange(leftIndex[next], i);
				changeValue(leftIndex[next], 1);
			}
		}
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < ans.length; i++) {
			fout.append(ans[i]).append(" ");
		}
		System.out.println(fout.substring(0, fout.length()));
	}
}
