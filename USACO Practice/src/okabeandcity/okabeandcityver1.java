package okabeandcity;

import java.util.*;
import java.io.*;

public class okabeandcityver1 {
	public static void main(String[] args) throws IOException {
		
		//first we organize all the lit squares into nodes with connections in between them
		//then we run dijkstra's algorithm on it to find the shortest path to the end node. 
		
		//hard part of this problem is making the algorithm to make the connections between the nodes.
		//lit nodes are connected if okabe can light up a row that is adjacent to the node he is standing on, and walk to the other lit node.
		//if two nodes are adjacent to each other, then okabe can just walk between them, forgoing the cost of turning on the row or column. 
		//the end node is trickier though, since it can be either lit or unlit. If the end node is lit, then treat it like a normal lit node,
		//but if it is unlit, then you have to apply special connection rules to it. Okabe can only get to the unlit end node if he directly lights it up
		//he can't light up an adjacent node and walk to it like he could with a lit node. This means that an unlit end node makes Okabe always pay
		//one coin
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int[][] nodes = new int[k + 1][2];
		int startNode = 0;
		boolean endNodeLit = false;
		for(int i = 0; i < k; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			if(a == 1 && b == 1) {
				startNode = i;
			}
			else if(a == n && b == n) {
				endNodeLit = true;
				a = -100;
				b = -100;	//removing the ending node if there is one.
			}
			nodes[i] = new int[] {a, b};
		}
		//nodes[k] = new int[] {0, 0};	//starting node
		nodes[k] = new int[] {n - 1, m - 1};	//ending node
		ArrayList<ArrayList<int[]>> connections = new ArrayList<ArrayList<int[]>>();
		for(int i = 0; i < nodes.length; i++) {
			connections.add(new ArrayList<int[]>());
		}
		for(int i = 0; i < nodes.length; i++) {
			int curX = nodes[i][0];
			int curY = nodes[i][1];
			for(int j = i + 1; j < nodes.length; j++) {
				if(curX == nodes[j][0]) {
					if((curY - 1 >= 0 && curY - 1 == nodes[j][1]) || (curY + 1 < m && curY + 1 == nodes[j][1])){
						connections.get(i).add(new int[] {j, 0});
						connections.get(j).add(new int[] {i, 0});
					}
					else {
						connections.get(i).add(new int[] {j, 1});
						connections.get(j).add(new int[] {i, 1});
					}
				}
				else if(curY == nodes[j][1]) {
					if((curX - 1 >= 0 && curX - 1 == nodes[j][0]) || (curX + 1 < n && curX + 1 == nodes[j][0])){
						connections.get(i).add(new int[] {j, 0});
						connections.get(j).add(new int[] {i, 0});
					}
					else {
						connections.get(i).add(new int[] {j, 1});
						connections.get(j).add(new int[] {i, 1});
					}
				}
			}
		}
		boolean[] visited = new boolean[k + 1];
		int[] cost = new int[k + 1];
		Arrays.fill(cost, -1);
		cost[startNode] = 0;	//the first node
		while(true) {
			boolean hasNext = false;
			int next = -1;
			int curCost = Integer.MAX_VALUE;
			for(int i = 0; i < visited.length; i++) {
				if(!visited[i] && cost[i] != -1 && cost[i] < curCost) {
					curCost = cost[i];
					next = i;
					hasNext = true;
				}
			}
			if(!hasNext) {
				break;
			}
			System.out.println(next);
			visited[next] = true;
			for(int i = 0; i < connections.get(next).size(); i++) {
				int pointer = connections.get(next).get(i)[0];
				int destCost = curCost + connections.get(next).get(i)[1];
				if(destCost < cost[pointer] || cost[pointer] == -1) {
					cost[pointer] = destCost;
				}
			}
		}
		
		System.out.println(visited[k]? (cost[k]) : "-1");
	}
}
