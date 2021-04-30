//package berlandregional;

import java.util.*;
import java.io.*;

public class berlandregionalver1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			int n = Integer.parseInt(fin.readLine());
			ArrayList<HashSet<Integer>> sizes = new ArrayList<HashSet<Integer>>();
			ArrayList<ArrayList<Integer>> teams = new ArrayList<ArrayList<Integer>>();
			ArrayList<Integer> teamSizes = new ArrayList<Integer>();
			for(int i = 0; i < n; i++) {
				sizes.add(new HashSet<Integer>());
				teams.add(new ArrayList<Integer>());
				teamSizes.add(0);
			}
			StringTokenizer st = new StringTokenizer(fin.readLine());
			StringTokenizer st2 = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken()) - 1;
				sizes.get(teamSizes.get(next)).add(next);
				teamSizes.set(next, teamSizes.get(next) + 1);
				teams.get(next).add(Integer.parseInt(st2.nextToken()));
			}
			ArrayList<ArrayList<Long>> pfx = new ArrayList<ArrayList<Long>>();
			for(int i = 0; i < n; i++) {
				teams.get(i).sort((a, b) -> -Integer.compare(a, b));
			}
			for(int i = 0; i < n; i++) {
				long sum = 0;
				pfx.add(new ArrayList<Long>());
				pfx.get(i).add(sum);
				for(int j = 0; j < teams.get(i).size(); j++) {
					sum += (long) teams.get(i).get(j);
					pfx.get(i).add(sum);
				}
			}
			for(int i = 1; i <= n; i++) {
				long sum = 0;
				HashSet<Integer> prev = sizes.get(0);
				int index = 0;
				for(int j = 1; j * i <= n; j++) {
					//System.out.print(j * i + " ");
					index = j * i;
					HashSet<Integer> next = sizes.get(index - 1);
					for(int k : prev) {
						if(!next.contains(k)) {
							sum += pfx.get(k).get(index - i);
							////System.out.println("doesn't contain");
						}
					}
					prev = next;
				}
				for(int k : prev) {
					sum += pfx.get(k).get(index);
				}
				//System.out.println();
				fout.append(sum).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}	
