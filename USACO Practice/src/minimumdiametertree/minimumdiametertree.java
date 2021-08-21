//package minimumdiametertree;

import java.util.*;
import java.io.*;

public class minimumdiametertree {
	public static void main(String[] args) throws IOException {
		
		//1085D
		
		//the only edges you want to put weight on is the edges leading to verticies. Split the weight evenly across them, so that the maximum weight will always be 
		//(s / numVerticieEdges) * 2, or in case that there is only 1 edge: s.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		double s = Integer.parseInt(st.nextToken());
		ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<Integer>());
		}
		int[][] edges = new int[n - 1][2];
		for(int i = 0; i < n - 1; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			edges[i][0] = a;
			edges[i][1] = b;
			c.get(a).add(b);
			c.get(b).add(a);
		}
		int numEdgeVerticies = 0;
		for(int i = 0; i < edges.length; i++) {
			int a = edges[i][0];
			int b = edges[i][1];
			if(c.get(a).size() == 1 || c.get(b).size() == 1) {
				numEdgeVerticies ++;
			}
		}
		System.out.println(numEdgeVerticies != 1? (s / (double) numEdgeVerticies) * 2 : s);
	}
}
