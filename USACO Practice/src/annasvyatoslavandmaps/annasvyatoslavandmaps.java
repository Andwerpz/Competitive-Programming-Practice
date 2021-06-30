//package annasvyatoslavandmaps;

import java.util.*;
import java.io.*;

public class annasvyatoslavandmaps {
	
	static ArrayList<ArrayList<Integer>> c;
	static ArrayList<HashMap<Integer, Integer>> paths;
	
	public static void shortestPaths(int start) {
		boolean[] v = new boolean[c.size()];
		HashMap<Integer, Integer> curPaths = new HashMap<Integer, Integer>();
		Queue<Integer> q = new ArrayDeque<Integer>();
		Queue<Integer> costs = new ArrayDeque<Integer>();
		q.add(start);
		costs.add(0);
		v[start] = true;
		while(q.size() != 0) {
			int cur = q.poll();
			int curCost = costs.poll();
			for(int i = 0; i < c.get(cur).size(); i++) {
				int next = c.get(cur).get(i);
				if(!v[next]) {
					v[next] = true;
					q.add(next);
					costs.add(curCost + 1);
					curPaths.put(next, curCost + 1);
				}
			}
		}
		paths.add(curPaths);
	}
	
	public static void main(String[] args) throws IOException {
		
		//1204C
		
		//generate matrix of shortest path from every node to every node. Then when you go through the path, use a greedy approach. Add node 1 of the given path to your answer
		//and then look to the next node. On the ith node of the path, if the minimum cost from the last node in the answer to the ith node is less than the cost given by the given
		//path, add the i - 1th node, and move on.
		//add the mth node, and you're done.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		c = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<Integer>());
			char[] s = fin.readLine().toCharArray();
			for(int j = 0; j < n; j++) {
				if(s[j] == '1') {
					c.get(i).add(j);
				}
			}
		}
		paths = new ArrayList<HashMap<Integer, Integer>>();
		for(int i = 0; i < n; i++) {
			shortestPaths(i);
		}
		int m = Integer.parseInt(fin.readLine());
		int[] nums = new int[m];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int pointer = 0;
		StringBuilder fout = new StringBuilder();
		int counter = 0;
		//System.out.println(paths);
		for(int i = 0; i < m; i++) {
			int next = Integer.parseInt(st.nextToken()) - 1;
			nums[i] = next;
			if(i == 0) {
				counter ++;
				fout.append(next + 1).append(" ");
			}
			else {
				//System.out.println(i + " " + pointer + ": " + nums[pointer] + " " + next);
				int pathCost = i - pointer;
				int minCost = nums[pointer] == next? 0 : paths.get(nums[pointer]).get(next);
				//System.out.println("PATH: " + pathCost + " MIN COST: " + minCost);
				if(pathCost > minCost) {
					//System.out.println("ADD");
					counter ++;
					fout.append(nums[i - 1] + 1).append(" ");
					pointer = i - 1;
				}
			}
		}
		counter ++;
		fout.append(nums[m - 1] + 1);
		System.out.println(counter + "\n" + fout);
	}
}
