//package numbersontree;

import java.util.*;
import java.io.*;

public class numbersontree {
	
	static ArrayList<ArrayList<Integer>> c;
	static int[] nums;
	static boolean isValid;
	
	public static ArrayList<Integer> getAns(int node) {
		//System.out.println(node);
		int midVal = nums[node];
		ArrayList<Integer> ans = new ArrayList<Integer>();
		if(c.get(node).size() == 0) {
			if(midVal != 0) {
				isValid = false;
			}
			ans.add(node);
			return ans;
		}
		else {
			if(midVal == 0) {
				ans.add(node);
			}
			for(int i = 0; i < c.get(node).size(); i++) {
				ArrayList<Integer> nextAns = getAns(c.get(node).get(i));
				for(int j : nextAns) {
					ans.add(j);
					if(ans.size() == midVal) {
						ans.add(node);
					}
				}
			}
			if(midVal > ans.size()) {
				isValid = false;
			}
			return ans;
		}
	}
	
	public static void main(String[] args) throws IOException {
		
		//1286B
		
		//recursive. consider the root node. you can determine the value of all the nodes in its subtrees, and then insert the root node at the correct location. notice that the values of one subtree do not affect
		//the values of another subtree if they do not share any verticies.
		
		//do a recursive search from the root node.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		c = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<Integer>());
		}
		int rootIndex = 0;
		nums = new int[n];
		for(int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int val = Integer.parseInt(st.nextToken());
			if(a != -1) {
				c.get(a).add(i);
			}
			else {
				rootIndex = i;
			}
			nums[i] = val;
		}
		isValid = true;
		ArrayList<Integer> ans = getAns(rootIndex);
		StringBuilder fout = new StringBuilder();
		if(isValid) {
			fout.append("YES\n");
			int[] printAns = new int[n];
			for(int i = 0; i < ans.size(); i++) {
				int next = ans.get(i);
				printAns[next] = i + 1;
			}
			for(int i : printAns) {
				fout.append(i).append(" ");
			}
			fout.append("\n");
		}
		else {
			fout.append("NO\n");
		}
		System.out.println(fout);
	}
}
