package cereal2;

import java.util.*;
import java.io.*;

public class cereal2 {
	public static void main(String[] args) throws IOException {
		
		//USACO Silver 2022 Feb
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		ArrayList<ArrayList<int[]>> c = new ArrayList<ArrayList<int[]>>();
		boolean[] v = new boolean[m];
		for(int i = 0; i < m; i++) {
			c.add(new ArrayList<int[]>());
		}
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			//next box, cow id, first or second
			c.get(a).add(new int[] {b, i + 1, 1});
			c.get(b).add(new int[] {a, i + 1, 0});
		}
		ArrayList<Integer> ans = new ArrayList<Integer>();
		HashSet<Integer> cows = new HashSet<Integer>();						
		HashSet<Integer> desperate = new HashSet<Integer>();
		for(int i = 0; i < n; i++) {
			cows.add(i + 1);
		}
		for(int i = 0; i < m; i++) {
			if(!v[i]) {
				System.out.println(i + "------");
				Stack<Integer> s = new Stack<Integer>();
				v[i] = true;
				//select first cow
				boolean isThereFirst = false;
				for(int[] j : c.get(i)) {
					if(j[2] == 1 && cows.contains(j[1])) {
						isThereFirst = true;
						ans.add(j[1]);
						cows.remove(j[1]);
						break;
					}
				}
				if(!isThereFirst) {
					continue;
				}
				System.out.println("there is first");
				for(int[] j : c.get(i)) {
					if(cows.contains(j[1]) && !v[j[0]]) {
						s.add(j[0]);
						v[j[0]] = true;
						if(j[2] == 1) {
							desperate.add(j[1]);
						}
					}
				}
				while(s.size() != 0) {
					int next = s.pop();
					isThereFirst = false;
					for(int[] j : c.get(next)) {
						if(cows.contains(j[1])) {
							isThereFirst = true;
							ans.add(j[1]);
							cows.remove(j[1]);
							break;
						}
					}
					if(!isThereFirst) {
						continue;
					}
					for(int[] j : c.get(next)) {
						if(cows.contains(j[1]) && !v[j[0]]) {
							s.add(j[0]);
							v[j[0]] = true;
						}
					}
				}
			}
		}
		StringBuilder fout = new StringBuilder();
		fout.append(n - ans.size()).append("\n");
		for(int i : ans) {
			fout.append(i).append("\n");
		}
		for(int i : cows) {
			fout.append(i).append("\n");
		}
		System.out.print(fout);
	}
}
