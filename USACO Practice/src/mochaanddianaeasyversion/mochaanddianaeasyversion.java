//package mochaanddianaeasyversion;

import java.util.*;
import java.io.*;

public class mochaanddianaeasyversion {
	public static void main(String[] args) throws IOException {
		
		//1559D
		
		//given one undirected graph, how do we guarantee that we're not adding cycles? We just have to take a look at the connected components of the graph, and connect them together. 
		//if we draw an edge between two nodes that are already connected, then we just made a cycle. 
		
		//now if we have two graphs, we just have to brute force through all possible edges that we can add, and see which edge connect two different connected components for both graphs.
		//after we connect two components, we also need to update the groups, to make sure that we don't accidentally connect two nodes within the same component.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m1 = Integer.parseInt(st.nextToken());
		int m2 = Integer.parseInt(st.nextToken());
		ArrayList<ArrayList<Integer>> mocha = new ArrayList<ArrayList<Integer>>();
		ArrayList<ArrayList<Integer>> diana = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < n; i++) {
			mocha.add(new ArrayList<Integer>());
			diana.add(new ArrayList<Integer>());
		}
		for(int i = 0; i < m1; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			mocha.get(a).add(b);
			mocha.get(b).add(a);
		}
		for(int i = 0; i < m2; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			diana.get(a).add(b);
			diana.get(b).add(a);
		}
		int[] mochaGroups = new int[n];
		int[] dianaGroups = new int[n];
		boolean[] v = new boolean[n];
		int pointer = 0;
		for(int i = 0; i < n; i++) {
			if(!v[i]) {
				v[i] = true;
				Stack<Integer> s = new Stack<Integer>();
				s.add(i);
				pointer ++;
				while(s.size() != 0) {
					int next = s.pop();
					mochaGroups[next] = pointer;
					for(int j = 0; j < mocha.get(next).size(); j++) {
						if(!v[mocha.get(next).get(j)]) {
							s.add(mocha.get(next).get(j));
							v[mocha.get(next).get(j)] = true;
						}
					}
				}
			}
		}
		v = new boolean[n];
		pointer = 0;
		for(int i = 0; i < n; i++) {
			if(!v[i]) {
				v[i] = true;
				Stack<Integer> s = new Stack<Integer>();
				s.add(i);
				pointer ++;
				while(s.size() != 0) {
					int next = s.pop();
					dianaGroups[next] = pointer;
					for(int j = 0; j < diana.get(next).size(); j++) {
						if(!v[diana.get(next).get(j)]) {
							s.add(diana.get(next).get(j));
							v[diana.get(next).get(j)] = true;
						}
					}
				}
			}
		}
		int ans = 0;
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(mochaGroups[i] != mochaGroups[j] && dianaGroups[i] != dianaGroups[j]) {
					ans ++;
					fout.append(i + 1).append(" ").append(j + 1).append("\n");
					int prevMocha = mochaGroups[i];
					int nextMocha = mochaGroups[j];
					int prevDiana = dianaGroups[i];
					int nextDiana = dianaGroups[j];
					for(int k = 0; k < n; k++) {
						if(mochaGroups[k] == prevMocha) {
							mochaGroups[k] = nextMocha;
						}
						if(dianaGroups[k] == prevDiana) {
							dianaGroups[k] = nextDiana;
						}
					}
				}
			}
		}
		System.out.print(ans + "\n" + fout);
	}
}
