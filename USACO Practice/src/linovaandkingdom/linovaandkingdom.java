//package linovaandkingdom;

import java.util.*;
import java.io.*;

public class linovaandkingdom {
	public static void main(String[] args) throws IOException{
		
		//1336A
		
		//too lazy to finish this solution
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		ArrayList<TreeSet<int[]>> degrees = new ArrayList<TreeSet<int[]>>();
		ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<Integer>());
		}
		for(int i = 0; i < n - 1; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			c.get(a).add(b);
			c.get(b).add(a);
		}
		boolean[] v = new boolean[n];
		ArrayDeque<Integer> q = new ArrayDeque<Integer>();
		ArrayDeque<Integer> d = new ArrayDeque<Integer>();
		d.add(0);
		q.add(0);
		v[0] = true;
		while(q.size() != 0) {
			int cur = q.pop();
			int deg = d.pop();
			int numBelow = 0;
			for(int i = 0; i < c.get(cur).size(); i++) {
				int next = c.get(cur).get(i);
				if(!v[next]) {
					v[next] = true;
					q.add(next);
					d.add(deg + 1);
					numBelow ++;
				}
			}
			//System.out.println(cur);
			if(deg > degrees.size() - 1) {
				degrees.add(new TreeSet<int[]>((a, b) -> Comparator.compareIntArr(a, b)));
			}
			degrees.get(deg).add(new int[] {numBelow, cur});
		}
//		for(TreeSet<int[]> i : degrees) {
//			for(int[] j : i) {
//				System.out.print(j[0] + " " + j[1] + ", ");
//				
//			}System.out.println();
//		}
		int[] values = new int[n];
		int ans = 0;
		for(int i = degrees.size() - 1; i >= 0; i--) {
			while(degrees.get(i).size() != 0) {
				int[] next = degrees.get(i).pollFirst();
				values[next[1]] = i - next[0];
			}
		}
		Arrays.sort(values);
		for(int i = values.length - 1; i >= 0; i--) {
			ans += values[i];
			k --;
			if(k == 0) {
				break;
			}
		}
		System.out.println(ans);
	}
	
	static class Comparator {
		public static int compareIntArr(int[] a, int[] b) {
			return Integer.compare(a[0], b[0]) != 0? Integer.compare(a[0], b[0]) : Integer.compare(a[1], b[1]);
		}
	}
}
