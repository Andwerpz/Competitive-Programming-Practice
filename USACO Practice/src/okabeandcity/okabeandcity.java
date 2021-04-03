//package okabeandcity;

import java.util.*;
import java.io.*;

public class okabeandcity {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int start = 0;
		boolean endLit = false;
		int[][] nodes = new int[k + 1][2];
		for(int i = 0; i < k; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			nodes[i] = new int[] {a, b};
			if(a == 1 && b == 1) {
				start = i;
			}
			else if(a == n && b == m) {
				endLit = true;
				nodes[i] = new int[] {-100, -100};	//making sure that there are no connections to this node, we're going to add a custom end node later
			}
		}
		nodes[k] = new int[] {n, m};
		ArrayList<ArrayList<int[]>> connections = new ArrayList<ArrayList<int[]>>();
		for(int i = 0; i < k + 1; i++) {
			connections.add(new ArrayList<int[]>());
		}
		for(int i = 0; i < k + 1; i++) {
			int x = nodes[i][0];
			int y = nodes[i][1];
			for(int j = i + 1; j < k + 1; j++) {
				int curX = nodes[j][0];
				int curY = nodes[j][1];
				if(j == k && !endLit) {	//checking whether or not this node is the end node. We only run this section if the end is not lit up
					if((x - 1 <= curX && x + 1 >= curX) || (y - 1 <= curY && y + 1 >= curY)) {
						connections.get(i).add(new int[] {j, 1});
						connections.get(j).add(new int[] {i, 1});
					}
				}
				else {
					if(x - 1 <= curX && x + 1 >= curX && y == curY) {	//adjacency checks
						connections.get(i).add(new int[] {j, 0});
						connections.get(j).add(new int[] {i, 0});
					}
					else if(y - 1 <= curY && y + 1 >= curY && x == curX) {	
						connections.get(i).add(new int[] {j, 0});
						connections.get(j).add(new int[] {i, 0});
					}
					else if(x - 2 <= curX && x + 2 >= curX) {	//horizontal
						connections.get(i).add(new int[] {j, 1});
						connections.get(j).add(new int[] {i, 1});
					}
					else if(y - 2 <= curY && y + 2 >= curY) {	//vertical
						connections.get(i).add(new int[] {j, 1});
						connections.get(j).add(new int[] {i, 1});
					}
				}
			}
		}
		
//		for(ArrayList<int[]> i : connections) {
//			for(int[] j : i) {
//				System.out.print(j[0] + " ");
//			}
//			System.out.println();
//		}
		
		boolean[] visited = new boolean[k + 1];
		int[] cost = new int[k + 1];
		Arrays.fill(cost, -1);
		cost[start] = 0;
		while(true) {
			int curCost = Integer.MAX_VALUE;
			int cur = -1;
			for(int i = 0; i < cost.length; i++) {
				if((cost[i] != -1 && curCost > cost[i]) && !visited[i]) {
					curCost = cost[i];
					cur = i;
				}
			}
			if(cur == -1) {
				break;
			}
			visited[cur] = true;
			//System.out.println(cur + " " + curCost);
			for(int i = 0; i < connections.get(cur).size(); i++) {
				int destCost = curCost + connections.get(cur).get(i)[1];
				int pointer = connections.get(cur).get(i)[0];
				if(destCost < cost[pointer] || cost[pointer] == -1) {
					cost[pointer] = destCost;
				}
			}
		}
		System.out.println(visited[k]? (cost[k]) : "-1");
	}
}
