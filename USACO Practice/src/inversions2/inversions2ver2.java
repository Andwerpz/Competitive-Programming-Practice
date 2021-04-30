package inversions2;

import java.util.*;

import java.io.*;

public class inversions2ver2 {
	
	static ArrayList<ArrayList<Integer>> tree;
	
	public static void changeValue(int index, int value) {
		tree.get(0).set(index, value);
		for(int l = 1; l < tree.size(); l++) {
			index /= 2;
			int a = tree.get(l - 1).get(index * 2);
			int b = tree.get(l - 1).get(index * 2 + 1);
			tree.get(l).set(index, a + b);
		}
	}
	
	public static int getRange(int target, int start) {	//we look to the left of the start index, return the index of the number that goes over the sum
		int sum = 0;
		for(int i = tree.get(0).size() - 1; i >= 0; i -= 0) {
			//System.out.println(i);
			int layer = 0;
			int index = i;
			int increment = 1;
			while(true) {
				if(layer == 0 && tree.get(0).get(index) + sum > target) {
					return index;
				}
				layer ++;
				int temp = index;
				index /= 2;
				increment *= 2;
				if(tree.get(layer).get(index) + sum > target) {
					layer --;
					index = temp;
					i -= increment / 2;
					break;
				}
			}
			sum += tree.get(layer).get(index);
			//System.out.println("sum " + sum);
		}
		return 0;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int treeSize = (int) Math.pow(2, Math.ceil(Math.log(n) / Math.log(2)));
		tree = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < treeSize; i++) {
			int layer = 0;
			while(true) {
				if(layer == tree.size()) {
					tree.add(new ArrayList<Integer>());
				}
				if(layer == 0) {
					tree.get(0).add(i < n? 1 : 0);
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
		//System.out.println();
		for(ArrayList<Integer> i : tree) {
			for(int j : i) {
				//System.out.print(j + " ");
			}
			//System.out.println();
		}
		ArrayList<Integer> ans = new ArrayList<Integer>();
		StringBuilder fout = new StringBuilder();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		Stack<Integer> s = new Stack<Integer>();
		for(int i = 0; i < n; i++) {
			s.add(Integer.parseInt(st.nextToken()));
		}
		while(s.size() != 0) {
			//System.out.println("new test : " + s.peek());
			int index = getRange(s.pop(), n - 1);
			ans.add(index + 1);
			changeValue(index, 0);
		}
		for(int i = ans.size() - 1; i >= 0; i--) {
			fout.append(ans.get(i)).append(" ");
		}
		System.out.println(fout.substring(0, fout.length() - 1));
	}
}
