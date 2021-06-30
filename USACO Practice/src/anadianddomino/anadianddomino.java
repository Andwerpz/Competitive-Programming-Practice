//package anadianddomino;

import java.util.*;
import java.io.*;

public class anadianddomino {
	
	static int[][] c;
	static int ans;
	
	public static void permute(int[] scramble, int k) {
		if(k == 1) {
			int[] temp = new int[scramble.length];
			for(int i = 0; i < scramble.length; i++) {
				temp[i] = scramble[i];
			}
			ans = Math.max(ans, getAns(temp));
		}
		else {
			permute(scramble, k - 1);
			for(int i = 0; i < k - 1; i++) {
				if(k % 2 == 0) {
					int temp = scramble[i];
					scramble[i] = scramble[k - 1];						//swapping elements i and k - 1
					scramble[k - 1] = temp;
				}
				else {
					int temp = scramble[0];
					scramble[0] = scramble[k - 1];						//swapping elements 0 and k - 1
					scramble[k - 1] = temp;
				}
				permute(scramble, k - 1);
			}
		}
	}
	
	public static int getAns(int[] nodes) {
		int max = 0;
		HashSet<ArrayList<Integer>> dominoes = new HashSet<ArrayList<Integer>>();
		for(int i = 0; i < c.length; i++) {
			int a = nodes[c[i][0]];
			int b = nodes[c[i][1]];
			if(a == 7) {
				a = 6;
			}
			if(b == 7) {
				b = 6;
			}
			ArrayList<Integer> temp = new ArrayList<Integer>(Arrays.asList(a, b));
			if(a <= 6 && b <= 6 && a <= b && !dominoes.contains(temp)) {
				dominoes.add(temp);
				max ++;
			}
			b = nodes[c[i][0]];
			a = nodes[c[i][1]];
			if(a == 7) {
				a = 6;
			}
			if(b == 7) {
				b = 6;
			}
			temp = new ArrayList<Integer>(Arrays.asList(a, b));
			if(a <= 6 && b <= 6 && a <= b && !dominoes.contains(temp)) {
				dominoes.add(temp);
				max ++;
			}
		}
		//System.out.println(dominoes);
		return max;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1210A
		
		//since each node can only have 1 number of domino pointing at it, you can just set each node to a value beforehand, and then test the edges to see if they line up with dominoes. 
		//since there are only 7 nodes, we can generate all possible permutations of values for each node. In the case of 7 nodes, we have to set the 7th node to a value of 6.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		c = new int[m][2];
		for(int i = 0; i < m; i++) {
			st = new StringTokenizer(fin.readLine());
			c[i] = new int[] {Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()) - 1};
		}
		int[] permutation = new int[n];
		for(int i = 0; i < n; i++) {
			permutation[i] = i + 1;
		}
		permute(permutation, n);
		System.out.println(ans);
	}
}
