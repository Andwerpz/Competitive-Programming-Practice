package inversions2;

import java.util.*;

import java.io.*;

public class inversions2ver1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int treeSize = (int) Math.pow(2, Math.ceil(Math.log(n) / Math.log(2)));
		ArrayList<ArrayList<Integer>> tree = new ArrayList<ArrayList<Integer>>();
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
		StringBuilder fout = new StringBuilder();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		Stack<Integer> s = new Stack<Integer>();
		for(int i = 0; i < n; i++) {
			s.add(Integer.parseInt(st.nextToken()));
		}
		while(s.size() != 0) {
			for(ArrayList<Integer> t : tree) {
				for(Integer i : t) {
					System.out.print(i + " ");
				}
				System.out.println();
			}
			System.out.println();
			
			int next = s.pop() + 1;System.out.println("next: " + next);
			int sum = 0;
			int index = 0;
			for(int i = n - 1; i >= 0; i -= 0) {
				
				int layer = 0;
				int increment = 1;
				index = i;
				System.out.println("before: " + index);
				while(layer + 1  != tree.size()) {
					increment *= 2;
					int temp = index;
					index /= 2;
					layer += 1;
					int low = index * increment;
					int high = low + increment;
					if(high > i || sum + tree.get(layer).get(index) > next) {
						i -= increment / 2;
						index = temp;
						layer --;
						break;
					}
				}
				System.out.println("after : " + layer + " " + index + " sum: " + sum);
				sum += tree.get(layer).get(index);
				if(sum == next) {
					System.out.println(sum + " " + next);
					fout.append(index).append(" ");
					break;
				}
				else if(next == 0) {
					index += 1;
					fout.append(index).append(" ");
					break;
				}
			}
			System.out.println("final index: " + index);
			System.out.println("sum: " + sum);
			index -= 1;
			tree.get(0).set(index, 0);
			for(int l = 1; l < tree.size(); l++) {
				index /= 2;
				int a = tree.get(l - 1).get(index * 2);
				int b = tree.get(l - 1).get(index * 2 + 1);
				tree.get(l).set(index, a + b);
			}
		}
		System.out.println(fout);
	}
}
