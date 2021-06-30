//package andryushaandcoloredballoons;

import java.util.*;
import java.io.*;

public class andryushaandcoloredballoons {
	public static void main(String[] args) throws IOException {
		
		//780C
		
		//we are given a tree, and our job is to make it so that any three consecutive nodes are of a different color. 
		//the fact that the graph is a tree makes this far easier. We don't have to worry about loops in the graph. 
		//to determine the number of unique colors that we need to color this graph, all we have to do is find the node with the most connections, and
		//add 1. We can say this since in order to satisfy the requirement that any sequence of three nodes being a different color, any given node
		//and it's connections must all be different colors. To actually color the graph is pretty simple. All you do is start at one node, and assign it a color. 
		//assign it's adjacent nodes different colors, and do the same for all nodes, reusing colors whenever possible.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
		int[] colors = new int[n];
		Arrays.fill(colors, -1);
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<Integer>());
		}
		int max = 0;
		for(int i = 0; i < n - 1; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			c.get(a).add(b);
			c.get(b).add(a);
		}
		for(ArrayList<Integer> i : c) {
			max = Math.max(i.size(), max);
		}
		max ++;
		Stack<Integer> s = new Stack<Integer>();
		HashSet<Integer> v = new HashSet<Integer>();
		s.add(0);
		v.add(0);
		colors[0] = 0;
		while(s.size() != 0) {
			//System.out.println("LOOP");
			int next = s.pop();
			HashSet<Integer> usedColors = new HashSet<Integer>();
			usedColors.add(colors[next]);
			for(int i = 0; i < c.get(next).size(); i++) {
				if(colors[c.get(next).get(i)] != -1) {
					usedColors.add(colors[c.get(next).get(i)]);
				}
			}
			int pointer = 0;
			for(int i = 0; i < c.get(next).size(); i++) {
				while(usedColors.contains(pointer)) {
					pointer ++;
				}
				if(!v.contains(c.get(next).get(i))) {
					s.add(c.get(next).get(i));
					v.add(c.get(next).get(i));
					colors[c.get(next).get(i)] = pointer;
					usedColors.add(pointer);
					pointer ++;
				}
			}
		}
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < n; i++) {
			fout.append(colors[i] + 1).append(" ");
		}
		System.out.println(max + "\n" + fout);
	}
}
